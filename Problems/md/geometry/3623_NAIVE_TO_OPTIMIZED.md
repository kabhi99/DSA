# PROBLEM 3623: FROM NAIVE TO OPTIMIZED SOLUTION

Problem: Count horizontal trapezoids from given points
Input: points = [[1,1], [2,1], [3,1], [1,2], [2,2], [3,2]]
Output: 9

Visual:
```
y=2  (1,2)o---(2,2)o---(3,2)o
        |       |           |
y=1  (1,1)o---(2,1)o---(3,1)o
```

## APPROACH 1: NAIVE (BRUTE FORCE) - O(n⁴)

Idea: Try ALL combinations of 4 points and check if they form a horizontal
trapezoid.

Algorithm:
----------
for i in 0..n:
for j in i+1..n:
for k in j+1..n:
for l in k+1..n:
if isHorizontalTrapezoid(points[i], points[j], points[k], points[l]):
count++

What is a horizontal trapezoid?
--------------------------------
A quadrilateral where at least 2 points share the same y-coordinate
AND another 2 points share a different y-coordinate.

Check function:
---------------
boolean isHorizontalTrapezoid(p1, p2, p3, p4):
```
// Count how many points share same y          
yCount = {}                                    
yCount[p1.y]+                                 +
yCount[p2.y]+                                 +
yCount[p3.y]+                                 +
yCount[p4.y]+                                 +

// Need at least 2 y-levels with >2 points each
levels_with_2_or_more = 0                      
for count in yCount.values():                  
    if count >= 2:                             
        levels_with_2_or_more+                +

return levels_with_2_or_more >= 2              
```

Example Trace: n=6 points
---------------------------
Total combinations: C(6,4) = 15

Test {0,1,2,3}: points (1,1), (2,1), (3,1), (1,2)
```
y=1: 3 points, y=2: 1 point
```

Only 1 level has >2 points > NOT a trapezoid X

Test {0,1,3,4}: points (1,1), (2,1), (1,2), (2,2)
```
y=1: 2 points, y=2: 2 points
```

Two levels with >2 points > IS a trapezoid Y

... check all 15 combinations ...

Complexity:
-----------
Time: O(n⁴) - four nested loops
For n=100: 100⁴ = 100,000,000 operations 
For n=1000: 1000⁴ = 1,000,000,000,000 operations 

Space: O(1)

Verdict: TOO SLOW! 

## APPROACH 2: BETTER (GROUP BY Y + NESTED LOOPS) - O(n + k2)

Key Insight: Instead of trying all 4-point combinations, GROUP points
by y-coordinate first, then combine groups!

Observation:
- For horizontal trapezoid, we need 2 points from one y-level and
2 points from another y-level
- So count points at each y-level first, then pick pairs of y-levels

Algorithm:
----------
```
// Step 1: Group points by y-coordinate
```

Map<Integer, Integer> yCount
for each point:
```
yCount[point.y]++

// Step 2: For each pair of y-levels, count combinations
count = 0
yLevels = list of (y-coordinate, point_count) pairs
```

for i in 0..yLevels.size():
for j in i+1..yLevels.size():
```
count1 = yLevels[i].count
count2 = yLevels[j].count
```

if count1 >= 2 and count2 >= 2:
```
edge1 = C(count1, 2)  // Ways to pick 2 from level i
edge2 = C(count2, 2)  // Ways to pick 2 from level j
count += edge1 * edge2

return count
```

Example Trace:
--------------
```
points = [[1,1], [2,1], [3,1], [1,2], [2,2], [3,2]]
```

Step 1: Group by y
```
y=1: 3 points > C(3,2) = 3 edges
y=2: 3 points > C(3,2) = 3 edges
```

Step 2: Nested loops
```
i=0 (y=1), j=1 (y=2):
count += 3 * 3 = 9
```

Final: 9 trapezoids Y

Visual of nested loop:
----------------------
```
 y=2 level                                                 
    v                                                      
o-o-o  (3 points > 3 ways to pick 2)                       
| |                                                       |
| | |  < Combine each edge from y=1 with each edge from y=2
| |                                                       |
o-o-o  (3 points > 3 ways to pick 2)                       
^                                                          
```

```
y=1 level
```

Combinations: 3 x 3 = 9

Complexity:
-----------
Time: O(n + k2)
- O(n): Group points by y-coordinate
- O(k2): Nested loops over k y-levels
where k = number of unique y-coordinates

Best case: k is small (few y-levels) > Fast! Y
Worst case: k = n (all different y) > O(n2) > Still slow for large n 

Space: O(k)

Verdict: BETTER, but can still TLE for large k! 

## DETAILED EXAMPLE: NESTED LOOPS WITH 3 Y-LEVELS

points with y-levels: y=1 (3 pts), y=2 (2 pts), y=3 (2 pts)

Visual:
```
y=3  o----o         C(2,2) = 1

y=2  o----o         C(2,2) = 1

y=1  o-o--o         C(3,2) = 3
```

Nested Loop Execution:
----------------------

