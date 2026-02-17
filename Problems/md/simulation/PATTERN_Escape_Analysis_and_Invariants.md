# PATTERN: ESCAPE ANALYSIS & INVARIANT COUNTING

Category: Greedy, Simulation Optimization, Observation-based

This pattern appears when:
- You have a complex simulation/process
- But you can identify elements that "escape" or don't participate
- And find an INVARIANT that lets you count directly instead of simulating

## CORE CONCEPTS

1. ESCAPE ANALYSIS
- Identify boundary conditions
- Find elements that exit without interaction
- Focus only on "active zone"

2. INVARIANT DISCOVERY
- Find what remains constant during process
- Each element contributes fixed amount
- Count instead of simulate

3. GREEDY SIMPLIFICATION
- Convert O(n2) simulation to O(n) counting
- Avoid tracking intermediate states
- Use mathematical properties

## THE GENERAL PATTERN

NAIVE APPROACH (Simulation):
-----------------------------
Simulate step by step:
- Complex state tracking
- Multiple iterations
- Time: O(n2) or worse
- Space: O(n)

OPTIMIZED APPROACH (Escape + Invariant):
-----------------------------------------
1. Identify escape boundaries
2. Find active zone (elements that participate)
3. Discover invariant (contribution per element)
4. Count directly

Time: O(n), Space: O(1)

## PROBLEM 1: COLLISION ON ROAD (LC 2211)

Observation:
- Leading L's escape left (no barrier)
- Trailing R's escape right (no barrier)
- Middle section: all moving cars collide

Invariant: Each non-escaping moving car > 1 collision

Solution:
collisions = count('L' and 'R' in active zone)

## PROBLEM 2: REMOVE OUTER PARENTHESES (LC 1021)

Problem: Remove outermost parentheses from primitives
Input: "(()())(())"
Output: "()()()"

Observation:
- Track depth/balance
- Outermost layer (depth 0>1 and n>n-1) escapes
- Inner layers (depth > 1) are kept

Invariant: Characters at depth > 2 always included

Solution:
int depth = 0;
for (char c : s) {
```
  if (c == '(') {                                  
      if (depth > 0) result += c;  // Not outermost
      depth++;                                     
  } else {                                         
      depth--;                                     
      if (depth > 0) result += c;  // Not outermost
  }                                                
```

}

## PROBLEM 3: CANDY CRUSH (Similar Pattern)

Problem: Remove consecutive same elements (>3)

Naive: Repeatedly scan and remove until no change
Time: O(n2)

Optimized (Stack-based):
- Track elements and counts
- Pop when count > 3
- One pass: O(n)

Invariant: Elements in final answer never crushed

## PROBLEM 4: MINIMUM DELETIONS TO MAKE VALID PARENTHESES

Problem: Min deletions to balance parentheses

Observation:
- Unmatched '(' at the end > delete
- Unmatched ')' at the beginning > delete

Invariant:
deletions = unmatched_open + unmatched_close

Solution:
int open = 0, deletions = 0;
for (char c : s) {
```
  if (c == '(') open++;              
  else if (open > 0) open--;         
  else deletions++;  // Unmatched ')'
```

}
return deletions + open;  // Add unmatched '('

## PROBLEM 5: ASTEROID COLLISION (LC 735)

Problem: Asteroids [10, 2, -5] > collide, negative = left

Observation:
- Only rightward (positive) meets leftward (negative) collide
- Same direction: no collision (escape together)

Using Stack:
- Rightward asteroids pushed to stack
- Leftward triggers collisions with stack top
- Survivors remain

Invariant: Only R>L direction causes collision

## GENERAL PROBLEM PATTERN RECOGNITION

**KEYWORDS THAT SUGGEST THIS PATTERN:**

Y "Moving in directions"
Y "Collisions"
Y "Remove/cancel/match"
Y "Valid" (parentheses, etc.)
Y "Consecutive same elements"
Y "Opposite directions"
Y "After all operations"
Y "Final state"

**APPROACH:**
---------
1. Can I identify what "escapes"?
2. Is there an "active zone"?
3. What's the contribution per element?
4. Can I count directly instead of simulating?

## TECHNIQUE BREAKDOWN

TECHNIQUE 1: BOUNDARY TRIMMING
-------------------------------
Remove elements that don't participate from edges

Example (Collision):
"LLRR" > trim LL from left, RR from right > ""

Code Pattern:
int left = 0, right = n - 1;
while (left < n && shouldSkip(arr[left])) left++;
while (right >= 0 && shouldSkip(arr[right])) right--;
// Process [left, right]

