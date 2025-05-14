#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include "Graph.h"
#include "Dijkstra.h"
#include "httplib.h"

int main() {
    std::string stationsFile = "../data/stations.csv";
    std::string routesFile = "../data/routes.csv";

    // Load station ID to name map
    std::unordered_map<int, std::string> idToName;
    std::ifstream stationFile(stationsFile);
    if (!stationFile.is_open()) {
        std::cerr << "Failed to open stations.csv\n";
        return 1;
    }

    std::string line;
    while (getline(stationFile, line)) {
        std::stringstream ss(line);
        std::string idStr, name;
        getline(ss, idStr, ',');
        getline(ss, name);
        if (!idStr.empty() && !name.empty()) {
            idToName[std::stoi(idStr)] = name;
        }
    }

    // Initialize graph
    Graph transportGraph(stationsFile, routesFile);

    // Setup HTTP server
    httplib::Server svr;

    // Serve static files from frontend directory
    svr.set_mount_point("/", "../frontend");

    // Route finding endpoint
    svr.Get("/find-route", [&](const httplib::Request& req, httplib::Response& res) {
        auto source = req.get_param_value("source");
        auto destination = req.get_param_value("destination");

        if (source.empty() || destination.empty()) {
            res.status = 400;
            res.set_content("Missing parameters", "text/plain");
            return;
        }

        int sourceId = std::stoi(source);
        int destId = std::stoi(destination);

        Dijkstra dijkstra(transportGraph);
        dijkstra.computeShortestPaths(sourceId);
        
        std::vector<int> path = dijkstra.getPathTo(destId);
        int distance = dijkstra.getDistanceTo(destId);

        // Create JSON response
        std::stringstream json;
        json << "{";
        json << "\"source\":" << sourceId << ",";
        json << "\"source_name\":\"" << idToName[sourceId] << "\",";
        json << "\"destination\":" << destId << ",";
        json << "\"destination_name\":\"" << idToName[destId] << "\",";
        json << "\"distance\":" << distance << ",";
        
        // Add path
        json << "\"path\":[";
        for (size_t i = 0; i < path.size(); ++i) {
            json << path[i];
            if (i < path.size() - 1) json << ",";
        }
        json << "],";

        // Add path names
        json << "\"path_names\":[";
        for (size_t i = 0; i < path.size(); ++i) {
            json << "\"" << idToName[path[i]] << "\"";
            if (i < path.size() - 1) json << ",";
        }
        json << "]}";

        res.set_content(json.str(), "application/json");
    });

    // Start server
    std::cout << "Server started on http://localhost:8080" << std::endl;
    svr.listen("localhost", 8080);

    return 0;
}