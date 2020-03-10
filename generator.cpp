// Banu Miruna-Elena, 321CA, November 2019
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "algo.h"
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;

#define MAX_V 1000
#define MAX_E 10000
#define MAX_WEIGHT 2000

void generateGraph (string inputFile) {
	ofstream outFile(inputFile);
	int V, E;

	V = 5 + rand() % MAX_V;
	E = (3 + rand() % MAX_E) % (V * V);
	outFile << V << " " << E << '\n';

	for (int i = 0; i < E; ++i) {
		int src, dest, weight;
		src = rand() % V + 1;
		dest = rand() % V + 1;
		weight = rand() % MAX_WEIGHT;
		outFile << src << " " << dest << " " << weight << '\n';
	}

	outFile.close();
}

std::vector<std::vector<int>> testResult (string inputFile,
	std::vector<std::vector<int>> (*testFunction)(const std::vector<std::vector<edge>>& graph)) {
		int V, E, src, dest, w;

		ifstream in(inputFile);
		in >> V >> E;
		std::vector<std::vector<edge>> graph(V);

		for (int i = 0; i < E; ++i) {
			in >> src >> dest >> w;
			edge e;
			e.first = dest - 1;
			e.second = w;
			graph[src - 1].push_back(e); 
		}

		in.close();
		return testFunction(graph);
}

void printMatrix(std::vector<std::vector<int>> mat, string outFile) {
	ofstream out(outFile);
	for (unsigned int i = 0; i < mat.size(); ++i) {
		for (unsigned int j = 0; j < mat[i].size(); ++j) {
			out << mat[i][j] << " ";
		}
		out << '\n';
	}
	out<<'\n';
	out.close();
}

void checkResult (string inputFile, string outFile) {

	ofstream out(outFile);

	auto start = high_resolution_clock::now();
	std::cout << "Running test " << inputFile << "\tDijkstra\t";
	std::vector<std::vector<int>> dijkstraRes = testResult(inputFile, Dijkstra::shortest_path);
	auto stop = high_resolution_clock::now(); 

    auto duration = duration_cast<microseconds>(stop - start); 
    std::cout << "\n Dijsktra duration in microseconds: " << duration.count() << "\n";

	auto startb = high_resolution_clock::now();
	std::cout << "\tBellmanFord\t";
	std::vector<std::vector<int>> bellmanFordRes = testResult(inputFile, BellmanFord::shortest_path);
	auto stopb = high_resolution_clock::now(); 

    auto durationb = duration_cast<microseconds>(stopb - startb); 
    std::cout << "\n Bellman-Ford duration in microseconds: " << durationb.count() << "\n";

	auto startj = high_resolution_clock::now();
	std::cout << "\tJohnson\t";
	std::vector<std::vector<int>> johnsonRes = testResult(inputFile, Johnson::shortest_path);
	auto stopj = high_resolution_clock::now(); 

    auto durationj = duration_cast<microseconds>(stopj - startj); 
    std::cout << "\n Johnson duration in microseconds: " << durationj.count() << "\n";

	bool compute = true;

	if (!dijkstraRes.size()) {
		out << "Negative weight graph, cannot compute Dijkstra.\n";
		compute = false;
	}

	if (!bellmanFordRes.size()) {
		out << "Negative weight cycle, cannot compute Bellman-Ford.\n";
		compute = false;
	}

	if (!johnsonRes.size()) {
		out << "Negative weight cycle, cannot compute Johnson.\n";
		compute = false;
	}

	if (compute) {
		printMatrix(johnsonRes, outFile);
	}

	bool ok = dijkstraRes == bellmanFordRes && bellmanFordRes == johnsonRes;

	if (ok && compute) {
		std::cout << "Passed!\n";
	} else {
		std::cout << "Failed!\n";
	}

	out.close();

}

int main () {
	srand(time(NULL));


	// Test general tests
	for (int i = 0; i < 10; ++i) {
		string inName = "./in/final_test" + to_string(i) + ".in";
		string outName = "./out/final_test" + to_string(i) + ".out";
		generateGraph(inName);
		checkResult(inName, outName);
	}

	// Test edge cases
	for (int i = 0; i < 2; ++i) {
		string inName = "./other_tests/in/test" + to_string(i) + ".in";
		string outName = "./other_tests/out/test" + to_string(i) + ".out";
		checkResult(inName, outName);
	}

	return 0;
}