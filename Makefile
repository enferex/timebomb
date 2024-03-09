CXXFLAGS=--std=c++20

all: test

test: test.o
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	$(RM) test test.o