Outer i=0 (y=1, 3 pts, edge=3):
```
                                                           |
+-> Inner j=1 (y=2, 2 pts, edge=1):                         
|   count += 3 * 1 = 3                                      
|   Meaning: 3 ways from y=1 x 1 way from y=2 = 3 trapezoids
                                                           |
+-> Inner j=2 (y=3, 2 pts, edge=1):                         
    count += 3 * 1 = 3                                      
    Meaning: 3 ways from y=1 x 1 way from y=3 = 3 trapezoids
```

Outer i=1 (y=2, 2 pts, edge=1):
```
                                                         |
+-> Inner j=2 (y=3, 2 pts, edge=1):                       
    count += 1 * 1 = 1                                    
    Meaning: 1 way from y=2 x 1 way from y=3 = 1 trapezoid
```

Outer i=2 (y=3, 2 pts, edge=1):
(no j > 2, loop ends)

Total: 3 + 3 + 1 = 7 trapezoids

Matrix View:
------------
```
  j=0  j=1  j=2  
  (y=1)(y=2)(y=3)
+----+----+-----+
```

```
i=0  | X  | 3x1| 3x1|  = 3 + 3 = 6
     +----+----+-----------------+
i=1  | X  | X  | 1x1|  = 1        
     +----+----+-----------------+
i=2  | X  | X  | X  |  = 0        
     +----+----+-----------------+
```

Sum: 6 + 1 = 7 Y

Problem with O(k2):
-------------------
If k = 1000 unique y-coordinates:
Nested loop: 1000 x 999 / 2 = 499,500 iterations
> Can cause TLE! ⏱

## APPROACH 3: OPTIMIZED (RUNNING SUM) - O(n + k)

Key Insight: We're computing e1*e2 + e1*e3 + e2*e3 (all pairwise products)
Can we do this WITHOUT nested loops?

Yes! Using RUNNING SUM technique!

Mathematical Trick:
-------------------
Instead of:
e1*e2 + e1*e3 + e2*e3

Rewrite as:
e1*(e2+e3) + e2*e3
= e1*e2 + e1*e3 + e2*e3  (same result!)

Pattern:
Process e1: multiply by (nothing) = 0
Process e2: multiply by (e1)
Process e3: multiply by (e1+e2)

In general for edge i:
Multiply edge_i by SUM of all previous edges!

Algorithm:
----------
```
// Step 1: Group points by y-coordinate (same as before)
```

Map<Integer, Integer> yCount
for each point:
```
yCount[point.y]++

// Step 2: Running sum (ONE loop, not nested!)
count = 0
sum = 0
```

for each y-level in yCount:
```
edge = C(pointCount, 2)
count += edge * sum      // Multiply with all previous
sum += edge              // Add current to sum

return count
```

Example Trace with 3 y-levels:
-------------------------------
```
y=1: 3 points > e1 = C(3,2) = 3
y=2: 2 points > e2 = C(2,2) = 1
y=3: 2 points > e3 = C(2,2) = 1
```

Goal: e1*e2 + e1*e3 + e2*e3 = 3*1 + 3*1 + 1*1 = 7

Running Sum Execution:
----------------------

Initial: count = 0, sum = 0

```
+--------------------------------------------------------------+
| ITERATION 1: Process y=1 (edge = 3)                          |
|                                                              |
|   count += 3 * sum = 3 * 0 = 0                               |
|   sum += 3         > sum = 3                                 |
|                                                              |
|   State: count = 0, sum = 3                                  |
|   Meaning: No trapezoids yet (need 2 y-levels)               |
+--------------------------------------------------------------+

+--------------------------------------------------------------+
| ITERATION 2: Process y=2 (edge = 1)                          |
|                                                              |
|   count += 1 * sum = 1 * 3 = 3                               |
|   sum += 1         > sum = 4                                 |
|                                                              |
|   State: count = 3, sum = 4                                  |
|   Meaning: e2 paired with e1 > 1*3 = 3 trapezoids            |
|                                                              |
|   What is sum=3? It's e1                                     |
|   So: 1 * 3 = e2 * e1 = trapezoids between y=2 and y=1 Y     |
+--------------------------------------------------------------+

+--------------------------------------------------------------+
| ITERATION 3: Process y=3 (edge = 1)                          |
|                                                              |
|   count += 1 * sum = 1 * 4 = 4                               |
|   sum += 1         > sum = 5                                 |
|                                                              |
|   State: count = 7, sum = 5                                  |
|   Meaning: e3 paired with (e1+e2) > 1*4 = 4 trapezoids       |
|                                                              |
|   What is sum=4? It's e1+e2 = 3+1 = 4                        |
|   So: 1 * (3+1) = 1*3 + 1*1 = e3*e1 + e3*e2 Y                |
|                                                              |
|   Added: e1*e3 = 3, e2*e3 = 1, total = 4                     |
+--------------------------------------------------------------+
```

Final: count = 7 Y

