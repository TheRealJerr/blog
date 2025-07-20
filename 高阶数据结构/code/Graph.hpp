#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include "UnionFindSet.hpp"
#define __GRAPH_MATRIX__
// 领接矩阵

#ifdef __GRAPH_MATRIX__

template <class V,class W,W MAX_W = __INT32_MAX__, bool Direction = false> 
class Graph
{
public:
    using Self = Graph<V,W,MAX_W,Direction>;
    Graph(const V* array, int n)
    {
        for(int i = 0;i < n;i++)
        {
            _vertexs.push_back(array[i]);
            _indexMap[array[i]] = i;
        }

        _matrix.resize(n);
        for(auto& row : _matrix)
        {
            row.resize(n, MAX_W);
        }

    }   

    void addEdge(const V& src, const V& dst, const W& w)
    {
        // 判断数据是否合理
        if(!_indexMap.count(src) || !_indexMap.count(dst)) 
        {
            throw std::invalid_argument("顶点不存在");
            return;
        }
        auto index1 = _indexMap[src];
        auto index2 = _indexMap[dst];
        // 添加边
        if(!Direction)
        {
            _matrix[index1][index2] = _matrix[index2][index1] = w; 
        }
        else _matrix[index1][index2] = w;
    }

    void addEdgeByPos(size_t src, size_t dst, const W& w)
    {
        // 判断数据是否合理
       
        // 添加边
        if(!Direction)
        {
            _matrix[src][dst] = _matrix[dst][src] = w; 
        }
        else _matrix[src][dst] = w;
    }
    void printMatrix() const 
    {
        for(auto& row : _matrix)
        {
            for(auto val : row)
                if(val != MAX_W) std::cout << val << " ";
                else std::cout << "* ";
            std::cout << std::endl;
        }
        
    }

    void BFS(const V& begin)
    {
        if(_indexMap.count(begin) == false) 
        {
            throw std::invalid_argument("没有该数据");
            return;
        }
        
        int cur = _indexMap[begin];
        std::queue<int> q;
        std::vector<bool> used(_vertexs.size(), false);
        q.push(cur);
        used[cur] = true;
        int step = 0;
        while(q.size())
        {
            int sz = q.size();
            std::cout << "第" << step << "层" << std::endl;
            for(int i = 0;i < sz;i++)
            {
                cur = q.front();
                q.pop();
                std::cout << _vertexs[cur] << std::endl;
                for(int j = 0;j < _matrix[cur].size();j++)
                {
                    if(_matrix[cur][j] != __INT32_MAX__ && !used[j])
                    {
                        q.push(j);
                        used[j] = true;
                    }
                }
            }
            ++step;
        }

    }

    // * step : 代表所处的层数
    void DFSHelper(int pos, std::vector<bool>& used)
    {
        used[pos] = true;
        std::cout << _vertexs[pos] << std::endl;
        for(decltype(_matrix[pos].size()) j = 0;j < _matrix[pos].size();j++)
        {
            if(_matrix[pos][j] != __INT32_MAX__ && used[j] == false)
                DFSHelper(j, used);
        }
    }
    void DFS(const V& val)
    {
        if(_indexMap.count(val) == false) 
        {
            throw std::invalid_argument("不含有该值");
            return;
        }
        std::vector<bool> used(_vertexs.size(), false);
        DFSHelper(_indexMap[val], used);
    }

    struct Edge
    {
        Edge(int src,int dst,int wage) : 
            _src(src), _dst(dst), _wage(wage)
        {}
        int _src;
        int _dst;
        W _wage;
        bool operator>(const Edge& edge) const 
        {
            return _wage > edge._wage;
        }
    };

    // 通过KrusKal算法构建最小生成树
    W KrusKal(Self& tree)
    {
        std::priority_queue<Edge,std::vector<Edge>,std::greater<Edge>> pq;
        // 
        int n = _vertexs.size();
        for(int i = 0;i < n;i++)
        { 
            for(int j = 0;j < n;j++)
            {
                if(i < j && _matrix[i][j] != MAX_W)
                    pq.push({i, j, _matrix[i][j]});
            }
        }
        UnionFindSet ufs(n);
        // 通过KrusKal算法选出n - 1条边
        int size = 0;
        W totalW = W();
        while(pq.size())
        {
            Edge min = pq.top();
            pq.pop();
            
            if(!ufs.isInOneSet(min._src,min._dst))
            {
                tree.addEdgeByPos(min._src,min._dst,min._wage);
                ufs.Union(min._src,min._dst);
                ++size;
                totalW += min._wage;
            }
        }
        // 判断是否构成最小生成树
        if(size == n - 1)
        {
            return totalW;
        }
        else 
        {
            return W();
        }
        return W();
    }   

    W Prime(Self& tree,const V& begin)
    {   
        if(_indexMap.count(begin) == false)
        {
            throw std::invalid_argument("错误的输入");
            return W();
        }

        auto index = _indexMap[begin];
        tree._vertexs = _vertexs;
        tree._indexMap = _indexMap;
        tree._matrix = _matrix;
        size_t n = _vertexs.size();
        for(size_t i = 0;i < n;i++)
            tree._matrix.resize(n, MAX_W);
        // prime算法的本质将原来的看做两块
        std::set<int> X_set;
        std::set<int> Y_set; 
        X_set.insert(index);
        for(size_t i = 0;i < n;i++)
            if(i != index) Y_set.insert(i);
        //
        
    }
private:
    std::vector<V> _vertexs;
    std::map<V,int> _indexMap;
    std::vector<std::vector<W>> _matrix;
};

#endif


#ifdef __GRAPH_TABLE__

// 领接表
template <class W>
struct Edge
{
    Edge(int src,int dst, W wage)
        : _src(src), _dst(dst), _wage(wage)
    {}
    int _src;
    int _dst; // 目标点的下标
    W _wage; 

    Edge<W>* _next = nullptr;
};

template <class V,class W, bool Direction = false>
class Graph
{
public:
    using EdgeType = Edge<W>;
    Graph(const V* a, int n)
    {
        for(int i = 0;i < n;i++)
        {
            _datas.push_back(a[i]);
            _indexMap[a[i]] = i;
        }
        _edges.resize(n, nullptr);
    }
    void addEdge(const V& src,const V& dst,W w)
    {
        auto index1 = _indexMap[src];
        auto index2 = _indexMap[dst];
        // 判断是有向还是无向
        EdgeType* edge = new EdgeType(index1, index2, w);
        edge->_next = _edges[index1];
        _edges[index1] = edge;

        if(!Direction)
        {
            EdgeType* redge = new EdgeType(index2, index1, w);
            redge->_next = _edges[index2];
            _edges[index2] = redge;
        }
    }

    void printTable()
    {
        for(size_t i = 0;i < _edges.size(); i++)
        {
            EdgeType* ptr = _edges[i];
            std::cout << "value:" << _datas[i] << std::endl;
            while(ptr)
            {
                std::cout << "[" << ptr->_src << "] -> " << ptr->_dst << std::endl; 
                ptr = ptr->_next;
            }
            std::cout << std::endl;
        }
    }
private:    

    std::vector<V> _datas;
    std::map<V,int> _indexMap;
    std::vector<EdgeType*> _edges;
};

#endif