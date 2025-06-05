#include <iostream>
#include "../AdjacencyList/AdjacencyList.hpp"
#include "Dijkstra.hpp"

int main() {
    AdjacencyList g(true);    // 단방향 그래프 기반 (다익스트라는 방향 있어도 OK)

    // 정점 번호: 1 ~ 5
    g.insertEdge(1, 2, 10);
    g.insertEdge(1, 3, 3);
    g.insertEdge(2, 3, 1);
    g.insertEdge(2, 4, 2);
    g.insertEdge(3, 2, 4);
    g.insertEdge(3, 4, 8);
    g.insertEdge(3, 5, 2);
    g.insertEdge(4, 5, 7);
    g.insertEdge(5, 4, 9);

    g.printGraph();
    std::cout << "\n";

    // 시작 정점 1로 Dijkstra 실행
    GraphSearch::dijkstra(g, 1);

    return 0;
}
