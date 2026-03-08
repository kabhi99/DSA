# **BACKTRACKING - COMPLETE GUIDE**

Master Permutations, Combinations, Subsets, and Constraint Satisfaction!

### **TABLE OF CONTENTS**

1. What is Backtracking?
2. Universal Template
3. Pattern 1: Subsets
4. Pattern 2: Combinations
5. Pattern 3: Permutations
6. Pattern 4: Grid/Matrix Backtracking
7. Pattern 5: Constraint Satisfaction (N-Queens, Sudoku)
8. Pruning Techniques
9. Pattern Recognition Guide
10. Problem List by Category

## **PART 1: WHAT IS BACKTRACKING?**

### **DEFINITION**

```
Backtracking = DFS + UNDO (make choice, explore, undo choice)
```

 **MEMORY AID**: "**T**ry, **E**xplore, **U**ndo" (TEU)
1. Try a choice (add to path)
2. Explore recursively
3. Undo the choice (remove from path)

**CORE IDEA:**
- Build candidates incrementally
- Abandon candidate as soon as it can't lead to valid solution ("pruning")
- Return to previous state and try other options

WHY "BACKTRACKING"?
- We "track back" to previous decision point when current path fails
- Like exploring a maze: go forward, hit dead end, go back, try another path

### **WHEN TO USE BACKTRACKING?** 

**STRONG SIGNALS:**
 "Find ALL" solutions (not just one)
 "Generate all" possibilities
 "All permutations/combinations/subsets"
 "N-Queens", "Sudoku solver"
 "Word search in grid"
 Constraint satisfaction problems

**KEYWORDS:**
- "all", "generate", "enumerate"
- "permutations", "combinations", "subsets"
- "valid configurations"
- "place N items such that..."

### **BACKTRACKING vs DFS vs DYNAMIC PROGRAMMING**

```
+----------------------------------------------------------------------------+
| Technique      | Goal                    | Key Feature                     |
+----------------+-------------------------+---------------------------------+
| DFS            | Traverse/Search         | Visit all nodes                 |
| Backtracking   | Find ALL valid paths    | DFS + undo invalid choices      |
| DP             | Find OPTIMAL solution   | Store & reuse subproblems       |
+----------------+-------------------------+---------------------------------+
```

**GOLDEN RULE:**
> Need ALL solutions > Backtracking
> Need OPTIMAL solution > DP (if overlapping subproblems)
> Need to check if path EXISTS > DFS

## **PART 2: UNIVERSAL TEMPLATE** 

### **THE BACKTRACKING TEMPLATE**

```
void backtrack(state, choices, result) {
// 1. BASE CASE: Found a valid solution                        
if (isComplete(state)) {                                       
    result.add(copy of state);                                 
    return;                                                    
}                                                              

// 2. ITERATE: Try each choice                                 
for (choice : available_choices) {                             

    // 3. PRUNE: Skip invalid choices (optional but important!)
    if (!isValid(choice)) continue;                            

    // 4. MAKE CHOICE: Add to current state                    
    state.add(choice);                                         

    // 5. EXPLORE: Recurse with updated state                  
    backtrack(state, remaining_choices, result);               

    // 6. UNDO CHOICE: Remove from state (BACKTRACK!)          
    state.remove(choice);                                      
}                                                              

}
```

### **TEMPLATE BREAKDOWN**

1. BASE CASE:
- When is the solution complete?
- Subsets: always valid (add at each step)
- Combinations: path.size() == k
- Permutations: path.size() == n

2. ITERATE CHOICES:
- What are the available options?
- Subsets/Combinations: start from index to avoid duplicates
- Permutations: all elements not yet used

3. PRUNE:
- Skip invalid/unnecessary branches early
- Huge time saver!

4. MAKE CHOICE:
- Add current element to path/state
- Mark as used (if needed)

5. EXPLORE:
- Recursive call with updated parameters

6. UNDO CHOICE:
- Remove element from path/state
- Unmark as used
- THIS IS THE "BACKTRACK" STEP!

## **PART 3: PATTERN 1 - SUBSETS**

### **SUBSETS PATTERN**

**KEY CHARACTERISTICS:**
- Include or exclude each element
- Order doesn't matter
- Every intermediate state is a valid subset
- 2^n total subsets

**TEMPLATE:**

