#pragma once

#include <iomanip>
#include <map>
#include "../IGraph.hpp"

struct EdgeVertex {
    int to;
    int weight;
    EdgeVertex* next;

    EdgeVertex(int to, int weight, EdgeVertex* next = nullptr)
        : to(to), weight(weight), next(next) {}
};

class AdjacencyList : public IGraph {
private:
    // unordered_map이 평균적으로 더 빠르지만,
    // 정점 ID를 오름차순으로 출력하기 위해 학습 목적상 map 사용
    std::map<int, EdgeVertex*> table;

public:
    AdjacencyList();
    ~AdjacencyList();

    std::vector<int> getAdjacency(int v) const override;
    std::vector<int> getVertices() const override;
    bool isEmpty() const override;
    void insertVertex(int v) override;
    void insertEdge(int u, int v, int w) override;
    void deleteVertex(int v) override;
    void deleteEdge(int u, int v) override;
    void printGraph() const override;
};

inline AdjacencyList::AdjacencyList() {}

inline AdjacencyList::~AdjacencyList() {
    for (auto& item : table) {
        EdgeVertex* head = item.second;

        while (head) {
            EdgeVertex* temp = head;
            head = head->next;
            delete temp;
        }
    }
}

inline void AdjacencyList::insertVertex(int v) {
    if (table.count(v)) return;
    table[v] = nullptr;
}

inline void AdjacencyList::insertEdge(int u, int v, int w) {   
    // push_front 방식으로 구현 O(1)
    // push_back은 리스트의 길이 k에 비례해 O(k)

    if (!table.count(u)) insertVertex(u);
    if (!table.count(v)) insertVertex(v);

    EdgeVertex* newNode = new EdgeVertex(v, w, table[u]);
    table[u] = newNode;
}

inline void AdjacencyList::deleteEdge(int u, int v) {
    if (!table.count(u)) return;

    EdgeVertex* cur = table[u];
    EdgeVertex* prev = nullptr;

    while (cur) {
        if (cur->to == v) {
            if (prev) prev->next = cur->next;
            else table[u] = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

inline void AdjacencyList::deleteVertex(int v) {
    if (!table.count(v)) return;

    // v에서 나가는 간선 제거
    EdgeVertex* cur = table[v];
    while (cur) {
        EdgeVertex* next = cur->next;
        delete cur;
        cur = next;
    }
    table.erase(v);

    // 다른 정점에서 v로 가는 간선 제거
    for (auto& item : table) {
        int key = item.first;
        EdgeVertex* cur = item.second;
        EdgeVertex* prev = nullptr;

        while (cur) {
            if (cur->to == v) {
                if (prev) prev->next = cur->next;
                else table[key] = cur->next;
                delete cur;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
    }
}

inline std::vector<int> AdjacencyList::getAdjacency(int v) const {
    if (!table.count(v))
        throw std::out_of_range("Vertex does not exist");

    std::vector<int> adj;
    EdgeVertex* cur = table.at(v);
    while (cur) {
        adj.push_back(cur->to);
        cur = cur->next;
    }
    return adj;
}

std::vector<int> AdjacencyList::getVertices() const {
    std::vector<int> vertices;
    vertices.reserve(table.size());

    for (const auto& pair : table) {
        vertices.push_back(pair.first);
    }
    return vertices;
}

inline bool AdjacencyList::isEmpty() const {
    return table.empty();
}

inline void AdjacencyList::printGraph() const {
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* RESET = "\033[0m";

    if (table.empty()) {
        std::cout << "Graph is empty.\n";
        return;
    }

    for (const auto& item : table) {
        int v = item.first;
        EdgeVertex* cur = item.second;

        std::cout << GREEN << "[" << v << "]" << RESET << " -> ";
        while (cur) {
            std::cout << "(" << BLUE << cur->to << RESET << ", " << cur->weight << ") -> ";
            cur = cur->next;
        }
        std::cout << "NULL\n";
    }
}
