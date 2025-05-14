#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>
#include <string>
#include <limits>

class Dijkstra {
public:
    // Constructor takes a reference to a Graph object
    Dijkstra(Graph& graph);

    // Finds shortest path from source index to all other nodes
    void computeShortestPaths(int source);

    // Returns the shortest distance to a specific destination
    int getDistanceTo(int destination) const;

    // Returns the actual path from source to destination
    std::vector<int> getPathTo(int destination) const;

private:
    Graph& graph;
    std::vector<int> distances;
    std::vector<int> previous;
    int source;
};

#endif // DIJKSTRA_H
