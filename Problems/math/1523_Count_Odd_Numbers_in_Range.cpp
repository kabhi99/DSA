#include <iostream>
using namespace std;

/*
Problem: 1523. Count Odd Numbers in an Interval Range
Difficulty: Easy
Category: Math

Problem Statement:
Given two non-negative integers low and high.
Return the count of odd numbers between low and high (inclusive).

Examples:
Input: low = 3, high = 7
Output: 3
Explanation: Odd numbers are [3,5,7]

Input: low = 8, high = 10
Output: 1
Explanation: Odd number is [9]

Key Insight:
Don't iterate! Use mathematical formula.

Formula: count = (high + 1) / 2 - low / 2

Why this works:
- (n + 1) / 2 gives count of odd numbers from 1 to n
- n / 2 gives count of even numbers from 1 to n
- Subtract to get count in range [low, high]

Time: O(1)
Space: O(1)
*/

class Solution {
public:
    int countOdds(int low, int high) {
        // Formula: (high + 1) / 2 - low / 2
        return (high + 1) / 2 - low / 2;
    }
};

/*
============================================================================
DETAILED EXPLANATION
============================================================================

Mathematical Derivation:
------------------------

Count of odd numbers from 1 to n:
  - If n is odd: (n + 1) / 2
  - If n is even: n / 2
  - General formula: (n + 1) / 2 (works for both due to integer division)

Count from 1 to high: (high + 1) / 2
Count from 1 to (low-1): low / 2

Count in [low, high] = count[1, high] - count[1, low-1]
                     = (high + 1) / 2 - low / 2


Examples:
---------

Example 1: low = 3, high = 7
  Odd numbers: 1, 3, 5, 7 (from 1 to 7) = 4 numbers
  Odd numbers: 1 (from 1 to 2) = 1 number
  In range [3,7]: 4 - 1 = 3 ✓
  
  Formula: (7 + 1) / 2 - 3 / 2 = 4 - 1 = 3 ✓

Example 2: low = 8, high = 10
  Odd numbers: 1,3,5,7,9 (from 1 to 10) = 5 numbers
  Odd numbers: 1,3,5,7 (from 1 to 7) = 4 numbers
  In range [8,10]: 5 - 4 = 1 ✓
  
  Formula: (10 + 1) / 2 - 8 / 2 = 5 - 4 = 1 ✓

Example 3: low = 1, high = 5
  Formula: (5 + 1) / 2 - 1 / 2 = 3 - 0 = 3 ✓
  Odd numbers: [1, 3, 5]

Example 4: low = 2, high = 6
  Formula: (6 + 1) / 2 - 2 / 2 = 3 - 1 = 2 ✓
  Odd numbers: [3, 5]


============================================================================
ALTERNATIVE APPROACHES (Less Efficient)
============================================================================

APPROACH 1: Brute Force - O(n)
-------------------------------
int count = 0;
for (int i = low; i <= high; i++) {
    if (i % 2 == 1) count++;
}
return count;

Problem: Slow for large ranges (e.g., [1, 10^9])


APPROACH 2: Case Analysis
--------------------------
int count;
if (low % 2 == 1 && high % 2 == 1) {
    count = (high - low) / 2 + 1;
} else if (low % 2 == 0 && high % 2 == 0) {
    count = (high - low) / 2;
} else {
    count = (high - low + 1) / 2;
}
return count;

Problem: Too many cases, error-prone


APPROACH 3: Mathematical Formula (Best)
----------------------------------------
return (high + 1) / 2 - low / 2;

Clean, simple, O(1)! ✓


============================================================================
PATTERN: MATHEMATICAL COUNTING
============================================================================

Category: Math, Number Theory

When to use:
- Count elements with specific property in range
- Property has pattern (odd/even, divisible by k, etc.)
- Range can be very large
- O(n) iteration too slow

Common patterns:
- Odd numbers in [L, R]: (R+1)/2 - L/2
- Even numbers in [L, R]: R/2 - (L-1)/2 = R/2 - L/2 + (L%2)
- Multiples of k in [L, R]: R/k - (L-1)/k

Key: Use prefix count - subtract ranges


============================================================================
RELATED PROBLEMS
============================================================================

1. Count multiples of k in range
   Formula: high/k - (low-1)/k

2. Count numbers divisible by a or b (Inclusion-Exclusion)
   count(a) + count(b) - count(lcm(a,b))

3. Count primes in range (Sieve of Eratosthenes)
   More complex, but still avoid checking each

4. Count digits in range
   Use digit DP or mathematical formula


============================================================================
*/

// Test cases
int main() {
    Solution sol;
    
    cout << "Test 1 (3, 7): " << sol.countOdds(3, 7) << endl;
    // Expected: 3 (odd: 3, 5, 7)
    
    cout << "Test 2 (8, 10): " << sol.countOdds(8, 10) << endl;
    // Expected: 1 (odd: 9)
    
    cout << "Test 3 (1, 5): " << sol.countOdds(1, 5) << endl;
    // Expected: 3 (odd: 1, 3, 5)
    
    cout << "Test 4 (2, 6): " << sol.countOdds(2, 6) << endl;
    // Expected: 2 (odd: 3, 5)
    
    cout << "Test 5 (1, 1): " << sol.countOdds(1, 1) << endl;
    // Expected: 1 (odd: 1)
    
    cout << "Test 6 (2, 2): " << sol.countOdds(2, 2) << endl;
    // Expected: 0 (no odd)
    
    cout << "Test 7 (1, 1000000): " << sol.countOdds(1, 1000000) << endl;
    // Expected: 500000 (half are odd)
    
    return 0;
}

/*
============================================================================
KEY TAKEAWAYS
============================================================================

1. ✅ Don't iterate when you can calculate
2. ✅ Use prefix count technique: count[1,R] - count[1,L-1]
3. ✅ (n+1)/2 gives odd count from 1 to n
4. ✅ n/2 gives even count from 1 to n
5. ✅ O(1) solution always better than O(n) for large ranges

Formula to remember:
  Odd count in [L, R] = (R + 1) / 2 - L / 2

This pattern applies to many counting problems!

============================================================================
*/



