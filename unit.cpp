#include <cmath>
#include <iostream>
#include <string>

#define String std::string
#define randomSeed(i) srand(i)
#define random(i) (rand() % i)

#include "File_GFX.h"

#include "Grafici-GFX/src/Grafici.h"

/* check https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/ */
#define assert_float(a, b)                                    \
	do                                                        \
	{                                                         \
		if (fabs(float(b) - float(a)) > 0.02)                            \
		{                                                     \
			std::cout << std::endl                            \
			          << "Error on line " << __LINE__ << ": " \
			          << float(a) << " != " << float(b)                     \
			          << "( " << #a << " , " << #b << " )"    \
			          << std::endl                            \
			          << std::endl;                           \
			return -1;                                        \
		}                                                     \
	} while (0)

void printData(const DataSource<DataNorm> &data)
{
	for (size_t idx = 0; idx < data.size(); ++idx)
	{
		std::cout << data[idx].norm() << " " << data[idx].raw() << std::endl;
	}
	std::cout << std::endl;
}

void printDataRaw(const DataSource<DataNorm> &data)
{
	for (size_t idx = 0; idx < data.size(); ++idx)
	{
		std::cout << data[idx].raw() << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	/* == Test Range == */
	Range<int> r{ 0, 10 };
	assert_float(r.low, 0);
	assert_float(r.high, 10);

	/* == Test DataNorm == */
	DataNorm nf0{ 0.0, { 0.0, 10.0 } };
	assert_float(nf0.raw(), 0.0);
	assert_float(nf0.norm(), 0.0);

	DataNorm nf5{ 5, { 0, 10 } };
	assert_float(nf5.raw(), 5);
	assert_float(nf5.norm(), 0.5);

	DataNorm nf10{ 10, { 0, 10 } };
	assert_float(nf10.raw(), 10);
	assert_float(nf10.norm(), 1);

	/* == Test DataArray == */
	int array_int[5] = { 0, -1, -2, -3, -4 };
	DataArray<int> data_array_int(array_int, 5);
	assert_float(data_array_int[0].raw(), 0);
	assert_float(data_array_int[0].norm(), 1);
	assert_float(data_array_int[2].raw(), -2);
	assert_float(data_array_int[2].norm(), 0.5);
	assert_float(data_array_int[4].raw(), -4);
	assert_float(data_array_int[4].norm(), 0);

	float array_float[5] = { 0, -1, -2, -3, -4 };
	DataArray<float> data_array_float(array_float, 5);
	assert_float(data_array_float[0].raw(), 0);
	assert_float(data_array_float[0].norm(), 1);
	assert_float(data_array_float[2].raw(), -2);
	assert_float(data_array_float[2].norm(), 0.5);
	assert_float(data_array_float[4].raw(), -4);
	assert_float(data_array_float[4].norm(), 0);

	/* == Test DataLinear == */
	DataLinear data_linear1{ 11 };
	for (size_t idx = 0; idx < data_linear1.size(); ++idx)
	{
		assert_float(data_linear1[idx].raw(), static_cast<float>(idx));
		assert_float(data_linear1[idx].norm(), idx * 0.1);
	}

	/* y = 3x+1 with x in [0,10] */
	DataLinear data_linear2{ 11, 1, 3 };
	for (size_t idx = 0; idx < data_linear2.size(); ++idx)
	{
		assert_float(data_linear2[idx].raw(), idx * 3.0 + 1);
		assert_float(data_linear2[idx].norm(), idx * 0.1);
	}

	/* == Test DataFunction == */
	DataFunction data_function_sin{ 11, [](size_t idx) -> float
		                            { return sin(M_PI * idx / 20.0); } };
	for (size_t idx = 0; idx < data_function_sin.size(); ++idx)
	{
		assert_float(data_function_sin[idx].raw(), sin(M_PI * idx / 20.0));
		/* the raw function goes from 0 to 1, hence raw() == norm() */
		assert_float(data_function_sin[idx].norm(), sin(M_PI * idx / 20.0));
	}

	/* == Test DataConstant == */
	DataConstant data_constant1{ 10, (float)0.7 };
	for (size_t idx = 0; idx < data_constant1.size(); ++idx)
	{
		assert_float(data_constant1[idx].raw(), 0.7);
		assert_float(data_constant1[idx].norm(), 0.7);
	}

	DataConstant data_constant2{ 10, { 7, { 0, 10 } } };
	for (size_t idx = 0; idx < data_constant2.size(); ++idx)
	{
		assert_float(data_constant2[idx].raw(), 7);
		assert_float(data_constant2[idx].norm(), 0.7);
	}

	/* == Test DataLinear == */
	DataLinear data_linear_x{ 11 };
	DataLinear data_linear_y{ 11, 0, 2 };
	DataInterpolatorL linear_interpolator{ data_linear_x, data_linear_y, 110 };
	for (size_t idx = 0; idx < linear_interpolator.size(); ++idx)
	{
		assert_float(linear_interpolator.x()[idx].raw(), idx * (1.0 / 11));
		assert_float(linear_interpolator.x()[idx].norm(), idx * (1.0 / 110));
		assert_float(linear_interpolator.y()[idx].raw(), idx * (2.0 / 11));
		assert_float(linear_interpolator.y()[idx].norm(), idx * (1.0 / 110));
	}

	/* == Test DataFunction == */

	/* clang-format off */
	DataFunction data_function_zig_zag{ 11, [](size_t idx) -> float { return acos(cos(idx)); } };
	/* clang-format on */

	DataSpline<110> spline_interpolator{ data_linear_x, data_function_zig_zag };
	for (size_t idx = 0; idx < spline_interpolator.size(); ++idx)
	{
		assert_float(spline_interpolator.x()[idx].raw(), idx * (1.0 / 11));
		assert_float(spline_interpolator.x()[idx].norm(), idx * (1.0 / 110));
		/* we cannot test y */
	}

	/* == Test DataHistogramXY == */

	/* Test histogram when values are spread one per bin */
	size_t class_id = 0;
	size_t class_num = 1;
	DataHistogramXY<11> histogram_1{ data_linear1 };
	for (size_t idx = 0; idx < histogram_1.size(); ++idx)
	{
		assert_float(histogram_1.x()[idx].raw(), idx * class_num + class_id + 0.5);
		assert_float(histogram_1.x()[idx].norm(), (idx * class_num + class_id + 0.5) / (histogram_1.size() * class_num));
		assert_float(histogram_1.y()[idx].raw(), 1);
		assert_float(histogram_1.y()[idx].norm(), 1);
	}

	/* Test histogram when values are spread one per bin, but with space for multiple classes on the x axis */
	class_id = 1;
	class_num = 3;
	DataHistogramXY<11> histogram_2{ data_linear1, false, class_id, class_num };
	for (size_t idx = 0; idx < histogram_1.size(); ++idx)
	{
		assert_float(histogram_2.x()[idx].raw(), idx * class_num + class_id + 0.5);
		assert_float(histogram_2.x()[idx].norm(), (idx * class_num + class_id + 0.5) / (histogram_1.size() * class_num));
		assert_float(histogram_2.y()[idx].raw(), 1);
		assert_float(histogram_2.y()[idx].norm(), 1);
	}

	/* Test histogram when all values are inside one bin */
	DataHistogramXY<10> histogram_3{ data_constant1 };
	for (size_t idx = 0; idx < histogram_3.size(); ++idx)
	{
		float acc = (idx == 7) ? histogram_3.size() : 0;
		assert_float(histogram_3.y()[idx].raw(), acc);
	}

	/* == Test Color == */

	Color color_1{ 0, 0, 255 };
	Color color_2{ 255, 0, 0 };
	Color color_3 = color_1 + color_2;
	assert_float(color_1.red, 0);
	assert_float(color_1.green, 0);
	assert_float(color_1.blue, 255);
	assert_float(color_3.red, 255);
	assert_float(color_3.green, 0);
	assert_float(color_3.blue, 255);
	color_2 = color_2 * 0.5;
	assert_float(color_2.red, 127);
	assert_float(color_2.green, 0);
	assert_float(color_2.blue, 0);
	assert(color_1.to_R5G6B5() == 31);

	/* == Test DisplayVector == */

	DisplayVector a{ 0, 1 };
	DisplayVector b{ 1, 1 };
	a = a + b;
	a.y = a.y - 0.1;
	assert_float(a.y, 1.9);
	assert_float(a.x, 1);
	assert_float(b.y, 1);
	assert_float(b.x, 1);
	b = a - b;
	assert_float(a.y, 1.9);
	assert_float(a.x, 1);
	assert_float(b.y, 0.9);
	assert_float(b.x, 0);
	b = b * 0.5;
	assert_float(b.y, 0.45);
	assert_float(b.x, 0);

	/* == Test Window == */

	Window win{ { 0.25, 1 }, { 0, 0.75 } };

	auto res = win.data_to_display_vector(0, 0);
	assert_float(res.x, 0.25);
	assert_float(res.y, 0.0);

	auto res2 = win.data_to_display_vector(1, 1);
	assert_float(res2.x, 1.0);
	assert_float(res2.y, 0.75);

	auto res3 = win.origin();
	assert_float(res3.x, 0.25);
	assert_float(res3.y, 0);

	auto res4 = win.sub_window(3, 3, 1, 2).origin();
	assert_float(res4.x, 0.5);
	assert_float(res4.y, 0.5);

	auto res5 = win.sub_window(3, 3, 1, 2).sub_window(5, 5, 4, 4).origin();
	assert_float(res5.x, 0.7);
	assert_float(res5.y, 0.7);

	{
		File_GFX gfx(640, 480, "imgs/unit/rectangles_window.bmp");
		DisplayDriver display_driver(gfx);

		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, black, full_screen);

		Window display_window{ { 0, .5 }, { 0, 1 } };
		display_driver.fill_rect({ .4, 0 }, { .6, 1 }, red, display_window);
		display_driver.fill_rect({ 0, .4 }, { 1, .6 }, yellow, display_window);
		display_driver.fill_rect({ .4, .4 }, { .6, .6 }, orange, display_window);
		display_driver.draw_rect({ .4, .4 }, { .6, .6 }, white, display_window);

		PolarWindow polar_window{ { 0, 1 }, { 0, 1 }, Window{ { .5, 1 }, { 0, 1 } } };
		display_driver.fill_rect({ .4, 0 }, { .6, 1 }, red, polar_window, 36);
		display_driver.fill_rect({ 0, .4 }, { 1, .6 }, yellow, polar_window, 36);
		display_driver.fill_rect({ .4, .4 }, { .6, .6 }, orange, polar_window, 36);
		display_driver.draw_rect({ .4, .4 }, { .6, .6 }, white, polar_window, 36);
	}

	{
		File_GFX gfx(640, 480, "imgs/unit/triangles_window.bmp");
		DisplayDriver display_driver(gfx);

		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, black, full_screen);

		Window display_window{ { 0, .5 }, { 0, 1 } };
		display_driver.fill_triangle({ 0, 0 }, { 0, 1 }, { .25, .5 }, cyan, display_window);
		display_driver.fill_triangle({ 1, 1 }, { 1, 0 }, { .75, .5 }, magenta, display_window);
		display_driver.fill_triangle({ 1, 1 }, { 0, 1 }, { .5, .75 }, yellow, display_window);
		display_driver.fill_triangle({ 0, 0 }, { 1, 0 }, { .5, .25 }, white, display_window);

		PolarWindow polar_window{ { 0, 1 }, { 0, 1 }, Window{ { .5, 1 }, { 0, 1 } } };
		display_driver.fill_triangle({ 0, 0 }, { 0, 1 }, { .25, .5 }, cyan, polar_window, 10);
		display_driver.fill_triangle({ 1, 1 }, { 1, 0 }, { .75, .5 }, magenta, polar_window, 10);
		display_driver.fill_triangle({ 1, 1 }, { 0, 1 }, { .5, .75 }, yellow, polar_window, 10);
		display_driver.fill_triangle({ 0, 0 }, { 1, 0 }, { .5, .25 }, white, polar_window, 10);
	}

	{
		File_GFX gfx(640, 480, "imgs/unit/poligons_full_screen.bmp");
		DisplayDriver display_driver(gfx);

		for (size_t idx = 8; idx > 2; --idx)
		{
			const float x_radius = 0.5 * (480.0 / 640.0) * (idx / 8.0);
			const float y_radius = 0.5 * (idx / 8.0);
			display_driver.fill_polygon({ .5, .5 }, { x_radius, y_radius }, idx, .25, parula.index_to_color(idx));
			display_driver.draw_polygon({ .5, .5 }, { x_radius, y_radius }, idx, .75, parula.index_to_color(idx + 3));
		}
	}

	{
		File_GFX gfx(640, 640, "imgs/unit/polar_window.bmp");
		DisplayDriver display_driver(gfx);
		PolarWindow polar_window{ { 0, 1 }, { 0, 1 }, full_screen };
		constexpr size_t num_rays = 36;
		Range<size_t> loop_range{ 0, num_rays - 1 };

		for (size_t idx = 0; idx < num_rays; ++idx)
		{
			float norm_idx = loop_range.value_to_norm(idx);
			display_driver.fill_rect({ 0.3, norm_idx }, { 0.7, 1 }, rainbow.norm_to_color({ norm_idx, { 0, 1 } }), polar_window.sub_polar_window({ 0, .5 }, { .3, 1 }).sub_polar_window(num_rays, 1, idx, 0));
			display_driver.draw_rect({ 0.3, 0 }, { 0.7, norm_idx }, rainbow.norm_to_color({ 1 - norm_idx, { 0, 1 } }), polar_window.sub_polar_window({ 0, .5 }, { .3, 1 }).sub_polar_window(num_rays, 1, idx, 0));
		}

		for (size_t idx = 0; idx < num_rays; ++idx)
		{
			float norm_idx = loop_range.value_to_norm(idx);
			display_driver.fill_rect({ 0.3, norm_idx }, { 0.7, 1 }, parula.norm_to_color({ norm_idx, { 0, 1 } }), polar_window.sub_polar_window({ .5, 1 }, { .3, 1 }).sub_polar_window(num_rays, 1, idx, 0));
			display_driver.draw_rect({ 0.3, 0 }, { 0.7, norm_idx }, parula.norm_to_color({ 1 - norm_idx, { 0, 1 } }), polar_window.sub_polar_window({ .5, 1 }, { .3, 1 }).sub_polar_window(num_rays, 1, idx, 0));
		}
	}

	{
		/* Define a set of nice to plot functions */
		DataFunction data_y_sin(360, [](size_t idx) -> float
		                        { return sin(idx / 30.0 * M_PI); });
		DataFunction data_y_zig_zag(360, [](size_t idx) -> float
		                            { return acos(cos(idx / 30.0 * M_PI)); });
		DataFunction data_y_square(360, [](size_t idx) -> float
		                           { return ((idx / 30) % 2 == 0) ? 0 : 1; });
		DataFunction data_y_pixel_sin(360, [](size_t idx) -> float
		                              { return round(2 * sin(idx / 30.0 * M_PI)); });
		DataFunction data_y_beat(360, [](size_t idx) -> float
		                         { return idx % 17 == 0 ? 0 : (idx % 23 == 0 ? 1 : .5); });

		/* resize data sources from 0,1 range to custom range */
		DataResize data_y_1(data_y_sin, { 0.01, 0.09 });
		DataResize data_y_2(data_y_zig_zag, { 0.11, 0.19 });
		DataResize data_y_3(data_y_square, { 0.21, 0.29 });
		DataResize data_y_4(data_y_pixel_sin, { 0.31, 0.39 });
		DataResize data_y_5(data_y_beat, { 0.41, 0.49 });

		DataLinear data_x{ 360 };

		{
			File_GFX gfx(640, 640, "imgs/unit/plot_line.bmp");
			DisplayDriver display_driver(gfx);

			PlotLineOpts options;
			options.draw_background = false;
			options.segments = 45;
			plot_axis(display_driver, full_screen, { 10, 10, v_lines | h_lines, white * 0.3 });
			plot_line(display_driver, full_screen, rainbow, data_x, data_y_1, data_y_1, options);
			plot_line(display_driver, full_screen, rainbow, data_x, data_y_2, data_y_2, options);
			plot_line(display_driver, full_screen, rainbow, data_x, data_y_3, data_y_3, options);
			plot_line(display_driver, full_screen, rainbow, data_x, data_y_4, data_y_4, options);
			plot_line(display_driver, full_screen, rainbow, data_x, data_y_5, data_y_5, options);
		}

		{
			File_GFX gfx(640, 640, "imgs/unit/plot_line_polar.bmp");
			DisplayDriver display_driver(gfx);

			PolarWindow polar_window{ { 0, 1 }, { 0, 1 }, full_screen };

			PlotLineOpts options;
			options.draw_background = false;
			options.segments = 45;
			plot_axis(display_driver, polar_window, { 10, 10, v_lines | h_lines, white * 0.3, 45 });
			plot_line(display_driver, polar_window, rainbow, data_x, data_y_1, data_y_1, options);
			plot_line(display_driver, polar_window, rainbow, data_x, data_y_2, data_y_2, options);
			plot_line(display_driver, polar_window, rainbow, data_x, data_y_3, data_y_3, options);
			plot_line(display_driver, polar_window, rainbow, data_x, data_y_4, data_y_4, options);
			plot_line(display_driver, polar_window, rainbow, data_x, data_y_5, data_y_5, options);
		}
	}

	{
		DataLinear data_x{ 10, { 0, 11 }, 1, 1 };
		DataConstant data_size{ 10, (float)0.04 };

		std::string markers = "eps>^*x+o.";
		Range<size_t> rows = { 0, markers.size() + 1 };

		{
			File_GFX gfx(640, 640, "imgs/unit/plot_scatter.bmp");

			Grafici plot{ gfx };
			plot.set_color_map(rainbow);

			for (size_t idx_marker = 0; idx_marker < markers.size(); ++idx_marker)
			{
				DataConstant data_y{ 10, rows.value_to_norm(idx_marker + 1) };
				plot.scatter(data_x, data_y, data_x, data_size, full_screen, std::string(1, markers[idx_marker]));
			}
		}

		{
			File_GFX gfx(640, 640, "imgs/unit/plot_scatter_polar.bmp");

			Grafici plot{ gfx };
			plot.set_color_map(rainbow);
			auto window = PolarWindow{ { 0, 1 }, { 0, 1 }, full_screen };

			for (size_t idx_marker = 0; idx_marker < markers.size(); ++idx_marker)
			{
				DataConstant data_y{ 10, rows.value_to_norm(idx_marker + 1) };
				plot.scatter(data_x, data_y, data_x, data_size, window, std::string(1, markers[idx_marker]));
			}
		}
	}

	{
		File_GFX gfx(640, 640, "imgs/unit/rotations.bmp");

		/* clang-format off */
		DataResize data_x(DataLinear(10), { 0.5 / 11, 10.5 / 11 });
		DataFunction data_y(10, [](size_t idx) -> float { return pow(idx, 2); });
		/* clang-format on */

		Grafici plot{ gfx };
		plot.set_color_map(parula);

		PlotBarOpts opts;
		opts.thickness = 0.5;

		auto window1 = full_screen.sub_window({ 0, .5 }, { 0, .5 }).transform(WindowTransform::none);
		plot.bar(data_x, data_y, data_y, window1, opts);

		auto window2 = full_screen.sub_window({ .5, 1 }, { 0, .5 }).transform(WindowTransform::ccw_90_rotation);
		plot.bar(data_x, data_y, data_y, window2, opts);

		auto window3 = full_screen.sub_window({ 0, .5 }, { .5, 1 }).transform(WindowTransform::cw_90_rotation);
		plot.bar(data_x, data_y, data_y, window3, opts);

		auto window4 = full_screen.sub_window({ .5, 1 }, { .5, 1 }).transform(WindowTransform::both_flip);
		plot.bar(data_x, data_y, data_y, window4, opts);
	}

	{
		File_GFX gfx(640, 640, "imgs/unit/transformations.bmp");

		/* clang-format off */
		DataResize data_x(DataLinear(10), { 0.5 / 11, 10.5 / 11 });
		DataFunction data_y(10, [](size_t idx) -> float{ return pow(idx, 2); });
		/* clang-format on */

		Grafici plot{ gfx };
		plot.set_color_map(parula);
		plot.set_axis({ 10, 10, h_lines | v_lines, white * 0.5 });

		PlotBarOpts opts;
		opts.thickness = 0.5;

		auto window1 = full_screen.sub_window({ 0, .5 }, { 0, .5 }).transform(WindowTransform::none);
		plot.bar(data_x, data_y, data_y, window1, opts);

		auto window2 = full_screen.sub_window({ .5, 1 }, { 0, .5 }).transform(WindowTransform::h_flip);
		plot.bar(data_x, data_y, data_y, window2, opts);

		auto window3 = full_screen.sub_window({ 0, .5 }, { .5, 1 }).transform(WindowTransform::v_flip);
		plot.bar(data_x, data_y, data_y, window3, opts);

		auto window4 = full_screen.sub_window({ .5, 1 }, { .5, 1 }).transform(WindowTransform::both_flip);
		plot.bar(data_x, data_y, data_y, window4, opts);
	}

	{
		File_GFX gfx(240, 320, "imgs/examples/line_from_array.bmp");
		Grafici plot{ gfx };

		constexpr size_t ARRAY_SIZE = 25;
		constexpr size_t MAX_VALUE = 255;

		unsigned int raw_data[ARRAY_SIZE];
		DataArrayXY<unsigned int> data{ raw_data, ARRAY_SIZE, { 0, MAX_VALUE } };

		randomSeed(66);
		for (size_t i = 0; i < ARRAY_SIZE; ++i)
		{
			raw_data[i] = random(MAX_VALUE + 1);
		}

		/* Set the color map */
		plot.set_color_map(parula);

		/* break plot lines in multiple segments to create a gradient of colors between two data points */
		PlotLineOpts opts;
		opts.segments = 10;

		/* Plot data as a line. Color line using `data_y` */
		plot.line(data.x(), data.y(), data.y(), full_screen, opts);
	}

	{
		File_GFX gfx(240, 320, "imgs/examples/line_from_function.bmp");
		Grafici plot{ gfx };

		DataLinear data_x{ 100 };
		DataFunction data_y{ 100, [](size_t idx) -> float
			                 { return sin(M_PI * idx * 0.05); } };

		plot.set_color_map(parula);

		plot.line(data_x, data_y, data_y);
	}

	{
		File_GFX gfx(240, 320, "imgs/examples/line_and_histogram.bmp");
		Grafici plot{ gfx };

		constexpr size_t ARRAY_SIZE = 60;
		constexpr size_t HISTOGRAM_BINS = 20;

		plot.set_color_map(cmy);

		auto left_window = full_screen.sub_window({ 0, .74 }, { 0, 1 });

		plot.set_axis({ HISTOGRAM_BINS, 1, h_lines, white * 0.5 });

		float raw_data[ARRAY_SIZE];

		randomSeed(66);
		for (size_t i = 0; i < ARRAY_SIZE; ++i)
		{
			raw_data[i] = sqrt(-2 * log(float((random(HISTOGRAM_BINS) + 1) / (float)HISTOGRAM_BINS))) * sin(M_PI * 2.0 * random(HISTOGRAM_BINS) / (float)HISTOGRAM_BINS);
		}

		DataArrayXY<float> data{ raw_data, ARRAY_SIZE };

		PlotLineOpts left_opts;
		left_opts.segments = 10;

		plot.line(data.x(), data.y(), data.y(), left_window, left_opts);

		auto right_window = full_screen.sub_window({ .76, 1 }, { 0, 1 }).transform(WindowTransform::ccw_90_rotation);

		plot.set_axis({ 5, HISTOGRAM_BINS, h_lines | v_lines, white * 0.5 });

		DataHistogramXY<HISTOGRAM_BINS> data_hist{ data.y() };

		PlotBarOpts right_opts;
		right_opts.fill_bars = true;
		right_opts.thickness = 0.5;

		plot.bar(data_hist.x(), data_hist.y(), data_hist.x(), right_window, right_opts);
	}

	{
		// File_GFX gfx(240, 320, "imgs/examples/pie.bmp");
	}

	{
		// File_GFX gfx(240, 320, "imgs/examples/multi_bar.bmp");
	}

	{
		File_GFX gfx(240, 320, "imgs/examples/spline_from_array.bmp");
		Grafici plot{ gfx };

		constexpr size_t ARRAY_SIZE = 10;
		constexpr size_t SPLINE_SIZE = 50;
		constexpr size_t MAX_VALUE = 255;

		unsigned int raw_data[ARRAY_SIZE];
		DataArrayXY<unsigned int> data{ raw_data, ARRAY_SIZE, { 0, MAX_VALUE } };

		randomSeed(66);
		for (size_t i = 0; i < ARRAY_SIZE; ++i)
		{
			raw_data[i] = random(MAX_VALUE + 1);
		}

		/* Set the color map */
		plot.set_color_map(parula);

		DataSpline<SPLINE_SIZE> data_interpolated{data.x(),data.y()};

		/* Plot data as a line. Color line using `data_y` */
		plot.line(data_interpolated.x(), data_interpolated.y(), data_interpolated.y(), full_screen);
	}

	{
		File_GFX gfx(240, 240, "imgs/wiki/window.bmp");
	
		DisplayDriver display_driver(gfx);

		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, black, full_screen);

		Window display_window{ { .5, 1 }, {0, .5 } };
		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, red, display_window);
	}

	{
		File_GFX gfx(240, 240, "imgs/wiki/window2.bmp");
	
		DisplayDriver display_driver(gfx);

		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, black, full_screen);

		Window display_window{ { .5, 1 }, {0, .5 } };
		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, red, display_window);
		display_driver.fill_rect({ .25, .25 }, { .75, .75 }, blue, display_window);
	}

	{
		File_GFX gfx(240, 240, "imgs/wiki/window3.bmp");
	
		DisplayDriver display_driver(gfx);

		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, black, full_screen);

		Window display_window{ { .5, 1 }, {0, .5 } };
		display_driver.fill_rect({ 0, 0 }, { 1, 1 }, red, display_window);
		display_driver.fill_rect({ .25, .25 }, { .75, .75 }, blue, full_screen);
	}

	{
		File_GFX gfx(240, 320, "imgs/wiki/gartner_hype_cycle.bmp");
		Grafici plot{ gfx };

		int hype_raw[] = {0, 100, 20, 50,  60, 60 , 60 };

		DataArrayXY<int> hype{ hype_raw, 7 };
		DataSpline<30> interpolated_hype_cycle{hype.x(),hype.y()};

		/* Plot data as a line. Color line using `data_y` */
		plot.line(interpolated_hype_cycle.x(), interpolated_hype_cycle.y(), interpolated_hype_cycle.y());
	}

}
