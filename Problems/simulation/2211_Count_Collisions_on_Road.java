/**
 * Problem: 2211. Count Collisions on a Road
 * Difficulty: Medium
 * Category: Simulation, String, Greedy
 * 
 * Problem Statement:
 * - Cars on road: 'L' (left), 'R' (right), 'S' (stationary)
 * - Collisions:
 *   - R meets L (opposite directions): +2 collisions
 *   - Moving car hits stationary: +1 collision
 * - Find total collisions
 * 
 * Key Insight:
 * - Leading L's escape to the left (no collision)
 * - Trailing R's escape to the right (no collision)
 * - Everything else WILL collide
 * - Each non-escaping moving car (L or R) contributes 1 collision
 * 
 * Solution:
 * 1. Remove leading L's
 * 2. Remove trailing R's
 * 3. Count remaining L's and R's
 * 
 * Time: O(n)
 * Space: O(1)
 */

class Solution {
    public int countCollisions(String directions) {
        int n = directions.length();
        if (n <= 1) return 0;
        
        // Find first non-L from left (cars before this escape)
        int left = 0;
        while (left < n && directions.charAt(left) == 'L') {
            left++;
        }
        
        // Find first non-R from right (cars after this escape)
        int right = n - 1;
        while (right >= 0 && directions.charAt(right) == 'R') {
            right--;
        }
        
        // If all escape
        if (left > right) return 0;
        
        // Count moving cars (L and R) in the middle section
        int collisions = 0;
        for (int i = left; i <= right; i++) {
            if (directions.charAt(i) != 'S') {
                collisions++;
            }
        }
        
        return collisions;
    }
}

/**
 * Test Cases
 */
class TestCollisions {
    public static void main(String[] args) {
        Solution sol = new Solution();
        
        System.out.println("Test 1: " + sol.countCollisions("RLRSLL"));
        // Expected: 5
        
        System.out.println("Test 2: " + sol.countCollisions("LLRR"));
        // Expected: 0
        
        System.out.println("Test 3: " + sol.countCollisions("SSRSSRLLRLSSLR"));
        // Expected: 7
        
        System.out.println("Test 4: " + sol.countCollisions("RLLR"));
        // Expected: 3
    }
}

/*
============================================================================
VISUAL EXPLANATION
============================================================================

Example: "RLRSLL"

Initial state:
  R → L ← R → S   L ← L ←
  0   1   2   3   4   5

Step-by-step simulation:
  1. R(0) meets L(1) → both stop (opposite directions)
     Collisions: +2
     State: S   S   R → S   L ← L ←
  
  2. R(2) hits S(3) → R stops
     Collisions: +1
     State: S   S   S   S   L ← L ←
  
  3. L(4) hits S(3) → L stops
     Collisions: +1
     State: S   S   S   S   S   L ←
  
  4. L(5) hits S(4) → L stops
     Collisions: +1
     State: S   S   S   S   S   S
  
  Total: 2+1+1+1 = 5 ✓


Our Algorithm Approach:
-----------------------
  "RLRSLL"
   ^^^^^^  (no leading L's)
   ^^^^^^  (no trailing R's)
  
  Middle section: "RLRSLL" (entire string)
  Count L and R: R, L, R, L, L = 5 ✓


Example 2: "LLRR"
-----------------
  L ← L ← R → R →
  
  Leading L's: LL (escape left) ←←
  Trailing R's: RR (escape right) →→
  Middle: empty
  Collisions: 0 ✓


Example 3: "RLLR"
-----------------
  R → L ← L ← R →
  
  left = 0 (R is first non-L)
  right = 2 (L is last non-R, since R at index 3 escapes)
  
  Middle: "RLL" (indices 0-2)
  Count L and R: R, L, L = 3 ✓
  
  Simulation:
    R(0) and L(1) collide → SS
    L(2) hits S(1)
    R(3) escapes right →
  Total: 3 collisions


============================================================================
WHY COUNT ONLY L's AND R's?
============================================================================

Key Insight: Each moving car that doesn't escape will have exactly 
ONE collision event that stops it.

- When R hits L (opposite): counts as 2 (one for each car)
- When R hits S: counts as 1 (only R stops)
- When L hits S: counts as 1 (only L stops)
- S doesn't add to count (already stopped)

By counting all non-escaping L's and R's, we get the exact collision count!


============================================================================
COMPLEXITY ANALYSIS
============================================================================

Time Complexity: O(n)
  - Finding left boundary: O(n) worst case
  - Finding right boundary: O(n) worst case
  - Counting middle: O(n) worst case
  - Total: O(n)

Space Complexity: O(1)
  - Only using a few integer variables
  - No extra data structures

Optimal solution! ✅


============================================================================
COMMON MISTAKES
============================================================================

❌ Mistake 1: Try to simulate step by step
   - Too complex, easy to get wrong
   - O(n²) or worse time complexity

❌ Mistake 2: Count all non-S characters
   - Forgets that leading L's and trailing R's escape
   - Wrong answer

❌ Mistake 3: Try to track each collision type
   - Unnecessary complexity
   - The simple count works!

✅ Correct: Count non-escaping moving cars
   - Clean, simple, O(n)
   - Correct logic


============================================================================
PATTERN RECOGNITION
============================================================================

This problem uses the "Escape Analysis" pattern:
  1. Identify elements that escape/don't participate
  2. Focus only on elements in the "active zone"
  3. Count based on simple rules

Similar problems:
  - Remove Outermost Parentheses
  - Valid Parenthesis String
  - Candy Crush variants

============================================================================
*/




