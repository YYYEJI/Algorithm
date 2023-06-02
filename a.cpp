#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#define INF std::numeric_limits<int>::max()

void readInputFile(const std::string& filename, std::vector<std::vector<int>>& graph) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::vector<int> row;
            int value;
            while (iss >> value) {
                if (value == INF) {
                    row.push_back(std::numeric_limits<int>::max());
                } else {
                    row.push_back(value);
                }
            }
            graph.push_back(row);
        }
        inputFile.close();
    } else {
        std::cout << "Failed to open the input file." << std::endl;
    }
}
void dijkstra(const std::vector<std::vector<int>>& graph, int source, std::vector<int>& distances) {
    int numVertices = graph.size();
    std::vector<bool> visited(numVertices, false);
    distances.assign(numVertices, INF);
    distances[source] = 0;
    
    for (int i = 0; i < numVertices - 1; ++i) {
        int minDist = INF;
        int minIndex = -1;
        
        // Find the vertex with the minimum distance
        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && distances[j] < minDist) {
                minDist = distances[j];
                minIndex = j;
            }
        }
        
        // Mark the selected vertex as visited
        visited[minIndex] = true;
        
        // Update the distances of the adjacent vertices
        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && graph[minIndex][j] != INF && distances[minIndex] != INF &&
                distances[minIndex] + graph[minIndex][j] < distances[j]) {
                distances[j] = distances[minIndex] + graph[minIndex][j];
            }
        }
    }
}

void printShortestDistances(const std::vector<std::vector<int>>& graph) {
    int numVertices = graph.size();
    for (int i = 0; i < numVertices; ++i) {
        std::vector<int> distances;
        dijkstra(graph, i, distances);
        
        std::cout << "The following are shortest distances between cities with Dijkstra's algorithm:\n";
        for (int j = 0; j < numVertices; ++j) {
            if (distances[j] == std::numeric_limits<int>::max()) {
                std::cout << "INF\t";
            } else {
                std::cout << distances[j] << "\t";
            }
        }
        std::cout << "\n";
    }
}



int main() {
    std::string filename = "hw6.txt";
    std::vector<std::vector<int>> graph;
    
    readInputFile(filename, graph);
    
    printShortestDistances(graph);
    
    return 0;
}
