
#include <iostream>
#include "Graph.hpp"

void testGraph()
{
    Graph<char,int> g("012378",6);
    g.addEdge('0', '1', 1);
    g.addEdge('0', '3', 4);
    g.addEdge('0', '2', 2);
    g.addEdge('1', '2', 5);
    g.addEdge('3', '2', 1);
    g.addEdge('3','7',3);
    g.addEdge('2','8',3);
    // g.BFS('0');
    g.DFS('0');
    g.printMatrix();
}

void testDFS()
{
    Graph<char,int> g("012378",6);
    g.addEdge('0', '1', 1);
    g.addEdge('0', '3', 4);
    g.addEdge('0', '2', 2);
    g.addEdge('1', '2', 5);
    g.addEdge('3', '2', 1);
    g.addEdge('3','7',3);
    g.addEdge('2','8',3);
    // g.BFS('0');
    g.DFS('0');
}

auto main() -> int
{
    testDFS();

    return 0;
}