Visual Flow:
------------
```
 sum = 0            
    v               
Process e1=3        
                   |
 sum = 3            
    v               
Process e2=1        
                   |
 sum = 4 (=e1+e2)   
    v               
Process e3=1        
                   |
 sum = 5 (=e1+e2+e3)
```

Results:
e1: paired with 0       > added 0
e2: paired with e1      > added e1*e2 = 3
e3: paired with e1+e2   > added e1*e3 + e2*e3 = 4
Total: 0 + 3 + 4 = 7 Y

Why it works:
-------------
Distributive property!

e3 * sum = e3 * (e1 + e2)
= e3*e1 + e3*e2

By maintaining sum as cumulative total of all previous edges,
we get ALL combinations in ONE multiplication per edge!

Complexity:
-----------
Time: O(n + k)
- O(n): Group points by y-coordinate
- O(k): Single loop over k y-levels
where k = number of unique y-coordinates

Space: O(k)

Verdict: OPTIMAL! 

## SIDE-BY-SIDE COMPARISON

Example: 3 y-levels with edges [3, 1, 1]
Goal: 3*1 + 3*1 + 1*1 = 7

NESTED LOOPS (O(k2)):                RUNNING SUM (O(k)):
---------------------                --------------------

```
i=0, j=1:                            sum=0
ans += 3*1 = 3                     Process e1=3:
ans += 3*0 = 0

i=0, j=2:                              sum = 3
ans += 3*1 = 3
```

Process e2=1:

```
i=1, j=2:                              ans += 1*3 = 3
ans += 1*1 = 1                       sum = 4
```

Final: 3+3+1 = 7 Y                   Process e3=1:
```
ans += 1*4 = 4
```

Iterations: 3                          sum = 5

Final: 0+3+4 = 7 Y

Iterations: 3

Both give same answer, but:
- Nested: O(k2) > scales poorly
- Running sum: O(k) > scales linearly

## CODE COMPARISON

### APPROACH 2: Nested Loops - O(k2)

```
Map<Integer, Integer> yCount = new HashMap<>();
for (int[] point : points) {
yCount.put(point[1], yCount.getOrDefault(point[1], 0) + 1);

}

List<Integer> counts = new ArrayList<>(yCount.values());
long ans = 0;

// NESTED LOOPS
for (int i = 0; i < counts.size(); i++) {
for (int j = i + 1; j < counts.size(); j++) {            
    long edge1 = counts.get(i) * (counts.get(i) - 1) / 2;
    long edge2 = counts.get(j) * (counts.get(j) - 1) / 2;
    ans += edge1 * edge2;                                
}                                                        

}

return (int)(ans % MOD);
```

### APPROACH 3: Running Sum - O(k)

```
Map<Integer, Integer> yCount = new HashMap<>();
for (int[] point : points) {
yCount.put(point[1], yCount.getOrDefault(point[1], 0) + 1);

}

long ans = 0, sum = 0;

// SINGLE LOOP with running sum
for (int count : yCount.values()) {
long edge = (long)count * (count - 1) / 2;
ans += edge * sum;   // < Key: multiply with accumulated sum
sum += edge;         // < Key: add to running sum

}

return (int)(ans % MOD);
```

## PERFORMANCE COMPARISON

Number of y-levels (k):  Nested Loops:   Running Sum:   Speed Up:
---------------------    -------------   ------------   ---------
10                   45             10            4.5x
100                4,950           100           49.5x
1,000            499,500          1,000          500x
10,000         49,995,000         10,000         5,000x

For k=1000:
Nested: 499,500 iterations > TLE! ⏱
Running sum: 1,000 iterations > Accepted! 

## KEY INSIGHTS

1.  Group by y-coordinate first (reduces from O(n⁴) to O(n+k2))

2.  Use combinatorics: C(n,2) = n*(n-1)/2
- Represents ways to pick 2 points from n points

3.  Pairwise products can be computed with running sum
- e1*e2 + e1*e3 + e2*e3 = e1*(e2+e3) + e2*e3
- Maintain sum of all previous edges

4.  Distributive property is the key
- edge * (sum of previous) = (edge * each previous)
- Gets all combinations in one multiplication!

5.  Running sum: O(k) vs Nested: O(k2)
- Critical optimization for large k

## FINAL OPTIMIZED SOLUTION

```java
class Solution {
private static final int MOD = 1_000_000_007;                      

public int countTrapezoids(int[][] points) {                       
    // Step 1: Group by y-coordinate                               
    Map<Integer, Integer> yCount = new HashMap<>();                
    for (int[] point : points) {                                   
        yCount.put(point[1], yCount.getOrDefault(point[1], 0) + 1);
    }                                                              

    // Step 2: Running sum to count trapezoids                     
    long ans = 0, sum = 0;                                         
    for (int count : yCount.values()) {                            
        long edge = (long)count * (count - 1) / 2;                 
        ans += edge * sum;                                         
        sum += edge;                                               
    }                                                              

    return (int)(ans % MOD);                                       
}                                                                  

}
```

Time: O(n + k) where k = unique y-coordinates
Space: O(k)
Result: OPTIMAL! 
