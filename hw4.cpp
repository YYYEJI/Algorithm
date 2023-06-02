/* 
// 22100396 송예지 
// https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
// https://foxtrotin.tistory.com/91
// https://velog.io/@jinh2352/01-%EB%B0%B0%EB%82%AD%EB%AC%B8%EC%A0%9CDP-vs-%EB%B6%84%ED%95%A0%EA%B0%80%EB%8A%A5-%EB%B0%B0%EB%82%AD%EB%AC%B8%EC%A0%9C%EA%B7%B8%EB%A6%AC%EB%94%94
// https://velog.io/@blacklandbird/%EB%83%85%EC%83%89-%EB%AC%B8%EC%A0%9C
// https://jja2han.tistory.com/22
// https://boomrabbit.tistory.com/7
// https://sepang2.tistory.com/40
// 강의 slide, Knapsack Problem p.17
// Hyperscale AI ChatGPT
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip> // std::setprecision
using namespace std;

struct Item {
    int benefit;
    int weight;
    Item(int b, int w) {
        benefit = b;
        weight = w;
    }
};


struct Node {
    int level;
    int benefit;
    int weight;
    int bound;

    Node(int l, int b, int w, int bound) : level(l), benefit(b), weight(w), bound(bound) {}

    bool operator<(const Node& other) const {
        return bound < other.bound;
    }
};


int rand_num(int a, int b);
int brute_force(vector<Item>& items, int W, int idx);
double greedy(vector<Item>& items, int W);
int dynamic_programming(vector<Item>& items, int W);
int branch_and_bound(vector<Item>& items, int W);
int bound(Node node, vector<Item>& items, int W);


int main() {
    srand(100);
    int n = 1000;
    int W = n*25;
    vector<Item> items;

    cout << "[1] Brute force" << endl;
    int brute[3] = {11, 21, 31};
    cout << "-------------------------------------------------------------------------------"<<endl;
    cout << "|   Number of Items  |   Processing in milliseconds  /  Maximum benefit value   |"<< endl;
    cout << "-------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i<3; i++) {
        for(int j = 0; j<brute[i]; j++) {
            int benefit = rand_num(1, 500);
            int weight = rand_num(1, 100);
            items.push_back(Item(benefit, weight));
        }
        auto start_time_brute = chrono::high_resolution_clock::now();
        int max_benefit = brute_force(items, W, 0);
        auto end_time_brute = chrono::high_resolution_clock::now();
        double duration_brute = chrono::duration_cast<chrono::microseconds>(end_time_brute - start_time_brute).count()/1000000.0;
        cout << "|         "<<  brute[i] << "         |     " << fixed << setprecision(2) << "          " << duration_brute << "            /           " << setw(5) << max_benefit <<  "          |"<< endl;
        items.clear();
    }
    cout << "-------------------------------------------------------------------------------"<<endl;

    cout << endl <<endl;
    cout << "[2] Greedy / D.P. / B.&B." << endl;
    int GDB[4] = {10, 100, 1000, 10000};
    cout << "---------------------------------------------------------------------------------"<<endl;
    cout << "|   Number of Items  |    Processing in milliseconds / Maximum benefit value     |"<< endl;
    cout << "                      ------------------------------------------------------------"<<endl;
    cout << "|                    |      Greedy      |       D.P.       |        B. & B.      |"<< endl;
    cout << "----------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<GDB[i]; j++) {
            int benefit = rand_num(1, 500);
            int weight = rand_num(1, 100);
            items.push_back(Item(benefit, weight));
        }
        auto start_time_greedy = chrono::high_resolution_clock::now();
        int max_benefit_greedy = greedy(items, W);
        auto end_time_greedy = chrono::high_resolution_clock::now();
        double duration_greedy = chrono::duration_cast<chrono::microseconds>(end_time_greedy - start_time_greedy).count()/1000000.0;

        cout << "|       "<<  setw(5) << GDB[i] << "        |  " <<  setw(6) << max_benefit_greedy << " / " << duration_greedy;

        auto start_time_dp = chrono::high_resolution_clock::now();
        int max_benefit_dp = dynamic_programming(items, W);
        auto end_time_dp = chrono::high_resolution_clock::now();
        double duration_dp = chrono::duration_cast<chrono::microseconds>(end_time_dp - start_time_dp).count()/1000000.0;

        cout << "   |   " <<  setw(6) << max_benefit_dp << " / " << duration_dp;

        auto start_time_bb = chrono::high_resolution_clock::now();
        int max_benefit_bb = branch_and_bound(items, W);
        auto end_time_bb = chrono::high_resolution_clock::now();
        double duration_bb = chrono::duration_cast<chrono::microseconds>(end_time_bb - start_time_bb).count() / 1000000.0;

        cout << "   |   " <<  setw(6) << max_benefit_bb << " / " << duration_bb << "    |" << endl;

        items.clear();
    }
    cout << "----------------------------------------------------------------------------------"<<endl;

    return 0;
}

int rand_num(int a, int b) {
    return a + rand() % (b - a + 1);
}

// Brute Force 
int brute_force(vector<Item>& items, int W, int idx) {
    if (W < 0) {
        return -1;
    }
    if (idx == items.size()) {
        return 0;
    }
    int res = brute_force(items, W - items[idx].weight, idx + 1);
    if (res != -1) {
        res += items[idx].benefit;
    }
    return max(res, brute_force(items, W, idx + 1));
}

// Greedy
double greedy(vector<Item>& items, int W) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.benefit * 1.0 / a.weight > b.benefit * 1.0 / b.weight;
    });

    double value = 0.0;
    for (const auto& item : items) {
        if (item.weight <= W) {
            W -= item.weight;
            value += item.benefit;
        } else {
            value += (W * 1.0 / item.weight) * item.benefit;
            break;
        }
    }
    return value;
}

// Dynamic Programming 
int dynamic_programming(vector<Item>& items, int W) {
    vector<vector<int>> dp(items.size() + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= items.size(); i++) {
        for (int j = 1; j <= W; j++) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].benefit);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[items.size()][W];
}


// Branch and Bound
int branch_and_bound(vector<Item>& items, int W) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.benefit / (double) a.weight > b.benefit / (double) b.weight;
    });

    int max_benefit = 0;
    priority_queue<Node> pq;

    Node root(-1, 0, 0, bound(Node(0, 0, 0, 0), items, W));
    pq.push(root);

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.bound <= max_benefit) {
            continue;
        }

        if (node.level == items.size() - 1) {
            if (node.benefit > max_benefit) {
                max_benefit = node.benefit;
            }
            continue;
        }

        Node left_child = Node(node.level + 1, node.benefit, node.weight, bound(Node(node.level + 1, node.benefit, node.weight, node.bound), items, W));
        if (left_child.bound > max_benefit) {
            pq.push(left_child);
        }

        Node right_child = Node(node.level + 1, node.benefit + items[node.level + 1].benefit, node.weight + items[node.level + 1].weight, bound(Node(node.level + 1, node.benefit + items[node.level + 1].benefit, node.weight + items[node.level + 1].weight, node.bound), items, W));
        if (right_child.bound > max_benefit) {
            pq.push(right_child);
        }
    }

    return max_benefit;
}
int bound(Node node, vector<Item>& items, int W) {
    int benefit = node.benefit;
    int weight = node.weight;
    int level = node.level;

    if (weight > W) {
        return 0;
    }

    for (int i = level; i < items.size(); i++) {
        if (weight + items[i].weight <= W) {
            benefit += items[i].benefit;
            weight += items[i].weight;
        } else {
            benefit += (W - weight) * items[i].benefit / (double) items[i].weight;
            break;
        }
    }

    return benefit;
}