// Banu Miruna-Elena, 321CA, November 2019
#include "algo.h"
#include <iostream>
#include <queue>

std::vector<int> computeDijkstra(const std::vector<std::vector<edge>>& graph, int node) {

	std::vector<int> dist(graph.size(), INF2);
    std::priority_queue<edge, std::vector<edge>, std::greater<edge>> q;

    q.push(std::make_pair(0, node));
    dist[node] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        for (auto n : graph[u]) {
            int v = n.first;
            int w = n.second;

            if (w < 0) {
                return std::vector<int>();
            }

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                q.push(std::make_pair(dist[v], v));
            }
        }
    }

    for (auto& d : dist) {
        if (d == INF2) {
            d = INF;
        }
    }

    return dist;
}

namespace Dijkstra {
	std::vector<std::vector<int>> shortest_path(const std::vector<std::vector<edge>>& graph) {
		std::vector<std::vector<int>> distanceMatrix;
        std::vector<int> nodeArray;

		for (unsigned int i = 0; i < graph.size(); ++i) {
			nodeArray = computeDijkstra(graph, i);
            if (!nodeArray.size()) {
                return std::vector<std::vector<int>>();
            } else {
                distanceMatrix.push_back(nodeArray);
            }
		}

    	return distanceMatrix;
	}
}