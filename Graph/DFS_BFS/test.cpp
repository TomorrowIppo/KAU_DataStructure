#include "../AdjacencyMatrix/AdjacencyMatrix.hpp"
#include "../AdjacencyList/AdjacencyList.hpp"
#include "GraphSearch.hpp"

int main() {
    // 인접행렬 탐색
    std::cout << "[AdjMatrix]\n";

    AdjacencyMatrix g(5);

    g.insertEdge(1, 2);
    g.insertEdge(1, 4);
    g.insertEdge(2, 3);
    g.insertEdge(2, 5);
    g.insertEdge(4, 5); 
    g.insertEdge(3, 1); // 순환 발생

    // 그래프 형태 출력
    g.printGraph();

    std::cout << "DFS:\n";
    GraphSearch::dfs(g, 1);

    std::cout << "BFS:\n";
    GraphSearch::bfs(g, 1);

    std::cout << "\n-------------------------------------------------------------------------------\n\n";
    std::cout << "[AdjList]\n";

    // 인접리스트 탐색
    AdjacencyList h;

    h.insertEdge(1, 2);
    h.insertEdge(1, 4);
    h.insertEdge(2, 3);
    h.insertEdge(2, 5);
    h.insertEdge(4, 5); 
    h.insertEdge(3, 1); // 순환 발생

    // 그래프 형태 출력
    h.printGraph();

    std::cout << "DFS:\n";
    GraphSearch::dfs(h, 1);

    std::cout << "BFS:\n";
    GraphSearch::bfs(h, 1);
}