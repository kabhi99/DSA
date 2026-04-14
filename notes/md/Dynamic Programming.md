# **DYNAMIC PROGRAMMING - COMPLETE GUIDE**

Master the 10 Core Patterns - From Beginner to Expert!

### **TABLE OF CONTENTS**

1. DP Fundamentals - What, When, Why
2. Top-Down vs Bottom-Up
3. ⚡ HOW TO IDENTIFY BASE CASES ⚡ (4 Strategies)
4. ⚡ HOW TO CONVERT TOP-DOWN TO BOTTOM-UP ⚡ (7-Step Process)

**CORE PATTERNS (5):**
5.  Pattern 1: Minimum/Maximum Path to Reach Target
6.  Pattern 2: Distinct Ways
7.  Pattern 3: Merging Intervals
8.  Pattern 4: DP on Strings
9.  Pattern 5: Decision Making

**ADDITIONAL PATTERNS (5):**
10.  Pattern 6: LIS (Longest Increasing Subsequence)  NEW
11.  Pattern 7: Kadane's Algorithm (Max Subarray)  NEW
12.  Pattern 8: Tree DP  NEW
13.  Pattern 9: Bitmask DP  NEW
14.  Pattern 10: Digit DP  NEW

15. How to Identify DP Problems (Decision Flowchart)
16. Common Mistakes & Space Optimization
17. Problem List by Pattern

## **PART 1: DP FUNDAMENTALS**

### **WHAT IS DYNAMIC PROGRAMMING?**

**DEFINITION:**
Solving complex problems by breaking them into simpler subproblems,
storing results to avoid recomputation.

 **MEMORY AID**: "**D**on't **R**epeat, **R**euse" (DP = Don't Repeat, Reuse!)

**CORE IDEA:**
Recursion + Memoization = Dynamic Programming

**THE MAGIC:**
Overlapping Subproblems + Optimal Substructure = DP Solution!

### **WHEN TO USE DP?** 

**STRONG SIGNALS:**

 "Find maximum/minimum value"
 "Count number of ways"
 "Is it possible to..."
 Optimal substructure (optimal solution contains optimal subsolutions)
 Overlapping subproblems (same calculation multiple times)

**KEYWORDS:**
- "Maximize/minimize"
- "Count all possible ways"
- "Longest/shortest"
- "Can we achieve..."
- "Optimal solution"

### **⚡ QUICK PATTERN DECISION FLOWCHART ⚡**

### START HERE: What does the problem ask?

```
+-----------------------------------------------------------------------------+
| "MINIMUM/MAXIMUM cost/path/value to reach target"                           |
|  > PATTERN 1: Min/Max Path                                                  |
|    dp[i] = min(dp[i-k]) + cost                                              |
|    Examples: Coin Change (min coins), Min Path Sum, Climbing Stairs (cost)  |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "COUNT number of ways / distinct paths"                                     |
|  > PATTERN 2: Distinct Ways                                                 |
|    dp[i] = sum(dp[i-k])                                                     |
|    Examples: Climbing Stairs (ways), Unique Paths, Coin Change II           |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "MERGE/SPLIT ranges optimally" or "Partition array"                         |
|  > PATTERN 3: Merging Intervals                                             |
|    dp[i][j] = best(dp[i][k] + dp[k+1][j])                                   |
|    Examples: Burst Balloons, Matrix Chain, Palindrome Partition             |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "COMPARE two strings" or "Single string palindrome"                         |
|  > PATTERN 4: DP on Strings                                                 |
|    if match: dp[i][j] = dp[i-1][j-1] + ...                                  |
|    Examples: LCS, Edit Distance, Longest Palindrome Subsequence             |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "TAKE or SKIP each item" (0/1 constraint, can't take adjacent)              |
|  > PATTERN 5: Decision Making                                               |
|    dp[i] = max(take + dp[i-2], skip + dp[i-1])                              |
|    Examples: House Robber, 0/1 Knapsack, Stock Buy/Sell                     |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "LONGEST INCREASING subsequence" or chain/nesting problems                  |
|  > PATTERN 6: LIS                                                           |
|    dp[i] = max(dp[j] + 1) where nums[j] < nums[i]                           |
|    Examples: LIS, Russian Dolls, Longest String Chain                       |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "MAX/MIN CONTIGUOUS subarray sum/product"                                   |
|  > PATTERN 7: Kadane's                                                      |
|    curr = max(nums[i], curr + nums[i])                                      |
|    Examples: Max Subarray, Max Product Subarray, Circular Max               |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Problem on TREE structure" (path sum, diameter, subtree)                   |
|  > PATTERN 8: Tree DP                                                       |
|    Post-order DFS, return info to parent                                    |
|    Examples: Max Path Sum, Diameter, House Robber III                       |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Small N < 20" and track which items visited/selected (subset tracking)     |
|  > PATTERN 9: Bitmask DP                                                    |
|    dp[mask] = answer for subset                                             |
|    Examples: TSP, Partition to K Subsets, Shortest Path Visiting All        |
+-----------------------------------------------------------------------------+
                              v if not...                                      
+-----------------------------------------------------------------------------+
| "Count numbers in range [L, R] with digit property"                         |
|  > PATTERN 10: Digit DP                                                     |
|    Build digit by digit with tight bound                                    |
|    Examples: Numbers with Repeated Digits, Count of Integers                |
+-----------------------------------------------------------------------------+
```

**TWO KEY PROPERTIES:**

1. **Optimal Substructure**
Solution to problem can be constructed from solutions to subproblems
Example: Shortest path A>C = min(A>B + B>C, A>D + D>C)

2. **Overlapping Subproblems**
Same subproblems solved multiple times
Example: fibonacci(5) calls fibonacci(3) multiple times

### **WHY DP WORKS - FIBONACCI EXAMPLE**

### NAIVE RECURSION (Exponential Time):

```
int fib(int n) {
if (n <= 1) return n;                                    
return fib(n-1) + fib(n-2);  // Recalculates same values!

}
```

TIME: O(2^N) - Every call spawns 2 more calls
SPACE: O(N) - Recursion depth

VISUALIZATION - fib(5):
```
fib(5)
```

/      \
```
fib(4)      fib(3)
```

/     \      /     \
```
fib(3)  fib(2) fib(2) fib(1)
```

/   \    /  \   /  \
```
fib(2) fib(1) ...
```

Notice: fib(3) computed twice, fib(2) computed 3 times!

### TOP-DOWN DP (Memoization):

```cpp
int fib(int n, vector<int>& memo) {
if (n <= 1) return n;                                   
if (memo[n] != -1) return memo[n];  // Already computed!

return memo[n] = fib(n-1, memo) + fib(n-2, memo);       

}
```

TIME: O(N) - Each subproblem computed once
SPACE: O(N) - Memo array + recursion stack

### BOTTOM-UP DP (Tabulation):

```cpp
int fib(int n) {
if (n <= 1) return n;         

vector<int> dp(n + 1);        
dp[0] = 0;                    
dp[1] = 1;                    

for (int i = 2; i <= n; i++) {
    dp[i] = dp[i-1] + dp[i-2];
}                             

return dp[n];                 

}
```

TIME: O(N)
SPACE: O(N)

```
+-----------------------------------------------------------------------------+
|                 TABULATION SIZE QUICK REFERENCE                             |
+-----------------------------+-----------------------------------------------+
| Recursive parameter range   | Table size                                    |
+-----------------------------+-----------------------------------------------+
| 0 to amount                 | amount + 1                                    |
| 0 to n                      | n + 1                                         |
| 0 to n-1                    | n                                             |
| 1 to n                      | n + 1 (index 0 unused or base case)           |
+-----------------------------+-----------------------------------------------+
```

 RULE: If final answer is dp[X], vector needs size X + 1.
```
dp[0] always holds the BASE CASE value from recursion.
```

**SPACE-OPTIMIZED:**

```
int fib(int n) {
if (n <= 1) return n;         

int prev2 = 0, prev1 = 1;     
for (int i = 2; i <= n; i++) {
    int curr = prev1 + prev2; 
    prev2 = prev1;            
    prev1 = curr;             
}                             
return prev1;                 

}
```

TIME: O(N)
SPACE: O(1) Y

## **PART 2: TOP-DOWN vs BOTTOM-UP**

### **COMPARISON**

```
+------------------+----------------------+----------------------+
| Aspect           | Top-Down (Memo)      | Bottom-Up (Tabulation|
+------------------+----------------------+----------------------+
| Approach         | Recursion + Cache    | Iteration + Table    |
| Direction        | Problem > Base       | Base > Problem       |
| Intuition        | More natural         | Requires thinking    |
| Space            | Stack + Memo         | Just table           |
| Speed            | Slightly slower      | Slightly faster      |
| Subproblems      | Only needed ones     | All subproblems      |
| Easier to write  | Yes Y                | Requires practice    |
+------------------+----------------------+----------------------+
```

 **MEMORY AID**:
**T**op-Down = **T**hink recursively first
**B**ottom-Up = **B**uild table from base

### **WHEN TO USE WHICH?**

**USE TOP-DOWN WHEN:**
 Problem has natural recursive structure
 Not all subproblems are needed
 Easier to think recursively
 Interview setting (faster to code)

**USE BOTTOM-UP WHEN:**
 Need to optimize space
 Recursion depth might overflow
 Want maximum performance
 All subproblems needed anyway

**RECOMMENDATION:**
Start with Top-Down (easier to think), convert to Bottom-Up if needed!

## **HOW TO IDENTIFY BASE CASES**  (CRITICAL SKILL!)

This is where most people get stuck! Here's the systematic approach:

### **STRATEGY 1: Ask "When Does Recursion Stop?"**

BASE CASE = Simplest subproblem you can answer WITHOUT recursion!

### EXAMPLE: Fibonacci

Question: When can I answer immediately?
```
fib(0) = 0  (by definition)
fib(1) = 1  (by definition)
```

These are base cases!

```
int fib(int n) {
if (n <= 1) return n;  //  Base case
return fib(n-1) + fib(n-2);         

}
```

### EXAMPLE: Climbing Stairs

Question: What are trivial cases?
```
stairs = 0 > 0 ways (or 1 way: don't move)
stairs = 1 > 1 way (one step)
stairs = 2 > 2 ways (1+1 or 2)

int climbStairs(int n) {
if (n <= 2) return n;  //  Base cases
...                                  

}
```

### **STRATEGY 2: Identify "Invalid" vs "Valid" Base Cases**

**TWO TYPES:**
1. **Valid base** > Return meaningful answer
2. **Invalid base** > Return impossible value

### EXAMPLE: Coin Change

```
int coinChange(int amount) {
if (amount == 0) return 0;      //  Valid: 0 coins needed
if (amount < 0) return INT_MAX; //  Invalid: impossible  
...                                                      

}
```

For MIN problems:
Valid base > return 0 or specific value
Invalid > return INT_MAX or amount+1

For COUNT problems:
Valid base > return 1 (one way)
Invalid > return 0 (no ways)

### **STRATEGY 3: Base Case Patterns by Problem Type**

```
+------------------------+------------------+----------------------+
| Problem Type           | Base Case        | Value                |
+------------------------+------------------+----------------------+
| Min/Max Path           | target == 0      | 0                    |
|                        | target < 0       | INT_MAX (impossible) |
+------------------------+------------------+----------------------+
| Count Ways             | target == 0      | 1 (one way)          |
|                        | target < 0       | 0 (no ways)          |
+------------------------+------------------+----------------------+
| DP on Strings (2D)     | i == 0 or j == 0 | 0 or i or j          |
+------------------------+------------------+----------------------+
| Decision Making        | i == 0           | arr[0] or 0          |
| (House Robber)         | i == 1           | max(arr[0], arr[1])  |
+------------------------+------------------+----------------------+
| Merging Intervals      | i == j           | 0                    |
|                        | length == 1      | arr[i]               |
+------------------------+------------------+----------------------+
```

 **MEMORY AID**:
"**Z**ero target, **Z**ero or one base"
(Target 0 usually returns 0 for min/max, 1 for count)

### **STRATEGY 4: Work Backwards from Small Examples**

TECHNIQUE: Manually solve for n=0, 1, 2 > These become base cases!

### EXAMPLE: Unique Paths (mxn grid)

Draw small grids:

1x1 grid: 1 way (already there)
1xn grid: 1 way (only move right)
mx1 grid: 1 way (only move down)

Base cases:
```
dp[i][0] = 1  (first column)
dp[0][j] = 1  (first row)
```

### EXAMPLE: Longest Common Subsequence

What if one string is empty?
```
LCS("abc", "") = 0
LCS("", "xyz") = 0
```

Base cases:
```
dp[0][j] = 0
dp[i][0] = 0
```

## **HOW TO CONVERT TOP-DOWN TO BOTTOM-UP**  (STEP-BY-STEP!)

This is an art! Here's the systematic 7-step process:

### **THE 7-STEP CONVERSION PROCESS**

STEP 1: Identify the states (parameters that change)
STEP 2: Create DP table with those dimensions
STEP 3: Identify base cases from recursion
STEP 4: Determine iteration order (dependencies!)
STEP 5: Convert recurrence relation
STEP 6: Return final answer
STEP 7: (Optional) Optimize space

Let's see this with COMPLETE EXAMPLES!

### **EXAMPLE 1: Fibonacci (Simple 1D)**

**TOP-DOWN:**

```cpp
int fib(int n, vector<int>& memo) {
if (n <= 1) return n;                    // < Base case
if (memo[n] != -1) return memo[n];                     

return memo[n] = fib(n-1, memo) + fib(n-2, memo);      
                 // ^ Recurrence relation              

}
```

**CONVERSION STEPS:**

STEP 1: States > Just "n" (1 parameter)
STEP 2: DP table > vector<int> dp(n+1)
STEP 3: Base cases > dp[0] = 0, dp[1] = 1
STEP 4: Order > i from 2 to n (depends on i-1, i-2, so build forward)
STEP 5: Recurrence > dp[i] = dp[i-1] + dp[i-2]
STEP 6: Return > dp[n]

**BOTTOM-UP:**

```cpp
int fib(int n) {
if (n <= 1) return n;                            

vector<int> dp(n + 1);                           
dp[0] = 0;  // Base                              
dp[1] = 1;  // Base                              

for (int i = 2; i <= n; i++) {  // Order: forward
    dp[i] = dp[i-1] + dp[i-2];  // Recurrence    
}                                                

return dp[n];  // Answer                         

}
```

### STEP 7: Space optimization > Only need prev2 and prev1!

```
int fib(int n) {
if (n <= 1) return n;         
int prev2 = 0, prev1 = 1;     
for (int i = 2; i <= n; i++) {
    int curr = prev1 + prev2; 
    prev2 = prev1;            
    prev1 = curr;             
}                             
return prev1;                 

}
```

### **EXAMPLE 2: Coin Change (1D with Loop)**

**TOP-DOWN:**

```cpp
int coinChange(int amount, vector<int>& coins, vector<int>& memo) {
if (amount == 0) return 0;           // < Base: valid      
if (amount < 0) return INT_MAX;      // < Base: invalid    
if (memo[amount] != -1) return memo[amount];               

int result = INT_MAX;                                      
for (int coin : coins) {                                   
    int subResult = coinChange(amount - coin, coins, memo);
    if (subResult != INT_MAX) {                            
        result = min(result, subResult + 1);               
    }                                                      
}                                                          

return memo[amount] = result;                              

}
```

**CONVERSION STEPS:**

STEP 1: States > amount (1 parameter)
STEP 2: DP table > vector<int> dp(amount+1)
STEP 3: Base > dp[0] = 0, others = amount+1 (impossible value)
STEP 4: Order > i from 1 to amount (depends on smaller amounts)
STEP 5: Recurrence > dp[i] = min(dp[i], dp[i-coin] + 1) for each coin
STEP 6: Return > dp[amount] > amount ? -1 : dp[amount]

**BOTTOM-UP:**

```cpp
int coinChange(vector<int>& coins, int amount) {
vector<int> dp(amount + 1, amount + 1);  // Init with impossible  
dp[0] = 0;  // Base case                                          

for (int i = 1; i <= amount; i++) {      // Build from 1 to amount
    for (int coin : coins) {                                      
        if (coin <= i) {                                          
            dp[i] = min(dp[i], dp[i - coin] + 1);                 
        }                                                         
    }                                                             
}                                                                 

return dp[amount] > amount ? -1 : dp[amount];                     

}
```

 **KEY INSIGHT**:
Top-Down goes amount > 0 (recursive)
Bottom-Up goes 0 > amount (iterative)
Same logic, opposite direction!

### **EXAMPLE 3: Longest Common Subsequence (2D)**

**TOP-DOWN:**

```cpp
int lcs(string& s1, string& s2, int i, int j, vector<vector<int>>& memo) {
if (i == 0 || j == 0) return 0;  // < Base: empty string
if (memo[i][j] != -1) return memo[i][j];                

if (s1[i-1] == s2[j-1]) {                               
    return memo[i][j] = 1 + lcs(s1, s2, i-1, j-1, memo);
} else {                                                
    return memo[i][j] = max(lcs(s1, s2, i-1, j, memo),  
                            lcs(s1, s2, i, j-1, memo)); 
}                                                       

}
```

**CONVERSION STEPS:**

STEP 1: States > i, j (2 parameters)
STEP 2: DP table > vector<vector<int>> dp(m+1, vector<int>(n+1))
STEP 3: Base > dp[0][j] = 0, dp[i][0] = 0 (empty string)
STEP 4: Order > i from 1 to m, j from 1 to n (depends on i-1, j-1)
STEP 5: Recurrence >
```
    if (s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1] + 1
    else dp[i][j] = max(dp[i-1][j], dp[i][j-1])        
```

STEP 6: Return > dp[m][n]

**BOTTOM-UP:**

```cpp
int longestCommonSubsequence(string text1, string text2) {
int m = text1.size(), n = text2.size();                           
vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));             

// Base cases already initialized (0s)                            

for (int i = 1; i <= m; i++) {           // Build row by row      
    for (int j = 1; j <= n; j++) {       // Build column by column
        if (text1[i-1] == text2[j-1]) {                           
            dp[i][j] = dp[i-1][j-1] + 1;                          
        } else {                                                  
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);               
        }                                                         
    }                                                             
}                                                                 

return dp[m][n];                                                  

}
```

### STEP 7: Space optimization > Only need previous row!

```cpp
int longestCommonSubsequence(string text1, string text2) {
int m = text1.size(), n = text2.size();   
vector<int> dp(n + 1, 0);                 

for (int i = 1; i <= m; i++) {            
    int prev = 0;  // This is dp[i-1][j-1]
    for (int j = 1; j <= n; j++) {        
        int temp = dp[j];                 
        if (text1[i-1] == text2[j-1]) {   
            dp[j] = prev + 1;             
        } else {                          
            dp[j] = max(dp[j], dp[j-1]);  
        }                                 
        prev = temp;                      
    }                                     
}                                         

return dp[n];                             

}
```

### **CRITICAL: DETERMINING ITERATION ORDER** 

This is THE trickiest part! Follow dependencies!

RULE: Compute smaller subproblems BEFORE larger ones.

### EXAMPLE 1: Fibonacci

```
fib(n) depends on fib(n-1) and fib(n-2)
```

> Compute smaller n first
> Loop: for (i = 0 to n) Y

### EXAMPLE 2: Unique Paths

```
dp[i][j] depends on dp[i-1][j] and dp[i][j-1]
```

> Need previous row and previous column
> Loop: for (i = 0 to m) { for (j = 0 to n) } Y

### EXAMPLE 3: Merging Intervals (TRICKY!)

```
dp[i][j] depends on dp[i][k] and dp[k+1][j] for i < k < j
```

> Need SMALLER intervals first!
> Loop by LENGTH (not position!):
```
for (length = 1 to n) {        
    for (i = 0 to n-length) {  
        j = i + length;        
        // Now compute dp[i][j]
    }                          
}                              
```

 **CRITICAL INSIGHT**:
For interval problems, ALWAYS loop by length first!
This ensures smaller intervals computed before larger ones.

### **COMMON CONVERSION MISTAKES** 

### MISTAKE 1: Wrong iteration direction

```
 for (i = n down to 0)  // If you need i-1!
 for (i = 0 to n)        // Compute smaller first
```

Check dependencies! Draw on paper if needed.

### MISTAKE 2: Off-by-one in array access

Top-Down uses s1[i-1] when i is from (1 to n)
Bottom-Up must do same!

```
 if (s1[i] == s2[j])     // Wrong!
 if (s1[i-1] == s2[j-1]) // Correct!
```

### MISTAKE 3: Forgetting to initialize base cases

In Top-Down, you return base case.
In Bottom-Up, you MUST initialize it!

```
 dp[0] = 0;  // Don't forget!
```

MISTAKE 4: Not handling edge cases
### if (n <= 1) return n;  // Handle before loop!

**PRACTICE: Try Converting These!**
### TOP-DOWN House Robber:

```cpp
int rob(int i, vector<int>& nums, vector<int>& memo) {
if (i < 0) return 0;                                 
if (i == 0) return nums[0];                          
if (memo[i] != -1) return memo[i];                   

return memo[i] = max(rob(i-1, nums, memo),           
                     rob(i-2, nums, memo) + nums[i]);

}
```

YOUR TASK: Convert to Bottom-Up!

SOLUTION: (See Pattern 5 in the notes above)

### **VISUAL GUIDE: Understanding Iteration Order** 

EXAMPLE: Unique Paths (2D DP)

### DEPENDENCIES: dp[i][j] depends on dp[i-1][j] and dp[i][j-1]

Visualize the grid:
```
j=0  j=1  j=2  j=3

i=0   1    1    1    1
```

v    v    v    v

```
i=1   1  < ?
```

v

```
i=2   1
```

v

```
i=3   1
```

To compute dp[1][1]:
Need dp[0][1] (above) < Must compute first!
Need dp[1][0] (left)  < Must compute first!

Iteration order:
```
for (i = 1 to m):      // Row by row
  for (j = 1 to n):  // Column by column
      dp[i][j] = dp[i-1][j] + dp[i][j-1]
                   ^            ^       
                above         left      
            (already computed!)         
```

**WRONG ORDER EXAMPLE:**

```
 for (i = m down to 0):  // Computing larger first!
  for (j = n down to 0):                
      dp[i][j] = dp[i-1][j] + dp[i][j-1]
                   ^            ^       
              NOT computed yet! BUG!    
```

### **ITERATION ORDER PATTERNS** 

### Pattern Type          Dependency            Iteration Order

1D (Fibonacci)        dp[i-1], dp[i-2]      for (i = 0 to n) >

2D (Paths)            dp[i-1][j]            for (i = 0 to m)
```
dp[i][j-1]              for (j = 0 to n)
```

Intervals             dp[i][k], dp[k+1][j]  for (len = 1 to n)
(smaller intervals)     for (i = 0 to n-len)
```
j = i + len
```

Strings (Match)       dp[i-1][j-1]          for (i = 1 to m)
```
dp[i-1][j]              for (j = 1 to n)
dp[i][j-1]
```

Palindrome            dp[i+1][j-1]          for (len = 1 to n)
(one string)          (inner substring)       for (i = 0 to n-len)
```
j = i + len
```

 **GOLDEN RULE**:
Draw dependency arrows > iterate so arrows point to ALREADY computed!

### **COMPLETE CONVERSION EXAMPLE: House Robber**

STEP-BY-STEP with all details:

**TOP-DOWN VERSION:**

```cpp
int rob(vector<int>& nums) {
vector<int> memo(nums.size(), -1);         
return helper(nums.size() - 1, nums, memo);

}

int helper(int i, vector<int>& nums, vector<int>& memo) {
// STEP 1: Identify base cases                       
if (i < 0) return 0;           // No houses left     
if (i == 0) return nums[0];    // Only one house     

if (memo[i] != -1) return memo[i];                   

// STEP 2: Identify recurrence                       
// Option 1: Rob current house (can't rob i-1)       
int robCurrent = nums[i] + helper(i - 2, nums, memo);

// Option 2: Don't rob current (can rob i-1)         
int skipCurrent = helper(i - 1, nums, memo);         

return memo[i] = max(robCurrent, skipCurrent);       

}
```

**ANALYZE:**
- States: i (position in array)
- Base: i < 0 > 0, i == 0 > nums[0]
- Recurrence: max(nums[i] + dp[i-2], dp[i-1])
- Direction: n > 0 (recursive)

**CONVERT TO BOTTOM-UP:**

```cpp
int rob(vector<int>& nums) {
int n = nums.size();                              
if (n == 0) return 0;                             
if (n == 1) return nums[0];  // STEP 3: Edge cases

// STEP 2: Create DP table                        
vector<int> dp(n);                                

// STEP 3: Initialize base cases                  
dp[0] = nums[0];                                  
dp[1] = max(nums[0], nums[1]);                    

// STEP 4: Determine order (forward! 0 > n)       
for (int i = 2; i < n; i++) {                     
    // STEP 5: Convert recurrence                 
    dp[i] = max(nums[i] + dp[i-2], dp[i-1]);      
}                                                 

// STEP 6: Return answer                          
return dp[n-1];                                   

}
```

###  **INDEX SHIFT: WHY dp IS SIZE n? CAN WE USE n+1?**

In recursion, base case is: if (i < 0) return 0
But arrays can't have index -1! Two choices:

### APPROACH 1 (size n) - Direct mapping, handle edges manually:

```
rob(i) > dp[i]     (same index)

rob(-1) = 0  > CAN'T STORE! So handle dp[0], dp[1] manually:
dp[0] = nums[0]                        // rob(0) = nums[0]
dp[1] = max(nums[0], nums[1])          // rob(1) needs rob(-1)=0, done by hand
```

Loop: dp[i] = max(dp[i-1], dp[i-2] + nums[i])
Answer: dp[n-1]

 PROBLEM: Need if(n==0), if(n==1) edge cases before the loop.

### APPROACH 2 (size n+1) - Shift by +1, base case fits naturally:

SHIFT:  dp[i+1] = rob(i)     (every index moves right by 1)

```
rob(-1)=0  > dp[0] = 0     < NOW IT FITS! Index 0 = "no houses"
rob(0)     > dp[1] = nums[0]
rob(1)     > dp[2] = max(nums[0], nums[1])
rob(i)     > dp[i+1]
```

Recurrence after shift:
```
rob(i) = max(rob(i-1), rob(i-2) + nums[i])
dp[i+1] = max(dp[i], dp[i-1] + nums[i])
```

But we loop with i from 2 to n (dp indices), so substitute:
```
dp[i] = max(dp[i-1], dp[i-2] + nums[i-1])
```

^
INDEX SHIFT: nums[i-1] not nums[i]
because dp[i] = rob(i-1), so house index = i-1

Answer: dp[n]

 NO edge cases needed! dp[0]=0 and dp[1]=nums[0] handle everything.

**SIDE BY SIDE:**

SIZE n (direct):                    SIZE n+1 (shifted):
-----------------                   ------------------
```
if (n==0) return 0;     < extra    // no edge cases needed!
if (n==1) return nums[0]; < extra
dp(n)                               dp(n+1, 0)
dp[0] = nums[0]                     dp[0] = 0    < "no houses"
dp[1] = max(nums[0],nums[1])        dp[1] = nums[0]
```

for i=2 to n-1:                     for i=2 to n:
```
dp[i]=max(dp[i-1],                  dp[i]=max(dp[i-1],
dp[i-2]+nums[i])                    dp[i-2]+nums[i-1])

return dp[n-1]                       return dp[n]
```

^ nums[i-1] is the only change

### CODE (n+1 approach):

```cpp
int rob(vector<int>& nums) {
int n = nums.size();                          
vector<int> dp(n + 1, 0);                     
dp[1] = nums[0];                              

for (int i = 2; i <= n; i++) {                
    dp[i] = max(dp[i-1], dp[i-2] + nums[i-1]);
}                                             

return dp[n];                                 

}
```

WHY nums[i-1]? Because dp[i] means "best answer for first i houses",
so the i-th house (1-indexed) is at nums[i-1] (0-indexed array).

###  **CAN YOU ALWAYS USE n+1?** YES!

The n+1 approach works for ANY DP problem. Benefits:
 Base case (empty/zero state) always fits at dp[0]
 No if(n==0), if(n==1) edge cases
 Consistent pattern across all problems
 Matches how LCS, Edit Distance, Coin Change already work

The ONLY thing to remember:
```
dp[i] represents "first i elements", so element index = i-1
```

> Use nums[i-1], text[i-1], etc. in the loop

Problems that ALREADY use n+1 naturally:
Coin Change:   dp[0]=0 means "amount 0 needs 0 coins"
LCS:           dp[0][j]=0 means "empty string has LCS 0"
Edit Distance: dp[0][j]=j means "insert j chars into empty"
Climbing Stairs: dp[0]=1 means "1 way to stay at ground"

Problems where n+1 is OPTIONAL (both work):
House Robber, Stock Buy/Sell, Delete and Earn
> Direct mapping (size n) also works fine since dp[0] = nums[0]
is already meaningful, but n+1 removes edge cases.

### STEP 7: Space Optimization (only need last 2 values):

```cpp
int rob(vector<int>& nums) {
int prev2 = 0;                         
int prev1 = 0;                         

for (int num : nums) {                 
    int curr = max(prev1, prev2 + num);
    prev2 = prev1;                     
    prev1 = curr;                      
}                                      

return prev1;                          

}
```

 **BEAUTIFUL**: O(N) time, O(1) space!

### **QUICK CHECKLIST FOR CONVERSION** 

Converting Top-Down to Bottom-Up? Check these:

o Identified all changing parameters > DP table dimensions
o Found base cases from recursion > Initialize DP
o Determined correct iteration order > Check dependencies!
o Converted recurrence relation > Same logic
o Handled edge cases (empty input, n=0, etc.)
o Return correct value > dp[final_state]
o (Optional) Optimized space > Keep only needed values

 **PRO TIP**:
Write Top-Down first (easier to think).
Then convert to Bottom-Up mechanically using these 7 steps!

## **PATTERN 1: MINIMUM/MAXIMUM PATH TO REACH TARGET** 

```
+-----------------------------------------------------------------------------+
| SUBCATEGORIES:                                                              |
|   1.1 Basic Target (Coin Change, Climbing Stairs)                           |
|   1.2 Grid-based (Min Path Sum, Triangle)                                   |
|   1.3 Kadane's (Max Subarray - special case)                                |
+-----------------------------------------------------------------------------+
```

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Minimum cost to reach..."
- "Shortest path to..."
- "Maximum sum/profit to achieve..."
- "Least operations to..."
- "Fewest steps to..."

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "To reach state i optimally, I need to come from the BEST          |
|   previous state and add my current cost."                          |
|                                                                     |
|   dp[i] = BEST(dp[previous states]) + cost_to_reach_i               |
+---------------------------------------------------------------------+
```

**MENTAL MODEL:**
Think of it as: "I'm standing at position i. What's the cheapest way
I could have arrived here?" Look back at all possible previous positions.

### ** UNIVERSAL TEMPLATE**

**STATE DEFINITION:**
```
dp[i] = minimum/maximum cost to reach target i
```

**RECURRENCE:**
```
dp[i] = min/max(dp[i-k] for all valid transitions k) + cost[i]
```

**BASE CASE:**
```
dp[0] = 0 (no cost to reach starting point)
```

**INVALID STATE:**
Return INT_MAX (for min) or INT_MIN (for max)

**TEMPLATE:**

```cpp
int solve(int target, vector<int>& options) {
vector<int> dp(target + 1, INT_MAX);  // or amount+1 to avoid overflow
dp[0] = 0;                                                            

for (int i = 1; i <= target; i++) {                                   
    for (int opt : options) {                                         
        if (opt <= i && dp[i - opt] != INT_MAX) {                     
            dp[i] = min(dp[i], dp[i - opt] + cost);                   
        }                                                             
    }                                                                 
}                                                                     

return dp[target] == INT_MAX ? -1 : dp[target];                       

}
```

### ** COMMON PITFALLS**

 PITFALL 1: Using INT_MAX directly
```
dp[i] = INT_MAX;
dp[i] = min(dp[i], dp[j] + 1);  // OVERFLOW when dp[j] = INT_MAX!
```

 FIX: Use amount+1 or check before adding

 PITFALL 2: Wrong base case for MAX problems
For MAX: dp[0] might be 0 or negative depending on problem

 PITFALL 3: Forgetting impossible cases
Always return -1 or handle when target is unreachable

### **1.1 SUBCATEGORY: BASIC TARGET PROBLEMS**

### **PROBLEM: Min Cost Climbing Stairs (LC 746)** 

PROBLEM: Each step has cost. Can climb 1 or 2 steps. Find min cost to reach top.

 **KEY INSIGHT**: At each step, choose cheaper path (from 1 or 2 steps back)

**RECURSIVE (Top-Down):**

```cpp
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    vector<int> memo(n + 1, -1);
    return solve(cost, n, memo);
}

