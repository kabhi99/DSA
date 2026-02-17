#include <iostream>
#include <string>
using namespace std;

/*
Problem: 2211. Count Collisions on a Road
Difficulty: Medium
Category: Simulation, String, Greedy

Problem Statement:
- Cars on road: 'L' (left), 'R' (right), 'S' (stationary)
- Collisions:
  - R meets L (opposite directions): +2 collisions, both stop
  - Moving car hits stationary: +1 collision, moving car stops
- Find total collisions

Key Insights:
1. Leading 'L's escape to the left (no collision)
2. Trailing 'R's escape to the right (no collision)
3. Everything else WILL collide and become stationary
4. Each moving car (L or R) that doesn't escape contributes 1 collision

Solution:
- Remove leading L's
- Remove trailing R's
- Count remaining L's and R's

Why this works:
- Any L that has no barrier to its left escapes
- Any R that has no barrier to its right escapes
- Once there's a barrier (S, or collision), everything piles up
- Each non-escaping moving car contributes exactly 1 collision

Time: O(n)
Space: O(1)
*/

class Solution {
public:
    int countCollisions(string directions) {
        int n = directions.length();
        if (n <= 1) return 0;
        
        // Find first non-L from left (cars before this escape)
        int left = 0;
        while (left < n && directions[left] == 'L') {
            left++;
        }
        
        // Find first non-R from right (cars after this escape)
        int right = n - 1;
        while (right >= 0 && directions[right] == 'R') {
            right--;
        }
        
        // If all escape (all L's or all R's or no overlap)
        if (left > right) return 0;
        
        // Count moving cars (L and R) in the middle section
        // These will all collide and contribute 1 collision each
        int collisions = 0;
        for (int i = left; i <= right; i++) {
            if (directions[i] != 'S') {
                collisions++;
            }
        }
        
        return collisions;
    }
};

/*
============================================================================
DETAILED EXPLANATION
============================================================================

Example 1: "RLRSLL"
-------------------
Step-by-step simulation:
  Initial: R L R S L L
           0 1 2 3 4 5

  1. R(0) and L(1) collide: +2 collisions
     Result: S S R S L L
  
  2. R(2) hits S(3): +1 collision
     Result: S S S S L L
  
  3. L(4) hits S(3): +1 collision
     Result: S S S S S L
  
  4. L(5) hits S(4): +1 collision
     Result: S S S S S S
  
  Total: 2+1+1+1 = 5 ✓

Our algorithm:
  - left = 0 (first non-L)
  - right = 5 (first non-R from right)
  - Middle section: "RLRSLL" (indices 0 to 5)
  - Count L and R: R, L, R, L, L = 5 ✓


Example 2: "LLRR"
-----------------
  L L R R
  0 1 2 3

  - LL escape to left
  - RR escape to right
  - No collisions: 0 ✓

Our algorithm:
  - left = 2 (first non-L)
  - right = 1 (first non-R from right)
  - left > right → return 0 ✓


Example 3: "SSRSSRLLRLSSLR"
----------------------------
Visual analysis:
  S S R S S R L L R L S S L R
  0 1 2 3 4 5 6 7 8 9 ...

  - left = 0 (first non-L is at index 0)
  - right = 13 (R at end escapes, so right = 12)
  - Middle: indices 0 to 12
  - Count non-S: R, R, L, L, R, L, L = 7 collisions

Our algorithm correctly handles this!


============================================================================
WHY THIS WORKS - INTUITIVE EXPLANATION
============================================================================

Think of the road as having three sections:
  
  [Escape Left] [Collision Zone] [Escape Right]
       LLLL      RLRSRSLR...         RRRR
       ↓↓↓↓      ⚡⚡⚡⚡⚡⚡         ↑↑↑↑
    (no barrier) (barriers)     (no barrier)


Key Observations:
-----------------
1. Leading L's have nothing to stop them → escape
2. Trailing R's have nothing to stop them → escape
3. Middle section has "barriers" (opposite direction or S)

In the middle section:
- First non-L from left creates a barrier (it's R or S)
- First non-R from right creates a barrier (it's L or S)
- Everything between these barriers WILL collide

Each moving car (L or R) that gets trapped:
- Will eventually hit something (another car or stationary)
- Contributes exactly 1 collision

Even 'S' cars don't add to collision count because:
- They're already stationary
- When moving car hits S: the MOVING car contributes the +1


============================================================================
EDGE CASES
============================================================================

1. All L's: "LLLL"
   - All escape left
   - Collisions: 0

2. All R's: "RRRR"
   - All escape right
   - Collisions: 0

3. All S's: "SSSS"
   - No moving cars
   - Collisions: 0

4. Single barrier: "LLLS"
   - LL escape, L hits S
   - left=2, right=3
   - Count: 1 L → 1 collision

5. Complex: "RLLR"
   - R(0) and L(1) collide → SS
   - L(2) hits S(1)
   - R(3) hits S(2)
   - left=0, right=3
   - Count: R,L,L,R = 4 collisions


============================================================================
ALTERNATIVE APPROACHES
============================================================================

APPROACH 1: Simulation (Brute Force)
-------------------------------------
Simulate step by step until no more collisions.
Time: O(n²) or worse
Space: O(n)
Verdict: Too slow ❌


APPROACH 2: Stack-based
------------------------
Process cars left to right using stack.
Time: O(n)
Space: O(n)
Verdict: Works but uses extra space


APPROACH 3: Our Greedy Approach
--------------------------------
Count non-escaping moving cars directly.
Time: O(n)
Space: O(1)
Verdict: Optimal! ✅


============================================================================
*/

// Test cases
int main() {
    Solution sol;
    
    cout << "Test 1: " << sol.countCollisions("RLRSLL") << endl;
    // Expected: 5
    
    cout << "Test 2: " << sol.countCollisions("LLRR") << endl;
    // Expected: 0
    
    cout << "Test 3: " << sol.countCollisions("SSRSSRLLRLSSLR") << endl;
    // Expected: 7 (count L and R in middle)
    
    cout << "Test 4: " << sol.countCollisions("LLLL") << endl;
    // Expected: 0 (all escape)
    
    cout << "Test 5: " << sol.countCollisions("RRRR") << endl;
    // Expected: 0 (all escape)
    
    cout << "Test 6: " << sol.countCollisions("RLLR") << endl;
    // R collides with LL, last R escapes
    // Expected: 3
    
    cout << "Test 7: " << sol.countCollisions("LLRS") << endl;
    // LL escape, R hits S → 1 collision
    // Expected: 1
    
    return 0;
}

