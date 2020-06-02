#include "File_GFX.h"
#include "Grafici-GFX/src/Grafici.h"

int main()
{

	/* taxonomy from https://vcg.seas.harvard.edu/files/pfister/files/viztaxonomy2013.pdf */

	{
		/* simple plot */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/simple_plot.bmp");
		grafici.begin(gfx, Colors::blackAndWhite);

		Linear x(num_elem);
		ArrayFloat y(array, num_elem);
		Constant c(num_elem, 1);

		grafici.clear();
		grafici.plot(line, x, y, c);
		gfx.flush();
	}

	{
		/* linear interpolation */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/linear_interpolation.bmp");
		grafici.begin(gfx, Colors::rainbow);

		Linear x(num_elem);
		ArrayFloat y(array, num_elem);
		// Chose a big enough number for the samples. Too small and you risk sub-sampling issues
		// Even better chose samples = n + (n-1) * x
		LinearInterpolator dataLinear{ x, y, y, y, 85 };

		grafici.clear();
		grafici.plot(line, dataLinear);
		gfx.flush();
	}

	{
		/* spline interpolation */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/spline_interpolation.bmp");
		grafici.begin(gfx, Colors::rainbow);

		Linear x(num_elem);
		ArrayFloat y(array, num_elem);
		SplineInterpolator dataSpline{ x, y, y, y, 100 };

		grafici.clear();
		grafici.plot(line, dataSpline);
		gfx.flush();
	}

	{
		/* Multiplot */
		constexpr size_t source_data_size = 6;
		constexpr size_t spline_size = 100;
		constexpr size_t histogram_size = 20;
		float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };

		File_GFX gfx(640, 320, "imgs/multiplot.bmp");
		grafici.begin(gfx, Colors::temperature);
		grafici.clear();

		/* Load raw data */
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		SplineInterpolator dataSpline{ x, y, y, y, spline_size };
		Histogram dataHistogram{ dataSpline.y(), histogram_size };
		BarIndex histogramX(histogram_size);
		Constant dataOpt(histogram_size, 0.3);

		Boundary barBoundary;
		Boundary lineBoundary;
		barBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 }).boundaryRotation() = BoundaryRotation::clockWise90;
		lineBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 });
		grafici.plot(bar, histogramX, dataHistogram, histogramX, dataOpt, barBoundary);
		grafici.plot(line, dataSpline, lineBoundary);
		gfx.flush();
	}

	{
		/* Subplot */
		constexpr size_t source_data_size = 6;
		constexpr size_t spline_size = 100;
		constexpr size_t histogram_size = 10;
		float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };

		File_GFX gfx(640, 320, "imgs/subplot.bmp");
		grafici.begin(gfx, Colors::csParula);
		grafici.clear();

		/* Load raw data */
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);

		SplineInterpolator dataSpline{ x, y, y, y, spline_size };
		Boundary leftBoundary;

		leftBoundary.cropGridCartesian(1, 2, 0, 0).cropAbsoluteCartesian({ 0.04, 0.02 }, { 0.04, 0.04 });
		grafici.plot(line, dataSpline, leftBoundary);

		/* Bar chart + histogram */
		Histogram dataHistogram{ dataSpline.y(), histogram_size };
		/* TODO extend BarIndex to allow for group bar chart */
		BarIndex histogramX(histogram_size);

		Boundary rightTopBoundary;
		rightTopBoundary.cropGridCartesian(2, 2, 0, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.04, 0.02 });
		grafici.plot(bar, histogramX, dataHistogram, histogramX, Constant(histogram_size, 0.5), rightTopBoundary);

		/* Stripe graph */
		Boundary rightBottomBoundary;
		Constant barY(spline_size, 1.0);

		rightBottomBoundary.cropGridCartesian(2, 2, 1, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.02, 0.04 });
		grafici.plot(bar, dataSpline.y(), barY, dataSpline.y(), Constant(spline_size, 0.0), rightBottomBoundary);

		gfx.flush();
	}

	{
		/* styles plot */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/styles.bmp");
		grafici.begin(gfx, Colors::blackAndWhite);
		grafici.clear();

		Linear x(num_elem);
		ArrayFloat y(array, num_elem);
		Constant opt(num_elem, 0.01);
		Constant optBar(num_elem, 0);
		Constant c(num_elem, 1);
		Boundary boundary;

		/* TODO scatter size to behave like barplot thickness? */

		boundary.cropAbsoluteCartesian({ 0.04, 0.04 }, { 0.04, 0.04 });
		grafici.plot(scatter, x, y, c, opt, boundary);
		grafici.plot(line, x, y, c, boundary);
		grafici.plot(bar, x, y, c, optBar, boundary);
		gfx.flush();
	}

	{
		/* Boundaries */

		constexpr size_t source_data_size = 9;
		constexpr size_t spline_size = 97;
		float array[source_data_size] = { 0, 2, 0, 1.5, 0, 0.5, 0, 1, 0 };

		File_GFX gfx(640, 320, "imgs/boundaries.bmp");
		grafici.begin(gfx, Colors::csParula);
		grafici.clear();

		/* Load raw data */
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		SplineInterpolator dataSpline{ x, y, y, y, spline_size };

		// axisPlot.numAxisX = 10;
		// axisPlot.numAxisY = 4;

		Boundary leftBoundary;
		leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 }).cropGridCartesian(1, 2, 0, 0);
		grafici.plot(line, dataSpline, leftBoundary);

		PolarBoundary rightBoundary;
		rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 }).cropGridCartesian(1, 2, 0, 1);
		grafici.plot(line, dataSpline, rightBoundary);

		gfx.flush();
	}

	// {
	// 	/* Round 2 */
	// 	DataSource::Float dataset;
	// 	DataSource::Spline dataSpline;
	// 	RoundBoundary roundBoundary;

	// 	float dataArray[9] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };

	// 	File_GFX gfx(640, 320, "imgs/round_2.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 9);
	// 	dataSpline.begin(dataset, 100);
	// 	axisPlot.numAxisX = 10;
	// 	axisPlot.numAxisY = 4;

	// 	grafici.clear();

	// 	roundBoundary.fullScreen().subBoundary(1, 2, 0).crop(0.02, 0.02, 0.02, 0.02);
	// 	roundBoundary.subBoundaryRadial(1, 2, 0);
	// 	grafici.plot(axisPlot, dataSpline, roundBoundary);
	// 	grafici.plot(barPlot, dataSpline, roundBoundary);

	// 	roundBoundary.fullScreen().subBoundary(1, 2, 1).crop(0.02, 0.02, 0.02, 0.02);
	// 	roundBoundary.cropRadial(0.5, 0.1, 0.25, 0);
	// 	grafici.plot(axisPlot, dataSpline, roundBoundary);
	// 	grafici.plot(barPlot, dataSpline, roundBoundary);

	// 	roundBoundary.fullScreen().subBoundary(1, 2, 1);
	// 	roundBoundary.cropRadial(0, 0.6, 0.25, 0);
	// 	grafici.plot(axisPlot, dataSpline, roundBoundary);
	// 	grafici.plot(line, dataSpline, roundBoundary);

	// 	gfx.flush();
	// }

	// {
	// 	/* Colors */
	// 	DataSource::Float dataset;
	// 	DataSource::LinearInterpolator dataLinearInterpolator;
	// 	RoundBoundary roundBoundary;

	// 	float dataArray[2] = { 2, 2 };

	// 	File_GFX gfx(640, 320, "imgs/colors.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 2);
	// 	dataset.yMin = 0; /* ovverride min value */
	// 	dataLinearInterpolator.begin(dataset, 100);
	// 	grafici.style.colorSource = ColorSource::computeFromX;

	// 	grafici.clear();

	// 	ColorSet colorPlots[] = { csBright,
	// 		                      csBw,
	// 		                      csCmyk,
	// 		                      csFrance,
	// 		                      csHeat,
	// 		                      csNeon,
	// 		                      csParula,
	// 		                      csRainbow };

	// 	for (int i = 0; i < sizeof(colorPlots) / sizeof(ColorSet); i++)
	// 	{
	// 		grafici.style.setPalette(colorPlots[i]);
	// 		roundBoundary.fullScreen().subBoundary(2, 4, i).crop(0.02, 0.02, 0.02, 0.02);
	// 		roundBoundary.cropRadial(0, 0.25, 0, 0);
	// 		grafici.plot(barPlot, dataLinearInterpolator, roundBoundary);
	// 	}

	// 	gfx.flush();
	// }

	// {
	// 	DataSource::Float dataset;
	// 	DataSource::LinearInterpolator dataLinearInterpolator;
	// 	DataSource::Spline dataSpline;
	// 	Histogram dataHist;
	// 	/* == INTERPOLATION == */
	// 	//float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
	// 	float dataArrayY[13] = { 0, 5, 10, 10, 0, 0, -10, -10, 0, 0, 10, 0, 0 };

	// 	Adafruit_GFX *gfx = new File_GFX(1024, 768, "interpolation.bmp");

	// 	grafici.begin(*gfx);

	// 	grafici.style.colorPalette = &csBright;
	// 	grafici.style.colorSource = ColorSource::computeFromX;

	// 	dataset.begin(dataArrayY, dataArrayY, 13);
	// 	dataLinearInterpolator.begin(dataset, 100);
	// 	dataSpline.begin(dataset, 100);

	// 	grafici.clear();
	// 	barPlot.thickness = 0.0;

	// 	grafici.boundary.subBoundary(1, 3, 0);
	// 	grafici.boundary.crop(0.04, 0.04, 0.04, 0.02);
	// 	grafici.plot(axisPlot, dataset);
	// 	grafici.plot(line, dataset);
	// 	grafici.plot(barPlot, dataset);

	// 	grafici.boundary.fullScreen();
	// 	grafici.boundary.subBoundary(1, 3, 1);
	// 	grafici.boundary.crop(0.04, 0.04, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataLinearInterpolator);
	// 	grafici.plot(line, dataLinearInterpolator);
	// 	grafici.plot(barPlot, dataLinearInterpolator);

	// 	grafici.boundary.fullScreen();
	// 	grafici.boundary.subBoundary(1, 3, 2);
	// 	grafici.boundary.crop(0.04, 0.04, 0.02, 0.04);
	// 	grafici.plot(axisPlot, dataSpline);
	// 	grafici.plot(line, dataSpline);
	// 	grafici.plot(barPlot, dataSpline);

	// 	//flush to file
	// 	((File_GFX *)gfx)->flush();
	// }

	// {
	// 	DataSource::Float dataset;
	// 	DataSource::LinearInterpolator dataLinearInterpolator;
	// 	DataSource::Spline dataSpline;
	// 	Histogram dataHist;
	// 	/* == COLOR SCHEMES == */
	// 	float dataArrayY[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	// 	Adafruit_GFX *gfx = new File_GFX(1024, 768, "color_schemes.bmp");

	// 	grafici.begin(*gfx);
	// 	grafici.style.colorSource = ColorSource::computeFromX;

	// 	// dataset - we provide the same array for Y and values so that the color encodes the bar height
	// 	dataset.begin(dataArrayY, dataArrayY, 11);
	// 	dataSpline.begin(dataset, 20);

	// 	ColorSet colorPalettes[6] = { csRainbow, csBright, csFrance, csCmyk, csHeat, csBw };

	// 	barPlot.thickness = 0.9;

	// 	for (int i = 0; i < 6; i++)
	// 	{
	// 		Boundary boundary;
	// 		grafici.style.colorPalette = &(colorPalettes[i]);

	// 		boundary.subBoundary(2, 3, i);
	// 		grafici.clear(boundary);

	// 		boundary.crop(0.02, 0.02, 0.02, 0.02);
	// 		grafici.plot(barPlot, dataSpline, boundary);
	// 	}

	// 	//flush to file
	// 	((File_GFX *)gfx)->flush();
	// }

	// {
	// 	DataSource::Float dataset;
	// 	DataSource::LinearInterpolator dataLinearInterpolator;
	// 	DataSource::Spline dataSpline;
	// 	Histogram dataHist;
	// 	/* == PLOT STYLES == */
	// 	float dataArrayY[11] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };

	// 	Adafruit_GFX *gfx = new File_GFX(1024, 768, "plot_types.bmp");

	// 	grafici.begin(*gfx);
	// 	grafici.style.colorSource = ColorSource::computeFromY;
	// 	grafici.style.colorPalette = &csCmyk;
	// 	grafici.clear();

	// 	// dataset - we provide the same array for Y and values so that the color encodes the bar height
	// 	dataset.begin(dataArrayY, 1.0, 11);
	// 	dataSpline.begin(dataset, 20);

	// 	Plotter *plots[6] = { &barcodePlot, &barPlot, &line, &scatterPlot, &line, &line };

	// 	barPlot.thickness = 0.9;

	// 	for (int i = 0; i < 6; i++)
	// 	{
	// 		Boundary boundary;
	// 		boundary.subBoundary(2, 3, i);
	// 		boundary.crop(0.02, 0.02, 0.02, 0.02);

	// 		grafici.plot(*plots[i], dataSpline, boundary);
	// 	}

	// 	//flush to file
	// 	((File_GFX *)gfx)->flush();
	// }

	return 0;
}
