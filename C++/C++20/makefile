src=main.cpp
obj=$(src:.cpp=.o)

all: $(obj)
	g++ -o main $(obj) 

%.o: %.cpp
	g++ -c $< -std=c++20

.PHONY: clean
clean:
	rm $(obj) main