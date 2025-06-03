#include "../AdjacencyMatrix/AdjacencyMatrix.hpp"
#include "GraphSearch.hpp"

int main() {
    AdjacencyMatrix g(5);
    g.insertEdge(1, 2);
    g.insertEdge(1, 4);
    g.insertEdge(2, 3);
    g.insertEdge(2, 5);
    g.insertEdge(4, 5); // 순환 발생생

    // 그래프 형태 출력
    g.printGraph();

    std::cout << "DFS:\n";
    GraphSearch::dfs(g, 1);

    std::cout << "BFS:\n";
    GraphSearch::bfs(g, 1);
}