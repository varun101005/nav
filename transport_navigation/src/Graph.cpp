#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

Graph::Graph(const std::string& stationsFile, const std::string& routesFile) {
    // Reading stations.csv
    std::ifstream stationsFileStream(stationsFile);
    std::string line;
    while (std::getline(stationsFileStream, line)) {
        std::stringstream ss(line);
        std::string id, name;
        std::getline(ss, id, ',');
        std::getline(ss, name);
        stations.push_back(name);
    }
    stationsFileStream.close();

    // Initialize adjacency matrix
    int n = stations.size();
    adjacencyMatrix = std::vector<std::vector<int>>(n, std::vector<int>(n, std::numeric_limits<int>::max()));
    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i][i] = 0;
    }

    // Reading routes.csv
    std::ifstream routesFileStream(routesFile);
    while (std::getline(routesFileStream, line)) {
        std::stringstream ss(line);
        std::string source, destination, time;
        std::getline(ss, source, ',');
        std::getline(ss, destination, ',');
        std::getline(ss, time);
        
        int srcID = std::stoi(source);
        int destID = std::stoi(destination);
        int travelTime = std::stoi(time);
        
        adjacencyMatrix[srcID][destID] = travelTime;
        adjacencyMatrix[destID][srcID] = travelTime; // Bidirectional
    }
    routesFileStream.close();
}

void Graph::printGraph() {
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
            if (adjacencyMatrix[i][j] == std::numeric_limits<int>::max()) {
                std::cout << "INF ";
            } else {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}

int Graph::getNumberOfStations() {
    return stations.size();
}

std::vector<std::vector<int>>& Graph::getAdjacencyMatrix() {
    return adjacencyMatrix;
}
