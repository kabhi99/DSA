# **STRING PATTERNS - COMPLETE GUIDE**

Master string manipulation, palindromes, pattern matching & parsing!

### **TABLE OF CONTENTS**

PART 1: Core Concepts & Golden Rules
PART 2: Pattern Recognition Guide

PART 3: Pattern 1 - String Reversal / Manipulation
- Reverse Words in a String (LC 151) 
- Count and Say (LC 38)
- Longest Common Prefix (LC 14)

PART 4: Pattern 2 - Palindrome Techniques
- Longest Palindromic Substring (LC 5) 
- Minimum Insertions to Make String Palindrome (LC 1312) 

PART 5: Pattern 3 - Pattern Matching Algorithms
- KMP Algorithm / strStr (LC 28) 
- Rabin-Karp Algorithm
- Z-Function Algorithm
- Repeated DNA Sequences (LC 187)

PART 6: Pattern 4 - String Parsing / Conversion
- Roman to Integer (LC 13)
- Integer to Roman (LC 12)
- String to Integer - atoi (LC 8) 
- Compare Version Numbers (LC 165)

PART 7: Interview Cheat Codes
PART 8: Quick Revision Table
PART 9: Complete Problem List by Category
PART 10: Master Problem Mapping Table

## **PART 1: CORE CONCEPTS & GOLDEN RULES**

### ** WHEN TO USE STRING-SPECIFIC TECHNIQUES?**

**STRONG SIGNALS:**

 Reverse, rotate, or rearrange characters/words
 Check or find palindromes
 Search for a pattern/substring in text
 Parse strings into numbers or vice versa
 Compare strings character by character
 Prefix/suffix matching

**KEYWORDS TO WATCH FOR:**

- "reverse", "palindrome"
- "pattern matching", "find substring"
- "convert", "parse", "atoi"
- "common prefix/suffix"
- "anagram" > See Hashmap Patterns.txt
- "longest substring with condition" > See Sliding Window.txt

### **⚡ GOLDEN RULES OF STRING PROBLEMS**

### RULE 1: IN-PLACE vs NEW STRING

- C++ strings are MUTABLE - you CAN modify in-place!
- In-place > O(1) space. Building new string > O(N) space.
- Always ask: "Can I solve this without extra space?"

### RULE 2: TWO POINTERS FOR PALINDROMES

- Expand from center for "find longest palindrome"
- Converge from ends for "check if palindrome"
- Always handle both ODD (i, i) and EVEN (i, i+1) centers

### RULE 3: REVERSE TRICK FOR WORD MANIPULATION

- Reverse entire string, then reverse each word (or vice versa)
- Works for: reverse words, rotate string, rearrange

### RULE 4: KMP FOR O(N+M) PATTERN MATCHING

- Build LPS (Longest Prefix Suffix) array first
- Never re-scan matched characters > O(N+M) instead of O(N*M)
- LPS[i] = length of longest proper prefix that is also suffix

### RULE 5: CAREFUL WITH OVERFLOW IN PARSING

- Use long long for intermediate results
- Check INT_MAX/INT_MIN before each multiplication
- Handle: spaces, signs, leading zeros, non-digit chars

### RULE 6: SLIDING WINDOW FOR SUBSTRING PROBLEMS

- "Longest/shortest substring with condition" > Sliding Window
- See Sliding Window.txt for templates
- Frequency array [26] or [128] for character counts

### ** C++ STRING ESSENTIALS**

**USEFUL OPERATIONS:**

s.size() / s.length()        > length of string
s.substr(pos, len)           > substring from pos, length len
s.find(sub)                  > index of first occurrence (string::npos if not found)
s.find(sub, start)           > find starting from index start
```
reverse(s.begin(), s.end())  > reverse entire string
```

s.resize(n)                  > truncate or pad to length n
s.push_back(c)               > append char
```
s += "abc"                   > append string
to_string(num)               > int/long to string
stoi(s) / stol(s)            > string to int/long
isdigit(c), isalpha(c)       > character type checks
tolower(c), toupper(c)       > case conversion
```

## **PART 2: PATTERN RECOGNITION GUIDE**

### ** PATTERN DECISION FLOWCHART**

```
+-----------------------------------------------------------------------------+
| "REVERSE words/characters" or "rearrange in-place"                          |
|  > PATTERN 1: String Reversal / Manipulation                                |
|    Reverse entire + reverse parts trick. Two pointers in-place.             |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Is palindrome" / "Find longest palindrome" / "Make palindrome"             |
|  > PATTERN 2: Palindrome Techniques                                         |
|    Expand from center O(N2), DP for subsequence, LCS for min insertions.    |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Find pattern in text" / "First occurrence of substring"                    |
|  > PATTERN 3: Pattern Matching (KMP / Rabin-Karp / Z-function)              |
|    KMP for exact match O(N+M). Rabin-Karp for rolling hash.                 |
|    Z-function for all occurrences, period detection.                        |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Convert string-number" / "Parse with rules" / "Compare versions"           |
|  > PATTERN 4: String Parsing / Conversion                                   |
|    Careful state machine: skip spaces, handle signs, check overflow.        |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Longest/shortest SUBSTRING with condition" / "Anagram" / "Permutation"     |
|  > See Sliding Window.txt and Hashmap Patterns.txt                          |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Longest palindromic SUBSEQUENCE" / "Edit distance" / "LCS"                 |
|  > See Dynamic Programming.txt (Pattern 4: DP on Strings)                   |
+-----------------------------------------------------------------------------+

===============================================================================
        **PART 3: PATTERN 1 - STRING REVERSAL / MANIPULATION**                 
===============================================================================
```

### ** PATTERN OVERVIEW**

