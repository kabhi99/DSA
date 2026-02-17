# GENERAL TRAPEZOID PROBLEM - COMPLETE EXPLANATION

Problem: Count unique trapezoids from given points
- Trapezoid = convex quadrilateral with AT LEAST one pair of parallel sides
- Parallel sides = same slope (ANY slope, not just horizontal!)

Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
Output: 2

## SOLUTION APPROACH

STEP 1: Generate All Pairs of Points
-------------------------------------
For n points, we have C(n,2) = n*(n-1)/2 pairs
Each pair represents a potential SIDE of the trapezoid

Example with 5 points: 10 pairs total
(0,1), (0,2), (0,3), (0,4)
(1,2), (1,3), (1,4)
(2,3), (2,4)
(3,4)

STEP 2: Calculate Slope for Each Pair
--------------------------------------
```
slope = Δy/Δx = (y2 - y1)/(x2 - x1)
```

Important Details:
1. Reduce to lowest terms using GCD
Example: dy=6, dx=4 > 6/4 > 3/2

2. Normalize: Make dx always positive
Example: dy=-3, dx=-2 > dy=3, dx=2

3. Handle vertical lines: dx=0 > represent as {1,0}

Examples:
Point pair ([-3,2], [3,0]):
```
dy = 0-2 = -2
dx = 3-(-3) = 6
gcd(2,6) = 2
slope = {-1, 3}  (after reduction)
```

Point pair ([3,0], [3,2]):
```
dy = 2-0 = 2
dx = 3-3 = 0
slope = {1, 0}  (vertical line)
```

STEP 3: Group Pairs by Slope
-----------------------------
Use a Map: slope > list of point pairs

This groups all PARALLEL line segments together!

Example grouping:
{-1,1}: [(0,4), (2,3)]  < These 2 pairs are parallel!
{1,0}:  [(1,3), (2,4)]  < These 2 pairs are parallel!
{0,1}:  [(0,3)]         < Only 1 pair, can't form trapezoid
...

STEP 4: Count Valid Trapezoids
-------------------------------
For each slope with >2 pairs:
For each combination of 2 pairs:
1. Check if they share any points (must be 4 distinct points)
2. Check if 4 points are not all collinear
3. If valid > count as 1 trapezoid

## DETAILED EXAMPLE TRACE

Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]

Index:
0: [-3, 2]
1: [3, 0]
2: [2, 3]
3: [3, 2]
4: [2, -3]

### STEP 1 & 2: Generate All Pairs and Calculate Slopes

Pair (0,1): [-3,2] to [3,0]
```
dy = 0-2 = -2, dx = 3-(-3) = 6
gcd(2,6) = 2
slope = {-2/2, 6/2} = {-1, 3}
```

Pair (0,2): [-3,2] to [2,3]
```
dy = 3-2 = 1, dx = 2-(-3) = 5
slope = {1, 5}
```

Pair (0,3): [-3,2] to [3,2]
```
dy = 2-2 = 0, dx = 3-(-3) = 6
gcd(0,6) = 6
slope = {0, 1}  (horizontal)
```

Pair (0,4): [-3,2] to [2,-3]
```
dy = -3-2 = -5, dx = 2-(-3) = 5
gcd(5,5) = 5
slope = {-1, 1}  < Remember this!
```

Pair (1,2): [3,0] to [2,3]
```
dy = 3-0 = 3, dx = 2-3 = -1
```

Normalize: dx=-1 > dx=1, dy=-3
```
slope = {-3, 1}
```

Pair (1,3): [3,0] to [3,2]
```
dy = 2-0 = 2, dx = 3-3 = 0
slope = {1, 0}  (vertical) < Remember this!
```

Pair (1,4): [3,0] to [2,-3]
```
dy = -3-0 = -3, dx = 2-3 = -1
```

Normalize: dx=-1 > dx=1, dy=3
```
slope = {3, 1}
```

Pair (2,3): [2,3] to [3,2]
```
dy = 2-3 = -1, dx = 3-2 = 1
slope = {-1, 1}  < Same as (0,4)! Parallel!
```

