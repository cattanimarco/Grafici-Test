# Grafici-Test

Unit test suite for the [Grafici-GFX](https://github.com/cattanimarco/Grafici-GFX) Arduino library. This project provides a testing environment that emulates display libraries by using a file-based graphics driver.

## Overview

Grafici-Test serves as a testing and development platform for the Grafici-GFX library, allowing developers to:
- Test graphics rendering without physical hardware
- Generate example outputs as JPEG images
- Verify the functionality of plotting functions and display drivers
- Document library features with visual examples

## Project Structure

- `File_GFX.h`: File-based graphics driver that implements the Adafruit GFX interface
- `unit.cpp`: Comprehensive test suite covering all Grafici-GFX features
- `Grafici-GFX/`: Arduino library (included as a git submodule)
- `imgs/`: Generated test outputs
  - `unit/`: Unit test output images
  - `examples/`: Example visualizations
  - `wiki/`: Images for the Grafici-Wiki documentation

## Dependencies

- C++11 compiler
- Make build system
- stb_image_write.h (included) for JPEG/PNG image generation

## Building and Running Tests

1. Clone the repository with submodules:
   ```bash
   git clone --recursive https://github.com/cattanimarco/Grafici-Test.git
   cd Grafici-Test
   ```

2. Build and run tests:
   ```bash
   make clean && make
   ./unit
   ```

The test suite will generate various JPEG images in the `imgs/` directory, demonstrating different plotting capabilities:
- Basic shapes (rectangles, triangles, polygons)
- Line plots
- Scatter plots
- Histograms
- Polar plots
- Heat maps

## File-Based Graphics Driver

The `File_GFX` class implements the Adafruit GFX interface but writes output to image files instead of a physical display. Features include:
- JPEG output (95% quality) with PNG fallback
- RGB565 to RGB888 color conversion
- Bounds checking for pixel drawing
- Efficient memory management using std::vector

## Documentation

The generated images are used to maintain the [Grafici-Wiki](https://github.com/cattanimarco/Grafici-Wiki), providing visual documentation of the library's capabilities and usage examples. Each test run produces a set of images that demonstrate various plotting features and capabilities of the Grafici-GFX library.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Run the test suite to ensure all tests pass
5. Submit a pull request

## License

Copyright 2025 Marco Cattani

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
