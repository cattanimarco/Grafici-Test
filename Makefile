CCSRC = $(wildcard *.cpp)                     \
	# $(wildcard Grafici-GFX/src/*.cpp)         \
	# $(wildcard Grafici-GFX/src/colors/*.cpp)  \
	# $(wildcard Grafici-GFX/src/plotter/*.cpp) \
	# $(wildcard Grafici-GFX/src/data/*.cpp)    \
	# $(wildcard Grafici-GFX/src/display/*.cpp) \

OBJ = $(CCSRC:.cpp=.o)

CXXFLAGS=-g -std=c++11 -Wall -Wpedantic -Wunused -Wextra -I.

lib:
	gcc -O -c ezdib.c

unit: $(OBJ) ezdib.o
	$(CXX) -o $@ $^ 
	
run: all
	@./unit

all: clean lib unit

doxygen:
	doxygen doxyfile

docs: doxygen
	moxygen -H --groups --output Grafici-Wiki/Api-%s.md ./xml
	rm -rf xml

.PHONY: clean

clean:
	rm -f $(OBJ) ezdib.o unit
	rm -f imgs/unit/*.bmp 
	rm -f imgs/examples/*.bmp 