# DSA Interview Priority Guide — 80/20 Pareto

> **Updated for 2025–2026 FAANG / Big-Tech interview trends**
>
> **The 80/20 rule**: ~20% of topics (Tier 1) generate ~80% of interview questions. Master these *first* and you'll be ready for most interviews. Tier 2 pushes you to ~95% coverage. Tier 3 is the long tail.
>
> Topics within each tier are sorted **most-asked → least-asked**. Within each topic, problems are also sorted by asking frequency.

---

## TL;DR — The Critical 20% (Study Order)

| # | Topic | Coverage | Notes File |
|---|---|---|---|
| 1 | **Arrays + Hashmaps** | ~25% of all questions | `Hashmap Patterns.md`, `Two Pointers.md` |
| 2 | **Two Pointers / Sliding Window** | ~15% | `Two Pointers.md`, `Sliding Window.md` |
| 3 | **Trees (BFS/DFS/BST)** | ~12% | `Tree Patterns.md` |
| 4 | **Graphs (BFS/DFS/Topo/Dijkstra)** | ~10% | `Graph Algorithms.md` |
| 5 | **Binary Search (incl. on answer)** | ~10% | `Binary Search.md` |
| 6 | **Dynamic Programming (1D/2D)** | ~10% | `Dynamic Programming.md` |

**These six topics together = ~82% of interview questions.** Get fluent here before anything else.

---

# TIER 1 — MUST KNOW (95% frequency)

## 1. Arrays + Hashmaps  ★★★★★ — `Hashmap Patterns.md`
The single highest-leverage topic. Asked in nearly every interview, often as the warm-up.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 1 | Two Sum | Complement lookup |
| 49 | Group Anagrams | Sort/count as key |
| 217 | Contains Duplicate | Set existence |
| 128 | Longest Consecutive Sequence | Set + start detection |
| 347 | Top K Frequent Elements | Freq map + bucket sort |
| 36 | Valid Sudoku | State encoding |
| 560 | Subarray Sum Equals K | Prefix sum + hashmap |
| 380 | Insert Delete GetRandom O(1) | Map + vector |
| 146 | LRU Cache | Map + doubly linked list |

---

## 2. Two Pointers  ★★★★★ — `Two Pointers.md`
Foundational. Four patterns (opposite ends, slow & fast, parallel, three pointers) cover 90% of two-pointer problems.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 15 | 3Sum | Sorted + opposite ends |
| 11 | Container With Most Water | Greedy opposite ends |
| 42 | Trapping Rain Water | Opposite ends + max tracking |
| 125 | Valid Palindrome | Opposite ends |
| 88 | Merge Sorted Array | Parallel (backward) |
| 75 | Sort Colors | Three pointers (Dutch flag) |
| 26 | Remove Duplicates Sorted | Slow & fast |
| 283 | Move Zeroes | Slow & fast |
| 680 | Valid Palindrome II | Opposite ends + skip |

---

## 3. Sliding Window  ★★★★★ — `Sliding Window.md`
Variable-size window for substring/subarray problems. The "shrink while invalid" template covers 80% of variants.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 3 | Longest Substring Without Repeat | Distinct char window |
| 76 | Minimum Window Substring | Shrinkable + freq map |
| 567 | Permutation in String | Fixed-size + freq |
| 424 | Longest Repeating Char Replacement | Max char + shrink |
| 209 | Minimum Size Subarray Sum | Shrinkable sum |
| 239 | Sliding Window Maximum | Monotonic deque |
| 438 | Find All Anagrams | Fixed-size + freq |
| 992 | Subarrays With K Distinct | atMost(K) − atMost(K−1) |

---

## 4. Trees (Binary Tree + BST)  ★★★★★ — `Tree Patterns.md`
DFS recursion + BFS level-order solve 90% of tree problems.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 104 | Max Depth Binary Tree | DFS recursion |
| 226 | Invert Binary Tree | DFS swap |
| 102 | Level Order Traversal | BFS queue |
| 199 | Right Side View | BFS last-of-level |
| 124 | Binary Tree Max Path Sum | DFS post-order + global max |
| 236 | LCA of Binary Tree | DFS bottom-up |
| 235 | LCA of BST | BST property |
| 297 | Serialize/Deserialize | DFS pre-order |
| 543 | Diameter of Binary Tree | DFS + global max |
| 98 | Validate BST | DFS with bounds |
| 230 | Kth Smallest in BST | Inorder traversal |

---

