# **PREFIX SUM - COMPLETE GUIDE**

### **TABLE OF CONTENTS**

1. Core Concepts & Templates
2. Pattern Recognition Guide
3. Section 1: Standard Prefix Sum
4. Section 2: Prefix Sum with Modulo/Divisibility
5. Section 3: Prefix Sum with XOR (Bit Manipulation)
6. Section 4: 2D Prefix Sum
7. Quick Revision Table

## **PART 1: CORE CONCEPTS**

### ** WHEN TO USE PREFIX SUM?**

**STRONG SIGNALS:**

 "Count subarrays" with some property
 "Subarray sum equals K"
 "Divisible by K" problems
 Array has negative numbers (Sliding Window won't work!)
 "Even/odd frequency" problems
 Range queries on immutable array
 "XOR of subarray"

### WHY NOT SLIDING WINDOW?

- Negative numbers make window sum non-monotonic
- Can't maintain valid window easily
- Need to check ALL possible subarrays

**GOLDEN RULE:**
> If Sliding Window fails due to negatives or non-monotonic state,
try Prefix Sum!

### ** FUNDAMENTAL CONCEPT**

 **MEMORY AID**: "**P**refix **S**ubtraction = **S**ubarray **S**um"
Think: psum[i] - psum[j] = sum of elements between j and i

**KEY INSIGHT:**
If psum[i] - psum[j] = K
Then subarray [j+1...i] has sum = K

**MATHEMATICAL FOUNDATION:**
psum[i] = arr[0] + arr[1] + ... + arr[i]
psum[j] = arr[0] + arr[1] + ... + arr[j]

psum[i] - psum[j] = arr[j+1] + arr[j+2] + ... + arr[i] = K

**THEREFORE:**
We look for: psum[j] = psum[i] - K

At index i, check if (psum[i] - K) exists in hashmap!

### ** UNIVERSAL TEMPLATE**

 **MEMORY AID for Initialization**:
**C**ount > map[0] = **1** (count of seeing sum=0 once)
**L**ength > map[0] = **-1** (index before array starts)

**FOR COUNTING PROBLEMS:**

int psum = 0;
unordered_map<int, int> countMap;
countMap[0] = 1;  //  Count: Initialize with 1
int ans = 0;

for (int i = 0; i < n; i++) {
```
psum += arr[i];  // or psum ^= arr[i] for XOR

// Check if (psum - K) exists                
if (countMap.count(psum - K)) {              
    ans += countMap[psum - K];               
}                                            

countMap[psum]++;  // Record current psum    
```

}

return ans;

**FOR LENGTH PROBLEMS:**

int psum = 0;
unordered_map<int, int> indexMap;
indexMap[0] = -1;  //  Length: Initialize with -1 (before start)
int maxLen = 0;

for (int i = 0; i < n; i++) {
```
psum += arr[i];                                   

// Check if (psum - K) exists                     
if (indexMap.count(psum - K)) {                   
    maxLen = max(maxLen, i - indexMap[psum - K]); 
}                                                 

// Only update if not exists (keep earliest index)
if (!indexMap.count(psum)) {                      
    indexMap[psum] = i;                           
}                                                 
```

}

return maxLen;

###  WHY Initialize map[0]?

FOR COUNTING: map[0] = 1
- If psum[i] - K = 0, entire subarray [0...i] is valid
- We need to count this case, so initialize map[0] = 1

FOR LENGTH: map[0] = -1
- If psum[i] - K = 0, entire subarray [0...i] is valid
- Length = i - (-1) = i + 1 (correct!)

## **PART 2: PATTERN RECOGNITION**

```
+-----------------------------------------------------------------------------+
| Problem Keywords            | Pattern               | Key Technique         |
+-----------------------------+-----------------------+-----------------------+
| "subarray sum equals K"     | Standard Prefix Sum   | psum - K in map       |
| "divisible by K"            | Modulo Prefix Sum     | (psum % K + K) % K    |
| "even/odd frequency"        | XOR Prefix Sum        | psum ^= bit           |
| "range queries"             | Precomputed Prefix    | psum[r] - psum[l-1]   |
| "2D matrix sum"             | 2D Prefix Sum         | Inclusion-Exclusion   |
| "negative numbers"          | Prefix Sum (not SW)   | HashMap tracking      |
+-----------------------------+-----------------------+-----------------------+

===============================================================================
      **PART 3: SECTION 1 - STANDARD PREFIX SUM**                              
===============================================================================
```

### **BRILLIANT TRANSFORMATIONS** 

 Equal 0s and 1s > Track diff = count(0) - count(1)
When diff repeats, we have equal counts between those indices

 K odd numbers > Transform: odd>1, even>0, find sum = K
Converts "count odds" to "subarray sum" problem

 Remove from ends > Find max middle with sum = total - x
Minimum operations = n - maximum_middle_length

 Divisible by K > Store remainders, same remainder = divisible diff
psum[i] % K = psum[j] % K > (psum[j] - psum[i]) % K = 0

### 1. Subarray Sum Equals K (LC 560)  FUNDAMENTAL

 PATTERN: Count subarrays with exact sum
 TEMPLATE: Standard Prefix Sum

**KEY INSIGHT:**
- If psum[i] - psum[j] = K, then subarray [j+1...i] has sum K
- At index i, look for (psum[i] - K) in hashmap
- Count how many times we've seen that value before

**WHY IT WORKS:**
- Each occurrence of (psum - K) represents a valid starting point
- Example: [1, 2, 3], K=3
- At i=1: psum=3, look for 0 (found in map[0]=1) > count=1
- At i=2: psum=6, look for 3 (found once) > count=2

**COMMON MISTAKES:**
 Forgetting to initialize map[0] = 1
 Updating map before checking
 Check first, then update map

int subarraySum(vector<int>& nums, int k) {
```
unordered_map<int, int> countMap;      
countMap[0] = 1;  // Important!        

int psum = 0, ans = 0;                 

for (int i = 0; i < nums.size(); i++) {
    psum += nums[i];                   

    // Check if (psum - k) exists      
    if (countMap.count(psum - k)) {    
        ans += countMap[psum - k];     
    }                                  

    countMap[psum]++;                  
}                                      

return ans;                            
```

}
// Time: O(N), Space: O(N)

### 2. Maximum Size Subarray Sum Equals K (LC 325)

 PATTERN: Find maximum length
 TEMPLATE: Index Map (keep earliest)

**KEY INSIGHT:**
- For maximum length, keep EARLIEST occurrence of each psum
- Don't update if psum already exists
- Length = current_index - earliest_index

WHY KEEP EARLIEST?
- We want maximum length
- Earlier index gives longer subarray
- Example: If psum=5 at i=2 and i=7, keep i=2

int maxSubArrayLen(vector<int>& nums, int k) {
```
unordered_map<int, int> indexMap;                    
indexMap[0] = -1;  // For full array case            

int psum = 0, maxLen = 0;                            

for (int i = 0; i < nums.size(); i++) {              
    psum += nums[i];                                 

    if (indexMap.count(psum - k)) {                  
        maxLen = max(maxLen, i - indexMap[psum - k]);
    }                                                

    // Only store if not exists (keep earliest)      
    if (!indexMap.count(psum)) {                     
        indexMap[psum] = i;                          
    }                                                
}                                                    

return maxLen;                                       
```

}
// Time: O(N), Space: O(N)

### 3. Range Sum Query - Immutable (LC 303)

 PATTERN: Range queries with precomputation
 TEMPLATE: Precomputed prefix array

**KEY INSIGHT:**
- Precompute prefix sums once: O(N)
- Answer queries in O(1)
- sum[i..j] = psum[j+1] - psum[i]

class NumArray {
vector<int> psum;

public:
```
NumArray(vector<int>& nums) {           
    int n = nums.size();                
    psum.resize(n + 1, 0);              

    for (int i = 0; i < n; i++) {       
        psum[i + 1] = psum[i] + nums[i];
    }                                   
}                                       

int sumRange(int left, int right) {     
    return psum[right + 1] - psum[left];
}                                       
```

};
// Constructor: O(N), Query: O(1)

### 4. Count Number of Nice Subarrays (LC 1248)

 PATTERN: Transform to binary + prefix sum
 TEMPLATE: Convert to 1/0, then standard prefix sum

**KEY INSIGHT:**
- "K odd numbers" > convert odd=1, even=0
- Now it's "subarray sum equals K"
- Same template as LC 560!

int numberOfSubarrays(vector<int>& nums, int k) {
```
unordered_map<int, int> countMap;                
countMap[0] = 1;                                 

int psum = 0, ans = 0;                           

for (int num : nums) {                           
    psum += (num % 2);  // Count only odd numbers

    if (countMap.count(psum - k)) {              
        ans += countMap[psum - k];               
    }                                            

    countMap[psum]++;                            
}                                                

return ans;                                      
```

}
// Time: O(N), Space: O(N)

### 5. Contiguous Array (LC 525)  BRILLIANT TRANSFORMATION

 PATTERN: Maximum length subarray with equal 0s and 1s
 TRANSFORMATION: Track diff = count(0) - count(1)

KEY INSIGHT (GENIUS!):
- Equal 0s and 1s > count(0) - count(1) = 0
- Transform: 0 > -1, 1 > 1 (or just track difference)
- When same diff appears again > equal counts in between!
- Find longest subarray where diff returns to same value

**WHY THIS WORKS:**
[0,1,0,1] with 2 zeros and 2 ones
diffs: [1,0,1,0] (count 0s minus 1s)
diff=0 at index 1 and 3 > subarray [2,3] has equal
But we want max, so diff=0 at -1 and 3 > length 4

int findMaxLength(vector<int>& nums) {
```
int maxLen = 0;                                       
unordered_map<int, int> mp;                           
mp[0] = -1;  // For full array case                   

int zeros = 0, ones = 0;                              

for (int i = 0; i < nums.size(); i++) {               
    if (nums[i] == 0) zeros++;                        
    else ones++;                                      

    int diff = zeros - ones;                          

    if (mp.count(diff)) {                             
        maxLen = max(maxLen, i - mp[diff]);           
    } else {                                          
        mp[diff] = i;  // Keep earliest for max length
    }                                                 
}                                                     

return maxLen;                                        
```

}
// Time: O(N), Space: O(N)

### 6. Minimum Operations to Reduce X to Zero (LC 1658) 

 PATTERN: Reverse thinking (find maximum middle)
 TEMPLATE: Find longest subarray with sum = total - x

KEY INSIGHT (BRILLIANT!):
- Remove from ends > keep middle subarray
- Want maximum middle subarray with sum = (total - x)
- Minimum removals = n - maximum_middle_length

**WHY IT WORKS:**
- [1,1,4,2,3], x=5, total=11
- Need middle sum = 11-5 = 6
- Find longest subarray with sum 6: [4,2] length 2
- Answer = 5 - 2 = 3 operations

int minOperations(vector<int>& nums, int x) {
```
int total = accumulate(nums.begin(), nums.end(), 0);      
int target = total - x;                                   

if (target == 0) return nums.size();                      
if (target < 0) return -1;                                

unordered_map<int, int> indexMap;                         
indexMap[0] = -1;                                         

int psum = 0, maxLen = -1;                                

for (int i = 0; i < nums.size(); i++) {                   
    psum += nums[i];                                      

    if (indexMap.count(psum - target)) {                  
        maxLen = max(maxLen, i - indexMap[psum - target]);
    }                                                     

    if (!indexMap.count(psum)) {                          
        indexMap[psum] = i;                               
    }                                                     
}                                                         

return maxLen == -1 ? -1 : nums.size() - maxLen;          
```

}
// Time: O(N), Space: O(N)

## **PART 4: SECTION 2 - PREFIX SUM WITH MODULO/DIVISIBILITY**

###  MATHEMATICAL FOUNDATION

**DIVISIBILITY RULE:**
If (psum[i] - psum[j]) is divisible by K, then:
(psum[i] - psum[j]) % K = 0
psum[i] % K = psum[j] % K

So we look for same remainder!

**NEGATIVE REMAINDER HANDLING:**
C++ gives negative remainder for negative numbers
Fix: ((psum % K) + K) % K

Example: -5 % 3 = -2 in C++
Fix: ((-2) + 3) % 3 = 1 Y

**GOLDEN RULE:**
> For divisibility, store and check: ((psum % K) + K) % K

### 6. Subarray Sums Divisible by K (LC 974) 

 PATTERN: Divisibility with modulo
 TEMPLATE: Store remainder, handle negatives

**KEY INSIGHT:**
- If psum[i] % K = psum[j] % K, subarray [j+1...i] divisible by K
- Must handle negative remainders!
- Formula: ((psum + num) % K + K) % K

WHY HANDLE NEGATIVES?
- [-1, 2, 9], K=2
- At i=0: psum=-1, -1%2=-1 in C++ (wrong!)
- Fix: ((-1%2) + 2) % 2 = 1

int subarraysDivByK(vector<int>& nums, int k) {
```
unordered_map<int, int> countMap;                          
countMap[0] = 1;                                           

int psum = 0, ans = 0;                                     

for (int num : nums) {                                     
    psum = ((psum + num) % k + k) % k;  // Handle negatives

    if (countMap.count(psum)) {                            
        ans += countMap[psum];                             
    }                                                      

    countMap[psum]++;                                      
}                                                          

return ans;                                                
```

}
// Time: O(N), Space: O(K)

### 7. Continuous Subarray Sum (LC 523)

 PATTERN: Divisibility + minimum length constraint
 TEMPLATE: Store index, check length > 2

**KEY INSIGHT:**
- Same as above, but length must be > 2
- Store indices, check: i - map[remainder] > 1

bool checkSubarraySum(vector<int>& nums, int k) {
```
unordered_map<int, int> indexMap;      
indexMap[0] = -1;                      

int psum = 0;                          

for (int i = 0; i < nums.size(); i++) {
    psum = (psum + nums[i]) % k;       

    if (indexMap.count(psum)) {        
        if (i - indexMap[psum] > 1) {  
            return true;               
        }                              
    } else {                           
        indexMap[psum] = i;            
    }                                  
}                                      

return false;                          
```

}
// Time: O(N), Space: O(K)

### 8. Make Sum Divisible by P (LC 1590)  HARD

 PATTERN: Remove smallest subarray with remainder
 TEMPLATE: Find shortest subarray with sum % p = remainder

KEY INSIGHT (BRILLIANT!):
- remainder = totalSum % p
- Find SMALLEST subarray with sum % p = remainder
- Remove it > rest is divisible by p!

**WHY IT WORKS:**
- total = X * p + remainder
- Remove subarray = remainder
- Left = X * p (divisible!)

int minSubarray(vector<int>& nums, int p) {
```
long long total = accumulate(nums.begin(), nums.end(), 0LL);
int remainder = total % p;                                  

if (remainder == 0) return 0;                               

unordered_map<int, int> indexMap;                           
indexMap[0] = -1;                                           

int psum = 0, minLen = nums.size();                         

for (int i = 0; i < nums.size(); i++) {                     
    psum = (psum + nums[i]) % p;                            

    int target = (psum - remainder + p) % p;                
    if (indexMap.count(target)) {                           
        minLen = min(minLen, i - indexMap[target]);         
    }                                                       

    indexMap[psum] = i;  // Overwrite (want shortest)       
}                                                           

return minLen == nums.size() ? -1 : minLen;                 
```

}
// Time: O(N), Space: O(P)

### 9. Count of Interesting Subarrays (LC 2845)

 PATTERN: Binary transformation + modulo prefix sum
 TEMPLATE: Combine two techniques

**KEY INSIGHT:**
- Convert to binary: nums[i] % modulo == k > 1, else > 0
- Then apply modulo prefix sum technique
- Count subarrays where (count of 1s) % modulo == k

long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
```
// Step 1: Convert to binary                                   
int n = nums.size();                                           
for (int i = 0; i < n; i++) {                                  
    nums[i] = (nums[i] % modulo == k) ? 1 : 0;                 
}                                                              

// Step 2: Apply modulo prefix sum                             
unordered_map<long long, long long> countMap;                  
countMap[0] = 1;                                               

long long psum = 0, ans = 0;                                   

for (int num : nums) {                                         
    psum = (psum + num) % modulo;                              

    long long target = ((psum - k) % modulo + modulo) % modulo;
    if (countMap.count(target)) {                              
        ans += countMap[target];                               
    }                                                          

    countMap[psum]++;                                          
}                                                              

return ans;                                                    
```

}
// Time: O(N), Space: O(modulo)

