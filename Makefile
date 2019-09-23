CCSRC = $(wildcard *.cpp) \
	$(wildcard Grafici-GFX/*.cpp) \

OBJ = $(CCSRC:.cpp=.o)

CFLAGS=-I.
CXXFLAGS=-g -std=c++11 -Wall -Wpedantic -Wunused -I.

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
	$(RM) $(FixPath) $(exec) *.bmp
