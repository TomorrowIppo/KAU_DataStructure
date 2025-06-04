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

    inline void kruskal(IGraph &g) {
        std::vector<std::tuple<int, int, int>> edges;
        std::vector<int> vertices = g.getVertices();
        
        for (int u : vertices) {
            for (int v : g.getAdjacency(u)) {
                if (u < v)  // 중복 방지
                    edges.push_back({g.getWeight(u, v), u, v});
            }
        }
        std::sort(edges.begin(), edges.end());

        int size = vertices.size();
        UnionFind uf(size);
        int total = 0;

        std::cout << "[Kruskal] Edges in MST:\n";

        for (const auto& [w, u, v] : edges) {
            if (uf.find_root(u) != uf.find_root(v)) {
                uf.merge(u, v);
                std::cout << u << " - " << v << " : " << w << "\n";
                total += w;
            }
        }

        std::cout << "Total Weight of MST: " << total << "\n\n";
    }
} // namespace GraphSearch