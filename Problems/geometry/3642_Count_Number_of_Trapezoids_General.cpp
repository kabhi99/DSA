#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;

/*
Problem: Count Number of Trapezoids (General - Any Parallel Sides)
Difficulty: Hard
Category: Geometry, Math, Combinatorics

Problem Statement:
- Given 2D points, count unique trapezoids
- Trapezoid: convex quadrilateral with EXACTLY ONE pair of parallel sides
- Parallel sides = same slope (not just horizontal!)
- Choose any 4 distinct points

Key Difference from 3623. Count Number of Trapezoids I:
- 3623: Only HORIZONTAL trapezoids (parallel to x-axis)
- This: ANY parallel sides (any slope) AND exclude parallelograms

CORRECT APPROACH:
================
1. Count all quadrilaterals with at least one pair of parallel sides
2. Subtract parallelograms (which have TWO pairs of parallel sides)

For Trapezoids:
- Group segments by (slope, intercept)
- Segments with same slope but DIFFERENT intercepts are parallel (not collinear)
- Count combinations using running sum

For Parallelograms:
- Group segments by midpoint
- Two segments with same midpoint but different slopes form a parallelogram
- Count combinations using running sum

Formula: Trapezoids = All_parallel_quads - Parallelograms

Time Complexity: O(n²) for generating pairs + processing
Space Complexity: O(n²) for storing segments
*/

class Solution {
private:
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
    
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        if (n < 4) return 0;
        
        // Map: slope -> vector of intercepts
        // Each element represents a segment with that (slope, intercept)
        map<pair<int,int>, vector<long long>> slopeToIntercept;
        
        // Map: midpoint -> vector of slopes
        // Each element represents a segment with that midpoint
        map<pair<long long, long long>, vector<pair<int,int>>> midToSlope;
        
        // Generate all segments (pairs of points)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                
                int dy = y2 - y1;
                int dx = x2 - x1;
                
                // Calculate slope
                pair<int, int> slope;
                if (dx == 0) {
                    slope = {1, 0};  // Vertical line
                } else {
                    int g = gcd(abs(dx), abs(dy));
                    dx /= g;
                    dy /= g;
                    // Normalize: make dx always positive
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }
                    slope = {dy, dx};
                }
                
                // Calculate intercept for the line
                // For line passing through (x1,y1) with slope dy/dx:
                // y - y1 = (dy/dx) * (x - x1)
                // y*dx - y1*dx = dy*x - dy*x1
                // dy*x - y*dx = dy*x1 - y1*dx
                // Intercept = dy*x1 - y1*dx (to avoid floating point)
                long long intercept = (long long)dy * x1 - (long long)dx * y1;
                
                slopeToIntercept[slope].push_back(intercept);
                
                // Calculate midpoint (using 2x coordinates to avoid fractions)
                long long midX = (long long)x1 + x2;
                long long midY = (long long)y1 + y2;
                pair<long long, long long> midpoint = {midX, midY};
                
                midToSlope[midpoint].push_back(slope);
            }
        }
        
        // Count trapezoids (at least one pair of parallel sides)
        long long trapezoidCount = 0;
        
        for (auto& [slope, intercepts] : slopeToIntercept) {
            // Group by intercept value
            map<long long, long long> interceptCount;
            for (long long intercept : intercepts) {
                interceptCount[intercept]++;
            }
            
            // For each pair of different intercepts, count combinations
            // Use running sum technique
            long long sum = 0;
            for (auto& [intercept, count] : interceptCount) {
                // For each segment in current intercept group
                // pair it with all segments in previous intercept groups
                trapezoidCount += count * sum;
                sum += count;  // Add count of segments (not combinations)
            }
        }
        
        // Count parallelograms (two pairs of parallel sides)
        long long parallelogramCount = 0;
        
        for (auto& [midpoint, slopes] : midToSlope) {
            // Group by slope value
            map<pair<int,int>, long long> slopeCount;
            for (auto& slope : slopes) {
                slopeCount[slope]++;
            }
            
            // For each pair of different slopes, count combinations
            // Use running sum technique
            long long sum = 0;
            for (auto& [slope, count] : slopeCount) {
                // Pair segments with current slope with all previous different slopes
                parallelogramCount += count * sum;
                sum += count;
            }
        }
        
        // Trapezoids = All with parallel sides - Parallelograms
        return trapezoidCount - parallelogramCount;
    }
};

