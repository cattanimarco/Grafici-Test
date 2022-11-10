#ifndef GRAFICI_GFX_DRIVER_FILE_H
#define GRAFICI_GFX_DRIVER_FILE_H

#include "Adafruit_GFX.h"
#include "ezdib.h"
#include <iostream>

class File_GFX : public Adafruit_GFX
{
  public:
  
	File_GFX(int width, int height, const char *filename)
	    : Adafruit_GFX(width, height)
	    , filename(filename)
	{
		hDib = ezd_create(width, height, 24, 0);
	}

	~File_GFX()
	{
		flush();
	}

	void drawPixel(int16_t x, int16_t y, uint16_t color)
	{
		int r = (((color >> 11) & 31) / 31.0) * 255;
		int g = (((color >> 5) & 63) / 63.0) * 255;
		int b = ((color & 31) / 31.0) * 255;
		int c = (r << 16) | (g << 8) | (b);

		ezd_set_pixel(hDib, x, _height - y, c);
	}

	void flush(void)
	{
		ezd_save(hDib, filename);
	}

  private:
	HEZDIMAGE hDib;
	const char *filename;
};

#endif //GRAFICI_GFX_DRIVER_FILE_H
