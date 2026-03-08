# COMBINATORICS: COMPLETE TECHNIQUES GUIDE

```
Combinatorics = Math of counting, arranging, and selecting objects
```

Essential for: DP, probability, optimization, counting problems

## TABLE OF CONTENTS

1. Basic Counting Principles
2. Permutations & Combinations
3. Stars and Bars
4. Inclusion-Exclusion Principle
5. Pigeonhole Principle
6. Binomial Coefficients & Pascal's Triangle
7. Catalan Numbers
8. Derangements
9. Partitions
10. Generating Functions
11. Running Sum Pattern (Already Covered)
12. Problem Recognition Guide

## 1. BASIC COUNTING PRINCIPLES

RULE OF SUM (Addition Principle):
----------------------------------
If there are m ways to do A and n ways to do B (mutually exclusive),
then there are m + n ways to do A OR B.

Example: Choose a shirt
- 5 red shirts OR 3 blue shirts
- Total: 5 + 3 = 8 choices

RULE OF PRODUCT (Multiplication Principle):
--------------------------------------------
If there are m ways to do A and n ways to do B (independent),
then there are m x n ways to do A AND B.

Example: Choose outfit
- 5 shirts AND 3 pants
- Total: 5 x 3 = 15 outfits

Code Pattern:
```
total = ways_A * ways_B * ways_C * ...
```

## 2. PERMUTATIONS & COMBINATIONS

PERMUTATIONS (Order Matters):
------------------------------
```
P(n, r) = n! / (n-r)!
```

= Number of ways to arrange r items from n items

Example: Choose 3 winners from 5 contestants
```
P(5, 3) = 5!/(5-3)! = 5x4x3 = 60
```

(1st place, 2nd place, 3rd place are different)

Special Case: P(n, n) = n! (arrange all n items)

Code:
```
long permutation(int n, int r) {
  long result = 1;             
  for (int i = 0; i < r; i++) {
      result *= (n - i);       
  }                            
  return result;               

}
```

