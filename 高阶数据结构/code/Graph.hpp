#pragma once
#include <iostream>
#include <vector>
#include <map>

#define __GRAPH_TABLE__
// 领接矩阵

#ifdef __GRAPH_MATRIX__

template <class V,class W,W MAX_W = __INT32_MAX__, bool Direction = false> 
class Graph
{
public:
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

    void printMatrix() const 
    {
        for(auto& row : _matrix)
        {
            for(auto val : row)
                std::cout << val << " ";
            std::cout << std::endl;
        }
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