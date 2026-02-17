# **BINARY SEARCH - COMPLETE GUIDE**

Two powerful patterns: Search for Element vs Search for Answer!

### **TABLE OF CONTENTS**

1. Core Concepts - When to Use Binary Search
2. Template Comparison: `l < r` vs `l <= r`  CRITICAL!
 MINIMIZE MAX vs MAXIMIZE MIN - Which Pattern? 
3.  HOW TO ESTABLISH BOUNDS (lo, hi)  COMPLETE GUIDE
- 5 Proven Strategies
- Pattern-Based Bounds Table
- Common Mistakes to Avoid
- Step-by-Step Process
4. Binary Search Patterns (Classic, Bounds, Min/Max, Kth)
5. Key Problems with Complete Solutions (20+ problems!)
6. Deep Dive - `l < r` vs `l <= r` Explained
- Why +1 is Critical (Visual Explanation)
7. Count Function Patterns (Staircase, Sliding Window, etc.)
8. Advanced Tips & Tricks
9. Problem List by Category (80+ problems!)
10. Quick Reference Cheat Sheet

## **PART 1: CORE CONCEPTS**

### ** WHAT IS BINARY SEARCH?**

**TWO MAIN TYPES:**

**TYPE 1: Classic Binary Search**
Search for specific element in sorted array
Example: Find index of 5 in [1, 3, 5, 7, 9]

**TYPE 2: Binary Search on Answer**  (More Common in Interviews!)
Search for answer in a range of possible values
Example: What's the minimum speed to eat all bananas in H hours?

### ** WHEN TO USE BINARY SEARCH?**

**STRONG SIGNALS:**

 Array is sorted (classic binary search)
 "Find kth smallest/largest"
 "Minimum/Maximum value such that..."
 "Minimize maximum" or "Maximize minimum"
 Can define search space [lo, hi] with bounds
 Can write validation/count function: "Is X possible?"

**KEYWORDS:**

- "Kth smallest/largest"
- "Minimum speed/time/capacity to..."
- "Split array into K parts minimizing..."
- "Smallest number that satisfies..."
- "Find element in sorted/rotated array"

**GOLDEN RULE:**

If you can:
1. Define search space [lo, hi]
2. Write a function: isValid(mid) or count(mid)
3. The answer has MONOTONIC property (if X works, X+1 also works OR vice versa)

Then use Binary Search!

### **⚡ TIME COMPLEXITY**

Classic BS:           O(log N)
BS on Answer:         O(log(range) x O(validation_function))

Example: Koko Eating Bananas
Range: [1, max(piles)] ~ 10^9
Validation: O(N) to check all piles
Total: O(N log(10^9)) = O(30N) ~ O(N)

## **PART 2: TEMPLATE COMPARISON - `l < r` vs `l <= r`** 

This is THE most confusing part! Let's clarify once and for all.

### **TEMPLATE 1: `while (l < r)` - FIND MINIMUM**  RECOMMENDED FOR BS ON ANSWER

USE WHEN: Finding MINIMUM value that satisfies condition

**TEMPLATE:**

```
int l = 0, r = max_value;

while (l < r) {
int mid = l + (r - l) / 2;  // NO +1 here!                 

if (isValid(mid)) {                                        
    r = mid;        // mid works, try smaller (search left)
} else {                                                   
    l = mid + 1;    // mid doesn't work, must go bigger    
}                                                          

}

return l;  // or r, they're equal when loop exits
```

**KEY POINTS:**
- Loop exits when l == r
- mid = (l + r) / 2  (NO +1)
- r = mid (NOT mid - 1)
- l = mid + 1
- Return l (or r, same thing)

**WHY IT WORKS:**
We're finding LEFTMOST valid value. When isValid(mid) is true,
answer could be mid or something smaller, so r = mid.

INFINITE LOOP?
No! Because l = mid + 1 always increases l, eventually l == r.

### **TEMPLATE 2: `while (l < r)` - FIND MAXIMUM**  NEEDS +1 TRICK!

USE WHEN: Finding MAXIMUM value that satisfies condition

**TEMPLATE:**

```
int l = 0, r = max_value;

while (l < r) {
int mid = l + (r - l + 1) / 2;  //  +1 is CRITICAL!        

if (isValid(mid)) {                                        
    l = mid;        // mid works, try larger (search right)
} else {                                                   
    r = mid - 1;    // mid doesn't work, must go smaller   
}                                                          

}

return l;  // or r, they're equal
```

**KEY POINTS:**
- mid = (l + r + 1) / 2   THE +1 IS CRITICAL!
- l = mid (NOT mid + 1)
- r = mid - 1
- Return l (or r)

### **WHY +1 IS CRITICAL - VISUAL EXPLANATION** 

THE PROBLEM: Without +1, you get INFINITE LOOP!

SCENARIO: Searching for maximum, currently l=5, r=6, answer is 6

###  WITHOUT +1 (WRONG - INFINITE LOOP!):

```
while (l < r) {              // l=5, r=6
mid = (5 + 6) / 2;       // mid = 11/2 = 5  (integer division!)

if (isValid(5)) {        // Let's say 5 is valid               
    l = mid;             // l = 5                              
}                                                              

}
```

Next iteration:
```
l = 5, r = 6             //  NOTHING CHANGED!
mid = (5 + 6) / 2 = 5    // Same mid!
isValid(5) is still true
l = 5                    // l doesn't move!
```

> INFINITE LOOP! 

The loop will run FOREVER because l and r never converge!

###  WITH +1 (CORRECT - CONVERGES!):

```
while (l < r) {              // l=5, r=6
mid = (5 + 6 + 1) / 2;   // mid = 12/2 = 6  Y  

if (isValid(6)) {        // Check if 6 is valid
    l = mid;             // l = 6              
}                                              

}
```

Now:
```
l = 6, r = 6             // Y Loop exits! (l == r)
```

OR if isValid(6) is false:
```
r = mid - 1;             // r = 5
```

Next iteration:
```
l = 5, r = 5             // Y Loop exits! (l == r)
```

> CONVERGES CORRECTLY! 

### **THE GOLDEN RULE** 

```
+-------------------------------------------------------------------------+
|  If you write:  l = mid   >  You MUST use:  mid = (l + r + 1) / 2       |
|  If you write:  r = mid   >  You can use:   mid = (l + r) / 2           |
+-------------------------------------------------------------------------+
```

WHY? Integer division rounds DOWN. When l and r are adjacent:
- mid = (l + r) / 2 = l  (rounds to left)
- If we do l = mid, nothing changes > infinite loop!
- Adding +1 forces mid = r > loop progresses

**SYMMETRY:**
MINIMUM: mid = (l+r)/2,     r = mid,   l = mid+1
MAXIMUM: mid = (l+r+1)/2 , l = mid,   r = mid-1

## ⚡ MINIMIZE MAXIMUM vs MAXIMIZE MINIMUM ⚡ (CONFUSING BUT CRITICAL!)

This trips up EVERYONE! The wording seems backwards.

### **THE RULE** 

"MINIMIZE the MAXIMUM"  >  Use MINIMUM Pattern (no +1)
"MAXIMIZE the MINIMUM"  >  Use MAXIMUM Pattern (+1 needed!)

Wait, WHAT?! Let me explain...

### **WHY: MINIMIZE THE MAXIMUM**

**PROBLEM PATTERN:**
"Split array into k parts, MINIMIZE the MAXIMUM sum"
"Ship packages in d days, MINIMIZE the MAXIMUM capacity needed"
"Eat bananas in h hours, MINIMIZE the MAXIMUM eating speed"

WHAT YOU'RE ACTUALLY SEARCHING FOR:
The MINIMUM value that makes the task possible!

Search space: [some_min, some_max]
Question: "What's the SMALLEST capacity/speed that works?"

> You want the MINIMUM valid value
> Use MINIMUM PATTERN (no +1)

**TEMPLATE:**

```
int minimizeMaximum(...) {
int lo = ...;  // minimum possible maximum                      
int hi = ...;  // maximum possible maximum                      

while (lo < hi) {                                               
    int mid = lo + (hi - lo) / 2;  // NO +1!                    

    if (canDoWithMax(mid)) {  // Can we do it with this maximum?
        hi = mid;              // Yes! Try smaller maximum      
    } else {                                                    
        lo = mid + 1;          // No, need larger maximum       
    }                                                           
}                                                               

return lo;  // The MINIMUM of all possible MAXIMUMs             

}
```

### EXAMPLE: Koko Eating Bananas (LC 875)

```
piles = [3, 6, 7, 11], h = 8
lo = 1, hi = 11
```

> Answer: 6 (MINIMUM speed that works)
> TEMPLATE: MINIMUM (no +1) Y

Other examples: Split Array (LC 410), Ship Packages (LC 1011)

### **WHY: MAXIMIZE THE MINIMUM**

**PROBLEM PATTERN:**
"Place m balls, MAXIMIZE the MINIMUM distance"
"Distribute candies to k children, MAXIMIZE the MINIMUM per child"
"Divide chocolate, MAXIMIZE the MINIMUM sweetness"

WHAT YOU'RE ACTUALLY SEARCHING FOR:
The MAXIMUM value that's still achievable!

Search space: [some_min, some_max]
Question: "What's the LARGEST minimum we can guarantee?"

> You want the MAXIMUM valid value
> Use MAXIMUM PATTERN (+1 needed!)

**TEMPLATE:**

```
int maximizeMinimum(...) {
int lo = ...;  // minimum possible minimum                    
int hi = ...;  // maximum possible minimum                    

while (lo < hi) {                                             
    int mid = lo + (hi - lo + 1) / 2;  //  +1 NEEDED!         

    if (canAchieveMin(mid)) {  // Can we achieve this minimum?
        lo = mid;               // Yes! Try larger minimum    
    } else {                                                  
        hi = mid - 1;           // No, need smaller minimum   
    }                                                         
}                                                             

return lo;  // The MAXIMUM of all achievable MINIMUMs         

}
```

### EXAMPLE: Magnetic Force Between Balls (LC 1552)

```
position = [1,2,3,4,7], m = 3
lo = 1, hi = 6
```

> Answer: 3 (MAXIMUM achievable minimum distance)
> TEMPLATE: MAXIMUM (+1 needed!) Y

Other examples: Maximum Candies (LC 2226), Divide Chocolate (LC 1231)

### **THE KEY INSIGHT** 

Look at the FIRST word to determine template:

```
+-------------------------------------------------------------------------+
|                                                                         |
|  "MINIMIZE ..."  >  Finding MINIMUM  >  Use MINIMUM pattern (no +1)     |
|  "MAXIMIZE ..."  >  Finding MAXIMUM  >  Use MAXIMUM pattern (+1!)       |
|                                                                         |
|  Ignore the second word! It just describes what you're optimizing.      |
|                                                                         |
+-------------------------------------------------------------------------+
```

Think of it as:
"Minimize X" = Find the smallest X
"Maximize X" = Find the largest X

### **COMPARISON TABLE**

```
+----------------------------+----------------+----------------+----------+
| Problem Phrasing           | Searching For  | Pattern        | Need +1? |
+----------------------------+----------------+----------------+----------+
| MINIMIZE maximum sum       | Minimum value  | MINIMUM        | NO       |
| MINIMIZE maximum capacity  | Minimum value  | MINIMUM        | NO       |
| MINIMIZE maximum speed     | Minimum value  | MINIMUM        | NO       |
| MINIMIZE largest value     | Minimum value  | MINIMUM        | NO       |
+----------------------------+----------------+----------------+----------+
| MAXIMIZE minimum distance  | Maximum value  | MAXIMUM        | YES      |
| MAXIMIZE minimum sweetness | Maximum value  | MAXIMUM        | YES      |
| MAXIMIZE candies per child | Maximum value  | MAXIMUM        | YES      |
| MAXIMIZE smallest value    | Maximum value  | MAXIMUM        | YES      |
+----------------------------+----------------+----------------+----------+
```

### **DECISION FLOWCHART** 