**CORE IDEA:**
Rearrange characters or words in-place using reverse operations
and two-pointer techniques.

###  TEMPLATE: REVERSE WORDS IN-PLACE

Step 1: Reverse the ENTIRE string
Step 2: Reverse each WORD individually
Step 3: Clean up extra spaces (if needed)

KEY INSIGHT: Two reverses cancel out positionally but flip word order!

**WHEN TO USE:**
- "Reverse words in a string"
- "Rotate string by k positions"
- "Rearrange words/characters"

### **LC 151: Reverse Words in a String** 

PROBLEM: Given a string s, reverse the order of words. Words are separated
by spaces. Remove leading/trailing/extra spaces.

Input:  "  hello   world  "
Output: "world hello"

KEY INSIGHT: Reverse entire string > each word is reversed in correct
position > reverse each word back. Use two pointers to skip/compact spaces.

```
string reverseWords(string s) {
int n = s.size();                                
reverse(s.begin(), s.end());                     
int i = 0, j = 0;                                
while (j < n) {                                  
    while (j < n && s[j] == ' ') j++;            
    if (j == n) break;                           
    if (i != 0) s[i++] = ' ';                    
    int start = i;                               
    while (j < n && s[j] != ' ') s[i++] = s[j++];
    reverse(s.begin() + start, s.begin() + i);   
}                                                
s.resize(i);                                     
return s;                                        

}
```

**WHY THIS WORKS:**
1. Reverse entire: "  dlrow   olleh  "
2. Two pointers compact spaces + copy words: "dlrow olleh"
3. Reverse each word in-place: "world hello"

TIME: O(N)  |  SPACE: O(1) - true in-place!

### **LC 38: Count and Say**

PROBLEM: Generate the nth term of the count-and-say sequence.
1 > "1"
2 > "11" (one 1)
3 > "21" (two 1s)
4 > "1211" (one 2, one 1)
5 > "111221" (one 1, one 2, two 1s)

KEY INSIGHT: Iteratively build each term by "reading" the previous term.
Group consecutive identical characters, then write count + character.

```
string countAndSay(int n) {
string result = "1";                                                  
for (int i = 1; i < n; i++) {                                         
    string next;                                                      
    int j = 0;                                                        
    while (j < result.size()) {                                       
        char ch = result[j];                                          
        int count = 0;                                                
        while (j < result.size() && result[j] == ch) { j++; count++; }
        next += to_string(count) + ch;                                
    }                                                                 
    result = next;                                                    
}                                                                     
return result;                                                        

}
```

TIME: O(N * L) where L = length of result at each step
SPACE: O(L)

### **LC 14: Longest Common Prefix**

PROBLEM: Find the longest common prefix string among an array of strings.

Input:  ["flower", "flow", "flight"]
Output: "fl"

KEY INSIGHT: Start with first string as prefix. Shrink it character by
character until it matches the start of every string.

```cpp
string longestCommonPrefix(vector<string>& strs) {
if (strs.empty()) return "";                         
string prefix = strs[0];                             
for (int i = 1; i < strs.size(); i++) {              
    while (strs[i].find(prefix) != 0) {              
        prefix = prefix.substr(0, prefix.size() - 1);
        if (prefix.empty()) return "";               
    }                                                
}                                                    
return prefix;                                       

}
```

ALTERNATIVE: Vertical scanning (compare char by char across all strings)

```cpp
string longestCommonPrefix(vector<string>& strs) {
if (strs.empty()) return "";                         
for (int i = 0; i < strs[0].size(); i++) {           
    char c = strs[0][i];                             
    for (int j = 1; j < strs.size(); j++) {          
        if (i >= strs[j].size() || strs[j][i] != c) {
            return strs[0].substr(0, i);             
        }                                            
    }                                                
}                                                    
return strs[0];                                      

}
```

TIME: O(S) where S = total characters across all strings
SPACE: O(1)

## **PART 4: PATTERN 2 - PALINDROME TECHNIQUES**

### ** PATTERN OVERVIEW**

**THREE MAIN APPROACHES:**

1. EXPAND FROM CENTER > Find longest palindromic SUBSTRING
- Try each index as center
- Expand outward while chars match
- Handle odd (single center) and even (two centers)
- Time: O(N2), Space: O(1)

2. TWO POINTERS FROM ENDS > Check if string IS a palindrome
- left = 0, right = n-1, compare and converge
- See Two Pointers.txt for details
- Time: O(N), Space: O(1)

3. DP / LCS > Palindromic SUBSEQUENCE or MIN INSERTIONS
- LCS of string and its reverse = longest palindromic subsequence
- Min insertions = N - LPS length
- Time: O(N2), Space: O(N2) or O(N) with optimization
- See Dynamic Programming.txt (Pattern 4: DP on Strings)

###  TEMPLATE: EXPAND FROM CENTER

```cpp
auto expand = [&](int l, int r) {
while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
return r - l - 1;  // length of palindrome           

};

for (int i = 0; i < n; i++) {
int oddLen  = expand(i, i);      // Odd-length: "aba"
int evenLen = expand(i, i + 1);  // Even-length: "abba"

}
```

KEY INSIGHT: Every palindrome has a center. There are 2N-1 possible
centers (N single chars + N-1 pairs). Expanding from each is O(N) worst.

### **LC 5: Longest Palindromic Substring** 

PROBLEM: Find the longest palindromic substring in s.

Input:  "babad"
Output: "bab" (or "aba")

KEY INSIGHT: For each center position, expand outward while characters
match. Track the longest found. Must check BOTH odd and even centers.

