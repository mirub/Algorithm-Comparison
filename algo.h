#ifndef ALGO_H
#define ALGO_H

#include <vector>
#define INF -1
#define INF2 0x4e4e4e4e
#include <iostream>
#include <fstream>

typedef std::pair<int, int> edge;

/**
 * For a given input graph T, computes the distance from every node to every other node in the graph.
 *
 * @graph: The graph is represented using adjacency lists (graph[i] - gives you the neighbours of node i) *
 * @returns: The adjacency matrix with the minimum distances between every node. If there is no way
 *           reach node j from i, store -1 in the matrix. (print it as "inf" in the tests)
 */

std::vector<int> computeBellmanFord(const std::vector<std::vector<edge>>& graph, int node);

namespace Dijkstra {
	std::vector<std::vector<int>> shortest_path(const std::vector<std::vector<edge>>& graph);
}

namespace BellmanFord {
	std::vector<std::vector<int>> shortest_path(const std::vector<std::vector<edge>>& graph);
}

namespace Johnson {
	std::vector<std::vector<int>> shortest_path(const std::vector<std::vector<edge>>& graph);
}

std::vector<std::vector<int>> shortest_path_all(const std::vector<std::vector<edge>>& graph);

#endif
