CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Werror -Weffc++
INC = -I/opt/curl/include
LDFLAGS = -L/opt/curl/lib -lcurl
OPT = -O3
OBJS = curl.o csv_writer.o
EXEC = main

.PHONY: all
all: compile clean

compile: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INC) $(OPT) $^ $@.cpp -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

.PHONY: run
run:
	./main help

.PHONY: clean
clean:
	rm -f $(OBJS)