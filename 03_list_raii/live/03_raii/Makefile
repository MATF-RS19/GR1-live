PROGRAM = raii_example
CXX = g++
CXXFLAGS = -Wall -Wextra

$(PROGRAM): main.o
	$(CXX) $(CXXFLAGS) -o $@ $<

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o $(PROGRAM)