```
void subsetBacktrack(nums, start, path, result) {
result.add(copy of path);  // Every state is valid!                   

for (int i = start; i < nums.size(); i++) {                           
    path.add(nums[i]);                                                
    subsetBacktrack(nums, i + 1, path, result);  // i+1 to avoid reuse
    path.remove_last();                                               
}                                                                     

}
```

### **PROBLEM: Subsets (LC 78)** 

 PATTERN: Basic subset generation
 TEMPLATE: Add current state, iterate from start index

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

**VISUALIZATION:**
```
                  []            
       /          |          \  
     [1]         [2]         [3]
    /   \                      |
  [1,2] [1,3]   [2,3]           
                               |
 [1,2,3]                        
```

```cpp
vector<vector<int>> subsets(vector<int>& nums) {
vector<vector<int>> result;      
vector<int> path;                
backtrack(nums, 0, path, result);
return result;                   

}

void backtrack(vector<int>& nums, int start,
           vector<int>& path, vector<vector<int>>& result) {
result.push_back(path);  // Add current subset              

for (int i = start; i < nums.size(); i++) {                 
    path.push_back(nums[i]);           // Choose            
    backtrack(nums, i + 1, path, result);  // Explore       
    path.pop_back();                   // Unchoose          
}                                                           

}
```

TIME: O(N x 2^N) - 2^N subsets, O(N) to copy each
SPACE: O(N) for recursion depth

### **PROBLEM: Subsets II (LC 90)** 

 PATTERN: Subsets with DUPLICATES
 TEMPLATE: Sort + skip consecutive duplicates

**KEY INSIGHT:**
- Sort array first
- Skip duplicates at same decision level
- if (i > start && nums[i] == nums[i-1]) skip!

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

```cpp
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
sort(nums.begin(), nums.end());  // Sort first!
vector<vector<int>> result;                    
vector<int> path;                              
backtrack(nums, 0, path, result);              
return result;                                 

}

void backtrack(vector<int>& nums, int start,
           vector<int>& path, vector<vector<int>>& result) {
result.push_back(path);                                     

for (int i = start; i < nums.size(); i++) {                 
    // Skip duplicates at same level                        
    if (i > start && nums[i] == nums[i-1]) continue;        

    path.push_back(nums[i]);                                
    backtrack(nums, i + 1, path, result);                   
    path.pop_back();                                        
}                                                           

}
```

 CRITICAL: i > start (not i > 0)
We only skip duplicates at SAME decision level!

## **PART 4: PATTERN 2 - COMBINATIONS**

### **COMBINATIONS PATTERN**

**KEY CHARACTERISTICS:**
- Select K elements from N
- Order doesn't matter
- Fixed size output (exactly K elements)
- C(n,k) = n!/(k!(n-k)!) combinations

**TEMPLATE:**

```
void combBacktrack(n, k, start, path, result) {
if (path.size() == k) {  // Base case: found valid combination
    result.add(copy of path);                                 
    return;                                                   
}                                                             

for (int i = start; i <= n; i++) {                            
    path.add(i);                                              
    combBacktrack(n, k, i + 1, path, result);                 
    path.remove_last();                                       
}                                                             

}
```

### **PROBLEM: Combinations (LC 77)** 

 PATTERN: Select k elements from 1 to n
 TEMPLATE: Stop when path.size() == k

Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]

```cpp
vector<vector<int>> combine(int n, int k) {
vector<vector<int>> result;      
vector<int> path;                
backtrack(n, k, 1, path, result);
return result;                   

}

void backtrack(int n, int k, int start,
           vector<int>& path, vector<vector<int>>& result) {
if (path.size() == k) {                                     
    result.push_back(path);                                 
    return;                                                 
}                                                           

// Pruning: need (k - path.size()) more elements            
// Can only start from i where n - i + 1 >= remaining needed
for (int i = start; i <= n - (k - path.size()) + 1; i++) {  
    path.push_back(i);                                      
    backtrack(n, k, i + 1, path, result);                   
    path.pop_back();                                        
}                                                           

}
```

**PRUNING EXPLANATION:**
If path.size() = 1 and k = 3, we need 2 more elements
If we're at i = 3 and n = 4, we have [3, 4] available = 2 elements Y
If we're at i = 4 and n = 4, we have [4] available = 1 element X
So we can stop early!

### **PROBLEM: Combination Sum (LC 39)** 

 PATTERN: Combinations with REUSE allowed, sum to target
 TEMPLATE: Don't increment start (allow reuse), check sum

