src=main.cpp
obj=$(src:.cpp=.o)

all: $(obj)
	g++ -o main $(obj) -lfmt -lspdlog -lpthread

%.o: %.cpp
	g++ -c $< -std=c++20 

.PHONY: clean
clean:
	rm $(obj) main
