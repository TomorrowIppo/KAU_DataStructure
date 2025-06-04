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
    bool dir;

public:
    AdjacencyList(bool dir = false) : dir(dir) {}
    ~AdjacencyList();

    std::vector<int> getAdjacency(int v) const override;
    std::vector<int> getVertices() const override;
    int getWeight(int u, int v) const override;
    bool isEmpty() const override;
    void insertVertex(int v) override;
    void insertEdge(int u, int v, int w) override;
    void setDirected(bool directed) override;
    bool isDirected() const override;
    void deleteVertex(int v) override;
    void deleteEdge(int u, int v) override;
    void printGraph() const override;
};

inline AdjacencyList::~AdjacencyList() {
    for (auto& item : this->table) {
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

    if (!this->table.count(u)) insertVertex(u);
    if (!this->table.count(v)) insertVertex(v);

    EdgeVertex* newNode = new EdgeVertex(v, w, this->table[u]);
    this->table[u] = newNode;

    // 무방향일 경우 v -> u도 삽입
    if (!this->dir) {
        EdgeVertex* revNode = new EdgeVertex(u, w, this->table[v]);
        this->table[v] = revNode;
    }
}

inline void AdjacencyList::setDirected(bool directed) {
    this->dir = directed;
}

inline bool AdjacencyList::isDirected() const {
    return this->dir;
}

inline void AdjacencyList::deleteEdge(int u, int v) {
    if (!this->table.count(u)) return;

    EdgeVertex* cur = this->table[u];
    EdgeVertex* prev = nullptr;

    while (cur) {
        if (cur->to == v) {
            if (prev) prev->next = cur->next;
            else this->table[u] = cur->next;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

inline void AdjacencyList::deleteVertex(int v) {
    if (!this->table.count(v)) return;

    // v에서 나가는 간선 제거
    EdgeVertex* cur = this->table[v];
    while (cur) {
        EdgeVertex* next = cur->next;
        delete cur;
        cur = next;
    }
    this->table.erase(v);

    // 다른 정점에서 v로 가는 간선 제거
    for (auto& item : this->table) {
        int key = item.first;
        EdgeVertex* cur = item.second;
        EdgeVertex* prev = nullptr;

        while (cur) {
            if (cur->to == v) {
                if (prev) prev->next = cur->next;
                else this->table[key] = cur->next;
                delete cur;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
    }
}

inline std::vector<int> AdjacencyList::getAdjacency(int v) const {
    if (!this->table.count(v))
        throw std::out_of_range("Vertex does not exist");

    std::vector<int> adj;
    EdgeVertex* cur = this->table.at(v);
    while (cur) {
        adj.push_back(cur->to);
        cur = cur->next;
    }
    return adj;
}

inline std::vector<int> AdjacencyList::getVertices() const {
    std::vector<int> vertices;
    vertices.reserve(this->table.size());

    for (const auto& pair : this->table) {
        vertices.push_back(pair.first);
    }
    return vertices;
}

inline int AdjacencyList::getWeight(int u, int v) const {
    if (!this->table.count(u))
        throw std::out_of_range("Vertex u does not exist");

    EdgeVertex* cur = this->table.at(u);
    while (cur != nullptr) {
        if (cur->to == v)
            return cur->weight;
        cur = cur->next;
    }

    throw std::out_of_range("Edge from u to v does not exist");
}

inline bool AdjacencyList::isEmpty() const {
    return this->table.empty();
}

inline void AdjacencyList::printGraph() const {
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* RESET = "\033[0m";

    if (this->table.empty()) {
        std::cout << "Graph is empty.\n";
        return;
    }

    std::cout << "[AdjList]\n";
    for (const auto& item : this->table) {
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