// Test cases
int main() {
    Solution sol;
    
    // Test 1: Given example
    vector<vector<int>> points1 = {{-3,2}, {3,0}, {2,3}, {3,2}, {2,-3}};
    cout << "Test 1: " << sol.countTrapezoids(points1) << endl;  // Expected: 2
    
    // Test 2: Four points forming square
    vector<vector<int>> points2 = {{0,0}, {1,0}, {0,1}, {1,1}};
    cout << "Test 2: " << sol.countTrapezoids(points2) << endl;
    // Square has 2 pairs of parallel sides = parallelogram
    // Horizontal + Vertical + 2 Diagonals = 4 parallel pairs
    // But it's a square (parallelogram), so count = 0
    
    // Test 3: All points collinear - no trapezoids
    vector<vector<int>> points3 = {{0,0}, {1,1}, {2,2}, {3,3}};
    cout << "Test 3: " << sol.countTrapezoids(points3) << endl;  // Expected: 0
    
    // Test 4: Trapezoid (not parallelogram)
    vector<vector<int>> points4 = {{0,0}, {4,0}, {1,2}, {3,2}};
    cout << "Test 4: " << sol.countTrapezoids(points4) << endl;
    // Two horizontal parallel sides: y=0 and y=2
    // Expected: 1
    
    return 0;
}

/*
============================================================================
DETAILED EXPLANATION - CORRECT APPROACH
============================================================================

KEY INSIGHT:
-----------
Trapezoid = quadrilateral with EXACTLY ONE pair of parallel sides
We need to count quads with at least one parallel pair, then SUBTRACT 
parallelograms (which have TWO pairs of parallel sides)

Formula: Trapezoids = All_with_parallel - Parallelograms


STEP 1: Count quads with at least one pair of parallel sides
--------------------------------------------------------------
Challenge: Just grouping by slope is not enough!
Problem: Segments with same slope might be COLLINEAR

Solution: Track both SLOPE and INTERCEPT
- Same slope, different intercept = parallel but not collinear ✓
- Same slope, same intercept = collinear (on same line) ✗

For each slope:
  Group segments by intercept
  For different intercepts, count combinations using running sum
  
Example: 3 segments with slope {1,1}
  Intercept 0: 2 segments → C(2,2) = 1 edge group
  Intercept 1: 3 segments → C(3,2) = 3 edge groups
  Intercept 2: 2 segments → C(2,2) = 1 edge group
  
  Combinations: 1*3 + 1*1 + 3*1 = 7 quads with this parallel slope


STEP 2: Count parallelograms to subtract
-----------------------------------------
Parallelogram property: Two diagonals bisect each other
→ Both diagonals share the SAME MIDPOINT

For each midpoint:
  If multiple segments share this midpoint with different slopes
  → They form parallelograms
  
Count using running sum for each midpoint


STEP 3: Final answer
--------------------
Trapezoids = (Step 1 count) - (Step 2 count)


============================================================================
EXAMPLE TRACE: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
============================================================================

Index: 0:[-3,2], 1:[3,0], 2:[2,3], 3:[3,2], 4:[2,-3]

All segments with (slope, intercept, midpoint):

Segment (0,1): [-3,2] to [3,0]
  dy=-2, dx=6 → slope={-1,3}
  intercept = -1*(-3) - 3*2 = 3-6 = -3
  midpoint = (0, 2)

Segment (0,2): [-3,2] to [2,3]
  dy=1, dx=5 → slope={1,5}
  intercept = 1*(-3) - 5*2 = -13
  midpoint = (-1, 5)

Segment (0,3): [-3,2] to [3,2]
  dy=0, dx=6 → slope={0,1} (horizontal)
  intercept = 0*(-3) - 1*2 = -2
  midpoint = (0, 4)

Segment (0,4): [-3,2] to [2,-3]
  dy=-5, dx=5 → slope={-1,1}
  intercept = -1*(-3) - 1*2 = 1
  midpoint = (-1, -1)

Segment (1,2): [3,0] to [2,3]
  dy=3, dx=-1 → normalized: slope={-3,1}
  intercept = -3*3 - 1*0 = -9
  midpoint = (5, 3)

Segment (1,3): [3,0] to [3,2]
  dy=2, dx=0 → slope={1,0} (vertical)
  intercept = 1*3 - 0*0 = 3
  midpoint = (6, 2)

Segment (1,4): [3,0] to [2,-3]
  dy=-3, dx=-1 → normalized: slope={3,1}
  intercept = 3*3 - 1*0 = 9
  midpoint = (5, -3)

Segment (2,3): [2,3] to [3,2]
  dy=-1, dx=1 → slope={-1,1}
  intercept = -1*2 - 1*3 = -5
  midpoint = (5, 5)

Segment (2,4): [2,3] to [2,-3]
  dy=-6, dx=0 → slope={1,0} (vertical)
  intercept = 1*2 - 0*3 = 2
  midpoint = (4, 0)

Segment (3,4): [3,2] to [2,-3]
  dy=-5, dx=-1 → normalized: slope={5,1}
  intercept = 5*3 - 1*2 = 13
  midpoint = (5, -1)


Group by (slope, intercept):
-----------------------------
slope={-1,1}: intercept 1 (1 segment), intercept -5 (1 segment)
              → 1 combination = 1 quad
              
slope={1,0}: intercept 3 (1 segment), intercept 2 (1 segment)
             → 1 combination = 1 quad

All other slopes: only 1 segment each → 0 combinations

Total quads with parallel sides = 2


Group by midpoint:
------------------
All segments have different midpoints → 0 parallelograms


Final Answer: 2 - 0 = 2 ✓

============================================================================
*/

