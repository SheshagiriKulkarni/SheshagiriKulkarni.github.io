#include <iostream>
#include <vector>
using namespace std;

// Structure to represent a subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Class for Union-Find (Disjoint Set)
class UnionFind {
private:
    vector<Subset> subsets;

public:
    // Constructor to create Union-Find data structure
    UnionFind(int n) {
        subsets.resize(n);
        // Initialize each subset with itself as parent and rank 0
        for (int i = 0; i < n; ++i) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }
    }

    // Find operation with path compression
    int find(int i) {
        // Path compression
        if (subsets[i].parent != i) {
            subsets[i].parent = find(subsets[i].parent);
        }
        return subsets[i].parent;
    }

    // Union operation by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // Union by rank
        if (subsets[rootX].rank < subsets[rootY].rank) {
            subsets[rootX].parent = rootY;
        } else if (subsets[rootX].rank > subsets[rootY].rank) {
            subsets[rootY].parent = rootX;
        } else {
            subsets[rootY].parent = rootX;
            subsets[rootX].rank++;
        }
    }

    // Utility function to print all subsets
    void printSets(int n) {
        cout << "Subset elements: ";
        for (int i = 0; i < n; i++) {
            cout << i << ":" << find(i) << " ";
        }
        cout << endl;
    }
};

// Example usage
int main() {
    int n = 5;
    UnionFind uf(n);

    // Perform union operations
    uf.unionSets(0, 2);
    uf.unionSets(4, 2);
    uf.unionSets(3, 1);

    // Print all subsets after union operations
    uf.printSets(n);

    // Find operations
    cout << "Find(4): " << uf.find(4) << endl;
    cout << "Find(3): " << uf.find(3) << endl;

    return 0;
}