## 5. Graphs (BFS / DFS / Topo Sort / Dijkstra)  ★★★★★ — `Graph Algorithms.md`
After trees, graphs is the next most-tested topic. BFS for shortest path, DFS for exploration, Topo for dependencies.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 200 | Number of Islands | DFS / BFS on grid |
| 994 | Rotting Oranges | Multi-source BFS |
| 207 | Course Schedule | Topological sort (cycle detect) |
| 210 | Course Schedule II | Topological order |
| 133 | Clone Graph | DFS + hashmap |
| 127 | Word Ladder | BFS shortest path |
| 417 | Pacific Atlantic Water Flow | Multi-source DFS |
| 743 | Network Delay Time | Dijkstra |
| 787 | Cheapest Flights K Stops | Bellman-Ford / BFS-with-stops |
| 684 | Redundant Connection | Union-Find |
| 269 | Alien Dictionary | Topo sort |
| 130 | Surrounded Regions | DFS from border |

---

## 6. Binary Search  ★★★★★ — `Binary Search.md`
"Binary search on the answer" pattern is increasingly popular in 2025–2026 interviews.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 704 | Binary Search (basic) | Classic template |
| 33 | Search in Rotated Sorted Array | Modified binary search |
| 153 | Find Min in Rotated Array | Binary search |
| 875 | Koko Eating Bananas | **BS on answer** |
| 1011 | Capacity to Ship Packages | **BS on answer** |
| 410 | Split Array Largest Sum | **BS on answer** (HARD) |
| 4 | Median of Two Sorted Arrays | BS partition (HARD) |
| 162 | Find Peak Element | BS variant |
| 74 | Search 2D Matrix | BS on flattened |
| 1268 | Search Suggestions System | BS + sort |

---

## 7. Dynamic Programming  ★★★★★ — `Dynamic Programming.md`
Heavy at FAANG (Google, Meta). 1D and 2D string DP are most common.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 70 | Climbing Stairs | 1D linear |
| 198 | House Robber | 1D pick/skip |
| 213 | House Robber II | Circular variant |
| 322 | Coin Change | Unbounded knapsack |
| 300 | Longest Increasing Subseq | LIS / Patience sort |
| 1143 | Longest Common Subsequence | 2D string DP |
| 72 | Edit Distance | 2D string DP |
| 53 | Maximum Subarray (Kadane) | 1D running max |
| 152 | Maximum Product Subarray | Track min+max |
| 416 | Partition Equal Subset Sum | 0/1 Knapsack |
| 139 | Word Break | 1D + dict lookup |
| 5 | Longest Palindromic Substring | Expand center / 2D |
| 121 | Best Time to Buy Stock | State machine |
| 188 | Best Time Buy Stock IV | k-transactions DP |
| 312 | Burst Balloons | Interval DP (HARD) |

---

# TIER 2 — HIGH PRIORITY (60–85% frequency)

## 8. Backtracking  ★★★★ — `Backtracking.md`
Permutations, combinations, subsets, and grid/word problems. One template handles 80% of cases.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 78 | Subsets | Include/exclude |
| 46 | Permutations | Used-set + swap |
| 39 | Combination Sum | Include with reuse |
| 51 | N-Queens | Constraint backtrack |
| 79 | Word Search | DFS + visited |
| 22 | Generate Parentheses | Constraint-pruned |
| 17 | Letter Combinations of Phone | Multi-choice |
| 131 | Palindrome Partitioning | String DP + backtrack |

---

## 9. Heap / Priority Queue  ★★★★ — `Heap & Kth Problems.md`
"Top K", "Kth element", and streaming problems. Heap of size K is the bread-and-butter pattern.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 215 | Kth Largest in Array | Min heap size K |
| 295 | Find Median From Data Stream | Two heaps |
| 23 | Merge K Sorted Lists | Min heap |
| 253 | Meeting Rooms II | Sweep + heap |
| 621 | Task Scheduler | Greedy + max heap |
| 767 | Reorganize String | Greedy + max heap |
| 973 | K Closest Points to Origin | Max heap size K |
| 658 | Find K Closest Elements | Heap or BS + 2P |
| 1383 | Max Performance of Team | Sort + heap |
| 502 | IPO | Two heaps |

---

## 10. Stack & Monotonic Stack  ★★★★ — `Monotonic Stack.md`
"Next greater/smaller" pattern is the most distinctive monotonic-stack signal.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 20 | Valid Parentheses | Basic stack |
| 739 | Daily Temperatures | Next greater (monotonic) |
| 84 | Largest Rectangle Histogram | Monotonic stack (HARD) |
| 85 | Maximal Rectangle | LC 84 per row (HARD) |
| 496 | Next Greater Element I | Monotonic + map |
| 503 | Next Greater Element II | Circular array |
| 150 | Evaluate Reverse Polish | Stack eval |
| 224 | Basic Calculator | Stack + parsing |
| 71 | Simplify Path | Stack of tokens |
| 394 | Decode String | Stack of state |
| 901 | Online Stock Span | Monotonic stack |