Pair (2,4): [2,3] to [2,-3]
```
dy = -3-3 = -6, dx = 2-2 = 0
slope = {1, 0}  (vertical) < Same as (1,3)! Parallel!
```

Pair (3,4): [3,2] to [2,-3]
```
dy = -3-2 = -5, dx = 2-3 = -1
```

Normalize: slope = {5, 1}

### STEP 3: Grouping by Slope

Slope {-1, 3}: [(0,1)]           - only 1 pair
Slope {1, 5}:  [(0,2)]           - only 1 pair
Slope {0, 1}:  [(0,3)]           - only 1 pair (horizontal)
Slope {-1, 1}: [(0,4), (2,3)]    - 2 pairs! Y
Slope {-3, 1}: [(1,2)]           - only 1 pair
Slope {1, 0}:  [(1,3), (2,4)]    - 2 pairs! Y
Slope {3, 1}:  [(1,4)]           - only 1 pair
Slope {5, 1}:  [(3,4)]           - only 1 pair

### STEP 4: Count Trapezoids

GROUP 1: Slope {-1, 1} - Diagonal lines v
----------------------------------------
Pairs: [(0,4), (2,3)]

Check combination: pair (0,4) with pair (2,3)
Point indices: {0, 4} and {2, 3}
Total unique points: 4 Y

Points: [-3,2], [2,-3], [2,3], [3,2]
Check collinearity: NOT collinear Y

TRAPEZOID #1 FOUND! Y

Visual:
```
 [2,3]o----o[3,2]    slope = -1/1
     /      /                    
    /      /                     
```

[-3,2]o----o[2,-3]    slope = -1/1

Two parallel diagonal sides!

GROUP 2: Slope {1, 0} - Vertical lines ↕
-----------------------------------------
Pairs: [(1,3), (2,4)]

Check combination: pair (1,3) with pair (2,4)
Point indices: {1, 3} and {2, 4}
Total unique points: 4 Y

Points: [3,0], [3,2], [2,3], [2,-3]
Check collinearity: NOT collinear Y

TRAPEZOID #2 FOUND! Y

Visual:
[2,3]o      o[3,2]
```
|      |  (vertical sides)
|                        |
```

[2,-3]o      o[3,0]

Two parallel vertical sides!

### FINAL ANSWER: 2 Trapezoids Y

## WHY CHECK FOR COLLINEARITY?

If all 4 points are on the same line, they don't form a quadrilateral!

Example: Points [0,0], [1,1], [2,2], [3,3] (all on y=x line)

All pairs have slope {1,1}:
(0,1), (0,2), (0,3), (1,2), (1,3), (2,3) - all 6 pairs!

Without collinearity check, we'd incorrectly count:
- (0,1) with (2,3): 4 distinct points but ALL on same line!
- (0,2) with (1,3): same issue
- etc.

These are NOT convex quadrilaterals, just 4 collinear points.

So we use cross product to check:
If (p2-p1) x (p3-p1) = 0 AND (p2-p1) x (p4-p1) = 0
> All on same line > REJECT

## COMPLEXITY ANALYSIS

Time Complexity: O(n2 + k2)
- Generate all pairs: O(n2)
- For each slope group: O(pairs2)
- Worst case: All pairs same slope > O(n⁴)
- Average case: k << n2 > O(n2 + k2)

Space Complexity: O(n2)
- Store all pairs in map

For most inputs, pairs are distributed across different slopes,
so the k2 part is much smaller than n⁴.

## KEY INSIGHTS

1. **Parallel = Same Slope**
Group all line segments by slope to find parallel sides

2. **Trapezoid = 2 Parallel Sides**
Pick any 2 parallel segments with 4 distinct points

3. **Must Check Collinearity**
4 points on same line ! quadrilateral

4. **Slope Representation**
Use reduced fraction (dy/dx) normalized with positive dx
Handle vertical lines specially as {1, 0}
