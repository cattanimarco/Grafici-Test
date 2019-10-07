CCSRC = $(wildcard *.cpp) \
	$(wildcard Grafici-GFX/src/*.cpp) \
	$(wildcard Grafici-GFX/src/modules/*.cpp) \

OBJ = $(CCSRC:.cpp=.o)

CXXFLAGS=-g -std=c++11 -Wall -Wpedantic -Wunused -I.

lib:
	gcc -O -c ezdib.c

test: $(OBJ) ezdib.o
	$(CXX) -o $@ $^ 
	
run: lib test
	@./test

.PHONY: clean

clean:
	rm -f $(OBJ) ezdib.o test 

