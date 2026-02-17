# TRAPEZOID COUNTING - CORRECT APPROACH EXPLAINED

Problem: Count trapezoids (exactly ONE pair of parallel sides)
Input: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]
Output: 2

## WHY MY FIRST APPROACH WAS WRONG

 WRONG APPROACH: Just group by slope
------------------------------------
Problem 1: COLLINEAR SEGMENTS
Three points on same line: A, B, C (all on y = x)
Segments: AB, AC, BC all have slope = 1

If we just group by slope:
Pick AB and BC > But they share point B! X
Even if we check for 4 distinct points, A-B-C-D on same line
doesn't form a quadrilateral! X

Problem 2: PARALLELOGRAMS
A square has:
- 2 horizontal parallel sides
- 2 vertical parallel sides
= parallelogram (2 pairs of parallel sides)

```
Trapezoid = EXACTLY 1 pair of parallel sides
```

We're counting parallelograms when we shouldn't! X

##  CORRECT APPROACH: Track Intercept + Midpoint

Formula: Trapezoids = All_with_parallel_sides - Parallelograms

PART 1: Count All Quads with At Least One Pair of Parallel Sides
------------------------------------------------------------------

Key Insight: Same slope + DIFFERENT intercept = parallel but not collinear

What is intercept?
For line passing through (x,y) with slope dy/dx:
Standard form: dy*x - dx*y = constant
This constant is the "intercept" (generalized form)

Example:
Line y = 2x + 3 > 2x - y + 3 = 0 > 2x - y = -3
For slope {2,1}: intercept = 2*x - 1*y = -3

Why Different Intercepts Matter:
Same slope, same intercept = COLLINEAR (same line) > reject!
Same slope, different intercept = PARALLEL (different lines) > count!

Algorithm:
1. For each segment (pair of points):
- Calculate slope {dy, dx} (reduced, normalized)
- Calculate intercept = dy*x - dx*y
- Store in map: slope > list of intercepts

2. For each slope:
- Group segments by intercept value
- For different intercept values, count combinations
- Use running sum: intercept_i pairs with all previous intercepts

PART 2: Count Parallelograms to Subtract
-----------------------------------------

Key Insight: Parallelogram's diagonals bisect each other (share midpoint)

Property of Parallelogram:
If ABCD is a parallelogram:
Diagonal AC and diagonal BD intersect at their midpoint M

Converse: If two segments share a midpoint, they're diagonals of a parallelogram

Algorithm:
1. For each segment:
- Calculate midpoint (use 2x coordinates to avoid fractions)
- Store in map: midpoint > list of slopes

2. For each midpoint:
- If multiple segments share this midpoint with different slopes
- They form parallelograms
- Use running sum: slope_i pairs with all previous slopes

PART 3: Final Answer
---------------------
```
Trapezoids = (All with parallel sides) - (Parallelograms)
```

## DETAILED EXAMPLE: points = [[-3,2],[3,0],[2,3],[3,2],[2,-3]]

Let's label points:
0: [-3,2]
1: [3,0]
2: [2,3]
3: [3,2]
4: [2,-3]

### STEP 1: Generate All Segments with (Slope, Intercept, Midpoint)

Segment (0,1): [-3,2] > [3,0]
```
dy = 0-2 = -2, dx = 3-(-3) = 6
gcd(2,6) = 2 > slope = {-1, 3}
intercept = (-1)*(-3) - 3*2 = 3 - 6 = -3
midpoint = (-3+3, 2+0) = (0, 2)
```

Segment (0,2): [-3,2] > [2,3]
```
dy = 1, dx = 5
slope = {1, 5}
intercept = 1*(-3) - 5*2 = -13
midpoint = (-1, 5)
```

Segment (0,3): [-3,2] > [3,2]
```
dy = 0, dx = 6
slope = {0, 1} (horizontal)
intercept = 0*(-3) - 1*2 = -2
midpoint = (0, 4)
```

Segment (0,4): [-3,2] > [2,-3]
```
dy = -5, dx = 5
gcd = 5 > slope = {-1, 1}
intercept = (-1)*(-3) - 1*2 = 3 - 2 = 1  *
midpoint = (-1, -1)
```

Segment (1,2): [3,0] > [2,3]
```
dy = 3, dx = -1 > normalized: dy = -3, dx = 1 > slope = {-3, 1}
intercept = (-3)*3 - 1*0 = -9
midpoint = (5, 3)
```

