#ifndef GRAFICI_GFX_DRIVER_FILE_H
#define GRAFICI_GFX_DRIVER_FILE_H

#include "Adafruit_GFX.h"
#include <vector>
#include <string>
#include <cstring>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

class File_GFX : public Adafruit_GFX
{
public:
    File_GFX(int width, int height, const char* filename)
        : Adafruit_GFX(width, height)
        , filename(filename)
        , buffer(width * height * 3, 0)  // RGB format, 3 bytes per pixel
    {
    }

    ~File_GFX()
    {
        flush();
    }

    void drawPixel(int16_t x, int16_t y, uint16_t color)
    {
        if (x < 0 || x >= _width || y < 0 || y >= _height) return;
        
        // Convert RGB565 to RGB888
        uint8_t r = ((color >> 11) & 0x1F) * 255 / 31;
        uint8_t g = ((color >> 5) & 0x3F) * 255 / 63;
        uint8_t b = (color & 0x1F) * 255 / 31;

        // Calculate position in buffer (y is flipped to match standard image coordinates)
        size_t pos = ((_height - 1 - y) * _width + x) * 3;
        buffer[pos] = r;
        buffer[pos + 1] = g;
        buffer[pos + 2] = b;
    }

    void flush(void)
    {
        if (std::string(filename).find(".jpg") != std::string::npos ||
            std::string(filename).find(".jpeg") != std::string::npos) {
            stbi_write_jpg(filename, _width, _height, 3, buffer.data(), 95);  // Quality 95
        } else {
            // Default to PNG if not JPEG
            stbi_write_png(filename, _width, _height, 3, buffer.data(), _width * 3);
        }
    }

private:
    const char* filename;
    std::vector<uint8_t> buffer;
};

#endif //GRAFICI_GFX_DRIVER_FILE_H
