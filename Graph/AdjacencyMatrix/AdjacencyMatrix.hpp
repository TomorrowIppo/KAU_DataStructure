#pragma once

#include <iomanip>
#include "../IGraph.hpp"

/*
인접행렬에서 비연속적인 정점을 추가할 때 사이에 빈 정점이 생길 수 있으나, 
현재는 큰 필요성을 느끼지 않아 별도의 vertices 멤버변수를 두지 않고 의미 있는 정점만 관리하는 기능은 구현하지 않았습니다.
*/

class AdjacencyMatrix : public IGraph {
private:
    std::vector<std::vector<int>> matrix;
    int v_cnt;
    int e_cnt;

public:
    AdjacencyMatrix(int n) : 
        matrix(n + 1, std::vector<int>(n + 1, 0)), 
        v_cnt(n),
        e_cnt(0) 
        {}

    std::vector<int> getAdjacency(int v) const override;
    std::vector<int> getVertices() const override;
    bool isEmpty() const override;
    void insertVertex(int v) override;
    void insertEdge(int u, int v) override;
    void deleteVertex(int v) override;
    void deleteEdge(int u, int v) override;
    void printGraph() const override;
};

// ------------------------ Implementation ----------------------------

inline std::vector<int> AdjacencyMatrix::getAdjacency(int v) const {
    if(v < 1 || v >= this->matrix.size()) 
        throw std::out_of_range("Node does not exist in the graph.");

    std::vector<int> adj;
    for(int i = 1; i < this->matrix[v].size(); i++)
        if(this->matrix[v][i]) adj.push_back(i);
    return adj;
}

inline std::vector<int> AdjacencyMatrix::getVertices() const {
    std::vector<int> vertices;
    // 1부터 v_cnt까지 정점 번호를 모두 추가
    for (int v = 1; v <= v_cnt; ++v) {
        vertices.push_back(v);
    }
    return vertices;
}

inline bool AdjacencyMatrix::isEmpty() const {
    return this->v_cnt == 0 || this->e_cnt == 0;
}

inline void AdjacencyMatrix::insertVertex(int v) {
    if(v + 1 <= this->matrix.size()) 
        return;

    this->matrix.resize(v + 1);
    for(auto& row : this->matrix)
        row.resize(v + 1, 0);
    
    this->v_cnt = v;
}

inline void AdjacencyMatrix::insertEdge(int u, int v) {
    if (u < 1 || v < 1 || u >= this->matrix.size() || v >= this->matrix.size())
        throw std::out_of_range("Invalid vertex index in insertEdge");

    this->matrix[u][v] = 1;
    this->e_cnt++;
}

inline void AdjacencyMatrix::deleteVertex(int v) {
    // 삭제 시 정점 번호 고정을 위해 간선만 제거하여 고립시킴킴
    if (v < 1 || v >= matrix.size())
        throw std::out_of_range("Invalid vertex index");

    for (int i = 1; i < this->matrix.size(); i++) {
        if(this->matrix[v][i]) {
            this->matrix[v][i] = 0;
            this->e_cnt--;
        }
        if(this->matrix[i][v]) {
            this->matrix[i][v] = 0;
            this->e_cnt--;
        }
    }
}

inline void AdjacencyMatrix::deleteEdge(int u, int v) {
    if (u < 1 || v < 1 || u >= this->matrix.size() || v >= this->matrix.size())
        throw std::out_of_range("Invalid vertex index in deleteEdge");

    this->matrix[u][v] = 0;
    this->e_cnt--;
}

inline void AdjacencyMatrix::printGraph() const
{
    int n = matrix.size();
    if (n <= 1) {
        std::cout << "Graph is empty.\n";
        return;
    }

    constexpr const char* GREEN = "\033[32m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* RESET = "\033[0m";

    // 헤더 행: 정점 번호 초록색 출력
    std::cout << "    ";  // 왼쪽 공간
    for (int i = 1; i < n; ++i)
        std::cout << GREEN << std::setw(2) << i << RESET << " ";
    std::cout << "\n";

    for (int i = 1; i < n; ++i) {
        std::cout << GREEN << std::setw(2) << i << RESET << ": ";
        for (int j = 1; j < n; ++j) {
            if (matrix[i][j] == 1)
                std::cout << BLUE << std::setw(2) << 1 << RESET << " ";
            else
                std::cout << std::setw(2) << 0 << " ";
        }
        std::cout << "\n";
    }
}
