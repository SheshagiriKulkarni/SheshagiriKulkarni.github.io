#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Function to compute Levenshtein Distance between two strings
int levenshteinDistance(string word1, string word2) {
    int m = word1.length();
    int n = word2.length();

    // Create a 2D array to store distances
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Initialize base cases
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i; // Deletion cost
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j; // Insertion cost
    }

    // Fill the DP table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No operation needed
            } else {
                dp[i][j] = 1 + min({ dp[i - 1][j],     // Deletion
                                     dp[i][j - 1],     // Insertion
                                     dp[i - 1][j - 1]  // Substitution
                                   });
            }
        }
    }

    // The final cell contains the Levenshtein Distance
    return dp[m][n];
}

// Example usage
int main() {
    string word1 = "kitten";
    string word2 = "sitting";

    int distance = levenshteinDistance(word1, word2);

    cout << "Levenshtein Distance between '" << word1 << "' and '" << word2 << "' is: " << distance << endl;

    return 0;
}
