#include <iostream>
#include <string>
#include <algorithm>
// Function to create the bad character heuristic table for the Horspool algorithm
void preprocessBadCharacter(const std::string &pattern, int badChar[]) {
    int m = pattern.size();  // Length of the pattern
    // Initialize all values in badchar[] as length of pattern (m)
    for (int i = 0; i < 256; ++i) {
        badChar[i] = m;
    }
    // The table is filled by the shift value based on the last occurrence of each character in the pattern
    for (int i = 0; i < m - 1; ++i) {
        badChar[(int)pattern[i]] = m - i - 1; // badChar[‘A’] = m-0-1 = 3 
	//It use the ASCII value of ‘A’ is 65, so badChar[65] = 3
	// so for situations where the character is repeated in the pattern like ‘B’ it will update the value where we will use the value of the last occurrence of repeated character
	//The value of the last character in the pattern will be the same as other characters that is not present in the pattern which is the length of pattern (m)
    }
}
// Boyer-Moore-Horspool search function
void boyerMooreHorspoolSearch(const std::string &text, const std::string &pattern) {
    int n = text.size();  // Length of the text
    int m = pattern.size();  // Length of the pattern
    int badChar[256];  // Initialize bad character heuristic table
    // Create the bad character heuristic table for the pattern
    preprocessBadCharacter(pattern, badChar);
    int s = 0; // s is the shift of the pattern with respect to the text
    // Continue searching until the pattern can fit within the remaining text
    while (s <= (n - m)) {
        int j = m - 1; // j is the index for comparing characters from the end of the pattern towards the beginning.
// comparison happens in the nested loop below, it will loop until mismatch to compare characters of the pattern and the text from right to left. the j will be reduce
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }
// If the pattern is present at the current shift, then j will become -1 after the above loop
// the if will handle the case is pattern found in text
// the else will handle the case where mismatch occur
        if (j < 0) {
            std::cout << "Pattern occurs at shift = " << s << std::endl;
          // Move the pattern to the next possible alignment in the text to find other possible occurrences of pattern in text
            s += (s + m < n) ? badChar[(int)text[s + m]] : 1;
// the (s+m<n) will check if there are any characters left in the text.
//if true it will shift based on the character shift value.
//if false, we shift the pattern by 1 to exit the loop
        } else {
            // Shift the pattern based on the bad character heuristic value for text[s + j]
            s += badChar[(int)text[s + j]];
        }
    }
}
int main() {
    std::string text = "ABABBABBCAB";
    std::string pattern = "ABBC";
    boyerMooreHorspoolSearch(text, pattern);  // Perform pattern search
    return 0;  // Exit the program
}

