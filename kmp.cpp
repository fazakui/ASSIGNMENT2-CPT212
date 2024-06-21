#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to create the longest prefix suffix (LPS) array
void computeLPSArray(string pattern, vector<int> &lps) {
    int length = 0;  // Length of the previous longest prefix suffix
    int i = 1; // Start from the second character of the pattern 
    lps[0] = 0;  // lps[0] is always 0 since a single character prefix has no proper prefix

    // Loop to calculate lps[i] for i = 1 to pattern.size() - 1
    while (i < pattern.size()) {
       // If characters match, increment the length of the current LPS and assign it to lps[i]
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else if (length != 0) {  // If characters don't match
            length = lps[length - 1];
        } else { // If length is 0, there is no proper prefix suffix, set lps[i] to 0
            lps[i] = 0;
            i++;
        }
    }
}

// Function to implement Knuth-Morris-Pratt search algorithm
void KMPSearch(string text, string pattern) {
    int m = pattern.size();
    int n = text.size();

    // Create lps[] that will hold the longest prefix suffix values for pattern
    vector<int> lps(m);

    // Preprocess the pattern (calculate lps[] array)

    computeLPSArray(pattern, lps);
    
    int i = 0;  // index for text[]
    int j = 0;  // index for pattern[]
    while (i < n) {
        if (pattern[j] == text[i]) {
            // If characters match, move to the next character in both text and pattern
            i++;
            j++;
        }

        if (j == m) {
            // If j reaches the end of the pattern, we found a match
            cout << "Pattern occurs at index " << i - j << endl;
            // Update j to the previous longest prefix suffix to continue searching
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            // If characters don't match and i is within the text
            if (j != 0) {
                // If j is not at the beginning of the pattern, update j to lps[j - 1]
                j = lps[j - 1];
            } else {
                // If j is at the beginning of the pattern, move to next character in the text
                i++;
            }
        }
    }
}

int main() {
    string text = "ABABBABBCAB"; // The text to search within
    string pattern = "ABBC"; // The pattern to search for
    KMPSearch(text, pattern); // Perform KMP search
    return 0;
}
