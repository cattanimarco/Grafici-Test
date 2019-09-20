#include "File_GFX.h"

#include "arduinoLibrary/Grafici.h"

#include "arduinoLibrary/plotters/spaghettiPlot.h"
#include "arduinoLibrary/plotters/barPlot.h"
#include "arduinoLibrary/plotters/linePlot.h"
#include "arduinoLibrary/plotters/axisPlot.h"
#include "arduinoLibrary/plotters/scatterPlot.h"

#include "arduinoLibrary/datasets/DataSetFloat.h"
#include "arduinoLibrary/decorators/DataSetInterpolator.h"
#include "arduinoLibrary/decorators/DataSetSpline.h"
#include "arduinoLibrary/decorators/DataSetHistogram.h"

#include "arduinoLibrary/colorSchemes/rainbow.h"
#include "arduinoLibrary/colorSchemes/heat.h"
#include "arduinoLibrary/colorSchemes/neon.h"
#include "arduinoLibrary/colorSchemes/france.h"
#include "arduinoLibrary/colorSchemes/cmyk.h"
#include "arduinoLibrary/colorSchemes/bright.h"
#include "arduinoLibrary/colorSchemes/bw.h"

//todo make an h file to include all basic essentials
//#include <iostream>

int main()
{
	Grafici grafici;

	DataSetFloat dataset;
	DataSetInterpolator dataInterpolator;
	DataSetSpline dataSpline;
	DataSetHistogram dataHist;

	ColorTheme myTheme(csBright, ColorSource::computeFromX);

	{
		/* == INTERPOLATION == */
		//float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
		float dataArrayY[13] = {0, 5, 10, 10, 0, 0, -10, -10, 0, 0, 10, 0, 0};

		Adafruit_GFX *gfx = new File_GFX(1024, 768, "interpolation.bmp");

		grafici.begin(*gfx, myTheme);

		DisplayBoundaries left;
		DisplayBoundaries mid;
		DisplayBoundaries right;

		dataset.begin(dataArrayY, dataArrayY, 13);
		dataInterpolator.begin(&dataset, 40);
		dataSpline.begin(&dataset, 40);

		//left.begin();
		left.subBoundaries(1, 3, 0);
		left.applyBorder(0.04, 0.04, 0.04, 0.02);

		//mid.begin();
		mid.subBoundaries(1, 3, 1);
		mid.applyBorder(0.04, 0.04, 0.02, 0.02);

		//right.begin();
		right.subBoundaries(1, 3, 2);
		right.applyBorder(0.04, 0.04, 0.02, 0.04);

		//grafici.clear();
		grafici.plot(linePlot, dataset, left);
		grafici.plot(linePlot, dataInterpolator, mid);
		grafici.plot(linePlot, dataSpline, right);

		grafici.plot(scatterPlot, dataset, left);
		grafici.plot(scatterPlot, dataInterpolator, mid);
		grafici.plot(scatterPlot, dataSpline, right);

		grafici.plot(spaghettiPlot, dataset, left);
		grafici.plot(spaghettiPlot, dataInterpolator, mid);
		grafici.plot(spaghettiPlot, dataSpline, right);
		//flush to file
		((File_GFX *)gfx)->flush();
	}

	{
		/* == COLOR SCHEMES == */
		float dataArrayY[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		Adafruit_GFX *gfx = new File_GFX(1024, 768, "color_schemes.bmp");

		grafici.begin(*gfx, myTheme);

		// dataset - we provide the same array for Y and values so that the color encodes the bar height
		dataset.begin(dataArrayY, dataArrayY, 11);
		dataSpline.begin(&dataset, 20);

		ColorPalette colorPalettes[6] = {csRainbow, csBright, csFrance, csCmyk, csHeat, csBw};

		for (int i = 0; i < 6; i++)
		{
			DisplayBoundaries boundaries;
			ColorTheme theme(colorPalettes[i], ColorSource::computeFromX);
			//boundaries.begin();
			boundaries.subBoundaries(2, 3, i);
			grafici.clear(boundaries, theme);
			boundaries.applyBorder(0.02, 0.02, 0.02, 0.02);
			grafici.plot(barPlot, dataSpline, boundaries, theme);
		}

		//flush to file
		((File_GFX *)gfx)->flush();
	}

	return 0;
}