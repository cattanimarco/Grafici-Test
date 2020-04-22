#include "File_GFX.h"

#include "Grafici-GFX/src/Grafici.h"
#include "Grafici-GFX/src/data/DataSourceArray.h"

//#include "Grafici-GFX/src/plots/linePlot.h"

// #include "Grafici-GFX/src/data/DataSourceArray.h"
// #include "Grafici-GFX/src/data/DataSourceHistogram.h"
// #include "Grafici-GFX/src/data/DataSourceInterpolator.h"
// #include "Grafici-GFX/src/data/DataSourceSpline.h"
// #include "Grafici-GFX/src/plots/axisPlot.h"
// #include "Grafici-GFX/src/plots/barPlot.h"
// #include "Grafici-GFX/src/plots/barcodePlot.h"
// #include "Grafici-GFX/src/plots/linePlot.h"
// #include "Grafici-GFX/src/plots/scatterPlot.h"

int main()
{

	{
		// 	/* simple_plot */
				std::cout << "ciao" ;

		float x[5] = { 1, 2, 3, 4, 5 };
		float y[5] = { 1, 3, 2, 1, 2 };
		std::cout << "ciao" ;

		DataSourceArray<float> dataSourceX;
		DataSourceArray<float> dataSourceY;
		File_GFX gfx(640, 320, "imgs/1.bmp");
		std::cout << "ciao" ;

		grafici.begin(gfx,grafici_colors::rainbow);
		dataSourceX.begin(x, 5);
		dataSourceY.begin(y, 5);
		std::cout << "ciao" ;

		grafici.clear();

		std::cout << "ciao" ;
		grafici.plot(linePlot, dataSourceX, dataSourceY, dataSourceY);

		gfx.flush();
	}

	// {
	// 	/* data interpolation */
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;

	// 	float dataArray[5] = { 1, 0, 2, 1, 2 };

	// 	File_GFX gfx(640, 320, "imgs/interpolation.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 5);
	// 	dataSpline.begin(dataset, 100);

	// 	grafici.clear();
	// 	grafici.plot(linePlot, dataSpline);

	// 	gfx.flush();
	// }

	// {
	// 	/* data analysis */
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;
	// 	DataSourceHistogram dataHist;

	// 	float dataArray[5] = { 1, 0, 2, 2, 1 };

	// 	File_GFX gfx(640, 320, "imgs/histogram.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 5);
	// 	dataSpline.begin(dataset, 100); // interpolate 5 point to 100 points
	// 	dataHist.begin(dataSpline, 30); // histogram of interpolation

	// 	grafici.clear();
	// 	grafici.plot(barPlot, dataHist);

	// 	gfx.flush();
	// }

	// {
	// 	/* Subplot */
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;
	// 	DataSourceHistogram dataHist;

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
	// 	grafici.plot(linePlot, dataSpline);

	// 	// set boundary to full screen
	// 	// divide screen in 2 colum and select first one
	// 	// add empty border
	// 	grafici.boundary.fullScreen().subBoundary(1, 2, 1).addBorder(0.04, 0.04, 0.02, 0.04);
	// 	grafici.plot(barPlot, dataHist);

	// 	gfx.flush();
	// }

	// {
	// 	/* Multiplot */
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;

	// 	float dataArray[5] = { 1, 0, 2, 1, 2 };

	// 	File_GFX gfx(640, 320, "imgs/multiplot.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 5);
	// 	dataSpline.begin(dataset, 100);
	// 	scatterPlot.markerSize = 0.0002; // this is defined a proportion of the area of the plot

	// 	grafici.clear();
	// 	grafici.boundary.fullScreen().addBorder(0.04, 0.04, 0.04, 0.04); // add empty border
	// 	grafici.plot(linePlot, dataSpline);                                // keep the same boundary and plot multiple times
	// 	grafici.plot(scatterPlot, dataSpline);

	// 	gfx.flush();
	// }

	// {
	// 	/* Transformations */
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;

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
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;

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
	// 	grafici.plot(linePlot, dataSpline);

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
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;
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
	// 	DataSourceFloat dataset;
	// 	DataSourceSpline dataSpline;
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
	// 	grafici.plot(linePlot, dataSpline, roundBoundary);

	// 	gfx.flush();
	// }

	// {
	// 	/* Colors */
	// 	DataSourceFloat dataset;
	// 	DataSourceInterpolator dataInterpolator;
	// 	RoundBoundary roundBoundary;

	// 	float dataArray[2] = { 2, 2 };

	// 	File_GFX gfx(640, 320, "imgs/colors.bmp");

	// 	grafici.begin(gfx);
	// 	dataset.begin(dataArray, 1, 2);
	// 	dataset.yMin = 0; /* ovverride min value */
	// 	dataInterpolator.begin(dataset, 100);
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
	// 		grafici.plot(barPlot, dataInterpolator, roundBoundary);
	// 	}

	// 	gfx.flush();
	// }

	// {
	// 	DataSourceFloat dataset;
	// 	DataSourceInterpolator dataInterpolator;
	// 	DataSourceSpline dataSpline;
	// 	DataSourceHistogram dataHist;
	// 	/* == INTERPOLATION == */
	// 	//float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
	// 	float dataArrayY[13] = { 0, 5, 10, 10, 0, 0, -10, -10, 0, 0, 10, 0, 0 };

	// 	Adafruit_GFX *gfx = new File_GFX(1024, 768, "interpolation.bmp");

	// 	grafici.begin(*gfx);

	// 	grafici.style.colorPalette = &csBright;
	// 	grafici.style.colorSource = ColorSource::computeFromX;

	// 	dataset.begin(dataArrayY, dataArrayY, 13);
	// 	dataInterpolator.begin(dataset, 100);
	// 	dataSpline.begin(dataset, 100);

	// 	grafici.clear();
	// 	barPlot.thickness = 0.0;

	// 	grafici.boundary.subBoundary(1, 3, 0);
	// 	grafici.boundary.addBorder(0.04, 0.04, 0.04, 0.02);
	// 	grafici.plot(axisPlot, dataset);
	// 	grafici.plot(linePlot, dataset);
	// 	grafici.plot(barPlot, dataset);

	// 	grafici.boundary.fullScreen();
	// 	grafici.boundary.subBoundary(1, 3, 1);
	// 	grafici.boundary.addBorder(0.04, 0.04, 0.02, 0.02);
	// 	grafici.plot(axisPlot, dataInterpolator);
	// 	grafici.plot(linePlot, dataInterpolator);
	// 	grafici.plot(barPlot, dataInterpolator);

	// 	grafici.boundary.fullScreen();
	// 	grafici.boundary.subBoundary(1, 3, 2);
	// 	grafici.boundary.addBorder(0.04, 0.04, 0.02, 0.04);
	// 	grafici.plot(axisPlot, dataSpline);
	// 	grafici.plot(linePlot, dataSpline);
	// 	grafici.plot(barPlot, dataSpline);

	// 	//flush to file
	// 	((File_GFX *)gfx)->flush();
	// }

	// {
	// 	DataSourceFloat dataset;
	// 	DataSourceInterpolator dataInterpolator;
	// 	DataSourceSpline dataSpline;
	// 	DataSourceHistogram dataHist;
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
	// 	DataSourceFloat dataset;
	// 	DataSourceInterpolator dataInterpolator;
	// 	DataSourceSpline dataSpline;
	// 	DataSourceHistogram dataHist;
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

	// 	Plotter *plots[6] = { &barcodePlot, &barPlot, &linePlot, &scatterPlot, &linePlot, &linePlot };

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