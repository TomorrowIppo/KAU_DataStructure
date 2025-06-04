#pragma once

#include <iostream>
#include "../IGraph.hpp"
#include <tuple>
#include <algorithm>

namespace GraphSearch {

    class UnionFind {
    public:
        std::vector<int> parent, rank;

        UnionFind(int n) : parent(n + 1), rank(n + 1, 0) {
            for(int i = 0; i <= n; i++) this->parent[i] = i;
        }

        int find_root(int x) {
            if(x == this->parent[x]) return x;
            return this->parent[x] = find_root(this->parent[x]);
        }

        bool merge(int u, int v) {
            u = find_root(u);
            v = find_root(v);
            if (u == v) return false;
            if (rank[u] < rank[v]) std::swap(u, v);
            this->parent[v] = u;
            if (rank[u] == rank[v]) rank[u]++;
            return true;
        }
    };
} // namespace GraphSearch