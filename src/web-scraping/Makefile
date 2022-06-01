CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Werror -Weffc++ -I/opt/curl/include
LDFLAGS = -L/opt/curl/lib -lcurl
OPT = -O3

.PHONY: all, compile, run, clean

all: compile run clean

compile: curl.cpp
	$(CXX) $(CXXFLAGS) $(OPT) $^ main.cpp -o main $(LDFLAGS)

run:
	./main

clean:
	rm -f main curl.o