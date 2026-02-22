# DSA — Interview Preparation

Complete DSA notes and problem solutions, organized by **interview probability**.

> Start from Priority 1 and work down. Priority 1 + 2 covers ~85% of coding interviews.

## Interview-Ready Quick Notes

| Resource | Description |
|----------|-------------|
| **[INTERVIEW-READY-NOTES.md](INTERVIEW-READY-NOTES.md)** | All patterns condensed into one file with templates, probability rankings, and cheat sheets |

---

## Priority 1 — Must Know (90%+ Interview Probability)

These patterns appear in **almost every** coding interview. Non-negotiable.

| # | Topic | Key Patterns | Top Problems |
|---|-------|-------------|-------------|
| 1 | [Arrays + Hashmap Patterns](notes/md/Hashmap%20Patterns.md) | Frequency counting, complement lookup, grouping | Two Sum, Group Anagrams, Longest Consecutive |
| 2 | [Two Pointers](notes/md/Two%20Pointers.md) | Opposite ends, slow/fast, Floyd's cycle, Dutch flag | 3Sum, Container With Most Water, Trapping Rain Water |
| 3 | [Sliding Window](notes/md/Sliding%20Window.md) | Max/min length, counting subarrays, exactly-K trick | Longest Substring Without Repeating, Min Window Substring |
| 4 | [Binary Search](notes/md/Binary%20Search.md) | Classic BS, BS on answer (minimize max / maximize min) | Koko Bananas, Search Rotated Array, Median Two Arrays |
| 5 | [Tree Patterns](notes/md/Tree%20Patterns.md) | DFS/BFS traversals, BST validation, LCA, path sums | Max Path Sum, Validate BST, LCA, Serialize/Deserialize |
| 6 | [Dynamic Programming](notes/md/Dynamic%20Programming.md) | Min/max cost, count ways, knapsack, strings, intervals | Coin Change, LCS, Edit Distance, House Robber, LIS |
| 7 | [Graph Algorithms](notes/md/Graph%20Algorithms.md) | BFS, DFS, topological sort, Union-Find, Dijkstra | Number of Islands, Course Schedule, Network Delay Time |

---

## Priority 2 — High Frequency (70%+ Interview Probability)

These appear in most interviews. Master them after Priority 1.

| # | Topic | Key Patterns | Top Problems |
|---|-------|-------------|-------------|
| 8 | [Backtracking](notes/md/Backtracking.md) | Subsets, combinations, permutations, constraint satisfaction | Subsets, Permutations, N-Queens, Word Search |
| 9 | [Greedy Algorithms](notes/md/Greedy%20Algorithms.md) | Interval scheduling, jump game, task scheduler | Non-overlapping Intervals, Jump Game, Gas Station |
| 10 | [Heap & Kth Problems](notes/md/Heap%20%26%20Kth%20Problems.md) | Kth smallest/largest, merge K sorted, two heaps | Kth Largest, Merge K Lists, Find Median from Stream |
| 11 | [Monotonic Stack](notes/md/Monotonic%20Stack.md) | Next/previous greater/smaller, histogram, expressions | Daily Temperatures, Largest Rectangle, Valid Parentheses |
| 12 | [Prefix Sum](notes/md/Prefix%20Sum.md) | Subarray sum, divisibility, 2D prefix sum | Subarray Sum Equals K, Contiguous Array |

---

## Priority 3 — Commonly Asked (40-70% Probability)

Solid to know. Comes up depending on company and role.

| # | Topic | Key Patterns | Top Problems |
|---|-------|-------------|-------------|
| 13 | [Intervals](notes/md/Intervals.md) | Merge, intersection, sweep line, meeting rooms | Merge Intervals, Meeting Rooms II, Insert Interval |
| 14 | [Prefix Sum + Hashmap](notes/md/Prefix%20Sum%20Hashmap.md) | Count subarrays, max length, existence check | Subarray Sum = K, Max Size Subarray, Divisible by K |
| 15 | [Queue](notes/md/Queue.md) | BFS templates, multi-source BFS, monotonic deque | Rotting Oranges, Sliding Window Max, Queue from Stacks |
| 16 | [Advanced DS Patterns](notes/md/Advanced%20DS%20Patterns.md) | LRU/LFU Cache, Trie, two heaps, design problems | LRU Cache, Trie, Word Search II, Design Twitter |

---

## Priority 4 — Specialized (20-40% Probability)

Good for differentiation. Focus on these after mastering Priority 1-3.

| # | Topic | Key Patterns | When Asked |
|---|-------|-------------|-----------|
| 17 | [Combinatorics](notes/md/Combinatorics%20-%20Complete%20Techniques%20Guide.md) | nCr, nPr, Catalan numbers, modular arithmetic | Math-heavy roles, competitive programming style |
| 18 | [STL Quick Reference](notes/md/STL%20Quick%20Reference.md) | C++ containers, algorithms, lambdas | Reference during practice, not directly asked |
| 19 | [Sliding Window vs Prefix Sum](notes/md/Sliding%20Window%20vs%20Prefix%20Sum%20-%20Decision%20Guide.md) | Decision flowchart for choosing technique | When stuck between the two approaches |

---

## Study Plan

| Timeframe | What to Cover | Goal |
|-----------|--------------|------|
| **Week 1-2** | Priority 1 (Arrays, Two Pointers, Sliding Window, Binary Search) | Pattern recognition + templates |
| **Week 3-4** | Priority 1 (Trees, DP, Graphs) | Recursive thinking + graph traversals |
| **Week 5-6** | Priority 2 (Backtracking, Greedy, Heap, Monotonic Stack, Prefix Sum) | Broaden pattern coverage |
| **Week 7-8** | Priority 3 + 4 (Intervals, Design, Advanced) + mixed practice | Fill gaps, simulate interviews |

---

## Problems (by Category)

| Category | Problems |
|----------|----------|
| **Array** | [3583 - Count Special Triplets](Problems/array/) |
| **Binary Search** | [2141 - Maximum Running Time N Computers](Problems/binary%20search/) |
| **Geometry** | [3623 - Trapezoids I](Problems/geometry/), [3642 - Trapezoids General](Problems/geometry/) |
| **Math** | [1523 - Count Odd Numbers in Range](Problems/math/) |
| **Simulation** | [2211 - Count Collisions on Road](Problems/simulation/) |

---

## Folder Structure

```
DSA/
├── INTERVIEW-READY-NOTES.md    # Condensed interview notes (START HERE)
├── README.md                   # This file
├── notes/
│   └── md/                     # Detailed notes (19 topics)
├── Problems/                   # Solutions by category
│   ├── array/
│   ├── binary search/
│   ├── geometry/
│   ├── math/
│   └── simulation/
└── format_txt_to_md.py
```
