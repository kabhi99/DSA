/**
 * Problem: 1523. Count Odd Numbers in an Interval Range
 * Difficulty: Easy
 * Category: Math
 * 
 * Given two non-negative integers low and high.
 * Return the count of odd numbers between low and high (inclusive).
 * 
 * Key Insight: Use mathematical formula instead of iteration
 * 
 * Formula: count = (high + 1) / 2 - low / 2
 * 
 * Time: O(1)
 * Space: O(1)
 */

class Solution {
    public int countOdds(int low, int high) {
        return (high + 1) / 2 - low / 2;
    }
}

class TestOddCount {
    public static void main(String[] args) {
        Solution sol = new Solution();
        
        System.out.println("Test 1 (3, 7): " + sol.countOdds(3, 7));
        // Expected: 3
        
        System.out.println("Test 2 (8, 10): " + sol.countOdds(8, 10));
        // Expected: 1
        
        System.out.println("Test 3 (1, 5): " + sol.countOdds(1, 5));
        // Expected: 3
        
        System.out.println("Test 4 (2, 6): " + sol.countOdds(2, 6));
        // Expected: 2
        
        System.out.println("Test 5 (1, 1000000): " + sol.countOdds(1, 1000000));
        // Expected: 500000
    }
}

/*
============================================================================
WHY THIS FORMULA WORKS
============================================================================

Visualization:
--------------
Numbers 1 to 10:
  Odd:  1  3  5  7  9     → 5 numbers = (10 + 1) / 2
  Even: 2  4  6  8  10    → 5 numbers = 10 / 2

Numbers 1 to 11:
  Odd:  1  3  5  7  9  11 → 6 numbers = (11 + 1) / 2
  Even: 2  4  6  8  10    → 5 numbers = 11 / 2


Range [3, 7]:
-------------
  Count from 1 to 7:  (7 + 1) / 2 = 4  (odd: 1,3,5,7)
  Count from 1 to 2:  3 / 2 = 1        (odd: 1)
  In range [3, 7]:    4 - 1 = 3        (odd: 3,5,7) ✓


Intuition:
----------
Every pair of consecutive numbers has exactly 1 odd number.
[1,2] → 1 odd, [3,4] → 1 odd, [5,6] → 1 odd, etc.

In range [L, R]:
  Total numbers = R - L + 1
  Approximately half are odd
  Exact count using prefix technique


============================================================================
SIMILAR PROBLEMS - MATHEMATICAL COUNTING
============================================================================

1. Count even numbers in range:
   evenCount = high/2 - (low-1)/2

2. Count multiples of k in range:
   multipleCount = high/k - (low-1)/k

3. Count numbers divisible by a OR b (Inclusion-Exclusion):
   count(a) + count(b) - count(lcm(a,b))

4. Count numbers with digit sum = k:
   Use digit DP (more complex)


Pattern: Prefix Count Technique
--------------------------------
answer = prefixCount(high) - prefixCount(low - 1)

Works for many counting problems!

============================================================================
*/



