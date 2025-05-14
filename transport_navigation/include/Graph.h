#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

class Graph {
public:
    // Constructor to initialize the graph with station and route data
    Graph(const std::string& stationsFile, const std::string& routesFile);

    // Method to print the graph (for debugging)
    void printGraph();

    // Getter for number of stations (nodes)
    int getNumberOfStations();

    // Getter for the adjacency matrix (graph edges and weights)
    std::vector<std::vector<int>>& getAdjacencyMatrix();

private:
    std::vector<std::string> stations;  // Station names
    std::vector<std::vector<int>> adjacencyMatrix;  // Adjacency matrix (edges and weights)
};

#endif  // GRAPH_H

