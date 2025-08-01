// 统计子矩阵
#include <iostream>
#include <vector>

using board_t = std::vector<std::vector<int>>;

int prefixSumSolve(board_t& matrix, int k)
{
    // 计算小于等于k
    board_t prefix(matrix.size(),std::vector<int>(matrix[0].size(), 0));
    // 构建前缀和矩阵
    int m = prefix.size() - 1, n = prefix[0].size() - 1;

    for(int i = 1;i <= m;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            // 可能出现越界的问题
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] + matrix[i][j] - prefix[i - 1][j - 1];
        }
    }

    // 
}
void process()
{
    
    int m = 0, n = 0, k = 0;
    std::cin >> m >> n >> k;
    // 由于越界的问题，提前加大空间
    board_t matrix(m + 1,std::vector<int>(n + 1,0));
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= n;j++)
            std::cin >> matrix[i][j];

    auto ret = prefixSumSolve(matrix,k);
    std::cout << ret << std::endl;
}
int main()
{
    process();
    return 0;
}