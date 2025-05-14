#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "Graph.h"
#include <vector>

class FloydWarshall {
public:
    // Constructor takes a Graph reference
    FloydWarshall(Graph& graph);

    // Compute all-pairs shortest paths
    void computeAllPairsShortestPaths();

    // Get shortest distance from u to v
    int getDistance(int u, int v) const;

    // Get path from u to v
    std::vector<int> getPath(int u, int v) const;

private:
    Graph& graph;
    std::vector<std::vector<int>> dist;
    std::vector<std::vector<int>> next;
};

#endif // FLOYD_WARSHALL_H