int solve(vector<int>& cost, int i, vector<int>& memo) {
    if (i <= 1) return 0;
    if (memo[i] != -1) return memo[i];
    return memo[i] = min(solve(cost, i-1, memo) + cost[i-1],
                         solve(cost, i-2, memo) + cost[i-2]);
}
```

**TABULATION (Bottom-Up):**

```cpp
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 0;

    for (int i = 2; i <= n; i++) {
        dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
    }

    return dp[n];
}
```

TIME: O(N)  |  SPACE: O(N) > Can optimize to O(1)!

 **WHY THIS BASE CASE?**
```
dp[0] = 0, dp[1] = 0
```

> You can START from step 0 or step 1 (problem says so).
> Starting costs nothing, so both are 0.
> dp[i] represents min cost to REACH step i, not to LEAVE it.
> The "top" is step n (one past the last step), which is why
dp array is size n+1 and answer is dp[n].

### **PROBLEM: Coin Change (LC 322)** 

PROBLEM: Min coins to make amount (coins can be reused)

 **KEY INSIGHT**: For each amount, try all coins, pick best!

**RECURSIVE (Top-Down):**

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> memo(amount + 1, -2);
    int ans = solve(coins, amount, memo);
    return ans == INT_MAX ? -1 : ans;
}

int solve(vector<int>& coins, int amt, vector<int>& memo) {
    if (amt == 0) return 0;
    if (amt < 0) return INT_MAX;
    if (memo[amt] != -2) return memo[amt];

    int best = INT_MAX;
    for (int coin : coins) {
        int sub = solve(coins, amt - coin, memo);
        if (sub != INT_MAX) best = min(best, sub + 1);
    }
    return memo[amt] = best;
}
```

**TABULATION (Bottom-Up):**

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i)
                dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
}
```

TIME: O(Amount x Coins)  |  SPACE: O(Amount)

**COMMON MISTAKE:**
```
 dp[i] = INT_MAX > overflow when adding 1
 dp[i] = amount + 1 (impossible value, safe upper bound)
```

 **WHY THIS BASE CASE?**
```
dp[0] = 0
```

> "How many coins to make amount 0?" > Zero coins. You're already there.
> This is the VALID base: recursion stops when amount reaches 0.

```
dp[1..amount] = amount + 1 (not INT_MAX!)
```

> These are UNKNOWN states, initialized to "impossible".
> Why amount+1 not INT_MAX? Because dp[i-coin] + 1 would OVERFLOW
if dp[i-coin] = INT_MAX. amount+1 is safe because you can never
need more than 'amount' coins (worst case: all 1-coins).

WHY size amount+1?
> dp[i] = min coins for amount i. We need dp[0] through dp[amount].
> Index 0 is the base case, index 'amount' is the answer.

---

### **"LOOP ALL CHOICES" vs "PICK/NOT-PICK" — TWO RECURSION STYLES**

The recursive solution above uses "loop all coins" style. There's another
way: "pick/not-pick" (index-based). Both are valid — here's the difference:

**STYLE 1: "Loop all choices" (used above)**

```cpp
int solve(vector<int>& coins, int amt, vector<int>& memo) {
    if (amt == 0) return 0;
    if (amt < 0) return INT_MAX;
    if (memo[amt] != -2) return memo[amt];

    int best = INT_MAX;
    for (int coin : coins) {                        // try EVERY coin at this state
        int sub = solve(coins, amt - coin, memo);
        if (sub != INT_MAX) best = min(best, sub + 1);
    }
    return memo[amt] = best;
}
// State: (amount) only → 1D memo
// Reuse: coins automatically reusable (same coin appears in loop next call)
```

**STYLE 2: "Pick / Not-Pick" (index-based)**

```cpp
int solve(vector<int>& coins, int i, int amt, vector<vector<int>>& memo) {
    if (amt == 0) return 0;
    if (i == coins.size()) return INT_MAX;
    if (memo[i][amt] != -2) return memo[i][amt];

    int notPick = solve(coins, i + 1, amt, memo);   // SKIP coin[i], move to next
    int pick = INT_MAX;
    if (coins[i] <= amt) {
        int sub = solve(coins, i, amt - coins[i], memo);  // USE coin[i], STAY at i
        if (sub != INT_MAX) pick = sub + 1;
    }
    return memo[i][amt] = min(pick, notPick);
}
// State: (coin_index, amount) → 2D memo
// Reuse: stay at index i (don't move to i+1) = unbounded
//         move to i+1 after pick = 0/1 (each item once)
```

**COMPARISON:**

```
+---------------------+----------------------------+----------------------------+
| Aspect              | Loop All Choices           | Pick / Not-Pick            |
+---------------------+----------------------------+----------------------------+
| State               | (amount) only              | (coin_index, amount)       |
| Memo                | 1D: O(amount)              | 2D: O(coins x amount)      |
| Decision at state   | Loop all coins             | Binary: use coin[i] or skip|
| Reuse of items      | Automatic (loop repeats)   | Stay at i = unbounded      |
|                     |                            | Move to i+1 = 0/1 knapsack |
+---------------------+----------------------------+----------------------------+
```

**WHEN TO USE WHICH?**

```
"Loop all choices" (Style 1):
  Use when: items are UNBOUNDED (reuse freely) AND order doesn't matter
  Simpler: 1D memo, less space
  Examples: Coin Change, Perfect Squares, Combination Sum IV

"Pick / Not-Pick" (Style 2):
  Use when: items used ONCE (0/1 knapsack)
            OR you need to track which items are chosen
            OR counting COMBINATIONS not permutations
  Required for: 0/1 Knapsack, Partition Subset Sum, Target Sum
  Also works for: Coin Change II (combinations — need index to avoid
                  counting [1,2] and [2,1] as different)
```

**KEY INSIGHT:** For Coin Change (LC 322), both styles give correct answer
because coins are unbounded. Style 1 is simpler (1D vs 2D), so we prefer it.
But for Coin Change II (LC 518) where we count COMBINATIONS, you MUST use
Style 2 (pick/not-pick with index) to avoid duplicate counting.

---

### **PROBLEM: Minimum Path Sum (LC 64)**

PROBLEM: Min path sum from top-left to bottom-right (only right/down moves)

**RECURSIVE (Top-Down):**

```cpp
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> memo(m, vector<int>(n, -1));
    return solve(grid, m-1, n-1, memo);
}

int solve(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& memo) {
    if (i == 0 && j == 0) return grid[0][0];
    if (i < 0 || j < 0) return INT_MAX;
    if (memo[i][j] != -1) return memo[i][j];
    return memo[i][j] = grid[i][j] + min(solve(grid, i-1, j, memo),
                                          solve(grid, i, j-1, memo));
}
```

**TABULATION (Bottom-Up, in-place):**

```cpp
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    for (int i = 1; i < m; i++) grid[i][0] += grid[i-1][0];
    for (int j = 1; j < n; j++) grid[0][j] += grid[0][j-1];

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
        }
    }

    return grid[m-1][n-1];
}
```

 **SPACE OPTIMIZATION**: Modify grid in-place!

 **WHY THIS BASE CASE?**
First row: grid[0][j] += grid[0][j-1]
> In the first row, you can ONLY come from the left (no row above).
> So cost = sum of all cells to the left.

First column: grid[i][0] += grid[i-1][0]
> In the first column, you can ONLY come from above (nothing to the left).
> So cost = sum of all cells above.

```
grid[0][0] stays as is
```

> Starting point. Cost to reach start = the cell's own value.
> No "n+1" trick needed here because we modify the grid in-place
and the grid itself already holds the starting values.

**MORE PROBLEMS IN THIS PATTERN:**
- 931. Minimum Falling Path Sum
- 983. Minimum Cost For Tickets
- 279. Perfect Squares
- 1049. Last Stone Weight II
- 120. Triangle
- 174. Dungeon Game (Hard)

## **PATTERN 2: DISTINCT WAYS** 

```
+-----------------------------------------------------------------------------+
| SUBCATEGORIES:                                                              |
|   2.1 Linear Counting (Climbing Stairs, Decode Ways)                        |
|   2.2 Grid Counting (Unique Paths)                                          |
|   2.3 Subset Sum Counting (Coin Change II, Target Sum)                      |
+-----------------------------------------------------------------------------+
```

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Count number of ways"
- "How many ways to..."
- "Number of distinct paths"
- "Total combinations/arrangements"

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "Ways to reach here = SUM of ways from all previous positions      |
|   that can transition to here."                                     |
|                                                                     |
|   dp[i] = dp[prev₁] + dp[prev₂] + ... + dp[prevₖ]                   |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE RIVER ANALOGY:**
Imagine water flowing from multiple tributaries into one point.
The total water (ways) at any point = sum of water from all
incoming streams (previous states).

CRITICAL DIFFERENCE FROM PATTERN 1:
```
+----------------------------------------------------------------------+
|  Pattern 1 (Min/Max): Pick the BEST option  > min() or max()         |
|  Pattern 2 (Count):   Sum ALL options       > dp[a] + dp[b] + ...    |
+----------------------------------------------------------------------+
```

### ** UNIVERSAL TEMPLATE**

**STATE DEFINITION:**
```
dp[i] = number of distinct ways to reach state i
```

**RECURRENCE:**
```
dp[i] = dp[i-k₁] + dp[i-k₂] + ... + dp[i-kₙ]
```

**BASE CASE:**
```
dp[0] = 1 (exactly ONE way to do nothing / reach start)
```

**TEMPLATE:**

```cpp
int countWays(int target, vector<int>& options) {
vector<long long> dp(target + 1, 0);          
dp[0] = 1;  // ONE way to make 0 / reach start

for (int i = 1; i <= target; i++) {           
    for (int opt : options) {                 
        if (opt <= i) {                       
            dp[i] += dp[i - opt];             
        }                                     
    }                                         
}                                             

return dp[target];                            

}
```

### ** COMMON PITFALLS**

 PITFALL 1: Base case dp[0] = 0
If dp[0] = 0, everything becomes 0!
 FIX: dp[0] = 1 (one way to reach the starting point)

 PITFALL 2: Confusing Permutations vs Combinations
- Outer loop on TARGET > Permutations (order matters)
- Outer loop on ITEMS  > Combinations (order doesn't matter)

```
// ORDER MATTERS (Combination Sum IV): 1+2+1 ! 2+1+1
for (int i = 1; i <= target; i++)
   for (int coin : coins) ...

// ORDER DOESN'T MATTER (Coin Change II): 1+2+1 = 2+1+1
for (int coin : coins)
   for (int i = coin; i <= target; i++) ...
```

 PITFALL 3: Integer overflow
Ways can grow exponentially! Use long long or modulo

### **2.1 SUBCATEGORY: LINEAR COUNTING**

### **PROBLEM: Climbing Stairs (LC 70)** 

PROBLEM: Count ways to climb n stairs (1 or 2 steps at a time)

 **KEY INSIGHT**: This is Fibonacci!
Ways to reach step n = ways to reach (n-1) + ways to reach (n-2)

**RECURSIVE (Top-Down):**

```cpp
int climbStairs(int n) {
    vector<int> memo(n + 1, -1);
    return solve(n, memo);
}

int solve(int n, vector<int>& memo) {
    if (n <= 2) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = solve(n-1, memo) + solve(n-2, memo);
}
```

**TABULATION (Bottom-Up):**

```cpp
int climbStairs(int n) {
    if (n <= 2) return n;
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}
```

TIME: O(N)  |  SPACE: O(N) > Can optimize to O(1)!

 **WHY THIS BASE CASE?**
```
dp[1] = 1, dp[2] = 2
```

> 1 stair: only 1 way (take 1 step). Trivially true.
> 2 stairs: 2 ways (1+1 or 2). You can verify by hand.
> dp[0] is not used because "0 stairs" has no physical meaning here.
> This is Fibonacci shifted: ways(n) = ways(n-1) + ways(n-2).
You MUST know two base values to start the chain.

### **PROBLEM: Unique Paths (LC 62)** 

PROBLEM: Count paths from top-left to bottom-right (only right/down)

 **KEY INSIGHT**:
Ways to reach (i,j) = ways from left + ways from top
dp[i][j] = dp[i-1][j] + dp[i][j-1]

**RECURSIVE (Top-Down):**

```cpp
int uniquePaths(int m, int n) {
    vector<vector<int>> memo(m, vector<int>(n, -1));
    return solve(m-1, n-1, memo);
}

int solve(int i, int j, vector<vector<int>>& memo) {
    if (i == 0 || j == 0) return 1;
    if (memo[i][j] != -1) return memo[i][j];
    return memo[i][j] = solve(i-1, j, memo) + solve(i, j-1, memo);
}
```

**TABULATION (Bottom-Up):**

```cpp
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}
```

TIME: O(M x N)  |  SPACE: O(M x N) > Can optimize to O(N)!

 **WHY THIS BASE CASE?**
All cells initialized to 1 (first row and first column = 1)
> First row: can ONLY move right > exactly 1 path to each cell.
> First column: can ONLY move down > exactly 1 path to each cell.
> Interior cells: dp[i][j] = dp[i-1][j] + dp[i][j-1] (from top + from left).
> Initializing all to 1 works because the loop starts at (1,1) and
overwrites interior cells. First row & column stay as 1.

### **PROBLEM: Combination Sum IV (LC 377)** 

PROBLEM: Count combinations to make target (ORDER MATTERS!)

**RECURSIVE (Top-Down):**

```cpp
int combinationSum4(vector<int>& nums, int target) {
    vector<int> memo(target + 1, -1);
    return solve(nums, target, memo);
}

int solve(vector<int>& nums, int target, vector<int>& memo) {
    if (target == 0) return 1;
    if (target < 0) return 0;
    if (memo[target] != -1) return memo[target];

    int ways = 0;
    for (int num : nums) {
        ways += solve(nums, target - num, memo);
    }
    return memo[target] = ways;
}
```

**TABULATION (Bottom-Up):**

```cpp
int combinationSum4(vector<int>& nums, int target) {
    vector<unsigned int> dp(target + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= target; i++) {
        for (int num : nums) {
            if (num <= i) dp[i] += dp[i - num];
        }
    }

    return dp[target];
}
```

 **CRITICAL**: Use unsigned int to handle overflow!

 **WHY THIS BASE CASE?**
```
dp[0] = 1
```

> "How many ways to make target 0?" > Exactly 1: pick nothing.
> This is the COUNT pattern: dp[0] = 1, NOT 0!
> If dp[0] = 0, then dp[i] += dp[0] adds nothing, and EVERY
state stays 0. The whole DP collapses.

```
dp[1..target] = 0
```

> "No ways found yet." We'll accumulate ways during iteration.

### **DETAILED EXAMPLE: Target Sum (LC 494)**  UNIQUE!

PROBLEM: Assign + or - to each number to reach target sum.

 **BRILLIANT TRANSFORMATION**:
This is actually SUBSET SUM in disguise!

 **WHY IT WORKS**:
Let P = sum of positive numbers, N = sum of negative numbers
P - N = target
P + N = sum (total sum)

Solving: P = (target + sum) / 2

Problem becomes: "Count subsets with sum = P"

**STEP-BY-STEP DERIVATION:**

```
nums = [1, 1, 1, 1, 1], target = 3
```

All numbers sum = 5
We want: positive - negative = 3

If we pick positive = 4, negative = 1:
4 - 1 = 3 Y

How to find P (positive sum)?
P + N = 5  (all numbers)
P - N = 3  (our target)
---------
2P = 8
```
P = 4
```

So we need to find: "Count subsets with sum = 4"

**RECURSIVE (Top-Down) — direct +/- approach:**

```cpp
int findTargetSumWays(vector<int>& nums, int target) {
    unordered_map<string, int> memo;
    return solve(nums, 0, target, memo);
}

