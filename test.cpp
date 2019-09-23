#include "File_GFX.h"

#include "Grafici-GFX/Grafici.h"

#include "Grafici-GFX/plotObjects/barPlot.h"
#include "Grafici-GFX/plotObjects/linePlot.h"
#include "Grafici-GFX/plotObjects/axisPlot.h"
#include "Grafici-GFX/plotObjects/scatterPlot.h"

#include "Grafici-GFX/datasets/DataSetFloat.h"
#include "Grafici-GFX/decorators/DataSetInterpolator.h"
#include "Grafici-GFX/decorators/DataSetSpline.h"
#include "Grafici-GFX/decorators/DataSetHistogram.h"

#include "Grafici-GFX/colorSchemes/bw.h"
#include "Grafici-GFX/colorSchemes/rainbow.h"
#include "Grafici-GFX/colorSchemes/heat.h"
#include "Grafici-GFX/colorSchemes/neon.h"
#include "Grafici-GFX/colorSchemes/france.h"
#include "Grafici-GFX/colorSchemes/cmyk.h"
#include "Grafici-GFX/colorSchemes/bright.h"

//todo make an h file to include all basic essentials
//#include <iostream>

int main()
{
	DataSetFloat dataset;
	DataSetInterpolator dataInterpolator;
	DataSetSpline dataSpline;
	DataSetHistogram dataHist;

	{
		/* == INTERPOLATION == */
		//float dataArrayValue[11] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2};
		float dataArrayY[13] = {0, 5, 10, 10, 0, 0, -10, -10, 0, 0, 10, 0, 0};

		Adafruit_GFX *gfx = new File_GFX(1024, 768, "interpolation.bmp");

		grafici.begin(*gfx);

		grafici.setColorPalette(csBright);
		grafici.setColorSource(ColorSource::computeFromX);

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

		barPlot.thickness = 0.0;
		grafici.plot(barPlot, dataset, left);
		grafici.plot(barPlot, dataInterpolator, mid);
		grafici.plot(barPlot, dataSpline, right);
		//flush to file
		((File_GFX *)gfx)->flush();
	}

	{
		/* == COLOR SCHEMES == */
		float dataArrayY[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		Adafruit_GFX *gfx = new File_GFX(1024, 768, "color_schemes.bmp");

		grafici.begin(*gfx);
		grafici.setColorSource(ColorSource::computeFromX);

		// dataset - we provide the same array for Y and values so that the color encodes the bar height
		dataset.begin(dataArrayY, dataArrayY, 11);
		dataSpline.begin(&dataset, 20);

		ColorPalette colorPalettes[6] = {csRainbow, csBright, csFrance, csCmyk, csHeat, csBw};

		barPlot.thickness = 0.9;

		for (int i = 0; i < 6; i++)
		{
			DisplayBoundaries boundaries;
			grafici.setColorPalette(colorPalettes[i]);
			
			boundaries.subBoundaries(2, 3, i);
			grafici.clear(boundaries);
			
			boundaries.applyBorder(0.02, 0.02, 0.02, 0.02);
			grafici.plot(barPlot, dataSpline, boundaries);
		}

		//flush to file
		((File_GFX *)gfx)->flush();
	}

	return 0;
}