**KEY INSIGHT:**
- Can reuse same element > use i (not i+1) in recursive call
- Stop when sum >= target

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]

```cpp
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
vector<vector<int>> result;                    
vector<int> path;                              
backtrack(candidates, target, 0, path, result);
return result;                                 

}

void backtrack(vector<int>& candidates, int remaining, int start,
           vector<int>& path, vector<vector<int>>& result) {          
if (remaining == 0) {                                                 
    result.push_back(path);                                           
    return;                                                           
}                                                                     
if (remaining < 0) return;                                            

for (int i = start; i < candidates.size(); i++) {                     
    path.push_back(candidates[i]);                                    
    backtrack(candidates, remaining - candidates[i], i, path, result);
    //                                               ^ NOT i+1!       
    path.pop_back();                                                  
}                                                                     

}
```

### **PROBLEM: Combination Sum II (LC 40)** 

 PATTERN: Combinations with duplicates, NO REUSE
 TEMPLATE: Sort + skip duplicates + use i+1

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: [[1,1,6],[1,2,5],[1,7],[2,6]]

```cpp
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
sort(candidates.begin(), candidates.end());  // Sort!
vector<vector<int>> result;                          
vector<int> path;                                    
backtrack(candidates, target, 0, path, result);      
return result;                                       

}

void backtrack(vector<int>& candidates, int remaining, int start,
           vector<int>& path, vector<vector<int>>& result) {              
if (remaining == 0) {                                                     
    result.push_back(path);                                               
    return;                                                               
}                                                                         
if (remaining < 0) return;                                                

for (int i = start; i < candidates.size(); i++) {                         
    // Skip duplicates at same level                                      
    if (i > start && candidates[i] == candidates[i-1]) continue;          

    path.push_back(candidates[i]);                                        
    backtrack(candidates, remaining - candidates[i], i + 1, path, result);
    //                                               ^ i+1 (no reuse)     
    path.pop_back();                                                      
}                                                                         

}
```

### **PROBLEM: Combination Sum III (LC 216)**

 PATTERN: K numbers from 1-9 that sum to N
 TEMPLATE: Standard combination with sum constraint

```cpp
vector<vector<int>> combinationSum3(int k, int n) {
vector<vector<int>> result;      
vector<int> path;                
backtrack(k, n, 1, path, result);
return result;                   

}

void backtrack(int k, int remaining, int start,
           vector<int>& path, vector<vector<int>>& result) {
if (path.size() == k && remaining == 0) {                   
    result.push_back(path);                                 
    return;                                                 
}                                                           
if (path.size() >= k || remaining < 0) return;              

for (int i = start; i <= 9; i++) {                          
    path.push_back(i);                                      
    backtrack(k, remaining - i, i + 1, path, result);       
    path.pop_back();                                        
}                                                           

}
```

## **PART 5: PATTERN 3 - PERMUTATIONS**

### **PERMUTATIONS PATTERN**

**KEY CHARACTERISTICS:**
- Order MATTERS ([1,2] ! [2,1])
- Use each element exactly once
- N! permutations for N elements
- Need to track which elements are used

**TEMPLATE:**

```
void permBacktrack(nums, path, used, result) {
if (path.size() == nums.size()) {               
    result.add(copy of path);                   
    return;                                     
}                                               

for (int i = 0; i < nums.size(); i++) {         
    if (used[i]) continue;  // Skip already used

    used[i] = true;                             
    path.add(nums[i]);                          
    permBacktrack(nums, path, used, result);    
    path.remove_last();                         
    used[i] = false;                            
}                                               

}
```

### **PROBLEM: Permutations (LC 46)** 

 PATTERN: Basic permutation generation
 TEMPLATE: Track used elements with boolean array

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

```cpp
vector<vector<int>> permute(vector<int>& nums) {
vector<vector<int>> result;           
vector<int> path;                     
vector<bool> used(nums.size(), false);
backtrack(nums, path, used, result);  
return result;                        

}

void backtrack(vector<int>& nums, vector<int>& path,
           vector<bool>& used, vector<vector<int>>& result) {
if (path.size() == nums.size()) {                            
    result.push_back(path);                                  
    return;                                                  
}                                                            

for (int i = 0; i < nums.size(); i++) {                      
    if (used[i]) continue;                                   

    used[i] = true;                                          
    path.push_back(nums[i]);                                 
    backtrack(nums, path, used, result);                     
    path.pop_back();                                         
    used[i] = false;                                         
}                                                            

}
```

