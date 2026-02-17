#include <bits/stdc++.h>
using namespace std;

/*
Problem: 3623. Count Number of Trapezoids I
Difficulty: Medium
Category: Geometry, Math, Combinatorics

Problem Statement:
- Given 2D points, count number of unique horizontal trapezoids
- Horizontal trapezoid: convex quadrilateral with at least one pair of horizontal sides
- Horizontal sides = parallel to x-axis (same y-coordinate)
- Choose any 4 distinct points
- Return answer modulo 10^9 + 7

Key Insights:
1. For horizontal trapezoid, we need horizontal parallel sides
2. Horizontal sides means points with same y-coordinate
3. A trapezoid needs 2 horizontal sides with different y-coordinates
4. Each side needs at least 2 points

Approach:
1. Group points by their y-coordinate
2. For each pair of different y-coordinates (y1, y2):
   - Select 2 points from line y1: C(n1, 2) ways
   - Select 2 points from line y2: C(n2, 2) ways
   - Total combinations: C(n1, 2) * C(n2, 2)
3. Sum all combinations

Formula: C(n, 2) = n * (n-1) / 2

Time Complexity: O(n + k^2) where n = number of points, k = unique y-coordinates
Space Complexity: O(k) for hashmap

Example:
points = [[1,1], [2,1], [3,2], [4,2]]
y=1: points (1,1), (2,1) -> 2 points
y=2: points (3,2), (4,2) -> 2 points
Trapezoids: C(2,2) * C(2,2) = 1 * 1 = 1
Answer: 1 trapezoid
*/

// OPTIMIZED SOLUTION - O(n + k) instead of O(n + k^2)
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<int, int> pointNum;
        const int mod = 1e9 + 7;
        long long ans = 0, sum = 0;
        
        // Count points at each y-coordinate
        for (auto& point : points) {
            pointNum[point[1]]++;
        }
        
        // For each y-level, calculate C(n,2) and accumulate
        // Key insight: instead of nested loop, maintain running sum
        for (auto& [y, pNum] : pointNum) {
            long long edge = (long long)pNum * (pNum - 1) / 2;
            ans += edge * sum;  // Multiply with all previous edges
            sum += edge;        // Add to running sum
        }
        
        return ans % mod;
    }
};

/*
============================================================================
DETAILED EXPLANATION OF RUNNING SUM OPTIMIZATION
============================================================================

APPROACH 1 (Nested Loops) - O(k²):
------------------------------------
for i in 0..k:
    for j in i+1..k:
        ans += C(count[i],2) * C(count[j],2)

Example: Say we have 3 y-levels with edges [e1, e2, e3]
We need: e1*e2 + e1*e3 + e2*e3

Nested loop does:
  i=0, j=1: ans += e1*e2
  i=0, j=2: ans += e1*e3
  i=1, j=2: ans += e2*e3
Total: ans = e1*e2 + e1*e3 + e2*e3 ✓

Problem: O(k²) iterations!


APPROACH 2 (Running Sum) - O(k):
---------------------------------
sum = 0
for each edge:
    ans += edge * sum
    sum += edge

Let's trace through the SAME example [e1, e2, e3]:

Step 1: Process e1
  ans += e1 * sum = e1 * 0 = 0
  sum += e1 → sum = e1
  Current state: ans = 0, sum = e1

Step 2: Process e2
  ans += e2 * sum = e2 * e1
  sum += e2 → sum = e1 + e2
  Current state: ans = e1*e2, sum = e1+e2

Step 3: Process e3
  ans += e3 * sum = e3 * (e1+e2) = e3*e1 + e3*e2
  sum += e3 → sum = e1 + e2 + e3
  Current state: ans = e1*e2 + e1*e3 + e2*e3 ✓

SAME RESULT! But only 3 iterations instead of 6!


WHY IT WORKS:
-------------
When we process edge 'i', sum contains (e1 + e2 + ... + e(i-1))
So: edge_i * sum = edge_i * (e1 + e2 + ... + e(i-1))
                 = edge_i*e1 + edge_i*e2 + ... + edge_i*e(i-1)

This gives us ALL products of edge_i with previous edges!

By doing this for each edge, we get ALL pairwise products exactly once.


CONCRETE EXAMPLE:
-----------------
points = [[1,1], [2,1], [3,1], [1,2], [2,2], [1,3], [2,3]]

y=1: 3 points → e1 = C(3,2) = 3
y=2: 2 points → e2 = C(2,2) = 1  
y=3: 2 points → e3 = C(2,2) = 1

We need: 3*1 + 3*1 + 1*1 = 3 + 3 + 1 = 7

Approach 1 (nested):
  i=0,j=1: ans += 3*1 = 3
  i=0,j=2: ans += 3*1 = 3
  i=1,j=2: ans += 1*1 = 1
  Final: ans = 7 ✓

Approach 2 (running sum):
  Process e1=3: ans += 3*0=0, sum=3  → ans=0
  Process e2=1: ans += 1*3=3, sum=4  → ans=3
  Process e3=1: ans += 1*4=4, sum=5  → ans=7 ✓

SAME ANSWER, but linear time!

Time: O(n + k) where k = unique y-coordinates
Space: O(k)
============================================================================
*/

// Test cases
int main() {
    Solution sol;
    
    // Test 1: Basic trapezoid
    vector<vector<int>> points1 = {{1,1}, {2,1}, {3,2}, {4,2}};
    cout << "Test 1: " << sol.countTrapezoids(points1) << endl; // Expected: 1
    
    // Test 2: Multiple points on same lines
    vector<vector<int>> points2 = {{1,1}, {2,1}, {3,1}, {1,2}, {2,2}, {3,2}};
    cout << "Test 2: " << sol.countTrapezoids(points2) << endl; // Expected: 9
    // C(3,2) * C(3,2) = 3 * 3 = 9
    
    // Test 3: Three horizontal lines
    vector<vector<int>> points3 = {{1,1}, {2,1}, {1,2}, {2,2}, {1,3}, {2,3}};
    cout << "Test 3: " << sol.countTrapezoids(points3) << endl;
    // C(2,2)*C(2,2) + C(2,2)*C(2,2) + C(2,2)*C(2,2) = 1+1+1 = 3
    
    // Test 4: Not enough points on one line
    vector<vector<int>> points4 = {{1,1}, {1,2}, {2,2}, {3,2}};
    cout << "Test 4: " << sol.countTrapezoids(points4) << endl; // Expected: 0
    // y=1: 1 point (not enough), y=2: 3 points
    
    return 0;
}

/*
Detailed Explanation:

Why this works:
- A horizontal trapezoid MUST have horizontal parallel sides
- Horizontal sides = points with same y-coordinate
- We need at least 2 points on each of 2 different y-coordinates
- Any selection of 2 points from one line + 2 points from another line forms a trapezoid

Why we don't need to check x-coordinates:
- The problem states "convex quadrilateral"
- Any 4 points (2 from each horizontal line) will form a trapezoid
- The convexity is guaranteed by having 2 horizontal parallel sides

Edge Cases:
1. Less than 4 points total -> 0 trapezoids
2. All points on same horizontal line -> 0 trapezoids
3. Only one point on one line -> 0 trapezoids
4. Multiple horizontal lines with enough points -> count all combinations

Alternative Approach (less efficient):
- Try all combinations of 4 points: C(n, 4)
- Check if they form horizontal trapezoid
- Time: O(n^4), not recommended for large inputs
*/

