#include "FloydWarshall.h"
#include <limits>

FloydWarshall::FloydWarshall(Graph& g) : graph(g) {}

void FloydWarshall::computeAllPairsShortestPaths() {
    int n = graph.getNumberOfStations();
    auto& adj = graph.getAdjacencyMatrix();

    dist = adj;  // Copy initial weights
    next = std::vector<std::vector<int>>(n, std::vector<int>(n, -1));

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] != std::numeric_limits<int>::max()) {
                next[u][v] = v;
            }
        }
        dist[u][u] = 0;
        next[u][u] = u;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] == std::numeric_limits<int>::max() || dist[k][j] == std::numeric_limits<int>::max()) {
                    continue;
                }
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

int FloydWarshall::getDistance(int u, int v) const {
    return dist[u][v];
}

std::vector<int> FloydWarshall::getPath(int u, int v) const {
    std::vector<int> path;
    if (next[u][v] == -1) return path;

    while (u != v) {
        path.push_back(u);
        u = next[u][v];
    }
    path.push_back(v);
    return path;
}
