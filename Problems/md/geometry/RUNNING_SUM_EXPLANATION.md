# RUNNING SUM TECHNIQUE - VISUAL EXPLANATION

PROBLEM: We have edges [e1, e2, e3, e4] and need ALL pairwise products
e1*e2 + e1*e3 + e1*e4 + e2*e3 + e2*e4 + e3*e4

## APPROACH 1: NESTED LOOPS (What you understand)

```
j=1  j=2  j=3  j=4

i=1  X   e1e2 e1e3 e1e4
i=2  X    X   e2e3 e2e4
i=3  X    X    X   e3e4
i=4  X    X    X    X
```

We manually compute each pair above diagonal: 6 computations

## APPROACH 2: RUNNING SUM (The optimization)

Think of it like this: When processing edge ei, multiply it with
ALL edges we've seen before!

```
+----------------------------------------------------------------+
|  sum = running total of all edges processed so far             |
|  edge * sum = multiply current edge with ALL previous edges!   |
+----------------------------------------------------------------+
```

**STEP-BY-STEP TRACE:**
-------------------

Initial: ans = 0, sum = 0

### STEP 1: Process e1

Previous edges: [none]
```
sum = 0

ans += e1 * sum = e1 * 0 = 0
```

v
Products added: (none - no previous edges)

```
sum += e1 > sum becomes e1
```

State: ans = 0
```
sum = e1
```

### STEP 2: Process e2

Previous edges: [e1]
```
sum = e1

ans += e2 * sum = e2 * e1
```

v
Products added: e1*e2

```
sum += e2 > sum becomes (e1 + e2)
```

State: ans = e1*e2
```
sum = e1 + e2
```

### STEP 3: Process e3

Previous edges: [e1, e2]
```
sum = e1 + e2

ans += e3 * sum = e3 * (e1 + e2) = e3*e1 + e3*e2
```

v
Products added: e1*e3, e2*e3

```
sum += e3 > sum becomes (e1 + e2 + e3)
```

State: ans = e1*e2 + e1*e3 + e2*e3
```
sum = e1 + e2 + e3
```

### STEP 4: Process e4

Previous edges: [e1, e2, e3]
```
sum = e1 + e2 + e3

ans += e4 * sum = e4 * (e1 + e2 + e3) = e4*e1 + e4*e2 + e4*e3
```

v
Products added: e1*e4, e2*e4, e3*e4

```
sum += e4 > sum becomes (e1 + e2 + e3 + e4)
```

State: ans = e1*e2 + e1*e3 + e2*e3 + e1*e4 + e2*e4 + e3*e4 Y
```
sum = e1 + e2 + e3 + e4
```

## FINAL RESULT

```
ans = e1*e2 + e1*e3 + e1*e4 + e2*e3 + e2*e4 + e3*e4
```

This is EXACTLY what we needed!

## KEY INSIGHT

When you multiply (edge * sum), you're multiplying the current edge
with the SUM of all previous edges.

By distributive property:
edge * (e1 + e2 + ... + ek) = edge*e1 + edge*e2 + ... + edge*ek

So in ONE multiplication, we get ALL products of current edge with
previous edges!

## NUMERIC EXAMPLE

Say: e1 = 3, e2 = 6, e3 = 10

We need: 3*6 + 3*10 + 6*10 = 18 + 30 + 60 = 108

**NESTED LOOPS:**
-------------
```
i=0,j=1: ans += 3*6  = 18  > ans = 18
i=0,j=2: ans += 3*10 = 30  > ans = 48
i=1,j=2: ans += 6*10 = 60  > ans = 108 Y
```

**RUNNING SUM:**
------------
Process e1=3:  ans += 3*0   = 0,  sum = 3   > ans = 0
Process e2=6:  ans += 6*3   = 18, sum = 9   > ans = 18
Process e3=10: ans += 10*9  = 90, sum = 19  > ans = 108 Y

SAME ANSWER!

## WHY IT'S FASTER

4 edges:
Nested: 6 iterations  (4 choose 2)
Running sum: 4 iterations

10 edges:
Nested: 45 iterations  (10 choose 2)
Running sum: 10 iterations

1000 edges:
Nested: 499,500 iterations  (1000 choose 2)
Running sum: 1000 iterations  <-- 500x FASTER!

This is why your solution avoids TLE! 
