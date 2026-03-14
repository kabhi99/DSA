# DSA INTERVIEW QUESTIONS — COMPANY WISE

*Frequently asked coding/DSA questions mapped to companies, with LeetCode links and pattern tags.*

> **How to use:** Questions are grouped by company with difficulty, pattern tag, and direct LeetCode link.
> Your local notes for each pattern are linked in the [Pattern Reference](#pattern-reference-local-notes) section at the bottom.

---

## WALMART GLOBAL TECH (DETAILED)

Walmart interviews have 4-6 rounds: OA (HackerRank) + 2-3 DSA rounds + System Design + Behavioral.
Difficulty skews **Medium** with occasional Hard. Strong focus on **caching, arrays, DP, and trees**.

### Round Structure
- **Online Assessment:** 2-3 problems (60-90 min), HackerRank. Usually Medium.
- **DSA Round 1:** 1-2 problems, live coding. Clean code + complexity analysis.
- **DSA Round 2:** 1-2 problems, different topic. Edge cases matter.
- **Core CS Round:** OOP concepts, polymorphism, interfaces, multithreading.
- **System Design:** Inventory, flash sale, e-commerce scale (SDE-2+).

### Most Asked Questions

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 2 | LFU Cache | Hard | Design / HashMap + DLL + Freq Map | [LC 460](https://leetcode.com/problems/lfu-cache/) |
| 3 | Combination Sum | Medium | Backtracking | [LC 39](https://leetcode.com/problems/combination-sum/) |
| 4 | Target Sum | Medium | DP / Backtracking | [LC 494](https://leetcode.com/problems/target-sum/) |
| 5 | Copy List with Random Pointer | Medium | Linked List / HashMap | [LC 138](https://leetcode.com/problems/copy-list-with-random-pointer/) |
| 6 | Word Search | Medium | Backtracking / DFS | [LC 79](https://leetcode.com/problems/word-search/) |
| 7 | Find the Celebrity | Medium | Array / Greedy | [LC 277](https://leetcode.com/problems/find-the-celebrity/) |
| 8 | Find Median from Data Stream | Hard | Heap (Two Heaps) | [LC 295](https://leetcode.com/problems/find-median-from-data-stream/) |
| 9 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 10 | Second Largest Element in Array | Easy | Array / Single Pass | — |
| 11 | Longest Consecutive Sequence | Medium | HashSet | [LC 128](https://leetcode.com/problems/longest-consecutive-sequence/) |
| 12 | Valid Anagram | Easy | HashMap / Sorting | [LC 242](https://leetcode.com/problems/valid-anagram/) |
| 13 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| 14 | House Robber (Non-adjacent Sum) | Medium | DP | [LC 198](https://leetcode.com/problems/house-robber/) |
| 15 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 16 | Valid Palindrome | Easy | Two Pointers | [LC 125](https://leetcode.com/problems/valid-palindrome/) |
| 17 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 18 | Binary Tree Level Order Traversal | Medium | BFS / Tree | [LC 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) |
| 19 | Serialize and Deserialize Binary Tree | Hard | Tree / DFS | [LC 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) |
| 20 | Top K Frequent Elements | Medium | Heap / Bucket Sort | [LC 347](https://leetcode.com/problems/top-k-frequent-elements/) |

### Walmart Prep Tips
- **LRU/LFU Cache is almost guaranteed** — know the O(1) implementation cold (HashMap + Doubly Linked List).
- **DP problems** lean towards classic patterns (House Robber, Combination Sum, Target Sum) — not obscure.
- **SQL round is common** — practice self-joins, window functions, date arithmetic.
- **Core CS**: Expect OOP questions (abstract vs interface, static keyword, polymorphism).
- **Clean code matters** — naming, modularity, edge case handling are explicitly evaluated.

---

## GOOGLE

Hardest bar. ~30% Hard problems. Heavy on **Graphs, DP, and Binary Search**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Median of Two Sorted Arrays | Hard | Binary Search | [LC 4](https://leetcode.com/problems/median-of-two-sorted-arrays/) |
| 2 | Longest Increasing Subsequence | Medium | DP / Binary Search | [LC 300](https://leetcode.com/problems/longest-increasing-subsequence/) |
| 3 | Word Ladder | Hard | BFS / Graph | [LC 127](https://leetcode.com/problems/word-ladder/) |
| 4 | Course Schedule II | Medium | Topological Sort | [LC 210](https://leetcode.com/problems/course-schedule-ii/) |
| 5 | Number of Islands | Medium | DFS / BFS / Graph | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 6 | Trapping Rain Water | Hard | Two Pointers / Stack | [LC 42](https://leetcode.com/problems/trapping-rain-water/) |
| 7 | Word Break | Medium | DP / Trie | [LC 139](https://leetcode.com/problems/word-break/) |
| 8 | Minimum Window Substring | Hard | Sliding Window | [LC 76](https://leetcode.com/problems/minimum-window-substring/) |
| 9 | Alien Dictionary | Hard | Topological Sort | [LC 269](https://leetcode.com/problems/alien-dictionary/) |
| 10 | Regular Expression Matching | Hard | DP | [LC 10](https://leetcode.com/problems/regular-expression-matching/) |
| 11 | Merge K Sorted Lists | Hard | Heap | [LC 23](https://leetcode.com/problems/merge-k-sorted-lists/) |
| 12 | Longest Valid Parentheses | Hard | Stack / DP | [LC 32](https://leetcode.com/problems/longest-valid-parentheses/) |
| 13 | Edit Distance | Medium | 2D DP | [LC 72](https://leetcode.com/problems/edit-distance/) |
| 14 | Shortest Path in Binary Matrix | Medium | BFS | [LC 1091](https://leetcode.com/problems/shortest-path-in-binary-matrix/) |
| 15 | Design Search Autocomplete System | Hard | Trie / Design | [LC 642](https://leetcode.com/problems/design-search-autocomplete-system/) |
| 16 | Count of Smaller Numbers After Self | Hard | Merge Sort / BIT | [LC 315](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) |
| 17 | Snapshot Array | Medium | Binary Search / Design | [LC 1146](https://leetcode.com/problems/snapshot-array/) |
| 18 | Maximum Profit in Job Scheduling | Hard | DP / Binary Search | [LC 1235](https://leetcode.com/problems/maximum-profit-in-job-scheduling/) |

---

## AMAZON

Medium-heavy (~58%). Focus on **Trees, Arrays/Strings, and OOP Design**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 3 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 4 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 5 | Lowest Common Ancestor of BST | Medium | Tree / Recursion | [LC 235](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) |
| 6 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| 7 | Word Break | Medium | DP | [LC 139](https://leetcode.com/problems/word-break/) |
| 8 | Validate Binary Search Tree | Medium | Tree / DFS | [LC 98](https://leetcode.com/problems/validate-binary-search-tree/) |
| 9 | 3Sum | Medium | Two Pointers | [LC 15](https://leetcode.com/problems/3sum/) |
| 10 | Rotting Oranges | Medium | BFS | [LC 994](https://leetcode.com/problems/rotting-oranges/) |
| 11 | Product of Array Except Self | Medium | Prefix/Suffix | [LC 238](https://leetcode.com/problems/product-of-array-except-self/) |
| 12 | Group Anagrams | Medium | HashMap / Sorting | [LC 49](https://leetcode.com/problems/group-anagrams/) |
| 13 | Min Stack | Medium | Stack / Design | [LC 155](https://leetcode.com/problems/min-stack/) |
| 14 | Reorder Data in Log Files | Medium | String / Sorting | [LC 937](https://leetcode.com/problems/reorder-data-in-log-files/) |
| 15 | K Closest Points to Origin | Medium | Heap / QuickSelect | [LC 973](https://leetcode.com/problems/k-closest-points-to-origin/) |
| 16 | Word Ladder | Hard | BFS | [LC 127](https://leetcode.com/problems/word-ladder/) |
| 17 | Sliding Window Maximum | Hard | Monotonic Deque | [LC 239](https://leetcode.com/problems/sliding-window-maximum/) |
| 18 | Meeting Rooms II | Medium | Intervals / Heap | [LC 253](https://leetcode.com/problems/meeting-rooms-ii/) |

---

## META (FACEBOOK / INSTAGRAM)

Arrays/Strings dominate (~40%). Practical recursion, graph traversal, and tree DFS/BFS.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Valid Palindrome II | Easy | Two Pointers | [LC 680](https://leetcode.com/problems/valid-palindrome-ii/) |
| 2 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 3 | Binary Tree Right Side View | Medium | BFS / Tree | [LC 199](https://leetcode.com/problems/binary-tree-right-side-view/) |
| 4 | Random Pick with Weight | Medium | Prefix Sum / Binary Search | [LC 528](https://leetcode.com/problems/random-pick-with-weight/) |
| 5 | Subarray Sum Equals K | Medium | Prefix Sum / HashMap | [LC 560](https://leetcode.com/problems/subarray-sum-equals-k/) |
| 6 | Lowest Common Ancestor of Binary Tree | Medium | Tree / DFS | [LC 236](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) |
| 7 | Vertical Order Traversal of Binary Tree | Hard | Tree / BFS | [LC 987](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/) |
| 8 | Diameter of Binary Tree | Easy | Tree / DFS | [LC 543](https://leetcode.com/problems/diameter-of-binary-tree/) |
| 9 | Clone Graph | Medium | BFS / DFS / Graph | [LC 133](https://leetcode.com/problems/clone-graph/) |
| 10 | Add Strings | Easy | String / Math | [LC 415](https://leetcode.com/problems/add-strings/) |
| 11 | Simplify Path | Medium | Stack / String | [LC 71](https://leetcode.com/problems/simplify-path/) |
| 12 | Move Zeroes | Easy | Two Pointers | [LC 283](https://leetcode.com/problems/move-zeroes/) |
| 13 | Minimum Remove to Make Valid Parentheses | Medium | Stack / String | [LC 1249](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/) |
| 14 | Accounts Merge | Medium | Union-Find / DFS | [LC 721](https://leetcode.com/problems/accounts-merge/) |
| 15 | Alien Dictionary | Hard | Topological Sort | [LC 269](https://leetcode.com/problems/alien-dictionary/) |
| 16 | Range Sum of BST | Easy | Tree / DFS | [LC 938](https://leetcode.com/problems/range-sum-of-bst/) |
| 17 | Nested List Weight Sum | Medium | DFS / Recursion | [LC 339](https://leetcode.com/problems/nested-list-weight-sum/) |
| 18 | Buildings With an Ocean View | Medium | Monotonic Stack | [LC 1762](https://leetcode.com/problems/buildings-with-an-ocean-view/) |

---

## MICROSOFT

Balanced across all topics. Clean code & communication weighted heavily.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | Reverse Linked List | Easy | Linked List | [LC 206](https://leetcode.com/problems/reverse-linked-list/) |
| 3 | Add Two Numbers | Medium | Linked List | [LC 2](https://leetcode.com/problems/add-two-numbers/) |
| 4 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 5 | String to Integer (atoi) | Medium | String / Parsing | [LC 8](https://leetcode.com/problems/string-to-integer-atoi/) |
| 6 | Spiral Matrix | Medium | Array / Simulation | [LC 54](https://leetcode.com/problems/spiral-matrix/) |
| 7 | Set Matrix Zeroes | Medium | Array / In-place | [LC 73](https://leetcode.com/problems/set-matrix-zeroes/) |
| 8 | Binary Tree Maximum Path Sum | Hard | Tree / DFS | [LC 124](https://leetcode.com/problems/binary-tree-maximum-path-sum/) |
| 9 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 10 | Course Schedule | Medium | Topological Sort / Graph | [LC 207](https://leetcode.com/problems/course-schedule/) |
| 11 | Min Stack | Medium | Stack / Design | [LC 155](https://leetcode.com/problems/min-stack/) |
| 12 | Serialize and Deserialize Binary Tree | Hard | Tree / DFS | [LC 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) |
| 13 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 14 | Group Anagrams | Medium | HashMap | [LC 49](https://leetcode.com/problems/group-anagrams/) |
| 15 | Coin Change | Medium | DP | [LC 322](https://leetcode.com/problems/coin-change/) |

---

## APPLE

Fundamentals-heavy. Clean code, edge cases, and practical problem solving.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | Valid Parentheses | Easy | Stack | [LC 20](https://leetcode.com/problems/valid-parentheses/) |
| 3 | Merge Two Sorted Lists | Easy | Linked List | [LC 21](https://leetcode.com/problems/merge-two-sorted-lists/) |
| 4 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 5 | Container With Most Water | Medium | Two Pointers | [LC 11](https://leetcode.com/problems/container-with-most-water/) |
| 6 | Search in Rotated Sorted Array | Medium | Binary Search | [LC 33](https://leetcode.com/problems/search-in-rotated-sorted-array/) |
| 7 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| 8 | Decode Ways | Medium | DP | [LC 91](https://leetcode.com/problems/decode-ways/) |
| 9 | Number of 1 Bits | Easy | Bit Manipulation | [LC 191](https://leetcode.com/problems/number-of-1-bits/) |
| 10 | Roman to Integer | Easy | String / HashMap | [LC 13](https://leetcode.com/problems/roman-to-integer/) |
| 11 | Letter Combinations of Phone Number | Medium | Backtracking | [LC 17](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) |
| 12 | Kth Largest Element in an Array | Medium | Heap / QuickSelect | [LC 215](https://leetcode.com/problems/kth-largest-element-in-an-array/) |

---

## NETFLIX

Focus on **Graphs, DP, and Streaming/Design** patterns.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 2 | Merge K Sorted Lists | Hard | Heap | [LC 23](https://leetcode.com/problems/merge-k-sorted-lists/) |
| 3 | Graph Valid Tree | Medium | Graph / Union-Find | [LC 261](https://leetcode.com/problems/graph-valid-tree/) |
| 4 | Clone Graph | Medium | BFS / DFS | [LC 133](https://leetcode.com/problems/clone-graph/) |
| 5 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| 6 | Word Search II | Hard | Trie / Backtracking | [LC 212](https://leetcode.com/problems/word-search-ii/) |
| 7 | Find Median from Data Stream | Hard | Heap (Two Heaps) | [LC 295](https://leetcode.com/problems/find-median-from-data-stream/) |
| 8 | Longest Consecutive Sequence | Medium | HashSet | [LC 128](https://leetcode.com/problems/longest-consecutive-sequence/) |
| 9 | Top K Frequent Elements | Medium | Heap / Bucket Sort | [LC 347](https://leetcode.com/problems/top-k-frequent-elements/) |
| 10 | Design Hit Counter | Medium | Design / Queue | [LC 362](https://leetcode.com/problems/design-hit-counter/) |

---

## UBER / LYFT

Heavy on **Arrays, Graphs, BFS/DFS, and Sliding Window**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 2 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 3 | 3Sum | Medium | Two Pointers | [LC 15](https://leetcode.com/problems/3sum/) |
| 4 | Word Search | Medium | Backtracking / DFS | [LC 79](https://leetcode.com/problems/word-search/) |
| 5 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 6 | Course Schedule | Medium | Topological Sort | [LC 207](https://leetcode.com/problems/course-schedule/) |
| 7 | Task Scheduler | Medium | Greedy / Heap | [LC 621](https://leetcode.com/problems/task-scheduler/) |
| 8 | Meeting Rooms II | Medium | Intervals / Heap | [LC 253](https://leetcode.com/problems/meeting-rooms-ii/) |
| 9 | Serialize and Deserialize Binary Tree | Hard | Tree / DFS | [LC 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) |
| 10 | Trapping Rain Water | Hard | Two Pointers / Stack | [LC 42](https://leetcode.com/problems/trapping-rain-water/) |
| 11 | Shortest Path in Binary Matrix | Medium | BFS | [LC 1091](https://leetcode.com/problems/shortest-path-in-binary-matrix/) |
| 12 | Design Tic-Tac-Toe | Medium | Design / Array | [LC 348](https://leetcode.com/problems/design-tic-tac-toe/) |

---

## STRIPE

Focus on **String parsing, Rate limiting logic, and Clean Design**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 2 | Rate Limiter (Custom) | Medium | Design / Sliding Window | — (custom) |
| 3 | Group Anagrams | Medium | HashMap | [LC 49](https://leetcode.com/problems/group-anagrams/) |
| 4 | Valid Parentheses | Easy | Stack | [LC 20](https://leetcode.com/problems/valid-parentheses/) |
| 5 | Basic Calculator II | Medium | Stack / String | [LC 227](https://leetcode.com/problems/basic-calculator-ii/) |
| 6 | Text Justification | Hard | String / Greedy | [LC 68](https://leetcode.com/problems/text-justification/) |
| 7 | Serialize and Deserialize Binary Tree | Hard | Tree / DFS | [LC 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) |
| 8 | Design Hit Counter | Medium | Design / Queue | [LC 362](https://leetcode.com/problems/design-hit-counter/) |
| 9 | Time Based Key-Value Store | Medium | Design / Binary Search | [LC 981](https://leetcode.com/problems/time-based-key-value-store/) |
| 10 | Integer to English Words | Hard | String / Recursion | [LC 273](https://leetcode.com/problems/integer-to-english-words/) |

---

## LINKEDIN

Focus on **Graphs, Trees, and Design** patterns.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Nested List Weight Sum | Medium | DFS / Recursion | [LC 339](https://leetcode.com/problems/nested-list-weight-sum/) |
| 2 | Max Stack | Hard | Design / DLL + TreeMap | [LC 716](https://leetcode.com/problems/max-stack/) |
| 3 | Shortest Word Distance | Easy | Array | [LC 243](https://leetcode.com/problems/shortest-word-distance/) |
| 4 | All O'one Data Structure | Hard | Design / HashMap + DLL | [LC 432](https://leetcode.com/problems/all-oone-data-structure/) |
| 5 | Isomorphic Strings | Easy | HashMap | [LC 205](https://leetcode.com/problems/isomorphic-strings/) |
| 6 | Maximum Product Subarray | Medium | DP | [LC 152](https://leetcode.com/problems/maximum-product-subarray/) |
| 7 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 8 | Can Place Flowers | Easy | Greedy / Array | [LC 605](https://leetcode.com/problems/can-place-flowers/) |
| 9 | Permutations | Medium | Backtracking | [LC 46](https://leetcode.com/problems/permutations/) |
| 10 | Valid Number | Hard | String / State Machine | [LC 65](https://leetcode.com/problems/valid-number/) |

---

## TWITTER (X)

Focus on **Arrays, HashMap, and practical string problems**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Design Twitter | Medium | Design / Heap | [LC 355](https://leetcode.com/problems/design-twitter/) |
| 2 | Top K Frequent Words | Medium | Heap / HashMap | [LC 692](https://leetcode.com/problems/top-k-frequent-words/) |
| 3 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 4 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 5 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 6 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 7 | Valid Anagram | Easy | HashMap | [LC 242](https://leetcode.com/problems/valid-anagram/) |
| 8 | Group Anagrams | Medium | HashMap | [LC 49](https://leetcode.com/problems/group-anagrams/) |

---

## FLIPKART

Machine coding round is unique to Flipkart. DSA rounds are Medium-Hard.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 2 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 3 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 4 | Course Schedule | Medium | Topological Sort | [LC 207](https://leetcode.com/problems/course-schedule/) |
| 5 | Binary Tree Level Order Traversal | Medium | BFS / Tree | [LC 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) |
| 6 | Coin Change | Medium | DP | [LC 322](https://leetcode.com/problems/coin-change/) |
| 7 | Sort Colors | Medium | Two Pointers (Dutch Flag) | [LC 75](https://leetcode.com/problems/sort-colors/) |
| 8 | Sliding Window Maximum | Hard | Monotonic Deque | [LC 239](https://leetcode.com/problems/sliding-window-maximum/) |
| 9 | Shortest Path in Graph | Medium | BFS / Dijkstra | [LC 743](https://leetcode.com/problems/network-delay-time/) |
| 10 | Partition Labels | Medium | Greedy / Two Pointers | [LC 763](https://leetcode.com/problems/partition-labels/) |

### Flipkart Machine Coding Round
- 90 min, must use **Java**
- Build a working app from scratch (e.g., Splitwise, Parking Lot, Cab Booking)
- In-memory only (HashMap, ArrayList, HashSet)
- Tests: OOP, design patterns, multithreading, clean code

---

## SWIGGY / ZOMATO

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Sliding Window Maximum | Hard | Monotonic Deque | [LC 239](https://leetcode.com/problems/sliding-window-maximum/) |
| 2 | Shortest Path in Weighted Graph | Medium | Dijkstra / BFS | [LC 743](https://leetcode.com/problems/network-delay-time/) |
| 3 | Count Complete Binary Trees | Medium | Tree / DFS | [LC 222](https://leetcode.com/problems/count-complete-tree-nodes/) |
| 4 | Partition Array Into Subarrays | Medium | Greedy | [LC 2294](https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/) |
| 5 | Longest Subsequence from Strings | Medium | DP / Two Pointers | [LC 1143](https://leetcode.com/problems/longest-common-subsequence/) |
| 6 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 7 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 8 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |

---

## PAYTM

Focus on **fintech fundamentals** — payments, wallets, transactions. DSA is Easy-Medium.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | Coin Change | Medium | DP | [LC 322](https://leetcode.com/problems/coin-change/) |
| 3 | Detect Cycle in Linked List | Easy | Fast & Slow Pointers | [LC 141](https://leetcode.com/problems/linked-list-cycle/) |
| 4 | Valid Palindrome | Easy | Two Pointers | [LC 125](https://leetcode.com/problems/valid-palindrome/) |
| 5 | Merge Sort (Implement) | Medium | Divide & Conquer | — |
| 6 | Missing Number | Easy | Math / XOR | [LC 268](https://leetcode.com/problems/missing-number/) |
| 7 | First Missing Positive | Hard | Array / In-place | [LC 41](https://leetcode.com/problems/first-missing-positive/) |
| 8 | Validate BST | Medium | Tree / DFS | [LC 98](https://leetcode.com/problems/validate-binary-search-tree/) |
| 9 | Convert Sorted Array to BST | Easy | Tree / Recursion | [LC 108](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/) |
| 10 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 11 | Binary Search | Easy | Binary Search | [LC 704](https://leetcode.com/problems/binary-search/) |
| 12 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |

### Paytm Prep Tips
- HackerRank OA: 2 problems (Easy/Medium) + MCQs (DBMS, OS, OOPs).
- Core CS round is common — be ready for ACID, indexing, normalization.
- Android roles: expect lifecycle, launch modes, Context questions.

---

## PHONEPE

Heavy on **fintech system concepts** alongside Medium DSA. Locking, consistency, and API design matter.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 3 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 4 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 5 | Valid Parentheses | Easy | Stack | [LC 20](https://leetcode.com/problems/valid-parentheses/) |
| 6 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 7 | Coin Change | Medium | DP | [LC 322](https://leetcode.com/problems/coin-change/) |
| 8 | Binary Tree Level Order Traversal | Medium | BFS / Tree | [LC 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) |
| 9 | Serialize and Deserialize Binary Tree | Hard | Tree / DFS | [LC 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) |
| 10 | Top K Frequent Elements | Medium | Heap / Bucket Sort | [LC 347](https://leetcode.com/problems/top-k-frequent-elements/) |

### PhonePe Prep Tips
- 4-5 rounds: OA → DSA → System Design → Domain → Behavioral.
- Expect questions on optimistic vs pessimistic locking, idempotency, REST vs gRPC.
- Fintech domain: PCI-DSS, encryption, tokenization come up in SD round.

---

## RAZORPAY

62+ DSA questions tracked. OA has Easy + Medium + Hard. Focus on **arrays, strings, and clean code**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | 3Sum | Medium | Two Pointers | [LC 15](https://leetcode.com/problems/3sum/) |
| 3 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 4 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 5 | Group Anagrams | Medium | HashMap | [LC 49](https://leetcode.com/problems/group-anagrams/) |
| 6 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| 7 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 8 | Word Break | Medium | DP | [LC 139](https://leetcode.com/problems/word-break/) |
| 9 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 10 | Validate BST | Medium | Tree / DFS | [LC 98](https://leetcode.com/problems/validate-binary-search-tree/) |

### Razorpay Prep Tips
- OA: 3 problems (easy, medium, hard) + 15 MCQs (DBMS, OS, OOPs).
- Hiring manager round includes array/algo questions + deep project discussion.
- Payment domain knowledge is a plus — idempotency, double-spend prevention.

---

## ZEPTO / BLINKIT (QUICK COMMERCE)

Medium-Hard DSA. Unique focus on **recursion, permutations, and tree traversals**. Referral-driven hiring.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Permutations | Medium | Backtracking | [LC 46](https://leetcode.com/problems/permutations/) |
| 2 | Binary Search (Recursive Variant) | Easy | Binary Search / Recursion | [LC 704](https://leetcode.com/problems/binary-search/) |
| 3 | Best Team With No Conflicts | Hard | DP / Sorting | [LC 1626](https://leetcode.com/problems/best-team-with-no-conflicts/) |
| 4 | Binary Tree Postorder Traversal (Iterative) | Medium | Tree / Stack | [LC 145](https://leetcode.com/problems/binary-tree-postorder-traversal/) |
| 5 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 6 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 7 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 8 | Sliding Window Maximum | Hard | Monotonic Deque | [LC 239](https://leetcode.com/problems/sliding-window-maximum/) |
| 9 | Course Schedule | Medium | Topological Sort | [LC 207](https://leetcode.com/problems/course-schedule/) |
| 10 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |

### Zepto/Blinkit Prep Tips
- 3 rounds: DSA (1.5h) → System Design (1.5h) → Culture Fit (30m).
- Must write O(N) solutions — brute force gets rejected.
- SD round covers inventory systems, cart design, quick-commerce delivery.
- Blinkit is heavily referral-driven — reach out to employees.

---

## ZETA

Hardest among Indian fintechs — **97% Medium/Hard** (34% Hard, 63% Medium). DP-heavy.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Longest Common Subsequence | Medium | 2D DP | [LC 1143](https://leetcode.com/problems/longest-common-subsequence/) |
| 2 | Edit Distance | Medium | 2D DP | [LC 72](https://leetcode.com/problems/edit-distance/) |
| 3 | 0/1 Knapsack | Medium | DP | — (classic) |
| 4 | Longest Palindromic Substring | Medium | DP / Expand Around Center | [LC 5](https://leetcode.com/problems/longest-palindromic-substring/) |
| 5 | Trapping Rain Water | Hard | Two Pointers / Stack | [LC 42](https://leetcode.com/problems/trapping-rain-water/) |
| 6 | Word Break | Medium | DP | [LC 139](https://leetcode.com/problems/word-break/) |
| 7 | Merge K Sorted Lists | Hard | Heap | [LC 23](https://leetcode.com/problems/merge-k-sorted-lists/) |
| 8 | Subarray Sum Equals K | Medium | Prefix Sum / HashMap | [LC 560](https://leetcode.com/problems/subarray-sum-equals-k/) |
| 9 | Coin Change | Medium | DP | [LC 322](https://leetcode.com/problems/coin-change/) |
| 10 | Minimum Window Substring | Hard | Sliding Window | [LC 76](https://leetcode.com/problems/minimum-window-substring/) |

### Zeta Prep Tips
- Phone screen → 2-3 coding questions → take-home assignment (1 week) → SD + Behavioral.
- **DP is king** — 6-week prep minimum. Start with 1D, progress to 2D, then hard combos.
- Kafka, Spark, AWS knowledge helps for system rounds.
- 50%+ practice should be Hard problems by week 5.

---

## MEESHO

1.7% selection rate. OA eliminates most — need 2.5+ correct out of 3. Focus on **optimization and edge cases**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | Best Time to Buy and Sell Stock | Easy | Array / Greedy | [LC 121](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) |
| 3 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 4 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 5 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 6 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| 7 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 8 | Coin Change | Medium | DP | [LC 322](https://leetcode.com/problems/coin-change/) |
| 9 | Top K Frequent Elements | Medium | Heap / Bucket Sort | [LC 347](https://leetcode.com/problems/top-k-frequent-elements/) |
| 10 | Valid Parentheses | Easy | Stack | [LC 20](https://leetcode.com/problems/valid-parentheses/) |

### Meesho Prep Tips
- 10,000+ applicants per role. OA is the bottleneck.
- Code quality matters as much as correctness.
- E-commerce domain: think cart, inventory, recommendation.

---

## DREAM11

4 rounds over ~7 days. Targets 3-6 years experience for SDE-2.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | 3Sum | Medium | Two Pointers | [LC 15](https://leetcode.com/problems/3sum/) |
| 2 | Minimum Path Sum | Medium | 2D DP | [LC 64](https://leetcode.com/problems/minimum-path-sum/) |
| 3 | Gas Station | Medium | Greedy | [LC 134](https://leetcode.com/problems/gas-station/) |
| 4 | Partition Equal Subset Sum | Medium | DP / Knapsack | [LC 416](https://leetcode.com/problems/partition-equal-subset-sum/) |
| 5 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 6 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 7 | Course Schedule | Medium | Topological Sort | [LC 207](https://leetcode.com/problems/course-schedule/) |
| 8 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |

### Dream11 Prep Tips
- Coding (45m) → System Design (60m) → Behavioral (45m) → Hiring Manager (30m).
- Fantasy sports domain: think real-time scoring, leaderboards, concurrent contests.

---

## CRED / GROWW

Clean code culture. Medium DSA with strong emphasis on **design thinking and product sense**.

| # | Problem | Difficulty | Pattern | LeetCode |
|---|---------|-----------|---------|----------|
| 1 | LRU Cache | Medium | Design / HashMap + DLL | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 2 | Two Sum | Easy | HashMap | [LC 1](https://leetcode.com/problems/two-sum/) |
| 3 | Longest Substring Without Repeating Characters | Medium | Sliding Window | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 4 | Merge Intervals | Medium | Intervals / Sorting | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 5 | Number of Islands | Medium | DFS / BFS | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 6 | Valid Parentheses | Easy | Stack | [LC 20](https://leetcode.com/problems/valid-parentheses/) |
| 7 | Coin Change | Medium | DP | [LC 322](https://leetcode.com/problems/coin-change/) |
| 8 | Maximum Subarray | Medium | DP / Kadane's | [LC 53](https://leetcode.com/problems/maximum-subarray/) |

### CRED/Groww Prep Tips
- CRED: machine coding round is common — build a working system in 90 min.
- Groww: fintech domain — portfolio tracking, real-time stock updates, transactions.
- Both value clean code, SOLID principles, and design patterns heavily.

---

## CROSS-COMPANY: TOP 20 MOST UNIVERSAL DSA QUESTIONS

These appear at **almost every** company. Solve these first.

| # | Problem | Difficulty | Pattern | Companies | LeetCode |
|---|---------|-----------|---------|-----------|----------|
| 1 | Two Sum | Easy | HashMap | All | [LC 1](https://leetcode.com/problems/two-sum/) |
| 2 | LRU Cache | Medium | Design | All | [LC 146](https://leetcode.com/problems/lru-cache/) |
| 3 | Merge Intervals | Medium | Intervals | All | [LC 56](https://leetcode.com/problems/merge-intervals/) |
| 4 | Number of Islands | Medium | DFS/BFS | All | [LC 200](https://leetcode.com/problems/number-of-islands/) |
| 5 | Longest Substring Without Repeating Characters | Medium | Sliding Window | All | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) |
| 6 | Maximum Subarray | Medium | DP/Kadane's | All | [LC 53](https://leetcode.com/problems/maximum-subarray/) |
| 7 | Valid Parentheses | Easy | Stack | All | [LC 20](https://leetcode.com/problems/valid-parentheses/) |
| 8 | 3Sum | Medium | Two Pointers | Amazon, Uber, Meta | [LC 15](https://leetcode.com/problems/3sum/) |
| 9 | Course Schedule | Medium | Topological Sort | Google, Uber, Flipkart | [LC 207](https://leetcode.com/problems/course-schedule/) |
| 10 | Word Break | Medium | DP | Google, Amazon | [LC 139](https://leetcode.com/problems/word-break/) |
| 11 | Group Anagrams | Medium | HashMap | Amazon, Microsoft, Stripe | [LC 49](https://leetcode.com/problems/group-anagrams/) |
| 12 | Coin Change | Medium | DP | Microsoft, Flipkart | [LC 322](https://leetcode.com/problems/coin-change/) |
| 13 | Top K Frequent Elements | Medium | Heap | Walmart, Netflix, Twitter | [LC 347](https://leetcode.com/problems/top-k-frequent-elements/) |
| 14 | Serialize and Deserialize Binary Tree | Hard | Tree/DFS | Google, Microsoft, Uber | [LC 297](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) |
| 15 | Merge K Sorted Lists | Hard | Heap | Google, Netflix | [LC 23](https://leetcode.com/problems/merge-k-sorted-lists/) |
| 16 | Trapping Rain Water | Hard | Two Pointers | Google, Uber | [LC 42](https://leetcode.com/problems/trapping-rain-water/) |
| 17 | Find Median from Data Stream | Hard | Two Heaps | Walmart, Netflix | [LC 295](https://leetcode.com/problems/find-median-from-data-stream/) |
| 18 | Reverse Linked List | Easy | Linked List | Microsoft, Apple | [LC 206](https://leetcode.com/problems/reverse-linked-list/) |
| 19 | Binary Tree Level Order Traversal | Medium | BFS/Tree | Walmart, Flipkart | [LC 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) |
| 20 | Sliding Window Maximum | Hard | Monotonic Deque | Amazon, Flipkart, Swiggy | [LC 239](https://leetcode.com/problems/sliding-window-maximum/) |

---

## PATTERN FREQUENCY BY COMPANY

```
                    FAANG & GLOBAL                         INDIAN COMPANIES
Pattern           Google Amazon Meta  MSFT  Walmart Uber  Paytm PhonePe Razorpay Zepto Zeta  Flipkart Meesho
──────────────────────────────────────────────────────────────────────────────────────────────────────────────
Arrays/Strings    ███░░  ████░  █████ ████░ ████░   ████░ ████░ ████░   ████░    ███░░ ████░ ████░    ████░
Trees/BST         ███░░  █████  ████░ ████░ ███░░   ███░░ ███░░ ███░░   ███░░    ███░░ ██░░░ ███░░    ██░░░
Graphs            █████  ███░░  ███░░ ███░░ ██░░░   ████░ ██░░░ ██░░░   ██░░░    ███░░ ██░░░ ███░░    ██░░░
Dynamic Prog.     █████  ███░░  ██░░░ ███░░ ████░   ██░░░ ███░░ ███░░   ███░░    ███░░ █████ ███░░    ███░░
Two Pointers      ███░░  ███░░  ████░ ███░░ ███░░   ████░ ███░░ ██░░░   ███░░    ██░░░ ██░░░ ███░░    ██░░░
Sliding Window    ███░░  ███░░  ███░░ ███░░ ███░░   ████░ ██░░░ ███░░   ███░░    ███░░ ████░ ███░░    ███░░
Heap/PQ           ████░  ███░░  ██░░░ ██░░░ ████░   ███░░ ██░░░ ███░░   ██░░░    ██░░░ ███░░ ██░░░    ██░░░
Binary Search     ████░  ██░░░  ██░░░ ██░░░ ██░░░   ██░░░ ███░░ ██░░░   ██░░░    ███░░ ██░░░ ██░░░    ██░░░
Backtracking      ████░  ██░░░  ██░░░ ██░░░ ███░░   ███░░ ██░░░ ██░░░   ██░░░    ███░░ ██░░░ ██░░░    ██░░░
Stack             ███░░  ███░░  ███░░ ███░░ ██░░░   ██░░░ ██░░░ ██░░░   ██░░░    ██░░░ ██░░░ ██░░░    ██░░░
Design (DS)       ███░░  ███░░  ██░░░ ███░░ █████   ██░░░ ███░░ ███░░   ███░░    ███░░ ███░░ █████    ██░░░
```

---

## PATTERN REFERENCE (LOCAL NOTES)

| Pattern | Your Notes File |
|---------|-----------------|
| Two Pointers | `notes/Two Pointers.txt` |
| Sliding Window | `notes/Sliding Window.txt` |
| Prefix Sum | `notes/Prefix Sum.txt` + `notes/Prefix Sum Hashmap.txt` |
| Binary Search | `notes/Binary Search.txt` |
| Linked List | `notes/Linked List.txt` |
| Tree Patterns | `notes/Tree Patterns.txt` |
| Graph Algorithms | `notes/Graph Algorithms.txt` |
| Dynamic Programming | `notes/Dynamic Programming.txt` |
| Backtracking | `notes/Backtracking.txt` |
| Greedy Algorithms | `notes/Greedy Algorithms.txt` |
| Heap & Kth Problems | `notes/Heap & Kth Problems.txt` |
| Monotonic Stack | `notes/Monotonic Stack.txt` |
| Intervals | `notes/Intervals.txt` |
| String Patterns | `notes/String Patterns.txt` |
| Hashmap Patterns | `notes/Hashmap Patterns.txt` |
| Advanced DS Patterns | `notes/Advanced DS Patterns.txt` |
| Sliding Window vs Prefix Sum | `notes/Sliding Window vs Prefix Sum - Decision Guide.txt` |
| Combinatorics | `notes/Combinatorics - Complete Techniques Guide.txt` |
| Queue | `notes/Queue.txt` |
| STL Reference | `notes/STL Quick Reference.txt` |

---

*Last updated: Feb 2026*
*Sources: LeetCode Discuss, Exponent, CodingKaro, GeeksForGeeks, DSAPrep.dev, InterviewPilot, Glassdoor, AmbitionBox, Prepfully, PlacementPreparation.io*