## **PART 5: SECTION 3 - PREFIX SUM WITH XOR**

###  XOR PROPERTIES FOR PREFIX SUM

**KEY PROPERTIES:**
1. a ^ a = 0 (self-cancellation)
2. a ^ 0 = a (identity)
3. XOR is commutative and associative
4. If a ^ b = c, then a = b ^ c

**FOR PREFIX XOR:**
If pxor[i] ^ pxor[j] = K
Then XOR of subarray [j+1...i] = K

**EVEN/ODD FREQUENCY DETECTION:**
- XOR perfect for tracking even/odd occurrences
- Even occurrences > bit becomes 0
- Odd occurrences > bit becomes 1

**WHEN TO USE:**
 "Even frequency" problems
 "At most 1 odd" problems
 "Palindrome with at most 1 odd char"

### 10. Number of Wonderful Substrings (LC 1915)  HARD

 PATTERN: XOR bitmask for frequency tracking
 TEMPLATE: Check even AND at-most-1-odd cases

**KEY INSIGHT:**
- "Wonderful" = all even frequencies OR exactly 1 odd
- Use bitmask: bit i = 1 if char i has odd count
- Check: same mask (all even) + toggle each bit (1 odd)

WHY BITMASK?
- 10 characters (0-9) > 10 bits
- Bit i = 0: char i appears even times
- Bit i = 1: char i appears odd times

