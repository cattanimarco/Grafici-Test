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
#include "Grafici-GFX/colorSchemes/rainbow.h"

int main()
{

	{
		/* usage */
		DataSetFloat dataset;
		float dataArray[5] = { 1, 0, 2, 1, 2 };

		Adafruit_GFX *gfx = new File_GFX(640, 240, "imgs/usage.bmp");

		grafici.begin(*gfx);
		dataset.begin(dataArray, 1, 5);

		grafici.clear();
		grafici.plot(linePlot, dataset);

		((File_GFX *)gfx)->flush();
	}

	{
		/* data interpolation */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		Adafruit_GFX *gfx = new File_GFX(640, 240, "imgs/interpolation.bmp");

		grafici.begin(*gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(&dataset, 100);

		grafici.clear();
		grafici.plot(linePlot, dataSpline);

		((File_GFX *)gfx)->flush();
	}

	{
		/* data analysis */
		DataSetFloat dataset;
		DataSetSpline dataSpline;
		DataSetHistogram dataHist;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		Adafruit_GFX *gfx = new File_GFX(640, 240, "imgs/histogram.bmp");

		grafici.begin(*gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(&dataset, 100); // interpolate 5 point to 100 points
		dataHist.begin(&dataSpline, 15); // histogram of interpolation

		grafici.clear();
		grafici.plot(barPlot, dataHist);

		((File_GFX *)gfx)->flush();
	}

	{
		/* Subplot */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		Adafruit_GFX *gfx = new File_GFX(640, 240, "imgs/subplot.bmp");

		grafici.begin(*gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(&dataset, 100);

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

		((File_GFX *)gfx)->flush();
	}

	{
		/* Multiplot */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		Adafruit_GFX *gfx = new File_GFX(640, 240, "imgs/multiplot.bmp");

		grafici.begin(*gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(&dataset, 100);

		grafici.clear();
		grafici.boundaries.reset().addBorder(0.04, 0.04, 0.04, 0.04); // add empty border
		grafici.plot(linePlot, dataSpline);                           // keep the same boundaries and plot multiple times
		grafici.plot(scatterPlot, dataSpline);

		((File_GFX *)gfx)->flush();
	}

	{
		/* Subplot */
		DataSetFloat dataset;
		DataSetSpline dataSpline;

		float dataArray[5] = { 1, 0, 2, 1, 2 };

		Adafruit_GFX *gfx = new File_GFX(640, 240, "imgs/transformations.bmp");

		grafici.begin(*gfx);
		dataset.begin(dataArray, 1, 5);
		dataSpline.begin(&dataset, 100);

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

		((File_GFX *)gfx)->flush();
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
		dataInterpolator.begin(&dataset, 100);
		dataSpline.begin(&dataset, 100);

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
		dataSpline.begin(&dataset, 20);

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
		dataSpline.begin(&dataset, 20);

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