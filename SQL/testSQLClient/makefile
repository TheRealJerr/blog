# 编译器设置
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra

# 目标可执行文件名
TARGET := test_mysql

# 源文件
SRC := testSQL.cpp

# 对象文件 (由 .cpp 文件生成 .o 文件)
OBJ := $(SRC:.cpp=.o)

# 链接器标志：链接 mysqlcppconn 库
LDFLAGS := -lmysqlcppconnx

# 默认目标：编译所有
all: $(TARGET)

# 链接目标：将 .o 文件链接成可执行文件
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# 编译规则：将 .cpp 文件编译成 .o 文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(TARGET) $(OBJ)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 声明这些目标不是实际文件
.PHONY: all clean run