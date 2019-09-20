ARDUINO_DIR = ~/Documents/Arduino/libraries/Grafici
CCSRC = $(wildcard *.cpp) \
	$(wildcard arduinoLibrary/*.cpp) \

OBJ = $(CCSRC:.cpp=.o)

CFLAGS=-I.
CXXFLAGS=-g -std=c++11 -Wall -I.#-pedantic

ifdef OS
	RM = del /Q
	FixPath = $(subst /,\,$(OBJ))
	exec = test.exe
else
	RM = rm -f
	FixPath = $(OBJ)
	exec = test
endif

lib:
	gcc -O -c ezdib.c

test: $(OBJ) ezdib.o
	$(CXX) -o $@ $^ $(CFLAGS)

run: lib test
	@./test

.PHONY: clean

clean:$
	$(RM) $(FixPath) $(exec) prova.bmp
