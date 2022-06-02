CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Werror -Weffc++ -I/opt/curl/include
LDFLAGS = -L/opt/curl/lib -lcurl
OPT = -O3

.PHONY: compile
compile: main

main: curl.cpp csv_writer.cpp
	@$(CXX) $(CXXFLAGS) $(OPT) $^ $@.cpp -o $@ $(LDFLAGS)

.PHONY: run
run:
	@./main

.PHONY: clean
clean:
	@rm -f main