```cpp
string longestPalindrome(string s) {
int n = s.size(), start = 0, maxLen = 1;                 
auto expand = [&](int l, int r) {                        
    while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
    if (r - l - 1 > maxLen) {                            
        maxLen = r - l - 1;                              
        start = l + 1;                                   
    }                                                    
};                                                       
for (int i = 0; i < n; i++) {                            
    expand(i, i);                                        
    expand(i, i + 1);                                    
}                                                        
return s.substr(start, maxLen);                          

}
```

**WHY EXPAND FROM CENTER:**
- Brute force checks all O(N2) substrings, each O(N) > O(N3)
- Expanding from center: 2N-1 centers, each expands O(N) > O(N2)
- Much cleaner than DP approach for this specific problem

TIME: O(N2)  |  SPACE: O(1)

### **LC 1312: Minimum Insertions to Make String Palindrome** 

PROBLEM: Return the minimum number of insertions to make s a palindrome.

Input:  "mbadm"
Output: 2 ("mbdadbm")

KEY INSIGHT: Min insertions = N - LPS(s), where LPS = Longest Palindromic
Subsequence. LPS(s) = LCS(s, reverse(s)). Characters already forming a
palindromic subsequence are "free" - only the rest need insertions.

```cpp
int minInsertions(string s) {
int n = s.size();                                           
string rev(s.rbegin(), s.rend());                           
vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));       
for (int i = 1; i <= n; i++) {                              
    for (int j = 1; j <= n; j++) {                          
        if (s[i-1] == rev[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
        else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);        
    }                                                       
}                                                           
return n - dp[n][n];                                        

}
```

**WHY LCS TRICK:**
- Longest palindromic subsequence = LCS(s, reverse(s))
- Characters NOT in LPS must each be "mirrored" by one insertion
- So answer = n - LPS_length

SPACE-OPTIMIZED VERSION (O(N) space):

```cpp
int minInsertions(string s) {
int n = s.size();                                       
string rev(s.rbegin(), s.rend());                       
vector<int> prev(n + 1, 0), curr(n + 1, 0);             
for (int i = 1; i <= n; i++) {                          
    for (int j = 1; j <= n; j++) {                      
        if (s[i-1] == rev[j-1]) curr[j] = prev[j-1] + 1;
        else curr[j] = max(prev[j], curr[j-1]);         
    }                                                   
    swap(prev, curr);                                   
    fill(curr.begin(), curr.end(), 0);                  
}                                                       
return n - prev[n];                                     

}
```

TIME: O(N2)  |  SPACE: O(N2) or O(N) optimized

 CROSS-REFERENCE: For full DP on Strings patterns (LCS, Edit Distance,
Longest Palindromic Subsequence), see Dynamic Programming.txt Pattern 4.

## **PART 5: PATTERN 3 - PATTERN MATCHING ALGORITHMS**

### ** PATTERN OVERVIEW**

**THREE KEY ALGORITHMS:**

1. KMP (Knuth-Morris-Pratt) > O(N+M)
- Precompute LPS (failure function) for pattern
- On mismatch, skip already-matched prefix
- Best for: single pattern search, repeated pattern detection

2. RABIN-KARP > O(N+M) average, O(N*M) worst
- Rolling hash to compare pattern hash with window hash
- Best for: multiple pattern search, plagiarism detection
- Verify matches to handle hash collisions

3. Z-FUNCTION > O(N+M)
- Z[i] = length of longest substring starting at i that matches a prefix
- Concatenate pattern + "$" + text, then scan Z-array
- Best for: all occurrences, period detection, string compression

**WHEN TO CHOOSE:**
- Single exact pattern > KMP (guaranteed O(N+M))
- All occurrences + simpler code > Z-function (O(N+M))
- Multiple patterns > Rabin-Karp or Aho-Corasick
- Simple problems > built-in s.find() is fine!

### ** KMP ALGORITHM - DEEP DIVE**

### THE LPS ARRAY (Longest Proper Prefix which is also Suffix):

Pattern: "ABACABAD"
Index:    0 1 2 3 4 5 6 7
LPS:      0 0 1 0 1 2 3 2

```
LPS[0] = 0  > "A"        > no proper prefix = suffix
LPS[1] = 0  > "AB"       > no match
LPS[2] = 1  > "ABA"      > "A" is prefix and suffix
LPS[3] = 0  > "ABAC"     > no match
LPS[4] = 1  > "ABACA"    > "A" is prefix and suffix
LPS[5] = 2  > "ABACAB"   > "AB" is prefix and suffix
LPS[6] = 3  > "ABACABA"  > "ABA" is prefix and suffix
LPS[7] = 2  > "ABACABAD" > "AB"... wait, check pattern[3]='C' vs 'D'
```

fallback to LPS[2]=1, check pattern[1]='B' vs 'D'
fallback to LPS[0]=0, check pattern[0]='A' vs 'D'
no match > LPS[7] = 0
(Actually rechecking: "ABACABAD" proper prefixes
that are also suffixes: none > 0. Let me fix.)

Corrected:
Pattern: "AABAAAB"
Index:    0 1 2 3 4 5 6
LPS:      0 1 0 1 2 2 3

KEY INSIGHT: When a mismatch occurs at position j in pattern, we don't
restart from 0. We jump to LPS[j-1] because that many characters at the
start of the pattern ALREADY match what we just saw in the text.

### **LC 28: Find the Index of the First Occurrence in a String** 

PROBLEM: Return the index of the first occurrence of needle in haystack,
or -1 if needle is not part of haystack.

Input:  haystack = "sadbutsad", needle = "sad"
Output: 0

