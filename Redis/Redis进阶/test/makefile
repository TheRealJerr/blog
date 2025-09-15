# makefile文件
CC=g++
CFLAGS=-Wall -g
SRCS=test.cpp
OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test -std=c++17 -lboost_regex
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o test