TIME: O(N x N!)
SPACE: O(N)

### **PROBLEM: Permutations II (LC 47)** 

 PATTERN: Permutations with DUPLICATES
 TEMPLATE: Sort + skip used OR skip unused duplicate at same level

KEY INSIGHT (TRICKY!):
- Sort array first
- Skip if: same as previous AND previous is not used
- This ensures we only use duplicates in order

Input: nums = [1,1,2]
Output: [[1,1,2],[1,2,1],[2,1,1]]

```cpp
vector<vector<int>> permuteUnique(vector<int>& nums) {
sort(nums.begin(), nums.end());  // Sort!
vector<vector<int>> result;              
vector<int> path;                        
vector<bool> used(nums.size(), false);   
backtrack(nums, path, used, result);     
return result;                           

}

void backtrack(vector<int>& nums, vector<int>& path,
           vector<bool>& used, vector<vector<int>>& result) { 
if (path.size() == nums.size()) {                             
    result.push_back(path);                                   
    return;                                                   
}                                                             

for (int i = 0; i < nums.size(); i++) {                       
    if (used[i]) continue;                                    

    // Skip duplicate: same as prev AND prev not used         
    if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;

    used[i] = true;                                           
    path.push_back(nums[i]);                                  
    backtrack(nums, path, used, result);                      
    path.pop_back();                                          
    used[i] = false;                                          
}                                                             

}
```

WHY !used[i-1]?
If nums[i-1] is NOT used, we're at same decision level
If nums[i-1] IS used, it's in the path (deeper level), okay to use nums[i]

### **PROBLEM: Letter Combinations of Phone (LC 17)** 

 PATTERN: Permutation-like with different choices per position
 TEMPLATE: Iterate through letters for current digit

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

```cpp
vector<string> letterCombinations(string digits) {
if (digits.empty()) return {};                               

vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl",
                          "mno", "pqrs", "tuv", "wxyz"};     
vector<string> result;                                       
string path;                                                 
backtrack(digits, 0, mapping, path, result);                 
return result;                                               

}

void backtrack(string& digits, int idx, vector<string>& mapping,
           string& path, vector<string>& result) {    
if (idx == digits.size()) {                           
    result.push_back(path);                           
    return;                                           
}                                                     

string letters = mapping[digits[idx] - '0'];          
for (char c : letters) {                              
    path.push_back(c);                                
    backtrack(digits, idx + 1, mapping, path, result);
    path.pop_back();                                  
}                                                     

}
```

## **PART 6: PATTERN 4 - GRID/MATRIX BACKTRACKING**

### **PROBLEM: Word Search (LC 79)** 

 PATTERN: DFS/Backtracking on grid
 TEMPLATE: Mark visited, explore 4 directions, unmark

**KEY INSIGHT:**
- Start DFS from each cell
- Mark cell as visited (change to '#')
- Explore 4 directions
- Restore cell (backtrack)

```cpp
bool exist(vector<vector<char>>& board, string word) {
int m = board.size(), n = board[0].size();    

for (int i = 0; i < m; i++) {                 
    for (int j = 0; j < n; j++) {             
        if (backtrack(board, word, 0, i, j)) {
            return true;                      
        }                                     
    }                                         
}                                             

return false;                                 

}

bool backtrack(vector<vector<char>>& board, string& word,
           int idx, int i, int j) {                      
// Base case: found all characters                       
if (idx == word.size()) return true;                     

// Boundary check and character match                    
if (i < 0 || i >= board.size() |                       |
    j < 0 || j >= board[0].size() |                     |
    board[i][j] != word[idx]) {                          
    return false;                                        
}                                                        

// Mark as visited                                       
char temp = board[i][j];                                 
board[i][j] = '#';                                       

// Explore 4 directions                                  
bool found = backtrack(board, word, idx + 1, i + 1, j) ||
             backtrack(board, word, idx + 1, i - 1, j) ||
             backtrack(board, word, idx + 1, i, j + 1) ||
             backtrack(board, word, idx + 1, i, j - 1);  

// Restore (backtrack)                                   
board[i][j] = temp;                                      

return found;                                            

}
```

### **PROBLEM: Word Search II (LC 212)**  HARD

 PATTERN: Backtracking + Trie for multiple words
 TEMPLATE: Build Trie from words, DFS with Trie pruning

