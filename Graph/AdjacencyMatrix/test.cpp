#include <iostream>
#include "AdjacencyMatrix.hpp"

int main() {
    // 정점 5개짜리 그래프 생성
    AdjacencyMatrix graph(5);

    // isEmpty 검사
    std::cout << "\n그래프가 비어있나요? " << (graph.isEmpty() ? "Yes" : "No") << "\n\n";

    // 간선 추가 (방향 그래프)
    graph.insertEdge(1, 2);
    graph.insertEdge(1, 3);
    graph.insertEdge(2, 4);
    graph.insertEdge(3, 5);
    graph.insertEdge(5, 1);

    std::cout << "그래프 상태 (초기):\n";
    graph.printGraph();

    // 간선 삭제
    graph.deleteEdge(1, 3);
    std::cout << "\n간선 (1->3) 삭제 후:\n";
    graph.printGraph();

    // 정점 삭제 (간선 제거만)
    graph.deleteVertex(2);
    std::cout << "\n정점 2 삭제 (간선 제거) 후:\n";
    graph.printGraph();

    // 정점 추가 (사실 insertVertex는 크기 조정용이므로 v=7 넣어봄)
    graph.insertVertex(7);
    graph.insertEdge(6, 7);
    graph.insertEdge(7, 1);
    std::cout << "\n정점 7 추가 및 (6, 7), (7, 1) 간선 생성 후:\n";
    graph.printGraph();

    // isEmpty 검사
    std::cout << "\n그래프가 비어있나요? " << (graph.isEmpty() ? "Yes" : "No") << "\n";

    // Vertices 검사
    auto all_v = graph.getVertices();
    std::cout << "\n정점들 : ";
    for(auto v : all_v) {
        std::cout << v << ' ';
    }
    std::cout << "\n";

    return 0;
}
