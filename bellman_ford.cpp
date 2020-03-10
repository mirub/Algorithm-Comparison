// Banu Miruns Elena, 321CA, November 2019
#include "algo.h"
#include <iostream>
#include <queue>

std::vector<int> computeBellmanFord(const std::vector<std::vector<edge>>& graph, int node) {
    std::queue<int> q;
    std::vector<bool> isEnqueued(graph.size(), false);
    std::vector<int> distance(graph.size(), INF);
    std::vector<unsigned int> count(graph.size(), 0);

    distance[node] = 0;
    q.push(node);
    isEnqueued[node] = true;
    count[node]++;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        isEnqueued[u] = false;
        for (unsigned int i = 0; i < graph[u].size(); ++i) {
            int v = graph[u][i].first;
            int w = graph[u][i].second;

            if ((w + distance[u] < distance[v] || distance[v] == INF) && distance[u] != INF) {
                distance[v] = w + distance[u];
                if (!isEnqueued[v]) {
                    q.push(v);
                    isEnqueued[v] = true;
                } 
                count[v]++;
                if (count[v] > graph.size()) {
                    return std::vector<int>();
                }
            }
        }
    }

    return distance;
}

namespace BellmanFord {
    std::vector<std::vector<int>> shortest_path(const std::vector<std::vector<edge>>& graph) {
	   std::vector<std::vector<int>> distanceMatrix;
       std::vector<int> nodeArray;

	    for (unsigned int i = 0; i < graph.size(); ++i) {
            nodeArray = computeBellmanFord(graph, i);
            if (!nodeArray.size()) {
                return std::vector<std::vector<int>>();
            } else {
		        distanceMatrix.push_back(nodeArray);
            }
	    }

        return distanceMatrix;
    }
}