(See Trie section for detailed solution - combines Backtracking + Trie)

## **PART 7: PATTERN 5 - CONSTRAINT SATISFACTION**

### **PROBLEM: N-Queens (LC 51)**  HARD

 PATTERN: Constraint satisfaction with backtracking
 TEMPLATE: Place queen row by row, check column and diagonals

**KEY INSIGHT:**
- Place one queen per row (guarantee row constraint)
- Track which columns are used
- Track which diagonals are used:
- Main diagonal: row - col (constant for same diagonal)
- Anti-diagonal: row + col (constant for same diagonal)

```cpp
vector<vector<string>> solveNQueens(int n) {
vector<vector<string>> result;                     
vector<string> board(n, string(n, '.'));           

set<int> cols;       // Used columns               
set<int> diag1;      // row - col                  
set<int> diag2;      // row + col                  

backtrack(0, n, board, cols, diag1, diag2, result);
return result;                                     

}

void backtrack(int row, int n, vector<string>& board,
           set<int>& cols, set<int>& diag1, set<int>& diag2, 
           vector<vector<string>>& result) {                 
// Base case: all rows filled                                
if (row == n) {                                              
    result.push_back(board);                                 
    return;                                                  
}                                                            

// Try placing queen in each column                          
for (int col = 0; col < n; col++) {                          
    // Check constraints                                     
    if (cols.count(col) |                                  |
        diag1.count(row - col) |                           |
        diag2.count(row + col)) {                            
        continue;                                            
    }                                                        

    // Place queen                                           
    board[row][col] = 'Q';                                   
    cols.insert(col);                                        
    diag1.insert(row - col);                                 
    diag2.insert(row + col);                                 

    // Recurse                                               
    backtrack(row + 1, n, board, cols, diag1, diag2, result);

    // Remove queen (backtrack)                              
    board[row][col] = '.';                                   
    cols.erase(col);                                         
    diag1.erase(row - col);                                  
    diag2.erase(row + col);                                  
}                                                            

}
```

### **PROBLEM: N-Queens II (LC 52)**  HARD

 PATTERN: Constraint satisfaction with backtracking (count only)
 TEMPLATE: Same as N-Queens but just count solutions, don't store boards

```
int totalNQueens(int n) {
int count = 0;                                                                  
set<int> cols, diag1, diag2;                                                    

function<void(int)> backtrack = [&](int row) {                                  
    if (row == n) { count++; return; }                                          

    for (int col = 0; col < n; col++) {                                         
        if (cols.count(col) || diag1.count(row - col) || diag2.count(row + col))
            continue;                                                           

        cols.insert(col); diag1.insert(row - col); diag2.insert(row + col);     
        backtrack(row + 1);                                                     
        cols.erase(col); diag1.erase(row - col); diag2.erase(row + col);        
    }                                                                           
};                                                                              

backtrack(0);                                                                   
return count;                                                                   

}
```

TIME: O(N!)  |  SPACE: O(N)

### **PROBLEM: Sudoku Solver (LC 37)**  HARD

 PATTERN: Constraint satisfaction - rows, columns, boxes
 TEMPLATE: Try each digit 1-9, validate constraints

```cpp
void solveSudoku(vector<vector<char>>& board) {
solve(board);

}

bool solve(vector<vector<char>>& board) {
for (int i = 0; i < 9; i++) {                       
    for (int j = 0; j < 9; j++) {                   
        if (board[i][j] == '.') {                   
            // Try each digit                       
            for (char c = '1'; c <= '9'; c++) {     
                if (isValid(board, i, j, c)) {      
                    board[i][j] = c;                

                    if (solve(board)) {             
                        return true;                
                    }                               

                    board[i][j] = '.';  // Backtrack
                }                                   
            }                                       
            return false;  // No valid digit found  
        }                                           
    }                                               
}                                                   
return true;  // Board is complete                  

}

bool isValid(vector<vector<char>>& board, int row, int col, char c) {
for (int i = 0; i < 9; i++) {                    
    // Check row                                 
    if (board[row][i] == c) return false;        

    // Check column                              
    if (board[i][col] == c) return false;        

    // Check 3x3 box                             
    int boxRow = 3 * (row / 3) + i / 3;          
    int boxCol = 3 * (col / 3) + i % 3;          
    if (board[boxRow][boxCol] == c) return false;
}                                                
return true;                                     

}
```