**BRILLIANT TECHNIQUE:**
- Check mask (all even)
- Check mask ^ (1<<i) for each i (toggle one bit for "1 odd")

long long wonderfulSubstrings(string word) {
```
unordered_map<int, int> countMap;              
countMap[0] = 1;                               

int mask = 0;                                  
long long ans = 0;                             

for (char c : word) {                          
    mask ^= (1 << (c - 'a'));                  

    // Case 1: All even (same mask seen before)
    if (countMap.count(mask)) {                
        ans += countMap[mask];                 
    }                                          

    // Case 2: Exactly 1 odd (toggle each bit) 
    for (int i = 0; i < 10; i++) {             
        int toggledMask = mask ^ (1 << i);     
        if (countMap.count(toggledMask)) {     
            ans += countMap[toggledMask];      
        }                                      
    }                                          

    countMap[mask]++;                          
}                                              

return ans;                                    
```

}
// Time: O(N * 10), Space: O(2^10) = O(1024)

### 11. Find Longest Awesome Substring (LC 1542)  HARD

 PATTERN: XOR bitmask + maximum length
 TEMPLATE: Track earliest index for each mask

**KEY INSIGHT:**
- "Awesome" = palindrome = at most 1 odd frequency
- Same approach as above but track LENGTH
- Keep earliest index for maximum length