int solve(vector<int>& nums, int i, int remaining, unordered_map<string, int>& memo) {
    if (i == nums.size()) return remaining == 0 ? 1 : 0;
    string key = to_string(i) + "," + to_string(remaining);
    if (memo.count(key)) return memo[key];
    return memo[key] = solve(nums, i+1, remaining - nums[i], memo)
                     + solve(nums, i+1, remaining + nums[i], memo);
}
```

**TABULATION (Bottom-Up) — subset sum reduction:**

```cpp
int findTargetSumWays(vector<int>& nums, int target) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (target > sum || target < -sum) return 0;
    if ((target + sum) % 2 != 0) return 0;

    int P = (target + sum) / 2;
    vector<int> dp(P + 1, 0);
    dp[0] = 1;

    for (int num : nums) {
        for (int j = P; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }

    return dp[P];
}
```

TIME: O(N x Sum)  |  SPACE: O(Sum)

 **WHY THIS BASE CASE?**
```
dp[0] = 1
```

> "How many subsets sum to 0?" > Exactly 1: the empty subset {}.
> This seeds the entire DP. Without it, dp[j-num] is always 0,
so no subset is ever counted.

> Edge cases handled BEFORE DP: if target > sum or target < -sum
or (target+sum) is odd > return 0 immediately.

 **CRITICAL**: Inner loop goes BACKWARDS!
Why? In 0/1 knapsack, each item used once.
Forward would use same item multiple times!

**EXAMPLE WALKTHROUGH:**
```
nums = [1, 1, 1], P = 2
```

Initial: dp = [1, 0, 0]

After num=1: dp[2] += dp[1]=0, dp[1] += dp[0]=1
```
dp = [1, 1, 0]
```

After num=1: dp[2] += dp[1]=1, dp[1] += dp[0]=1
```
dp = [1, 2, 1]
```

After num=1: dp[2] += dp[1]=2, dp[1] += dp[0]=1
```
dp = [1, 3, 3]
```

Answer: dp[2] = 3 Y

### **DETAILED EXAMPLE: Partition Equal Subset Sum (LC 416)** 

PROBLEM: Can we partition array into two subsets with equal sum?

 **KEY INSIGHT**: Find subset with sum = total_sum / 2

**THOUGHT PROCESS:**

```
nums = [1, 5, 11, 5], sum = 22
```

Can we split into two sets with sum = 11 each?
Set 1: [1, 5, 5] = 11 Y
Set 2: [11] = 11 Y

Problem: "Can we pick numbers that sum to 11?"
> Classic 0/1 Knapsack!

**BASE CASES:**
```
sum = 0 > return true (pick nothing)
```

sum < 0 > return false (impossible)
```
i = n > return sum == 0
```

**TOP-DOWN:**

```cpp
bool canPartition(vector<int>& nums) {
int sum = accumulate(nums.begin(), nums.end(), 0);                
if (sum % 2) return false;  // Odd sum can't be split equally     

vector<vector<int>> memo(nums.size(), vector<int>(sum/2 + 1, -1));
return helper(nums, 0, sum / 2, memo);                            

}

bool helper(vector<int>& nums, int i, int target, vector<vector<int>>& memo) {
// Base cases                                           
if (target == 0) return true;   // Found a valid subset!
if (i == nums.size()) return false;  // No more elements
if (target < 0) return false;   // Exceeded target      

if (memo[i][target] != -1) return memo[i][target];      

// Decision: take or skip                               
bool take = helper(nums, i + 1, target - nums[i], memo);
bool skip = helper(nums, i + 1, target, memo);          

return memo[i][target] = (take || skip);                

}
```

### BOTTOM-UP (Space Optimized!):

```cpp
bool canPartition(vector<int>& nums) {
int sum = accumulate(nums.begin(), nums.end(), 0);      
if (sum % 2) return false;                              

int target = sum / 2;                                   
vector<bool> dp(target + 1, false);                     
dp[0] = true;  // Base: can make 0                      

for (int num : nums) {                                  
    for (int j = target; j >= num; j--) {  // Backwards!
        dp[j] = dp[j] || dp[j - num];                   
    }                                                   
}                                                       

return dp[target];                                      

}
```

TIME: O(N x Sum)  |  SPACE: O(Sum)

 **WHY THIS BASE CASE?**
```
dp[0] = true > "Can we make sum 0?" > YES, pick nothing.
dp[1..target] = false > "No way found yet."
```

WHY reverse loop (j = target down to num)?
> 0/1 Knapsack: each number used AT MOST ONCE.
> Forward loop would let dp[j-num] use an already-updated value,
effectively using the same number multiple times.

> Backward loop reads dp[j-num] from the PREVIOUS item's row.

**EXAMPLE TRACE:**
```
nums = [1, 5, 5], target = 11/2 = 5 (invalid, sum=11 is odd!)
nums = [1, 2, 3, 4], target = 10/2 = 5
```

Initial: dp = [T, F, F, F, F, F]
0  1  2  3  4  5

After 1: dp[1] = dp[1] || dp[0] = T
```
dp = [T, T, F, F, F, F]
```

After 2: dp[3] = dp[3] || dp[1] = T
```
dp[2] = dp[2] || dp[0] = T
dp = [T, T, T, T, F, F]
```

After 3: dp[5] = dp[5] || dp[2] = T Y
```
dp = [T, T, T, T, T, T]
```

Answer: dp[5] = true Y

### **DETAILED EXAMPLE: Perfect Squares (LC 279)** 

PROBLEM: Minimum perfect squares that sum to n.

 **KEY INSIGHT**: Similar to Coin Change! Coins = perfect squares.

**THOUGHT PROCESS:**

```
n = 12
```

Perfect squares < 12: [1, 4, 9]

Find minimum coins to make 12:
12 = 4 + 4 + 4 (3 squares) Y
12 = 9 + 1 + 1 + 1 (4 squares)

```
Minimum = 3
```

**BASE CASES:**
```
n = 0 > 0 (no squares needed)
n = 1 > 1 (one square: 12)
```

**RECURRENCE:**
```
dp[n] = min(dp[n - i2] + 1) for all i where i2 < n
```

**RECURSIVE (Top-Down):**

```cpp
int numSquares(int n) {
    vector<int> memo(n + 1, -1);
    return solve(n, memo);
}

int solve(int n, vector<int>& memo) {
    if (n == 0) return 0;
    if (memo[n] != -1) return memo[n];

    int best = INT_MAX;
    for (int j = 1; j * j <= n; j++) {
        best = min(best, solve(n - j*j, memo) + 1);
    }
    return memo[n] = best;
}
```

**TABULATION (Bottom-Up):**

```cpp
int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            dp[i] = min(dp[i], dp[i - j*j] + 1);
        }
    }

    return dp[n];
}
```

TIME: O(N x VN)  |  SPACE: O(N)

 **WHY THIS BASE CASE?**
```
dp[0] = 0
```

> "Min squares to make 0" > Zero squares needed. Already at target.
> Same logic as Coin Change: target reached, no more work.

```
dp[1..n] = INT_MAX
```

> "Unknown / impossible until proven otherwise."
> Safe here because we check dp[i - j*j] and add 1. The +1 won't
```python
overflow INT_MAX since j*j <= i guarantees dp[i-j*j] was computed
from dp[0] chain and is a small number.                          
```

### DETAILED TRACE for n = 12:

```
dp[0] = 0
dp[1] = dp[0] + 1 = 1              (12)
dp[2] = dp[1] + 1 = 2              (12 + 12)
dp[3] = dp[2] + 1 = 3              (12 + 12 + 12)
dp[4] = min(dp[3]+1, dp[0]+1) = 1  (22)
dp[5] = min(dp[4]+1, dp[1]+1) = 2  (22 + 12)
```

...
```
dp[9] = dp[0] + 1 = 1              (32)
dp[12] = min(dp[11]+1, dp[8]+1, dp[3]+1)
```

= min(3, 3, 4) = 3 Y        (22 + 22 + 22)

**MORE PROBLEMS:**
- 688. Knight Probability
- 935. Knight Dialer
- 1155. Number of Dice Rolls With Target Sum

## **PATTERN 3: MERGING INTERVALS (INTERVAL DP)** 

```
+-----------------------------------------------------------------------------+
| SUBCATEGORIES:                                                              |
|   3.1 Range Merging (Burst Balloons, Merge Stones)                          |
|   3.2 Partition DP (Palindrome Partitioning, MCM)                           |
|   3.3 Counting Structures (Unique BSTs)                                     |
+-----------------------------------------------------------------------------+
```

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Burst/merge/combine elements"
- "Matrix chain multiplication"
- "Optimal way to partition"
- "Operations on contiguous ranges"
- Answer depends on BOTH left and right subproblems

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "For range [i, j], I try EVERY possible split point k.             |
|   I solve [i, k] and [k+1, j] separately, then combine."            |
|                                                                     |
|   It's like asking: 'Where should I cut this rod?'                  |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE PIZZA CUTTING ANALOGY:**
Imagine you have a pizza (range) and need to cut it optimally.
You try cutting at every position, compute cost of left slice +
right slice + cost of this cut, and pick the best cut point.

 **THE BACKWARD TRICK** (Burst Balloons):
```
+----------------------------------------------------------------------+
|  Forward thinking is HARD: "Which element to remove first?"          |
|  Backward thinking is EASY: "Which element to remove LAST?"          |
|                                                                      |
|  Why? When element k is removed LAST in range [i,j]:                 |
|  - Left boundary is always nums[i-1]                                 |
|  - Right boundary is always nums[j+1]                                |
|  - No neighbor changes!                                              |
+----------------------------------------------------------------------+
```

### ** UNIVERSAL TEMPLATE**

**STATE DEFINITION:**
```
dp[i][j] = optimal answer for range [i, j]
```

**RECURRENCE:**
```
dp[i][j] = best(dp[i][k] + dp[k+1][j] + cost(i, k, j)) for all k
```

**BASE CASE:**
```
dp[i][i] = 0 or arr[i] (single element)
```

 **CRITICAL: LOOP ORDER**
Must iterate by LENGTH first! (small ranges before large)

**TEMPLATE:**

```cpp
int solve(vector<int>& arr) {
int n = arr.size();                                                
vector<vector<int>> dp(n, vector<int>(n, 0));                      

// CRITICAL: Loop by LENGTH first!                                 
for (int len = 2; len <= n; len++) {           // length           
    for (int i = 0; i <= n - len; i++) {       // start            
        int j = i + len - 1;                    // end             
        dp[i][j] = INT_MAX;  // or INT_MIN for max                 

        // Try all split points                                    
        for (int k = i; k < j; k++) {                              
            int cost = dp[i][k] + dp[k+1][j] + merge_cost(i, k, j);
            dp[i][j] = min(dp[i][j], cost);                        
        }                                                          
    }                                                              
}                                                                  

return dp[0][n-1];                                                 

}
```

### ** COMMON PITFALLS**

 PITFALL 1: Wrong loop order
Looping i then j WON'T work - you need dp[i][k] and dp[k+1][j]
which may not be computed yet!
 FIX: Always loop by LENGTH first

 PITFALL 2: Off-by-one in split points
k can range from i to j-1 (not j!)
```
dp[i][k] needs k < j so dp[k+1][j] is valid
```

 PITFALL 3: Forgetting boundary handling
In "Burst Balloons", add virtual 1s at boundaries
```
nums = [3,1,5] > nums = [1,3,1,5,1]
```

 **COMPLEXITY**: Always O(N3) - three nested loops

### **3.1 SUBCATEGORY: RANGE MERGING**

### **PROBLEM: Minimum Cost Tree From Leaf Values (LC 1130)** 

PROBLEM: Build binary tree minimizing sum of non-leaf nodes.

**RECURSIVE (Top-Down):**

```cpp
int mctFromLeafValues(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> maxs(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        maxs[i][i] = arr[i];
        for (int j = i+1; j < n; j++) maxs[i][j] = max(maxs[i][j-1], arr[j]);
    }
    vector<vector<int>> memo(n, vector<int>(n, -1));
    return solve(0, n-1, maxs, memo);
}

int solve(int i, int j, vector<vector<int>>& maxs, vector<vector<int>>& memo) {
    if (i == j) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    int best = INT_MAX;
    for (int k = i; k < j; k++) {
        best = min(best, solve(i, k, maxs, memo) + solve(k+1, j, maxs, memo)
                        + maxs[i][k] * maxs[k+1][j]);
    }
    return memo[i][j] = best;
}
```

**TABULATION (Bottom-Up):**

```cpp
int mctFromLeafValues(vector<int>& arr) {
int n = arr.size();                                                
vector<vector<int>> dp(n, vector<int>(n, 0));                      

// Precompute max in each range                                    
vector<vector<int>> maxs(n, vector<int>(n));                       
for (int i = 0; i < n; i++) {                                      
    maxs[i][i] = arr[i];                                           
    for (int j = i + 1; j < n; j++) {                              
        maxs[i][j] = max(maxs[i][j-1], arr[j]);                    
    }                                                              
}                                                                  

for (int l = 1; l < n; l++) {                                      
    for (int i = 0; i < n - l; i++) {                              
        int j = i + l;                                             
        dp[i][j] = INT_MAX;                                        

        for (int k = i; k < j; k++) {                              
            dp[i][j] = min(dp[i][j],                               
                dp[i][k] + dp[k+1][j] + maxs[i][k] * maxs[k+1][j]);
        }                                                          
    }                                                              
}                                                                  

return dp[0][n-1];                                                 

}
```

TIME: O(N3)  |  SPACE: O(N2)

 **WHY THIS BASE CASE?**
```
dp[i][i] = 0 (implicit, array initialized to 0)
```

> A single leaf has no non-leaf node > cost = 0.
> Only when we MERGE two groups do we create a non-leaf node.
> The loop starts at len=1 (two elements), where the first
merge happens and costs max(left) x max(right).

### **PROBLEM: Burst Balloons (LC 312)**  HARD

PROBLEM: Burst balloons to maximize coins (multiply adjacent values).

 **BRILLIANT INSIGHT**: Think backwards! Which balloon to burst LAST?

**RECURSIVE (Top-Down):**

```cpp
int maxCoins(vector<int>& nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    vector<vector<int>> memo(n + 2, vector<int>(n + 2, -1));
    return solve(nums, 1, n, memo);
}

int solve(vector<int>& nums, int i, int j, vector<vector<int>>& memo) {
    if (i > j) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    int best = 0;
    for (int k = i; k <= j; k++) {
        int coins = nums[i-1] * nums[k] * nums[j+1];
        best = max(best, solve(nums, i, k-1, memo) + coins + solve(nums, k+1, j, memo));
    }
    return memo[i][j] = best;
}
```

**TABULATION (Bottom-Up):**

```cpp
int maxCoins(vector<int>& nums) {
int n = nums.size();                                        
nums.insert(nums.begin(), 1);  // Add boundary balloons     
nums.push_back(1);                                          

vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));       

for (int l = 1; l <= n; l++) {                              
    for (int i = 1; i <= n - l + 1; i++) {                  
        int j = i + l - 1;                                  

        // Try bursting each balloon k LAST in range [i,j]  
        for (int k = i; k <= j; k++) {                      
            int coins = nums[i-1] * nums[k] * nums[j+1];    
            dp[i][j] = max(dp[i][j],                        
                           dp[i][k-1] + coins + dp[k+1][j]);
        }                                                   
    }                                                       
}                                                           

return dp[1][n];                                            

}
```

 **WHY BACKWARDS?**
Bursting changes neighbors > hard to track forward
Bursting LAST > neighbors are fixed (i-1 and j+1)!

 **WHY THIS BASE CASE?**
```
dp[i][j] = 0 for all i, j (array init)
```

> When range is empty (i > j), cost = 0. No balloons to burst.
> Single balloon (i == j) is NOT 0 in the loop! When it's the
LAST balloon burst in range [i,j], cost = nums[i-1]*nums[k]*nums[j+1].

> Boundary balloons (value 1) are added at start and end. This handles
edge cases: bursting the first/last real balloon always has a
neighbor with value 1.

### **DETAILED EXAMPLE: Unique Binary Search Trees (LC 96)** 

PROBLEM: Count unique BSTs with n nodes (values 1 to n).

 **KEY INSIGHT**: Pick each value as root, count left x right subtrees!

**THOUGHT PROCESS:**

```
n = 3, values = [1, 2, 3]
```

Pick 1 as root:
Left subtree: [] > 1 tree
Right subtree: [2, 3] > ? trees
Total: 1 x numTrees(2)

Pick 2 as root:
Left: [1] > 1 tree
Right: [3] > 1 tree
Total: 1 x 1

Pick 3 as root:
Left: [1, 2] > numTrees(2)
Right: [] > 1
Total: numTrees(2) x 1

Answer: numTrees(2) + 1 + numTrees(2) = 2 + 1 + 2 = 5

**BASE CASES:**
```
n = 0 > 1 (empty tree is valid)
n = 1 > 1 (only one tree)
```

**RECURRENCE:**
For each root k in [1, n]:
left subtrees = numTrees(k - 1)
right subtrees = numTrees(n - k)
```
total += left x right
```

**RECURSIVE (Top-Down):**

```cpp
int numTrees(int n) {
    vector<int> memo(n + 1, -1);
    return solve(n, memo);
}

int solve(int n, vector<int>& memo) {
    if (n <= 1) return 1;
    if (memo[n] != -1) return memo[n];
    int total = 0;
    for (int root = 1; root <= n; root++) {
        total += solve(root - 1, memo) * solve(n - root, memo);
    }
    return memo[n] = total;
}
```

**TABULATION (Bottom-Up):**

```cpp
int numTrees(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;

    for (int nodes = 2; nodes <= n; nodes++) {
        for (int root = 1; root <= nodes; root++) {
            dp[nodes] += dp[root - 1] * dp[nodes - root];
        }
    }

    return dp[n];
}
```

TIME: O(N2)  |  SPACE: O(N)

 **WHY THIS BASE CASE?**
```
dp[0] = 1 > "How many BSTs with 0 nodes?" > 1: the empty tree.
```

WHY 1 not 0? Because empty tree is a VALID subtree. When root=1,
left subtree has 0 nodes > must count as 1 possibility, not 0.
If dp[0] = 0, then dp[left] x dp[right] = 0 x anything = 0,
and every answer collapses to 0.

```
dp[1] = 1 > "How many BSTs with 1 node?" > 1: just that node.
```

Catalan Number: dp[n] = Σ dp[k-1] x dp[n-k] for k=1..n
Left subtree has k-1 nodes, right subtree has n-k nodes.
Multiply because choices are INDEPENDENT.

### DETAILED TRACE for n = 4:

```
dp[0] = 1, dp[1] = 1

dp[2]:
root=1: dp[0] x dp[1] = 1 x 1 = 1
root=2: dp[1] x dp[0] = 1 x 1 = 1
dp[2] = 2

dp[3]:
root=1: dp[0] x dp[2] = 1 x 2 = 2
root=2: dp[1] x dp[1] = 1 x 1 = 1
root=3: dp[2] x dp[0] = 2 x 1 = 2
dp[3] = 5

dp[4]:
root=1: dp[0] x dp[3] = 1 x 5 = 5
root=2: dp[1] x dp[2] = 1 x 2 = 2
root=3: dp[2] x dp[1] = 2 x 1 = 2
root=4: dp[3] x dp[0] = 5 x 1 = 5
dp[4] = 14 Y
```

FUN FACT: This is the Catalan Number! C(n) = (2n)! / ((n+1)! x n!)

### **DETAILED EXAMPLE: Minimum Cost to Merge Stones (LC 1000)**  HARD

PROBLEM: Merge stones into piles. Each merge costs sum of stones.
Can only merge K consecutive piles. Find min cost.

 **KEY INSIGHT**:
To merge n piles into 1: need (n-1)/(k-1) merges
Check if (n-1) % (k-1) == 0, else impossible!

**THOUGHT PROCESS:**

```
stones = [3, 2, 4, 1], k = 2
```

Can merge 4 piles into 1?
(4-1) / (2-1) = 3 Y (need 3 merges)

Merge [3,2]: cost = 5, result = [5, 4, 1]
Merge [5,4]: cost = 9, result = [9, 1]
Merge [9,1]: cost = 10, result = [10]
Total: 5 + 9 + 10 = 24

But is this optimal? Try other orders...

**RECURRENCE:**
```
dp[i][j][m] = min cost to merge stones[i..j] into m piles
```

To merge into 1 pile:
```
dp[i][j][1] = dp[i][j][k] + sum[i..j]
```

To merge into m piles (m > 1):
```
dp[i][j][m] = min(dp[i][mid][1] + dp[mid+1][j][m-1])
```

**RECURSIVE (Top-Down):**

```cpp
int mergeStones(vector<int>& stones, int k) {
    int n = stones.size();
    if ((n - 1) % (k - 1) != 0) return -1;
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + stones[i];
    vector<vector<vector<int>>> memo(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
    return solve(0, n-1, 1, k, prefix, memo);
}

int solve(int i, int j, int m, int k, vector<int>& prefix,
          vector<vector<vector<int>>>& memo) {
    if (i == j) return m == 1 ? 0 : INT_MAX;
    if (memo[i][j][m] != -1) return memo[i][j][m];
    if (m == 1) {
        int sub = solve(i, j, k, k, prefix, memo);
        return memo[i][j][1] = sub == INT_MAX ? INT_MAX : sub + prefix[j+1] - prefix[i];
    }
    int best = INT_MAX;
    for (int mid = i; mid < j; mid += k - 1) {
        int left = solve(i, mid, 1, k, prefix, memo);
        int right = solve(mid+1, j, m-1, k, prefix, memo);
        if (left != INT_MAX && right != INT_MAX)
            best = min(best, left + right);
    }
    return memo[i][j][m] = best;
}
```

**TABULATION (Bottom-Up):**

```cpp
int mergeStones(vector<int>& stones, int k) {
    int n = stones.size();
    if ((n - 1) % (k - 1) != 0) return -1;                                 

// Prefix sum for range sum                                                            
vector<int> sum(n + 1, 0);                                                             
for (int i = 0; i < n; i++) {                                                          
    sum[i + 1] = sum[i] + stones[i];                                                   
}                                                                                      

// dp[i][j][m] = min cost to merge [i,j] into m piles                                  
vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, INT_MAX)));

// Base: 1 pile needs 0 cost                                                           
for (int i = 0; i < n; i++) {                                                          
    dp[i][i][1] = 0;                                                                   
}                                                                                      

// Try all lengths                                                                     
for (int len = 2; len <= n; len++) {                                                   
    for (int i = 0; i <= n - len; i++) {                                               
        int j = i + len - 1;                                                           

        // Try merging into m piles                                                    
        for (int m = 2; m <= k; m++) {                                                 
            for (int mid = i; mid < j; mid += k - 1) {                                 
                dp[i][j][m] = min(dp[i][j][m],                                         
                                  dp[i][mid][1] + dp[mid+1][j][m-1]);                  
            }                                                                          
        }                                                                              

        // Merge k piles into 1                                                        
        dp[i][j][1] = dp[i][j][k] + sum[j+1] - sum[i];                                 
    }                                                                                  
}                                                                                      

