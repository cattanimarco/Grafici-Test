#include "File_GFX.h"
#include "Grafici-GFX/src/Grafici.h"

int main()
{

	/* taxonomy from https://vcg.seas.harvard.edu/files/pfister/files/viztaxonomy2013.pdf */

	{
		/* simple plot */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 480, "imgs/simple_plot.bmp");
		grafici.begin(gfx, Colors::blackAndWhite);

		ArrayFloat y(array, num_elem);

		grafici.clear();
		grafici.plot(line, Linear(num_elem), y, Constant(num_elem, 1));
		gfx.flush();
	}

	{
		/* linear interpolation */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 480, "imgs/linear_interpolation.bmp");
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

		File_GFX gfx(640, 480, "imgs/spline_interpolation.bmp");
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

		File_GFX gfx(640, 480, "imgs/multiplot.bmp");
		grafici.begin(gfx, Colors::temperature);
		grafici.clear();

		/* Load raw data */
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		SplineInterpolator dataSpline{ x, y, y, y, spline_size };
		Histogram dataHistogram{ dataSpline.y(), histogram_size };

		Boundary barBoundary;
		Boundary lineBoundary;
		barBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 }).boundaryRotation() = BoundaryRotation::clockWise90;
		lineBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 });
		grafici.plot(bar, BarIndex(histogram_size), dataHistogram, BarIndex(histogram_size), Constant(histogram_size, 0.0), barBoundary);
		grafici.plot(line, dataSpline, lineBoundary);
		gfx.flush();
	}

	{
		/* Subplot */
		constexpr size_t source_data_size = 6;
		constexpr size_t spline_size = 100;
		constexpr size_t histogram_size = 10;
		float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };

		File_GFX gfx(640, 480, "imgs/subplot.bmp");
		grafici.begin(gfx, Colors::parula);
		grafici.clear();

		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		SplineInterpolator dataSpline{ x, y, y, y, spline_size };
		Histogram dataHistogram{ dataSpline.y(), histogram_size };

		/* Data plot */
		Boundary leftBoundary;
		leftBoundary.cropGridCartesian(1, 2, 0, 0).cropAbsoluteCartesian({ 0.04, 0.02 }, { 0.04, 0.04 });
		grafici.plot(line, dataSpline, leftBoundary);

		/* Traditional histogram */
		Boundary rightTopBoundary;
		rightTopBoundary.cropGridCartesian(2, 2, 0, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.04, 0.02 });
		grafici.plot(bar, BarIndex(histogram_size), dataHistogram, BarIndex(histogram_size), Constant(histogram_size, 0.5), rightTopBoundary);

		/* Stripe graph */
		Boundary rightBottomBoundary;
		rightBottomBoundary.cropGridCartesian(2, 2, 1, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.02, 0.04 });
		grafici.plot(bar, dataSpline.y(), Constant(spline_size, 1.0), dataSpline.y(), Constant(spline_size, 0.0), rightBottomBoundary);

		gfx.flush();
	}

	{
		/* styles plot */
		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 480, "imgs/styles.bmp");
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
		/* boundary_projections */

		constexpr size_t source_data_size = 9;
		constexpr size_t spline_size = 33;
		float array[source_data_size] = { 0, 2, 0, 1.5, 0, 0.5, 0, 1, 0 };

		File_GFX gfx(640, 480, "imgs/boundary_projections.bmp");
		grafici.begin(gfx, Colors::heat);
		grafici.clear();

		/* Load raw data */
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		Constant opt(source_data_size, 0.5);
		SplineInterpolator dataSpline{ x, y, y, opt, spline_size };

		Boundary leftBoundary;
		leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		leftBoundary.cropGridCartesian(1, 2, 0, 0);
		grafici.plot(axis, Linear(25), Linear(10), Constant(25, 0.1), leftBoundary);
		grafici.plot(bar, dataSpline, leftBoundary);

		PolarBoundary rightBoundary;
		rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightBoundary.cropGridCartesian(1, 2, 0, 1);
		grafici.plot(axis, Linear(25), Linear(10), Constant(25, 0.1), rightBoundary);
		grafici.plot(bar, dataSpline, rightBoundary);

		gfx.flush();
	}

	{
		/* Polar Boundary */

		constexpr size_t source_data_size = 9;
		constexpr size_t spline_size = 49;
		float array[source_data_size] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };

		File_GFX gfx(640, 480, "imgs/polar_boundary.bmp");
		grafici.begin(gfx, Colors::parula);
		grafici.clear();

		/* Load raw data */
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		Constant opt(source_data_size, 0.0);
		SplineInterpolator dataSpline{ x, y, y, opt, spline_size };

		PolarBoundary leftBoundary;
		leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		leftBoundary.cropGridCartesian(1, 2, 0, 0);
		leftBoundary.cropGridPolar(1, 2, 0, 0);
		grafici.plot(bar, dataSpline, leftBoundary);

		PolarBoundary rightBoundary;
		Linear xAxe(27);
		Linear yAxe(5);
		Constant cAxe(10, 0);
		rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightBoundary.cropGridCartesian(1, 2, 0, 1);
		rightBoundary.cropRelativePolar({ 0, 0.25 }, { 0, 0.0 });
		grafici.plot(axis, xAxe, yAxe, cAxe, rightBoundary);

		PolarBoundary rightBottomBoundary;
		rightBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightBottomBoundary.cropGridCartesian(1, 2, 0, 1);
		rightBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0, 0.5 });
		grafici.plot(bar, dataSpline, rightBottomBoundary);

		PolarBoundary middleBottomBoundary;
		middleBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		middleBottomBoundary.cropGridCartesian(1, 2, 0, 1);
		middleBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0.35, 0.35 });
		grafici.plot(scatter, dataSpline.x(), dataSpline.y(), dataSpline.c(), Constant(spline_size, 0.01), middleBottomBoundary);

		PolarBoundary rightTopBoundary;
		rightTopBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightTopBoundary.cropGridCartesian(1, 2, 0, 1);
		rightTopBoundary.cropRelativePolar({ 0, 0.25 }, { 0.5, 0.0 });
		grafici.plot(line, dataSpline, rightTopBoundary);

		gfx.flush();
	}

	{
		/* Colors */
		constexpr size_t data_size = 240;

		File_GFX gfx(640, 480, "imgs/colors.bmp");
		grafici.begin(gfx, Colors::parula);
		grafici.clear();

		Linear x(data_size);
		Constant y(data_size, 1.0);
		Constant opt(data_size, 1.0);

		const ColorMap *colorPlots[] = { &Colors::rainbow,
			                             &Colors::temperature,
			                             &Colors::blackAndWhite,
			                             &Colors::cmy,
			                             &Colors::heat,
			                             &Colors::bright,
			                             &Colors::semaphore,
			                             &Colors::parula };

		for (size_t idx = 0; idx < sizeof(colorPlots) / sizeof(ColorMap*); idx++)
		{			
			Boundary boundary;
			*(grafici.colorMap()) = colorPlots[idx];
			boundary.cropGridCartesian(8, 1, idx).cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
			grafici.plot(bar, x, y, x, opt, boundary);
		}
		gfx.flush();
	}
	// {
	// 	/* Colors */
	// 	DataSource::Float dataset;
	// 	DataSource::LinearInterpolator dataLinearInterpolator;
	// 	RoundBoundary roundBoundary;

	// 	float dataArray[2] = { 2, 2 };

	// 	File_GFX gfx(640, 480, "imgs/colors.bmp");

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
	// 		                      heat,
	// 		                      semaphore,
	// 		                      parula,
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

	return 0;
}
