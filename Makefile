CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wpedantic -Wunused -Wextra
INCLUDES = -I.

# Source directories
SRC_DIRS = . \
           Grafici-GFX/src \
           Grafici-GFX/src/colors \
           Grafici-GFX/src/plotter \
           Grafici-GFX/src/data \
           Grafici-GFX/src/display

# Find all cpp files in source directories
CCSRC = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJ = $(CCSRC:%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJ:.o=.d)

# Output directories
BUILD_DIR = build
IMG_DIRS = imgs/unit imgs/examples

# Main targets
.PHONY: all clean run docs doxygen help

all: directories unit

help:
	@echo "Available targets:"
	@echo "  all        - Build everything (default)"
	@echo "  unit       - Build unit tests"
	@echo "  run        - Build and run unit tests"
	@echo "  docs       - Generate documentation"
	@echo "  clean      - Remove build artifacts"
	@echo "  help       - Show this help message"

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(foreach dir,$(SRC_DIRS),$(BUILD_DIR)/$(dir))
	@mkdir -p $(IMG_DIRS)

unit: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	@./unit

# Documentation targets
docs: doxygen
	moxygen -H --language cpp-light --classes --output Grafici-Wiki/Api-%s.md ./xml
	rm -rf xml

doxygen:
	doxygen doxyfile

# Build rules with dependency tracking
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f unit
	rm -f imgs/unit/*.bmp imgs/unit/*.jpg imgs/unit/*.jpeg
	rm -f imgs/examples/*.bmp imgs/examples/*.jpg imgs/examples/*.jpeg

# Include dependency files
-include $(DEPS)