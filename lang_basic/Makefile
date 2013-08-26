
CXX := clang++
CXX_FLAGS := -g -std=c++11

sources := main.cpp
objects := $(subst %.cpp,%.o,$(sources))

all: main

main: main.cpp

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $<

%: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

clean:
	rm -rf *.o main *.dSYM 
.PHONY:
	clean all
