#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Structure for a node in the K-D tree
struct Node {
    vector<int> point;  // Point coordinates
    Node* left;         // Pointer to left subtree
    Node* right;        // Pointer to right subtree

    Node(vector<int> p) : point(p), left(nullptr), right(nullptr) {}
};

// Function to compare points based on current depth
bool comparePoints(const vector<int>& point1, const vector<int>& point2, int depth) {
    int dim = point1.size();
    int cd = depth % dim;  // Current dimension

    return point1[cd] < point2[cd];
}

// Function to construct K-D tree recursively
Node* constructKdTree(vector<vector<int>>& points, int depth) {
    if (points.empty()) return nullptr;

    int dim = points[0].size();
    int median = points.size() / 2;

    // Sort points based on current depth dimension
    nth_element(points.begin(), points.begin() + median, points.end(), [depth](const vector<int>& point1, const vector<int>& point2) {
        return comparePoints(point1, point2, depth);
    });

    Node* root = new Node(points[median]);
    vector<vector<int>> leftPoints(points.begin(), points.begin() + median);
    vector<vector<int>> rightPoints(points.begin() + median + 1, points.end());

    root->left = constructKdTree(leftPoints, depth + 1);
    root->right = constructKdTree(rightPoints, depth + 1);

    return root;
}

// Function to calculate squared distance between two points
int squaredDistance(const vector<int>& point1, const vector<int>& point2) {
    int dist = 0;
    for (int i = 0; i < point1.size(); ++i) {
        dist += pow(point1[i] - point2[i], 2);
    }
    return dist;
}

// Function to find nearest neighbor in K-D tree
vector<int> nearestNeighbor(Node* root, const vector<int>& queryPoint, int depth) {
    if (root == nullptr) return {};

    int dim = queryPoint.size();
    int cd = depth % dim;  // Current dimension

    vector<int> nearest = root->point;

    if (queryPoint[cd] < root->point[cd]) {
        vector<int> temp = nearestNeighbor(root->left, queryPoint, depth + 1);
        if (!temp.empty() && squaredDistance(queryPoint, temp) < squaredDistance(queryPoint, nearest)) {
            nearest = temp;
        }
        temp = nearestNeighbor(root->right, queryPoint, depth + 1);
        if (!temp.empty() && squaredDistance(queryPoint, temp) < squaredDistance(queryPoint, nearest)) {
            nearest = temp;
        }
    } else {
        vector<int> temp = nearestNeighbor(root->right, queryPoint, depth + 1);
        if (!temp.empty() && squaredDistance(queryPoint, temp) < squaredDistance(queryPoint, nearest)) {
            nearest = temp;
        }
        temp = nearestNeighbor(root->left, queryPoint, depth + 1);
        if (!temp.empty() && squaredDistance(queryPoint, temp) < squaredDistance(queryPoint, nearest)) {
            nearest = temp;
        }
    }

    return nearest;
}

// Function to print a point
void printPoint(const vector<int>& point) {
    cout << "(";
    for (int i = 0; i < point.size(); ++i) {
        cout << point[i];
        if (i < point.size() - 1) cout << ", ";
    }
    cout << ")";
}

// Example usage
int main() {
    vector<vector<int>> points = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};
    Node* root = constructKdTree(points, 0);

    vector<int> queryPoint = {7, 2};
    vector<int> nearest = nearestNeighbor(root, queryPoint, 0);

    cout << "Nearest neighbor to ";
    printPoint(queryPoint);
    cout << " is ";
    printPoint(nearest);
    cout << endl;

    return 0;
}
