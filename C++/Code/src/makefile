src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

all: $(obj)
	g++ -o main $(obj)

%.o: %.cpp
	g++ -c -o $@ $< -Wall -g -std=c++17

.PHONY: clean
clean:
	rm -f $(obj) main