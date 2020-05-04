#include "File_GFX.h"

#include "Grafici-GFX/src/DataSet/LinearInterpolator.h"
#include "Grafici-GFX/src/DataSet/SplineInterpolator.h"
#include "Grafici-GFX/src/DataSource/Array.h"
#include "Grafici-GFX/src/DataSource/Histogram.h"
#include "Grafici-GFX/src/DataSource/Parametric.h"
#include "Grafici-GFX/src/Grafici.h"

//#include "Grafici-GFX/src/plots/line.h"

// #include "Grafici-GFX/src/data/DataSource::Array.h"
// #include "Grafici-GFX/src/data/DataSource::Histogram.h"
// #include "Grafici-GFX/src/data/DataSource::LinearInterpolator.h"
// #include "Grafici-GFX/src/data/DataSource::Spline.h"
// #include "Grafici-GFX/src/plots/axisPlot.h"
// #include "Grafici-GFX/src/plots/barPlot.h"
// #include "Grafici-GFX/src/plots/barcodePlot.h"
// #include "Grafici-GFX/src/plots/line.h"
// #include "Grafici-GFX/src/plots/scatterPlot.h"

int main()
{

	{
		/* simple plot */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/simple_plot.bmp");
		grafici.begin(gfx, Colors::blackAndWhite);

		DataSource::Linear x(num_elem);
		DataSource::Array<float> y(array, num_elem);
		DataSource::Constant c(num_elem, 1);

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

		DataSource::Linear x(num_elem);
		DataSource::Array<float> y(array, num_elem);
		// Chose a big enough number for the samples. Too small and you risk sub-sampling issues
		// Even better chose samples = n + (n-1) * x
		DataSet::LinearInterpolator dataLinear{ x, y, y, y, 85 };

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

		DataSource::Linear x(num_elem);
		DataSource::Array<float> y(array, num_elem);
		DataSet::SplineInterpolator dataSpline{ x, y, y, y, 100 };

		grafici.clear();
		grafici.plot(line, dataSpline);
		gfx.flush();
	}

	{
		/* data histogram */
		constexpr size_t data_elem = 6;
		constexpr size_t spline_elem = 100;
		constexpr size_t hist_elem = 20;
		float array[data_elem] = { 1, 0, 2, 1, 2, 2 };

		File_GFX gfx(640, 320, "imgs/data_histogram.bmp");
		grafici.begin(gfx, Colors::csHeat);

		/* Load raw data */
		DataSource::Linear x(data_elem);
		DataSource::Array<float> y(array, data_elem);

		/* Artificially create more elements to make the histogram more interesting */
		DataSet::SplineInterpolator dataSpline{ x, y, y, y, spline_elem };

		/* Generate the histogram */
		DataSource::Histogram dataHistogram{ dataSpline.y(), hist_elem };
		DataSource::BarIndex histogramX(hist_elem);
		DataSource::Constant dataOpt(hist_elem, 0.5);

		grafici.clear();
		grafici.plot(bar, histogramX, dataHistogram, histogramX, dataOpt);
		gfx.flush();
	}

	{
		/* subplot 1*/
		constexpr size_t data_elem = 6;
		constexpr size_t spline_elem = 100;
		constexpr size_t hist_elem = 20;
		float array[data_elem] = { 1, 0, 2, 1, 2, 2 };

		File_GFX gfx(640, 320, "imgs/subplot_1.bmp");
		grafici.begin(gfx, Colors::csParula);
		grafici.clear();

		/* Load raw data */
		DataSource::Linear x(data_elem);
		DataSource::Array<float> y(array, data_elem);

		DataSet::SplineInterpolator dataSpline{ x, y, y, y, spline_elem };
		Boundary leftBoundary;

		leftBoundary.cropGridCartesian(1, 2, 0, 0);
		grafici.plot(line, dataSpline, leftBoundary);

		// /* Generate the histogram */
		DataSource::Histogram dataHistogram{ dataSpline.y(), hist_elem };
		DataSource::BarIndex histogramX(hist_elem);
		DataSource::Constant dataOpt(hist_elem, 0.5);
		Boundary rightBoundary;

		rightBoundary.cropGridCartesian(1, 2, 0, 1);
		grafici.plot(bar, histogramX, dataHistogram, histogramX, dataOpt, rightBoundary);
		gfx.flush();
	}

	{
		/* subplot 2*/
		constexpr size_t data_elem = 6;
		constexpr size_t spline_elem = 100;
		constexpr size_t hist_elem = 20;
		float array[data_elem] = { 1, 0, 2, 1, 2, 2 };

		File_GFX gfx(640, 320, "imgs/subplot_2.bmp");
		grafici.begin(gfx, Colors::temperature);
		grafici.clear();

		/* Load raw data */
		DataSource::Linear x(data_elem);
		DataSource::Array<float> y(array, data_elem);
		DataSet::SplineInterpolator dataSpline{ x, y, y, y, spline_elem };
		DataSource::Histogram dataHistogram{ dataSpline.y(), hist_elem };
		DataSource::BarIndex histogramX(hist_elem);
		DataSource::Constant dataOpt(hist_elem, 0.1);

		Boundary barBoundary;
		barBoundary.shrinkCartesian({ 0.0, 0.85 }, { 0.0, 0.0 }).boundaryRotation() = BoundaryRotation::clockWise90;
		grafici.plot(bar, histogramX, dataHistogram, histogramX, dataOpt, barBoundary);
		grafici.plot(line, dataSpline);
		gfx.flush();
	}

	/* TODO draw axis */

	// {
	// 	/* Subplot */
	// 	DataSource::Float dataset;
	// 	DataSource::Spline dataSpline;
	// 	DataSource::Histogram dataHist;

	// 	float dataArray[5] = { 1, 0, 2, 2, 1 };

	// 	File_GFX gfx(640, 320, "imgs/subplot.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 5);
	// 	dataSpline.begin(dataset, 100);
	// 	dataHist.begin(dataSpline, 30);

	// 	grafici.clear();

	// 	// set boundary to full screen
	// 	// divide screen in 2 colum and select first one
	// 	// add empty border
	// 	grafici.boundary.fullScreen().subBoundary(1, 2, 0).addBorder(0.04, 0.04, 0.04, 0.02);
	// 	grafici.plot(line, dataSpline);

	// 	// set boundary to full screen
	// 	// divide screen in 2 colum and select first one
	// 	// add empty border
	// 	grafici.boundary.fullScreen().subBoundary(1, 2, 1).addBorder(0.04, 0.04, 0.02, 0.04);
	// 	grafici.plot(barPlot, dataHist);

	// 	gfx.flush();
	// }

	// {
	// 	/* Multiplot */
	// 	DataSource::Float dataset;
	// 	DataSource::Spline dataSpline;

	// 	float dataArray[5] = { 1, 0, 2, 1, 2 };

	// 	File_GFX gfx(640, 320, "imgs/multiplot.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 5);
	// 	dataSpline.begin(dataset, 100);
	// 	scatterPlot.markerSize = 0.0002; // this is defined a proportion of the area of the plot

	// 	grafici.clear();
	// 	grafici.boundary.fullScreen().addBorder(0.04, 0.04, 0.04, 0.04); // add empty border
	// 	grafici.plot(line, dataSpline);                                // keep the same boundary and plot multiple times
	// 	grafici.plot(scatterPlot, dataSpline);

	// 	gfx.flush();
	// }

	// {
	// 	/* Transformations */
	// 	DataSource::Float dataset;
	// 	DataSource::Spline dataSpline;

	// 	float dataArray[5] = { 1, 0, 2, 1, 2 };

	// 	File_GFX gfx(640, 320, "imgs/transformations.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 5);
	// 	dataSpline.begin(dataset, 100);

	// 	grafici.clear();

	// 	grafici.boundary.fullScreen().subBoundary(2, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.plot(barPlot, dataSpline);

	// 	grafici.boundary.fullScreen().subBoundary(2, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.boundary.horizzontalFlip();
	// 	grafici.plot(barPlot, dataSpline);

	// 	grafici.boundary.fullScreen().subBoundary(2, 2, 2).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.boundary.verticalFlip();
	// 	grafici.plot(barPlot, dataSpline);

	// 	grafici.boundary.fullScreen().subBoundary(2, 2, 3).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.boundary.horizzontalFlip().verticalFlip();
	// 	grafici.plot(barPlot, dataSpline);

	// 	gfx.flush();
	// }

	// {
	// 	/* Styles */
	// 	DataSource::Float dataset;
	// 	DataSource::Spline dataSpline;

	// 	float dataArray[5] = { 1, 0, 2, 1, 2 };

	// 	File_GFX gfx(640, 320, "imgs/styles.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 5);
	// 	dataSpline.begin(dataset, 30);

	// 	grafici.clear();
	// 	axisPlot.numAxisX = 9;
	// 	axisPlot.numAxisY = 3;
	// 	scatterPlot.markerSize = 0.0001;

	// 	grafici.boundary.fullScreen().subBoundary(1, 3, 0).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataSpline);
	// 	grafici.plot(line, dataSpline);

	// 	grafici.boundary.fullScreen().subBoundary(1, 3, 1).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataSpline);
	// 	grafici.plot(barPlot, dataSpline);

	// 	grafici.boundary.fullScreen().subBoundary(1, 3, 2).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataSpline);
	// 	grafici.plot(scatterPlot, dataSpline);

	// 	gfx.flush();
	// }

	// {
	// 	/* Round 1 */
	// 	DataSource::Float dataset;
	// 	DataSource::Spline dataSpline;
	// 	RoundBoundary roundBoundary;

	// 	float dataArray[9] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };

	// 	File_GFX gfx(640, 320, "imgs/round_1.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 9);
	// 	dataSpline.begin(dataset, 100);
	// 	axisPlot.numAxisX = 10;
	// 	axisPlot.numAxisY = 4;

	// 	grafici.clear();

	// 	grafici.boundary.fullScreen().subBoundary(1, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataSpline);
	// 	grafici.plot(barPlot, dataSpline);

	// 	roundBoundary.fullScreen().subBoundary(1, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataSpline, roundBoundary);
	// 	grafici.plot(barPlot, dataSpline, roundBoundary);

	// 	gfx.flush();
	// }

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

	// 	roundBoundary.fullScreen().subBoundary(1, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	roundBoundary.subBoundaryRadial(1, 2, 0);
	// 	grafici.plot(axisPlot, dataSpline, roundBoundary);
	// 	grafici.plot(barPlot, dataSpline, roundBoundary);

	// 	roundBoundary.fullScreen().subBoundary(1, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
	// 	roundBoundary.addBorderRadial(0.5, 0.1, 0.25, 0);
	// 	grafici.plot(axisPlot, dataSpline, roundBoundary);
	// 	grafici.plot(barPlot, dataSpline, roundBoundary);

	// 	roundBoundary.fullScreen().subBoundary(1, 2, 1);
	// 	roundBoundary.addBorderRadial(0, 0.6, 0.25, 0);
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
	// 		roundBoundary.fullScreen().subBoundary(2, 4, i).addBorder(0.02, 0.02, 0.02, 0.02);
	// 		roundBoundary.addBorderRadial(0, 0.25, 0, 0);
	// 		grafici.plot(barPlot, dataLinearInterpolator, roundBoundary);
	// 	}

	// 	gfx.flush();
	// }

	// {
	// 	DataSource::Float dataset;
	// 	DataSource::LinearInterpolator dataLinearInterpolator;
	// 	DataSource::Spline dataSpline;
	// 	DataSource::Histogram dataHist;
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
	// 	grafici.boundary.addBorder(0.04, 0.04, 0.04, 0.02);
	// 	grafici.plot(axisPlot, dataset);
	// 	grafici.plot(line, dataset);
	// 	grafici.plot(barPlot, dataset);

	// 	grafici.boundary.fullScreen();
	// 	grafici.boundary.subBoundary(1, 3, 1);
	// 	grafici.boundary.addBorder(0.04, 0.04, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataLinearInterpolator);
	// 	grafici.plot(line, dataLinearInterpolator);
	// 	grafici.plot(barPlot, dataLinearInterpolator);

	// 	grafici.boundary.fullScreen();
	// 	grafici.boundary.subBoundary(1, 3, 2);
	// 	grafici.boundary.addBorder(0.04, 0.04, 0.02, 0.04);
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
	// 	DataSource::Histogram dataHist;
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

	// 		boundary.addBorder(0.02, 0.02, 0.02, 0.02);
	// 		grafici.plot(barPlot, dataSpline, boundary);
	// 	}

	// 	//flush to file
	// 	((File_GFX *)gfx)->flush();
	// }

	// {
	// 	DataSource::Float dataset;
	// 	DataSource::LinearInterpolator dataLinearInterpolator;
	// 	DataSource::Spline dataSpline;
	// 	DataSource::Histogram dataHist;
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
	// 		boundary.addBorder(0.02, 0.02, 0.02, 0.02);

	// 		grafici.plot(*plots[i], dataSpline, boundary);
	// 	}

	// 	//flush to file
	// 	((File_GFX *)gfx)->flush();
	// }

	return 0;
}