COMBINATIONS (Order Doesn't Matter):
-------------------------------------
```
C(n, r) = n! / (r! x (n-r)!)
```

= Number of ways to choose r items from n items

Example: Choose 3 team members from 5 people
```
C(5, 3) = 5!/(3!x2!) = 10
```

(ABC is same as BAC, CBA, etc.)

Common formulas:
```
C(n, 0) = 1
C(n, 1) = n
C(n, 2) = nx(n-1)/2
C(n, n) = 1
C(n, r) = C(n, n-r)
```

Code:
```
long combination(int n, int r) {
  if (r > n - r) r = n - r;  // Optimize
  long result = 1;                      
  for (int i = 0; i < r; i++) {         
      result *= (n - i);                
      result /= (i + 1);                
  }                                     
  return result;                        

}
```

Problems:
- Choose k items from n items
- Count subsets of specific size
- Binomial expansion

**PERMUTATIONS WITH REPETITION:**
------------------------------
n^r = ways to arrange r items from n types (with replacement)

Example: 4-digit PIN from 10 digits
10^4 = 10,000 possibilities

**COMBINATIONS WITH REPETITION:**
------------------------------
```
C(n+r-1, r) = ways to choose r items from n types (with replacement)
```

Example: Buy 3 fruits from 4 types
```
C(4+3-1, 3) = C(6, 3) = 20
```

## 3. STARS AND BARS

Problem: Distribute n identical items into k distinct bins
Formula: C(n+k-1, k-1) or C(n+k-1, n)

Visual: Place n stars and k-1 bars
Example: Distribute 5 items into 3 bins
**|***|| represents {2, 3, 0}

Total arrangements: C(5+3-1, 3-1) = C(7, 2) = 21

Applications:
- Distribute items into groups
- Count solutions to x₁+x₂+...+xₖ = n (xᵢ > 0)
- Partition problems

Code:
```
long starsAndBars(int n, int k) {
  return combination(n + k - 1, k - 1);

}
```

Variation: Each bin must have at least 1 item
Formula: C(n-1, k-1)
(First give 1 to each, then distribute remaining n-k)

Problems:
- LC 39: Combination Sum
- Distribute coins
- Count ways to make change

## 4. INCLUSION-EXCLUSION PRINCIPLE

Principle: |A ∪ B| = |A| + |B| - |A ∩ B|

General Form:
|A₁ ∪ A₂ ∪ ... ∪ Aₙ| =
Σ|Aᵢ| - Σ|Aᵢ ∩ Aⱼ| + Σ|Aᵢ ∩ Aⱼ ∩ Aₖ| - ... + (-1)ⁿ⁺¹|A₁ ∩ ... ∩ Aₙ|

Visual Example: Count multiples of 2 or 3 in [1,100]
|A| = multiples of 2 = 50
|B| = multiples of 3 = 33
|A ∩ B| = multiples of 6 = 16
|A ∪ B| = 50 + 33 - 16 = 67

Code Pattern (3 sets):
```
int inclusionExclusion(int A, int B, int C, int AB, int AC, int BC, int ABC) {
  return A + B + C - AB - AC - BC + ABC;

}
```

Applications:
- Count elements with at least one property
- Subtract overcounting
- Derangements (special case)
- GCD/LCM problems

Problems:
- LC 878: Nth Magical Number
- Count numbers divisible by A or B
- Trapezoids problem (count all - parallelograms)

## 5. PIGEONHOLE PRINCIPLE

Principle: If n items are placed into m containers and n > m,
then at least one container has more than one item.

Extended: If n items in m containers, at least one has ⌈n/m⌉ items.

Example: In any group of 13 people, at least 2 share birth month
13 people > 12 months > pigeonhole!

Applications:
- Prove existence (not construct)
- Find duplicates
- Guarantee collisions

Problems:
- Birthday paradox
- Find duplicate in array
- Substring patterns

## 6. BINOMIAL COEFFICIENTS & PASCAL'S TRIANGLE

PASCAL'S TRIANGLE:
------------------
1
1 1
1 2 1
1 3 3 1

1 4 6 4 1

Property: C(n,r) = C(n-1,r-1) + C(n-1,r)

Code (DP):
```cpp
vector<vector<long>> pascalTriangle(int n) {
  vector<vector<long>> dp(n + 1, vector<long>(n + 1));
  for (int i = 0; i <= n; i++) {                      
      dp[i][0] = dp[i][i] = 1;                        
      for (int j = 1; j < i; j++) {                   
          dp[i][j] = dp[i-1][j-1] + dp[i-1][j];       
      }                                               
  }                                                   
  return dp;                                          

}
```

**BINOMIAL THEOREM:**
-----------------
(a + b)ⁿ = Σ C(n,k) x aⁿ⁻ᵏ x bᵏ

Example: (x + 1)3 = 1x3 + 3x2 + 3x + 1
Coefficients: 1, 3, 3, 1 (from Pascal's triangle)

Properties:
```
C(n,0) + C(n,1) + ... + C(n,n) = 2ⁿ
C(n,0) - C(n,1) + C(n,2) - ... = 0
```

Problems:
- Subset counting
- Path counting in grid
- Probability calculations

## 7. CATALAN NUMBERS

Sequence: 1, 1, 2, 5, 14, 42, 132, 429, ...

Formula: C(n) = C(2n,n)/(n+1) = (2n)!/(n!(n+1)!)

Recursive: C(n) = Σ C(i)xC(n-1-i) for i=0 to n-1

Code:
```cpp
long catalan(int n) {
  if (n <= 1) return 1;              
  vector<long> dp(n + 1);            
  dp[0] = dp[1] = 1;                 
  for (int i = 2; i <= n; i++) {     
      for (int j = 0; j < i; j++) {  
          dp[i] += dp[j] * dp[i-1-j];
      }                              
  }                                  
  return dp[n];                      

}
```

Applications:
- Valid parentheses sequences
- Binary search trees with n nodes
- Ways to triangulate polygon
- Paths in grid (not crossing diagonal)
- Ways to multiply n matrices

Problems:
- LC 22: Generate Parentheses
- LC 96: Unique Binary Search Trees
- LC 95: Unique Binary Search Trees II (generate all trees)
- LC 894: All Possible Full Binary Trees

**Unique Binary Search Trees II (LC 95)** 
SERIES: I (count trees) > II (generate all trees)

**KEY INSIGHT:**
- For each root value i, left subtrees use [1..i-1], right use [i+1..n]
- Recursively generate all left and right subtrees
- Combine: every left x every right pairing

```cpp
vector<TreeNode*> generateTrees(int n) {
if (n == 0) return {};
return build(1, n);   

}

vector<TreeNode*> build(int lo, int hi) {
if (lo > hi) return {nullptr};               

vector<TreeNode*> result;                    
for (int i = lo; i <= hi; i++) {             
    auto lefts = build(lo, i - 1);           
    auto rights = build(i + 1, hi);          

    for (auto l : lefts) {                   
        for (auto r : rights) {              
            TreeNode* root = new TreeNode(i);
            root->left = l;                  
            root->right = r;                 
            result.push_back(root);          
        }                                    
    }                                        
}                                            
return result;                               

}
// Time: O(4^n / n^(3/2)) Catalan number, Space: O(4^n / n^(3/2))
```

## 8. DERANGEMENTS

Derangement: Permutation where no element appears in original position
Example: [2, 3, 1] is derangement of [1, 2, 3]

Formula: D(n) = n! x (1 - 1/1! + 1/2! - 1/3! + ... + (-1)ⁿ/n!)

Recursive: D(n) = (n-1) x [D(n-1) + D(n-2)]

Values: D(0)=1, D(1)=0, D(2)=1, D(3)=2, D(4)=9, D(5)=44

Code:
```cpp
long derangement(int n) {
  if (n == 0) return 1;                     
  if (n == 1) return 0;                     
  vector<long> dp(n + 1);                   
  dp[0] = 1;                                
  dp[1] = 0;                                
  for (int i = 2; i <= n; i++) {            
      dp[i] = (i - 1) * (dp[i-1] + dp[i-2]);
  }                                         
  return dp[n];                             

}
```

Uses Inclusion-Exclusion:
```
D(n) = n! - (ways with at least 1 fixed point)
```

Applications:
- Secret Santa (no one gets own name)
- Hat check problem
- Permutations with restrictions

Problems:
- Find permutations with constraints
- Count arrangements avoiding patterns

## 9. PARTITIONS

**INTEGER PARTITION:**
------------------
Ways to write n as sum of positive integers (order doesn't matter)
Example: 4 = 4 = 3+1 = 2+2 = 2+1+1 = 1+1+1+1 > 5 partitions

Code (DP):
```cpp
int partition(int n) {
  vector<int> dp(n + 1);            
  dp[0] = 1;                        
  for (int i = 1; i <= n; i++) {    
      for (int j = i; j <= n; j++) {
          dp[j] += dp[j - i];       
      }                             
  }                                 
  return dp[n];                     

}
```

SET PARTITION (Bell Numbers):
------------------------------
```
B(n) = ways to partition set of n elements
```

Example: {1,2,3} > {{1,2,3}}, {{1,2},{3}}, {{1,3},{2}}, {{2,3},{1}}, {{1},{2},{3}}
```
B(3) = 5
```

Stirling Numbers of Second Kind:
```
S(n,k) = ways to partition n elements into exactly k non-empty subsets
```

## 10. GENERATING FUNCTIONS

Technique: Encode sequence as coefficients of polynomial/series

Example: Count ways to make change with coins {1,2,5}
```
G(x) = (1 + x + x2 + ...) x (1 + x2 + x⁴ + ...) x (1 + x⁵ + x¹⁰ + ...)
```

Coefficient of xⁿ = ways to make n cents

Applications:
- Partition problems
- Recurrence relations
- Counting with restrictions

Advanced: Uses power series, Fibonacci with generating functions

Problems:
- Coin change variations
- Sequence counting
- Combinatorial identities

## 11. PATTERN RECOGNITION: WHICH TECHNIQUE TO USE?

KEYWORD/PATTERN                 TECHNIQUE
-------------------            --------------------------
"arrange/order matters"     >  Permutations
"choose/select"             >  Combinations
"at least one"              >  Inclusion-Exclusion
"distribute identical"      >  Stars and Bars
"must exist"                >  Pigeonhole Principle
"valid parentheses"         >  Catalan Numbers
"no element in position"    >  Derangements
"ways to partition"         >  Partition/Bell Numbers
"sum of products of pairs"  >  Running Sum Pattern
"count paths in grid"       >  Combinations/DP
"subset sum"                >  DP/Generating Functions

## 12. COMMON PROBLEM TYPES

### TYPE 1: SUBSET/SUBSEQUENCE COUNTING

Q: How many subsets of size k from n elements?
A: C(n, k)

Q: How many non-empty subsets?
A: 2ⁿ - 1

Q: How many ways to choose with/without replacement?
A: With replacement: C(n+r-1, r), Without: C(n, r)

### TYPE 2: ARRANGEMENT PROBLEMS

Q: Arrange n distinct items
A: n!

Q: Arrange n items with repetitions (n₁ of type 1, n₂ of type 2, ...)
A: n! / (n₁! x n₂! x ... x nₖ!)

Q: Circular arrangements
A: (n-1)!

### TYPE 3: DISTRIBUTION PROBLEMS

Q: Distribute n identical balls into k distinct boxes
A: Stars and Bars: C(n+k-1, k-1)

Q: Each box must have at least 1
A: C(n-1, k-1)

Q: Distribute distinct items
A: kⁿ ways

### TYPE 4: PATH COUNTING

Q: Paths in mxn grid (only right/down)
A: C(m+n, m)

Q: Paths not crossing diagonal
A: Catalan numbers

Q: Paths with obstacles
A: DP or inclusion-exclusion

### TYPE 5: STRING/SEQUENCE PROBLEMS

Q: Valid parentheses with n pairs
A: Catalan number C(n)

Q: Binary strings with constraints
A: DP or recurrence

Q: Palindromic arrangements
A: Count letter frequencies, use formula

## 13. ADVANCED TECHNIQUES

BURNSIDE'S LEMMA:
-----------------
Count distinct objects under symmetry/rotation
Used in: counting necklaces, patterns with rotation

MÖBIUS INVERSION:
-----------------
Number theory technique
Used in: GCD/LCM problems, coprime counting

LUCAS' THEOREM:
---------------
Compute C(n,r) mod p efficiently
Used in: modular combinatorics

**HOCKEY STICK IDENTITY:**
----------------------
```
C(r,r) + C(r+1,r) + ... + C(n,r) = C(n+1,r+1)
```

Used in: sum of binomial coefficients

## 14. IMPLEMENTATION TIPS

**AVOIDING OVERFLOW:**
------------------
1. Use modular arithmetic: (a*b) % MOD
2. Compute C(n,r) incrementally
3. Use logarithms for large factorials

**PRECOMPUTATION:**
---------------
For multiple queries:
- Precompute factorials up to n
- Precompute inverse factorials (modular)
- Use Pascal's triangle

Code:
```cpp
const int MOD = 1e9 + 7;
vector<long> fact, inv_fact;

void precompute(int n) {
  fact.resize(n + 1);                             
  inv_fact.resize(n + 1);                         
  fact[0] = 1;                                    
  for (int i = 1; i <= n; i++) {                  
      fact[i] = (fact[i-1] * i) % MOD;            
  }                                               
  // Compute inverse using Fermat's little theorem
  inv_fact[n] = modPow(fact[n], MOD - 2, MOD);    
  for (int i = n - 1; i >= 0; i--) {              
      inv_fact[i] = (inv_fact[i+1] * (i+1)) % MOD;
  }                                               

}

long nCr(int n, int r) {
  if (r > n) return 0;                                       
  return (fact[n] * inv_fact[r] % MOD) * inv_fact[n-r] % MOD;

}
```

## 15. PRACTICE PROBLEMS BY TECHNIQUE

**COMBINATIONS:**
- LC 77: Combinations
- LC 39: Combination Sum
- LC 1863: Sum of All Subset XOR Totals

**PERMUTATIONS:**
- LC 46: Permutations
- LC 47: Permutations II
- LC 60: Permutation Sequence

**CATALAN:**
- LC 22: Generate Parentheses
- LC 95: Unique Binary Search Trees II
- LC 96: Unique Binary Search Trees
- LC 894: All Possible Full Binary Trees

**STARS AND BARS:**
- LC 377: Combination Sum IV
- Distribute items problems

**INCLUSION-EXCLUSION:**
- LC 878: Nth Magical Number
- LC 1201: Ugly Number III

**RUNNING SUM:**
- LC 3623: Count Horizontal Trapezoids
- Sum of pairwise products

## KEY TAKEAWAYS

1.  Combinatorics = Math of counting/selecting/arranging
2.  Multiple techniques for different problem types
3.  Pattern recognition is KEY
4.  Often combined with DP for efficiency
5.  Understanding formulas saves time
6.  Modular arithmetic crucial for large numbers
7.  Precomputation helps with multiple queries

Most Common in Interviews:
1. Combinations C(n,r)
2. Permutations P(n,r)
3. Stars and Bars
4. Running Sum Pattern
5. Catalan Numbers

Master these 5 and you'll handle 90% of combinatorics problems!