int longestAwesome(string s) {
```
unordered_map<int, int> indexMap;                           
indexMap[0] = -1;                                           

int mask = 0, maxLen = 0;                                   

for (int i = 0; i < s.size(); i++) {                        
    mask ^= (1 << (s[i] - '0'));                            

    // Case 1: All even                                     
    if (indexMap.count(mask)) {                             
        maxLen = max(maxLen, i - indexMap[mask]);           
    }                                                       

    // Case 2: Exactly 1 odd                                
    for (int j = 0; j < 10; j++) {                          
        int toggledMask = mask ^ (1 << j);                  
        if (indexMap.count(toggledMask)) {                  
            maxLen = max(maxLen, i - indexMap[toggledMask]);
        }                                                   
    }                                                       

    // Store earliest occurrence                            
    if (!indexMap.count(mask)) {                            
        indexMap[mask] = i;                                 
    }                                                       
}                                                           

return maxLen;                                              
```

}
// Time: O(N * 10), Space: O(2^10)

### 12. Longest Substring with Vowels in Even Counts (LC 1371)

 PATTERN: XOR bitmask (vowels only)
 TEMPLATE: Simpler - only check same mask

**KEY INSIGHT:**
- Only vowels matter (5 bits: a,e,i,o,u)
- All must be even > check same mask
- Ignore consonants

