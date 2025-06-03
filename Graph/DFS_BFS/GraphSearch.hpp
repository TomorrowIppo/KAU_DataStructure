#pragma once

#include <iostream>
#include "../IGraph.hpp"
#include <unordered_set>
#include <queue>

namespace GraphSearch {

    void dfsUtil(const IGraph& g, int v, std::unordered_set<int>& visited) {
        if (visited.count(v)) return;

        visited.insert(v);
        std::cout << v << " ";

        for (int neighbor : g.getAdjacency(v)) {
            dfsUtil(g, neighbor, visited);
        }
    }

    void dfs(const IGraph& g, int start) {
        std::unordered_set<int> visited;
        dfsUtil(g, start, visited);
        std::cout << std::endl;
    }

    void bfs(const IGraph& g, int start) {
        std::unordered_set<int> visited;
        std::queue<int> q;

        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            std::cout << cur << " ";

            for (int nxt : g.getAdjacency(cur)) {
                if (!visited.count(nxt)) {
                    visited.insert(nxt);
                    q.push(nxt);
                }
            }
        }
        std::cout << std::endl;
    }

}   // namespace GraphSearch