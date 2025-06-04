#pragma once

#include <iostream>
#include <vector>

#define INF 1e9

class IGraph {
public:
    virtual std::vector<int> getAdjacency(int v) const = 0;
    virtual std::vector<int> getVertices() const = 0;
    virtual int getWeight(int u, int v) const = 0;
    virtual bool isEmpty() const = 0;

    // 삽입
    virtual void insertVertex(int v) = 0;
    virtual void insertEdge(int u, int v, int w) = 0;

    // 삽입 지원 함수 (무방향 삽입, 방향 삽입) 기본적으로 무방향 삽입
    virtual void setDirected(bool directed) = 0;
    virtual bool isDirected() const = 0;


    // 삭제
    virtual void deleteVertex(int v) = 0;
    virtual void deleteEdge(int u, int v) = 0;

    // 시각화
    virtual void printGraph() const = 0;
    
    virtual ~IGraph() = default;
};