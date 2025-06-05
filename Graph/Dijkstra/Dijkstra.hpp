#pragma once

#include <iostream>
#include <vector>
#include "../IGraph.hpp"
#include "../../Queue/PriorityQueue/PriorityQueue_by_Heap.hpp"

namespace GraphSearch {

    inline void dijkstra(IGraph& g, int start) {
        using namespace std;

        vector<int> vertices = g.getVertices();
        int n = vertices.size();

        vector<int> dist(n + 1, INF);
        vector<bool> visited(n + 1, false);
        dist[start] = 0;

        PriorityQueue<int> pq(HeapType::MIN);
        pq.Insert(0, start);

        while (!pq.isEmpty()) {
            int u = pq.Delete().getValue();

            if (visited[u]) continue;
            visited[u] = true;

            for (int v : g.getAdjacency(u)) {
                int weight = g.getWeight(u, v);
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.Insert(dist[v], v);
                }
            }
        }

        cout << "[Dijkstra] Shortest distances from vertex " << start << ":\n";
        for (int v : vertices) {
            if (dist[v] == INF)
                cout << "Vertex " << v << " : INF\n";
            else
                cout << "Vertex " << v << " : " << dist[v] << "\n";
        }
        cout << "\n";
    }

} // namespace GraphSearch