return dp[0][n-1][1];                                                                  

}
```

TIME: O(N3 x K)  |  SPACE: O(N2 x K)

 **WHY THIS BASE CASE?**
```
dp[i][i][1] = 0 > A single pile is already 1 pile. No merge needed.
dp[i][i][m] = INT_MAX for m > 1 > Can't split 1 pile into 2+. Impossible.
```

(n-1) % (k-1) != 0 > return -1
> Each merge reduces pile count by (k-1). Starting from n piles,
after one merge: n-(k-1) piles. To reach 1 pile, need exactly
(n-1)/(k-1) merges. If not divisible, impossible.

**BRILLIANT OBSERVATION:**
Must merge in steps of (k-1) intervals!
If k=3: [a,b,c,d,e] > can split at b (merge [a,b,c] and [d,e])
or at d (merge [a,b,c,d] and [e])
mid jumps by k-1!

**MORE PROBLEMS:**
- 1039. Minimum Score Triangulation
- 546. Remove Boxes (Very Hard!)

## **PATTERN 4: DP ON STRINGS** 

```
+-----------------------------------------------------------------------------+
| SUBCATEGORIES:                                                              |
|   4.1 Two Strings (LCS, Edit Distance, Interleaving)                        |
|   4.2 Single String Palindromes (Longest Palindrome, Partitioning)          |
|   4.3 Subsequence Counting (Distinct Subsequences)                          |
|   4.4 Pattern Matching (Regex, Wildcard)                                    |
+-----------------------------------------------------------------------------+
```

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Longest common subsequence/substring"
- "Edit distance / transforms"
- "Palindrome" (comparing string to its reverse)
- "String matching / pattern matching"
- Two strings being compared character by character

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "At position i in string1 and position j in string2:               |
|                                                                     |
|   If characters MATCH: Use diagonal dp[i-1][j-1] + something        |
|   If they DON'T MATCH: Use adjacent cells dp[i-1][j] or dp[i][j-1]  |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE ALIGNMENT VIEW:**
Imagine aligning two strings character by character.
At each position, you decide: match them, skip one, or skip the other.

A G C T A

A v
C     v
T       v

```
v = match (diagonal move)
```

> = skip char in string1
```
v = skip char in string2
```

 **TWO STRING VS ONE STRING**:
```
+----------------------------------------------------------------------+
|  TWO STRINGS: dp[i][j] = answer for s1[0..i-1] and s2[0..j-1]        |
|  ONE STRING:  dp[i][j] = answer for substring s[i..j]                |
|                                                                      |
|  ONE STRING often uses interval DP style (loop by length!)           |
+----------------------------------------------------------------------+
```

### ** UNIVERSAL TEMPLATES**

**TEMPLATE A: TWO STRINGS**
### STATE: dp[i][j] = answer for s1[0..i-1] and s2[0..j-1]

```
for (int i = 1; i <= n; i++) {
for (int j = 1; j <= m; j++) {                                         
    if (s1[i-1] == s2[j-1]) {                                          
        dp[i][j] = dp[i-1][j-1] + /* match bonus */;                   
    } else {                                                           
        dp[i][j] = /* min/max */ (dp[i-1][j], dp[i][j-1]) + /* cost */;
    }                                                                  
}                                                                      

}
```

**TEMPLATE B: SINGLE STRING PALINDROME**
### STATE: dp[i][j] = answer for substring s[i..j]

```
// Base: single chars are palindromes
for (int i = 0; i < n; i++) dp[i][i] = 1;

// Loop by LENGTH (interval DP style)
for (int len = 2; len <= n; len++) {
for (int i = 0; i <= n - len; i++) {                            
    int j = i + len - 1;                                        
    if (s[i] == s[j]) {                                         
        dp[i][j] = dp[i+1][j-1] + 2;  // expand palindrome      
    } else {                                                    
        dp[i][j] = max(dp[i+1][j], dp[i][j-1]);  // skip one end
    }                                                           
}                                                               

}
```

### ** COMMON PITFALLS**

 PITFALL 1: Off-by-one in string indexing
```
dp[i][j] represents s1[0..i-1] not s1[0..i]!
```

When comparing: s1[i-1] == s2[j-1], NOT s1[i] == s2[j]

 PITFALL 2: Wrong base case for edit distance
```
dp[i][0] = i (need i deletions to make empty)
dp[0][j] = j (need j insertions from empty)
```

NOT dp[i][0] = 0!

 PITFALL 3: LCS vs substring
LCS: characters don't need to be contiguous
Longest Common Substring: characters must be contiguous
Substring: reset to 0 when mismatch instead of max(left, up)

 PITFALL 4: Single string palindrome loop order
Must loop by LENGTH (small to large) not by start position
Otherwise dp[i+1][j-1] might not be computed yet

### **4.1 SUBCATEGORY: TWO STRINGS**

### **PROBLEM: Longest Common Subsequence (LC 1143)** 

PROBLEM: Find longest subsequence common to both strings.

 **KEY INSIGHT**:
If match: include this char + LCS of remaining
If no match: max(skip from s1, skip from s2)

**RECURSIVE (Top-Down):**

```cpp
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> memo(m, vector<int>(n, -1));
    return solve(text1, text2, m-1, n-1, memo);
}

int solve(string& s1, string& s2, int i, int j, vector<vector<int>>& memo) {
    if (i < 0 || j < 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (s1[i] == s2[j]) return memo[i][j] = 1 + solve(s1, s2, i-1, j-1, memo);
    return memo[i][j] = max(solve(s1, s2, i-1, j, memo), solve(s1, s2, i, j-1, memo));
}
```

**TABULATION (Bottom-Up):**

```cpp
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[m][n];
}
```

TIME: O(M x N)  |  SPACE: O(M x N) > Can optimize to O(min(M,N))!

 **WHY THIS BASE CASE?**
```
dp[0][j] = 0 and dp[i][0] = 0 (array initialized to 0)
```

> dp[0][j]: LCS of "" (empty) with text2[0..j-1] > 0. No common chars.
> dp[i][0]: LCS of text1[0..i-1] with "" > 0. Same reason.
> This is why size is (m+1) x (n+1): row 0 and col 0 represent
"empty string" and hold the base case values (all zeros).

> The actual characters start at index 1, so we compare
text1[i-1] vs text2[j-1] (not text1[i] vs text2[j]).

 SPACE OPTIMIZATION to O(N) with prev trick:
> Row i only depends on row i-1. Use single array dp[n+1].
> Diagonal dp[i-1][j-1] gets destroyed when dp[j-1] is overwritten.
> Save it in a 'prev' variable before overwriting. See Space
Optimization section below for full explanation.

### **PROBLEM: Edit Distance (LC 72)**  HARD

PROBLEM: Min operations (insert/delete/replace) to convert s1 to s2.

 **KEY INSIGHT**:
Match: no operation needed, dp[i-1][j-1]
No match: min of (insert, delete, replace) + 1

**RECURSIVE (Top-Down):**

```cpp
int minDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    return solve(word1, word2, m, n, memo);
}

int solve(string& w1, string& w2, int i, int j, vector<vector<int>>& memo) {
    if (i == 0) return j;
    if (j == 0) return i;
    if (memo[i][j] != -1) return memo[i][j];
    if (w1[i-1] == w2[j-1]) return memo[i][j] = solve(w1, w2, i-1, j-1, memo);
    return memo[i][j] = 1 + min({solve(w1, w2, i-1, j, memo),
                                  solve(w1, w2, i, j-1, memo),
                                  solve(w1, w2, i-1, j-1, memo)});
}
```

**TABULATION (Bottom-Up):**

```cpp
int minDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i-1] == word2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }

    return dp[m][n];
}
```

TIME: O(M x N)  |  SPACE: O(M x N)

 **WHY THIS BASE CASE?**
```
dp[i][0] = i > "Convert word1[0..i-1] to empty string" > need i deletions.
```

Delete every character one by one. 3 chars > 3 deletes.

```
dp[0][j] = j > "Convert empty string to word2[0..j-1]" > need j insertions.
```

Insert every character one by one. 4 chars > 4 inserts.

```
dp[0][0] = 0 > "Convert empty to empty" > 0 operations.
```

WHY NOT dp[i][0] = 0?
> That would mean "converting 'abc' to '' costs 0", which is wrong.
> You need exactly i delete operations to empty a string of length i.

### **PROBLEM: Palindromic Substrings (LC 647)**

**RECURSIVE (Top-Down) — expand from center:**

```cpp
int countSubstrings(string s) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        expand(s, i, i, count);
        expand(s, i, i+1, count);
    }
    return count;
}

void expand(string& s, int l, int r, int& count) {
    while (l >= 0 && r < s.size() && s[l] == s[r]) {
        count++;
        l--; r++;
    }
}
```

**TABULATION (Bottom-Up):**

```cpp
int countSubstrings(string s) {
    int n = s.size(), count = 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) { dp[i][i] = true; count++; }

    for (int i = 0; i < n-1; i++) {
        if (s[i] == s[i+1]) { dp[i][i+1] = true; count++; }
    }

    for (int l = 3; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            if (s[i] == s[j] && dp[i+1][j-1]) { dp[i][j] = true; count++; }
        }
    }

    return count;
}
```

 **WHY THIS BASE CASE?**
```
dp[i][i] = true > Every single character is a palindrome by itself.
dp[i][i+1] = true only if s[i] == s[i+1] > Two-char palindrome.
```

> Longer substrings dp[i][j] depend on dp[i+1][j-1] (inner substring).
> For len=3, dp[i+1][j-1] = dp[i+1][i+1] (single char) > needs base.
> For len=2, dp[i+1][j-1] = dp[i+1][i] where i+1 > i > would be
invalid/uninitialized without the explicit len=2 base case.

### **DETAILED EXAMPLE: Longest Palindromic Subsequence (LC 516)** 

PROBLEM: Find length of longest palindromic subsequence.

 **KEY INSIGHT**: LCS of string with its reverse!
BUT we can solve directly with interval DP.

**THOUGHT PROCESS:**

```
s = "bbbab"
```

If s[i] == s[j]: Include both! lps[i+1][j-1] + 2
If s[i] != s[j]: Try skipping either end, take max

**BASE CASES:**
Single char: lps[i][i] = 1
Two chars: lps[i][i+1] = (s[i] == s[i+1]) ? 2 : 1

**RECURRENCE:**
```
if (s[i] == s[j]):
dp[i][j] = dp[i+1][j-1] + 2
```

else:
```
dp[i][j] = max(dp[i+1][j], dp[i][j-1])
```

**RECURSIVE (Top-Down):**

```cpp
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> memo(n, vector<int>(n, -1));
    return solve(s, 0, n-1, memo);
}

int solve(string& s, int i, int j, vector<vector<int>>& memo) {
    if (i > j) return 0;
    if (i == j) return 1;
    if (memo[i][j] != -1) return memo[i][j];
    if (s[i] == s[j]) return memo[i][j] = 2 + solve(s, i+1, j-1, memo);
    return memo[i][j] = max(solve(s, i+1, j, memo), solve(s, i, j-1, memo));
}
```

**TABULATION (Bottom-Up):**

```cpp
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) dp[i][i] = 1;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j])
                dp[i][j] = (len == 2) ? 2 : dp[i+1][j-1] + 2;
            else
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
        }
    }

    return dp[0][n-1];
}
```

TIME: O(N2)  |  SPACE: O(N2)

 **WHY THIS BASE CASE?**
```
dp[i][i] = 1 > A single character is a palindrome of length 1.
dp[i][i+1] = 2 if s[i]==s[i+1], else 1
```

> Two matching chars = palindrome of length 2.
> Two non-matching chars = best palindrome is just 1 (either char).

WHY loop by LENGTH?
> dp[i][j] depends on dp[i+1][j-1] (shrink from both ends).
> i+1 > i and j-1 < j, so we need SMALLER ranges computed first.
> Looping by length (2, 3, 4...) guarantees this.

### DETAILED TRACE for s = "bbbab":

0   1   2   3   4
b   b   b   a   b

Base (len=1):
```
dp[0][0]=1, dp[1][1]=1, dp[2][2]=1, dp[3][3]=1, dp[4][4]=1

len=2:
dp[0][1]: s[0]==s[1]? YES > dp[0][1] = 2
dp[1][2]: s[1]==s[2]? YES > dp[1][2] = 2
dp[2][3]: s[2]==s[3]? NO > dp[2][3] = max(dp[3][3], dp[2][2]) = 1
dp[3][4]: s[3]==s[4]? NO > dp[3][4] = max(dp[4][4], dp[3][3]) = 1

len=3:
dp[0][2]: s[0]==s[2]? YES > dp[0][2] = dp[1][1] + 2 = 3
dp[1][3]: s[1]==s[3]? NO > dp[1][3] = max(dp[2][3], dp[1][2]) = 2
dp[2][4]: s[2]==s[4]? YES > dp[2][4] = dp[3][3] + 2 = 3

len=4:
dp[0][3]: s[0]==s[3]? NO > max(dp[1][3], dp[0][2]) = 3
dp[1][4]: s[1]==s[4]? YES > dp[1][4] = dp[2][3] + 2 = 3

len=5:
dp[0][4]: s[0]==s[4]? YES > dp[0][4] = dp[1][3] + 2 = 4 Y
```

Answer: 4 (subsequence "bbbb")

### **DETAILED EXAMPLE: Distinct Subsequences (LC 115)**  HARD

PROBLEM: Count distinct subsequences of s that equal t.

 **KEY INSIGHT**: At each position, decide to use match or skip it!

**THOUGHT PROCESS:**

```
s = "rabbbit", t = "rabbit"
```

How many ways to form "rabbit" from "rabbbit"?

If s[i] == t[j]:
- Use this match: dp[i-1][j-1]
- Skip this match: dp[i-1][j] (maybe use it later)
- Total: sum both!

If s[i] != t[j]:
- Can only skip: dp[i-1][j]

**BASE CASES:**
t is empty: 1 way (delete all from s)
s is empty but t is not: 0 ways

**RECURSIVE (Top-Down):**

```cpp
int numDistinct(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    return solve(s, t, m, n, memo);
}

int solve(string& s, string& t, int i, int j, vector<vector<int>>& memo) {
    if (j == 0) return 1;
    if (i == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    int res = solve(s, t, i-1, j, memo);
    if (s[i-1] == t[j-1]) res += solve(s, t, i-1, j-1, memo);
    return memo[i][j] = res;
}
```

**TABULATION (Bottom-Up):**

```cpp
int numDistinct(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<unsigned long>> dp(m + 1, vector<unsigned long>(n + 1, 0));

    for (int i = 0; i <= m; i++) dp[i][0] = 1;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i-1][j];
            if (s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];
        }
    }

    return dp[m][n];
}
```

TIME: O(M x N)  |  SPACE: O(M x N)

 **WHY THIS BASE CASE?**
```
dp[i][0] = 1 for all i
```

> "How many ways to form empty string t from s[0..i-1]?"
> Exactly 1: delete everything from s. The empty subsequence always matches "".

```
dp[0][j] = 0 for j > 0 (implicit, array initialized to 0)
```

> "How many ways to form t[0..j-1] from empty string?"
> Zero ways. Can't form a non-empty string from nothing.

WHY dp[i][0] = 1 not 0?
> This is the "successful match" base: we've matched ALL of t.
> Every position i in s can reach this success state by skipping
all remaining characters.

### DETAILED TRACE for s = "rabb", t = "rab":

""  r   a   b
"" 1   0   0   0
r  1   1   0   0   (r matches r: use=1, skip=0, total=1)
a  1   1   1   0   (a matches a: use=1, skip=0, total=1)
b  1   1   1   1   (b matches b: use=1, skip=0, total=1)
b  1   1   1   2   (b matches b: use=1, skip=1, total=2) Y
^
Two ways to form "rab"!

**MORE PROBLEMS:**
- 5. Longest Palindromic Substring
- 1092. Shortest Common Supersequence
- 712. Minimum ASCII Delete Sum

## **PATTERN 5: DECISION MAKING** 

```
+-----------------------------------------------------------------------------+
| SUBCATEGORIES:                                                              |
|   5.1 Take/Skip (House Robber, 0/1 Knapsack)                                |
|   5.2 Buy/Sell Stock (State Machine DP)                                     |
|   5.3 Subset Sum / Partition                                                |
|   5.4 LIS (Longest Increasing Subsequence)                                  |
+-----------------------------------------------------------------------------+
```

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Can't take adjacent elements"
- "Each item used at most once" (0/1 constraint)
- "Buy and sell stocks"
- "Partition into subsets"
- Binary choice at each position: TAKE or SKIP

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "At each element, I have a CHOICE:                                 |
|   TAKE it (with constraints) OR SKIP it.                            |
|                                                                     |
|   My current decision depends on what I did PREVIOUSLY."            |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE STATE MACHINE:**
Think of yourself holding or not holding something.

For House Robber:
```
State A: Just robbed (must skip next)             
State B: Didn't rob (can rob or skip next)        

+------------------------------------------------+
|   SKIP +---+ SKIP          ROB                 |
|   +--> | B | <--+    +-----------+             |
|   |    +---+    |    v           |             |
|   |      |      |  +---+         |             |
|   |      | ROB  +- | A | --------+             |
|   |      +------>  +---+  MUST SKIP            |
|   +--------------------------------------------+
```

For Stock Buy/Sell:
State: HOLD (have stock) or CASH (no stock)
Transitions: buy, sell, rest

 **0/1 KNAPSACK INSIGHT** (Subset Sum):
```
+----------------------------------------------------------------------+
|  "Can I reach sum S using items [0..i]?"                             |
|  dp[j] = dp[j] || dp[j - item]  (skip OR take)                       |
|                                                                      |
|   CRITICAL: Iterate j BACKWARDS to avoid using same item twice!      |
+----------------------------------------------------------------------+
```

### ** UNIVERSAL TEMPLATES**

**TEMPLATE A: TAKE/SKIP (House Robber style)**

```
int prev2 = 0, prev1 = 0;  // dp[i-2] and dp[i-1]
for (int num : nums) {
int curr = max(prev1, prev2 + num);  // skip OR take
prev2 = prev1;
prev1 = curr;

}
return prev1;
```

**TEMPLATE B: 0/1 KNAPSACK (Subset Sum)**

```cpp
vector<bool> dp(target + 1, false);
dp[0] = true;  // empty subset sums to 0

for (int item : items) {
for (int j = target; j >= item; j--) {  //  BACKWARDS! 
    dp[j] = dp[j] || dp[j - item];      // skip OR take
}                                                      

}
return dp[target];
```

**TEMPLATE C: STOCK BUY/SELL (State Machine)**

```
int hold = -prices[0];  // max profit while holding stock
int cash = 0;           // max profit without stock

for (int i = 1; i < n; i++) {
int newHold = max(hold, cash - prices[i]);  // keep OR buy
int newCash = max(cash, hold + prices[i]);  // rest OR sell
hold = newHold;
cash = newCash;

}
return cash;
```

### ** COMMON PITFALLS**

 PITFALL 1: Forward loop in 0/1 Knapsack
```
for (int j = item; j <= target; j++)  //  WRONG!
```

This uses same item multiple times! (Unbounded Knapsack)

 FIX: Loop BACKWARDS
```
for (int j = target; j >= item; j--)
```

 PITFALL 2: Mixing up states in stock problems
```
hold = max(hold, hold - prices[i])  //  Can't buy if already holding!
```

 FIX: Buy only from cash state
```
hold = max(hold, cash - prices[i])
```

 PITFALL 3: House Robber II (circular array)
Can't just apply House Robber directly!

 FIX: Run twice - exclude first house OR exclude last house
```
return max(rob(nums[1..n-1]), rob(nums[0..n-2]))
```

 PITFALL 4: Forgetting "do nothing" as valid choice
Sometimes optimal is to skip ALL elements (return 0)

### **5.1 SUBCATEGORY: TAKE/SKIP**

### **PROBLEM: House Robber (LC 198)** 

PROBLEM: Max money robbing houses (can't rob adjacent houses).

 **KEY INSIGHT**:
At each house: max(rob this + skip last, don't rob this)

**RECURSIVE (Top-Down):**

```cpp
int rob(vector<int>& nums) {
    vector<int> memo(nums.size(), -1);
    return solve(nums, nums.size() - 1, memo);
}

int solve(vector<int>& nums, int i, vector<int>& memo) {
    if (i < 0) return 0;
    if (memo[i] != -1) return memo[i];
    return memo[i] = max(solve(nums, i-1, memo),
                         solve(nums, i-2, memo) + nums[i]);
}
```

**TABULATION (Bottom-Up):**

```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];

    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
    }

    return dp[n-1];
}
```

 **WHY THIS BASE CASE?**
```
dp[0] = nums[0] > Only 1 house > must rob it (or skip for 0, but max is nums[0]).
dp[1] = max(nums[0], nums[1]) > 2 houses > can only rob ONE (adjacent rule).
```

Pick the richer house.

WHY two base cases?
> dp[i] = max(dp[i-1], dp[i-2] + nums[i]) looks back 2 steps.
> Need dp[0] AND dp[1] defined before the loop starts at i=2.

Space-optimized version uses prev2=0, prev1=0 (not nums[0], nums[1]):
> This works because the loop processes nums[0] first, setting
```
prev1 = max(0, 0+nums[0]) = nums[0]. Then nums[1] sets
prev1 = max(nums[0], nums[1]). Same result, cleaner code.
```

### SPACE OPTIMIZED O(1):

```cpp
int rob(vector<int>& nums) {
int prev2 = 0, prev1 = 0;              

for (int num : nums) {                 
    int curr = max(prev1, prev2 + num);
    prev2 = prev1;                     
    prev1 = curr;                      
}                                      

return prev1;                          

}
```

### **PROBLEM: Best Time to Buy/Sell Stock with Cooldown (LC 309)** 

PROBLEM: Max profit with transactions, 1 day cooldown after selling.

 **STATE MACHINE**:
3 states: hold stock, sold (cooldown), no stock

**RECURSIVE (Top-Down):**

```cpp
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> memo(n, vector<int>(2, -1));
    return solve(prices, 0, 0, memo);
}

int solve(vector<int>& prices, int i, int holding, vector<vector<int>>& memo) {
    if (i >= prices.size()) return 0;
    if (memo[i][holding] != -1) return memo[i][holding];
    int doNothing = solve(prices, i+1, holding, memo);
    if (holding)
        return memo[i][holding] = max(doNothing,
                                      prices[i] + solve(prices, i+2, 0, memo));
    else
        return memo[i][holding] = max(doNothing,
                                      -prices[i] + solve(prices, i+1, 1, memo));
}
```

**TABULATION (Bottom-Up, O(1) space):**

```cpp
int maxProfit(vector<int>& prices) {
    int hold = -prices[0], sold = 0, rest = 0;

    for (int i = 1; i < prices.size(); i++) {
        int prevHold = hold, prevSold = sold, prevRest = rest;
        hold = max(prevHold, prevRest - prices[i]);
        sold = prevHold + prices[i];
        rest = max(prevRest, prevSold);
    }

    return max(sold, rest);
}
```

 **WHY THIS BASE CASE?**
```
hold = -prices[0] > "Bought stock on day 0." Profit = -price (spent money).
sold = 0 > "Just sold" state on day 0: can't sell without buying first.
```

Effectively impossible, but 0 is safe because max() will skip it.

```
rest = 0 > "Resting / doing nothing." Start with 0 profit.
```

Three states form a state machine:
rest > hold (buy) > sold (sell) > rest (cooldown) > ...

Each state on day i depends on previous day's states.

### **DETAILED EXAMPLE: Best Time to Buy/Sell Stock IV (LC 188)**  HARD

PROBLEM: Max profit with at most K transactions.

 **KEY INSIGHT**: Track state (transaction count, holding stock or not)

**THOUGHT PROCESS:**

```
prices = [3, 2, 6, 5, 0, 3], k = 2
```

States:
- Day i
- Transactions used (0 to k)
- Holding stock (0 or 1)

For each day, 4 choices:
1. Do nothing (holding)
2. Do nothing (not holding)
3. Buy (if not holding)
4. Sell (if holding)

**BASE CASES:**
Day 0, no stock: profit = 0
Day 0, has stock: profit = -prices[0]
0 transactions left: can't trade anymore

**RECURRENCE:**
```
buy[i][t] = max(buy[i-1][t], sell[i-1][t-1] - prices[i])
// keep holding   or buy today

sell[i][t] = max(sell[i-1][t], buy[i-1][t] + prices[i])
// keep no stock   or sell today
```

**RECURSIVE (Top-Down):**

```cpp
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    if (n == 0 || k == 0) return 0;
    vector<vector<vector<int>>> memo(n, vector<vector<int>>(k + 1, vector<int>(2, -1)));
    return solve(prices, 0, k, 0, memo);
}

