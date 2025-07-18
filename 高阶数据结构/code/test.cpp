
#include <iostream>
#include "Graph.hpp"

void testGraph()
{
    Graph<char,int,true> g("0123",4);
    g.addEdge('0', '1', 1);
    g.addEdge('0', '3', 4);
    g.addEdge('0', '2', 2);
    g.addEdge('1', '2', 5);
    g.addEdge('3', '2', 1);
    g.printTable();
}

auto main() -> int
{
    testGraph();

    return 0;
}