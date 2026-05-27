#include <stdio.h>
#include <string.h>

// Function prototypes
void computeLPS(char *pattern, int m, int *lps);
int KMPSearch(char *pattern, char *text);
int NaiveSearch(char *pattern, char *text);
void compareAlgorithms(char *text, char *pattern);

int main() {
    char text[] = "ABABDABACDABABCABABABABCABABC";
    char pattern[] = "ABABCABAB";
    
    printf("=== STRING SEARCHING ALGORITHM COMPARISON ===\n\n");
    printf("Text: %s\n", text);
    printf("Pattern: %s\n\n", pattern);
    
    // Find using KMP
    int kmp_index = KMPSearch(pattern, text);
    printf("KMP Algorithm Result:\n");
    if (kmp_index != -1) {
        printf("  Pattern found at index: %d\n", kmp_index);
    } else {
        printf("  Pattern not found\n");
    }
    
    // Find using Naive
    int naive_index = NaiveSearch(pattern, text);
    printf("\nNaive Algorithm Result:\n");
    if (naive_index != -1) {
        printf("  Pattern found at index: %d\n", naive_index);
    } else {
        printf("  Pattern not found\n");
    }
    
    // Compare both algorithms
    printf("\n");
    compareAlgorithms(text, pattern);
    
    // Additional test cases
    printf("\n=== ADDITIONAL TEST CASES ===\n\n");
    
    char test1[] = "AAAAAAAB";
    char pat1[] = "AAAB";
    printf("Test 1: Text='%s', Pattern='%s'\n", test1, pat1);
    printf("  KMP: %d, Naive: %d\n", KMPSearch(pat1, test1), NaiveSearch(pat1, test1));
    
    char test2[] = "ABCDE"
;
    char pat2[] = "xyz";
    printf("Test 2: Text='%s', Pattern='%s'\n", test2, pat2);
    printf("  KMP: %d, Naive: %d\n", KMPSearch(pat2, test2), NaiveSearch(pat2, test2));
    
    return 0;
}

// Compute LPS (Longest Prefix Suffix) array
void computeLPS(char *pattern, int m, int *lps) {
    int length = 0;  // Length of previous longest prefix suffix
    int i = 1;
    
    lps[0] = 0;  // lps[0] is always 0
    
    // Loop calculates lps[i] for i = 1 to m-1
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Algorithm - Find first occurrence of pattern in text
int KMPSearch(char *pattern, char *text) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    if (m == 0) return 0;
    if (m > n) return -1;
    
    // Create LPS array
    int lps[m];
    computeLPS(pattern, m, lps);
    
    int i = 0;  // Index for text
    int j = 0;  // Index for pattern
    
    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        
        if (j == m) {
            // Pattern 