#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include "../IGraph.hpp"
#include "../../Queue/PriorityQueue/PriorityQueue_by_Heap.hpp"

namespace GraphSearch {

    inline void prim(IGraph &g) {
        using namespace std;

        vector<int> vertices = g.getVertices();
        int n = vertices.size();

        // 각 정점에 대한 최소 가중치와 부모 정보
        vector<int> key(n + 1, INF);
        vector<int> parent(n + 1, -1);
        vector<bool> inMST(n + 1, false);

        // 너가 만든 PriorityQueue 활용
        PriorityQueue<int> pq(HeapType::MIN);

        int start = vertices[0];
        pq.Insert(0, start); // 가중치 0부터 시작점 삽입
        key[start] = 0;

        while (!pq.isEmpty()) {
            int u = pq.Delete().getValue();

            if (inMST[u]) continue;
            
            inMST[u] = true;
            for (int v : g.getAdjacency(u)) {
                int weight = g.getWeight(u, v);
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.Insert(weight, v);
                }
            }
        }

        int total = 0;
        cout << "[Prim] Edges in MST:" << '\n';
        for (int v : vertices) {
            int u = parent[v];

            if (u == -1) continue;

            int w = g.getWeight(u, v);
            cout << u << " - " << v << " : " << w << '\n';
            total += w;
        }
        cout << "Total Weight of MST: " << total << "\n\n";
    }

} // namespace GraphSearch