Problem says "MINIMIZE ..."?
```
                                                        |
+- YES > You're finding the MINIMUM value                
|        Use: mid = (lo + hi) / 2  (no +1)               
|        Use: if (valid) hi = mid; else lo = mid + 1;    
                                                        |
+- NO > Problem says "MAXIMIZE ..."?                     
                                                        |
    +- YES > You're finding the MAXIMUM value            
             Use: mid = (lo + hi + 1) / 2   (+1)         
             Use: if (valid) lo = mid; else hi = mid - 1;
```

### **COMMON PROBLEMS BY TYPE**

### MINIMIZE THE MAXIMUM (Use MINIMUM pattern, no +1):

Y LC 875: Koko Eating Bananas (minimize max speed)
Y LC 410: Split Array Largest Sum (minimize max sum)
Y LC 1011: Capacity to Ship Packages (minimize max capacity)
Y LC 1482: Minimum Days to Make Bouquets (minimize max days)
Y LC 2064: Minimized Maximum of Products (minimize max products)
Y LC 2187: Minimum Time to Complete Trips (minimize max time)

### MAXIMIZE THE MINIMUM (Use MAXIMUM pattern, +1 needed!):

Y LC 1552: Magnetic Force Between Balls (maximize min distance)
Y LC 1231: Divide Chocolate (maximize min sweetness)
Y LC 2226: Maximum Candies Allocated (maximize min candies)
Y LC 2517: Maximum Tastiness (maximize min difference)
Y LC 2560: House Robber IV (maximize min capability)

### **TEMPLATE 3: `while (l <= r)` - CLASSIC BINARY SEARCH**

USE WHEN: Finding exact element or first/last occurrence

### TEMPLATE - Find Element:

```
int l = 0, r = n - 1;

while (l <= r) {
int mid = l + (r - l) / 2;     

if (arr[mid] == target) {      
    return mid;  // Found it!  
} else if (arr[mid] < target) {
    l = mid + 1;               
} else {                       
    r = mid - 1;               
}                              

}

return -1;  // Not found
```

**KEY POINTS:**
- l <= r (includes equality)
- r = mid - 1 and l = mid + 1 (always ~1)
- Can return -1 if not found

### TEMPLATE - Find First/Last Occurrence:

```
// Find FIRST occurrence (leftmost)
int l = 0, r = n - 1, result = -1;

while (l <= r) {
int mid = l + (r - l) / 2;              

if (arr[mid] == target) {               
    result = mid;                       
    r = mid - 1;  // Keep searching left
} else if (arr[mid] < target) {         
    l = mid + 1;                        
} else {                                
    r = mid - 1;                        
}                                       

}

return result;

// Find LAST occurrence (rightmost)
int l = 0, r = n - 1, result = -1;

while (l <= r) {
int mid = l + (r - l) / 2;               

if (arr[mid] == target) {                
    result = mid;                        
    l = mid + 1;  // Keep searching right
} else if (arr[mid] < target) {          
    l = mid + 1;                         
} else {                                 
    r = mid - 1;                         
}                                        

}

return result;
```

### ** QUICK COMPARISON TABLE**

### Problem Type         Loop        Mid Calc        Updates       Return

Find MINIMUM         l < r       (l+r)/2         r=mid         l or r
```
l=mid+1
```

Find MAXIMUM         l < r       (l+r+1)/2     l=mid         l or r
```
r=mid-1
```

Find Element         l <= r      (l+r)/2         r=mid-1       mid or -1
```
l=mid+1
```

First Occurrence     l <= r      (l+r)/2         Keep l/r      result
Last Occurrence      l <= r      (l+r)/2         Keep l/r      result

### WHY PREFER `l <= r`?

You mentioned preferring `l <= r`. It's valid! Just be careful:

 GOOD for classic binary search (find element)
 GOOD when you need to handle l == r explicitly
 TRICKY for "binary search on answer" (min/max problems)
- You'll need to be very careful with updates
- The `l < r` pattern is cleaner for these

**RECOMMENDATION:**
- Classic BS (find element): Use `l <= r`
- BS on answer (min/max): Use `l < r` (cleaner!)

## **PART 3: BINARY SEARCH PATTERNS**

### **PATTERN 1: CLASSIC BINARY SEARCH**

PROBLEM: Find element in sorted array

**TEMPLATE:**

```cpp
int binarySearch(vector<int>& arr, int target) {
int l = 0, r = arr.size() - 1;         

while (l <= r) {                       
    int mid = l + (r - l) / 2;         

    if (arr[mid] == target) return mid;
    if (arr[mid] < target) l = mid + 1;
    else r = mid - 1;                  
}                                      

return -1;                             

}
```

TIME: O(log N)  |  SPACE: O(1)

## **⚡ HOW TO ESTABLISH BOUNDS (lo, hi) - COMPLETE GUIDE** ⚡

This is THE hardest part! Use these systematic strategies:

### **STRATEGY 1: Think of WORST and BEST Case** 

Ask yourself:
- What's the MINIMUM possible answer? (lo)
- What's the MAXIMUM possible answer? (hi)

Your answer MUST be in [lo, hi], so think of extremes!

### EXAMPLE 1: Koko Eating Bananas

Problem: Minimum eating speed to finish all bananas in h hours
```
piles = [3, 6, 7, 11], h = 8
```