---

## 11. Linked List  ★★★★ — `Linked List.md`
Almost every interview will test pointer manipulation. Reverse, merge, cycle = top three patterns.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 206 | Reverse Linked List | Pointer reversal |
| 21 | Merge Two Sorted Lists | Parallel |
| 141 | Linked List Cycle | Floyd's slow/fast |
| 142 | Linked List Cycle II | Floyd's + math |
| 19 | Remove Nth From End | Slow/fast with gap |
| 138 | Copy List With Random Pointer | Hashmap or interleave |
| 25 | Reverse Nodes in K-Group | Reversal + grouping (HARD) |
| 146 | LRU Cache | Map + DLL |
| 460 | LFU Cache | Map + DLL of buckets (HARD) |
| 23 | Merge K Sorted Lists | Heap |
| 234 | Palindrome Linked List | Reverse half |

---

## 12. Greedy  ★★★ — `Greedy Algorithms.md`
Sort + scan is the canonical greedy pattern. Often combined with intervals, scheduling, or strings.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 56 | Merge Intervals | Sort + merge |
| 253 | Meeting Rooms II | Sort + heap |
| 435 | Non-overlapping Intervals | Sort by end |
| 55 | Jump Game | Track farthest |
| 45 | Jump Game II | Greedy BFS |
| 763 | Partition Labels | Last occurrence |
| 134 | Gas Station | Single pass |
| 135 | Candy | Two passes |
| 621 | Task Scheduler | Max freq formula / heap |
| 678 | Valid Parenthesis String | Range tracking |
| 1029 | Two City Scheduling | Sort by diff |

---

## 13. Prefix Sum + Hashmap  ★★★ — `Prefix Sum.md`, `Prefix Sum Hashmap.md`
Critical for subarray problems with **negative numbers** (where sliding window fails).

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 560 | Subarray Sum Equals K | Prefix + hashmap |
| 974 | Subarray Sums Divisible by K | Modulo + hashmap |
| 525 | Contiguous Array | Map +1/−1 first occurrence |
| 304 | Range Sum Query 2D | 2D prefix sum |
| 238 | Product of Array Except Self | Left × right prefix |
| 523 | Continuous Subarray Sum | Modulo + first index |
| 437 | Path Sum III | Prefix on tree |
| 1248 | Count Nice Subarrays | atMost(K) prefix |

---

# TIER 3 — COMMONLY ASKED (40–60% frequency)

## 14. Intervals  ★★★ — `Intervals.md`
Most interval problems reduce to: **sort by start (or end), then process**.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 56 | Merge Intervals | Sort + merge |
| 57 | Insert Interval | Linear scan |
| 253 | Meeting Rooms II | Sort + heap |
| 435 | Non-overlapping Intervals | Sort by end |
| 452 | Min Arrows to Burst Balloons | Sort by end |
| 986 | Interval List Intersections | Two pointers |
| 729 | My Calendar I | TreeMap / sorted set |
| 1851 | Min Interval to Include Each Query | Offline sort + heap (HARD) |

---

## 15. Tries (Prefix Trees)  ★★★ — `Advanced DS Patterns.md`
Critical for prefix-based problems and autocomplete. One template, used in many ways.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 208 | Implement Trie | Classic trie |
| 211 | Add and Search Word | Trie + DFS |
| 212 | Word Search II | Trie + grid DFS (HARD) |
| 648 | Replace Words | Trie prefix lookup |
| 1268 | Search Suggestions System | Trie + sorted |
| 421 | Max XOR of Two Numbers | Bitwise trie |

---

## 16. Union-Find (DSU)  ★★ — covered in `Graph Algorithms.md`
Connectivity / cycle detection without graph traversal. The "rank + path compression" template is the only one you need.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 684 | Redundant Connection | DSU cycle detect |
| 547 | Number of Provinces | DSU connected components |
| 1319 | Make Network Connected | DSU |
| 721 | Accounts Merge | DSU + hashmap |
| 200 | Number of Islands | DSU alternative |
| 305 | Number of Islands II | DSU streaming (HARD) |

---

