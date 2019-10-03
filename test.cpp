#include "File_GFX.h"

#include "Grafici-GFX/Grafici.h"

#include "Grafici-GFX/plotObjects/axisPlot.h"
#include "Grafici-GFX/plotObjects/barPlot.h"
#include "Grafici-GFX/plotObjects/barcodePlot.h"
#include "Grafici-GFX/plotObjects/linePlot.h"
#include "Grafici-GFX/plotObjects/scatterPlot.h"

#include "Grafici-GFX/datasets/DataSetFloat.h"
#include "Grafici-GFX/decorators/DataSetHistogram.h"
#include "Grafici-GFX/decorators/DataSetInterpolator.h"
#include "Grafici-GFX/decorators/DataSetSpline.h"

#include "Grafici-GFX/colorSchemes/bright.h"
#include "Grafici-GFX/colorSchemes/bw.h"
#include "Grafici-GFX/colorSchemes/cmyk.h"
#include "Grafici-GFX/colorSchemes/france.h"
#include "Grafici-GFX/colorSchemes/heat.h"
#include "Grafici-GFX/colorSchemes/neon.h"
#include "Grafici-GFX/colorSchemes/parula.h"
#include "Grafici-GFX/colorSchemes/rainbow.h"

int main()
{

	{
		/* usage */
		DataSetFloat dataset;
		float dataArray[5] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/usage.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 5);

		grafici.clear();
		grafici.plot(linePlot, dataset);

		gfx.flush();
	}

	{
		/* data interpolation */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/interpolation.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(dataset, 100);

		grafici.clear();
		grafici.plot(linePlot, dataSpline);

		gfx.flush();
	}

	{
		/* data analysis */
		DataSetFloat dataset;
		DataSetSpline dataSpline;
		DataSetHistogram dataHist;

		float dataArray[5] = { 1, 0, 2, 2, 1 };

		File_GFX gfx(640, 320, "imgs/histogram.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(dataset, 100); // interpolate 5 point to 100 points
		dataHist.begin(dataSpline, 30); // histogram of interpolation

		grafici.clear();
		grafici.plot(barPlot, dataHist);

		gfx.flush();
	}

	{
		/* Subplot */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/subplot.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(dataset, 100);

		grafici.clear();

		// set boundaries to full screen
		// divide screen in 2 colum and select first one
		// add empty border
		grafici.boundaries.reset().crop(1, 2, 0).addBorder(0.04, 0.04, 0.04, 0.02);
		grafici.plot(linePlot, dataSpline);

		// set boundaries to full screen
		// divide screen in 2 colum and select first one
		// add empty border
		grafici.boundaries.reset().crop(1, 2, 1).addBorder(0.04, 0.04, 0.02, 0.04);
		grafici.plot(barPlot, dataSpline);

		gfx.flush();
	}

	{
		/* Multiplot */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/multiplot.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(dataset, 100);
		scatterPlot.markerSize = 0.0002; // this is defined a proportion of the area of the plot

		grafici.clear();
		grafici.boundaries.reset().addBorder(0.04, 0.04, 0.04, 0.04); // add empty border
		grafici.plot(linePlot, dataSpline);                           // keep the same boundaries and plot multiple times
		grafici.plot(scatterPlot, dataSpline);

		gfx.flush();
	}

	{
		/* Transformations */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/transformations.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(dataset, 100);

		grafici.clear();

		grafici.boundaries.reset().crop(2, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.plot(barPlot, dataSpline);

		grafici.boundaries.reset().crop(2, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.boundaries.horizzontalFlip();
		grafici.plot(barPlot, dataSpline);

		grafici.boundaries.reset().crop(2, 2, 2).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.boundaries.verticalFlip();
		grafici.plot(barPlot, dataSpline);

		grafici.boundaries.reset().crop(2, 2, 3).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.boundaries.horizzontalFlip().verticalFlip();
		grafici.plot(barPlot, dataSpline);

		gfx.flush();
	}

	{
		/* Styles */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		File_GFX gfx(640, 320, "imgs/styles.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(dataset, 30);

		grafici.clear();
		axisPlot.numAxisX = 9;
		axisPlot.numAxisY = 3;
		scatterPlot.markerSize = 0.0001;

		grafici.boundaries.reset().crop(1, 3, 0).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.plot(axisPlot, dataSpline);
		grafici.plot(linePlot, dataSpline);

		grafici.boundaries.reset().crop(1, 3, 1).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.plot(axisPlot, dataSpline);
		grafici.plot(barPlot, dataSpline);

		grafici.boundaries.reset().crop(1, 3, 2).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.plot(axisPlot, dataSpline);
		grafici.plot(scatterPlot, dataSpline);

		gfx.flush();
	}

	{
		/* Round 1 */
		DataSetFloat dataset;
		DataSetSpline dataSpline;
		RoundDisplayBoundaries roundBoundaries;

		float dataArray[9] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };

		File_GFX gfx(640, 320, "imgs/round_1.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 9);
		dataSpline.begin(dataset, 100);
		axisPlot.numAxisX = 10;
		axisPlot.numAxisY = 4;

		grafici.clear();

		grafici.boundaries.reset().crop(1, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.plot(axisPlot, dataSpline);
		grafici.plot(barPlot, dataSpline);

		roundBoundaries.reset().crop(1, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
		grafici.plot(axisPlot, dataSpline, roundBoundaries);
		grafici.plot(barPlot, dataSpline, roundBoundaries);

		gfx.flush();
	}

	{
		/* Round 2 */
		DataSetFloat dataset;
		DataSetSpline dataSpline;
		RoundDisplayBoundaries roundBoundaries;

		float dataArray[9] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };

		File_GFX gfx(640, 320, "imgs/round_2.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 9);
		dataSpline.begin(dataset, 100);
		axisPlot.numAxisX = 10;
		axisPlot.numAxisY = 4;

		grafici.clear();

		roundBoundaries.reset().crop(1, 2, 0).addBorder(0.02, 0.02, 0.02, 0.02);
		roundBoundaries.cropRadial(1, 2, 0);
		grafici.plot(axisPlot, dataSpline, roundBoundaries);
		grafici.plot(barPlot, dataSpline, roundBoundaries);

		roundBoundaries.reset().crop(1, 2, 1).addBorder(0.02, 0.02, 0.02, 0.02);
		roundBoundaries.addBorderRadial(0.5, 0.1, 0.25, 0);
		grafici.plot(axisPlot, dataSpline, roundBoundaries);
		grafici.plot(barPlot, dataSpline, roundBoundaries);

		roundBoundaries.reset().crop(1, 2, 1);
		roundBoundaries.addBorderRadial(0, 0.6, 0.25, 0);
		grafici.plot(axisPlot, dataSpline, roundBoundaries);
		grafici.plot(linePlot, dataSpline, roundBoundaries);

		gfx.flush();
	}

	{
		/* Colors */
		DataSetFloat dataset;
		DataSetInterpolator dataInterpolator;
		RoundDisplayBoundaries roundBoundaries;

		float dataArray[2] = { 2, 2 };

		File_GFX gfx(640, 320, "imgs/colors.bmp");

		grafici.begin(gfx);
		dataset.begin(dataArray, 1, 2);
		dataset.yMin = 0; /* ovverride min value */
		dataInterpolator.begin(dataset, 100);
		grafici.style.colorSource = ColorSource::computeFromX;

		grafici.clear();

		ColorPalette colorPlots[] = { csBright,
			                           csBw,
			                           csCmyk,
			                           csFrance,
			                           csHeat,
			                           csNeon,
			                           csParula,
			                           csRainbow };

		for (int i = 0; i < sizeof(colorPlots)/sizeof(ColorPalette); i++)
		{
			grafici.style.setPalette(colorPlots[i]);
			roundBoundaries.reset().crop(2, 4, i).addBorder(0.02, 0.02, 0.02, 0.02);
			roundBoundaries.addBorderRadial(0, 0.25, 0, 0);
			grafici.plot(barPlot, dataInterpolator, roundBoundaries);
		}

		gfx.flush();
	}

	{
		DataSetFloat dataset;
		DataSetInterpolator dataInterpolator;
		DataSetSpline dataSpline;
		DataSetHistogram dataHist;
		/* == INTERPOLATION == */
		//float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
		float dataArrayY[13] = { 0, 5, 10, 10, 0, 0, -10, -10, 0, 0, 10, 0, 0 };

		Adafruit_GFX *gfx = new File_GFX(1024, 768, "interpolation.bmp");

		grafici.begin(*gfx);

		grafici.style.colorPalette = &csBright;
		grafici.style.colorSource = ColorSource::computeFromX;

		dataset.begin(dataArrayY, dataArrayY, 13);
		dataInterpolator.begin(dataset, 100);
		dataSpline.begin(dataset, 100);

		grafici.clear();
		barPlot.thickness = 0.0;

		grafici.boundaries.crop(1, 3, 0);
		grafici.boundaries.addBorder(0.04, 0.04, 0.04, 0.02);
		grafici.plot(axisPlot, dataset);
		grafici.plot(linePlot, dataset);
		grafici.plot(barPlot, dataset);

		grafici.boundaries.reset();
		grafici.boundaries.crop(1, 3, 1);
		grafici.boundaries.addBorder(0.04, 0.04, 0.02, 0.02);
		grafici.plot(axisPlot, dataInterpolator);
		grafici.plot(linePlot, dataInterpolator);
		grafici.plot(barPlot, dataInterpolator);

		grafici.boundaries.reset();
		grafici.boundaries.crop(1, 3, 2);
		grafici.boundaries.addBorder(0.04, 0.04, 0.02, 0.04);
		grafici.plot(axisPlot, dataSpline);
		grafici.plot(linePlot, dataSpline);
		grafici.plot(barPlot, dataSpline);

		//flush to file
		((File_GFX *)gfx)->flush();
	}

	{
		DataSetFloat dataset;
		DataSetInterpolator dataInterpolator;
		DataSetSpline dataSpline;
		DataSetHistogram dataHist;
		/* == COLOR SCHEMES == */
		float dataArrayY[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		Adafruit_GFX *gfx = new File_GFX(1024, 768, "color_schemes.bmp");

		grafici.begin(*gfx);
		grafici.style.colorSource = ColorSource::computeFromX;

		// dataset - we provide the same array for Y and values so that the color encodes the bar height
		dataset.begin(dataArrayY, dataArrayY, 11);
		dataSpline.begin(dataset, 20);

		ColorPalette colorPalettes[6] = { csRainbow, csBright, csFrance, csCmyk, csHeat, csBw };

		barPlot.thickness = 0.9;

		for (int i = 0; i < 6; i++)
		{
			DisplayBoundaries boundaries;
			grafici.style.colorPalette = &(colorPalettes[i]);

			boundaries.crop(2, 3, i);
			grafici.clear(boundaries);

			boundaries.addBorder(0.02, 0.02, 0.02, 0.02);
			grafici.plot(barPlot, dataSpline, boundaries);
		}

		//flush to file
		((File_GFX *)gfx)->flush();
	}

	{
		DataSetFloat dataset;
		DataSetInterpolator dataInterpolator;
		DataSetSpline dataSpline;
		DataSetHistogram dataHist;
		/* == PLOT STYLES == */
		float dataArrayY[11] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };

		Adafruit_GFX *gfx = new File_GFX(1024, 768, "plot_types.bmp");

		grafici.begin(*gfx);
		grafici.style.colorSource = ColorSource::computeFromY;
		grafici.style.colorPalette = &csCmyk;
		grafici.clear();

		// dataset - we provide the same array for Y and values so that the color encodes the bar height
		dataset.begin(dataArrayY, 1.0, 11);
		dataSpline.begin(dataset, 20);

		PlotObj *plots[6] = { &barcodePlot, &barPlot, &linePlot, &scatterPlot, &linePlot, &linePlot };

		barPlot.thickness = 0.9;

		for (int i = 0; i < 6; i++)
		{
			DisplayBoundaries boundaries;
			boundaries.crop(2, 3, i);
			boundaries.addBorder(0.02, 0.02, 0.02, 0.02);

			grafici.plot(*plots[i], dataSpline, boundaries);
		}

		//flush to file
		((File_GFX *)gfx)->flush();
	}

	return 0;
}