KEY INSIGHT: Build LPS array for the pattern. Use it to avoid re-scanning
matched characters in the text. On mismatch at pattern[j], jump j to
```cpp
LPS[j-1] instead of resetting to 0.

vector<int> buildLPS(string& pattern) {
int n = pattern.size();              
vector<int> lps(n, 0);               
int len = 0, i = 1;                  
while (i < n) {                      
    if (pattern[i] == pattern[len]) {
        lps[i++] = ++len;            
    } else if (len > 0) {            
        len = lps[len - 1];          
    } else {                         
        lps[i++] = 0;                
    }                                
}                                    
return lps;                          

}

int strStr(string haystack, string needle) {
if (needle.empty()) return 0;                
vector<int> lps = buildLPS(needle);          
int i = 0, j = 0;                            
while (i < haystack.size()) {                
    if (haystack[i] == needle[j]) {          
        i++; j++;                            
        if (j == needle.size()) return i - j;
    } else if (j > 0) {                      
        j = lps[j - 1];                      
    } else {                                 
        i++;                                 
    }                                        
}                                            
return -1;                                   

}
```

WHY KMP IS O(N+M):
- Building LPS: O(M) - each char processed at most twice
- Searching: O(N) - text pointer i NEVER moves backward
- Total: O(N+M) vs naive O(N*M)

**WALKTHROUGH EXAMPLE:**
```
haystack = "ABABDABACDABABCABAB"
needle   = "ABABCABAB"
LPS      = [0,0,1,2,0,1,2,3,4]

i=0,j=0: A=A Y > i=1,j=1
i=1,j=1: B=B Y > i=2,j=2
i=2,j=2: A=A Y > i=3,j=3
i=3,j=3: B=B Y > i=4,j=4
i=4,j=4: D!C X > j=LPS[3]=2  (skip! already matched "AB")
i=4,j=2: D!A X > j=LPS[1]=0
i=4,j=0: D!A X > i=5
```

...continues until match found

TIME: O(N+M)  |  SPACE: O(M) for LPS array

### **RABIN-KARP ALGORITHM** (Rolling Hash Pattern Matching)

PROBLEM: Find pattern in text using hashing.

KEY INSIGHT: Compute hash of pattern. Slide a window of same length across
text, updating hash in O(1) using rolling hash. Only do character-by-character
comparison when hashes match (to handle collisions).

###  TEMPLATE: ROLLING HASH

```
hash("abc") = a*base2 + b*base¹ + c*base⁰
```

To slide window right (remove 'a', add 'd'):
```
hash("bcd") = (hash("abc") - a*base2) * base + d

int rabinKarp(string text, string pattern) {
int n = text.size(), m = pattern.size();                                         
if (m > n) return -1;                                                            

long long base = 31, mod = 1e9 + 7;                                              
long long patHash = 0, textHash = 0, power = 1;                                  

// Compute hash of pattern and first window                                      
for (int i = 0; i < m; i++) {                                                    
    patHash = (patHash + (long long)(pattern[i] - 'a' + 1) * power) % mod;       
    textHash = (textHash + (long long)(text[i] - 'a' + 1) * power) % mod;        
    if (i < m - 1) power = (power * base) % mod;                                 
}                                                                                

// Slide window                                                                  
for (int i = 0; i <= n - m; i++) {                                               
    if (patHash == textHash) {                                                   
        if (text.substr(i, m) == pattern) return i;                              
    }                                                                            
    if (i < n - m) {                                                             
        // Remove leftmost char, add new rightmost char                          
        textHash = (textHash - (long long)(text[i] - 'a' + 1) + mod) % mod;      
        textHash = (textHash / base) % mod;  // Simplified; see note below       
        textHash = (textHash + (long long)(text[i + m] - 'a' + 1) * power) % mod;
    }                                                                            
}                                                                                
return -1;                                                                       

}
```

 NOTE: Division in modular arithmetic requires modular inverse.
A simpler approach uses the hash formula: h = (h*base + new - old*base^m) % mod

SIMPLER ROLLING HASH (recommended for interviews):

```
int rabinKarp(string text, string pattern) {
int n = text.size(), m = pattern.size();                                    
if (m > n) return -1;                                                       

long long base = 26, mod = 1e9 + 7;                                         
long long patHash = 0, textHash = 0;                                        
long long highPow = 1;                                                      

for (int i = 0; i < m - 1; i++) highPow = (highPow * base) % mod;           

for (int i = 0; i < m; i++) {                                               
    patHash = (patHash * base + (pattern[i] - 'a')) % mod;                  
    textHash = (textHash * base + (text[i] - 'a')) % mod;                   
}                                                                           

for (int i = 0; i <= n - m; i++) {                                          
    if (patHash == textHash && text.substr(i, m) == pattern) return i;      
    if (i < n - m) {                                                        
        textHash = (textHash - (text[i] - 'a') * highPow % mod + mod) % mod;
        textHash = (textHash * base + (text[i + m] - 'a')) % mod;           
    }                                                                       
}                                                                           
return -1;                                                                  

}
```

**WHEN TO USE RABIN-KARP OVER KMP:**
- Multiple pattern search (compute hash for each pattern)
- 2D pattern matching
- When you need all occurrences (easy to continue after match)

TIME: O(N+M) average, O(N*M) worst (hash collisions)
SPACE: O(1) extra (excluding output)

### ** Z-FUNCTION ALGORITHM - DEEP DIVE**

**THE Z-ARRAY:**

```
Z[i] = length of the longest substring starting at position i
```

that matches a PREFIX of the string.

```
Z[0] is undefined (or set to 0 / n by convention).
```

String:  "aabxaab"
Index:    0 1 2 3 4 5 6
Z:        - 1 0 0 3 1 0

```
Z[1] = 1  > "a" matches prefix "a"
Z[4] = 3  > "aab" matches prefix "aab"
```

