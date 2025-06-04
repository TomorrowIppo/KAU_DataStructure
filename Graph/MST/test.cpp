#include <iostream>
#include "../AdjacencyMatrix/AdjacencyMatrix.hpp"
#include "../AdjacencyList/AdjacencyList.hpp"
#include "Kruskal.hpp"

using namespace std;

int main() {
    AdjacencyList g;

    // 단방향이 기본이므로 양방향 간선을 직접 넣어줌
    g.insertEdge(1, 2, 1);
    g.insertEdge(2, 1, 1);

    g.insertEdge(1, 3, 2);
    g.insertEdge(3, 1, 2);

    g.insertEdge(2, 4, 11);
    g.insertEdge(4, 2, 11);

    g.insertEdge(3, 5, 5);
    g.insertEdge(5, 3, 5);

    g.insertEdge(5, 1, 7);
    g.insertEdge(1, 5, 7);

    g.printGraph();

    std::cout << "\nKruskal MST Edges:\n";
    GraphSearch::kruskal(g);

    return 0;
}