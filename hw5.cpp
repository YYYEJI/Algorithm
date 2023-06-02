/* 
이름: 송예지
학번: 22100396
컴파일: g++ -std=c++11 hw5.cpp

code: graph_const_7.cpp 
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int num_nodes = 8;

char graph[num_nodes][num_nodes] = {0,};
char transpose[num_nodes][num_nodes] = {0,};

void Read_from_file(char graph[][num_nodes]) {
    ifstream inputFile("hw5_data.txt");
    for (int i = 0; i < num_nodes+1; i++) {
        for (int j = 0; j < num_nodes+1; j++) {
            if(i == 0 && j == 0) continue;
            inputFile >> graph[i][j];
            // cout << graph[i][j] << '\t';
        }
        // cout << endl;
    }
    // cout << endl;
}

void PrintAdjacencyList(const char graph[][num_nodes]) {
    for (int i = 0; i < num_nodes; i++) {
        if (i == 0) continue;
        cout << (char)('A' + i-1) << " ---> ";
        for (int j = 0; j < num_nodes+1; j++) {
            if (graph[i][j] == '1') {
                cout << (char)('A' + j-1) << " ";
            }
        }
        cout << endl;
    }
}


int main() {
    Read_from_file(graph);

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            transpose[j][i] = graph[i][j];
        }
    }

    // Adjacency array of the graph
    cout << "< Array of adjacency list of graph >\n ";
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    PrintAdjacencyList(graph);

    // Adjacency array of the transpose graph
    cout << "\n\n< Array of adjacency list of transpose graph >\n ";
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            cout << transpose[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    PrintAdjacencyList(transpose);

    return 0;
}