int solve(vector<int>& prices, int i, int txLeft, int holding,
          vector<vector<vector<int>>>& memo) {
    if (i == prices.size() || txLeft == 0) return 0;
    if (memo[i][txLeft][holding] != -1) return memo[i][txLeft][holding];
    int doNothing = solve(prices, i+1, txLeft, holding, memo);
    if (holding)
        return memo[i][txLeft][holding] = max(doNothing,
            prices[i] + solve(prices, i+1, txLeft-1, 0, memo));
    else
        return memo[i][txLeft][holding] = max(doNothing,
            -prices[i] + solve(prices, i+1, txLeft, 1, memo));
}
```

**TABULATION (Bottom-Up):**

```cpp
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    if (n == 0 || k == 0) return 0;

    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++) profit += max(0, prices[i] - prices[i-1]);
        return profit;
    }

    vector<vector<int>> buy(n, vector<int>(k + 1, -prices[0]));
    vector<vector<int>> sell(n, vector<int>(k + 1, 0));

    for (int i = 1; i < n; i++) {
        for (int t = 1; t <= k; t++) {
            buy[i][t] = max(buy[i-1][t], sell[i-1][t-1] - prices[i]);
            sell[i][t] = max(sell[i-1][t], buy[i-1][t] + prices[i]);
        }
    }

    return sell[n-1][k];
}
```

TIME: O(N x K)  |  SPACE: O(N x K) > Can optimize to O(K)!

 **WHY THIS BASE CASE?**
```
buy[0][t] = -prices[0] for all t
```

> "On day 0, if we hold stock, we must have bought at prices[0]."
> Profit = -prices[0] (spent that money).
> Same regardless of how many transactions allowed (t).

```
sell[0][t] = 0 for all t
```

> "On day 0, if we don't hold stock, profit = 0."
> Can't have sold without buying first on day 0.

k >= n/2 > unlimited transactions (greedy)
> With enough transactions, grab EVERY upward price movement.
> No DP needed, just sum positive differences.

### EXAMPLE TRACE for prices = [3,2,6,5,0,3], k = 2:

Day 0 (price=3):
```
buy[0][1] = -3 (bought at 3)
sell[0][1] = 0 (no action)
```

Day 1 (price=2):
```
buy[1][1] = max(-3, 0-2) = -2 (better to buy at 2)
sell[1][1] = max(0, -3+2) = 0
```

Day 2 (price=6):
```
buy[2][1] = max(-2, 0-6) = -2
sell[2][1] = max(0, -2+6) = 4 (sold at 6!)
buy[2][2] = max(-3, 0-6) = -3
sell[2][2] = max(0, -3+6) = 3
```

...continue until day 5...

Final: sell[5][2] = 7 Y
Transaction 1: Buy at 2, sell at 6 > profit = 4
Transaction 2: Buy at 0, sell at 3 > profit = 3
```
Total = 7
```

### **DETAILED EXAMPLE: Shortest Common Supersequence (LC 1092)** 

PROBLEM: Find shortest string containing both s1 and s2 as subsequences.

 **BRILLIANT INSIGHT**:
```
Length = s1.length + s2.length - LCS(s1, s2)
```

But we need the actual string, not just length!

**THOUGHT PROCESS:**

```
s1 = "abac", s2 = "cab"

LCS(s1, s2) = "ab" (length 2)
```

SCS length = 4 + 3 - 2 = 5

One possible SCS: "cabac"
Contains "abac"? Y (c-abac)
Contains "cab"? Y (cab-ac)

**ALGORITHM:**
1. Build LCS DP table
2. Backtrack to construct SCS

During backtracking:
- If match: include once (part of LCS)
- If no match: include both

**RECURSIVE (Top-Down) — LCS part only, then backtrack:**

```cpp
int solveLCS(string& s1, string& s2, int i, int j,
             vector<vector<int>>& memo) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (s1[i-1] == s2[j-1]) return memo[i][j] = 1 + solveLCS(s1, s2, i-1, j-1, memo);
    return memo[i][j] = max(solveLCS(s1, s2, i-1, j, memo),
                            solveLCS(s1, s2, i, j-1, memo));
}
```

NOTE: SCS needs the full DP table for backtracking, so tabulation is preferred.

**TABULATION (Bottom-Up) — build LCS table + backtrack:**

```cpp
string shortestCommonSupersequence(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

// Build LCS table                                    
for (int i = 1; i <= m; i++) {                        
    for (int j = 1; j <= n; j++) {                    
        if (s1[i-1] == s2[j-1]) {                     
            dp[i][j] = dp[i-1][j-1] + 1;              
        } else {                                      
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);   
        }                                             
    }                                                 
}                                                     

// Backtrack to build SCS                             
string result = "";                                   
int i = m, j = n;                                     

while (i > 0 && j > 0) {                              
    if (s1[i-1] == s2[j-1]) {                         
        result = s1[i-1] + result;  // Include once   
        i--;                                          
        j--;                                          
    } else if (dp[i-1][j] > dp[i][j-1]) {             
        result = s1[i-1] + result;  // Include from s1
        i--;                                          
    } else {                                          
        result = s2[j-1] + result;  // Include from s2
        j--;                                          
    }                                                 
}                                                     

// Add remaining characters                           
while (i > 0) result = s1[i-1] + result, i--;         
while (j > 0) result = s2[j-1] + result, j--;         

return result;                                        

}
```

TIME: O(M x N)  |  SPACE: O(M x N)

 **WHY THIS BASE CASE?**
Uses LCS table, so base cases are same as LCS:
```
dp[0][j] = 0, dp[i][0] = 0 > LCS with empty string = 0.
```

During backtracking to build the actual SCS string:
> When i=0: remaining chars of s2 must be added.
> When j=0: remaining chars of s1 must be added.
> These handle the "one string exhausted" cases.

KEY INSIGHT for SCS length:
SCS length = len(s1) + len(s2) - LCS length
> LCS chars appear ONCE (shared), non-LCS chars from both strings
must all appear. So total = both lengths minus the overlap.

### BACKTRACKING VISUALIZATION for s1="ab", s2="ac":

""  a   c

"" 0   0   0
a  0   1   1
b  0   1   1

```
LCS = "a"
```

Backtrack from (2,2):
```
s1[1]='b' != s2[1]='c', dp[1][2]=1 > dp[2][1]=1
```

> Add 'c', move to (2,1)

```
s1[1]='b' != s2[0], dp[1][1]=1 > dp[2][0]=0
```

> Add 'b', move to (1,1)

```
s1[0]='a' == s2[0]='a'
```

> Add 'a', move to (0,0)

Result: "abc" (built backwards, so "a" then "b" then "c")

**MORE PROBLEMS:**
- 712. Minimum ASCII Delete Sum
- 583. Delete Operation for Two Strings

### **ADVANCED EXAMPLE: Interleaving String (LC 97)**  UNIQUE!

PROBLEM: Check if s3 is formed by interleaving s1 and s2.

 **KEY INSIGHT**: 2D DP tracking positions in both strings!

**THOUGHT PROCESS:**

```
s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
```

At position k in s3:
- Can we use s1[i]? Check if dp[i-1][j] is true
- Can we use s2[j]? Check if dp[i][j-1] is true

**BASE CASES:**
```
dp[0][0] = true (empty strings match)
dp[i][0] = s1[0..i-1] == s3[0..i-1]
dp[0][j] = s2[0..j-1] == s3[0..j-1]
```

**RECURRENCE:**
```
dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
```

(dp[i][j-1] && s2[j-1] == s3[i+j-1])

**RECURSIVE (Top-Down):**

```cpp
bool isInterleave(string s1, string s2, string s3) {
    if (s1.size() + s2.size() != s3.size()) return false;
    vector<vector<int>> memo(s1.size() + 1, vector<int>(s2.size() + 1, -1));
    return solve(s1, s2, s3, 0, 0, memo);
}

bool solve(string& s1, string& s2, string& s3, int i, int j,
           vector<vector<int>>& memo) {
    if (i + j == s3.size()) return true;
    if (memo[i][j] != -1) return memo[i][j];
    bool res = false;
    if (i < s1.size() && s1[i] == s3[i+j]) res = solve(s1, s2, s3, i+1, j, memo);
    if (!res && j < s2.size() && s2[j] == s3[i+j]) res = solve(s1, s2, s3, i, j+1, memo);
    return memo[i][j] = res;
}
```

**TABULATION (Bottom-Up):**

```cpp
bool isInterleave(string s1, string s2, string s3) {
    int m = s1.size(), n = s2.size();
    if (m + n != s3.size()) return false;

    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= m; i++) dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1];
    for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j-1] && s2[j-1] == s3[j-1];

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
                       (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
        }
    }

    return dp[m][n];
}
```

TIME: O(M x N)  |  SPACE: O(M x N) > Can optimize to O(N)!

 **WHY THIS BASE CASE?**
```
dp[0][0] = true
```

> "Can empty s1 + empty s2 form empty s3?" > YES.

```
dp[i][0] = dp[i-1][0] && s1[i-1] == s3[i-1]
```

> Using ONLY s1 (no characters from s2). Check if s1[0..i-1] == s3[0..i-1].
> The moment one char doesn't match, all further dp[i][0] are false.

```
dp[0][j] = dp[0][j-1] && s2[j-1] == s3[j-1]
```

> Using ONLY s2 (no characters from s1). Same logic.

m + n != s3.size() > return false immediately
> If lengths don't add up, interleaving is impossible.

### DETAILED TRACE for s1="aa", s2="ab", s3="aaba":

""  a   b
"" T   F   F
a  T   T   F
a  T   T   T
^   ^
Match!

```
dp[2][2]:
```

Use s1[1]='a'? dp[1][2]=F, skip
Use s2[1]='b'? dp[2][1]=T && s2[1]==s3[3]='b' > TRUE Y

Answer: true
Interleaving: s1[0] > s1[1] > s2[0] > s2[1]
"a" + "a" + "a" + "b" = "aaab"

Wait, s2="ab" has s2[0]='a' and s2[1]='b', so:
"a"(s1[0]) + "a"(s1[1]) + "a"(s2[0]) + "b"(s2[1]) = "aaab" Y

### **ADVANCED EXAMPLE: Regular Expression Matching (LC 10)**  HARD

PROBLEM: Implement regex matching with '.' and '*'.
- '.' matches any single character
- '*' matches zero or more of preceding element

 **KEY INSIGHT**: Handle '*' by trying 0, 1, 2... matches!

**THOUGHT PROCESS:**

```
s = "aa", p = "a*"
```

'a*' can match "", "a", "aa", "aaa"...
So "aa" matches! Y

```
s = "ab", p = ".*"
```

'.*' matches any string! Y

**BASE CASES:**
```
dp[0][0] = true (empty matches empty)
dp[i][0] = false (non-empty s can't match empty pattern)
dp[0][j] = true if pattern is like "a*b*c*" (all with *)
```

**RECURRENCE:**
```
if (p[j-1] == '*'):
```

- Match 0 times: dp[i][j-2]
- Match 1+ times: dp[i-1][j] if s[i-1] matches p[j-2]

else:
- Direct match: dp[i-1][j-1] if s[i-1] matches p[j-1]

**RECURSIVE (Top-Down):**

```cpp
bool isMatch(string s, string p) {
    vector<vector<int>> memo(s.size() + 1, vector<int>(p.size() + 1, -1));
    return solve(s, p, 0, 0, memo);
}

bool solve(string& s, string& p, int i, int j, vector<vector<int>>& memo) {
    if (j == p.size()) return i == s.size();
    if (memo[i][j] != -1) return memo[i][j];

    bool first_match = (i < s.size()) && (s[i] == p[j] || p[j] == '.');

    if (j + 1 < p.size() && p[j+1] == '*') {
        return memo[i][j] = solve(s, p, i, j+2, memo) ||
                            (first_match && solve(s, p, i+1, j, memo));
    }
    return memo[i][j] = first_match && solve(s, p, i+1, j+1, memo);
}
```

**TABULATION (Bottom-Up):**

```cpp
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;

    for (int j = 2; j <= n; j++) {
        if (p[j-1] == '*') dp[0][j] = dp[0][j-2];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') {
                dp[i][j] = dp[i][j-2];
                if (p[j-2] == s[i-1] || p[j-2] == '.')
                    dp[i][j] = dp[i][j] || dp[i-1][j];
            } else {
                if (p[j-1] == s[i-1] || p[j-1] == '.')
                    dp[i][j] = dp[i-1][j-1];
            }
        }
    }

    return dp[m][n];
}
```

TIME: O(M x N)  |  SPACE: O(M x N)

 **WHY THIS BASE CASE?**
```
dp[0][0] = true > Empty string matches empty pattern. Trivially true.

dp[i][0] = false (for i > 0)
```

> Non-empty string can NEVER match empty pattern. Nothing to match against.

```
dp[0][j]: Special! Can be true if pattern is "a*b*c*..."
```

> "a*" can match ZERO 'a's, effectively vanishing.
> dp[0][j] = dp[0][j-2] when p[j-1] == '*' (use '*' to match 0 times).
> This handles patterns like "a*b*" matching empty string.
> Without this, we'd miss valid matches where * consumes its
preceding char zero times.

### DETAILED TRACE for s="aab", p="c*a*b":

""  c   *   a   *   b
"" T   F   T   F   T   F
a  F   F   F   T   T   F
a  F   F   F   F   T   F
b  F   F   F   F   F   T
^
Match!

Explanation:
- "c*" matches "" (0 c's)
- "a*" matches "aa" (2 a's)
- "b" matches "b"
> dp[3][5] = TRUE Y

### **ADVANCED EXAMPLE: Maximal Rectangle (LC 85)**  BRILLIANT!

PROBLEM: Find largest rectangle of 1's in binary matrix.

 **BRILLIANT APPROACH**: Treat each row as histogram base!
Reuse "Largest Rectangle in Histogram" solution.

**THOUGHT PROCESS:**

```
matrix = [
```

["1","0","1","0","0"],
["1","0","1","1","1"],
["1","1","1","1","1"],
["1","0","0","1","0"]
]

Build heights for each row:
Row 0: [1, 0, 1, 0, 0]
Row 1: [2, 0, 2, 1, 1] (stack on row 0)
Row 2: [3, 1, 3, 2, 2]
Row 3: [4, 0, 0, 3, 0]

For each row, find largest rectangle using histogram method!

**COMPLETE SOLUTION:**

```cpp
int maximalRectangle(vector<vector<char>>& matrix) {
if (matrix.empty()) return 0;                                   

int m = matrix.size(), n = matrix[0].size();                    
vector<int> heights(n, 0);                                      
int maxArea = 0;                                                

for (int i = 0; i < m; i++) {                                   
    // Build histogram for this row                             
    for (int j = 0; j < n; j++) {                               
        heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
    }                                                           

    // Find largest rectangle in this histogram                 
    maxArea = max(maxArea, largestRectangleArea(heights));      
}                                                               

return maxArea;                                                 

}

int largestRectangleArea(vector<int>& heights) {
stack<int> st;                                        
int maxArea = 0;                                      
int n = heights.size();                               

for (int i = 0; i <= n; i++) {                        
    int h = (i == n) ? 0 : heights[i];                

    while (!st.empty() && heights[st.top()] > h) {    
        int height = heights[st.top()];               
        st.pop();                                     
        int width = st.empty() ? i : i - st.top() - 1;
        maxArea = max(maxArea, height * width);       
    }                                                 

    st.push(i);                                       
}                                                     

return maxArea;                                       

}
```

TIME: O(M x N)  |  SPACE: O(N)

**EXAMPLE WALKTHROUGH:**

At row 2: heights = [3, 1, 3, 2, 2]

Process histogram:
```
i=0: push 0
i=1: heights[0]=3 > heights[1]=1, pop 0
height=3, width=1 > area=3
```

push 1

```
i=2: push 2 (heights[2]=3)
i=3: push 3 (heights[3]=2)
i=4: push 4 (heights[4]=2)
i=5 (end): pop all
heights[4]=2, width=2 > area=4
heights[3]=2, width=3 > area=6 Y
heights[2]=3, width=4 > area=12? No, width calculation...
```

Largest rectangle in row 2's histogram = 6

## **PATTERN 6: LIS (Longest Increasing Subsequence)** 

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Longest increasing/decreasing subsequence"
- "Maximum chain length"
- "Nested objects" (Russian dolls, envelopes)
- Subsequence (not substring) with ordering constraint

**EXAMPLE:**
[10, 9, 2, 5, 3, 7, 101, 18]
```
LIS = [2, 3, 7, 101] or [2, 5, 7, 101] > length 4
```

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  O(N2): "For each element i, look back at all j < i.                |
|          If nums[j] < nums[i], I can extend j's LIS by 1."          |
|                                                                     |
|  O(N log N): "Maintain smallest possible tail for each length.      |
|              Binary search to find where current element fits."     |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE PATIENT SORTING ANALOGY:**
Imagine sorting cards into piles where each pile's top is increasing.
When a new card comes:
- If it's larger than all pile tops > start new pile
- Otherwise > place on leftmost pile with top > card

Number of piles = LIS length!

 **KEY VARIATIONS**:
```
+----------------------------------------------------------------------+
|  STRICTLY INCREASING: nums[j] < nums[i] > lower_bound                |
|  NON-DECREASING:      nums[j] <= nums[i] > upper_bound               |
|  LONGEST DECREASING:  negate values or reverse compare               |
|  2D (Envelopes):      sort by width, LIS on heights                  |
+----------------------------------------------------------------------+
```

### ** TEMPLATE 1: O(N2) DP** (Conceptual, interviews accept this)

STATE: dp[i] = length of LIS ending at index i
RECURRENCE: dp[i] = max(dp[j] + 1) for all j < i where nums[j] < nums[i]
BASE: dp[i] = 1 (each element is LIS of length 1)

```cpp
int lengthOfLIS(vector<int>& nums) {
int n = nums.size();                      
vector<int> dp(n, 1);                     
int maxLen = 1;                           

for (int i = 1; i < n; i++) {             
    for (int j = 0; j < i; j++) {         
        if (nums[j] < nums[i]) {          
            dp[i] = max(dp[i], dp[j] + 1);
        }                                 
    }                                     
    maxLen = max(maxLen, dp[i]);          
}                                         

return maxLen;                            

}
```

TIME: O(N2)  |  SPACE: O(N)

 **WHY THIS BASE CASE?**
```
dp[i] = 1 for all i
```

> Every single element is an increasing subsequence of length 1.
> Even if no element before i is smaller, the answer is at least 1
(the element itself).

> The loop then tries to EXTEND by looking at all j < i where
```
nums[j] < nums[i]. If found, dp[i] = max(dp[i], dp[j]+1).
```

### **TEMPLATE 2: O(N log N) Binary Search** 

**KEY INSIGHT:**
Maintain array "tails" where tails[i] = smallest ending element of all LIS of length i+1

For each number:
- If larger than all tails > extend LIS
- Else > replace the first tail >= num (binary search)

**WHY IT WORKS:**
- tails is always sorted!
- Replacing with smaller value keeps more room for future elements
- tails.size() = length of LIS

```cpp
int lengthOfLIS(vector<int>& nums) {
vector<int> tails;  // tails[i] = smallest tail of LIS with length i+1

for (int num : nums) {                                                
    // Find position to insert/replace                                
    auto it = lower_bound(tails.begin(), tails.end(), num);           

    if (it == tails.end()) {                                          
        tails.push_back(num);  // Extend LIS                          
    } else {                                                          
        *it = num;  // Replace with smaller value                     
    }                                                                 
}                                                                     

return tails.size();                                                  

}
```

TIME: O(N log N)  |  SPACE: O(N)

**VISUALIZATION:**
```
nums = [10, 9, 2, 5, 3, 7, 101, 18]
```

10: tails = [10]
9:  tails = [9]      (replace 10 with 9)
2:  tails = [2]      (replace 9 with 2)
5:  tails = [2, 5]   (extend)
3:  tails = [2, 3]   (replace 5 with 3)
7:  tails = [2, 3, 7] (extend)
101: tails = [2, 3, 7, 101] (extend)
18: tails = [2, 3, 7, 18]   (replace 101 with 18)

```
Answer = 4
```

## **SOLVED: Longest Increasing Subsequence (LC 300)** 

**RECURSIVE (Top-Down) — O(N^2):**

```cpp
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> memo(n, -1);
    int ans = 1;
    for (int i = 0; i < n; i++) ans = max(ans, solve(nums, i, memo));
    return ans;
}

int solve(vector<int>& nums, int i, vector<int>& memo) {
    if (memo[i] != -1) return memo[i];
    int best = 1;
    for (int j = 0; j < i; j++) {
        if (nums[j] < nums[i]) best = max(best, 1 + solve(nums, j, memo));
    }
    return memo[i] = best;
}
```

**TABULATION (Bottom-Up) — O(N^2):**

```cpp
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) dp[i] = max(dp[i], dp[j] + 1);
        }
    }

    return *max_element(dp.begin(), dp.end());
}
```

**OPTIMAL — O(N log N) patience sort:**

```cpp
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;
    for (int num : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) tails.push_back(num);
        else *it = num;
    }
    return tails.size();
}
```

## **SOLVED: Number of Longest Increasing Subsequence (LC 673)** 

PROBLEM: Count how many LIS exist.

KEY INSIGHT: Track both length AND count for each position.

**TABULATION (Bottom-Up) — O(N^2):**

```cpp
int findNumberOfLIS(vector<int>& nums) {
int n = nums.size();                                                 
vector<int> len(n, 1);    // len[i] = length of LIS ending at i      
vector<int> cnt(n, 1);    // cnt[i] = count of LIS ending at i       
int maxLen = 1;                                                      

for (int i = 1; i < n; i++) {                                        
    for (int j = 0; j < i; j++) {                                    
        if (nums[j] < nums[i]) {                                     
            if (len[j] + 1 > len[i]) {                               
                len[i] = len[j] + 1;                                 
                cnt[i] = cnt[j];       // New max length, reset count
            } else if (len[j] + 1 == len[i]) {                       
                cnt[i] += cnt[j];      // Same length, add count     
            }                                                        
        }                                                            
    }                                                                
    maxLen = max(maxLen, len[i]);                                    
}                                                                    

int result = 0;                                                      
for (int i = 0; i < n; i++) {                                        
    if (len[i] == maxLen) result += cnt[i];                          
}                                                                    
return result;                                                       

}
```

TIME: O(N2)  |  SPACE: O(N)

 **WHY THIS BASE CASE?**
```
len[i] = 1, cnt[i] = 1 for all i
```

> len[i] = 1: Each element alone is LIS of length 1 (same as standard LIS).
> cnt[i] = 1: There's exactly 1 way to form LIS of length 1 at position i
(just the element itself).

> When len[j]+1 > len[i]: found a LONGER LIS > reset cnt[i] = cnt[j].
> When len[j]+1 == len[i]: found ANOTHER way to get same length > cnt[i] += cnt[j].

## **SOLVED: Russian Doll Envelopes (LC 354)**  HARD

PROBLEM: Given envelopes [width, height], find max nested envelopes.

**KEY INSIGHT:**
1. Sort by width ascending
2. For same width, sort by height DESCENDING (prevents using same width twice)
3. Find LIS on heights!

```cpp
int maxEnvelopes(vector<vector<int>>& envelopes) {
// Sort: width ascending, height descending for same width     
sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
    return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];           
});                                                            

// LIS on heights                                              
vector<int> tails;                                             
for (auto& env : envelopes) {                                  
    int h = env[1];                                            
    auto it = lower_bound(tails.begin(), tails.end(), h);      
    if (it == tails.end()) tails.push_back(h);                 
    else *it = h;                                              
}                                                              

