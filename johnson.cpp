// Banu Miruna-Elena, 321CA, November 2019
#include "algo.h"
#include <iostream>


std::vector<std::vector<int>> computeJohnson(const std::vector<std::vector<edge>>& graph) {
	std::vector<std::vector<edge>> g = graph;

	g.resize(graph.size() + 1);

	for (unsigned int i = 0; i < graph.size(); ++i) {
		edge e;
		e.first = i;
		e.second = 0;
		g[g.size() - 1].push_back(e); 
	}


	std::vector<int> vWeight = computeBellmanFord(g, g.size() - 1);

	if (!vWeight.size()) {
		return std::vector<std::vector<int>>();
	}

	for (unsigned int i = 0; i < g.size(); ++i) {
        for (unsigned int j = 0; j < g[i].size(); ++j) {
            g[i][j].second += (vWeight[i] - vWeight[g[i][j].first]);
        }
    }

	g.resize(graph.size());

	std::vector<std::vector<int>> finalPaths = Dijkstra::shortest_path(g);

	for (unsigned int i = 0; i < g.size(); ++i) {
        for (unsigned int j = 0; j < g[i].size(); ++j) {
        	if (finalPaths[i][j] != INF) {
            	finalPaths[i][j] -= (vWeight[i] - vWeight[g[i][j].first]);
        	}
        }
    }

	return finalPaths;
}

namespace Johnson {
	std::vector<std::vector<int>> shortest_path(const std::vector<std::vector<edge>>& graph) {
		return computeJohnson(graph);
	}
}