KEY INSIGHT: For pattern matching, concatenate pattern + "$" + text.
Any Z[i] == len(pattern) means a match starts at position i - len(pattern) - 1
in the original text. The "$" separator prevents matches across the boundary.

###  TEMPLATE: BUILD Z-ARRAY

```cpp
vector<int> zFunction(string s) {
int n = s.size();                                         
vector<int> z(n, 0);                                      
int l = 0, r = 0;                                         
for (int i = 1; i < n; i++) {                             
    if (i < r) z[i] = min(r - i, z[i - l]);               
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) { l = i; r = i + z[i]; }            
}                                                         
return z;                                                 

}
```

**PATTERN MATCHING WITH Z-FUNCTION:**

```cpp
int zSearch(string text, string pattern) {
string concat = pattern + "$" + text;        
vector<int> z = zFunction(concat);           
int m = pattern.size();                      
for (int i = m + 1; i < concat.size(); i++) {
    if (z[i] == m) return i - m - 1;         
}                                            
return -1;                                   

}
```

**WHY Z-FUNCTION IS O(N):**
- The [l, r) window only moves forward (r never decreases)
- Each character is compared at most twice (once to extend r,
once to verify via the copied z-value)

- Total work: O(N)

**WHEN TO USE Z-FUNCTION OVER KMP:**
- Simpler to implement and reason about than LPS
- Finding ALL occurrences of pattern (just check Z[i] == m)
- Period/repetition detection (smallest i where i + Z[i] == n)
- String compression problems

TIME: O(N+M)  |  SPACE: O(N+M) for concatenated string + Z-array

### **LC 187: Repeated DNA Sequences** (Rabin-Karp Application)

PROBLEM: Find all 10-letter-long sequences that occur more than once
in a DNA string (characters: A, C, G, T).

Input:  "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]

KEY INSIGHT: Slide a window of length 10 across the string. Use a hashmap
to count occurrences. Add to result when count reaches exactly 2 (avoids
duplicates). Can also use rolling hash for O(1) per window shift.

```cpp
vector<string> findRepeatedDnaSequences(string s) {
unordered_map<string, int> seen;                
vector<string> result;                          
for (int i = 0; i + 10 <= s.size(); i++) {      
    string sub = s.substr(i, 10);               
    if (++seen[sub] == 2) result.push_back(sub);
}                                               
return result;                                  

}
```

WHY ++seen[sub] == 2:
- First time seen: count becomes 1, not added
- Second time seen: count becomes 2, added to result
- Third+ time: count > 2, NOT added again (no duplicates)

ROLLING HASH OPTIMIZATION (for very large strings):
Encode A=0, C=1, G=2, T=3 > each 10-char window is a 20-bit number.
Shift hash left by 2 bits, add new char, mask to 20 bits.

TIME: O(N)  |  SPACE: O(N)

### **KMP vs RABIN-KARP vs Z-FUNCTION COMPARISON**

```
+------------------+-------------------------+-------------------------+--------------------------+
| Feature          | KMP                     | Rabin-Karp              | Z-Function               |
+------------------+-------------------------+-------------------------+--------------------------+
| Time (worst)     | O(N+M) guaranteed       | O(N*M) (collisions)     | O(N+M) guaranteed        |
| Time (average)   | O(N+M)                  | O(N+M)                  | O(N+M)                   |
| Preprocessing    | O(M) - LPS array        | O(M) - hash computation | O(N+M) - Z-array         |
| Space            | O(M) - LPS array        | O(1)                    | O(N+M) - Z-array         |
| Multiple patterns| Need separate LPS each  | Just compute more hashes| Need separate concat     |
| Best for         | Single exact match       | Multi-pattern, 2D match | All occurrences, period |
| Ease of coding   |  Moderate            |  Moderate            |  Simplest                      |
| Interview freq.  |  Very common       |  Moderate            |  Moderate                        |
+------------------+-------------------------+-------------------------+--------------------------+

===============================================================================                    
        **PART 6: PATTERN 4 - STRING PARSING / CONVERSION**                                        
===============================================================================                    
```

### ** PATTERN OVERVIEW**

**CORE IDEA:**
Parse strings according to specific rules, convert between representations.
These problems test careful implementation and edge case handling.

###  TEMPLATE: STRING-TO-NUMBER PARSING

Step 1: Skip leading whitespace
Step 2: Handle optional sign (+/-)
Step 3: Process digits, building number: result = result * 10 + digit
Step 4: Check overflow at EACH step
Step 5: Return result * sign

**COMMON PITFALLS:**
- Forgetting leading spaces
- Missing sign handling
- Integer overflow (check BEFORE multiply)
- Non-digit characters stopping parse

### **LC 13: Roman to Integer**

PROBLEM: Convert Roman numeral string to integer.
"MCMXCIV" > 1994

KEY INSIGHT: If a smaller value appears BEFORE a larger value, subtract it.
Otherwise add it. Scan left to right, compare current with next.

```
int romanToInt(string s) {
unordered_map<char, int> m = {                    
    {'I',1}, {'V',5}, {'X',10}, {'L',50},         
    {'C',100}, {'D',500}, {'M',1000}              
};                                                
int result = 0;                                   
for (int i = 0; i < s.size(); i++) {              
    if (i + 1 < s.size() && m[s[i]] < m[s[i+1]]) {
        result -= m[s[i]];                        
    } else {                                      
        result += m[s[i]];                        
    }                                             
}                                                 
return result;                                    

}
```

WALKTHROUGH: "MCMXCIV"
```
M(1000) < C? No > +1000  result=1000
C(100) < M(1000)? Yes > -100  result=900
M(1000) < X? No > +1000  result=1900
X(10) < C(100)? Yes > -10  result=1890
C(100) < I? No > +100  result=1990
I(1) < V(5)? Yes > -1  result=1989
V(5) last > +5  result=1994 Y
```