return tails.size();                                           

}
```

TIME: O(N log N)  |  SPACE: O(N)

WHY DESCENDING HEIGHT FOR SAME WIDTH?
Example: [3,3], [3,4], [3,5]
If ascending: LIS might pick all 3 (wrong! same width)
If descending: [3,5], [3,4], [3,3] > LIS picks at most 1

### PRACTICE PROBLEMS - LIS Pattern:

- 300.  Longest Increasing Subsequence 
- 673.  Number of Longest Increasing Subsequence 
- 354.  Russian Doll Envelopes 
- 1964. Find the Longest Valid Obstacle Course at Each Position
- 1048. Longest String Chain
- 368.  Largest Divisible Subset

## **PATTERN 7: KADANE'S ALGORITHM (Max Subarray)** 

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Maximum/minimum sum of contiguous subarray"
- "Maximum product subarray"
- "Circular array maximum sum"
- CONTIGUOUS (not subsequence)

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "At each position, I make ONE simple decision:                     |
|   Should I EXTEND the previous subarray, or START FRESH here?"      |
|                                                                     |
|   curr = max(nums[i], curr + nums[i])                               |
|          ^             ^                                            |
|        start fresh   extend                                         |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE RESET DECISION:**
You're accumulating a running sum. At each step ask:
"Would adding this element help, or should I ditch everything and restart?"

If previous sum is NEGATIVE > restart (negative prefix hurts)
If previous sum is POSITIVE > extend (positive prefix helps)

 **PRODUCT VS SUM** (Critical Difference!):
```
+----------------------------------------------------------------------+
|  SUM: Only track current max                                         |
|  PRODUCT: Track BOTH max AND min!                                    |
|                                                                      |
|  Why? A large negative x negative = large positive!                  |
|  So today's min might become tomorrow's max.                         |
+----------------------------------------------------------------------+
```

### ** TEMPLATE**

**TEMPLATE A: MAX SUM**

```cpp
int maxSubArray(vector<int>& nums) {
int curr = nums[0], maxSum = nums[0];                          

for (int i = 1; i < nums.size(); i++) {                        
    curr = max(nums[i], curr + nums[i]);  // restart or extend?
    maxSum = max(maxSum, curr);                                
}                                                              

return maxSum;                                                 

}
```

**TEMPLATE B: MAX PRODUCT** (track both max AND min!)

```cpp
int maxProduct(vector<int>& nums) {
int maxProd = nums[0], minProd = nums[0], result = nums[0];     

for (int i = 1; i < nums.size(); i++) {                         
    if (nums[i] < 0) swap(maxProd, minProd);  // negative flips!

    maxProd = max(nums[i], maxProd * nums[i]);                  
    minProd = min(nums[i], minProd * nums[i]);                  
    result = max(result, maxProd);                              
}                                                               

return result;                                                  

}
```

TIME: O(N)  |  SPACE: O(1)

### ** COMMON PITFALLS**

 PITFALL 1: Starting curr/max at 0
All elements could be negative!
 FIX: Initialize with nums[0]

 PITFALL 2: Forgetting minProd for products
[-2, 3, -4] > max product = 24 (all three!)
If you only track max, you miss the double-negative opportunity

 PITFALL 3: Circular array
Don't just apply Kadane's directly!
 FIX: max(normal Kadane, total_sum - min_subarray)
(Wrapping around = total minus middle part)

 PITFALL 4: Empty subarray
Some problems allow empty subarray (sum = 0)
Check problem constraints!

## **SOLVED: Maximum Subarray (LC 53)** 

**TABULATION (dp[] version):**

```cpp
int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];

    for (int i = 1; i < n; i++) {
        dp[i] = max(nums[i], dp[i-1] + nums[i]);
    }

    return *max_element(dp.begin(), dp.end());
}
```

**SPACE OPTIMIZED (Kadane's O(1)):**

```cpp
int maxSubArray(vector<int>& nums) {
    int curr = nums[0], maxSum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        curr = max(nums[i], curr + nums[i]);
        maxSum = max(maxSum, curr);
    }
    return maxSum;
}
```

 **WHY THIS BASE CASE?**
```
curr = nums[0], maxSum = nums[0]
```

> Start with first element (not 0!).
> WHY NOT 0? If all elements are negative (e.g. [-3, -2, -1]),
starting at 0 would give maxSum = 0 (empty subarray), which is wrong.
The problem requires at least 1 element.

> curr tracks "best subarray ending HERE". At each step:
```
curr = max(nums[i], curr + nums[i]) means "start fresh or extend".
```

If previous sum was negative, starting fresh is better.

## **SOLVED: Maximum Sum Circular Subarray (LC 918)** 

PROBLEM: Array is circular, find max subarray sum.

KEY INSIGHT (BRILLIANT!):
Two cases:
1. Max subarray is in the middle > standard Kadane
2. Max subarray wraps around > total - minSubarray

```
Answer = max(maxSubarray, total - minSubarray)
```

EDGE CASE: If all negative, minSubarray = total > avoid returning 0!

```cpp
int maxSubarraySumCircular(vector<int>& nums) {
int total = 0;                                       
int currMax = nums[0], maxSum = nums[0];             
int currMin = nums[0], minSum = nums[0];             

for (int i = 0; i < nums.size(); i++) {              
    total += nums[i];                                

    if (i > 0) {                                     
        currMax = max(nums[i], currMax + nums[i]);   
        maxSum = max(maxSum, currMax);               

        currMin = min(nums[i], currMin + nums[i]);   
        minSum = min(minSum, currMin);               
    }                                                
}                                                    

// If all negative, maxSum is the answer (can't wrap)
if (maxSum < 0) return maxSum;                       

return max(maxSum, total - minSum);                  

}
```

TIME: O(N)  |  SPACE: O(1)

 **WHY THIS BASE CASE?**
All initialized with nums[0], same as Max Subarray.
maxSum < 0 > return maxSum (edge case: ALL elements negative)
> If all negative, total - minSum = 0 (empty subarray), which is wrong.
> In this case, the max non-wrapping subarray is the answer.
> The "wrap = total - minSubarray" trick only works when at least
one element is non-negative.

## **SOLVED: Maximum Product Subarray (LC 152)** 

PROBLEM: Find contiguous subarray with max product.

KEY INSIGHT: Track both MAX and MIN!
- Negative * negative = positive
- When we see negative, max and min swap roles

```cpp
int maxProduct(vector<int>& nums) {
int maxProd = nums[0], minProd = nums[0], result = nums[0];

for (int i = 1; i < nums.size(); i++) {                    
    if (nums[i] < 0) {                                     
        swap(maxProd, minProd);  // Negative flips max/min 
    }                                                      

    maxProd = max(nums[i], maxProd * nums[i]);             
    minProd = min(nums[i], minProd * nums[i]);             
    result = max(result, maxProd);                         
}                                                          

return result;                                             

}
```

TIME: O(N)  |  SPACE: O(1)

 **WHY THIS BASE CASE?**
```
maxProd = nums[0], minProd = nums[0], result = nums[0]
```

> Initialize with first element, not 0 or 1!
> WHY track minProd? Because negative x negative = positive.
e.g. [-2, 3, -4]: minProd after [-2,3] = -6, then -6 x -4 = 24!

> WHY swap when nums[i] < 0? Multiplying by negative FLIPS signs:
the old max becomes the new min and vice versa.

> WHY NOT start at 1? Because [0.5, 0.1] would give wrong answer
(though LeetCode uses integers). More importantly, empty product
(value 1) isn't valid - problem requires at least 1 element.

### PRACTICE PROBLEMS - Kadane's Pattern:

- 53.   Maximum Subarray 
- 918.  Maximum Sum Circular Subarray 
- 152.  Maximum Product Subarray 
- 1749. Maximum Absolute Sum of Any Subarray
- 2606. Find the Substring With Maximum Cost

## **PATTERN 8: TREE DP** 

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Maximum path sum in tree"
- "Diameter of tree"
- "Tree distance problems"
- "House robber on tree"
- "Answer for every node as root" (rerooting)

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "Tree DP is bottom-up: compute CHILDREN first, then PARENT.        |
|   Parent's answer depends on children's answers."                   |
|                                                                     |
|   Use POST-ORDER traversal: left > right > node                     |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE INFORMATION BUBBLE UP:**
Imagine each node computing something and "bubbling it up" to its parent.
Leaves compute first (base case), then their parents, up to root.

```
     compute 3rd  
        [A]       
       /   \      
 compute   compute
    1st     2nd   
    [B]     [C]   
```

 **THE TWO TYPES**:
```
+----------------------------------------------------------------------+
|  TYPE 1: SINGLE ROOT - Answer only needed for one root               |
|          > Single DFS from root                                      |
|                                                                      |
|  TYPE 2: ALL ROOTS (Rerooting) - Answer needed for every node        |
|          > Two DFS passes: down then up                              |
+----------------------------------------------------------------------+
```

 **RETURN vs GLOBAL UPDATE**:
```
+----------------------------------------------------------------------+
|  RETURN to parent: What can parent USE from this subtree?            |
|  (Usually a PATH starting from this node going down)                 |
|                                                                      |
|  UPDATE global: What's the best answer AT this node?                 |
|  (Usually a path THROUGH this node: left + node + right)             |
+----------------------------------------------------------------------+
```

**COMMON PATTERNS:**
- Path sum: track max path starting from node (return), update global with through-path
- Diameter: track max depth (return), update global with left + right
- House Robber III: return {rob_this, skip_this} pair

### **TEMPLATE: POST-ORDER DP**

```cpp
// General structure for Tree DP
pair<int, int> dfs(TreeNode* node) {
if (!node) return {baseCase1, baseCase2};          

auto [left1, left2] = dfs(node->left);             
auto [right1, right2] = dfs(node->right);          

// Compute current node's DP values from children  
int val1 = /* combine left1, right1, node->val */; 
int val2 = /* combine left2, right2, node->val */; 

// Update global answer if needed                  
globalAns = max(globalAns, /* some combination */);

return {val1, val2};                               

}
```

## **SOLVED: Binary Tree Maximum Path Sum (LC 124)**  HARD

PROBLEM: Find max sum path (any start to any end).

**KEY INSIGHT:**
For each node, compute:
1. Max path sum PASSING THROUGH this node (update global answer)
2. Max path sum STARTING from this node going down (return to parent)

```cpp
int maxPathSum(TreeNode* root) {
int maxSum = INT_MIN;                                          

function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {    
    if (!node) return 0;                                       

    // Get max gain from left and right (ignore negative paths)
    int leftGain = max(0, dfs(node->left));                    
    int rightGain = max(0, dfs(node->right));                  

    // Path through current node                               
    int pathSum = node->val + leftGain + rightGain;            
    maxSum = max(maxSum, pathSum);                             

    // Return max gain if continuing through this node         
    return node->val + max(leftGain, rightGain);               
};                                                             

dfs(root);                                                     
return maxSum;                                                 

}
```

TIME: O(N)  |  SPACE: O(H) where H = height

 **WHY THIS BASE CASE?**
```
if (!node) return 0 > Null node contributes 0 gain.
maxSum = INT_MIN (global) > Must handle all-negative trees.

leftGain = max(0, dfs(left)) > WHY max with 0?
```

> If a subtree's best path is NEGATIVE, don't include it!
> Taking a negative path would reduce our sum. Better to skip.
> max(0, gain) effectively says "use this subtree or don't".

Return: node->val + max(leftGain, rightGain) > WHY only one side?
> Parent can only use ONE path down from this node (can't fork).
> But GLOBAL update uses BOTH sides (path passing through this node).
> This "return vs update" distinction is the core of Tree DP.

## **SOLVED: Diameter of Binary Tree (LC 543)** 

PROBLEM: Longest path between any two nodes.

KEY INSIGHT: Diameter through node = leftHeight + rightHeight

```cpp
int diameterOfBinaryTree(TreeNode* root) {
int diameter = 0;                                             

function<int(TreeNode*)> height = [&](TreeNode* node) -> int {
    if (!node) return 0;                                      

    int left = height(node->left);                            
    int right = height(node->right);                          

    // Update diameter (path through this node)               
    diameter = max(diameter, left + right);                   

    // Return height                                          
    return 1 + max(left, right);                              
};                                                            

height(root);                                                 
return diameter;                                              

}
```

TIME: O(N)  |  SPACE: O(H)

 **WHY THIS BASE CASE?**
```
if (!node) return 0 > Null node has height 0.
diameter = 0 (global) > Minimum possible diameter.
```

Return: 1 + max(left, right) > Height of subtree rooted here.
Update: diameter = max(diameter, left + right) > Path THROUGH this node.
> Diameter through a node = left height + right height (edges, not nodes).
> We return HEIGHT to parent but update DIAMETER globally.
> Same "return vs update" pattern as Max Path Sum.

## **SOLVED: House Robber III (LC 337)** 

PROBLEM: Rob houses on tree, can't rob parent + child together.

KEY INSIGHT: Return {robThis, skipThis} for each node.

```cpp
int rob(TreeNode* root) {
// Returns {rob this node, skip this node}                                     
function<pair<int,int>(TreeNode*)> dfs = [&](TreeNode* node) -> pair<int,int> {
    if (!node) return {0, 0};                                                  

    auto [leftRob, leftSkip] = dfs(node->left);                                
    auto [rightRob, rightSkip] = dfs(node->right);                             

    // Rob this node: must skip children                                       
    int robThis = node->val + leftSkip + rightSkip;                            

    // Skip this node: take max from each child                                
    int skipThis = max(leftRob, leftSkip) + max(rightRob, rightSkip);          

    return {robThis, skipThis};                                                
};                                                                             

auto [rob, skip] = dfs(root);                                                  
return max(rob, skip);                                                         

}
```

TIME: O(N)  |  SPACE: O(H)

 **WHY THIS BASE CASE?**
```cpp
if (!node) return {0, 0} > Null node: 0 profit whether robbed or skipped.

robThis = node->val + leftSkip + rightSkip
```

> If we rob THIS node, we MUST skip both children (adjacency rule).

```
skipThis = max(leftRob, leftSkip) + max(rightRob, rightSkip)
```

> If we skip this node, each child independently chooses best option.
> Children are NOT adjacent to each other, so both can be robbed.

Return {robThis, skipThis} > Parent needs BOTH values to decide.
> This "return a pair" pattern avoids recomputation. Each node
computed exactly once in post-order traversal.

### PRACTICE PROBLEMS - Tree DP:

- 124.  Binary Tree Maximum Path Sum 
- 543.  Diameter of Binary Tree 
- 337.  House Robber III 
- 968.  Binary Tree Cameras 
- 834.  Sum of Distances in Tree (Rerooting) 

## **PATTERN 9: BITMASK DP** 

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- Small N < 20 (usually < 15)
- "Visit all nodes" / TSP
- "Assign items to groups"
- "Partition into subsets"
- Need to track which elements are used

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "I can represent ANY SUBSET using a single integer!                |
|   Bit i is 1 if element i is in the subset, 0 otherwise."           |
|                                                                     |
|   mask = 5 = 0b101 means {element 0, element 2} are selected        |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE CHECKBOXES:**
Imagine N checkboxes. Each mask is a unique combination of checked boxes.

For N=3: masks 0 to 7 cover all 8 subsets
0 = [ ][ ][ ]  = empty
1 = [Y][ ][ ]  = {0}
5 = [Y][ ][Y]  = {0, 2}
7 = [Y][Y][Y]  = {0, 1, 2}

 **COMPLEXITY AWARENESS**:
```
+----------------------------------------------------------------------+
|  N = 15 > 2^15 = 32,768 states       Fast                            |
|  N = 20 > 2^20 = 1,048,576 states    Borderline                      |
|  N = 25 > 2^25 = 33,554,432 states   Too slow                        |
|                                                                      |
|  Total time: O(2^N x N) or O(2^N x N2) depending on transitions      |
+----------------------------------------------------------------------+
```

### ** BIT OPERATIONS CHEATSHEET**

CHECK if i-th bit set:    mask & (1 << i)
SET i-th bit:             mask | (1 << i)
CLEAR i-th bit:           mask & ~(1 << i)
TOGGLE i-th bit:          mask ^ (1 << i)
COUNT set bits:           __builtin_popcount(mask)
LOWEST set bit:           mask & (-mask)
FULL mask for N items:    (1 << N) - 1

ITERATE over set bits:
```
for (int i = 0; i < n; i++) {
if (mask & (1 << i)) {              
    // i-th element is in the subset
}                                   

}
```

**STATE:**
```
dp[mask] = answer when subset represented by mask is processed
```

### **TEMPLATE: TSP-STYLE**

```cpp
// dp[mask][i] = min cost to visit nodes in mask, ending at node i
int tsp(vector<vector<int>>& dist) {
int n = dist.size();                                                   
int fullMask = (1 << n) - 1;                                           

// dp[mask][i] = min cost to reach node i with visited set = mask      
vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));               
dp[1][0] = 0;  // Start at node 0                                      

for (int mask = 1; mask < (1 << n); mask++) {                          
    for (int last = 0; last < n; last++) {                             
        if (!(mask & (1 << last))) continue;  // last not in mask      
        if (dp[mask][last] == INT_MAX) continue;                       

        for (int next = 0; next < n; next++) {                         
            if (mask & (1 << next)) continue;  // already visited      

            int newMask = mask | (1 << next);                          
            dp[newMask][next] = min(dp[newMask][next],                 
                                    dp[mask][last] + dist[last][next]);
        }                                                              
    }                                                                  
}                                                                      

// Return to start                                                     
int ans = INT_MAX;                                                     
for (int last = 0; last < n; last++) {                                 
    if (dp[fullMask][last] != INT_MAX) {                               
        ans = min(ans, dp[fullMask][last] + dist[last][0]);            
    }                                                                  
}                                                                      
return ans;                                                            

}
```

TIME: O(2^N x N2)  |  SPACE: O(2^N x N)

 **WHY THIS BASE CASE?**
```
dp[1][0] = 0 > "At node 0, having visited only node 0, cost = 0."
```

> mask = 1 means binary 0...001 > only node 0 is visited.
> We start the journey at node 0 with zero travel cost.
> All other dp values = INT_MAX (unreachable until computed).
> fullMask = (1<<n)-1 = all bits set = all nodes visited.

## **SOLVED: Shortest Path Visiting All Nodes (LC 847)** 

PROBLEM: Shortest path to visit all nodes (can revisit).

KEY INSIGHT: BFS with state = (currentNode, visitedMask)

```cpp
int shortestPathLength(vector<vector<int>>& graph) {
int n = graph.size();                             
int fullMask = (1 << n) - 1;                      

// BFS: {node, mask}                              
queue<pair<int, int>> q;                          
set<pair<int, int>> visited;                      

// Start from every node                          
for (int i = 0; i < n; i++) {                     
    q.push({i, 1 << i});                          
    visited.insert({i, 1 << i});                  
}                                                 

int steps = 0;                                    
while (!q.empty()) {                              
    int size = q.size();                          
    while (size--) {                              
        auto [node, mask] = q.front();            
        q.pop();                                  

        if (mask == fullMask) return steps;       

        for (int next : graph[node]) {            
            int newMask = mask | (1 << next);     
            if (!visited.count({next, newMask})) {
                visited.insert({next, newMask});  
                q.push({next, newMask});          
            }                                     
        }                                         
    }                                             
    steps++;                                      
}                                                 

return -1;                                        

}
```

TIME: O(2^N x N2)  |  SPACE: O(2^N x N)

 **WHY THIS BASE CASE?**
Start BFS from EVERY node: q.push({i, 1 << i}) for all i.
> Unlike TSP, there's no fixed start. Any node can be the start.
> State = (currentNode, visitedMask). BFS finds shortest path.
> mask == fullMask > all nodes visited > return steps.
> "Can revisit nodes" > BFS handles this by tracking (node, mask)
pairs, not just node. Same node with different masks = different states.

## **SOLVED: Partition to K Equal Sum Subsets (LC 698)** 

PROBLEM: Partition array into K subsets with equal sum.

**RECURSIVE (Top-Down with bitmask):**

```cpp
bool canPartitionKSubsets(vector<int>& nums, int k) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % k != 0) return false;
    int target = total / k;
    sort(nums.rbegin(), nums.rend());
    unordered_map<int, bool> memo;
    return solve(nums, 0, 0, k, target, memo);
}

bool solve(vector<int>& nums, int mask, int curSum, int k, int target,
           unordered_map<int, bool>& memo) {
    if (k == 0) return true;
    if (curSum == target) return solve(nums, mask, 0, k-1, target, memo);
    if (memo.count(mask)) return memo[mask];
    for (int i = 0; i < nums.size(); i++) {
        if (mask & (1 << i)) continue;
        if (curSum + nums[i] > target) continue;
        if (solve(nums, mask | (1 << i), curSum + nums[i], k, target, memo))
            return memo[mask] = true;
    }
    return memo[mask] = false;
}
```

**TABULATION (Bottom-Up bitmask):**

```cpp
int canPartitionKSubsets(vector<int>& nums, int k) {
int total = accumulate(nums.begin(), nums.end(), 0);                           
if (total % k != 0) return false;                                              
int target = total / k;                                                        

int n = nums.size();                                                           
vector<int> dp(1 << n, -1);                                                    
dp[0] = 0;  // dp[mask] = sum of current bucket                                

sort(nums.rbegin(), nums.rend());  // Optimization: try large first            

for (int mask = 0; mask < (1 << n); mask++) {                                  
    if (dp[mask] == -1) continue;                                              

    for (int i = 0; i < n; i++) {                                              
        if (mask & (1 << i)) continue;  // Already used                        
        if (dp[mask] + nums[i] > target) continue;  // Would overflow bucket   

        int newMask = mask | (1 << i);                                         
        dp[newMask] = (dp[mask] + nums[i]) % target;  // Reset when bucket full
    }                                                                          
}                                                                              

return dp[(1 << n) - 1] == 0;                                                  

}
```

TIME: O(N x 2^N)  |  SPACE: O(2^N)

 **WHY THIS BASE CASE?**
```
dp[0] = 0 > "Empty subset has current bucket sum = 0."
```

> dp[mask] stores the current bucket's running sum (mod target).
> When bucket fills up (sum == target), reset to 0 via % target.
> dp[(1<<n)-1] == 0 means all elements used AND all buckets exactly full.

total % k != 0 > return false
> If total sum isn't divisible by k, equal partition is impossible.

Sorting in descending order > optimization: large elements fail fast.

### PRACTICE PROBLEMS - Bitmask DP:

- 847.  Shortest Path Visiting All Nodes 
- 698.  Partition to K Equal Sum Subsets 
- 473.  Matchsticks to Square
- 1125. Smallest Sufficient Team 
- 1595. Minimum Cost to Connect Two Groups

## **PATTERN 10: DIGIT DP** 

### ** PATTERN RECOGNITION**

**RECOGNIZE BY:**
- "Count numbers in range [L, R] with property..."
- "Numbers with digit sum..."
- "Numbers without repeated digits"
- Very large range (up to 10^18)

 **THE "AHA" INSIGHT**:
```
+---------------------------------------------------------------------+
|  "I build the number digit by digit, tracking whether I'm still     |
|   'tight' (bounded by the upper limit) or 'free' to use any digit." |
|                                                                     |
|   Key: solve(R) - solve(L-1) = count in range [L, R]                |
+---------------------------------------------------------------------+
```

**MENTAL MODEL - THE DIGIT CONSTRUCTION:**
Building number 3456:
Position 0 (thousands): Can I put 4? NO, N starts with 3 (tight!)
If I put 2: Now I'm FREE (2 < 3), next positions can be 0-9
If I put 3: Still TIGHT, next position limited by N's next digit

 **THE TIGHT BOUND CONCEPT**:
```
+----------------------------------------------------------------------+
|  tight = true:  We've matched N exactly so far.                      |
|                 Next digit limited to < N's digit                    |
|                                                                      |
|  tight = false: We've gone smaller somewhere.                        |
|                 Next digit can be 0-9 freely!                        |
|                                                                      |
|  Example: N = 345                                                    |
|  Building 34_: tight, can only put 0-5                               |
|  Building 33_: free, can put 0-9                                     |
+----------------------------------------------------------------------+
```

 **THE "STARTED" FLAG** (for leading zeros):
```
+----------------------------------------------------------------------+
|  started = false: Haven't placed non-zero digit yet (leading zeros)  |
|  started = true:  Number has actually begun                          |
|                                                                      |
|  Important for: digit sum, no repeated digits, etc.                  |
|  Leading zeros don't count towards sum/restrictions!                 |
+----------------------------------------------------------------------+
```

**COMMON STATES:**
- pos: Current digit position (left to right)
- tight: Are we still bounded by N?
- started: Have we placed a non-zero digit?
- Problem-specific state (sum, last digit, used digits mask, etc.)

### **TEMPLATE**

```cpp
string num;
int memo[MAXLEN][STATES][2][2];  // pos, state, tight, started

int solve(int pos, int state, bool tight, bool started) {
if (pos == num.size()) {                                     
    return started ? (validState(state) ? 1 : 0) : 0;        
}                                                            

if (memo[pos][state][tight][started] != -1) {                
    return memo[pos][state][tight][started];                 
}                                                            

int limit = tight ? (num[pos] - '0') : 9;                    
int result = 0;                                              

// Try placing digit 0 to limit                              
for (int d = 0; d <= limit; d++) {                           
    bool newStarted = started || (d > 0);                    
    bool newTight = tight && (d == limit);                   
    int newState = updateState(state, d, newStarted);        

    result += solve(pos + 1, newState, newTight, newStarted);
}                                                            

return memo[pos][state][tight][started] = result;            

}

