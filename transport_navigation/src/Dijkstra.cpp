#include "Dijkstra.h"
#include <queue>
#include <utility> // for std::pair

Dijkstra::Dijkstra(Graph& g) : graph(g) {}

void Dijkstra::computeShortestPaths(int src) {
    int n = graph.getNumberOfStations();
    distances = std::vector<int>(n, std::numeric_limits<int>::max());
    previous = std::vector<int>(n, -1);
    source = src;

    distances[src] = 0;
    using pii = std::pair<int, int>; // {distance, node}
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, src});

    auto& adj = graph.getAdjacencyMatrix();

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distances[u]) continue;

        for (int v = 0; v < n; ++v) {
            if (adj[u][v] != std::numeric_limits<int>::max()) {
                int newDist = dist + adj[u][v];
                if (newDist < distances[v]) {
                    distances[v] = newDist;
                    previous[v] = u;
                    pq.push({newDist, v});
                }
            }
        }
    }
}

int Dijkstra::getDistanceTo(int destination) const {
    return distances[destination];
}

std::vector<int> Dijkstra::getPathTo(int destination) const {
    std::vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.insert(path.begin(), at);
    }
    return path;
}