TIME: O(N)  |  SPACE: O(1)

### **LC 12: Integer to Roman**

PROBLEM: Convert integer to Roman numeral string.
1994 > "MCMXCIV"

KEY INSIGHT: Greedy approach - always use the LARGEST possible Roman value.
Pre-define all 13 values (including subtractives like 900, 400, etc.) in
descending order. Repeatedly subtract and append.

```cpp
string intToRoman(int num) {
vector<pair<int,string>> vals = {                 
    {1000,"M"}, {900,"CM"}, {500,"D"}, {400,"CD"},
    {100,"C"}, {90,"XC"}, {50,"L"}, {40,"XL"},    
    {10,"X"}, {9,"IX"}, {5,"V"}, {4,"IV"}, {1,"I"}
};                                                
string result;                                    
for (auto& [val, sym] : vals) {                   
    while (num >= val) {                          
        result += sym;                            
        num -= val;                               
    }                                             
}                                                 
return result;                                    

}
```

WHY 13 VALUES: The 6 subtractive cases (CM, CD, XC, XL, IX, IV) are
treated as single "units" alongside the 7 standard values. This eliminates
all special-case logic.

TIME: O(1) - number of iterations bounded by constant (max ~15 for 3999)
SPACE: O(1)

### **LC 8: String to Integer - atoi** 

PROBLEM: Implement atoi - convert string to 32-bit signed integer.
Rules: skip whitespace, optional sign, read digits, clamp to [INT_MIN, INT_MAX].

Input:  "   -42abc"
Output: -42

KEY INSIGHT: Sequential state machine - whitespace > sign > digits > stop.
Check overflow BEFORE each multiplication/addition to avoid UB.

```
int myAtoi(string s) {
int i = 0, n = s.size();                        
while (i < n && s[i] == ' ') i++;               
int sign = 1;                                   
if (i < n && (s[i] == '+' || s[i] == '-')) {    
    sign = (s[i] == '-') ? -1 : 1;              
    i++;                                        
}                                               
long long result = 0;                           
while (i < n && isdigit(s[i])) {                
    result = result * 10 + (s[i] - '0');        
    if (result * sign > INT_MAX) return INT_MAX;
    if (result * sign < INT_MIN) return INT_MIN;
    i++;                                        
}                                               
return result * sign;                           

}
```

**EDGE CASES TO HANDLE:**
- "   " > 0 (all spaces)
- "+-12" > 0 (invalid sign)
- "21474836460" > INT_MAX (overflow)
- "words 123" > 0 (non-digit first)
- "" > 0 (empty string)

TIME: O(N)  |  SPACE: O(1)

### **LC 165: Compare Version Numbers**

PROBLEM: Compare two version strings. Return -1, 0, or 1.
"1.01" vs "1.001" > 0 (equal: 1.1 vs 1.1)
"1.0.1" vs "1" > 1 (1.0.1 > 1.0.0)