Think: What's the SLOWEST speed that could work?
> Minimum speed = 1 banana/hour (can't be 0!)
> lo = 1 Y

WHY NOT 0? 
If speed = 0, Koko eats 0 bananas per hour
> She'll NEVER finish! (infinite time needed)
> 0 is physically impossible/meaningless
> Smallest valid speed = 1 banana/hour

Think: What's the FASTEST speed we'd ever need?
> If we eat the biggest pile in 1 hour, we're done fastest
> Fastest = max(piles) = 11
> hi = 11 Y

Why not hi = sum(piles)? 
> sum(piles) = 3+6+7+11 = 27
> Would this work? YES! 
> Is it optimal? NO! 

**DETAILED EXPLANATION:**

Option 1: hi = sum(piles) = 27
> Binary search range: [1, 27]
> Iterations: log₂(27) ~ 5 iterations

Option 2: hi = max(piles) = 11
> Binary search range: [1, 11]
> Iterations: log₂(11) ~ 4 iterations

Both give correct answer, but Option 2 is faster!

WHY max(piles) IS ENOUGH:
At speed = max(piles), Koko eats the biggest pile in 1 hour.

Example: piles = [3, 6, 7, 11], h = 8

At speed = 11:
Pile 1: 3/11 = 1 hour  (eats 3, wastes capacity for 8 more)
Pile 2: 6/11 = 1 hour  (eats 6, wastes capacity for 5 more)
Pile 3: 7/11 = 1 hour  (eats 7, wastes capacity for 4 more)
Pile 4: 11/11 = 1 hour (eats 11, perfect!)
Total: 4 hours Y

At speed = 27 (sum):
Same result! 4 hours (even more waste per hour)

Key insight: Eating FASTER than max(piles) doesn't help!
> You still need 1 hour per pile minimum
> Can't eat multiple piles in the same hour
> Extra speed is wasted

WHY sum(piles) WORKS BUT IS WASTEFUL:
It's a valid upper bound (answer is definitely < sum)
But it's unnecessarily large!

Think: If speed = sum = 27, Koko could eat ALL piles in 1 hour...
but the problem doesn't allow that (one pile per hour rule)!

ANSWER: lo = 1, hi = max(piles)  (optimal)
OR: lo = 1, hi = sum(piles)  (works but slower)

### EXAMPLE 2: Split Array Largest Sum

Problem: Split array into k subarrays, minimize largest sum
```
nums = [7, 2, 5, 10, 8], k = 2
```

Think: What's the SMALLEST largest sum possible?
> We must have at least 1 complete element in a subarray
> Smallest largest = max(nums) = 10
> lo = 10 Y

Think: What's the LARGEST largest sum possible?
> Worst case: all elements in 1 subarray
> Largest = sum(nums) = 32
> hi = 32 Y

ANSWER: lo = max(nums), hi = sum(nums)

### EXAMPLE 3: Maximum Candies to K Children

Problem: Maximize candies per child
```
candies = [5, 8, 6], k = 3
```

Think: What's the MINIMUM candies per child?
> If sum < k, answer is 0
> Otherwise, minimum is 1
> lo = 1 Y

Think: What's the MAXIMUM candies per child?
> Best case: give max pile to 1 child
> Maximum = max(candies) = 8
> hi = 8 Y

Why not hi = sum/k?
> That's the average, but we can't always split evenly
> max(candies) is a safe upper bound

ANSWER: lo = 1, hi = max(candies)

### EXAMPLE 4: Kth Smallest in Sorted Matrix

```
matrix = [[1,  5,  9],
      [10, 11, 13],    k = 8
      [12, 13, 15]]         
```

Think: What's the SMALLEST value in matrix?
> Top-left corner = matrix[0][0] = 1
> lo = 1 Y

Think: What's the LARGEST value in matrix?
> Bottom-right corner = matrix[n-1][n-1] = 15
> hi = 15 Y

Key insight: kth smallest MUST be between min and max values!

ANSWER: lo = matrix[0][0], hi = matrix[n-1][n-1]

### EXAMPLE 5: Minimum Time to Complete Trips

```
time = [1, 2, 3], totalTrips = 5
```

Think: What's the MINIMUM time needed?
> At least 1 unit of time
> lo = 1 Y

Think: What's the MAXIMUM time needed?
> Worst case: slowest bus completes all trips
> slowest_bus = max(time) = 3
> Maximum = 3 x 5 = 15

BUT problem says totalTrips can be 10^7 and time[i] can be 10^7
> Worst = 10^7 x 10^7 = 10^14
> hi = 1e14 Y

ANSWER: lo = 1, hi = 1e14 (from constraints!)

### **STRATEGY 2: Pattern-Based Bounds** 

### Problem Type                      lo                    hi

**Speed/Rate Problems**
Eating bananas               1                     max(piles)
Ship packages                max(weights)          sum(weights)
Minimum speed                1                     max_value

**Capacity/Size Problems**
Split array                  max(nums)             sum(nums)
Divide chocolate             min(sweetness)        sum(sweetness)
Allocate books               max(pages)            sum(pages)

**Distance Problems**
Pair distance                0                     max - min
Magnetic force               1                     max_pos - min_pos
K closest                    0                     diff_range

**Time Problems**
Complete trips               1                     slowest x total
Make bouquets                min(bloomDay)         max(bloomDay)
Running computers            0                     sum(batteries)

**Kth in Sorted Structure**
Matrix (sorted)              matrix[0][0]          matrix[n-1][n-1]
Pair products                min_product           max_product
Prime fractions              0.0                   1.0

**Count/Amount Problems**
Maximum candies              1                     max(piles)
Nth magical number           min(a, b)             n x min(a, b)
Kth denomination             1                     k x max(coins)

**Substring/Array Problems**
Repeating substring          0                     n - 1
Duplicate substring          1                     n
Subarray sum                 min_element           sum(array)

### **STRATEGY 3: Mathematical Bounds from Constraints** 

Read problem constraints carefully!

### EXAMPLE: LC 2187 - Minimum Time to Complete Trips

Constraints:
- 1 <= time.length <= 10^5
- 1 <= time[i] <= 10^7
- 1 <= totalTrips <= 10^7

Bounds calculation:
```
lo = 1 (minimum time)
hi = max(time) x totalTrips
```

= 10^7 x 10^7
= 10^14 Y

### EXAMPLE: LC 2040 - Kth Smallest Product

Constraints:
- -10^5 <= nums1[i], nums2[i] <= 10^5

Products range:
- Smallest: -10^5 x 10^5 = -10^10
- Largest:   10^5 x 10^5 =  10^10

ANSWER: lo = -1e10, hi = 1e10

### EXAMPLE: LC 3007 - Maximum Number (Bit Counting)

Constraints:
- 1 <= k <= 10^15

Think: What number has price sum = k?
> Could be very large!
> Safe upper bound = 10^15

ANSWER: lo = 1, hi = 1e15

### **STRATEGY 4: Verify Your Bounds** 

After choosing bounds, verify:

CHECK 1: Is the answer guaranteed to be in [lo, hi]?
> Run through examples
> Check edge cases

CHECK 2: Is lo too small?
> Would lo - 1 be impossible/invalid?
> If yes, lo is correct Y

CHECK 3: Is hi too large?
> Would hi + 1 change the answer?
> If answer can't exceed hi, it's correct Y

### EXAMPLE: Koko Bananas

Chosen: lo = 1, hi = max(piles)

Verify lo = 1:
Y Can't eat 0 bananas/hour (invalid)
Y 1 is minimum valid speed

Verify hi = max(piles):
Y At this speed, we eat biggest pile in 1 hour
Y Going faster doesn't help (still 1 hour per pile)
Y This is the maximum useful speed

BOUNDS VERIFIED! 

### **STRATEGY 5: When Stuck, Use Safe (Wide) Bounds**

If you can't figure out tight bounds, use wider ones!

Binary search still works, just takes a few more iterations.

**SAFE BOUNDS:**

For positive integers:     lo = 1, hi = 1e9 or 1e18
For any integers:          lo = -1e9, hi = 1e9
For array values:          lo = 0, hi = sum(array) x 10
For floats:                lo = 0.0, hi = 1e9

Trade-off:
- Tighter bounds > Fewer iterations
- Wider bounds > Safer but more iterations

Example: log₂(10⁹) ~ 30 iterations (very fast!)

### **COMMON MISTAKES TO AVOID** 

###  MISTAKE 1: Setting lo = 0 when 0 is invalid

Problem: Eating speed (can't be 0!)
```
 lo = 0, hi = max(piles)
 lo = 1, hi = max(piles)
```

WHY 0 IS INVALID:
```
Speed = 0 means eating 0 bananas/hour > never finishes!
```

General rule for RATE/SPEED problems:
- lo = 1 (can't have 0 speed/rate)

For DISTANCE/VALUE problems:
- lo = 0 (0 distance is valid)

**EXAMPLES:**

```
 lo = 1 (0 invalid):
```

- Eating speed (0 = no progress)
- Ship capacity (can't ship with 0 capacity)
- Trips per bus (0 = no trips)
- Candies per child (need at least 1)
- Speed to arrive on time (0 = never arrive)

```
 lo = 0 (0 valid):
```

- Pair distance (0 distance is possible)
- Subarray sum (empty subarray = 0)
- Minimum difference (identical elements = 0)
- Repeating substring length (no repeat = 0)

**QUICK CHECK:**
Ask: "Does value 0 make sense for this problem?"
- If 0 means "no progress" or "impossible" > lo = 1
- If 0 is a valid answer > lo = 0

###  MISTAKE 2: Forgetting about constraints

Problem: Arrays can be huge (10^7 elements)
```
 hi = max_element (too small!)
 hi = constraint_max x constraint_count
```

###  MISTAKE 3: Using sum when max is enough

Problem: Koko bananas
```
 hi = sum(piles) (unnecessarily large!)
 hi = max(piles) (sufficient!)
```

WHY max IS ENOUGH:
Koko eats one pile per hour.
At speed = max(piles), she finishes biggest pile in 1 hour.
Going faster doesn't help! (still 1 hour per pile)

Example: piles = [3, 6, 7, 11], h = 8

Speed 11 (max): Takes 4 hours Y
Speed 27 (sum): Takes 4 hours (same, but searches [1,27] not [1,11])

Binary search iterations:
```
[1, 11]: log₂(11) ~ 4 iterations
[1, 27]: log₂(27) ~ 5 iterations
```

Tighter bound = fewer iterations!

**GENERAL PRINCIPLE:**

Always think: "What's the TIGHTEST upper bound?"

 GOOD (tight bounds):
- Eating speed: max(piles)
- Ship capacity: max(weights) to sum(weights) (need sum!)
- Split array: max(nums) to sum(nums) (need sum!)

 WASTEFUL (loose bounds):
- Eating speed: sum(piles) (works but slow)
- Any problem: hi = 10^18 (usually too large!)

### WHEN TO USE sum vs max:

Use max(array):
- When you process items ONE AT A TIME with max capacity
- Example: Eating bananas (one pile per hour)

Use sum(array):
- When you can GROUP items together
- Example: Ship packages (combine weights in one day)
- Example: Split array (subarrays can have multiple elements)

**RULE OF THUMB:**
If in doubt, use a wider bound. Binary search is fast!
But try to think of the tightest reasonable bound.

### COMPARISON TABLE - max vs sum:

```
+------------------------+--------------+--------------+----------------+
| Problem                | Use max      | Use sum      | Why?           |
+------------------------+--------------+--------------+----------------+
| Koko Bananas           | max(piles) Y | sum(piles)  | One pile/hour   |
| Ship Packages          | max(weights) | sum(weights)Y| Can combine    |
| Split Array            | max(nums)    | sum(nums) Y  | Can group      |
| Divide Chocolate       | min(sweet)   | sum(sweet) Y | Can accumulate |
| Maximum Candies        | max(piles) Y | sum        | Distribute one   |
| Magnetic Force         | 1            | max-min Y    | Distance range |
+------------------------+--------------+--------------+----------------+
```

**KEY INSIGHT:**
Can you COMBINE/GROUP items? > Use sum
Process ONE AT A TIME? > Use max

###  MISTAKE 4: Off-by-one in initialization

Classic binary search:
```
 int lo = 1, hi = n;  // Wrong if 0-indexed!
 int lo = 0, hi = n - 1;  // Correct for 0-indexed array
```

Binary search on answer:
```
 int lo = min_answer, hi = max_answer;  // No -1 needed
```

###  MISTAKE 5: Not handling negative numbers

Problem: Array has negative numbers
```
 lo = 0, hi = max_element
 lo = min_element, hi = max_element
```

Or for products with negatives:
```
 lo = negative_min x negative_min (positive!)
 hi = positive_max x positive_max
```

### **STEP-BY-STEP PROCESS FOR ANY PROBLEM** 

STEP 1: Identify what you're searching for
> Speed? Time? Distance? Value? Count?

STEP 2: Ask: "What's the smallest possible answer?"
> This is your lo
> Consider: Can it be 0? 1? min_element?

STEP 3: Ask: "What's the largest possible answer?"
> This is your hi
> Consider: max_element? sum? constraint_max?

STEP 4: Verify with examples
> Test on given examples
> Check edge cases

STEP 5: If stuck, use safe wide bounds
> lo = 1 or 0, hi = 1e9 or 1e18
> Binary search is fast enough!

STEP 6: Code and test
> If WA, your bounds might be wrong
> Debug: print lo, hi, mid values

### **PRACTICE EXERCISES**

Try determining bounds for these:

1. Problem: Maximum distance between m balls in positions
What are lo and hi?

Answer: lo = 1 (minimum distance)
```
hi = max(positions) - min(positions) (maximum distance)
```

2. Problem: Divide chocolate into k pieces, maximize minimum sweetness
What are lo and hi?

Answer: lo = min(sweetness) (minimum piece value)
```
hi = sum(sweetness) / k (maximum achievable minimum)
```

3. Problem: Kth smallest sum from matrix rows
What are lo and hi?

Answer: lo = sum of first elements (minimum sum)
```
hi = sum of last elements (maximum sum)
```

4. Problem: Find number with k set bits at x-th positions
What are lo and hi?

Answer: lo = 1
```
hi = 1e15 (from constraints)
```

### **ROTATED SORTED ARRAY (LC 33, 81, 153, 154)** 

INSIGHT: One half is ALWAYS sorted!

### SEARCH TARGET (LC 33):

```cpp
int search(vector<int>& nums, int target) {
int l = 0, r = nums.size() - 1;                                  
while (l <= r) {                                                 
    int mid = l + (r - l) / 2;                                   
    if (nums[mid] == target) return mid;                         

    // BS works on sorted array so search for sorted side        

    if (nums[l] <= nums[mid]) {  // Left sorted                  
        if (nums[l] <= target && target < nums[mid]) r = mid - 1;
        else l = mid + 1;                                        
    } else {  // Right sorted                                    
        if (nums[mid] < target && target <= nums[r]) l = mid + 1;
        else r = mid - 1;                                        
    }                                                            
}                                                                
return -1;                                                       

}
```

### FIND MINIMUM (LC 153):

```cpp
int findMin(vector<int>& nums) {
int l = 0, r = nums.size() - 1;                           
while (l < r) {                                           
    int mid = l + (r - l) / 2;                            
    if (nums[mid] > nums[r]) l = mid + 1;  // Min in right
    else r = mid;  // Min in left or at mid               
}                                                         
return nums[l];                                           

}
```

### SEARCH WITH DUPLICATES (LC 81):

```cpp
bool search(vector<int>& nums, int target) {
int l = 0, r = nums.size() - 1;                                  
while (l <= r) {                                                 
    int mid = l + (r - l) / 2;                                   
    if (nums[mid] == target) return true;                        

    // Handle duplicates: can't determine which side is sorted   
    // Example: [1,1,1,2,1] target=2, l=0, r=4, mid=2            
    //          nums[l]=1, nums[mid]=1, nums[r]=1                
    //          Is left sorted? Is right sorted? Can't tell!     
    //          Min could be at index 4 (right) or anywhere      
    if (nums[l] == nums[mid] && nums[mid] == nums[r]) {          
        l++; r--;  // Shrink both ends                           
    }                                                            
    else if (nums[l] <= nums[mid]) {  // Left sorted             
        if (nums[l] <= target && target < nums[mid]) r = mid - 1;
        else l = mid + 1;                                        
    } else {  // Right sorted                                    
        if (nums[mid] < target && target <= nums[r]) l = mid + 1;
        else r = mid - 1;                                        
    }                                                            
}                                                                
return false;                                                    

}
// Time: O(n) worst case (all duplicates), O(log n) average
```

### FIND MINIMUM WITH DUPLICATES (LC 154):

```cpp
int findMin(vector<int>& nums) {
int l = 0, r = nums.size() - 1;                       
while (l < r) {                                       
    int mid = l + (r - l) / 2;                        
    if (nums[mid] > nums[r]) {                        
        l = mid + 1;  // Min in right half            
    } else if (nums[mid] < nums[r]) {                 
        r = mid;      // Min in left half or at mid   
    } else {                                          
        r--;          // Can't determine, shrink right
    }                                                 
}                                                     
return nums[l];                                       

}
// Time: O(n) worst case (all duplicates), O(log n) average
```

**KEY INSIGHT FOR DUPLICATES:**
- When nums[l] == nums[mid] == nums[r], we can't determine which half is sorted
- Solution: Shrink search space by l++ and/or r--
- This degrades to O(n) in worst case but handles all edge cases

### **MEDIAN & KTH ELEMENT OF TWO SORTED ARRAYS (LC 4)** 

PROBLEM: Find median of two sorted arrays in O(log(min(m,n)))

**KEY INSIGHT:**
- Median divides combined array into two equal halves
- Binary search on partition position of SMALLER array
- If we pick i elements from nums1, we need (m+n+1)/2 - i from nums2

**VISUAL:**
nums1: [1, 3, | 8, 9, 15]     i = 2 elements on left
nums2: [7, 11, | 18, 19, 21]  j = 2 elements on left

Left half: [1, 3, 7, 11]  Right half: [8, 9, 15, 18, 19, 21]

Valid partition when: max(left) <= min(right)
- nums1[i-1] <= nums2[j]  (maxLeft1 <= minRight2)
- nums2[j-1] <= nums1[i]  (maxLeft2 <= minRight1)

**KTH ELEMENT OF TWO SORTED ARRAYS:**

CORE IDEA: Binary search on "how many elements to take from each array"
- Take i elements from nums1
- Take j = k - i elements from nums2
- Kth element = max(last element of each part)

VISUAL EXAMPLE - Find 5th element:
```
nums1 = [1, 4, 7, 10, 12]    (m = 5)
nums2 = [2, 3, 6, 15]        (n = 4)
k = 5
```

Try i = 2 (take 2 from nums1, j = 3 from nums2):

nums1: [1, 4 |  7, 10, 12]    maxLeft1 = 4,  minRight1 = 7
nums2: [2, 3, 6 | 15]         maxLeft2 = 6,  minRight2 = 15
<--------->
Left half (5 elements)

Valid? 4 <= 15 Y and 6 <= 7 Y
```
Answer = max(4, 6) = 6 Y
```

**UNDERSTANDING BOUNDS:**
```
lo = max(0, k - n)   > Minimum from nums1 (if nums2 can't provide enough)
hi = min(k, m)       > Maximum from nums1 (can't take more than k or m)
```

Example: k=7, n=4, m=5
```
lo = max(0, 7-4) = 3  (must take at least 3 from nums1)
hi = min(7, 5) = 5    (can take at most 5 from nums1)
```

**WHEN TO ADJUST:**
- maxLeft1 > minRight2 > Take FEWER from nums1 (hi = i - 1)
nums1: [1, 4, 7, 10 | 12]   maxLeft1 = 10 > minRight2 = 6 
nums2: [2, 3 | 6, 15]       Element from left1 > element in right2!

- maxLeft2 > minRight1 > Take MORE from nums1 (lo = i + 1)
nums1: [1 | 4, 7, 10, 12]   minRight1 = 4 < maxLeft2 = 6 
nums2: [2, 3, 6 | 15]       Element from left2 > element in right1!

WHY INT_MIN/INT_MAX?
- i = 0: Taking nothing from nums1 > maxLeft1 = INT_MIN (always valid)
- i = m: Taking everything from nums1 > minRight1 = INT_MAX (always valid)
- Handles edge cases where one array contributes 0 or all elements

**CODE:**
```cpp
int kthElement(vector<int>& nums1, vector<int>& nums2, int k) {
if (nums1.size() > nums2.size())                                   
    return kthElement(nums2, nums1, k);  // Ensure nums1 is smaller

int m = nums1.size(), n = nums2.size();                            

// Binary search bounds for elements taken from nums1              
int lo = max(0, k - n);    // At least k-n from nums1 (if n < k)   
int hi = min(k, m);        // At most k or m elements from nums1   

while (lo <= hi) {                                                 
    int i = lo + (hi - lo) / 2;  // Elements from nums1            
    int j = k - i;                // Elements from nums2           

    // Edge values (use INT_MIN/MAX for boundaries)                
    int maxLeft1 = (i == 0) ? INT_MIN : nums1[i - 1];              
    int minRight1 = (i == m) ? INT_MAX : nums1[i];                 
    int maxLeft2 = (j == 0) ? INT_MIN : nums2[j - 1];              
    int minRight2 = (j == n) ? INT_MAX : nums2[j];                 

    if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {          
        // Valid partition! Kth element is max of left halves      
        return max(maxLeft1, maxLeft2);                            
    }                                                              
    else if (maxLeft1 > minRight2) {                               
        hi = i - 1;  // Too many from nums1, take fewer            
    }                                                              
    else {                                                         
        lo = i + 1;  // Too few from nums1, take more              
    }                                                              
}                                                                  
return -1;  // Should never reach                                  

}
// Time: O(log(min(m, n)))
```

### MEDIAN OF TWO SORTED ARRAYS (LC 4):

Same logic as Kth element, but:
- k = (m + n + 1) / 2  (median position)
- For odd total: return max(maxLeft1, maxLeft2)
- For even total: return (max(left) + min(right)) / 2.0

WHY (m + n + 1) / 2?
- Odd total (5): left gets 3, right gets 2 > median = max(left)
- Even total (6): left gets 3, right gets 3 > median = avg of boundary
- The +1 ensures left half gets extra element for odd case

**CODE:**
```cpp
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
if (nums1.size() > nums2.size())                                           
    return findMedianSortedArrays(nums2, nums1);                           

int m = nums1.size(), n = nums2.size();                                    
int lo = 0, hi = m;                                                        

while (lo <= hi) {                                                         
    int i = lo + (hi - lo) / 2;      // Partition in nums1                 
    int j = (m + n + 1) / 2 - i;     // Partition in nums2                 

    int maxLeft1 = (i == 0) ? INT_MIN : nums1[i - 1];                      
    int minRight1 = (i == m) ? INT_MAX : nums1[i];                         
    int maxLeft2 = (j == 0) ? INT_MIN : nums2[j - 1];                      
    int minRight2 = (j == n) ? INT_MAX : nums2[j];                         

    if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {                  
        // Found valid partition                                           
        if ((m + n) % 2 == 1) {                                            
            return max(maxLeft1, maxLeft2);  // Odd: median is max of left 
        }                                                                  
        return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
    }                                                                      
    else if (maxLeft1 > minRight2) {                                       
        hi = i - 1;                                                        
    }                                                                      
    else {                                                                 
        lo = i + 1;                                                        
    }                                                                      
}                                                                          
return 0.0;                                                                

}
// Time: O(log(min(m, n)))
```

**EXAMPLE WALKTHROUGH:**
```
nums1 = [1, 3], nums2 = [2]
Total = 3 elements, median is 2nd element (k = 2)

m = 2, n = 1, need (2+1+1)/2 = 2 elements in left half

lo = 0, hi = 2
```

Iteration 1: i = 1, j = 2-1 = 1
```
maxLeft1 = nums1[0] = 1
minRight1 = nums1[1] = 3
maxLeft2 = nums2[0] = 2
minRight2 = INT_MAX
```

Check: 1 <= INT_MAX Y and 2 <= 3 Y
Valid! Median = max(1, 2) = 2 Y

WHY (m + n + 1) / 2?
- For odd total: left half gets the extra element
- Median = max(left half)
- For even total: median = (max(left) + min(right)) / 2

### **PATTERN 2: LOWER/UPPER BOUND (STL-style)**

Min value with below condition:
LOWER BOUND: First element >= target
UPPER BOUND: First element > target

### TEMPLATE - Lower Bound:

```cpp
int lowerBound(vector<int>& arr, int target) {
int l = 0, r = arr.size();                         

while (l < r) {                                    
    int mid = l + (r - l) / 2;                     

    if (arr[mid] >= target) {                      
        r = mid;                                   
    } else {                                       
        l = mid + 1;                               
    }                                              
}                                                  

return l;  // First position where arr[i] >= target

}
```

### TEMPLATE - Upper Bound:

```cpp
int upperBound(vector<int>& arr, int target) {
int l = 0, r = arr.size();                        

while (l < r) {                                   
    int mid = l + (r - l) / 2;                    

    if (arr[mid] > target) {                      
        r = mid;                                  
    } else {                                      
        l = mid + 1;                              
    }                                             
}                                                 

return l;  // First position where arr[i] > target

}
```

**KEY INSIGHT:**
- r = arr.size() (NOT size - 1) allows returning "past end"
- Useful for insertion position

### **PATTERN 3: BINARY SEARCH ON ANSWER - MINIMIZE MAXIMUM** 

PROBLEM TYPE: "Find minimum value such that condition is satisfied"

**EXAMPLES:**
- Minimum eating speed (Koko Bananas)
- Minimum capacity to ship packages
- Minimum largest sum when splitting array

**UNIVERSAL TEMPLATE:**

STEP 1: Establish bounds [lo, hi]
STEP 2: Write isValid(mid) or count(mid) function
STEP 3: Binary search

```
int findMinimum() {
int lo = min_possible_value;                      
int hi = max_possible_value;                      

while (lo < hi) {                                 
    int mid = lo + (hi - lo) / 2;  // NO +1       

    if (isValid(mid)) {                           
        hi = mid;        // mid works, try smaller
    } else {                                      
        lo = mid + 1;    // mid fails, need larger
    }                                             
}                                                 

return lo;                                        

}
```

TIME: O(log(hi - lo) x O(isValid))

### **PATTERN 4: BINARY SEARCH ON ANSWER - MAXIMIZE MINIMUM** 

PROBLEM TYPE: "Find maximum value such that condition is satisfied"

**EXAMPLES:**
- Maximum candies per child
- Maximum distance between balls (Magnetic Force)
- Divide chocolate - maximize minimum sweetness

**UNIVERSAL TEMPLATE:**

```
int findMaximum() {
int lo = min_possible_value;                              
int hi = max_possible_value;                              

while (lo < hi) {                                         
    int mid = lo + (hi - lo + 1) / 2;  //  +1 IS CRITICAL!

    if (isValid(mid)) {                                   
        lo = mid;        // mid works, try larger         
    } else {                                              
        hi = mid - 1;    // mid fails, need smaller       
    }                                                     
}                                                         

return lo;                                                

}
```

CRITICAL: The +1 in mid calculation prevents infinite loop!

### **PATTERN 5: KTH SMALLEST/LARGEST** 

PROBLEM TYPE: Find kth smallest element

APPROACH: Binary search on value + count function

**TEMPLATE:**

```
int kthSmallest() {
int lo = minimum_value;                          
int hi = maximum_value;                          

while (lo < hi) {                                
    int mid = lo + (hi - lo) / 2;                

    // Count how many elements are <= mid        
    if (count(mid) >= k) {                       
        hi = mid;        // kth element is <= mid
    } else {                                     
        lo = mid + 1;    // kth element is > mid 
    }                                            
}                                                

return lo;                                       

}
```

**KEY INSIGHT:**
If count(mid) >= k, then kth smallest is somewhere in [lo, mid]
If count(mid) < k, then kth smallest is in [mid+1, hi]

**EXAMPLES:**
- Kth smallest in sorted matrix
- Kth smallest pair distance
- Kth smallest prime fraction

## **PART 4: KEY PROBLEMS WITH SOLUTIONS**

### **PROBLEM: Koko Eating Bananas (LC 875)** 

PROBLEM: Find minimum eating speed K to finish all bananas in H hours

APPROACH: Binary search on speed [1, max(piles)]

**TEMPLATE:**

```cpp
int minEatingSpeed(vector<int>& piles, int h) {
int lo = 1;                                       
int hi = *max_element(piles.begin(), piles.end());

while (lo < hi) {                                 
    int mid = lo + (hi - lo) / 2;                 

    if (canFinish(piles, mid, h)) {               
        hi = mid;        // Can finish, try slower
    } else {                                      
        lo = mid + 1;    // Too slow, need faster 
    }                                             
}                                                 

return lo;                                        

}

bool canFinish(vector<int>& piles, int speed, int h) {
int hours = 0;                                               

for (int pile : piles) {                                     
    hours += (pile + speed - 1) / speed;  // Ceiling division
    if (hours > h) return false;                             
}                                                            

return true;                                                 

}
```

TIME: O(N log(max))  |  SPACE: O(1)

**KEY INSIGHT:**
If speed K works, all speeds > K also work (monotonic!)
Binary search finds minimum K that works.

**CEILING DIVISION TRICK:**
```
ceil(a / b) = (a + b - 1) / b
```

### **PROBLEM: Kth Smallest in Sorted Matrix (LC 378)** 

PROBLEM: nxn matrix with sorted rows and columns. Find kth smallest.

APPROACH: Binary search on value + staircase counting

**TEMPLATE:**

```cpp
int kthSmallest(vector<vector<int>>& matrix, int k) {
int n = matrix.size();                     
int lo = matrix[0][0];                     
int hi = matrix[n-1][n-1];                 

while (lo < hi) {                          
    int mid = lo + (hi - lo) / 2;          

    if (countLessEqual(matrix, mid) >= k) {
        hi = mid;                          
    } else {                               
        lo = mid + 1;                      
    }                                      
}                                          

return lo;                                 

}

// Count elements <= target using staircase method
int countLessEqual(vector<vector<int>>& matrix, int target) {
int n = matrix.size();                                            
int row = 0, col = n - 1;                                         
int count = 0;                                                    

while (row < n && col >= 0) {                                     
    if (matrix[row][col] <= target) {                             
        count += (col + 1);  // All elements in this row up to col
        row++;                                                    
    } else {                                                      
        col--;                                                    
    }                                                             
}                                                                 

return count;                                                     

}
```

TIME: O(N log(max - min))  |  SPACE: O(1)

**BRILLIANT STAIRCASE INSIGHT:**
Start from top-right corner.
If matrix[r][c] <= target: All elements in row r up to col c are <= target
Move down (r++)
If matrix[r][c] > target: Move left (c--)

This counts efficiently without checking every element!

**EXAMPLE:**
[1, 2, 3]
[4, 5, 6]    k = 5
[7, 8, 9]

```
lo=1, hi=9, mid=5
```

Count: Start (0,2)
```
matrix[0][2]=3 <= 5: count += 3, row=1
matrix[1][2]=6 > 5: col=1
matrix[1][1]=5 <= 5: count += 2, row=2
matrix[2][1]=8 > 5: col=0
matrix[2][0]=7 > 5: col=-1, done
```

Total count = 5 >= k, so hi = 5

### **PROBLEM: Kth Smallest Pair Distance (LC 719)**  HARD

PROBLEM: Find kth smallest distance between all pairs

APPROACH: Binary search on distance + sliding window count

**TEMPLATE:**

```cpp
int smallestDistancePair(vector<int>& nums, int k) {
sort(nums.begin(), nums.end());      

int lo = 0;                          
int hi = nums.back() - nums[0];      

while (lo < hi) {                    
    int mid = lo + (hi - lo) / 2;    

    if (countPairs(nums, mid) >= k) {
        hi = mid;                    
    } else {                         
        lo = mid + 1;                
    }                                
}                                    

return lo;                           

}

int countPairs(vector<int>& nums, int distance) {
int count = 0;                                                   
int left = 0;                                                    

for (int right = 0; right < nums.size(); right++) {              
    while (nums[right] - nums[left] > distance) {                
        left++;                                                  
    }                                                            
    count += (right - left);  // All pairs [left..right-1, right]
}                                                                

return count;                                                    

}
```

TIME: O(N log N + N log(max_dist))  |  SPACE: O(1)

**KEY INSIGHT:**
Sort first! Then use sliding window to count pairs efficiently.
For each right, find how many left positions form pairs with distance <= mid.

**EXAMPLE:**
[1,2,3,4,5], k=3

Sorted: [1,2,3,4,5]
```
lo=0, hi=4, mid=2
```

Count pairs with distance <= 2:
```
right=0: no pairs (count=0)
right=1: [0,1] has dist=1 (count=1)
right=2: [0,2] dist=2, [1,2] dist=1 (count=3)
right=3: [1,3] dist=2, [2,3] dist=1 (count=5)
```

...

5 >= 3, so hi = 2

### **PROBLEM: Split Array Largest Sum (LC 410)**  HARD

PROBLEM: Split array into k subarrays, minimize largest sum

APPROACH: Binary search on max sum + greedy validation

**TEMPLATE:**

```cpp
int splitArray(vector<int>& nums, int k) {
int lo = *max_element(nums.begin(), nums.end()); 
int hi = accumulate(nums.begin(), nums.end(), 0);

while (lo < hi) {                                
    int mid = lo + (hi - lo) / 2;                

    if (canSplit(nums, k, mid)) {                
        hi = mid;                                
    } else {                                     
        lo = mid + 1;                            
    }                                            
}                                                

return lo;                                       

}

bool canSplit(vector<int>& nums, int k, int maxSum) {
int subarrays = 1;                      
int currentSum = 0;                     

for (int num : nums) {                  
    if (currentSum + num > maxSum) {    
        subarrays++;                    
        currentSum = num;               
        if (subarrays > k) return false;
    } else {                            
        currentSum += num;              
    }                                   
}                                       

return true;                            

}
```

TIME: O(N log(sum))  |  SPACE: O(1)

**KEY INSIGHT:**
Greedy validation: Process left-to-right, start new subarray when
current sum would exceed maxSum.

If we can split into <= k subarrays with max sum = mid, then mid is valid.

**EXAMPLE:**
[7,2,5,10,8], k=2

```
lo=10 (max element), hi=32 (sum)
mid=21
```

Can split with maxSum=21?
```
currentSum=0
```

Add 7: sum=7
Add 2: sum=9
Add 5: sum=14
Add 10: sum=24 > 21, start new: subarrays=2, sum=10
Add 8: sum=18
Total subarrays=2 <= k Y

So 21 works, try smaller...

### **PROBLEM: Magnetic Force Between Two Balls (LC 1552)** 

PROBLEM: Place m balls in positions, maximize minimum distance

APPROACH: Binary search on distance (MAXIMUM pattern!)

**TEMPLATE:**

```cpp
int maxDistance(vector<int>& position, int m) {
sort(position.begin(), position.end());                          

int lo = 1;                                                      
int hi = position.back() - position[0];                          

while (lo < hi) {                                                
    int mid = lo + (hi - lo + 1) / 2;  //  +1 for maximum!       

    if (canPlace(position, m, mid)) {                            
        lo = mid;        // Can achieve this distance, try larger
    } else {                                                     
        hi = mid - 1;    // Too large, try smaller               
    }                                                            
}                                                                

return lo;                                                       

}

bool canPlace(vector<int>& position, int m, int minDist) {
int count = 1;  // Place first ball        
int lastPos = position[0];                 

for (int i = 1; i < position.size(); i++) {
    if (position[i] - lastPos >= minDist) {
        count++;                           
        lastPos = position[i];             
        if (count >= m) return true;       
    }                                      
}                                          

return count >= m;                         

}
```

TIME: O(N log N + N log(max_pos))  |  SPACE: O(1)

**KEY INSIGHT:**
Greedy placement: Place ball at first valid position.
If we can place all m balls with distance >= mid, try larger distance.

### **PROBLEM: Maximum Candies Allocated to K Children (LC 2226)** 

PROBLEM: Distribute candies to k children, maximize candies per child

APPROACH: Binary search on candies per child (MAXIMUM pattern!)

**TEMPLATE:**

```cpp
int maximumCandies(vector<int>& candies, long long k) {
long long sum = accumulate(candies.begin(), candies.end(), 0LL);
if (sum < k) return 0;                                          

long long lo = 1;                                               
long long hi = *max_element(candies.begin(), candies.end());    

while (lo < hi) {                                               
    long long mid = lo + (hi - lo + 1) / 2;  //  +1             

    if (canDistribute(candies, k, mid)) {                       
        lo = mid;                                               
    } else {                                                    
        hi = mid - 1;                                           
    }                                                           
}                                                               

return lo;                                                      

}

bool canDistribute(vector<int>& candies, long long k, long long perChild) {
long long children = 0;            

for (int pile : candies) {         
    children += pile / perChild;   
    if (children >= k) return true;
}                                  

return children >= k;              

}
```

TIME: O(N log(max))  |  SPACE: O(1)

**KEY INSIGHT:**
Each pile can be split into pile/x portions of size x.
If total portions >= k, we can give x candies to k children.

### **PROBLEM: Minimum Time to Complete Trips (LC 2187)** 

PROBLEM: Minimum time for buses to complete totalTrips trips

APPROACH: Binary search on time

**TEMPLATE:**

```cpp
long long minimumTime(vector<int>& time, int totalTrips) {
long long lo = 1;                             
long long hi = 1e14;  // max_time x totalTrips

while (lo < hi) {                             
    long long mid = lo + (hi - lo) / 2;       

    if (countTrips(time, mid) >= totalTrips) {
        hi = mid;                             
    } else {                                  
        lo = mid + 1;                         
    }                                         
}                                             

return lo;                                    

}

long long countTrips(vector<int>& time, long long maxTime) {
long long trips = 0;     

for (int t : time) {     
    trips += maxTime / t;
}                        

return trips;            

}
```

TIME: O(N log(10^14))  |  SPACE: O(1)

**KEY INSIGHT:**
In time T, bus with time[i] can complete T/time[i] trips.
Sum across all buses gives total trips possible in time T.

**BOUNDS DERIVATION:**
```
lo = 1 (minimum time)
hi = slowest_bus x totalTrips = 10^7 x 10^7 = 10^14
```

### **PROBLEM: Kth Smallest Subarray Sum (LC 1918)**  HARD

PROBLEM: Find kth smallest sum among all subarrays

APPROACH: Binary search on sum + sliding window count

**TEMPLATE:**

```cpp
int kthSmallestSubarraySum(vector<int>& nums, int k) {
int lo = *min_element(nums.begin(), nums.end());  // Min subarray (size 1)
int hi = accumulate(nums.begin(), nums.end(), 0);  // Max subarray (all)  

while (lo < hi) {                                                         
    int mid = lo + (hi - lo) / 2;                                         

    if (countSubarrays(nums, mid) >= k) {                                 
        hi = mid;                                                         
    } else {                                                              
        lo = mid + 1;                                                     
    }                                                                     
}                                                                         

return lo;                                                                

}

int countSubarrays(vector<int>& nums, int maxSum) {
int count = 0, sum = 0, left = 0;                                 

for (int right = 0; right < nums.size(); right++) {               
    sum += nums[right];                                           

    while (sum > maxSum) {                                        
        sum -= nums[left++];                                      
    }                                                             

    count += (right - left + 1);  // All subarrays ending at right
}                                                                 

return count;                                                     

}
```

TIME: O(N log(sum))  |  SPACE: O(1)

**KEY INSIGHT:**
Use sliding window to count subarrays with sum <= target.
For window [left, right], all subarrays ending at right are valid:
[left,right], [left+1,right], ..., [right,right] = (right-left+1) subarrays

**BRILLIANT TRICK:**
The count function counts "at most maxSum", which naturally fits
binary search for kth smallest!

**EXAMPLE WALKTHROUGH:**
```
nums = [1, 2, 3, 4, 5], k = 5
```

All subarrays: [1], [2], [3], [4], [5], [1,2], [2,3], [3,4], [4,5],
```
             [1,2,3], [2,3,4], [3,4,5], [1,2,3,4], [2,3,4,5], [1,2,3,4,5]
```

Sums: 1, 2, 3, 4, 5, 3, 5, 7, 9, 6, 9, 12, 10, 14, 15
Sorted: 1, 2, 3, 3, 4, 5, 5, 6, 7, 9, 9, 10, 12, 14, 15
5th smallest = 4

Binary search:
```
lo=1, hi=15, mid=8
```

Count subarrays with sum <= 8: Using sliding window = 9
9 >= 5, so hi = 8

Continue until finding answer = 4

### **PROBLEM: Longest Repeating Substring (LC 1062)**

PROBLEM: Find length of longest repeating substring

APPROACH: Binary search on length

**TEMPLATE:**

```
int longestRepeatingSubstring(string s) {
int lo = 0;                                             
int hi = s.size() - 1;                                  

while (lo < hi) {                                       
    int mid = lo + (hi - lo + 1) / 2;  // +1 for maximum

    if (hasRepeating(s, mid)) {                         
        lo = mid;                                       
    } else {                                            
        hi = mid - 1;                                   
    }                                                   
}                                                       

return lo;                                              

}

bool hasRepeating(string& s, int len) {
unordered_set<string> seen;                

for (int i = 0; i <= s.size() - len; i++) {
    string sub = s.substr(i, len);         
    if (seen.count(sub)) return true;      
    seen.insert(sub);                      
}                                          

return false;                              

}
```

TIME: O(N2 log N)  |  SPACE: O(N2)

**KEY INSIGHT:**
If length L has repeating substring, all lengths < L also have.
Binary search on length, find maximum L that works.

**BOUNDS:**
```
lo = 0 (no repeating substring)
hi = n-1 (e.g., "aaaa" has "aaa" repeating, length n-1)
```

**OPTIMIZATION:**
Use rolling hash to reduce time to O(N log2 N)

### **PROBLEM: Longest Duplicate Substring (LC 1044)**  HARD

PROBLEM: Find longest duplicate substring (return the string!)

APPROACH: Binary search + rolling hash (Rabin-Karp)

**ROLLING HASH FORMULA:**
```
hash = (c₀ x p⁰ + c₁ x p¹ + c₂ x p2 + ...) mod M
```

where p = 31, M = 10⁹+7

**TEMPLATE:**

```cpp
string longestDupSubstring(string s) {
int l = 1, h = s.size();              
string ans = "";                      

while (l <= h) {                      
    int mid = l + (h - l) / 2;        
    string dup = getDupString(s, mid);

    if (!dup.empty()) {               
        ans = dup;                    
        l = mid + 1;                  
    } else {                          
        h = mid - 1;                  
    }                                 
}                                     

return ans;                           

}

string getDupString(string& s, int len) {
long long MOD = 1e9 + 7;                                    
long long p = 31;                                           
long long pow = 1;                                          
long long hash = 0;                                         

// Calculate hash for first window                          
for (int i = len - 1; i >= 0; i--) {                        
    hash = (hash + (s[i] - 'a' + 1) * pow) % MOD;           
    if (i > 0) pow = (pow * p) % MOD;                       
}                                                           

unordered_map<long long, vector<int>> hashMap;              
hashMap[hash].push_back(0);                                 

// Rolling hash for remaining windows                       
for (int start = 1; start + len - 1 < s.size(); start++) {  
    // Remove first char of previous window                 
    long long remove = (pow * (s[start-1] - 'a' + 1)) % MOD;
    hash = (hash - remove + MOD) % MOD;                     

    // Shift and add new char                               
    hash = (hash * p) % MOD;                                
    hash = (hash + (s[start + len - 1] - 'a' + 1)) % MOD;   

    // Check for collision (hash match)                     
    if (hashMap.count(hash)) {                              
        string current = s.substr(start, len);              
        for (int idx : hashMap[hash]) {                     
            if (s.substr(idx, len) == current) {            
                return current;                             
            }                                               
        }                                                   
    }                                                       

    hashMap[hash].push_back(start);                         
}                                                           

return "";                                                  

}
```

TIME: O(N log N)  |  SPACE: O(N)

**ROLLING HASH INSIGHT:**
Instead of recalculating hash for each substring:
1. Remove leftmost character
2. Shift remaining hash (multiply by base)
3. Add new rightmost character

This reduces substring comparison from O(N2) to O(N)!

**WHY STORE INDICES IN MAP:**
Hash collisions possible! When hashes match, verify actual strings.

### **PROBLEM: Find K Closest Elements (LC 658)**

PROBLEM: Find k closest elements to x in sorted array

APPROACH: Binary search for closest + expand window

**TEMPLATE:**

```cpp
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
int n = arr.size();                                             

// Binary search for element >= x                               
int left = 0, right = n - 1;                                    
while (left < right) {                                          
    int mid = left + (right - left) / 2;                        
    if (arr[mid] >= x) {                                        
        right = mid;                                            
    } else {                                                    
        left = mid + 1;                                         
    }                                                           
}                                                               

// Expand window from closest position                          
left = left - 1;                                                
right = left + 1;                                               

while (right - left - 1 != k) {                                 
    if (left < 0) {                                             
        right++;                                                
    } else if (right == n) {                                    
        left--;                                                 
    } else if (abs(arr[left] - x) <= abs(arr[right] - x)) {     
        left--;                                                 
    } else {                                                    
        right++;                                                
    }                                                           
}                                                               

// Result is [left+1, right-1]                                  
return vector<int>(arr.begin() + left + 1, arr.begin() + right);

}
```

TIME: O(log N + K)  |  SPACE: O(1)

**KEY INSIGHT:**
Two-pointer expansion from closest element!
Compare distances and expand toward closer element.

### **PROBLEM: Minimize Max Difference of Pairs (LC 2616)** 

PROBLEM: Form p pairs, minimize maximum difference in any pair

APPROACH: Binary search on maximum difference

**TEMPLATE:**

```cpp
int minimizeMax(vector<int>& nums, int p) {
if (p == 0) return 0;                

sort(nums.begin(), nums.end());      

int lo = 0;                          
int hi = nums.back() - nums[0];      

while (lo < hi) {                    
    int mid = lo + (hi - lo) / 2;    

    if (canFormPairs(nums, p, mid)) {
        hi = mid;                    
    } else {                         
        lo = mid + 1;                
    }                                
}                                    

return lo;                           

}

bool canFormPairs(vector<int>& nums, int p, int maxDiff) {
int count = 0;                                
int i = 0;                                    

while (i < nums.size() - 1) {                 
    if (nums[i+1] - nums[i] <= maxDiff) {     
        count++;                              
        i += 2;  // Skip both elements in pair
        if (count >= p) return true;          
    } else {                                  
        i++;                                  
    }                                         
}                                             

return count >= p;                            

}
```

TIME: O(N log N + N log(max_diff))  |  SPACE: O(1)

**KEY INSIGHT:**
Greedy pairing: If consecutive elements have difference <= maxDiff,
pair them immediately (skip both).

This maximizes number of pairs we can form.

**WHY GREEDY WORKS:**
Once we pair (i, i+1), both are used. By pairing greedily from left,
we maximize count without conflicts.

### **PROBLEM: Capacity to Ship Packages (LC 1011)**

PROBLEM: Ship packages in D days, minimize capacity

APPROACH: Binary search on capacity

**TEMPLATE:**

```cpp
int shipWithinDays(vector<int>& weights, int days) {
int lo = *max_element(weights.begin(), weights.end()); 
int hi = accumulate(weights.begin(), weights.end(), 0);

while (lo < hi) {                                      
    int mid = lo + (hi - lo) / 2;                      

    if (canShip(weights, days, mid)) {                 
        hi = mid;                                      
    } else {                                           
        lo = mid + 1;                                  
    }                                                  
}                                                      

return lo;                                             

}

bool canShip(vector<int>& weights, int days, int capacity) {
int daysNeeded = 1;                         
int currentWeight = 0;                      

for (int weight : weights) {                
    if (currentWeight + weight > capacity) {
        daysNeeded++;                       
        currentWeight = weight;             
        if (daysNeeded > days) return false;
    } else {                                
        currentWeight += weight;            
    }                                       
}                                           

return true;                                

}
```

TIME: O(N log(sum))  |  SPACE: O(1)

**KEY INSIGHT:**
Same pattern as Split Array! Greedy assignment to days.

**SIMILAR PROBLEMS:**
- Split Array Largest Sum
- Divide Chocolate
- Minimize Maximum of Products

### **PROBLEM: Minimum Days to Make m Bouquets (LC 1482)**

PROBLEM: Wait for flowers to bloom, make m bouquets of k adjacent flowers

APPROACH: Binary search on days

**TEMPLATE:**

```cpp
int minDays(vector<int>& bloomDay, int m, int k) {
int n = bloomDay.size();                                
if ((long long)m * k > n) return -1;                    

int lo = *min_element(bloomDay.begin(), bloomDay.end());
int hi = *max_element(bloomDay.begin(), bloomDay.end());

while (lo < hi) {                                       
    int mid = lo + (hi - lo) / 2;                       

    if (canMake(bloomDay, m, k, mid)) {                 
        hi = mid;                                       
    } else {                                            
        lo = mid + 1;                                   
    }                                                   
}                                                       

return lo;                                              

}

bool canMake(vector<int>& bloomDay, int m, int k, int day) {
int bouquets = 0;                              
int flowers = 0;                               

for (int bloom : bloomDay) {                   
    if (bloom <= day) {                        
        flowers++;                             
        if (flowers == k) {                    
            bouquets++;                        
            flowers = 0;                       
            if (bouquets >= m) return true;    
        }                                      
    } else {                                   
        flowers = 0;  // Reset (need adjacent!)
    }                                          
}                                              

return bouquets >= m;                          

}
```

TIME: O(N log(max))  |  SPACE: O(1)

**KEY INSIGHT:**
Count consecutive bloomed flowers. Every k consecutive makes 1 bouquet.
Reset count when encounter non-bloomed flower (adjacency requirement).

### **PROBLEM: Divide Chocolate (LC 1231)**  HARD

PROBLEM: Divide chocolate into k+1 pieces, maximize minimum sweetness

APPROACH: Binary search on minimum sweetness (MAXIMUM pattern!)

**TEMPLATE:**

```cpp
int maximizeSweetness(vector<int>& sweetness, int k) {
k++;  // k friends + you = k+1 people total                

int lo = *min_element(sweetness.begin(), sweetness.end()); 
int hi = accumulate(sweetness.begin(), sweetness.end(), 0);

while (lo < hi) {                                          
    int mid = lo + (hi - lo + 1) / 2;  // +1 for maximum!  

    if (canDivide(sweetness, k, mid)) {                    
        lo = mid;                                          
    } else {                                               
        hi = mid - 1;                                      
    }                                                      
}                                                          

return lo;                                                 

}

bool canDivide(vector<int>& sweetness, int k, int minSweet) {
int pieces = 0;                      
int currentSum = 0;                  

for (int sweet : sweetness) {        
    currentSum += sweet;             

    if (currentSum >= minSweet) {    
        pieces++;                    
        currentSum = 0;              
        if (pieces >= k) return true;
    }                                
}                                    

return pieces >= k;                  

}
```

TIME: O(N log(sum))  |  SPACE: O(1)

**KEY INSIGHT:**
Greedy cutting: As soon as accumulated sweetness >= minSweet, cut!
This maximizes number of pieces we can make.

**BOUNDS EXPLANATION:**
```
lo = min(sweetness): Each piece has at least 1 chunk
hi = sum(sweetness): Worst case, 1 person gets everything
```

**EXAMPLE:**
```
sweetness = [1,2,3,4,5,6,7,8,9], k = 5 (6 people total)

lo = 1, hi = 45
mid = 23
```

Can we give everyone >= 23 sweetness?
Accumulate: 1+2+3+4+5+6+7 = 28 >= 23 Y (piece 1)
8+9 = 17 < 23 X (can't make piece 2)

Only 1 piece, need 6, so mid = 23 fails

Try mid = 7:
1+2+3+4 = 10 >= 7 Y
5+6 = 11 >= 7 Y
7 >= 7 Y
8 >= 7 Y
9 >= 7 Y
Total 5 pieces, need 6... try mid = 5

Eventually converge to answer!

### **PROBLEM: Maximum Number (Bit Counting) (LC 3007)**  HARD

PROBLEM: Find max number where sum of "prices" of bits <= k

**BRILLIANT BIT PATTERN INSIGHT:**
Write 0-7 in binary and observe column patterns:

Bit>  2  1  0
0     0  0  0
1     0  0  1
2     0  1  0
3     0  1  1
4     1  0  0
5     1  0  1
6     1  1  0
7     1  1  1

Pattern in column i:
- Group size = 2^i
- Each group has 2^(i-1) zeros, then 2^(i-1) ones
- Repeats!

COUNT SET BITS IN COLUMN i FOR NUMBERS [0, n]:
Complete groups: (n+1) / group_size x 2^(i-1)
Remainder: max(0, (n+1) % group_size - 2^(i-1))

**TEMPLATE:**

```
long long findMaximumNumber(long long k, int x) {
long long left = 1, right = 1e15;                             

while (left < right) {                                        
    long long mid = (left + right + 1) / 2;  // +1 for maximum

    if (countBits(mid, x) <= k) {                             
        left = mid;                                           
    } else {                                                  
        right = mid - 1;                                      
    }                                                         
}                                                             

return left;                                                  

}

long long countBits(long long n, int x) {
long long bits = log2(n) + 1;                       
long long count = 0;                                
n++;  // Count from 0 to n inclusive                

// Check every x-th column (x, 2x, 3x, ...)         
for (long long i = x; i <= bits; i += x) {          
    long long group = 1LL << i;                     

    // Complete groups                              
    count += (n / group) * (1LL << (i-1));          

    // Remainder                                    
    count += max(0LL, (n % group) - (1LL << (i-1)));
}                                                   

return count;                                       

}
```

TIME: O(log N x log N)  |  SPACE: O(1)

**MATHEMATICAL INSIGHT:**
Group size for bit position i = 2^i
First half (2^(i-1)) are 0s, second half are 1s

Example: Column 2 (group size 4 = 22)
0011 0011 0011 ... (pattern repeats)

### **PROBLEM: Minimum Work Sessions (LC 1986)**  HARD

PROBLEM: Minimum sessions to complete all tasks with time limit

APPROACH: Binary search on sessions + backtracking validation

**TEMPLATE:**

```cpp
int minSessions(vector<int>& tasks, int sessionTime) {
sort(tasks.rbegin(), tasks.rend());  // Sort descending (optimization)

int lo = 1;                                                           
int hi = tasks.size();                                                

while (lo < hi) {                                                     
    int mid = lo + (hi - lo) / 2;                                     

    vector<int> sessions(mid, 0);                                     
    if (canFinish(0, tasks, sessions, sessionTime)) {                 
        hi = mid;                                                     
    } else {                                                          
        lo = mid + 1;                                                 
    }                                                                 
}                                                                     

return lo;                                                            

}

bool canFinish(int idx, vector<int>& tasks, vector<int>& sessions, int limit) {
if (idx == tasks.size()) return true;                            

for (int i = 0; i < sessions.size(); i++) {                      
    if (sessions[i] + tasks[idx] <= limit) {                     
        sessions[i] += tasks[idx];                               

        if (canFinish(idx + 1, tasks, sessions, limit)) {        
            return true;                                         
        }                                                        

        sessions[i] -= tasks[idx];                               

        // Prune: If session was empty, skip other empty sessions
        if (sessions[i] == 0) return false;                      
    }                                                            
}                                                                

return false;                                                    

}
```

TIME: O(log N x N!)  |  SPACE: O(N)

**PRUNING OPTIMIZATION:**
If we can't fit task in empty session, other empty sessions won't work either!
This drastically reduces backtracking branches.

WHY SORT DESCENDING?
Place larger tasks first > better pruning > faster!

### **PROBLEM: Kth Smallest Product (LC 2040)**  HARD

PROBLEM: Kth smallest product from two sorted arrays (with negatives!)

TRICKY PART: Negative numbers make ordering complex

**KEY INSIGHT:**
Split arrays into positive and negative parts.
Keep reversed copies for easier counting.

WHY REVERSE?
For negative arrays: kth smallest is (n-k+1)th from end.
Reversing makes counting consistent!

**COUNTING STRATEGY:**
If guess >= 0:
```
count = pos1xpos2 + neg1_revxneg2_rev +
```

neg1.size()xpos2.size() + pos1.size()xneg2.size()

If guess < 0:
```
count = pos1_revxneg2 + neg1xpos2_rev
```

**TEMPLATE:**

```cpp
long long kthSmallestProduct(vector<int>& n1, vector<int>& n2, long long k) {
// Split into positive and negative                    
auto it1 = lower_bound(n1.begin(), n1.end(), 0);       
vector<int> neg1(n1.begin(), it1), pos1(it1, n1.end());

auto it2 = lower_bound(n2.begin(), n2.end(), 0);       
vector<int> neg2(n2.begin(), it2), pos2(it2, n2.end());

// Reversed copies                                     
vector<int> neg1_r(neg1.rbegin(), neg1.rend());        
vector<int> neg2_r(neg2.rbegin(), neg2.rend());        
vector<int> pos1_r(pos1.rbegin(), pos1.rend());        
vector<int> pos2_r(pos2.rbegin(), pos2.rend());        

long long lo = -1e10, hi = 1e10;                       

while (lo < hi) {                                      
    long long mid = lo + (hi - lo) / 2;                

    long long cnt;                                     
    if (mid >= 0) {                                    
        cnt = countProducts(pos1, pos2, mid)         +
              countProducts(neg1_r, neg2_r, mid)      +
              (long long)neg1.size() * pos2.size()   +
              (long long)pos1.size() * neg2.size();    
    } else {                                           
        cnt = countProducts(pos1_r, neg2, mid)       +
              countProducts(neg1, pos2_r, mid);        
    }                                                  

    if (cnt >= k) {                                    
        hi = mid;                                      
    } else {                                           
        lo = mid + 1;                                  
    }                                                  
}                                                      

return lo;                                             

}

long long countProducts(vector<int>& A, vector<int>& B, long long target) {
long long count = 0;                                   
int j = B.size() - 1;                                  

for (int i = 0; i < A.size(); i++) {                   
    while (j >= 0 && (long long)A[i] * B[j] > target) {
        j--;                                           
    }                                                  
    count += (j + 1);                                  
}                                                      

return count;                                          

}
```

TIME: O(N log(range))  |  SPACE: O(N)

**BRILLIANT HANDLING OF NEGATIVES:**
By splitting and reversing, we maintain monotonicity for counting!

## **PART 5: DEEP DIVE - `l < r` vs `l <= r`**  CRITICAL!

### **WHY THIS MATTERS**

This is the #1 source of bugs in binary search!

**THE CONFUSION:**
- Both can work for many problems
- But you must match loop condition with update logic
- Wrong combination > infinite loop or wrong answer!

### **APPROACH 1: `while (l < r)` - CLEANER FOR BINARY SEARCH ON ANSWER**

**ADVANTAGES:**
 No need to track result separately
 Automatically converges to answer
 Cleaner code
 Less error-prone for min/max problems

**WHEN LOOP EXITS:**
```
l == r (they meet at the answer)
```

### EXAMPLE - Find Minimum:

[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  Find minimum value >= 7

```
lo=1, hi=10
```

Iteration 1: mid=5, arr[5]=6 < 7, lo=6
Iteration 2: lo=6, hi=10, mid=8, arr[8]=9 >= 7, hi=8
Iteration 3: lo=6, hi=8, mid=7, arr[7]=8 >= 7, hi=7
Iteration 4: lo=6, hi=7, mid=6, arr[6]=7 >= 7, hi=6
Now lo==hi==6, exit, return 6 (which is index of 7) Y

### EXAMPLE - Find Maximum (with +1):

Find maximum value <= 7

```
lo=1, hi=10
```

Iteration 1: mid=(1+10+1)/2=6, arr[6]=7 <= 7, lo=6
Iteration 2: lo=6, hi=10, mid=(6+10+1)/2=8, arr[8]=9 > 7, hi=7
Iteration 3: lo=6, hi=7, mid=(6+7+1)/2=7, arr[7]=8 > 7, hi=6
Now lo==hi==6, exit, return 6 Y

Without +1, at iteration 2:
```
mid=(6+10)/2=8... (same as above)
```

At iteration 3: lo=6, hi=7, mid=(6+7)/2=6, arr[6]=7 <= 7, lo=6
> INFINITE LOOP! (lo and hi don't change)

### **APPROACH 2: `while (l <= r)` - BETTER FOR CLASSIC BINARY SEARCH**

**ADVANTAGES:**
 Familiar pattern (most tutorials use this)
 Natural for finding exact element
 Can return -1 if not found
 Works well with result variable

**WHEN TO USE:**
- Classic binary search (find element)
- Need to return -1 if not found
- First/last occurrence with result tracking

### EXAMPLE - Find Element:

[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]  Find 7

```
lo=0, hi=9
```

Iteration 1: mid=4, arr[4]=5 < 7, lo=5
Iteration 2: lo=5, hi=9, mid=7, arr[7]=8 > 7, hi=6
Iteration 3: lo=5, hi=6, mid=5, arr[5]=6 < 7, lo=6
Iteration 4: lo=6, hi=6, mid=6, arr[6]=7 == 7, return 6 Y

### **UNIFIED MENTAL MODEL** 

**THINK OF IT AS TWO INVARIANTS:**

**INVARIANT FOR MINIMUM PROBLEMS:**
[false, false, ..., false, TRUE, true, true, ...]
^
Find this position

lo always points to "could be false"
hi always points to "definitely true or could be true"
Converge to first TRUE

**INVARIANT FOR MAXIMUM PROBLEMS:**
[true, true, TRUE, false, false, ...]
^
Find this position

lo always points to "definitely true or could be true"
hi always points to "could be false"
Converge to last TRUE

**GOLDEN RULE SUMMARY:**

1. For MINIMUM (find first TRUE):
```
while (lo < hi) {
   mid = (lo + hi) / 2;                              
   if (isTrue(mid)) hi = mid;  // Mid might be answer
   else lo = mid + 1;                                

}
```

2. For MAXIMUM (find last TRUE):
```
while (lo < hi) {
   mid = (lo + hi + 1) / 2;  // +1 critical!         
   if (isTrue(mid)) lo = mid;  // Mid might be answer
   else hi = mid - 1;                                

}
```

3. For EXACT MATCH:
```
while (lo <= hi) {
   mid = (lo + hi) / 2;                
   if (arr[mid] == target) return mid; 
   if (arr[mid] < target) lo = mid + 1;
   else hi = mid - 1;                  

}
```

## **PART 6: WRITING isValid() METHODS - COMPLETE GUIDE** 

### **THE KEY INSIGHT**

The isValid(mid) function answers: "Can we achieve the target with constraint = mid?"

**GENERIC STRUCTURE:**

```
bool isValid(int mid) {
// Use GREEDY approach to check feasibility
// Simulate the process with constraint = mid
// Return true if we can satisfy all requirements

}
```

### **PATTERN 1: GREEDY SIMULATION (Most Common)**

PROBLEM TYPE: "Can we complete task with capacity/speed/time = mid?"

**TEMPLATE:**

```cpp
bool canFinish(vector<int>& tasks, int capacity) {
int count = 0;  // or time, or groups, etc.                        

for (int task : tasks) {                                           
    count += (task + capacity - 1) / capacity;  // ceiling division
    // OR: count += task / capacity + (task % capacity != 0);      
}                                                                  

return count <= limit;  // Can we finish within limit?             

}
```

**EXAMPLES:**

1. KOKO EATING BANANAS (LC 875):
"Can Koko eat all bananas with speed = mid in h hours?"

```cpp
bool canEat(vector<int>& piles, int speed, int h) {
   int hours = 0;                                               
   for (int pile : piles) {                                     
       hours += (pile + speed - 1) / speed;  // ceil(pile/speed)
   }                                                            
   return hours <= h;                                           

}
```

2. SHIP PACKAGES (LC 1011):
"Can we ship all packages with capacity = mid in D days?"

```cpp
bool canShip(vector<int>& weights, int capacity, int days) {
   int dayCount = 1, currentLoad = 0;   
   for (int w : weights) {              
       if (currentLoad + w > capacity) {
           dayCount++;                  
           currentLoad = 0;             
       }                                
       currentLoad += w;                
   }                                    
   return dayCount <= days;             

}
```

3. SPLIT ARRAY LARGEST SUM (LC 410):
"Can we split into k subarrays with max sum <= mid?"

```cpp
bool canSplit(vector<int>& nums, int maxSum, int k) {
   int splits = 1, currentSum = 0;     
   for (int num : nums) {              
       if (currentSum + num > maxSum) {
           splits++;                   
           currentSum = 0;             
       }                               
       currentSum += num;              
   }                                   
   return splits <= k;                 

}
```

### **PATTERN 2: GREEDY ASSIGNMENT**

PROBLEM TYPE: "Can we assign items with minimum gap/distance = mid?"

**TEMPLATE:**

```cpp
bool canPlace(vector<int>& positions, int minDist, int count) {
int placed = 1;                             
int lastPos = positions[0];                 

for (int i = 1; i < positions.size(); i++) {
    if (positions[i] - lastPos >= minDist) {
        placed++;                           
        lastPos = positions[i];             
    }                                       
}                                           

return placed >= count;                     

}
```

**EXAMPLES:**

1. MAGNETIC FORCE (LC 1552):
"Can we place m balls with minimum distance = mid?"

```cpp
sort(positions);  // IMPORTANT: Sort first!

bool canPlace(vector<int>& pos, int minDist, int m) {
   int balls = 1, lastPos = pos[0];      
   for (int i = 1; i < pos.size(); i++) {
       if (pos[i] - lastPos >= minDist) {
           balls++;                      
           lastPos = pos[i];             
           if (balls >= m) return true;  
       }                                 
   }                                     
   return false;                         

}
```

2. AGGRESSIVE COWS (Classic):
Same as magnetic force - maximize minimum distance

### **PATTERN 3: COUNTING (For Kth Element Problems)**

PROBLEM TYPE: "How many elements/pairs are <= mid?"

Instead of isValid, we use count(mid) >= k

**TEMPLATE:**

```
int countLessOrEqual(int mid) {
int count = 0;                                  
// Count how many elements/pairs/sums are <= mid
return count;                                   

}

// Binary search becomes:
if (count(mid) >= k) hi = mid;
else lo = mid + 1;
```

**EXAMPLES:**

1. KTH SMALLEST IN SORTED MATRIX (LC 378):
"Count elements <= mid using staircase"

```cpp
int count(vector<vector<int>>& matrix, int mid) {
   int n = matrix.size(), count = 0;                           
   int row = n - 1, col = 0;  // Start bottom-left             

   while (row >= 0 && col < n) {                               
       if (matrix[row][col] <= mid) {                          
           count += row + 1;  // All elements above are smaller
           col++;                                              
       } else {                                                
           row--;                                              
       }                                                       
   }                                                           
   return count;                                               

}
```

2. KTH SMALLEST PAIR DISTANCE (LC 719):
"Count pairs with distance <= mid using sliding window"

```cpp
sort(nums);  // IMPORTANT!

int count(vector<int>& nums, int mid) {
   int count = 0, left = 0;                                       
   for (int right = 0; right < nums.size(); right++) {            
       while (nums[right] - nums[left] > mid) left++;             
       count += right - left;  // All pairs (left..right-1, right)
   }                                                              
   return count;                                                  

}
```

### **PATTERN 4: MATHEMATICAL FORMULA**

PROBLEM TYPE: Can compute answer directly with formula

**EXAMPLES:**

1. NTH MAGICAL NUMBER (LC 878):
```
count(x) = x/a + x/b - x/lcm(a,b)   // Inclusion-Exclusion
```

2. RUNNING N COMPUTERS (LC 2141):
```
canRun(time) = sum(min(battery[i], time)) >= n * time
```

3. MINIMIZED MAXIMUM (LC 2064):
```
canDistribute(max) = sum(ceil(quantities[i]/max)) <= n
```

### **HOW TO IDENTIFY THE RIGHT PATTERN**

```
+-------------------------------------+------------------------------------+
| Problem Keywords                    | isValid Pattern                    |
+-------------------------------------+------------------------------------+
| "minimum time/speed to finish"      | Greedy Simulation (ceiling div)    |
| "split into k parts"                | Greedy Simulation (count splits)   |
| "ship in D days"                    | Greedy Simulation (count days)     |
| "place k items with min distance"   | Greedy Assignment (sort + place)   |
| "kth smallest element/pair"         | Counting (return count >= k)       |
| "kth multiple of A or B"            | Mathematical (inclusion-exclusion) |
| "run n computers for time T"        | Mathematical (sum formula)         |
+-------------------------------------+------------------------------------+
```

### **COMMON MISTAKES IN isValid()**

 MISTAKE 1: Forgetting to sort for distance/placement problems
FIX: Always sort positions array first!

 MISTAKE 2: Integer overflow in ceiling division
FIX: Use (a + b - 1) / b instead of ceil()

 MISTAKE 3: Wrong inequality direction
- "Can we achieve with <= mid?" > if valid, hi = mid
- "Can we achieve with >= mid?" > if valid, lo = mid

 MISTAKE 4: Not handling edge case where single element > mid
```cpp
bool canSplit(vector<int>& nums, int maxSum, int k) {
   for (int num : nums) {                                            
       if (num > maxSum) return false;  //  Single element too large!
   }                                                                 
   // ... rest of logic                                              

}
```

### **QUICK REFERENCE: isValid() CHEAT SHEET**

STEP 1: Identify what "mid" represents
- mid = speed? capacity? time? distance? max value?

STEP 2: Ask "What do I simulate/count?"
- Simulate: Process tasks greedily, count groups/days/splits
- Count: How many elements satisfy condition

STEP 3: Determine return condition
- Minimize: return count <= limit (or sum <= target)
- Maximize: return count >= requirement

STEP 4: Handle edge cases
- Empty input
- Single element larger than mid
- Overflow in calculations

## **PART 7: COUNT FUNCTION PATTERNS** 

### **COMMON COUNT FUNCTION PATTERNS**

### Problem Type              Count Function              Time

**Sorted Matrix**         Staircase from top-right    O(N)
**Pair Distance**         Sliding window              O(N)
**Split Array**           Greedy partitioning         O(N)
**Eating Bananas**        Ceiling division sum        O(N)
**Magical Number**        x/A + x/B - x/LCM           O(1)
**Running Computers**     sum(min(battery, T))        O(N)
**Repeating Substring**   Hash set check              O(N) or O(N2)
**Mathematical**          Inclusion-Exclusion         O(2^m)
**Capacity Problems**     Greedy assignment           O(N)

### **PATTERN: STAIRCASE COUNTING (Sorted Matrix)** 

PROBLEM: Count elements <= target in row/col sorted matrix

WHY STAIRCASE?
Start from top-right corner. Can only move left or down.
- If element > target: move left (all below are even larger)
- If element <= target: move down (count entire row up to this col)

**VISUALIZATION:**
[1,  4,  7, 11]
[2,  5,  8, 12]   Count elements <= 8
[3,  6,  9, 16]
[10, 13, 14, 17]

Start (0,3): 11 > 8, move left
At (0,2): 7 <= 8, count += 3, move down
At (1,2): 8 <= 8, count += 3, move down
At (2,2): 9 > 8, move left
At (2,1): 6 <= 8, count += 2, move down
At (3,1): 13 > 8, move left
At (3,0): 10 > 8, move left > done

```
Total = 3 + 3 + 2 = 8 elements
```

### **PATTERN: INCLUSION-EXCLUSION (LC 878, 3116)** 

PROBLEM: Count multiples of A or B (or multiple numbers)

FORMULA: count(x) = x/A + x/B - x/LCM(A,B)

### TEMPLATE - Two Numbers:

```
int nthMagicalNumber(int n, int a, int b) {
long lcm = (long)a * b / __gcd(a, b);    
long lo = min(a, b);                     
long hi = (long)n * lo;                  

while (lo < hi) {                        
    long mid = lo + (hi - lo) / 2;       

    long count = mid/a + mid/b - mid/lcm;

    if (count >= n) {                    
        hi = mid;                        
    } else {                             
        lo = mid + 1;                    
    }                                    
}                                        

return lo % (int)(1e9 + 7);              

}
```

**KEY INSIGHT:**
Multiples of A: {A, 2A, 3A, ...}
Multiples of B: {B, 2B, 3B, ...}
Common (LCM): counted twice, subtract once!

### TEMPLATE - Multiple Numbers (Power Set):

```
// For multiple coins/numbers, iterate all subsets
for (int mask = 1; mask < (1 << m); mask++) {
long long lcm = 1;                                             
int setBits = 0;                                               

for (int i = 0; i < m; i++) {                                  
    if (mask & (1 << i)) {                                     
        lcm = lcm / __gcd(lcm, (long long)coins[i]) * coins[i];
        setBits++;                                             
    }                                                          
}                                                              

// Inclusion-Exclusion: add if odd, subtract if even           
if (setBits % 2 == 1) {                                        
    total += n / lcm;                                          
} else {                                                       
    total -= n / lcm;                                          
}                                                              

}
```

### **PATTERN: SLIDING WINDOW COUNT** 

USE WHEN: Count subarrays with sum/property <= target

**TEMPLATE:**

```cpp
int countSubarrays(vector<int>& nums, int target) {
int left = 0, sum = 0, count = 0;                                 

for (int right = 0; right < nums.size(); right++) {               
    sum += nums[right];                                           

    while (sum > target) {                                        
        sum -= nums[left++];                                      
    }                                                             

    count += (right - left + 1);  // All subarrays ending at right
}                                                                 

return count;                                                     

}
```

KEY TRICK: (right - left + 1)
If window [left, right] is valid, these are ALL valid subarrays ending at right:
[left, right], [left+1, right], ..., [right, right]
```
Count = right - left + 1
```

## **PART 6: QUICK DECISION GUIDE**

### **DECISION FLOWCHART**

Is array sorted?
```
                                                                       |
+- YES > Classic Binary Search                                          
|   +- Find element? Use `while (l <= r)`                               
|   +- Find first/last? Use `while (l <= r)` with result tracking       
                                                                       |
+- NO > Can you define search space [lo, hi]?                           
                                                                       |
    +- NO > Not a binary search problem                                 
                                                                       |
    +- YES > Can you write isValid(mid) or count(mid)?                  
                                                                       |
        +- NO > Not a binary search problem                             
                                                                       |
        +- YES > Binary Search on Answer!                               
                                                                       |
            +- Find MINIMUM? > Use `while (l < r)` with mid = (l+r)/2   
                                                                       |
            +- Find MAXIMUM? > Use `while (l < r)` with mid = (l+r+1)/2 
```

### **TEMPLATE SELECTION GUIDE**

### Problem Asks For...           Use This Template

Find element                  l <= r, mid=(l+r)/2, r=mid-1, l=mid+1
First/Last occurrence         l <= r, save result, keep searching
Lower/Upper bound             l < r, r=size (not size-1)
Minimum value that works      l < r, mid=(l+r)/2, r=mid, l=mid+1
Maximum value that works      l < r, mid=(l+r+1)/2 , l=mid, r=mid-1
Kth smallest                  l < r, mid=(l+r)/2, count >= k
Kth largest                   l < r, mid=(l+r)/2, count >= k

### **COMMON MISTAKES & HOW TO AVOID THEM**

### MISTAKE 1: Integer Overflow

```
 int mid = (l + r) / 2;  // Can overflow if l + r > INT_MAX

 int mid = l + (r - l) / 2;
```

### MISTAKE 2: Infinite Loop in Maximum Problems

```
 while (l < r) {
int mid = (l + r) / 2;  // Missing +1!                    
if (isValid(mid)) l = mid;  // Infinite loop when l=5, r=6
else r = mid - 1;                                         

}

 while (l < r) {
int mid = (l + r + 1) / 2;  // +1 is critical!
if (isValid(mid)) l = mid;                    
else r = mid - 1;                             

}
```

### MISTAKE 3: Wrong Loop Condition

For binary search on answer, prefer `l < r` over `l <= r`
It's cleaner and less error-prone!

### MISTAKE 4: Ceiling Division

```
 int hours = (pile / speed) + (pile % speed ? 1 : 0);  // Clumsy

 int hours = (pile + speed - 1) / speed;  // Clean ceiling division
```

### MISTAKE 5: Off-by-One in Bounds

For classic BS:  r = n - 1 (last index)
For lower bound: r = n (one past end)

## **PART 7: PROBLEM LIST BY CATEGORY**

**CLASSIC BINARY SEARCH**

- 704. Binary Search
- 35. Search Insert Position
- 33. Search in Rotated Sorted Array
- 81. Search in Rotated Sorted Array II
- 153. Find Minimum in Rotated Sorted Array
- 154. Find Minimum in Rotated Sorted Array II
- 162. Find Peak Element
- 852. Peak Index in a Mountain Array
- 1095. Find in Mountain Array

**FIRST/LAST OCCURRENCE**

- 34. Find First and Last Position of Element
- 278. First Bad Version
- 374. Guess Number Higher or Lower

**KTH SMALLEST/LARGEST** 

- 378. Kth Smallest Element in a Sorted Matrix 
- 668. Kth Smallest Number in Multiplication Table
- 719. Find K-th Smallest Pair Distance 
- 786. K-th Smallest Prime Fraction
- 1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows
- 1918. Kth Smallest Subarray Sum
- 2040. Kth Smallest Product of Two Sorted Arrays  HARD
- 3116. Kth Smallest Amount With Single Denomination

**MINIMIZE MAXIMUM** 

- 410. Split Array Largest Sum  HARD
- 875. Koko Eating Bananas 
- 1011. Capacity To Ship Packages Within D Days
- 1231. Divide Chocolate
- 1482. Minimum Number of Days to Make m Bouquets
- 2064. Minimized Maximum of Products Distributed to Any Store
- 2187. Minimum Time to Complete Trips
- 2528. Maximize the Minimum Powered City

**MAXIMIZE MINIMUM** 

- 1552. Magnetic Force Between Two Balls 
- 1760. Minimum Limit of Balls in a Bag
- 2226. Maximum Candies Allocated to K Children
- 2517. Maximum Tastiness of Candy Basket
- 2560. House Robber IV

**MATHEMATICAL/ADVANCED**

- 878. Nth Magical Number (Inclusion-Exclusion)
- 1062. Longest Repeating Substring
- 1044. Longest Duplicate Substring (Rolling Hash)
- 3007. Maximum Number (Bit Counting Pattern)
- 3116. Kth Smallest Amount (Inclusion-Exclusion)

**SPECIAL PATTERNS**

- 658. Find K Closest Elements (Two pointers after BS)
- 1970. Last Day Where You Can Still Cross (BFS/DFS validation)
- 2141. Maximum Running Time of N Computers 
- 1986. Minimum Number of Work Sessions (Backtracking validation)

### **ROTATED ARRAY PROBLEMS**

- 33. Search in Rotated Sorted Array
- 81. Search in Rotated Sorted Array II
- 153. Find Minimum in Rotated Sorted Array
- 154. Find Minimum in Rotated Sorted Array II

## **END**