int findTheLongestSubstring(string s) {
```
unordered_map<int, int> indexMap;                   
indexMap[0] = -1;                                   

int mask = 0, maxLen = 0;                           
unordered_map<char, int> vowelBit = {               
    {'a', 0}, {'e', 1}, {'i', 2}, {'o', 3}, {'u', 4}
};                                                  

for (int i = 0; i < s.size(); i++) {                
    if (vowelBit.count(s[i])) {                     
        mask ^= (1 << vowelBit[s[i]]);              
    }                                               

    if (indexMap.count(mask)) {                     
        maxLen = max(maxLen, i - indexMap[mask]);   
    } else {                                        
        indexMap[mask] = i;                         
    }                                               
}                                                   

return maxLen;                                      
```

}
// Time: O(N), Space: O(2^5) = O(32)

## **PART 6: SECTION 4 - 2D PREFIX SUM**

###  2D PREFIX SUM FORMULAS

COMPUTE FORMULA (Inclusion-Exclusion):
psum[i+1][j+1] = psum[i][j+1] + psum[i+1][j] - psum[i][j] + grid[i][j]

Why -psum[i][j]? Because it's counted twice!

QUERY FORMULA (Extract Rectangle):
sum(r1,c1 to r2,c2) = psum[r2+1][c2+1]
- psum[r1][c2+1]
- psum[r2+1][c1]
+ psum[r1][c1]