TECHNIQUE 2: INVARIANT COUNTING
--------------------------------
Find what each element contributes

Example (Collision):
Each moving car in active zone > +1 collision

Code Pattern:
int count = 0;
for (element in active_zone) {
```
  if (participates(element)) count++;
```

}

TECHNIQUE 3: STACK FOR CANCELLATION
------------------------------------
Use stack when elements cancel/interact

Example (Parentheses):
'(' pushes, ')' pops
Unmatched elements need deletion

Code Pattern:
stack<T> st;
for (element : elements) {
```
  if (should_push(element)) st.push(element);                  
  else if (!st.empty() && cancels(st.top(), element)) st.pop();
  else deletions++;                                            
```

}

TECHNIQUE 4: BALANCE/DEPTH TRACKING
------------------------------------
Track net effect without storing all elements

Example (Nested structures):
depth++ for open, depth-- for close
Know nesting level without storing

Code Pattern:
int balance = 0;
for (element : elements) {
```
  if (opens(element)) balance++;      
  else if (closes(element)) balance--;
  // Use balance to make decisions    
```

}

## COMPLEXITY IMPROVEMENTS

### Simulation > Direct Counting

Before: O(n2) or O(n x k) iterations
After:  O(n) single pass

### State Tracking > Mathematical Formula

Before: Track all intermediate states
After:  Calculate final result directly

### Multiple Passes > Single Pass

Before: Repeat until stable
After:  Process once with proper logic

## PROBLEM-SOLVING FRAMEWORK

STEP 1: Understand the Process
-------------------------------
Q: What happens in the simulation?
Q: What are the rules?
Q: When does process stop?

STEP 2: Identify Escapes
-------------------------
Q: What elements don't participate?
Q: Where are the boundaries?
Q: Can we trim edges?

STEP 3: Find Invariants
------------------------
Q: What's constant per element?
Q: What's the contribution?
Q: Can we count directly?

STEP 4: Optimize
----------------
Q: Can we avoid simulation?
Q: Single pass possible?
Q: What data structure helps?

## PRACTICE PROBLEMS (Same Pattern)

**EASY:**
- LC 1021: Remove Outermost Parentheses
- LC 1047: Remove All Adjacent Duplicates

**MEDIUM:**
- LC 2211: Count Collisions on a Road *
- LC 735: Asteroid Collision
- LC 1209: Remove All Adjacent Duplicates in String II
- LC 1249: Minimum Remove to Make Valid Parentheses

**HARD:**
- LC 768: Max Chunks To Make Sorted II
- Complex candy crush variations

## KEY INSIGHTS

1.  Simulation often has O(n2) complexity
2.  Look for elements that "escape" boundaries
3.  Find INVARIANT: contribution per element
4.  Convert process to direct counting
5.  Stack useful for cancellation/matching
6.  Balance tracking for nested structures
7.  Greedy often works with proper observation

Mathematical Foundation:
------------------------
Instead of: result = Σ(step-by-step interactions)
Do:         result = Σ(invariant x element_count)

This is why collision problem:
Instead of tracking each collision event
Simply count: non_escaping_moving_cars

## RELATED PATTERNS

1. Two Pointers
- Similar boundary analysis
- Process from edges inward

2. Monotonic Stack
- Track "next greater/smaller"
- Escape analysis for elements

3. Greedy
- Local optimal > global optimal
- No backtracking needed

4. State Compression
- Reduce state space
- Track only essential info

## SUMMARY: WHEN TO USE THIS PATTERN

 USE when:
- Problem involves simulation/process
- Elements interact in predictable ways
- Some elements don't participate (escape)
- Each participating element has fixed contribution
- Direct counting possible

 DON'T USE when:
- Need exact sequence of events
- Order matters for output
- State dependencies are complex
- No clear invariant exists

**RECOGNITION CHECKLIST:**
o Is this a simulation problem?
o Do some elements escape/not participate?
o Is there a fixed contribution per element?
o Can I identify boundaries?
o Can I count instead of simulate?

If YES to 3+ > Use this pattern!

## FINAL THOUGHTS

The collision problem teaches us:

1. OBSERVE before implementing
- Don't rush to simulate
- Look for patterns

2. SIMPLIFY through math
- Each car > 1 collision (invariant)
- Count instead of track

3. IDENTIFY escapes
- Leading L's escape
- Trailing R's escape

4. GREEDY works
- Process boundaries
- Count middle

This pattern appears frequently in:
- String manipulation
- Simulation optimization
- Matching/cancellation problems
- Process simplification

Master this and you'll solve many problems faster! 

