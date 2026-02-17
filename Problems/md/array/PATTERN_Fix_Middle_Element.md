# PATTERN: FIX MIDDLE ELEMENT (Triplet Counting)

Problem 3583 "Count Special Triplets" belongs to this fundamental pattern!

Primary Topics:
- Hash Table / HashMap
- Combinatorics (Multiplication Principle)
- Array Processing

Related Patterns:
- Two Pointer (variant)
- Frequency Counting
- Range Query

## MAIN TOPIC: HASH TABLE + COMBINATORICS

Category: Counting Problems with Constraints

The pattern:
Fix middle element > Count left x Count right

This combines:
1. Hash Table: O(1) frequency lookups
2. Combinatorics: Multiplication principle for independent choices

## THE "FIX MIDDLE ELEMENT" PATTERN

When to Use:
------------
Y Problem asks to count triplets/tuples
Y Indices have order: i < j < k
Y Constraints involve relationships between elements
Y Need O(n) or O(n2) solution (not O(n3))

Recognition Keywords:
---------------------
- "Count triplets where..."
- "Find all (i, j, k) such that..."
- "0 <= i < j < k < n"
- "Specific relationship between elements"

Core Idea:
----------
Instead of trying all O(n3) combinations:
1. Fix the middle element (j)
2. Count valid left elements (i < j)
3. Count valid right elements (k > j)
4. Multiply: leftCount x rightCount

This reduces complexity from O(n3) to O(n2) or O(n)!

## RELATIONSHIP TO OTHER PATTERNS

1. RUNNING SUM PATTERN
----------------------
Running Sum: For pairs, accumulate as you go
result += element x sum
sum += element

Fix Middle: For triplets, multiply left x right
result += leftCount x rightCount

Similar Idea: Use prefix information to avoid nested loops

2. TWO POINTER (VARIANT)
----------------------
Traditional Two Pointer: Process from both ends

Fix Middle: Process from left, maintain left and right state
- leftFreq grows as we move right
- rightFreq shrinks as we move right

Both: Avoid redundant work by maintaining state

3. FREQUENCY COUNTING
-------------------
Core technique: Use HashMap to track element frequencies

Applications:
- Count valid left elements
- Count valid right elements
- O(1) lookup instead of O(n) scan

## COMPARISON WITH SIMILAR PROBLEMS

PROBLEM TYPE              APPROACH              COMPLEXITY
----------------          ------------          ----------
Two Sum                   HashMap               O(n)
Three Sum                 Two Pointer           O(n2)
Count Special Triplets    Fix Middle + HashMap  O(n)
Running Sum Pattern       Accumulate            O(n)

All use similar ideas: avoid brute force with smart state tracking!

## SPECIFIC TOPICS FOR THIS PROBLEM

1. HASH TABLE (Primary)
---------------------
Why: Need O(1) frequency lookups
What: Map value > count

Operations:
- leftFreq[value]++
- rightFreq[value]--
- Get count in O(1)

2. COMBINATORICS (Multiplication Principle)
-----------------------------------------
Principle: If task A has m ways and task B has n ways,
then doing both has m x n ways

Application:
- Pick from left: leftCount ways
- Pick from right: rightCount ways
- Total: leftCount x rightCount

3. ARRAY PROCESSING
-----------------
Technique: Single pass with state maintenance
- Process elements left to right
- Update left and right frequencies
- Compute contribution at each step

4. PREFIX/SUFFIX TECHNIQUE
------------------------
Similar to prefix sum idea:
- leftFreq = prefix state (elements seen so far)
- rightFreq = suffix state (elements yet to see)
- Combine both for each position

## WHERE TO CATEGORIZE THIS PROBLEM

In your notes folder structure:

Primary Category:
/Hash Table/
- Main technique used
- Core data structure

Secondary Categories:
/Combinatorics/
- Multiplication principle
- Counting techniques

/Array/
- Array processing
- Element relationships