Segment (1,3): [3,0] > [3,2]
```
dy = 2, dx = 0
slope = {1, 0} (vertical)
intercept = 1*3 - 0*0 = 3  *
midpoint = (6, 2)
```

Segment (1,4): [3,0] > [2,-3]
```
dy = -3, dx = -1 > normalized: slope = {3, 1}
intercept = 3*3 - 1*0 = 9
midpoint = (5, -3)
```

Segment (2,3): [2,3] > [3,2]
```
dy = -1, dx = 1
slope = {-1, 1}
intercept = (-1)*2 - 1*3 = -5  *
midpoint = (5, 5)
```

Segment (2,4): [2,3] > [2,-3]
```
dy = -6, dx = 0
slope = {1, 0} (vertical)
intercept = 1*2 - 0*3 = 2  *
midpoint = (4, 0)
```

Segment (3,4): [3,2] > [2,-3]
```
dy = -5, dx = -1 > normalized: slope = {5, 1}
intercept = 5*3 - 1*2 = 13
midpoint = (5, -1)
```

### STEP 2: Group by (Slope, Intercept)

slope {-1, 3}:
intercept -3: 1 segment (0,1)

slope {1, 5}:
intercept -13: 1 segment (0,2)

slope {0, 1}:
intercept -2: 1 segment (0,3)

slope {-1, 1}:  < TWO DIFFERENT INTERCEPTS! *
intercept 1:  1 segment (0,4)
intercept -5: 1 segment (2,3)

Running sum: count=1, sum=0 > add 1*0 = 0, sum=1
```
count=1, sum=1 > add 1*1 = 1, sum=2
```

Trapezoids from this slope: 1

slope {-3, 1}:
intercept -9: 1 segment (1,2)

slope {1, 0}:  < TWO DIFFERENT INTERCEPTS! *
intercept 3: 1 segment (1,3)
intercept 2: 1 segment (2,4)

Running sum: count=1, sum=0 > add 1*0 = 0, sum=1
```
count=1, sum=1 > add 1*1 = 1, sum=2
```

Trapezoids from this slope: 1

slope {3, 1}:
intercept 9: 1 segment (1,4)

slope {5, 1}:
intercept 13: 1 segment (3,4)

TOTAL TRAPEZOIDS (with at least one parallel pair): 1 + 1 = 2

### STEP 3: Group by Midpoint

midpoint (0, 2):
slope {-1, 3}: 1 segment

midpoint (-1, 5):
slope {1, 5}: 1 segment

midpoint (0, 4):
slope {0, 1}: 1 segment

midpoint (-1, -1):
slope {-1, 1}: 1 segment

midpoint (5, 3):
slope {-3, 1}: 1 segment

midpoint (6, 2):
slope {1, 0}: 1 segment

midpoint (5, -3):
slope {3, 1}: 1 segment

midpoint (5, 5):
slope {-1, 1}: 1 segment

midpoint (4, 0):
slope {1, 0}: 1 segment

midpoint (5, -1):
slope {5, 1}: 1 segment

All midpoints have only 1 segment > No parallelograms!

PARALLELOGRAMS: 0

### FINAL ANSWER

```
Trapezoids = All_with_parallel_sides - Parallelograms
```

= 2 - 0
= 2 Y

## VISUAL REPRESENTATION

Trapezoid 1: Using slope {-1,1} segments
Points: 0:[-3,2], 4:[2,-3], 2:[2,3], 3:[3,2]

```
 [2,3]o----o[3,2]    (segment with intercept -5)
     /      /                                   
    /      /  slope = -1/1                      
   /      /                                     
```

[-3,2]o----o[2,-3]    (segment with intercept 1)

Trapezoid 2: Using slope {1,0} (vertical) segments
Points: 1:[3,0], 3:[3,2], 2:[2,3], 4:[2,-3]

[2,3]o      o[3,2]
```
|      |  (vertical lines with different x-intercepts)
|                                                    |
|                                                    |
```

[2,-3]o      o[3,0]

## WHY RUNNING SUM WORKS

For slope S with intercept counts: [c1, c2, c3]

We want: c1*c2 + c1*c3 + c2*c3

Running sum:
Process c1: add c1*0 = 0,     sum = c1
Process c2: add c2*c1,        sum = c1+c2
Process c3: add c3*(c1+c2),   sum = c1+c2+c3

```
Total = c2*c1 + c3*c1 + c3*c2 = c1*c2 + c1*c3 + c2*c3 Y
```

This is the SAME technique used in the horizontal trapezoid problem!
