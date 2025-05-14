#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Graph.h"
#include "Dijkstra.h"

using json = nlohmann::json;

int main() {
    std::string stationsFile = "data/stations.csv";
    std::string routesFile = "data/routes.csv";

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
        idToName[std::stoi(idStr)] = name;
    }

    // Initialize graph and algorithms
    Graph transportGraph(stationsFile, routesFile);
    Dijkstra dijkstra(transportGraph);

    int source = 0;       // Change or read from user
    int destination = 4;  // Change or read from user

    dijkstra.computeShortestPaths(source);
    std::vector<int> path = dijkstra.getPath(destination);
    int distance = dijkstra.getDistance(destination);

    if (path.empty()) {
        std::cerr << "No path found from " << source << " to " << destination << "\n";
        return 1;
    }

    // Convert path to station names
    std::vector<std::string> pathNames;
    for (int id : path) {
        if (idToName.count(id)) {
            pathNames.push_back(idToName[id]);
        } else {
            pathNames.push_back("Unknown");
        }
    }

    // Create JSON output
    json output;
    output["algorithm"] = "Dijkstra";
    output["source"] = source;
    output["source_name"] = idToName[source];
    output["destination"] = destination;
    output["destination_name"] = idToName[destination];
    output["distance"] = distance;
    output["path"] = path;
    output["path_names"] = pathNames;

    // Write to frontend/output.json
    std::ofstream file("../frontend/output.json");
    if (file.is_open()) {
        file << output.dump(4);
        file.close();
        std::cout << "output.json written successfully.\n";
    } else {
        std::cerr << "Failed to write output.json\n";
        return 1;
    }

    return 0;
}