Related Patterns:
/Two Pointers/ (variant)
/Frequency Counting/
/Prefix-Suffix/

## SIMILAR PROBLEMS (SAME PATTERN)

**EASY-MEDIUM:**
1. LC 1: Two Sum (fix element, find complement)
2. LC 560: Subarray Sum Equals K (prefix sum + hashmap)
3. LC 454: 4Sum II (fix middle, count left x right)

**MEDIUM:**
1. LC 3583: Count Special Triplets * (this problem)
2. LC 1426: Counting Elements (element and element+1)
3. LC 930: Binary Subarrays With Sum (prefix sum)

**HARD:**
1. LC 1074: Number of Submatrices That Sum to Target
2. LC 1542: Find Longest Awesome Substring

## THE PATTERN IN ACTION

Template for "Fix Middle" problems:

```cpp
int countTriplets(vector<int>& nums) {
```
// Step 1: Precompute right frequencies
map<int, int> rightFreq;
for (int val : nums) rightFreq[val]++;

int result = 0;
map<int, int> leftFreq;

// Step 2: Fix each element as middle
for (int j = 0; j < nums.size(); j++) {
    // Remove from right (it's now middle)
    rightFreq[nums[j]]--;

    // Calculate target/relationship
    int target = calculateTarget(nums[j]);

    // Count left and right
    int leftCount = leftFreq[target];
    int rightCount = rightFreq[target];

    // Multiply (multiplication principle)
    result += leftCount * rightCount;

    // Add to left (for future iterations)
    leftFreq[nums[j]]++;
}

return result;
```

}
```

Key Steps:
1. Precompute right frequencies
2. For each middle element:
- Remove from right
- Count valid left and right
- Multiply counts
- Add to left

## CONNECTION TO PREVIOUSLY LEARNED PATTERNS

RUNNING SUM PATTERN (from trapezoid problem):
---------------------------------------------
For pairs (i, j):
result += edge[j] x sum
sum += edge[j]

Accumulates as we go, O(n)

FIX MIDDLE PATTERN (this problem):
----------------------------------
For triplets (i, j, k):
result += leftCount[j] x rightCount[j]

Maintains left and right state, O(n)

Both:
- Avoid nested loops
- Use mathematical properties
- Smart state tracking
- Combinatorics principles

**DIFFERENCE:**
-----------
Running Sum: Pairs, accumulative (sum grows)
Fix Middle: Triplets, multiplicative (left x right)

But same philosophy: Count instead of enumerate!

## LEARNING PATH

Master these in order:

1. Hash Table Basics
- Insert, lookup, delete: O(1)
- Frequency counting
- Two Sum problem

2. Combinatorics Basics
- Multiplication principle
- Combinations C(n,k)
- Running sum pattern

3. Fix Middle Pattern
- Understand left/right split
- State maintenance
- Apply to triplet problems

4. Advanced Applications
- 4Sum, k-Sum variations
- Subarray problems
- Range queries with constraints

## SUMMARY

Problem 3583 "Count Special Triplets" belongs to:

**PRIMARY TOPIC:**
 Hash Table + Combinatorics

**PATTERN NAME:**
 Fix Middle Element Pattern

**KEY TECHNIQUES:**
 Frequency counting with HashMap
 Multiplication principle
 Left/Right state maintenance
 Single pass O(n) algorithm

**RELATED PATTERNS:**
 Running Sum (for pairs)
 Two Pointer (variant)
 Prefix-Suffix technique

**COMPLEXITY ACHIEVEMENT:**
 Reduced from O(n3) brute force to O(n) optimal

This is a HIGH-VALUE pattern that appears frequently in:
- Coding interviews
- Competitive programming
- LeetCode Medium/Hard problems

File Location Suggestion:
/Hash Table/ - Primary
/Combinatorics/ - Secondary
/Array/ - Tertiary

Or create:
/Counting Problems/ - collection of all counting patterns