### **PROBLEM: Generate Parentheses (LC 22)** 

 PATTERN: Constraint-based backtracking
 TEMPLATE: Track open/close counts, add if valid

**KEY INSIGHT:**
- Can add '(' if open < n
- Can add ')' if close < open
- Valid when both = n

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

```cpp
vector<string> generateParenthesis(int n) {
vector<string> result;           
string path;                     
backtrack(n, 0, 0, path, result);
return result;                   

}

void backtrack(int n, int open, int close,
           string& path, vector<string>& result) {
if (path.size() == 2 * n) {                       
    result.push_back(path);                       
    return;                                       
}                                                 

if (open < n) {                                   
    path.push_back('(');                          
    backtrack(n, open + 1, close, path, result);  
    path.pop_back();                              
}                                                 

if (close < open) {                               
    path.push_back(')');                          
    backtrack(n, open, close + 1, path, result);  
    path.pop_back();                              
}                                                 

}
```

### **PROBLEM: Palindrome Partitioning (LC 131)** 

 PATTERN: Partitioning with constraint
 TEMPLATE: Try each partition point, check if palindrome

```cpp
vector<vector<string>> partition(string s) {
vector<vector<string>> result;
vector<string> path;          
backtrack(s, 0, path, result);
return result;                

}

void backtrack(string& s, int start,
           vector<string>& path, vector<vector<string>>& result) {
if (start == s.size()) {                                          
    result.push_back(path);                                       
    return;                                                       
}                                                                 

for (int end = start; end < s.size(); end++) {                    
    if (isPalindrome(s, start, end)) {                            
        path.push_back(s.substr(start, end - start + 1));         
        backtrack(s, end + 1, path, result);                      
        path.pop_back();                                          
    }                                                             
}                                                                 

}

bool isPalindrome(string& s, int left, int right) {
while (left < right) {                        
    if (s[left++] != s[right--]) return false;
}                                             
return true;                                  

}
```

NOTE: Palindrome Partitioning II (LC 132) asks for MINIMUM cuts, not all partitions.
That's a DP problem > See Dynamic Programming.txt

## **PART 8: PRUNING TECHNIQUES**

### **PRUNING = ELIMINATING INVALID BRANCHES EARLY**

**COMMON PRUNING TECHNIQUES:**

1. SORTING + SKIP DUPLICATES
- Sort array first
- if (i > start && nums[i] == nums[i-1]) continue;

2. SUM CONSTRAINT
- if (currentSum > target) return;
- Stop early when sum exceeds target

3. REMAINING ELEMENTS CHECK
- if (remaining elements < needed) return;
- Can't possibly complete the solution

4. CONSTRAINT VIOLATION
- N-Queens: Check column/diagonal before placing
- Sudoku: Check row/col/box before placing

5. SORTED + EARLY TERMINATION
- If array sorted and current > target, all future > target
- Can break loop entirely

### EXAMPLE - Combination Sum with Pruning:

```cpp
void backtrack(vector<int>& candidates, int remaining, int start,
           vector<int>& path, vector<vector<int>>& result) {          
if (remaining == 0) {                                                 
    result.push_back(path);                                           
    return;                                                           
}                                                                     

for (int i = start; i < candidates.size(); i++) {                     
    // PRUNING: if sorted and current > remaining, break              
    if (candidates[i] > remaining) break;                             

    path.push_back(candidates[i]);                                    
    backtrack(candidates, remaining - candidates[i], i, path, result);
    path.pop_back();                                                  
}                                                                     

}
```

## **PART 9: PATTERN RECOGNITION GUIDE**