// Count in range [1, n]
int countInRange(string n) {
num = n;                                   
memset(memo, -1, sizeof(memo));            
return solve(0, initialState, true, false);

}
```

## **SOLVED: Numbers With Repeated Digits (LC 1012)** 

PROBLEM: Count numbers in [1, n] with at least one repeated digit.

TRICK: Count numbers with ALL UNIQUE digits, then subtract from n.

```cpp
int numDupDigitsAtMostN(int n) {
string s = to_string(n);                                                           
int len = s.size();                                                                

// Count numbers with all unique digits                                            
function<int(int, int, bool, bool)> solve = [&](int pos, int mask,                 
                                                 bool tight, bool started) -> int {
    if (pos == len) return started ? 1 : 0;                                        

    int limit = tight ? (s[pos] - '0') : 9;                                        
    int result = 0;                                                                

    if (!started) {                                                                
        // Can skip (leading zero)                                                 
        result += solve(pos + 1, mask, false, false);                              
    }                                                                              

    int startDigit = started ? 0 : 1;                                              
    for (int d = startDigit; d <= limit; d++) {                                    
        if (mask & (1 << d)) continue;  // Already used                            

        result += solve(pos + 1, mask | (1 << d),                                  
                      tight && (d == limit), true);                                
    }                                                                              

    return result;                                                                 
};                                                                                 

int uniqueCount = solve(0, 0, true, false);                                        
return n - uniqueCount;                                                            

}
```

TIME: O(10 x 2^10 x len)  |  SPACE: O(10 x 2^10)

 **WHY THIS BASE CASE?**
```
pos == len > return started ? 1 : 0
```

> Reached end of number. If we actually started building (non-zero digit
placed), count this as 1 valid number. If only leading zeros, don't count.

mask tracks which digits are USED (bitmask of 10 digits).
> If digit d's bit is already set in mask > skip (duplicate digit).
> started = false: haven't placed non-zero digit yet (leading zeros).
Can "skip" (keep adding leading zeros) or place first non-zero digit.

WHY n - uniqueCount?
> Easier to count numbers with ALL UNIQUE digits, then subtract.
> "At least one repeated" = total - "all unique".

## **SOLVED: Count of Integers (LC 2719)** 

PROBLEM: Count integers in [num1, num2] where digit sum is in [min_sum, max_sum].

```cpp
int count(string num1, string num2, int min_sum, int max_sum) {
const int MOD = 1e9 + 7;                                                                        

auto countUpTo = [&](string& s) -> long long {                                                  
    int n = s.size();                                                                           
    // memo[pos][digitSum][tight]                                                               
    vector<vector<vector<long long>>> dp(n,                                                     
        vector<vector<long long>>(401, vector<long long>(2, -1)));                              

    function<long long(int, int, bool)> solve = [&](int pos, int sum, bool tight) -> long long {
        if (sum > max_sum) return 0;                                                            
        if (pos == n) return sum >= min_sum ? 1 : 0;                                            
        if (dp[pos][sum][tight] != -1) return dp[pos][sum][tight];                              

        int limit = tight ? (s[pos] - '0') : 9;                                                 
        long long result = 0;                                                                   

        for (int d = 0; d <= limit; d++) {                                                      
            result = (result + solve(pos + 1, sum + d, tight && (d == limit))) % MOD;           
        }                                                                                       

        return dp[pos][sum][tight] = result;                                                    
    };                                                                                          

    return solve(0, 0, true);                                                                   
};                                                                                              

// Subtract 1 from num1 for range [num1, num2]                                                  
auto subtractOne = [](string& s) {                                                              
    int i = s.size() - 1;                                                                       
    while (i >= 0 && s[i] == '0') s[i--] = '9';                                                 
    if (i >= 0) s[i]--;                                                                         
    if (s[0] == '0' && s.size() > 1) s = s.substr(1);                                           
};                                                                                              

subtractOne(num1);                                                                              
return ((countUpTo(num2) - countUpTo(num1)) % MOD + MOD) % MOD;                                 

}
```

### PRACTICE PROBLEMS - Digit DP:

- 1012. Numbers With Repeated Digits 
- 2719. Count of Integers 
- 233.  Number of Digit One
- 600.  Non-negative Integers without Consecutive Ones
- 902.  Numbers At Most N Given Digit Set

## **PATTERN IDENTIFICATION FLOWCHART**

### **DECISION FLOWCHART**

Problem asks "minimum/maximum"?
```
                                                                       |
+- YES > Is it a contiguous subarray?                                   
|                                                                      |
|    +- YES > Pattern 7 (Kadane's Algorithm)                            
|                                                                      |
|    +- NO > Pattern 1 (Min/Max Path)                                   
                                                                       |
+- NO > "Count ways"?                                                   
                                                                       |
    +- YES > Is it counting numbers with digit properties?              
                                                                  |    |
    |    +- YES > Pattern 10 (Digit DP)                                 
                                                                  |    |
    |    +- NO > Pattern 2 (Distinct Ways)                              
                                                                       |
    +- NO > "Longest increasing subsequence"?                           
                                                                       |
        +- YES > Pattern 6 (LIS)                                        
                                                                       |
        +- NO > Two strings given?                                      
                                                                       |
            +- YES > Pattern 4 (DP on Strings)                          
                                                                       |
            +- NO > Tree structure?                                     
                                                                       |
                +- YES > Pattern 8 (Tree DP)                            
                                                                       |
                +- NO > "Take or skip" / adjacency constraint?          
                                                                       |
                    +- YES > Pattern 5 (Decision Making)                
                                                                       |
                    +- NO > Visit all nodes / subset selection (N < 20)?
                                                                       |
                        +- YES > Pattern 9 (Bitmask DP)                 
                                                                       |
                        +- NO > Merge/split intervals?                  
                                                                       |
                            +- YES > Pattern 3 (Merging Intervals)      
```

### **QUICK PATTERN IDENTIFICATION**

```
+----------------------------+------------------------------------------------+
| Keywords                   | Pattern                                        |
+----------------------------+------------------------------------------------+
| "Minimum cost/path"        | Pattern 1: Min/Max Path                        |
| "Maximum profit"           | Pattern 1 or Pattern 5                         |
| "Count ways"               | Pattern 2: Distinct Ways                       |
| "How many paths"           | Pattern 2: Distinct Ways                       |
| "Longest common"           | Pattern 4: DP on Strings                       |
| "Edit distance"            | Pattern 4: DP on Strings                       |
| "Palindrome"               | Pattern 4: DP on Strings                       |
| "Burst/merge/split"        | Pattern 3: Merging Intervals                   |
| "Can't take adjacent"      | Pattern 5: Decision Making                     |
| "Buy/sell stock"           | Pattern 5: Decision Making                     |
| "0/1 Knapsack"             | Pattern 5: Decision Making                     |
| "Longest increasing"       | Pattern 6: LIS                                 |
| "Max subarray sum"         | Pattern 7: Kadane's                            |
| "Tree path/diameter"       | Pattern 8: Tree DP                             |
| "Visit all nodes" (N<20)   | Pattern 9: Bitmask DP                          |
| "Count numbers in range"   | Pattern 10: Digit DP                           |
+----------------------------+------------------------------------------------+

===============================================================================
        **PART 9: COMMON MISTAKES & OPTIMIZATION**                             
===============================================================================
```

### **COMMON MISTAKES** 

### MISTAKE 1: Using INT_MAX without overflow protection

```
 dp[i] = INT_MAX;
dp[i] = min(dp[i], dp[j] + 1);  // Overflow if dp[j] = INT_MAX!

 dp[i] = n + 1;  // Use impossible value instead
```

### MISTAKE 2: Wrong base case initialization

For "count ways" problems:
```
 dp[0] = 0;  // Wrong!
 dp[0] = 1;  // One way to make 0
```

### MISTAKE 3: Iterating in wrong order (Bottom-Up)

Dependencies matter! Make sure you compute smaller subproblems first.

### MISTAKE 4: Not handling negative indices

```
 if (i - coin >= 0)  // After access!
 if (coin <= i)      // Before access
```

MISTAKE 5: Using memo without initialization
### Always initialize memo with -1 or special value!

**SPACE OPTIMIZATION TECHNIQUES**
### TECHNIQUE 1: Only keep what you need

If dp[i] only depends on dp[i-1] and dp[i-2]:
```cpp
 vector<int> dp(n);
```

 Keep only prev1 and prev2

### TECHNIQUE 2: Reuse input array

If allowed, modify input grid/array in-place for DP!

### TECHNIQUE 3: Rolling array (2D > 1D)

If dp[i][j] only depends on previous row:
```cpp
vector<vector<int>> dp(m, vector<int>(n));  // O(MN) space
```

> vector<int> dp(n);  // O(N) space
Update in-place or use two rows alternating

### **⚡ TECHNIQUE 4: 2D > 1D with 'prev' TRICK (THE DIAGONAL PROBLEM) ⚡**

**WHEN TO USE:**
When dp[i][j] depends on dp[i-1][j-1] (diagonal), dp[i-1][j] (top),
AND dp[i][j-1] (left). This is the case for:
> LCS, Edit Distance, Distinct Subsequences, Interleaving String, etc.

**THE PROBLEM:**

In 2D, dp[i][j] uses three cells:

```
 j-1     j       
+-------+-------+
```

```
i-1  | DIAG  |  TOP  |   DIAG = dp[i-1][j-1]
     |       |       |   TOP  = dp[i-1][j]  
     +-------+-------+   LEFT = dp[i][j-1]  
 i   | LEFT  | HERE                        |
     +-------+-----------------------------+
```

When we compress to 1D and overwrite left-to-right:
```
dp[j-1] was ALREADY overwritten with row i's value (LEFT )
dp[j] still holds row i-1's value (TOP )
dp[i-1][j-1] is GONE! It was overwritten when we computed dp[j-1] 
```

The diagonal value is DESTROYED. We need to SAVE it.

###  **CORE INTUITION: WHY dp[i-1][j] = dp[j] AND dp[i][j-1] = dp[j-1]**

KEY IDEA: We only have ONE array. When we finish row i-1 and start
row i, the ENTIRE dp array still holds row i-1's values (nobody
touched it yet). Then we overwrite cells one by one, left to right.

At ANY point during the j-loop, the array looks like this:

```
Index:    0    1    2   j-1   j   j+1  ...   n          
        +----+----+----+----+----+----+----+-----------+
dp:     | i  | i  | i  | i  |i-1 |i-1 |i-1 |i-1        |
        +----+----+----+----+----+----+----+-----------+
         <-- already updated ->  <-- not yet touched -->
               (current row)         (previous row)     
```

WALKTHROUGH - computing row 2 (i=2) left to right:

Start of row 2:  dp = [ old, old, old, old ]    < ALL from row 1

Compute j=1:     dp = [ old, NEW, old, old ]    < dp[1] overwritten
Compute j=2:     dp = [ old, NEW, NEW, old ]    < dp[2] overwritten
Now at j=3:      dp = [ old, NEW, NEW, old ]
^     ^
j-1=2  j=3

At j=3:
- dp[3] = "old"  > we haven't touched it > it's still row 1's value
> dp[3] IS dp[i-1][3] IS dp[i-1][j]  

- dp[2] = "NEW"  > we just computed it in this row (at j=2)
> dp[2] IS dp[i][2] IS dp[i][j-1]    

That's it. No trick needed for these two:
```
dp[j]   = dp[i-1][j]   because we haven't overwritten it yet
dp[j-1] = dp[i][j-1]   because we already overwritten it this row
```

The ONLY problem is dp[i-1][j-1] (the diagonal):
```
dp[j-1] was overwritten when we processed j-1, so the OLD value
```

(from row i-1) at position j-1 is GONE. That's why we need 'prev'.

### THE SOLUTION: 'prev' variable

Before overwriting dp[j], save the OLD dp[j] in 'temp'.
After overwriting, set prev = temp.
Now 'prev' holds the old dp[j] = dp[i-1][j], which becomes
```
dp[i-1][(j+1)-1] = the DIAGONAL for the NEXT iteration.
```

**STEP-BY-STEP RECIPE:**

1. Check: does row i only depend on row i-1? > YES, proceed.
2. Replace 2D array with 1D array of size (n+1), initialized to base row.
3. At start of each row: set prev = dp[0] (the column-0 base case).
4. For each j from 1 to n:
a. temp = dp[j]          < save old value (it's dp[i-1][j])
b. compute new dp[j] using:
- prev    = dp[i-1][j-1]  (diagonal)
- dp[j]   = dp[i-1][j]    (top, not yet overwritten)
- dp[j-1] = dp[i][j-1]    (left, already overwritten)
c. prev = temp           < for next iteration's diagonal

### WHY prev = 0 AT START OF EACH ROW?

The first diagonal needed is dp[i-1][0].
For LCS:   dp[i-1][0] = 0 (LCS of anything with empty string = 0)
For Edit:  dp[i-1][0] = i-1 (need i-1 deletes to make empty)
The value depends on the specific problem's column-0 base case.

### FULL EXAMPLE: LCS Space-Optimized

```cpp
int longestCommonSubsequence(string text1, string text2) {
int m = text1.size(), n = text2.size();                          
vector<int> dp(n + 1, 0);    // base row: all 0s (row 0)         

for (int i = 1; i <= m; i++) {                                   
    int prev = 0;             // dp[i-1][0] = 0                  
    for (int j = 1; j <= n; j++) {                               
        int temp = dp[j];     // save dp[i-1][j] before overwrite
        if (text1[i-1] == text2[j-1]) {                          
            dp[j] = prev + 1;            // DIAGONAL + 1         
        } else {                                                 
            dp[j] = max(dp[j], dp[j-1]); // max(TOP, LEFT)       
        }                                                        
        prev = temp;          // this becomes diagonal for j+1   
    }                                                            
}                                                                

return dp[n];                                                    

}
// TIME: O(M x N)  |  SPACE: O(N)
```

### TRACE: text1 = "ac", text2 = "abc"

dp starts as: [0, 0, 0, 0]   < base case (row 0)
```
j=0 j=1 j=2 j=3

i=1 (text1[0]='a'), prev=0:
j=1: temp=0, 'a'=='a'? YES > dp[1]=0+1=1, prev=0
j=2: temp=0, 'a'=='b'? NO  > dp[2]=max(0,1)=1, prev=0
j=3: temp=0, 'a'=='c'? NO  > dp[3]=max(0,1)=1, prev=0
dp = [0, 1, 1, 1]

i=2 (text1[1]='c'), prev=0:
j=1: temp=1, 'c'=='a'? NO  > dp[1]=max(1,0)=1, prev=1
j=2: temp=1, 'c'=='b'? NO  > dp[2]=max(1,1)=1, prev=1
j=3: temp=1, 'c'=='c'? YES > dp[3]=1+1=2, prev=1
dp = [0, 1, 1, 2]
```

Answer: dp[3] = 2 Y (LCS = "ac")

### FULL EXAMPLE: Edit Distance Space-Optimized

```cpp
int minDistance(string word1, string word2) {
int m = word1.size(), n = word2.size();                                
vector<int> dp(n + 1);                                                 

// Base row: dp[0][j] = j (insert j chars into empty string)           
for (int j = 0; j <= n; j++) dp[j] = j;                                

for (int i = 1; i <= m; i++) {                                         
    int prev = dp[0];    // dp[i-1][0] = i-1                           
    dp[0] = i;           // dp[i][0] = i (delete i chars to make empty)

    for (int j = 1; j <= n; j++) {                                     
        int temp = dp[j];                                              
        if (word1[i-1] == word2[j-1]) {                                
            dp[j] = prev;              // DIAGONAL (no operation)      
        } else {                                                       
            dp[j] = 1 + min({prev,     // DIAGONAL (replace)           
                             dp[j],    // TOP (delete)                 
                             dp[j-1]});// LEFT (insert)                
        }                                                              
        prev = temp;                                                   
    }                                                                  
}                                                                      

return dp[n];                                                          

}
// TIME: O(M x N)  |  SPACE: O(N)
```

NOTE: dp[0] = i updates the column-0 base case EACH ROW.
> dp[i][0] = i means "delete all i chars of word1 to get empty string".

```
+------------------------------------------------------------------------------+
|                  WHEN TO USE WHICH TECHNIQUE                                 |
+------------------------------+-----------------------------------------------+
| Dependency                   | Technique                                     |
+------------------------------+-----------------------------------------------+
| dp[i-1] and dp[i-2] only    | Two variables (prev1, prev2)                   |
| (Fibonacci, House Robber)    | Space: O(1)                                   |
+------------------------------+-----------------------------------------------+
| dp[i-1][j] and dp[i][j-1]   | 1D array, overwrite left-to-right              |
| NO diagonal needed           | Space: O(N)                                   |
| (Unique Paths, Min Path Sum) |                                               |
+------------------------------+-----------------------------------------------+
| dp[i-1][j-1], dp[i-1][j],   | 1D array + prev variable for diagonal          |
| dp[i][j-1] (DIAGONAL needed)| Space: O(N)                                    |
| (LCS, Edit Distance)        |                                                |
+------------------------------+-----------------------------------------------+
| 0/1 Knapsack                 | 1D array, iterate BACKWARDS                   |
| (Partition Subset, Target Sum| Space: O(target)                              |
+------------------------------+-----------------------------------------------+
| Unbounded Knapsack           | 1D array, iterate FORWARDS                    |
| (Coin Change, Coin Change II)| Space: O(target)                              |
+------------------------------+-----------------------------------------------+

================================================================================
        **MENTAL MODEL: BASE CASES & ITERATION ORDER**                          
================================================================================

+------------------------------------------------------------------------------+
|                    FINDING BASE CASES                                        |
+------------------------------------------------------------------------------+
|                                                                              |
|  Ask: "What's the SIMPLEST input I can answer immediately?"                  |
|                                                                              |
|  +---------------------------------------------------------+                 |
|  | Empty/Zero          | Single Element   | Two Elements   |                 |
|  +---------------------------------------------------------+                 |
|  | n=0, amount=0       | n=1, one char    | n=2, two items |                 |
|  | empty string        | base case!       | sometimes base |                 |
|  +---------------------------------------------------------+                 |
|                                                                              |
|  For MIN/MAX: target=0 > return 0, target<0 > return impossible              |
|  For COUNT:   target=0 > return 1, target<0 > return 0                       |
|  For STRINGS: empty string > return 0 or length                              |
|                                                                              |
+------------------------------------------------------------------------------+

+------------------------------------------------------------------------------+
|              TOP-DOWN > BOTTOM-UP CONVERSION                                 |
+------------------------------------------------------------------------------+
|                                                                              |
|  1. Parameters of recursion > DP table dimensions                            |
|  2. Base case returns > DP initialization                                    |
|  3. Recursion direction > REVERSE for iteration!                             |
|                                                                              |
|     Top-Down: solve(n) > solve(n-1) > ... > solve(0)                         |
|     Bottom-Up: dp[0] > dp[1] > ... > dp[n]                                   |
|                        ^                                                     |
|                    OPPOSITE DIRECTION!                                       |
|                                                                              |
|  4. return memo[x] = ... > dp[x] = ...                                       |
|  5. Final call solve(n) > return dp[n]                                       |
|                                                                              |
+------------------------------------------------------------------------------+

================================================================================
              **QUICK REFERENCE CHEAT SHEET**                                   
================================================================================
```

**PATTERN 1: MIN/MAX PATH**
```
dp[i] = min/max(dp[i-k]) + cost[i]
```

Base: dp[0] = 0
Invalid: return INT_MAX or amount+1

**PATTERN 2: DISTINCT WAYS**
```
dp[i] = sum(dp[i-k])
```

Base: dp[0] = 1   (one way to make 0)
Invalid: return 0

**PATTERN 3: MERGING INTERVALS**
```
dp[i][j] = best(dp[i][k] + dp[k+1][j])
```

Base: dp[i][i] = 0 or arr[i]
Order: Loop by LENGTH first! 

**PATTERN 4: DP ON STRINGS (Two Strings)**
```
if (s1[i] == s2[j])
dp[i][j] = dp[i-1][j-1] + ...
```

else
```
dp[i][j] = max/min(dp[i-1][j], dp[i][j-1])
```

Base: dp[0][j] = 0, dp[i][0] = 0 (or i, j for edit distance)

**PATTERN 5: DECISION MAKING**
```
dp[i] = max(take + dp[i-2], skip + dp[i-1])
```

Base: dp[0] = first element, dp[1] = max(first, second)

**PATTERN 6: LIS (Longest Increasing Subsequence)** 
```
O(N2): dp[i] = max(dp[j] + 1) for j < i where nums[j] < nums[i]
O(N log N): Binary search on tails array
```

Base: dp[i] = 1 (each element is LIS of length 1)

**PATTERN 7: KADANE'S (Max Subarray)** 
```
curr = max(nums[i], curr + nums[i])
globalMax = max(globalMax, curr)
```

For product: track both max AND min (negatives swap!)

**PATTERN 8: TREE DP** 
Post-order DFS: compute children before parent
Return {value1, value2} to parent
Update global answer at each node

**PATTERN 9: BITMASK DP**  (N < 20)
```
dp[mask] = answer for subset represented by mask
```

Check bit: mask & (1 << i)
Set bit: mask | (1 << i)
Time: O(2^N x N)

**PATTERN 10: DIGIT DP** 
Process digit by digit, track: pos, state, tight, started
```
tight=true: can only use digits < current digit of N
```

Count in [1, R]: solve(R) - solve(L-1)

**CONVERSION CHECKLIST:** 
1. States > DP dimensions
2. Base cases > Initialize DP
3. Dependencies > Iteration order
4. Recurrence > Same logic
5. Edge cases > if statements before loop
6. Return > dp[final]
7. Optimize > Keep only needed values

**STEPS TO SOLVE ANY DP:**
1. Identify the pattern (use keywords!)
2. Define state (what varies?)
3. Write recurrence relation
4. Identify base cases  (Use 4 strategies!)
5. Implement top-down (easier)
6. Convert to bottom-up  (Use 7 steps!)
7. Optimize space

## **10 PATTERNS QUICK REFERENCE**

CORE PATTERNS (Foundational):
Pattern 1:  Min/Max Path        > dp[i] = min(dp[i-k]) + cost
Pattern 2:  Distinct Ways       > dp[i] = sum(dp[i-k])
Pattern 3:  Merging Intervals   > dp[i][j] = best(dp[i][k] + dp[k+1][j])
Pattern 4:  DP on Strings       > Compare s1[i] vs s2[j]
Pattern 5:  Decision Making     > take + dp[i-2] vs skip + dp[i-1]

ADDITIONAL PATTERNS (Advanced):
Pattern 6:  LIS                 > Binary search on tails array
Pattern 7:  Kadane's            > curr = max(nums[i], curr + nums[i])
Pattern 8:  Tree DP             > Post-order DFS, return to parent
Pattern 9:  Bitmask DP          > dp[mask], N < 20
Pattern 10: Digit DP            > Digit by digit, tight bound

### **PROBLEM: Best Time to Buy and Sell Stock (LC 121)** 

PROBLEM: Find max profit from ONE transaction (buy once, sell once).

**RECURSIVE (Top-Down):**

```cpp
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> memo(n, vector<int>(2, -1));
    return solve(prices, 0, 0, memo);
}

int solve(vector<int>& prices, int i, int holding, vector<vector<int>>& memo) {
    if (i == prices.size()) return 0;
    if (memo[i][holding] != -1) return memo[i][holding];
    int doNothing = solve(prices, i+1, holding, memo);
    if (holding)
        return memo[i][holding] = max(doNothing, prices[i]);
    else
        return memo[i][holding] = max(doNothing,
            -prices[i] + solve(prices, i+1, 1, memo));
}
```

**TABULATION (Greedy O(1)):**

```cpp
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX, maxProfit = 0;
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}
```

TIME: O(N)  |  SPACE: O(1)

 **WHY THIS BASE CASE?**
```
minPrice = INT_MAX > "Haven't seen any price yet." First price will
```

always be smaller, so it becomes the new minimum.

```
maxProfit = 0 > "No transaction yet." Profit starts at 0.
```

> This is greedy, not full DP. At each price: update min, compute
potential profit. No table needed because we only look backwards
at the single best buy point.

### **PROBLEM: Best Time to Buy and Sell Stock II (LC 122)** 

PROBLEM: Max profit with UNLIMITED transactions.

**RECURSIVE (Top-Down):**

```cpp
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<int>> memo(n, vector<int>(2, -1));
    return solve(prices, 0, 0, memo);
}

