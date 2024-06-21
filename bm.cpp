#include <bits/stdc++.h>
using namespace std;


// defining the number of possible characters in the ASCII character set.
#define TOTAL_CHARACTERS 256


// The Bad Character Heuristic preprocessing function to store the last occurrence of each character in the pattern
// m is length of pattern
void badCharacterHeuristic(string s, int m, int badCharacter[TOTAL_CHARACTERS]) {
   // First initializing all occurrences of each character with -1
   for (int i = 0; i < TOTAL_CHARACTERS; i++){
     badCharacter[i] = -1;
   }
   // Loop and update bad character value with the index of last occurrence of a character in pattern
   for (int i = 0; i < m; i++){
    badCharacter[(int)s[i]] = i;
   }
}


//A Good Suffix Heuristic function to handle the strong suffix case.It prepare the shift array based of suffix matches
void preprocess_suffix(int m, int* borderPosition, int* shift, const string& pattern){
   int i = m, j = m + 1;//set i to the length of pattern, m and j to m+1
   borderPosition[i] = j; //set the initial border of the pattern 


   while (i > 0) {
   	while (j <= m && pattern[i - 1] != pattern[j - 1]) {
          if (shift[j] == 0)
              shift[j] = j - i;
          j = borderPosition[j];
       }
       i--;
       j--;
       borderPosition[i] = j;
    }
}


// a function to handle the prefix case. It will adjust the shifting based on the prefix matches
void preprocess_prefix(int m, int* borderPosition, int* shift) {
   //use the borderPosition array to update the shift value
   int j = borderPosition[0];
   for (int i = 0; i <= m; i++) {
      if (shift[i] == 0)
          shift[i] = j;
      if (i == j)
          j = borderPosition[j];
   }
}


// A function that searches the string and returns the occurrence.
void BoyerMooreAlgorithm(string text, string pattern) {
   int m = pattern.size(); // length of the pattern
   int n = text.size();    //length of the text 
   
   //initialize array for badCharacter, borderPosition and shift
   int badCharacter[TOTAL_CHARACTERS];
   int* borderPosition = new int[m + 1];
   int* shift = new int[m + 1];


   // Initializing all occurrences of the shift to 0
   for (int i = 0; i < m + 1; i++)
        shift[i] = 0;


    // Preprocessing the bad character heuristic
    badCharacterHeuristic(pattern, m, badCharacter);


    // Preprocessing the good suffix heuristic
    preprocess_suffix(m, borderPosition, shift, pattern);
    preprocess_prefix(m, borderPosition, shift);


    
    int s = 0;  // s is the shift of the pattern
    //outer loop will continue looping as long as the pattern aligned with the remaining part of the text
    while (s <= n - m) {
    	int j = m - 1;
      //check for the matching character from right to left
      while (j >= 0 && pattern[j] == text[s + j])
      j--;
      //if a complete match is found, the shift is updated based on the good suffix heuristic.
      if (j < 0) {
          cout << "Pattern found at index " << s << endl;
          s += shift[0];
      } 
      //if mismatch occurs, the shift is updated based on the maximum of the good suffix and bad character heuristics.
      else {
         // Calculate the shift based on both heuristics
         // Shift based on bad character heuristic
         int badCharShift = j - badCharacter[(int)text[s + j]];  
         // Shift based on good suffix heuristic
         int goodSuffixShift = shift[j + 1];  
         //update the position in the text where the pattern is compared by adding the calculated maximum shift to ensure it shifted optimally in text using both approaches
         s += max(1, max(goodSuffixShift, badCharShift));
      }
    }
    //clean up dynamic memory
    delete[] borderPosition;
    delete[] shift;
}


int main() {
string text = "ABABBABBCAB";
string pattern = "ABBC";


BoyerMooreAlgorithm(text, pattern);//function call for the BoyerMooreAlgorithm


return 0;
}
