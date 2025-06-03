#include <iostream>
#include "AdjacencyMatrix.hpp"

int main() {
    // ���� 5��¥�� �׷��� ����
    AdjacencyMatrix graph(5);

    // isEmpty �˻�
    std::cout << "\n�׷����� ����ֳ���? " << (graph.isEmpty() ? "Yes" : "No") << "\n\n";

    // ���� �߰� (���� �׷���)
    graph.insertEdge(1, 2);
    graph.insertEdge(1, 3);
    graph.insertEdge(2, 4);
    graph.insertEdge(3, 5);
    graph.insertEdge(5, 1);

    std::cout << "�׷��� ���� (�ʱ�):\n";
    graph.printGraph();

    // ���� ����
    graph.deleteEdge(1, 3);
    std::cout << "\n���� (1->3) ���� ��:\n";
    graph.printGraph();

    // ���� ���� (���� ���Ÿ�)
    graph.deleteVertex(2);
    std::cout << "\n���� 2 ���� (���� ����) ��:\n";
    graph.printGraph();

    // ���� �߰� (��� insertVertex�� ũ�� �������̹Ƿ� v=7 �־)
    graph.insertVertex(7);
    graph.insertEdge(6, 7);
    graph.insertEdge(7, 1);
    std::cout << "\n���� 7 �߰� �� (6, 7), (7, 1) ���� ���� ��:\n";
    graph.printGraph();

    // isEmpty �˻�
    std::cout << "\n�׷����� ����ֳ���? " << (graph.isEmpty() ? "Yes" : "No") << "\n";

    // Vertices �˻�
    auto all_v = graph.getVertices();
    std::cout << "\n������ : ";
    for(auto v : all_v) {
        std::cout << v << ' ';
    }
    std::cout << "\n";

    return 0;
}