int solve(vector<int>& prices, int i, int holding, vector<vector<int>>& memo) {
    if (i == prices.size()) return 0;
    if (memo[i][holding] != -1) return memo[i][holding];
    int doNothing = solve(prices, i+1, holding, memo);
    if (holding)
        return memo[i][holding] = max(doNothing,
            prices[i] + solve(prices, i+1, 0, memo));
    else
        return memo[i][holding] = max(doNothing,
            -prices[i] + solve(prices, i+1, 1, memo));
}
```

**TABULATION (Greedy O(1)):**

```cpp
int maxProfit(vector<int>& prices) {
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i-1])
            profit += prices[i] - prices[i-1];
    }
    return profit;
}
```

TIME: O(N)  |  SPACE: O(1)

 **WHY THIS BASE CASE?**
```
profit = 0 > "No transactions made yet."
```

> Greedy: sum every positive price increase.
> prices[i] > prices[i-1] means price went up > capture that profit.
> This works because buying/selling on consecutive days is equivalent
to buying on the first day and selling on the last day of an uptrend.

### **PROBLEM: Best Time to Buy and Sell Stock III (LC 123)** 

PROBLEM: Max profit with at most 2 transactions.

**RECURSIVE (Top-Down) — same as Stock IV with k=2:**

```cpp
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    vector<vector<vector<int>>> memo(n, vector<vector<int>>(3, vector<int>(2, -1)));
    return solve(prices, 0, 2, 0, memo);
}

int solve(vector<int>& prices, int i, int txLeft, int holding,
          vector<vector<vector<int>>>& memo) {
    if (i == prices.size() || txLeft == 0) return 0;
    if (memo[i][txLeft][holding] != -1) return memo[i][txLeft][holding];
    int doNothing = solve(prices, i+1, txLeft, holding, memo);
    if (holding)
        return memo[i][txLeft][holding] = max(doNothing,
            prices[i] + solve(prices, i+1, txLeft-1, 0, memo));
    else
        return memo[i][txLeft][holding] = max(doNothing,
            -prices[i] + solve(prices, i+1, txLeft, 1, memo));
}
```

**TABULATION (State machine O(1)):**

```cpp
int maxProfit(vector<int>& prices) {
    int buy1 = INT_MIN, sell1 = 0;
    int buy2 = INT_MIN, sell2 = 0;
    for (int price : prices) {
        buy1 = max(buy1, -price);
        sell1 = max(sell1, buy1 + price);
        buy2 = max(buy2, sell1 - price);
        sell2 = max(sell2, buy2 + price);
    }
    return sell2;
}
```

TIME: O(N)  |  SPACE: O(1)

 **WHY THIS BASE CASE?**
```
buy1 = INT_MIN, sell1 = 0, buy2 = INT_MIN, sell2 = 0
```

> buy1/buy2 = INT_MIN: "Haven't bought yet." Any real buy will be better.
> sell1/sell2 = 0: "No profit from selling yet."

4 states processed in ORDER for each price:
> buy1 = max(buy1, -price) > Best first buy so far.
> sell1 = max(sell1, buy1+price) > Best profit after first sell.
> buy2 = max(buy2, sell1-price) > Second buy USES first sell's profit.
> sell2 = max(sell2, buy2+price) > Final profit after second sell.
> Each state builds on the previous. This chain is what makes it work.

### **PROBLEM: Best Time to Buy/Sell Stock with Transaction Fee (LC 714)** 

PROBLEM: Max profit with unlimited transactions, but each transaction costs a fee.

**RECURSIVE (Top-Down):**

```cpp
int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    vector<vector<int>> memo(n, vector<int>(2, -1));
    return solve(prices, fee, 0, 0, memo);
}

int solve(vector<int>& prices, int fee, int i, int holding,
          vector<vector<int>>& memo) {
    if (i == prices.size()) return 0;
    if (memo[i][holding] != -1) return memo[i][holding];
    int doNothing = solve(prices, fee, i+1, holding, memo);
    if (holding)
        return memo[i][holding] = max(doNothing,
            prices[i] - fee + solve(prices, fee, i+1, 0, memo));
    else
        return memo[i][holding] = max(doNothing,
            -prices[i] + solve(prices, fee, i+1, 1, memo));
}
```

**TABULATION (State machine O(1)):**

```cpp
int maxProfit(vector<int>& prices, int fee) {
    int hold = -prices[0], cash = 0;
    for (int i = 1; i < prices.size(); i++) {
        cash = max(cash, hold + prices[i] - fee);
        hold = max(hold, cash - prices[i]);
    }
    return cash;
}
```

TIME: O(N)  |  SPACE: O(1)

 **WHY THIS BASE CASE?**
```
hold = -prices[0], cash = 0
```

> hold: "Bought stock on day 0." Cost = -prices[0].
> cash: "No stock held, no profit yet." = 0.
> Fee is subtracted when SELLING: cash = max(cash, hold+price-fee).
> This ensures fee is paid once per round-trip transaction.
> Same state machine as Stock II, just with fee deducted at sell.

### **PROBLEM: Unique Paths II (LC 63)** 

PROBLEM: Count unique paths in grid with obstacles. Can only move right or down.

 PATTERN: Distinct Ways (Pattern 2)
 TEMPLATE: dp[i][j] = dp[i-1][j] + dp[i][j-1], but 0 if obstacle

 **KEY INSIGHT**: Same as Unique Paths (LC 62) but dp[i][j] = 0 whenever
grid[i][j] is an obstacle. Also check if start or end is blocked!

**RECURSIVE (Top-Down):**

```cpp
int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    if (grid[0][0] == 1 || grid[m-1][n-1] == 1) return 0;
    vector<vector<int>> memo(m, vector<int>(n, -1));
    return solve(grid, m-1, n-1, memo);
}

int solve(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& memo) {
    if (i < 0 || j < 0 || grid[i][j] == 1) return 0;
    if (i == 0 && j == 0) return 1;
    if (memo[i][j] != -1) return memo[i][j];
    return memo[i][j] = solve(grid, i-1, j, memo) + solve(grid, i, j-1, memo);
}
```

**TABULATION (Bottom-Up):**

```cpp
int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    if (grid[0][0] == 1 || grid[m-1][n-1] == 1) return 0;

    vector<vector<long long>> dp(m, vector<long long>(n, 0));
    dp[0][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) { dp[i][j] = 0; continue; }
            if (i > 0) dp[i][j] += dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}
```

TIME: O(M x N)  |  SPACE: O(M x N)

 **WHY THIS BASE CASE?**
```
dp[0][0] = 1 > Starting point (0,0) has exactly 1 path: already there.
grid[0][0] == 1 or grid[m-1][n-1] == 1 > return 0
```

> If start or end is blocked, no path exists. Check BEFORE DP.

```
grid[i][j] == 1 > dp[i][j] = 0, skip
```

> Obstacle cells are unreachable. Zero paths through them.
> Unlike Unique Paths I where first row/col = 1, here an obstacle
in first row BLOCKS all cells to its right (they stay 0).

### **PROBLEM: Word Break (LC 139)** 

PROBLEM: Can string s be segmented into words from dictionary?

 PATTERN: DP on Strings (Pattern 4)
 TEMPLATE: dp[i] = true if s[0..i-1] can be segmented

 **KEY INSIGHT**: dp[i] = true if there exists j < i such that dp[j] is
true AND s[j..i-1] is a word in the dictionary. Try all split points!

**RECURSIVE (Top-Down):**

```cpp
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    vector<int> memo(s.size(), -1);
    return solve(s, 0, dict, memo);
}

bool solve(string& s, int start, unordered_set<string>& dict, vector<int>& memo) {
    if (start == s.size()) return true;
    if (memo[start] != -1) return memo[start];
    for (int end = start + 1; end <= s.size(); end++) {
        if (dict.count(s.substr(start, end - start)) && solve(s, end, dict, memo))
            return memo[start] = 1;
    }
    return memo[start] = 0;
}
```

**TABULATION (Bottom-Up):**

```cpp
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && dict.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}
```

TIME: O(N2 x M)  |  SPACE: O(N)  where M = max word length

 **WHY THIS BASE CASE?**
```
dp[0] = true > "Empty string can be segmented." (Vacuously true.)
```

> This seeds the DP: dp[i] = true if there exists j where dp[j] is true
AND s[j..i-1] is a dictionary word.

> Without dp[0] = true, the first word can never be recognized.
e.g. s = "leet", dict = {"leet"}: dp[4] needs dp[0] = true.

```
dp[1..n] = false > "Not yet proven to be segmentable."
```

### **PROBLEM: Word Break II (LC 140)** 

PROBLEM: Return ALL possible word break segmentations of string s.

 PATTERN: DP on Strings (Pattern 4) - Backtracking + Memoization
 TEMPLATE: Recursive DFS with memoization on start index

 **KEY INSIGHT**: Unlike Word Break I which only checks feasibility, we need
all solutions. Use backtracking from each index, trying every word that
matches at that position, and memoize results per start index.

```cpp
vector<string> wordBreak(string s, vector<string>& wordDict) {
unordered_set<string> dict(wordDict.begin(), wordDict.end());
unordered_map<int, vector<string>> memo;                     
return backtrack(s, 0, dict, memo);                          

}

vector<string> backtrack(string& s, int start,
                     unordered_set<string>& dict,               
                     unordered_map<int, vector<string>>& memo) {
if (memo.count(start)) return memo[start];                      
if (start == s.size()) return {""};                             

vector<string> result;                                          
for (int end = start + 1; end <= s.size(); end++) {             
    string word = s.substr(start, end - start);                 
    if (dict.count(word)) {                                     
        auto rest = backtrack(s, end, dict, memo);              
        for (auto& r : rest) {                                  
            result.push_back(word + (r.empty() ? "" : " " + r));
        }                                                       
    }                                                           
}                                                               

return memo[start] = result;                                    

}
```

TIME: O(N x 2^N) worst case  |  SPACE: O(N x 2^N)

 **WHY THIS BASE CASE?**
```
start == s.size() > return {""}
```

> Reached end of string successfully. Return vector with empty string
to signal "valid segmentation found". The caller prepends its word.

> If we returned empty vector {}, no sentence would ever be built.

### **PROBLEM: Coin Change II (LC 518)** 

PROBLEM: Count number of combinations to make amount (coins can be reused).

 PATTERN: Distinct Ways (Pattern 2) - Unbounded Knapsack
 TEMPLATE: Outer loop = coins, inner loop = amounts (for combinations)

 **KEY INSIGHT**: Loop coins OUTSIDE, amounts INSIDE to count combinations
(not permutations). Each coin is considered once, avoiding duplicates.
Compare with Combination Sum IV (LC 377) which loops amounts outside for
permutations!

**RECURSIVE (Top-Down):**

```cpp
int change(int amount, vector<int>& coins) {
    vector<vector<int>> memo(coins.size(), vector<int>(amount + 1, -1));
    return solve(coins, 0, amount, memo);
}

int solve(vector<int>& coins, int idx, int amt, vector<vector<int>>& memo) {
    if (amt == 0) return 1;
    if (idx == coins.size() || amt < 0) return 0;
    if (memo[idx][amt] != -1) return memo[idx][amt];
    return memo[idx][amt] = solve(coins, idx, amt - coins[idx], memo)
                          + solve(coins, idx + 1, amt, memo);
}
```

**TABULATION (Bottom-Up):**

```cpp
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int j = coin; j <= amount; j++) {
            dp[j] += dp[j - coin];
        }
    }

    return dp[amount];
}
```

TIME: O(N x amount)  |  SPACE: O(amount)

 CRITICAL DIFFERENCE:
Combinations (this problem): outer loop = coins, inner = amounts
Permutations (LC 377):       outer loop = amounts, inner = coins

 **WHY THIS BASE CASE?**
```
dp[0] = 1 > "1 way to make amount 0: use no coins."
```

> Same as all COUNT problems: dp[0] = 1, not 0.

WHY forward loop (j = coin to amount), not backward?
> This is UNBOUNDED knapsack: coins can be reused!
> Forward loop allows dp[j-coin] to use already-updated values
```python
from this row > same coin used multiple times. Exactly what we want.
```

> Compare with 0/1 Knapsack (Partition Subset) which loops BACKWARD
to prevent reusing items.

### **PROBLEM: Palindrome Partitioning II (LC 132)** 

PROBLEM: Minimum cuts to partition string into all palindromes.

 PATTERN: DP on Strings (Pattern 4)
 TEMPLATE: dp[i] = min cuts for s[0..i], precompute palindrome table

 **KEY INSIGHT**: Two-phase DP. First precompute isPalin[i][j] for all
substrings. Then dp[i] = min(dp[j-1] + 1) for all j where s[j..i] is
a palindrome. If s[0..i] itself is a palindrome, dp[i] = 0 (no cuts).

**RECURSIVE (Top-Down):**

```cpp
int minCut(string s) {
    int n = s.size();
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));
    for (int len = 1; len <= n; len++)
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && (len <= 2 || isPalin[i+1][j-1]))
                isPalin[i][j] = true;
        }

    vector<int> memo(n, -1);
    return solve(s, 0, isPalin, memo);
}

int solve(string& s, int start, vector<vector<bool>>& isPalin, vector<int>& memo) {
    if (start == s.size()) return -1;
    if (memo[start] != -1) return memo[start];
    int best = INT_MAX;
    for (int end = start; end < s.size(); end++) {
        if (isPalin[start][end])
            best = min(best, 1 + solve(s, end + 1, isPalin, memo));
    }
    return memo[start] = best;
}
```

**TABULATION (Bottom-Up):**

```cpp
int minCut(string s) {
    int n = s.size();
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));

    for (int len = 1; len <= n; len++)
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && (len <= 2 || isPalin[i+1][j-1]))
                isPalin[i][j] = true;
        }

    vector<int> dp(n, INT_MAX);
    for (int i = 0; i < n; i++) {
        if (isPalin[0][i]) { dp[i] = 0; continue; }
        for (int j = 1; j <= i; j++) {
            if (isPalin[j][i])
                dp[i] = min(dp[i], dp[j-1] + 1);
        }
    }

    return dp[n-1];
}
```

TIME: O(N2)  |  SPACE: O(N2)

 **WHY THIS BASE CASE?**
```
isPalin[i][j]: precomputed palindrome table.
```

> isPalin base: len <= 2 && s[i]==s[j] > true.

```
dp[i] = INT_MAX > "Unknown minimum cuts."
dp[i] = 0 if isPalin[0][i] > "Entire s[0..i] is a palindrome. No cuts needed."
```

> This is the KEY optimization: if the whole prefix is already a
palindrome, we skip the inner loop entirely.

> Otherwise: dp[i] = min(dp[j-1] + 1) for all j where s[j..i] is palindrome.
"Best cut = best answer for s[0..j-1] + 1 more cut before s[j..i]."

## **SOLVED: Super Egg Drop (LC 887)**  HARD

**RECURSIVE (Top-Down) — binary search optimization:**

```cpp
int superEggDrop(int k, int n) {
    unordered_map<int, int> memo;
    return solve(k, n, memo);
}

int solve(int k, int n, unordered_map<int, int>& memo) {
    if (n <= 1 || k == 1) return n;
    int key = n * 1000 + k;
    if (memo.count(key)) return memo[key];

    int lo = 1, hi = n;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        int breakCase = solve(k-1, mid-1, memo);
        int noBreak = solve(k, n-mid, memo);
        if (breakCase < noBreak) lo = mid;
        else hi = mid;
    }
    return memo[key] = 1 + min(max(solve(k-1, lo-1, memo), solve(k, n-lo, memo)),
                                max(solve(k-1, hi-1, memo), solve(k, n-hi, memo)));
}
```

**TABULATION (Bottom-Up) — reverse thinking:**

```cpp
int superEggDrop(int k, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    int m = 0;
    while (dp[m][k] < n) {
        m++;
        for (int j = 1; j <= k; j++)
            dp[m][j] = dp[m-1][j-1] + dp[m-1][j] + 1;
    }
    return m;
}
```

 **WHY THIS BASE CASE?**
```
dp[0][j] = 0 for all j > "0 moves, any eggs > can check 0 floors."
dp[m][0] = 0 for all m > "Any moves, 0 eggs > can check 0 floors."
```

REVERSE THINKING: Instead of "min moves for n floors", ask
"max floors checkable with m moves and k eggs?"
> dp[m][k] = dp[m-1][k-1] + dp[m-1][k] + 1
> If egg breaks: check dp[m-1][k-1] floors below.
> If egg survives: check dp[m-1][k] floors above.
> +1 for the floor we just tested.
> Stop when dp[m][k] >= n.

## **SOLVED: Maximum Profit in Job Scheduling (LC 1235)** 

**RECURSIVE (Top-Down):**

```cpp
int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    int n = startTime.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return startTime[a] < startTime[b];
    });

    vector<int> sortedStart;
    for (int i : idx) sortedStart.push_back(startTime[i]);

    vector<int> memo(n, -1);
    return solve(0, idx, sortedStart, endTime, profit, memo);
}

int solve(int i, vector<int>& idx, vector<int>& sortedStart,
          vector<int>& endTime, vector<int>& profit, vector<int>& memo) {
    if (i >= idx.size()) return 0;
    if (memo[i] != -1) return memo[i];
    int next = lower_bound(sortedStart.begin(), sortedStart.end(),
                           endTime[idx[i]]) - sortedStart.begin();
    return memo[i] = max(solve(i+1, idx, sortedStart, endTime, profit, memo),
                         profit[idx[i]] + solve(next, idx, sortedStart, endTime, profit, memo));
}
```

**TABULATION (Bottom-Up):**

```cpp
int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    int n = startTime.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return endTime[a] < endTime[b];
    });

    vector<int> dp(n + 1, 0);
    vector<int> ends;
    for (int i : idx) ends.push_back(endTime[i]);

    for (int i = 0; i < n; i++) {
        int j = upper_bound(ends.begin(), ends.begin() + i,
                            startTime[idx[i]]) - ends.begin();
        dp[i + 1] = max(dp[i], dp[j] + profit[idx[i]]);
    }
    return dp[n];
}
```

 **WHY THIS BASE CASE?**
```
dp[0] = 0 > "Before any job, profit = 0."
```

> Jobs sorted by end time. dp[i+1] = max(dp[i], dp[j] + profit[i]).
> dp[i] = "don't take job i" (carry forward previous best).
> dp[j] + profit[i] = "take job i" (find last non-overlapping job j
```
using binary search on end times).
```

> Binary search: upper_bound finds first job ending AFTER current start.

## **COMPLETE PROBLEM LIST BY PATTERN**

**PATTERN 1: MIN/MAX PATH**
- 746.  Min Cost Climbing Stairs 
- 322.  Coin Change 
- 64.   Minimum Path Sum
- 120.  Triangle

**PATTERN 2: DISTINCT WAYS**
- 70.   Climbing Stairs 
- 62.   Unique Paths 
- 63.   Unique Paths II 
- 377.  Combination Sum IV
- 494.  Target Sum 
- 416.  Partition Equal Subset Sum
- 279.  Perfect Squares
- 518.  Coin Change II 

**PATTERN 3: MERGING INTERVALS**
- 312.  Burst Balloons 
- 96.   Unique Binary Search Trees
- 1130. Minimum Cost Tree From Leaf Values
- 1000. Minimum Cost to Merge Stones 

**PATTERN 4: DP ON STRINGS**
- 1143. Longest Common Subsequence 
- 72.   Edit Distance 
- 647.  Palindromic Substrings
- 516.  Longest Palindromic Subsequence 
- 115.  Distinct Subsequences 
- 1092. Shortest Common Supersequence
- 97.   Interleaving String
- 10.   Regular Expression Matching 
- 139.  Word Break 
- 140.  Word Break II 
- 132.  Palindrome Partitioning II 

**PATTERN 5: DECISION MAKING**
- 198.  House Robber 
- 213.  House Robber II
- 121.  Best Time to Buy/Sell Stock 
- 122.  Best Time to Buy/Sell Stock II 
- 123.  Best Time to Buy/Sell Stock III 
- 309.  Best Time to Buy/Sell Stock with Cooldown 
- 188.  Best Time to Buy/Sell Stock IV 
- 714.  Best Time to Buy/Sell Stock with Transaction Fee 
- 740.  Delete and Earn
- 887.  Super Egg Drop 
- 1235. Maximum Profit in Job Scheduling 

**PATTERN 6: LIS (Longest Increasing Subsequence)**
- 300.  Longest Increasing Subsequence 
- 673.  Number of Longest Increasing Subsequence 
- 354.  Russian Doll Envelopes 
- 1964. Find Longest Valid Obstacle Course
- 1048. Longest String Chain
- 368.  Largest Divisible Subset

**PATTERN 7: KADANE'S (Max Subarray)**
- 53.   Maximum Subarray 
- 918.  Maximum Sum Circular Subarray 
- 152.  Maximum Product Subarray 
- 1749. Maximum Absolute Sum

**PATTERN 8: TREE DP**
- 124.  Binary Tree Maximum Path Sum 
- 543.  Diameter of Binary Tree 
- 337.  House Robber III 
- 968.  Binary Tree Cameras 
- 834.  Sum of Distances in Tree (Rerooting) 

**PATTERN 9: BITMASK DP**
- 847.  Shortest Path Visiting All Nodes 
- 698.  Partition to K Equal Sum Subsets 
- 473.  Matchsticks to Square
- 1125. Smallest Sufficient Team 
- 1595. Minimum Cost to Connect Two Groups

**PATTERN 10: DIGIT DP**
- 1012. Numbers With Repeated Digits 
- 2719. Count of Integers 
- 233.  Number of Digit One
- 600.  Non-negative Integers without Consecutive Ones
- 902.  Numbers At Most N Given Digit Set

## ** PATTERN INSIGHTS CHEATSHEET - INTERVIEW READY **

```
+------------------------------------------------------------------------------+
| PATTERN 1 (Min/Max Path):                                                    |
|   "To reach i optimally, come from the BEST previous state + cost"           |
|    Pitfall: INT_MAX overflow when adding                                     |
+------------------------------------------------------------------------------+
| PATTERN 2 (Distinct Ways):                                                   |
|   "Ways to reach here = SUM of ways from all previous states"                |
|    Pitfall: dp[0] = 1 not 0 (one way to reach start)                         |
|    Pitfall: Order of loops matters (permutations vs combinations)            |
+------------------------------------------------------------------------------+
| PATTERN 3 (Merging Intervals):                                               |
|   "Try every split point k, combine left and right subproblems"              |
|    Pitfall: Must loop by LENGTH first, not by start position                 |
|    Trick: Think backwards - "which element to remove LAST?"                  |
+------------------------------------------------------------------------------+
| PATTERN 4 (DP on Strings):                                                   |
|   "Match: use diagonal | No match: use adjacent cells"                       |
|    Pitfall: Compare s[i-1] not s[i] (dp indices are 1-based)                 |
|    Single string palindrome = compare string with its reverse (LCS)          |
+------------------------------------------------------------------------------+
| PATTERN 5 (Decision Making):                                                 |
|   "At each item: TAKE (skip previous) or SKIP (use previous)"                |
|    Pitfall: 0/1 Knapsack inner loop must go BACKWARDS                        |
|    State machine: draw states and transitions                                |
+------------------------------------------------------------------------------+
| PATTERN 6 (LIS):                                                             |
|   "O(N2): For each i, look back at all j < i where nums[j] < nums[i]"        |
|   "O(N log N): Binary search on smallest possible tails"                     |
|    Strictly increasing = lower_bound | Non-decreasing = upper_bound          |
+------------------------------------------------------------------------------+
| PATTERN 7 (Kadane's):                                                        |
|   "Extend previous subarray OR start fresh here"                             |
|    Pitfall: Initialize with nums[0], not 0 (all negatives case)              |
|    Product: Track BOTH max AND min (negatives flip signs!)                   |
+------------------------------------------------------------------------------+
| PATTERN 8 (Tree DP):                                                         |
|   "Post-order: compute children first, then parent"                          |
|    Return to parent = what CAN parent use from my subtree                    |
|    Update global = best answer AT this node                                  |
+------------------------------------------------------------------------------+
| PATTERN 9 (Bitmask DP):                                                      |
|   "Represent subset as integer, each bit = element presence"                 |
|    Constraint: N < 20 (2^20 ~ 1M states)                                     |
|    Check bit: mask & (1<<i) | Set bit: mask | (1<<i)                         |
+------------------------------------------------------------------------------+
| PATTERN 10 (Digit DP):                                                       |
|   "Build number digit by digit, track 'tight' bound"                         |
|    Range [L,R] = solve(R) - solve(L-1)                                       |
|    'started' flag handles leading zeros                                      |
+------------------------------------------------------------------------------+

================================================================================
                                **END**                                         
================================================================================
```