Why +psum[r1][c1]? Because it's subtracted twice!

**IMPORTANT:**
- psum array is (m+1) x (n+1) in size
- Use 1-based indexing for psum
- Original grid is 0-based

**VISUAL:**
+-------+-------+
| [i,j] | add   |
+-------+-------+
| add   |-sub   |
+-------+-------+

### 13. Range Sum Query 2D - Immutable (LC 304) 

 PATTERN: Precompute 2D prefix sum
 TEMPLATE: Build once, query in O(1)

class NumMatrix {
vector<vector<int>> psum;

public:
```
NumMatrix(vector<vector<int>>& matrix) {                 
    int m = matrix.size(), n = matrix[0].size();         
    psum.resize(m + 1, vector<int>(n + 1, 0));           

    // Build 2D prefix sum                               
    for (int i = 0; i < m; i++) {                        
        for (int j = 0; j < n; j++) {                    
            psum[i+1][j+1] = psum[i][j+1] + psum[i+1][j] 
                           - psum[i][j] + matrix[i][j];  
        }                                                
    }                                                    
}                                                        

int sumRegion(int r1, int c1, int r2, int c2) {          
    return psum[r2+1][c2+1] - psum[r1][c2+1]             
         - psum[r2+1][c1] + psum[r1][c1];                
}                                                        
```

};
// Constructor: O(M*N), Query: O(1)

### 14. Matrix Block Sum (LC 1314)

 PATTERN: 2D prefix sum with boundary handling
 TEMPLATE: Build psum, then query each cell

**KEY INSIGHT:**
- For each cell, need sum of rectangle within distance K
- Use 2D prefix sum for O(1) queries
- Handle boundaries with max/min

vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
```
int m = mat.size(), n = mat[0].size();                 
vector<vector<int>> psum(m + 1, vector<int>(n + 1, 0));

// Build 2D prefix sum                                 
for (int i = 0; i < m; i++) {                          
    for (int j = 0; j < n; j++) {                      
        psum[i+1][j+1] = psum[i][j+1] + psum[i+1][j]   
                       - psum[i][j] + mat[i][j];       
    }                                                  
}                                                      

// Query for each cell                                 
for (int i = 0; i < m; i++) {                          
    for (int j = 0; j < n; j++) {                      
        int r1 = max(0, i - k);                        
        int c1 = max(0, j - k);                        
        int r2 = min(m - 1, i + k);                    
        int c2 = min(n - 1, j + k);                    

        mat[i][j] = psum[r2+1][c2+1] - psum[r1][c2+1]  
                  - psum[r2+1][c1] + psum[r1][c1];     
    }                                                  
}                                                      

return mat;                                            
```

}
// Time: O(M*N), Space: O(M*N)

### 15. Maximal Square (LC 221)

 PATTERN: DP with 2D prefix sum concept
 TEMPLATE: Check neighbors for square formation

**KEY INSIGHT:**
- For each cell with '1', check if it can form square
- dp[i][j] = min(top, left, diagonal) + 1
- This is like prefix sum but using min

int maximalSquare(vector<vector<char>>& matrix) {
```
int m = matrix.size(), n = matrix[0].size();                           
vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));                  
int maxSide = 0;                                                       

for (int i = 0; i < m; i++) {                                          
    for (int j = 0; j < n; j++) {                                      
        if (matrix[i][j] == '1') {                                     
            dp[i+1][j+1] = 1 + min({dp[i][j+1], dp[i+1][j], dp[i][j]});
            maxSide = max(maxSide, dp[i+1][j+1]);                      
        }                                                              
    }                                                                  
}                                                                      

return maxSide * maxSide;                                              
```

}
// Time: O(M*N), Space: O(M*N)

### 16. Maximum Difference Score in a Grid (LC 3148) 

 PATTERN: 2D prefix minimum
 TEMPLATE: Track minimum in path

KEY INSIGHT (BRILLIANT!):
- Can only move right or down
- Score = grid[i][j] - grid[prev]
- Want maximum score > minimize grid[prev]
- Track minimum value reachable from top-left!

