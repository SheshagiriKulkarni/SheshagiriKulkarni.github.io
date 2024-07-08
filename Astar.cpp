#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

// Define a structure to represent a node in the graph
struct Node {
    int x, y;       // Coordinates of the node
    int g_cost;     // Cost from start to current node
    int f_cost;     // Total estimated cost of path through current node
    Node* parent;   // Parent node for tracing path

    Node(int x, int y, int g_cost, int f_cost, Node* parent = nullptr)
        : x(x), y(y), g_cost(g_cost), f_cost(f_cost), parent(parent) {}

    // Overloading the less than operator for priority queue
    bool operator<(const Node& other) const {
        return f_cost > other.f_cost; // Priority queue is a min-heap, so we use > for smallest f_cost
    }
};

// Function to calculate heuristic (Manhattan distance)
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// A* search algorithm function
void AStarSearch(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Priority queue for open set
    priority_queue<Node> open_set;

    // Start node
    Node start_node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));

    open_set.push(start_node);

    // Maps to track g_cost and f_cost of each node
    unordered_map<int, unordered_map<int, int>> g_cost_map;
    unordered_map<int, unordered_map<int, int>> f_cost_map;

    g_cost_map[start.first][start.second] = 0;
    f_cost_map[start.first][start.second] = start_node.f_cost;

    // Directions: right, left, down, up (4-connected grid)
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!open_set.empty()) {
        // Get the node with the lowest f_cost from the priority queue
        Node current = open_set.top();
        open_set.pop();

        // If goal node reached, print the path
        if (current.x == goal.first && current.y == goal.second) {
            vector<pair<int, int>> path;
            while (current.parent != nullptr) {
                path.push_back({current.x, current.y});
                current = *current.parent;
            }
            path.push_back({start.first, start.second});

            // Reverse the path to get from start to goal
            reverse(path.begin(), path.end());

            // Print the path
            cout << "Path Found:" << endl;
            for (auto& p : path) {
                cout << "(" << p.first << ", " << p.second << ") ";
            }
            cout << endl;
            return;
        }

        // Explore neighbors
        for (auto& dir : directions) {
            int new_x = current.x + dir.first;
            int new_y = current.y + dir.second;

            // Check if the neighbor is within bounds and is passable
            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && grid[new_x][new_y] == 0) {
                // Calculate tentative g_cost for the neighbor
                int tentative_g_cost = g_cost_map[current.x][current.y] + 1;

                // Check if this path to the neighbor is better
                if (!g_cost_map.count(new_x) || !g_cost_map[new_x].count(new_y) || tentative_g_cost < g_cost_map[new_x][new_y]) {
                    // Update g_cost and f_cost for the neighbor
                    int f_cost = tentative_g_cost + heuristic(new_x, new_y, goal.first, goal.second);
                    g_cost_map[new_x][new_y] = tentative_g_cost;
                    f_cost_map[new_x][new_y] = f_cost;

                    // Create the neighbor node and push it to the priority queue
                    Node* neighbor = new Node(new_x, new_y, tentative_g_cost, f_cost, &current);
                    open_set.push(*neighbor);
                }
            }
        }
    }

    // If no path found
    cout << "No path found!" << endl;
}

// Example usage
int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    AStarSearch(grid, start, goal);

    return 0;
}