KEY INSIGHT: Parse one revision at a time from each string. Compare
numerically (leading zeros don't matter). If one string is shorter,
treat missing revisions as 0.

```
int compareVersion(string version1, string version2) {
int i = 0, j = 0;                                                             
int n1 = version1.size(), n2 = version2.size();                               
while (i < n1 || j < n2) {                                                    
    int v1 = 0, v2 = 0;                                                       
    while (i < n1 && version1[i] != '.') v1 = v1 * 10 + (version1[i++] - '0');
    while (j < n2 && version2[j] != '.') v2 = v2 * 10 + (version2[j++] - '0');
    if (v1 < v2) return -1;                                                   
    if (v1 > v2) return 1;                                                    
    i++; j++;                                                                 
}                                                                             
return 0;                                                                     

}
```

WHY TWO POINTERS: No need to split into arrays. Parse each segment
on-the-fly, handling different lengths naturally with the || condition.

TIME: O(N+M)  |  SPACE: O(1)

### **LC 242: Valid Anagram**

 CROSS-REFERENCE: Full solution and patterns in Hashmap Patterns.txt
(Pattern 3: Anagram Detection).

**QUICK SOLUTION:**

```
bool isAnagram(string s, string t) {
if (s.size() != t.size()) return false;                     
int freq[26] = {};                                          
for (char c : s) freq[c - 'a']++;                           
for (char c : t) freq[c - 'a']--;                           
for (int i = 0; i < 26; i++) if (freq[i] != 0) return false;
return true;                                                

}
```

TIME: O(N)  |  SPACE: O(1)

## **PART 7: INTERVIEW CHEAT CODES**

### **⚡ QUICK TRICKS FOR COMMON STRING OPERATIONS**

### TRICK 1: CHECK PALINDROME IN ONE LINE

```
bool isPalin = (s == string(s.rbegin(), s.rend()));
```

### TRICK 2: CONVERT TO LOWERCASE FOR CASE-INSENSITIVE

```cpp
transform(s.begin(), s.end(), s.begin(), ::tolower);
```

### TRICK 3: SPLIT STRING BY DELIMITER

```cpp
stringstream ss(s);
string word;
vector<string> words;
while (ss >> word) words.push_back(word);  // split by whitespace

// Split by custom delimiter:
while (getline(ss, word, '.')) words.push_back(word);
```

### TRICK 4: CHAR-TO-INT AND INT-TO-CHAR

```
int digit = c - '0';       // char '5' > int 5
char c = digit + '0';      // int 5 > char '5'
int idx = c - 'a';         // char 'c' > index 2
```

### TRICK 5: FREQUENCY ARRAY vs HASHMAP

```
int freq[26] = {};          // for lowercase letters only - FASTER
int freq[128] = {};         // for all ASCII - still O(1) space
unordered_map<char, int>    // for Unicode or when you need .size()
```

### TRICK 6: REVERSE ONLY PART OF STRING

```
reverse(s.begin() + start, s.begin() + end);  // [start, end)
```

### TRICK 7: STRING MULTIPLICATION/REPETITION

```
string repeated(n, c);      // n copies of char c
// For repeating a string: use a loop or string(n, c)
```

### ** COMMON MISTAKES TO AVOID**

MISTAKE 1: Off-by-one with substr
X s.substr(i, j)   > NOT from i to j!
Y s.substr(i, len) > from index i, length len

MISTAKE 2: Forgetting string::npos check
X if (s.find("abc"))  > 0 is a valid index, not false!
Y if (s.find("abc") != string::npos)

MISTAKE 3: Modifying string while iterating by index
X Erasing characters shifts indices
Y Use two-pointer compaction or build new string

MISTAKE 4: Comparing s.size() with negative int
X if (i < s.size() - 1)  > when s is empty, size()-1 wraps to huge number!
Y if (i + 1 < s.size())  > OR cast: if (i < (int)s.size() - 1)

MISTAKE 5: Integer overflow in atoi
X result = result * 10 + digit  > overflow before you check!
```
Y Check BEFORE: if (result > (INT_MAX - digit) / 10) return INT_MAX;
```

## **PART 8: QUICK REVISION TABLE**

### **PROBLEM > TECHNIQUE > KEY INSIGHT**

```
+----------------------------------------+------------------+--------------------------------+
| Problem                                | Technique        | Key Insight                    |
+----------------------------------------+------------------+--------------------------------+
| Reverse Words (LC 151)               | Reverse + 2-ptr  | Reverse all, then each word      |
| Longest Palindrome Substr (LC 5)   | Expand center    | 2N-1 centers, expand outward       |
| Min Insertions Palindrome (LC 1312)    | DP (LCS)         | N - LCS(s, reverse(s))         |
| KMP / strStr (LC 28)               | KMP + LPS        | LPS avoids re-scanning             |
| Rabin-Karp / DNA Sequences (LC 187)    | Rolling hash     | O(1) hash update per slide     |
| Z-Function                             | Z-array          | Prefix match at every position |
| Roman to Integer (LC 13)               | Map + scan       | Subtract if smaller before     |
| Integer to Roman (LC 12)               | Greedy           | 13 values in descending order  |
| atoi (LC 8)                          | State machine    | spaces > sign > digits > stop    |
| Longest Common Prefix (LC 14)          | Shrink prefix    | Start full, shrink per string  |
| Count and Say (LC 38)                  | Simulation       | Group consecutive, write count |
| Compare Versions (LC 165)              | Two pointers     | Parse segments, missing = 0    |
| Valid Anagram (LC 242)                 | Frequency array  | freq[26], increment/decrement  |
+----------------------------------------+------------------+--------------------------------+

===============================================================================               
              **PART 9: COMPLETE PROBLEM LIST BY CATEGORY**                                   
===============================================================================               
```

**STRING REVERSAL / MANIPULATION**

- 151.  Reverse Words in a String 
- 557.  Reverse Words in a String III 
- 344.  Reverse String  (> Two Pointers.txt)
- 541.  Reverse String II 
- 14.   Longest Common Prefix 
- 38.   Count and Say 
- 443.  String Compression  (> Two Pointers.txt)
- 6.    Zigzag Conversion 

**PALINDROME**

- 5.    Longest Palindromic Substring 
- 125.  Valid Palindrome  (> Two Pointers.txt)
- 680.  Valid Palindrome II  (> Two Pointers.txt)
- 9.    Palindrome Number 
- 131.  Palindrome Partitioning  (> Backtracking.txt)
- 132.  Palindrome Partitioning II  (> Dynamic Programming.txt)
- 516.  Longest Palindromic Subsequence  (> Dynamic Programming.txt)
- 1312. Minimum Insertions to Make String Palindrome 
- 647.  Palindromic Substrings 
- 214.  Shortest Palindrome  (KMP-based)

**PATTERN MATCHING**

- 28.   Find the Index of the First Occurrence  (KMP)
- 187.  Repeated DNA Sequences  (Rabin-Karp / Rolling Hash)
- 459.  Repeated Substring Pattern  (KMP trick: check if s+s contains s)
- 686.  Repeated String Match 
- 214.  Shortest Palindrome  (reverse + KMP)
- 572.  Subtree of Another Tree  (string serialization + KMP)

**STRING PARSING / CONVERSION**

- 8.    String to Integer (atoi) 
- 12.   Integer to Roman 
- 13.   Roman to Integer 
- 165.  Compare Version Numbers 
- 67.   Add Binary 
- 415.  Add Strings 
- 43.   Multiply Strings 
- 273.  Integer to English Words 
- 65.   Valid Number 

**ANAGRAM / FREQUENCY** (> Hashmap Patterns.txt, Sliding Window.txt)

- 242.  Valid Anagram 
- 49.   Group Anagrams  (> Hashmap Patterns.txt)
- 387.  First Unique Character in a String  (> Hashmap Patterns.txt)
- 438.  Find All Anagrams in a String  (> Sliding Window.txt)
- 567.  Permutation in String  (> Sliding Window.txt)

**PARENTHESES / BRACKET MATCHING** (> Monotonic Stack.txt)

- 20.   Valid Parentheses  (> Monotonic Stack.txt)
- 22.   Generate Parentheses  (> Backtracking.txt)
- 32.   Longest Valid Parentheses  (> Dynamic Programming.txt)

**SUBSTRING PROBLEMS** (> Sliding Window.txt)

- 3.    Longest Substring Without Repeating Characters 
- 76.   Minimum Window Substring 
- 424.  Longest Repeating Character Replacement 
- 340.  Longest Substring with At Most K Distinct Characters 

**DP ON STRINGS** (> Dynamic Programming.txt)

- 1143. Longest Common Subsequence 
- 72.   Edit Distance 
- 10.   Regular Expression Matching 
- 44.   Wildcard Matching 
- 115.  Distinct Subsequences 
- 97.   Interleaving String 

## **PART 10: MASTER PROBLEM MAPPING TABLE**

```
+----------------------------------------------+-------------------------------+
| Problem                                      | Pattern                       |
+----------------------------------------------+-------------------------------+
| Reverse Words in a String (LC 151)           | Reversal + Two Pointers       |
| Reverse Words in a String III (LC 557)       | Reverse Each Word             |
| Reverse String (LC 344)                      | Two Pointers (Opposite)       |
| Longest Common Prefix (LC 14)                | Shrink Prefix                 |
| Count and Say (LC 38)                        | Iterative Simulation          |
| String Compression (LC 443)                  | Slow & Fast Pointers          |
| Longest Palindromic Substring (LC 5)         | Expand From Center            |
| Valid Palindrome (LC 125)                    | Two Pointers (Opposite)       |
| Valid Palindrome II (LC 680)                 | Two Ptrs + Skip One           |
| Palindromic Substrings (LC 647)              | Expand From Center            |
| Min Insertions Palindrome (LC 1312)          | DP - LCS(s, rev(s))           |
| Shortest Palindrome (LC 214)                 | KMP on rev(s) + "#" + s       |
| Find First Occurrence (LC 28)                | KMP Algorithm                 |
| Repeated Substring Pattern (LC 459)          | KMP (LPS array trick)         |
| Repeated DNA Sequences (LC 187)              | Rolling Hash / Hashmap        |
| Roman to Integer (LC 13)                     | Map + Subtract-if-smaller     |
| Integer to Roman (LC 12)                     | Greedy Descending             |
| String to Integer (LC 8)                     | State Machine Parsing         |
| Compare Version Numbers (LC 165)             | Two-Pointer Segment Parse     |
| Valid Anagram (LC 242)                       | Frequency Array               |
| Group Anagrams (LC 49)                       | Sorted Key > Hashmap          |
| Add Binary (LC 67)                           | Reverse + Carry               |
| Multiply Strings (LC 43)                     | Grade-School Multiplication   |
| Longest Substring No Repeat (LC 3)           | Sliding Window                |
| Minimum Window Substring (LC 76)             | Sliding Window + Freq Map     |
| Longest Common Subsequence (LC 1143)         | DP on Strings                 |
| Edit Distance (LC 72)                        | DP on Strings                 |
| Regular Expression Matching (LC 10)          | DP on Strings                 |
| Valid Parentheses (LC 20)                    | Stack (> Monotonic Stack)     |
| First Unique Character (LC 387)              | Frequency Array (> Hashmap)   |
| Find All Anagrams (LC 438)                   | Sliding Window + Freq Map     |
+----------------------------------------------+-------------------------------+

+------------------------------------------------------------------------------+
|                   STRING PATTERN DECISION FLOWCHART                          |
+------------------------------------------------------------------------------+
|                                                                              |
|  Need to REVERSE or REARRANGE words/chars?                                   |
|    YES > Reverse trick (reverse all + reverse parts)                         |
|                                                                              |
|  Is it about PALINDROMES?                                                    |
|    Substring > EXPAND FROM CENTER O(N2)                                      |
|    Subsequence > DP (LCS with reverse)                                       |
|    Check > TWO POINTERS from ends                                            |
|                                                                              |
|  Need to FIND a pattern in text?                                             |
|    Single pattern > KMP O(N+M) or Z-function O(N+M)                          |
|    Multiple patterns > Rabin-Karp or Aho-Corasick                            |
|    Period/repetition > Z-function                                            |
|    Simple/short > built-in find() is fine                                    |
|                                                                              |
|  CONVERT between string and number?                                          |
|    String > Number: state machine (spaces, sign, digits, overflow)           |
|    Number > String: greedy with value table                                  |
|    Roman: map + subtraction rule                                             |
|                                                                              |
|  Find LONGEST/SHORTEST SUBSTRING with condition?                             |
|    > Sliding Window! See Sliding Window.txt                                  |
|                                                                              |
|  ANAGRAM or PERMUTATION detection?                                           |
|    > Frequency array + Sliding Window or Hashmap                             |
|    See Hashmap Patterns.txt and Sliding Window.txt                           |
|                                                                              |
|  COMPARE two strings optimally (LCS, edit distance)?                         |
|    > DP on Strings. See Dynamic Programming.txt                              |
|                                                                              |
+------------------------------------------------------------------------------+

================================================================================
                     **4 PATTERNS QUICK REFERENCE**                             
================================================================================
```

Pattern 1:  String Reversal    > Reverse all + reverse parts, two-pointer compact
Pattern 2:  Palindrome         > Expand center (substring), DP/LCS (subsequence)
Pattern 3:  Pattern Matching   > KMP (LPS array), Rabin-Karp (rolling hash), Z-function
Pattern 4:  Parsing/Conversion > State machine, greedy with value tables

  Substring with condition > See Sliding Window.txt
  Anagrams/Frequency > See Hashmap Patterns.txt
  DP on Strings (LCS, Edit Distance) > See Dynamic Programming.txt
  Palindrome check / Reverse > See Two Pointers.txt

## END