**WHY IT WORKS:**
- Score from multiple moves cancels: (c2-c1) + (c3-c2) = c3-c1
- Only first and last matter
- Find minimum predecessor for each cell

int maxScore(vector<vector<int>>& grid) {
```
int m = grid.size(), n = grid[0].size();                               
vector<vector<int>> pmin(m + 1, vector<int>(n + 1, INT_MAX));          
int maxScore = INT_MIN;                                                

for (int i = 1; i <= m; i++) {                                         
    for (int j = 1; j <= n; j++) {                                     
        // Minimum reachable from top-left to this position            
        pmin[i][j] = min({grid[i-1][j-1], pmin[i-1][j], pmin[i][j-1]});
    }                                                                  
}                                                                      

for (int i = 1; i <= m; i++) {                                         
    for (int j = 1; j <= n; j++) {                                     
        if (i == 1 && j == 1) continue;                                

        // Best score ending at this cell                              
        int prevMin = min(pmin[i-1][j], pmin[i][j-1]);                 
        maxScore = max(maxScore, grid[i-1][j-1] - prevMin);            
    }                                                                  
}                                                                      

return maxScore;                                                       
```

}
// Time: O(M*N), Space: O(M*N)

## **PART 7: QUICK REVISION TABLE**

```
+-----------------------------------------------------------------------------+
|                         PATTERN SELECTION GUIDE                             |
+---------------------------+---------------------+---------------------------+
| Problem Type              | Technique           | Key Formula               |
+---------------------------+---------------------+---------------------------+
| Subarray sum = K          | Standard Prefix Sum | psum - K in map           |
| Maximum length            | Store earliest idx  | Keep first occurrence     |
| Divisible by K            | Modulo Prefix Sum   | ((psum%K)+K)%K            |
| Even/odd frequency        | XOR Prefix Sum      | psum ^= (1 << bit)        |
| At most 1 odd             | XOR + toggle bits   | Check mask ^ (1<<i)       |
| 2D matrix sum             | 2D Prefix Sum       | Inclusion-Exclusion       |
| Range queries             | Precomputed Prefix  | O(1) query                |
+---------------------------+---------------------+---------------------------+

+-----------------------------------------------------------------------------+
|                         INITIALIZATION RULES                                |
+-----------------------------------------------------------------------------+
|                                                                             |
| FOR COUNTING: countMap[0] = 1                                               |
|   * Handles case where entire prefix is answer                              |
|   * Example: [1,2,3], K=6 > psum=6 at i=2, look for 0                       |
|                                                                             |
| FOR LENGTH: indexMap[0] = -1                                                |
|   * Handles full array case                                                 |
|   * Length = i - (-1) = i + 1 Y                                             |
|                                                                             |
| FOR 2D: psum[m+1][n+1] (one extra row/col)                                  |
|   * Simplifies boundary handling                                            |
|   * Use 1-based indexing for psum                                           |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                         CRITICAL FORMULAS                                   |
+-----------------------------------------------------------------------------+
|                                                                             |
| 1. STANDARD PREFIX SUM                                                      |
|    target = psum - K                                                        |
|    if (map.count(target)) ans += map[target]                                |
|                                                                             |
| 2. MODULO PREFIX SUM (Handle Negatives!)                                    |
|    psum = ((psum + num) % K + K) % K                                        |
|    target = ((psum - K) % K + K) % K                                        |
|                                                                             |
| 3. XOR PREFIX SUM                                                           |
|    psum ^= (1 << char_to_bit[c])                                            |
|    Check same mask: map[psum]                                               |
|    Check 1 odd: map[psum ^ (1 << i)] for each i                             |
|                                                                             |
| 4. 2D BUILD                                                                 |
|    psum[i+1][j+1] = psum[i][j+1] + psum[i+1][j]                             |
|                   - psum[i][j] + grid[i][j]                                 |
|                                                                             |
| 5. 2D QUERY                                                                 |
|    sum = psum[r2+1][c2+1] - psum[r1][c2+1]                                  |
|        - psum[r2+1][c1] + psum[r1][c1]                                      |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                         COMMON MISTAKES                                     |
+-----------------------------------------------------------------------------+
|                                                                             |
|  MISTAKE 1: Not initializing map[0]                                         |
|    FIX: countMap[0] = 1 or indexMap[0] = -1                                 |
|                                                                             |
|  MISTAKE 2: Not handling negative remainders                                |
|    FIX: ((psum % K) + K) % K                                                |
|                                                                             |
|  MISTAKE 3: Updating map before checking                                    |
|    FIX: Check psum-K first, THEN update map[psum]                           |
|                                                                             |
|  MISTAKE 4: Wrong 2D psum size                                              |
|    FIX: Use (m+1) x (n+1) size                                              |
|                                                                             |
|  MISTAKE 5: Overwriting index for max length                                |
|    FIX: if (!map.count(psum)) map[psum] = i                                 |
|                                                                             |
|  MISTAKE 6: XOR with wrong bit position                                     |
|    FIX: mask ^= (1 << (c - 'a')) for char offset                            |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                       GOLDEN RULES - MEMORIZE!                              |
+-----------------------------------------------------------------------------+
|                                                                             |
|  1⃣  psum[i] - psum[j] = subarray [j+1...i] sum                             |
|                                                                             |
|  2⃣  For counting: countMap[0] = 1, update AFTER checking                   |
|                                                                             |
|  3⃣  For length: indexMap[0] = -1, DON'T overwrite (keep earliest)          |
|                                                                             |
|  4⃣  Divisibility: use ((psum % K) + K) % K to handle negatives             |
|                                                                             |
|  5⃣  XOR for even/odd: psum ^= (1 << bit), check same mask                  |
|                                                                             |
|  6⃣  At most 1 odd: check mask AND mask^(1<<i) for each bit                 |
|                                                                             |
|  7⃣  2D psum: size (m+1)x(n+1), use Inclusion-Exclusion principle           |
|                                                                             |
|  8⃣  Time: O(N) for 1D, O(M*N) for 2D; Space: O(N) or O(M*N)                |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                        INTERVIEW CHEAT CODES                                |
+-----------------------------------------------------------------------------+
|                                                                             |
|   "This has negative numbers, so Sliding Window won't work. I'll use        |
|      Prefix Sum with a hashmap to track previous sums."                     |
|                                                                             |
|   "For divisibility problems, I need to check if remainders match:          |
|      psum[i] % K == psum[j] % K."                                           |
|                                                                             |
|   "Even/odd frequency problems are perfect for XOR prefix sum, where        |
|      bits track parity of each character."                                  |
|                                                                             |
|   "For 2D matrix queries, I'll precompute prefix sums using inclusion-      |
|      exclusion to answer each query in O(1)."                               |
|                                                                             |
|   "I'll initialize map[0] to handle the case where the entire prefix        |
|      from the start is a valid answer."                                     |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
                **PROBLEM LIST BY CATEGORY**                                   
===============================================================================
```

