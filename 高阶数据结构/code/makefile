src=test.cpp
dst=bin
cxx=g++
flag=-std=c++11 -g -Wall
includepath=./include

$(dst):$(src)
	@echo "start comiple"
	@$(cxx) -o $(dst) $(src) $(flag)
	@echo "compile sucess"

.PHONY:clean
clean:
	rm -rf $(dst)
