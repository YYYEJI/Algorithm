/* 
// 수업 시간 교수님 코드
ifstream inputFile("data.txt");
using loop 
    inputFile >> variable;
*/
#include <iostream>
#include <fstream>
using namespace std;
const int num_nodes = 5;

typedef struct h_node {
    int data;
    struct g_node * link;
} head_node;

int main() {
    int distance[num_nodes][num_nodes];
    ifstream inputFile("data.txt");
    for(int i = 0; i<num_nodes; i++) {
        for(int j = 0; j<num_nodes; j++) {
            inputFile >> distance[i][j];
            cout << distance[i][j] << "\t";
        }
        cout << endl;
    }
    cout<<endl;

    
}