## 17. Strings (KMP / Z / Palindrome)  ★★ — `String Patterns.md`
Most string problems are sliding window / hashmap. KMP and palindrome expansion are the distinctive techniques.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 28 | Find First Occurrence (strStr) | KMP / Z-function |
| 5 | Longest Palindromic Substring | Expand center |
| 647 | Palindromic Substrings | Expand center |
| 151 | Reverse Words in String | In-place reverse |
| 12/13 | Roman ↔ Integer | Lookup + parse |
| 8 | String to Integer (atoi) | State machine |
| 38 | Count and Say | String build |

---

## 18. Bit Manipulation  ★★ — covered in `Dynamic Programming.md` (Bitmask DP)
Asked moderately. Know XOR tricks and bit-set operations.

**Most-asked problems**
| LC | Problem | Pattern |
|---|---|---|
| 136 | Single Number | XOR all |
| 137 | Single Number II | Bit counting / state machine |
| 191 | Number of 1 Bits | n & (n−1) trick |
| 338 | Counting Bits | DP on bits |
| 268 | Missing Number | XOR or sum |
| 78 | Subsets | Bitmask enumeration |
| 187 | Repeated DNA Sequences | Rolling hash |

---

# TIER 4 — SPECIALIZED (20–40% frequency)

These are asked at specific companies / for specific roles. Learn after Tier 1–3.

| Topic | Notes File | When asked |
|---|---|---|
| **Advanced DP** (Digit DP, Bitmask DP, Game DP) | `Dynamic Programming.md` | Google / hard rounds |
| **Combinatorics & Math** (modular inverse, nCr mod p) | `Combinatorics - Complete Techniques Guide.md` | Adobe, math-heavy roles |
| **Segment Tree / BIT** | `Advanced DS Patterns.md` | Competitive backgrounds |
| **Reservoir Sampling** | mentioned in design notes | Streaming problems |
| **String Hashing (Rabin-Karp)** | `String Patterns.md` | Substring counting |
| **Sweep Line** | `Intervals.md` | Scheduling problems |
| **Sqrt Decomposition** | — | Very rare |

---

# THE TOP-50 PROBLEMS LIST (Cross-Topic, By Asking Frequency)

If you only have time for 50 problems, do these. Sorted by frequency at FAANG/Big-Tech 2025–2026:

| Rank | LC | Problem | Topic |
|---:|---|---|---|
| 1 | 1 | Two Sum | Hashmap |
| 2 | 20 | Valid Parentheses | Stack |
| 3 | 200 | Number of Islands | Graph/DFS |
| 4 | 206 | Reverse Linked List | Linked List |
| 5 | 21 | Merge Two Sorted Lists | Linked List |
| 6 | 53 | Maximum Subarray (Kadane) | DP |
| 7 | 121 | Best Time to Buy Stock | DP |
| 8 | 56 | Merge Intervals | Intervals |
| 9 | 3 | Longest Substring Without Repeat | Sliding Window |
| 10 | 15 | 3Sum | Two Pointers |
| 11 | 11 | Container With Most Water | Two Pointers |
| 12 | 42 | Trapping Rain Water | Two Pointers |
| 13 | 76 | Min Window Substring | Sliding Window (HARD) |
| 14 | 33 | Search Rotated Sorted Array | Binary Search |
| 15 | 153 | Find Min in Rotated Sorted | Binary Search |
| 16 | 875 | Koko Eating Bananas | BS on answer |
| 17 | 104 | Max Depth Binary Tree | Trees |
| 18 | 102 | Level Order Traversal | Trees BFS |
| 19 | 226 | Invert Binary Tree | Trees |
| 20 | 124 | Binary Tree Max Path Sum | Trees (HARD) |
| 21 | 236 | LCA of Binary Tree | Trees |
| 22 | 297 | Serialize/Deserialize Tree | Trees (HARD) |
| 23 | 98 | Validate BST | Trees |
| 24 | 207 | Course Schedule | Topo Sort |
| 25 | 994 | Rotting Oranges | Multi-source BFS |
| 26 | 127 | Word Ladder | BFS (HARD) |
| 27 | 133 | Clone Graph | Graph DFS |
| 28 | 743 | Network Delay Time | Dijkstra |
| 29 | 322 | Coin Change | DP |
| 30 | 300 | Longest Increasing Subseq | DP |
| 31 | 72 | Edit Distance | 2D DP (HARD) |
| 32 | 1143 | Longest Common Subseq | 2D DP |
| 33 | 198 | House Robber | DP |
| 34 | 416 | Partition Equal Subset Sum | DP (Knapsack) |
| 35 | 139 | Word Break | DP |
| 36 | 215 | Kth Largest Element | Heap / QuickSelect |
| 37 | 295 | Find Median Data Stream | Two Heaps (HARD) |
| 38 | 23 | Merge K Sorted Lists | Heap (HARD) |
| 39 | 347 | Top K Frequent Elements | Heap / Bucket |
| 40 | 253 | Meeting Rooms II | Heap / Intervals |
| 41 | 49 | Group Anagrams | Hashmap |
| 42 | 128 | Longest Consecutive Sequence | Hashmap |
| 43 | 560 | Subarray Sum Equals K | Prefix Sum + Map |
| 44 | 238 | Product Except Self | Prefix |
| 45 | 78 | Subsets | Backtracking |
| 46 | 46 | Permutations | Backtracking |
| 47 | 39 | Combination Sum | Backtracking |
| 48 | 739 | Daily Temperatures | Monotonic Stack |
| 49 | 84 | Largest Rectangle Histogram | Monotonic Stack (HARD) |
| 50 | 146 | LRU Cache | Design + LinkedList + Map |

