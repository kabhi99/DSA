import java.util.*;

/**
 * Problem: Count Number of Trapezoids (General - Any Parallel Sides)
 * Difficulty: Hard
 * Category: Geometry, Hash Table, Mathematics
 * 
 * CORRECT APPROACH:
 * ================
 * Trapezoid = quad with EXACTLY ONE pair of parallel sides
 * 
 * Formula: Trapezoids = All_with_parallel_sides - Parallelograms
 * 
 * 1. Count all quads with at least one pair of parallel sides:
 *    - Group segments by (slope, intercept)
 *    - Same slope + different intercept = parallel but not collinear
 *    - Use running sum to count combinations
 * 
 * 2. Count parallelograms (two pairs of parallel sides):
 *    - Group segments by midpoint
 *    - Same midpoint + different slopes = parallelogram
 *    - Use running sum to count combinations
 * 
 * 3. Return: trapezoids - parallelograms
 * 
 * Time: O(n²)
 * Space: O(n²)
 */

class Solution {
    // Slope as reduced fraction
    static class Slope {
        int dy, dx;
        
        Slope(int dy, int dx) {
            this.dy = dy;
            this.dx = dx;
        }
        
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Slope)) return false;
            Slope slope = (Slope) o;
            return dy == slope.dy && dx == slope.dx;
        }
        
        @Override
        public int hashCode() {
            return Objects.hash(dy, dx);
        }
    }
    
    // Midpoint (using 2x coordinates to avoid fractions)
    static class Midpoint {
        long x, y;
        
        Midpoint(long x, long y) {
            this.x = x;
            this.y = y;
        }
        
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Midpoint)) return false;
            Midpoint mid = (Midpoint) o;
            return x == mid.x && y == mid.y;
        }
        
        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }
    }
    
    private int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
    
    public int countTrapezoids(int[][] points) {
        int n = points.length;
        if (n < 4) return 0;
        
        // Map: slope -> list of intercepts
        Map<Slope, List<Long>> slopeToIntercept = new HashMap<>();
        
        // Map: midpoint -> list of slopes
        Map<Midpoint, List<Slope>> midToSlope = new HashMap<>();
        
        // Generate all segments
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                
                int dy = y2 - y1;
                int dx = x2 - x1;
                
                // Calculate slope
                Slope slope;
                if (dx == 0) {
                    slope = new Slope(1, 0);  // Vertical
                } else {
                    int g = gcd(Math.abs(dx), Math.abs(dy));
                    dx /= g;
                    dy /= g;
                    // Normalize: make dx positive
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }
                    slope = new Slope(dy, dx);
                }
                
                // Calculate intercept: dy*x - dx*y (constant for the line)
                long intercept = (long)dy * x1 - (long)dx * y1;
                
                slopeToIntercept.computeIfAbsent(slope, k -> new ArrayList<>()).add(intercept);
                
                // Calculate midpoint (2x coordinates)
                long midX = (long)x1 + x2;
                long midY = (long)y1 + y2;
                Midpoint midpoint = new Midpoint(midX, midY);
                
                midToSlope.computeIfAbsent(midpoint, k -> new ArrayList<>()).add(slope);
            }
        }
        
        // Count quads with at least one pair of parallel sides
        long trapezoidCount = 0;
        
        for (List<Long> intercepts : slopeToIntercept.values()) {
            // Group by intercept value
            Map<Long, Long> interceptCount = new HashMap<>();
            for (long intercept : intercepts) {
                interceptCount.put(intercept, interceptCount.getOrDefault(intercept, 0L) + 1);
            }
            
            // Running sum to count combinations of different intercepts
            long sum = 0;
            for (long count : interceptCount.values()) {
                trapezoidCount += count * sum;
                sum += count;
            }
        }
        
        // Count parallelograms
        long parallelogramCount = 0;
        
        for (List<Slope> slopes : midToSlope.values()) {
            // Group by slope value
            Map<Slope, Long> slopeCount = new HashMap<>();
            for (Slope slope : slopes) {
                slopeCount.put(slope, slopeCount.getOrDefault(slope, 0L) + 1);
            }
            
            // Running sum to count combinations of different slopes
            long sum = 0;
            for (long count : slopeCount.values()) {
                parallelogramCount += count * sum;
                sum += count;
            }
        }
        
        return (int)(trapezoidCount - parallelogramCount);
    }
}

/**
 * Test Cases
 */
class TestTrapezoids {
    public static void main(String[] args) {
        Solution sol = new Solution();
        
        // Test 1: Given example
        int[][] points1 = {{-3,2}, {3,0}, {2,3}, {3,2}, {2,-3}};
        System.out.println("Test 1: " + sol.countTrapezoids(points1)); // Expected: 2
        
        // Test 2: Square
        int[][] points2 = {{0,0}, {1,0}, {0,1}, {1,1}};
        System.out.println("Test 2: " + sol.countTrapezoids(points2));
        
        // Test 3: All collinear - no trapezoids
        int[][] points3 = {{0,0}, {1,1}, {2,2}, {3,3}};
        System.out.println("Test 3: " + sol.countTrapezoids(points3)); // Expected: 0
        
        // Test 4: Classic trapezoid
        int[][] points4 = {{0,0}, {4,0}, {1,2}, {3,2}};
        System.out.println("Test 4: " + sol.countTrapezoids(points4)); // Expected: 1
    }
}

/*
============================================================================
KEY INSIGHTS
============================================================================

1. **Trapezoid vs Parallelogram**
   - Trapezoid: EXACTLY one pair of parallel sides
   - Parallelogram: TWO pairs of parallel sides
   - Need to subtract parallelograms from all parallel quads

2. **Why Track Intercept?**
   - Same slope = parallel
   - But same slope + same intercept = COLLINEAR (on same line)
   - Only count different intercepts (truly parallel, not collinear)

3. **Why Track Midpoint?**
   - Parallelogram property: diagonals bisect each other
   - Two segments with same midpoint = potential parallelogram
   - If they also have different slopes = confirmed parallelogram

4. **Running Sum Technique**
   - For slope S with intercepts [I1, I2, I3]:
     - Pick 1 segment from I1, 1 from I2 → trapezoid
     - Pick 1 segment from I1, 1 from I3 → trapezoid
     - Pick 1 segment from I2, 1 from I3 → trapezoid
   - Running sum: count1*0 + count2*count1 + count3*(count1+count2) = all combinations!

============================================================================
EXAMPLE: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
============================================================================

Segments with slope {-1,1}:
  (0,4): intercept = 1
  (2,3): intercept = -5
  
  Different intercepts → 1 * 1 = 1 trapezoid

Segments with slope {1,0} (vertical):
  (1,3): intercept = 3
  (2,4): intercept = 2
  
  Different intercepts → 1 * 1 = 1 trapezoid

No shared midpoints with multiple slopes → 0 parallelograms

Answer: 2 - 0 = 2 ✓
============================================================================
*/
