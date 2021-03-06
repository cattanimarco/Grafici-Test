#include "File_GFX.h"
#include "Grafici-GFX/src/Grafici.h"

int main()
{

	/* taxonomy from https://vcg.seas.harvard.edu/files/pfister/files/viztaxonomy2013.pdf */

	{
		/* simple plot */
		File_GFX gfx(640, 480, "imgs/simple_plot.bmp");

		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };
		ArrayFloat y(array, num_elem);

		grafici.begin(gfx, Colors::blackAndWhite);
		grafici.clear();

		grafici.plot(line, Linear(num_elem), y, Constant(num_elem, 1));

		gfx.flush();
	}

	{
		/* linear interpolation */
		File_GFX gfx(640, 480, "imgs/linear_interpolation.bmp");

		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };
		Linear x(num_elem);
		ArrayFloat y(array, num_elem);
		// Chose a big enough number for the samples. Too small and you risk sub-sampling issues
		// Even better chose samples = n + (n-1) * x
		LinearInterpolator dataLinear{ x, y, y, y, 85 };

		grafici.begin(gfx, Colors::rainbow);
		grafici.clear();

		grafici.plot(line, dataLinear);

		gfx.flush();
	}

	{
		/* spline interpolation */
		File_GFX gfx(640, 480, "imgs/spline_interpolation.bmp");

		constexpr size_t num_elem = 5;
		float array[num_elem] = { 1, 0, 2, 1, 2 };
		Linear x(num_elem);
		ArrayFloat y(array, num_elem);
		SplineInterpolator dataSpline{ x, y, y, y, 85 };

		grafici.begin(gfx, Colors::rainbow);
		grafici.clear();

		grafici.plot(line, dataSpline);

		gfx.flush();
	}

	{
		/* Multiplot */
		File_GFX gfx(640, 480, "imgs/multiplot.bmp");

		constexpr size_t source_data_size = 6;
		constexpr size_t spline_size = 86;
		constexpr size_t histogram_size = 20;
		float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		SplineInterpolator dataSpline{ x, y, y, y, spline_size };
		Histogram dataHistogram{ dataSpline.y(), histogram_size };
		Boundary barBoundary;
		Boundary lineBoundary;

		grafici.begin(gfx, Colors::temperature);
		grafici.clear();

		barBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 }).boundaryRotation() = BoundaryRotation::clockWise90;
		lineBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 });
		grafici.plot(bar, BarIndex(histogram_size), dataHistogram, BarIndex(histogram_size), Constant(histogram_size, 0.0), barBoundary);
		grafici.plot(line, dataSpline, lineBoundary);
		grafici.plot(scatter, dataSpline.x(), dataSpline.y(), dataSpline.y(), Constant(spline_size, 0.015), lineBoundary);

		gfx.flush();
	}

	{
		/* Subplot */
		File_GFX gfx(640, 480, "imgs/subplot.bmp");

		constexpr size_t source_data_size = 6;
		constexpr size_t spline_size = 86;
		constexpr size_t histogram_size = 10;
		float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		SplineInterpolator dataSpline{ x, y, y, y, spline_size };
		Histogram dataHistogram{ dataSpline.y(), histogram_size };
		Boundary leftBoundary;
		Boundary rightTopBoundary;
		Boundary rightBottomBoundary;

		grafici.begin(gfx, Colors::parula);
		grafici.clear();

		/* Traditional plot (interpolated via spline) */
		leftBoundary.cropGridCartesian(1, 2, 0, 0).cropAbsoluteCartesian({ 0.04, 0.02 }, { 0.04, 0.04 });
		grafici.colorMap(Colors::blackAndWhite);
		grafici.plot(axis, Linear(6), Linear(11), Constant(12, 0.1), leftBoundary);
		grafici.colorMap(Colors::parula);
		grafici.plot(line, dataSpline, leftBoundary);

		/* Traditional histogram */
		rightTopBoundary.cropGridCartesian(2, 2, 0, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.04, 0.02 });
		grafici.colorMap(Colors::blackAndWhite);
		grafici.plot(axis, Linear(11), Linear(6), Constant(11, 0.1), rightTopBoundary);
		grafici.colorMap(Colors::parula);
		grafici.plot(bar, BarIndex(histogram_size), dataHistogram, BarIndex(histogram_size), Constant(histogram_size, 0.5), rightTopBoundary);

		/* Stripe graph */
		rightBottomBoundary.cropGridCartesian(2, 2, 1, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.02, 0.04 });
		grafici.plot(bar, dataSpline.y(), Constant(spline_size, 1.0), dataSpline.y(), Constant(spline_size, 0.0), rightBottomBoundary);

		gfx.flush();
	}

	{
		/* heatmap plot */
		File_GFX gfx(640, 480, "imgs/heatmaps.bmp");

		constexpr size_t num_elem = 6;
		float arrayX[num_elem] = { 0, 1, 2, 2, 3, 4 };
		float arrayY[num_elem] = { 1, 0, 2, 1, 1, 2 };
		ArrayFloat x(arrayX, num_elem);
		ArrayFloat y(arrayY, num_elem);
		Constant opt(num_elem, 0.02);
		Constant c(num_elem, 0);
		Boundary bl;
		Boundary br;
		Boundary tl;
		Boundary tr;

		grafici.begin(gfx, Colors::parula);
		grafici.clear();

		bl.cropGridCartesian(2, 2, 0, 0);
		bl.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
		grafici.plot(heatmap, x, y, c, opt, bl);
		grafici.plot(scatter, x, y, c, opt, bl);

		br.cropGridCartesian(2, 2, 0, 1);
		br.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
		grafici.plot(bubblemap, x, y, c, opt, br);
		grafici.plot(scatter, x, y, c, opt, br);

		tl.cropGridCartesian(2, 2, 1, 0);
		tl.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
		grafici.plot(cellmap, x, y, x, opt, tl);
		grafici.plot(scatter, x, y, c, opt, tl);

		tr.cropGridCartesian(2, 2, 1, 1);
		tr.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
		grafici.plot(cliquegraph, x, y, x, opt, tr);
		grafici.plot(scatter, x, y, c, opt, tr);

		gfx.flush();
	}

	{
		/* boundary_projections */
		File_GFX gfx(640, 480, "imgs/boundary_projections.bmp");

		constexpr size_t source_data_size = 9;
		constexpr size_t spline_size = 33;
		float array[source_data_size] = { 0, 2, 0, 1.5, 0, 0.5, 0, 1, 0 };
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		Constant opt(source_data_size, 0.5);
		SplineInterpolator dataSpline{ x, y, y, opt, spline_size };
		Boundary leftBoundary;
		PolarBoundary rightBoundary;

		grafici.begin(gfx);
		grafici.clear();

		leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		leftBoundary.cropGridCartesian(1, 2, 0, 0);
		grafici.colorMap(Colors::blackAndWhite);
		grafici.plot(axis, Linear(25), Linear(10), Constant(25, 0.1), leftBoundary);
		grafici.colorMap(Colors::heat);
		grafici.plot(bar, dataSpline, leftBoundary);

		rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightBoundary.cropGridCartesian(1, 2, 0, 1);
		grafici.colorMap(Colors::blackAndWhite);
		grafici.plot(axis, Linear(25), Linear(10), Constant(25, 0.1), rightBoundary);
		grafici.colorMap(Colors::heat);
		grafici.plot(bar, dataSpline, rightBoundary);

		gfx.flush();
	}

	{
		/* Polar Boundary */
		File_GFX gfx(640, 480, "imgs/polar_boundary.bmp");

		constexpr size_t source_data_size = 9;
		constexpr size_t spline_size = 49;
		float array[source_data_size] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };
		Linear x(source_data_size);
		ArrayFloat y(array, source_data_size);
		Constant opt(source_data_size, 0.0);
		SplineInterpolator dataSpline{ x, y, y, opt, spline_size };
		PolarBoundary leftBoundary;
		PolarBoundary rightBoundary;
		PolarBoundary rightBottomBoundary;
		PolarBoundary middleBottomBoundary;
		PolarBoundary rightTopBoundary;

		grafici.begin(gfx, Colors::parula);
		grafici.clear();

		leftBoundary.cropGridCartesian(1, 2, 0, 0);
		leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		leftBoundary.cropGridPolar(1, 2, 0, 0);
		grafici.colorMap(Colors::blackAndWhite);
		grafici.plot(axis, Linear(19), Linear(5), Constant(10, 0), leftBoundary);
		grafici.colorMap(Colors::parula);
		grafici.plot(bar, dataSpline, leftBoundary);

		rightBoundary.cropGridCartesian(1, 2, 0, 1);
		rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightBoundary.cropRelativePolar({ 0, 0.25 }, { 0, 0.0 });
		grafici.colorMap(Colors::blackAndWhite);
		grafici.plot(axis, Linear(28), Linear(5), Constant(10, 0), rightBoundary);
		grafici.colorMap(Colors::parula);

		rightBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightBottomBoundary.cropGridCartesian(1, 2, 0, 1);
		rightBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0, 0.5 });
		grafici.plot(bar, dataSpline, rightBottomBoundary);

		middleBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		middleBottomBoundary.cropGridCartesian(1, 2, 0, 1);
		middleBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0.35, 0.35 });
		grafici.plot(scatter, dataSpline.x(), dataSpline.y(), dataSpline.c(), Constant(spline_size, 0.01), middleBottomBoundary);

		rightTopBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
		rightTopBoundary.cropGridCartesian(1, 2, 0, 1);
		rightTopBoundary.cropRelativePolar({ 0, 0.25 }, { 0.5, 0.0 });
		grafici.plot(line, dataSpline, rightTopBoundary);

		gfx.flush();
	}

	{
		/* Colors */
		File_GFX gfx(640, 480, "imgs/colors.bmp");

		constexpr size_t data_size = 240;
		const ColorMap *colorPlots[] = { &Colors::rainbow,
			                             &Colors::temperature,
			                             &Colors::blackAndWhite,
			                             &Colors::cmy,
			                             &Colors::heat,
			                             &Colors::bright,
			                             &Colors::semaphore,
			                             &Colors::parula };
		Linear x(data_size);
		Constant y(data_size, 1.0);
		Constant opt(data_size, 1.0);

		grafici.begin(gfx, Colors::parula);
		grafici.clear();

		for (size_t idx = 0; idx < sizeof(colorPlots) / sizeof(ColorMap *); idx++)
		{
			Boundary boundary;
			grafici.colorMap(*colorPlots[idx]);
			boundary.cropGridCartesian(8, 1, idx).cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
			grafici.plot(bar, x, y, x, opt, boundary);
		}

		gfx.flush();
	}

	{
		/* shared axis */
		File_GFX gfx(640, 480, "imgs/shared_axis.bmp");

		constexpr size_t num_elem = 5;
		float array_y1[num_elem] = { 1, 2, 3, 4, 5 };
		float array_y2[num_elem] = { 2, 3, 4, 5, 6 };
		float array_x1[num_elem] = { 2, 3, 4, 5, 6 };
		float array_x2[num_elem] = { 0, 1, 2, 3, 4 };
		Linear xAxis(7);
		Linear yAxis(6, -1, 1);
		ArrayFloat y1(array_y1, num_elem);
		ArrayFloat y2(array_y2, num_elem);
		ArrayFloat x1(array_x1, num_elem);
		ArrayFloat x2(array_x2, num_elem);

		grafici.begin(gfx);
		grafici.clear();

		/* set each limit as the union (using + sign) of all the limits*/
		x1.limits() = x2.limits() = xAxis.limits() = (x1.limits() + x2.limits() + xAxis.limits());
		y1.limits() = y2.limits() = yAxis.limits() = (y1.limits() + y2.limits() + yAxis.limits());

		grafici.colorMap(Colors::blackAndWhite);
		grafici.plot(axis, xAxis, yAxis, Constant(8, 0.1));
		grafici.colorMap(Colors::semaphore);
		grafici.plot(line, x1, y1, y1);
		grafici.plot(line, x2, y2, y2);

		gfx.flush();
	}

	return 0;
}
