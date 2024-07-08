#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    // Declare an unordered_map with key as string and value as int
    unordered_map<string, int> hashMap;

    // Insert key-value pairs into the hash map
    hashMap["apple"] = 5;
    hashMap["banana"] = 10;
    hashMap["orange"] = 7;

    // Access elements
    cout << "Value of apple: " << hashMap["apple"] << endl;

    // Check if a key exists and retrieve its value
    string key = "banana";
    if (hashMap.find(key) != hashMap.end()) {
        cout << "Value of " << key << ": " << hashMap[key] << endl;
    } else {
        cout << key << " not found in hash map" << endl;
    }

    // Modify element value
    hashMap["orange"] = 8;
    cout << "Modified value of orange: " << hashMap["orange"] << endl;

    // Iterate over all key-value pairs
    cout << "All elements in hash map:" << endl;
    for (auto& pair : hashMap) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Remove an element
    string removeKey = "banana";
    if (hashMap.find(removeKey) != hashMap.end()) {
        hashMap.erase(removeKey);
        cout << "Removed " << removeKey << " from hash map" << endl;
    } else {
        cout << removeKey << " not found in hash map" << endl;
    }

    return 0;
}