---

# Suggested Study Order (4–6 weeks)

| Week | Focus | Goal |
|---|---|---|
| **1** | Topics 1–3 (Arrays/Hashmap, Two Pointers, Sliding Window) | ~30 problems, get fluent in templates |
| **2** | Topics 4–5 (Trees, Graphs) | ~25 problems, master DFS/BFS recursion |
| **3** | Topics 6–7 (Binary Search, DP) | ~25 problems, focus on BS-on-answer + 1D/2D DP |
| **4** | Topics 8–11 (Backtracking, Heap, Stack, Linked List) | ~25 problems |
| **5** | Topics 12–14 (Greedy, Prefix Sum, Intervals) | ~15 problems + revision |
| **6** | Topics 15–18 + Top 50 review + mock interviews | Polish + speed |

---

# Latest Trends (2025–2026)

1. **Binary search on the answer** has overtaken plain binary search in frequency — practice LC 875, 1011, 410, 1283.
2. **Multi-source BFS / DFS** is now standard at FAANG — LC 994, 1162, 417, 542 all appear regularly.
3. **Two heaps** pattern is rising — LC 295, 480, 502, 1834. Pair this with **sweep line** at meeting/scheduling problems.
4. **Monotonic stack on histograms** (LC 84, 85, 42, 1856) is hot at Meta and Amazon.
5. **String DP** (Edit Distance, LCS, palindromic) remains very common at Google.
6. **System-design-flavored DSA** (LRU/LFU, design Twitter, design HashMap) is rising at L4/L5 onsites.
7. **Newer LeetCode hard contests** (LC 2400+) are sometimes asked — they often combine 2 patterns (e.g., 2402 Meeting Rooms III = heap + sweep line).
8. **Decreased focus**: plain recursion-only problems, naive backtracking without pruning, niche math-heavy DP.

---

# Pattern Recognition Quick Map

| Problem says... | Use... |
|---|---|
| "Sorted array" | Two Pointers or Binary Search |
| "Subarray sum / contiguous" | Sliding Window (positive) or Prefix Sum (negative) |
| "Longest / shortest substring" | Sliding Window |
| "Top K / Kth" | Heap (size K) or QuickSelect |
| "Min / max cost reaching goal" | DP or Dijkstra |
| "Number of ways" | DP (count) |
| "Find all / generate all" | Backtracking |
| "Connected groups" | DFS / BFS / Union-Find |
| "Ordering / dependencies" | Topological Sort |
| "Shortest path unweighted" | BFS |
| "Shortest path weighted, positive" | Dijkstra |
| "Next greater / previous smaller" | Monotonic Stack |
| "Overlapping intervals" | Sort + sweep / heap |
| "Sliding maximum/minimum" | Monotonic Deque |
| "Exactly K" | atMost(K) − atMost(K−1) |
| "In place, O(1) extra" | Two Pointers |
| "Prefix / autocomplete" | Trie |
| "Cycle in graph" | DFS with state OR Union-Find |
| "Tree path / root-to-leaf" | DFS recursion |
| "Level / layer of tree" | BFS |
| "Cache with O(1) ops" | HashMap + Doubly Linked List |

---

# Cross-Reference: This File vs Your Other Notes

| Need | Use this file |
|---|---|
| What to study next? | `DSA-PRIORITY-80-20.md` (this file) |
| Pattern templates + code | `INTERVIEW-READY-NOTES.md` |
| Full deep-dive per topic | `notes/md/<Topic>.md` |
| Company-specific lists | `Company-Wise-DSA-Questions.md` |
| C++ STL reference | `notes/md/STL Quick Reference.md` |