```
+-----------------------------------------------------------------------------+
|                    BACKTRACKING PATTERN SELECTION                           |
+--------------------------+--------------------------------------------------+
| Problem Type             | Key Characteristics                              |
+--------------------------+--------------------------------------------------+
| SUBSETS                  | * Order doesn't matter                           |
|                          | * Every state is valid                           |
|                          | * use start index, i+1 for next                  |
|                          | * 2^n results                                    |
+--------------------------+--------------------------------------------------+
| COMBINATIONS             | * Order doesn't matter                           |
|                          | * Fixed size k                                   |
|                          | * use start index, i+1 for next                  |
|                          | * C(n,k) results                                 |
+--------------------------+--------------------------------------------------+
| PERMUTATIONS             | * Order MATTERS                                  |
|                          | * Use each element once                          |
|                          | * use 'used' array, start from 0                 |
|                          | * n! results                                     |
+--------------------------+--------------------------------------------------+
| GRID/WORD SEARCH         | * Mark cell visited                              |
|                          | * Explore 4/8 directions                         |
|                          | * Unmark on backtrack                            |
+--------------------------+--------------------------------------------------+
| CONSTRAINT SATISFACTION  | * Try values, check validity                     |
| (N-Queens, Sudoku)       | * Multiple constraints to track                  |
|                          | * Backtrack when stuck                           |
+--------------------------+--------------------------------------------------+

+-----------------------------------------------------------------------------+
|                         QUICK DECISION GUIDE                                |
+-----------------------------------------------------------------------------+
|                                                                             |
|  Q: Can elements be REUSED?                                                 |
|     YES > use 'i' in recursive call                                         |
|     NO  > use 'i+1' in recursive call                                       |
|                                                                             |
|  Q: Are there DUPLICATES in input?                                          |
|     YES > Sort + skip (i > start && nums[i] == nums[i-1])                   |
|     NO  > No special handling needed                                        |
|                                                                             |
|  Q: Does ORDER matter?                                                      |
|     YES > Permutation (use 'used' array)                                    |
|     NO  > Subset/Combination (use 'start' index)                            |
|                                                                             |
|  Q: Fixed SIZE result?                                                      |
|     YES > Combination (base case: size == k)                                |
|     NO  > Subset (add at every step)                                        |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
              **PART 10: PROBLEM LIST BY CATEGORY**                            
===============================================================================
```

**SUBSETS:**
Y 78.  Subsets 
Y 90.  Subsets II (with duplicates) 

**COMBINATIONS:**
Y 77.  Combinations 
Y 39.  Combination Sum (reuse allowed) 
Y 40.  Combination Sum II (no reuse, duplicates) 
Y 216. Combination Sum III
- 377. Combination Sum IV (DP problem, not backtracking)

**PERMUTATIONS:**
Y 46.  Permutations 
Y 47.  Permutations II (with duplicates) 
Y 17.  Letter Combinations of Phone Number 
- 31.  Next Permutation (not backtracking - array manipulation)

**GRID BACKTRACKING:**
Y 79.  Word Search 
- 212. Word Search II  (Backtracking + Trie)

**CONSTRAINT SATISFACTION:**
Y 51.  N-Queens  HARD
- 52.  N-Queens II
Y 37.  Sudoku Solver  HARD
Y 22.  Generate Parentheses 
Y 131. Palindrome Partitioning 

**OTHER BACKTRACKING:**
- 93.  Restore IP Addresses 
- 291. Word Pattern II 
- 282. Expression Add Operators  HARD
- 140. Word Break II 

```
+-----------------------------------------------------------------------------+
|                         GOLDEN RULES - MEMORIZE!                            |
+-----------------------------------------------------------------------------+
|                                                                             |
|  1⃣  Backtracking = DFS + UNDO (make choice, explore, unmake choice)        |
|                                                                             |
|  2⃣  Subsets: add state at every step, use i+1                              |
|                                                                             |
|  3⃣  Combinations: add when size == k, use i+1                              |
|                                                                             |
|  4⃣  Permutations: add when size == n, use 'used' array                     |
|                                                                             |
|  5⃣  Duplicates: SORT first, then skip (i > start && same as prev)          |
|                                                                             |
|  6⃣  Reuse allowed: use 'i' not 'i+1' in recursive call                     |
|                                                                             |
|  7⃣  Grid backtracking: mark visited, explore, unmark                       |
|                                                                             |
|  8⃣  Always PRUNE early to avoid TLE!                                       |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                        INTERVIEW CHEAT CODES                                |
+-----------------------------------------------------------------------------+
|                                                                             |
|   "This is a backtracking problem because we need to find ALL valid         |
|      combinations/permutations/subsets."                                    |
|                                                                             |
|   "I'll use a start index to avoid duplicates since order doesn't           |
|      matter in combinations."                                               |
|                                                                             |
|   "Since order matters, I'll use a 'used' array to track which              |
|      elements are already in the current permutation."                      |
|                                                                             |
|   "I'll sort first and skip duplicates to handle the duplicate              |
|      elements in the input."                                                |
|                                                                             |
|   "I'll prune early when the current sum exceeds the target to              |
|      avoid exploring invalid branches."                                     |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
                                   END                                         
===============================================================================
```
