
#include <iostream>
#include "Graph.hpp"
#include <cstring>
void testGraph()
{
    Graph<char, int> g("012378", 6);
    g.addEdge('0', '1', 1);
    g.addEdge('0', '3', 4);
    g.addEdge('0', '2', 2);
    g.addEdge('1', '2', 5);
    g.addEdge('3', '2', 1);
    g.addEdge('3', '7', 3);
    g.addEdge('2', '8', 3);
    // g.BFS('0');
    g.DFS('0');
    g.printMatrix();
}

void testDFS()
{
    Graph<char, int> g("012378", 6);
    g.addEdge('0', '1', 1);
    g.addEdge('0', '3', 4);
    g.addEdge('0', '2', 2);
    g.addEdge('1', '2', 5);
    g.addEdge('3', '2', 1);
    g.addEdge('3', '7', 3);
    g.addEdge('2', '8', 3);
    // g.BFS('0');
    g.DFS('0');
}
void TestGraphMinTree()
{
    const char *str = "abcdefghi";
    Graph<char, int> g(str, strlen(str));
    g.addEdge('a', 'b', 4);
    g.addEdge('a', 'h', 8);

//g.AdaddEdgea', 'h', 9);
    g.addEdge('b', 'c', 8);
    g.addEdge('b', 'h', 11);
    g.addEdge('c', 'i', 2);
    g.addEdge('c', 'f', 4);
    g.addEdge('c', 'd', 7);
    g.addEdge('d', 'f', 14);
    g.addEdge('d', 'e', 9);
    g.addEdge('e', 'f', 10);
    g.addEdge('f', 'g', 2);
    g.addEdge('g', 'h', 1);
    g.addEdge('g', 'i', 6);
    g.addEdge('h', 'i', 7);
    Graph<char, int> kminTree(str,strlen(str));
    std::cout << "Kruskal:" << g.KrusKal(kminTree) << std::endl;
    kminTree.printMatrix();
    kminTree.BFS('b');
    // Graph<char, int> pminTree;
    // std::cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
    // pminTree.Print();
}

auto main() -> int
{
    TestGraphMinTree();

    return 0;
}
