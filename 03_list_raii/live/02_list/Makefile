PROGRAM = list_testing
CXX = g++
CXXFLAGS = -Wall -Wextra
LDFLAGS = -lm

$(PROGRAM): main.o list.o
	$(CXX) $(LDFLAGS) -o $@ $^

main.o: main.cpp list.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

list.o: list.cpp list.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(PROGRAM)
