#include <iostream>
#include <queue>
using namespace std;

int main() {
    // Define a priority queue of integers (default is max heap)
    priority_queue<int> pq;

    // Insert elements into the priority queue
    pq.push(30);
    pq.push(10);
    pq.push(50);
    pq.push(20);

    // Access the top element (highest priority)
    cout << "Top element: " << pq.top() << endl;

    // Remove the top element
    pq.pop();

    // Access the new top element
    cout << "Top element after pop: " << pq.top() << endl;

    // Check if priority queue is empty
    cout << "Is priority queue empty? " << (pq.empty() ? "Yes" : "No") << endl;

    // Size of priority queue
    cout << "Size of priority queue: " << pq.size() << endl;

    // Iterate through elements (note: priority_queue doesn't support direct iteration)
    // To access elements, we need to pop them one by one
    cout << "Elements in priority queue: ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    return 0;
}