SECTION 1: STANDARD PREFIX SUM
Y 560.  Subarray Sum Equals K 
Y 325.  Maximum Size Subarray Sum Equals K
Y 303.  Range Sum Query - Immutable
Y 525.  Contiguous Array  (Equal 0s and 1s - BRILLIANT)
Y 1248. Count Number of Nice Subarrays
Y 930.  Binary Subarrays With Sum
Y 1658. Minimum Operations to Reduce X to Zero 
- 523.  Continuous Subarray Sum (Divisibility + length >= 2)
- 1480. Running Sum of 1D Array
- 2559. Count Vowel Strings in Ranges

SECTION 2: MODULO/DIVISIBILITY
Y 974.  Subarray Sums Divisible by K 
Y 523.  Continuous Subarray Sum
Y 1590. Make Sum Divisible by P  HARD
Y 2845. Count of Interesting Subarrays
- 1497. Check If Array Pairs Are Divisible by K
- 2575. Find the Divisibility Array of a String

SECTION 3: XOR PREFIX SUM
Y 1915. Number of Wonderful Substrings  HARD
Y 1542. Find Longest Awesome Substring  HARD
Y 1371. Find Longest Substring (Vowels Even)
- 1310. XOR Queries of a Subarray
- 1442. Count Triplets (Equal XOR)

SECTION 4: 2D PREFIX SUM
Y 304.  Range Sum Query 2D - Immutable 
Y 1314. Matrix Block Sum
Y 221.  Maximal Square
Y 3148. Maximum Difference Score in Grid 
- 2132. Stamping the Grid (Advanced)
- 2201. Count Artifacts That Can Be Extracted

## END

