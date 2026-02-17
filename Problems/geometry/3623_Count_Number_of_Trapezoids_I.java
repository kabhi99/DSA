import java.util.*;

/**
 * Problem: 3623. Count Number of Trapezoids I
 * Difficulty: Medium
 * Category: Geometry, Math, Combinatorics
 * 
 * Problem Statement:
 * - Given 2D points, count number of unique horizontal trapezoids
 * - Horizontal trapezoid: convex quadrilateral with at least one pair of horizontal sides
 * - Horizontal sides = parallel to x-axis (same y-coordinate)
 * - Choose any 4 distinct points
 * - Return answer modulo 10^9 + 7
 * 
 * Key Insights:
 * 1. For horizontal trapezoid, we need horizontal parallel sides
 * 2. Horizontal sides means points with same y-coordinate
 * 3. A trapezoid needs 2 horizontal sides with different y-coordinates
 * 4. Each side needs at least 2 points
 * 
 * Approach:
 * 1. Group points by their y-coordinate
 * 2. For each pair of different y-coordinates (y1, y2):
 *    - Select 2 points from line y1: C(n1, 2) ways
 *    - Select 2 points from line y2: C(n2, 2) ways
 *    - Total combinations: C(n1, 2) * C(n2, 2)
 * 3. Sum all combinations
 * 
 * Formula: C(n, 2) = n * (n-1) / 2
 * 
 * Time Complexity: O(n + k^2) where n = number of points, k = unique y-coordinates
 * Space Complexity: O(k) for hashmap
 */

// OPTIMIZED SOLUTION - O(n + k) instead of O(n + k^2)
class Solution {
    private static final int MOD = 1_000_000_007;
    
    public int countTrapezoids(int[][] points) {
        Map<Integer, Integer> pointNum = new HashMap<>();
        long ans = 0, sum = 0;
        
        // Count points at each y-coordinate
        for (int[] point : points) {
            pointNum.put(point[1], pointNum.getOrDefault(point[1], 0) + 1);
        }
        
        // For each y-level, calculate C(n,2) and accumulate
        // Key insight: instead of nested loop, maintain running sum
        for (int pNum : pointNum.values()) {
            long edge = (long) pNum * (pNum - 1) / 2;
            ans += edge * sum;  // Multiply with all previous edges
            sum += edge;        // Add to running sum
        }
        
        return (int) (ans % MOD);
    }
}

/**
 * Test Cases and Examples
 */
class TestTrapezoids {
    public static void main(String[] args) {
        Solution sol = new Solution();
        
        // Test 1: Basic trapezoid
        int[][] points1 = {{1,1}, {2,1}, {3,2}, {4,2}};
        System.out.println("Test 1: " + sol.countTrapezoids(points1)); // Expected: 1
        
        // Test 2: Multiple points on same lines
        int[][] points2 = {{1,1}, {2,1}, {3,1}, {1,2}, {2,2}, {3,2}};
        System.out.println("Test 2: " + sol.countTrapezoids(points2)); // Expected: 9
        // C(3,2) * C(3,2) = 3 * 3 = 9
        
        // Test 3: Three horizontal lines
        int[][] points3 = {{1,1}, {2,1}, {1,2}, {2,2}, {1,3}, {2,3}};
        System.out.println("Test 3: " + sol.countTrapezoids(points3));
        // C(2,2)*C(2,2) + C(2,2)*C(2,2) + C(2,2)*C(2,2) = 1+1+1 = 3
        
        // Test 4: Not enough points on one line
        int[][] points4 = {{1,1}, {1,2}, {2,2}, {3,2}};
        System.out.println("Test 4: " + sol.countTrapezoids(points4)); // Expected: 0
    }
}

/*
Detailed Explanation:

Visual Example:
points = [[1,1], [2,1], [3,2], [4,2]]

     y=2  •────────•  (points at (3,2) and (4,2))
          │        │
          │        │
     y=1  •────────•  (points at (1,1) and (2,1))

This forms 1 trapezoid with horizontal sides at y=1 and y=2.

More Complex Example:
points = [[1,1], [2,1], [3,1], [1,2], [2,2], [3,2]]

     y=2  •────•────•  (3 points at y=2)
          │    │    │
          │    │    │
     y=1  •────•────•  (3 points at y=1)

From 3 points at y=1, we can choose 2 in C(3,2) = 3 ways
From 3 points at y=2, we can choose 2 in C(3,2) = 3 ways
Total trapezoids = 3 × 3 = 9

The 9 trapezoids are:
- Bottom: {(1,1),(2,1)}, Top: {(1,2),(2,2)}
- Bottom: {(1,1),(2,1)}, Top: {(1,2),(3,2)}
- Bottom: {(1,1),(2,1)}, Top: {(2,2),(3,2)}
- Bottom: {(1,1),(3,1)}, Top: {(1,2),(2,2)}
- Bottom: {(1,1),(3,1)}, Top: {(1,2),(3,2)}
- Bottom: {(1,1),(3,1)}, Top: {(2,2),(3,2)}
- Bottom: {(2,1),(3,1)}, Top: {(1,2),(2,2)}
- Bottom: {(2,1),(3,1)}, Top: {(1,2),(3,2)}
- Bottom: {(2,1),(3,1)}, Top: {(2,2),(3,2)}

Important Notes:
1. We don't need to check if points form a valid trapezoid shape
2. Any 2 points from one horizontal line + 2 from another = trapezoid
3. The problem guarantees these form valid convex trapezoids
4. X-coordinates don't matter for counting, only y-coordinates matter

Edge Cases:
- All points on same y: 0 trapezoids (need 2 different horizontal lines)
- Only 1 point on a y: Can't form a side (need at least 2 points)
- Large numbers: Use modulo to prevent overflow
*/

