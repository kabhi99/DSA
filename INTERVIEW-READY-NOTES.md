# DSA Interview Notes — Prioritized by Probability

> **How to use**: Patterns are ranked by how often they appear in coding interviews. Tier 1 patterns show up in **almost every** interview. Master Tier 1 + 2 first — that covers ~85% of interview questions.

---

# TIER 1 — CORE PATTERNS (Asked in 90%+ Interviews)

These are non-negotiable. You will face multiple Tier 1 patterns in every coding interview.

---

## 1. Arrays + Hashmaps [P: 95%]

**One-liner**: The foundation. 40%+ of all interview problems involve arrays with hashmap lookups.

### Pattern A: Frequency Counting
```cpp
unordered_map<int, int> freq;
for (auto x : nums) freq[x]++;
```
**Use for**: Most frequent element, first unique, check anagrams, duplicate detection

### Pattern B: Complement/Pair Lookup (Two Sum)
```cpp
unordered_map<int, int> seen;  // value -> index
for (int i = 0; i < n; i++) {
    int complement = target - nums[i];
    if (seen.count(complement)) return {seen[complement], i};
    seen[nums[i]] = i;  // insert AFTER checking (avoid using same element)
}
```
**Extend to**: 4Sum II — split into (A+B) map, check -(C+D) → O(N²)

### Pattern C: Longest Consecutive Sequence (LC 128)
```cpp
unordered_set<int> s(nums.begin(), nums.end());
for (int num : s) {
    if (!s.count(num - 1)) {  // only start from sequence beginning
        int len = 1;
        while (s.count(num + len)) len++;
        maxLen = max(maxLen, len);
    }
}
```
**Key insight**: Without the `if (!s.count(num-1))` check, this becomes O(N²)

### Pattern D: Group By Key (Group Anagrams)
```cpp
map<string, vector<string>> groups;
for (auto& word : words) {
    string key = word;
    sort(key.begin(), key.end());
    groups[key].push_back(word);
}
```

### Critical Problems
| Problem | Pattern | Complexity |
|---------|---------|-----------|
| Two Sum (LC 1) | Complement lookup | O(N) |
| Contains Duplicate (LC 217) | Set existence | O(N) |
| Group Anagrams (LC 49) | Sort as key | O(NK log K) |
| Longest Consecutive (LC 128) | Set + start detection | O(N) |
| Top K Frequent (LC 347) | Freq map + bucket sort | O(N) |
| Valid Sudoku (LC 36) | State encoding in set | O(1) |

### Pitfalls
- `map[key]` **creates** the key if absent — use `count()` to check first
- Two Sum: check complement BEFORE inserting (avoid using same element twice)
- Longest Consecutive: must skip non-starting elements or it's O(N²)

---

## 2. Two Pointers [P: 95%]

**One-liner**: O(N) traversal of sorted arrays or linked lists. Four core variants cover 90% of problems.

### Pattern A: Opposite Ends (Sorted Array)
```cpp
int left = 0, right = n - 1;
while (left < right) {
    int sum = nums[left] + nums[right];
    if (sum == target) return {left, right};
    else if (sum < target) left++;
    else right--;
}
```
**Use for**: Two Sum II, Container With Most Water, Trapping Rain Water, 3Sum, Valid Palindrome

### Pattern B: Slow & Fast (In-Place Modification)
```cpp
int slow = 0;
for (int fast = 0; fast < n; fast++) {
    if (shouldKeep(nums[fast])) {
        nums[slow++] = nums[fast];
    }
}
// slow = new length
```
**Use for**: Remove Duplicates, Remove Element, Move Zeroes

### Pattern C: Floyd's Cycle Detection (Linked List)
```cpp
ListNode *slow = head, *fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;  // cycle found
}
// To find cycle start: reset slow to head, move both by 1
```

### Pattern D: Merge Two Sorted (Parallel Pointers)
```cpp
int i = 0, j = 0;
while (i < m && j < n) {
    if (a[i] <= b[j]) result.push_back(a[i++]);
    else result.push_back(b[j++]);
}
// DON'T FORGET: append remaining elements
```

### 3Sum Template (LC 15) — Asked Constantly
```cpp
sort(nums.begin(), nums.end());
for (int i = 0; i < n - 2; i++) {
    if (i > 0 && nums[i] == nums[i-1]) continue;  // skip dupes
    int left = i + 1, right = n - 1;
    while (left < right) {
        int sum = nums[i] + nums[left] + nums[right];
        if (sum == 0) {
            result.push_back({nums[i], nums[left], nums[right]});
            while (left < right && nums[left] == nums[left+1]) left++;
            while (left < right && nums[right] == nums[right-1]) right--;
            left++; right--;
        } else if (sum < 0) left++;
        else right--;
    }
}
```

### Dutch National Flag (Sort Colors, LC 75)
```cpp
int lo = 0, mid = 0, hi = n - 1;
while (mid <= hi) {
    if (nums[mid] == 0) swap(nums[lo++], nums[mid++]);
    else if (nums[mid] == 1) mid++;
    else swap(nums[mid], nums[hi--]);  // DON'T advance mid after hi swap!
}
```

### Critical Problems
| Problem | Variant | Key Insight |
|---------|---------|------------|
| Two Sum II (LC 167) | Opposite ends | Sorted array, squeeze inward |
| 3Sum (LC 15) | Sort + opposite ends | Skip duplicates at 3 levels |
| Container With Most Water (LC 11) | Opposite ends | Move the shorter wall |
| Trapping Rain Water (LC 42) | Opposite ends | Track left_max and right_max |
| Remove Duplicates (LC 26) | Slow/Fast | Slow writes unique values |
| Linked List Cycle (LC 141/142) | Floyd's | Fast catches slow in cycle |
| Sort Colors (LC 75) | Dutch National Flag | 3-way partition |

### Pitfalls
- Sort Colors: after swapping with `hi`, do NOT advance `mid` (swapped value unexamined)
- Floyd's: check `fast && fast->next` (not just `fast->next`)
- 3Sum: skip duplicates at the outer loop `(i > 0)` AND inner loop
- Merge sorted: always handle remaining elements after main loop

---

## 3. Sliding Window [P: 95%]

**One-liner**: Maintain a window over contiguous elements. O(N) because each element enters/leaves once.

### The 3 Core Templates

#### Template 1: Variable Window — Find MAXIMUM Length (Non-Shrinkable `if`)
```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    // add nums[right] to window state
    if (windowInvalid()) {
        // remove nums[left] from window state
        left++;
    }
    ans = max(ans, right - left + 1);
}
```
**Use for**: Longest Substring Without Repeating, Longest Repeating Character Replacement, Max Consecutive Ones III

#### Template 2: Variable Window — Find MINIMUM Length / Count (Shrinkable `while`)
```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    // add nums[right] to window state
    while (windowValid()) {  // shrink as much as possible
        ans = min(ans, right - left + 1);
        // remove nums[left] from window state
        left++;
    }
}
```
**Use for**: Minimum Window Substring, Min Size Subarray Sum

#### Template 3: Count ALL Valid Subarrays
```cpp
int left = 0, count = 0;
for (int right = 0; right < n; right++) {
    // add nums[right] to window state
    while (windowInvalid()) {
        // remove nums[left] from window state
        left++;
    }
    count += right - left + 1;  // all subarrays ending at right
}
```

### The "Exactly K" Trick
```
exactly(K) = atMost(K) - atMost(K-1)
```
**Use for**: Subarrays with Exactly K Distinct, Binary Subarrays With Sum

### Sliding Window vs Prefix Sum — Decision in 3 Questions
1. **Has negatives?** → Prefix Sum (sliding window breaks with negatives)
2. **"Exactly K"?** → Prefix Sum (or atMost trick)
3. **Can shrinking left fix invalid window?** → Sliding Window. Otherwise → Prefix Sum

### Critical Problems
| Problem | Template | Key Insight |
|---------|----------|------------|
| Longest Substring Without Repeating (LC 3) | Max length (`if`) | Freq map, shrink when duplicate |
| Min Window Substring (LC 76) | Min length (`while`) | Freq map, track `matched` count |
| Max Consecutive Ones III (LC 1004) | Max length (`if`) | Track zero count ≤ K |
| Subarrays with K Distinct (LC 992) | Exactly K | `atMost(K) - atMost(K-1)` |
| Longest Repeating Replacement (LC 424) | Max length (`if`) | `window_size - max_freq ≤ K` |
| Sliding Window Maximum (LC 239) | Fixed + Monotonic Deque | Decreasing deque of indices |

### Pitfalls
- Counting/Minimum **MUST** use `while` (shrinkable). `if` gives wrong results for these
- Window size = `right - left + 1` (inclusive), NOT `right - left`
- **Negatives break sliding window** for sum problems → must use prefix sum
- Use `long long` for sum/product to avoid overflow

---

## 4. Binary Search [P: 90%]

**One-liner**: O(log N) search on sorted/monotonic data. The "BS on Answer" pattern is the most interview-worthy.

### Template 1: Classic (Find Exact Element)
```cpp
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (nums[mid] == target) return mid;
    else if (nums[mid] < target) lo = mid + 1;
    else hi = mid - 1;
}
return -1;
```

### Template 2: Lower Bound (First Element >= Target)
```cpp
int lo = 0, hi = n;  // hi = n, not n-1
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (nums[mid] < target) lo = mid + 1;
    else hi = mid;  // r = mid (not mid-1)
}
return lo;
```

### Template 3: BS on Answer — MINIMIZE Maximum
```cpp
int lo = MIN_POSSIBLE, hi = MAX_POSSIBLE;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;  // NO +1
    if (canAchieve(mid)) hi = mid;  // try smaller
    else lo = mid + 1;
}
return lo;
```
**Use for**: Koko Eating Bananas, Ship Packages, Split Array Largest Sum

### Template 4: BS on Answer — MAXIMIZE Minimum
```cpp
int lo = MIN_POSSIBLE, hi = MAX_POSSIBLE;
while (lo < hi) {
    int mid = lo + (hi - lo + 1) / 2;  // +1 CRITICAL!
    if (canAchieve(mid)) lo = mid;  // try larger
    else hi = mid - 1;
}
return lo;
```
**Use for**: Magnetic Force, Aggressive Cows, Divide Chocolate

### Golden Rule
> `lo = mid` requires `mid = lo + (hi - lo + 1) / 2` (round up). Without +1 → infinite loop.
> `hi = mid` uses `mid = lo + (hi - lo) / 2` (round down). Safe as-is.

### BS on Answer — Setting Bounds

| Problem Type | `lo` | `hi` |
|-------------|------|------|
| Speed/rate | 1 | max(array) |
| Capacity/split items | max(array) | sum(array) |
| Distance between | 1 | max_pos - min_pos |
| Kth element in matrix | matrix[0][0] | matrix[n-1][n-1] |

### Rotated Sorted Array (LC 33)
```cpp
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (nums[mid] == target) return mid;
    if (nums[lo] <= nums[mid]) {  // left half sorted
        if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
        else lo = mid + 1;
    } else {  // right half sorted
        if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
        else hi = mid - 1;
    }
}
```

### Critical Problems
| Problem | Template | Bounds |
|---------|----------|--------|
| Koko Bananas (LC 875) | Minimize Max | lo=1, hi=max(piles) |
| Ship Packages (LC 1011) | Minimize Max | lo=max(w), hi=sum(w) |
| Split Array (LC 410) | Minimize Max | lo=max, hi=sum |
| Magnetic Force (LC 1552) | Maximize Min | lo=1, hi=max_pos-min_pos |
| Search Rotated (LC 33) | Classic + half-sorted check | — |
| Median Two Arrays (LC 4) | Partition on smaller array | lo=0, hi=m |

### Pitfalls
- **Infinite loop**: `lo = mid` without `+1` in mid calculation
- **lo = 0 vs lo = 1**: Speed/rate can't be 0; distance/value might
- **hi = sum vs hi = max**: Splitting items across groups → sum; one-at-a-time → max
- **Duplicates in rotated**: Degrades to O(N) worst case; shrink both ends
- Ceiling division: `ceil(a/b) = (a + b - 1) / b`

---

## 5. Trees (Binary Tree + BST) [P: 90%]

**One-liner**: DFS (recursive) for most problems. BFS for level-order. Know the templates cold.

### Universal DFS Template
```cpp
int dfs(TreeNode* root) {
    if (!root) return BASE_CASE;
    int left = dfs(root->left);
    int right = dfs(root->right);
    return COMBINE(left, right, root->val);
}
```

### Level Order BFS Template
```cpp
queue<TreeNode*> q;
q.push(root);
while (!q.empty()) {
    int size = q.size();  // snapshot BEFORE inner loop
    for (int i = 0; i < size; i++) {
        TreeNode* node = q.front(); q.pop();
        // process node
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

### Must-Know Patterns

**Max Path Sum (LC 124)** — The "return vs update" trick:
```cpp
int maxSum = INT_MIN;
int dfs(TreeNode* root) {
    if (!root) return 0;
    int left = max(0, dfs(root->left));   // ignore negative paths
    int right = max(0, dfs(root->right));
    maxSum = max(maxSum, left + right + root->val);  // UPDATE global (both branches)
    return max(left, right) + root->val;             // RETURN to parent (one branch)
}
```
Same trick for **Diameter** (LC 543): return height, update global with `left + right`.

**Validate BST (LC 98)**:
```cpp
bool isValid(TreeNode* root, long minVal, long maxVal) {
    if (!root) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValid(root->left, minVal, root->val) &&
           isValid(root->right, root->val, maxVal);
}
```
**Pitfall**: Don't just compare with children — must check against ALL ancestor constraints.

**LCA Binary Tree (LC 236)**:
```cpp
TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lca(root->left, p, q);
    TreeNode* right = lca(root->right, p, q);
    if (left && right) return root;  // split point = LCA
    return left ? left : right;
}
```

**LCA BST (LC 235)** — Use values to guide search:
```cpp
while (root) {
    if (p->val < root->val && q->val < root->val) root = root->left;
    else if (p->val > root->val && q->val > root->val) root = root->right;
    else return root;  // split point
}
```

### Critical Problems
| Problem | Pattern | Key Insight |
|---------|---------|------------|
| Max Depth (LC 104) | DFS `1 + max(left, right)` | Base: null → 0 |
| Balanced Tree (LC 110) | DFS return height or -1 sentinel | -1 means unbalanced |
| Max Path Sum (LC 124) | Return single branch, update global with both | `max(0, child)` ignores negatives |
| Diameter (LC 543) | Return height, update global with `left+right` | Same trick as path sum |
| Validate BST (LC 98) | Pass (min, max) range | Use `LONG_MIN/MAX` |
| LCA (LC 236) | Post-order, bubble up matches | Both found → current is LCA |
| Serialize/Deserialize (LC 297) | Preorder with null markers | Use queue for deserialize |
| Right Side View (LC 199) | BFS, take last of each level | Level order with size snapshot |

### Pitfalls
- **Min Depth**: Must reach a LEAF — if one child is null, must go to the other child
- **Max Path Sum**: Return value (single direction) ≠ update value (complete path through node)
- **Validate BST**: Use `long` for min/max bounds (INT_MIN is a valid node value)
- **Construction from traversals**: Preorder+Inorder → build left then right. Postorder+Inorder → build RIGHT first

---

## 6. Dynamic Programming [P: 90%]

**One-liner**: "Can I solve this using solutions to smaller subproblems?" If yes, it's DP.

### The 6 Most Common DP Patterns

#### Pattern 1: Min/Max Cost to Reach Target
```
dp[i] = min/max(dp[i - cost] + cost) for each option
Base: dp[0] = 0
```
**Problems**: Coin Change, Min Cost Climbing Stairs, Perfect Squares

#### Pattern 2: Count Distinct Ways
```
dp[i] = sum(dp[i - option]) for each option
Base: dp[0] = 1  (not 0!)
```
**Problems**: Climbing Stairs, Unique Paths, Combination Sum IV, Target Sum

#### Pattern 3: DP on Strings (Two Strings)
```
dp[i][j] = depends on s1[i-1] vs s2[j-1] match/mismatch
```
**Problems**: LCS, Edit Distance, Distinct Subsequences

#### Pattern 4: Take/Skip Decision
```
dp[i] = max(take + dp[i-2], skip + dp[i-1])
```
**Problems**: House Robber, Best Time to Buy/Sell Stock

#### Pattern 5: Longest Increasing Subsequence
```
dp[i] = max(dp[j] + 1) where j < i and nums[j] < nums[i]
```
O(N²) basic, O(N log N) with patience sort (binary search on tails array)

#### Pattern 6: Kadane's Algorithm (Max Subarray)
```cpp
int curr = nums[0], maxSum = nums[0];
for (int i = 1; i < n; i++) {
    curr = max(nums[i], curr + nums[i]);  // restart or extend
    maxSum = max(maxSum, curr);
}
```

### Must-Know Templates

**0/1 Knapsack** (items used once):
```cpp
for (int i = 0; i < items; i++)
    for (int w = capacity; w >= weight[i]; w--)  // BACKWARDS to avoid reuse
        dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
```

**Unbounded Knapsack** (items reusable):
```cpp
for (int i = 0; i < items; i++)
    for (int w = weight[i]; w <= capacity; w++)  // FORWARDS (reuse allowed)
        dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
```

**Permutations vs Combinations**:
- Outer loop on TARGET = **permutations** (order matters, like Combination Sum IV)
- Outer loop on ITEMS = **combinations** (order doesn't matter, like Coin Change)

**Interval DP (Merge Intervals)**:
```cpp
for (int len = 2; len <= n; len++)          // MUST loop by length first
    for (int i = 0; i <= n - len; i++) {
        int j = i + len - 1;
        for (int k = i; k < j; k++)
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost);
    }
```
**Problems**: Burst Balloons, Matrix Chain, Merge Stones

### Top-Down to Bottom-Up (7 Steps)
1. Identify state variables → dimensions of DP table
2. Create DP table with proper size
3. Set base cases
4. Determine iteration order (draw dependency arrows!)
5. Convert recurrence from recursion
6. Return the final cell
7. Optimize space if possible (often only need previous row/column)

### Critical Problems
| Problem | Pattern | Key Insight |
|---------|---------|------------|
| Coin Change (LC 322) | Min cost to target | `dp[0]=0`, use `amount+1` not INT_MAX |
| Climbing Stairs (LC 70) | Count ways | `dp[i] = dp[i-1] + dp[i-2]` |
| House Robber (LC 198) | Take/Skip | `dp[i] = max(dp[i-1], dp[i-2]+nums[i])` |
| LCS (LC 1143) | Two strings | Match: `dp[i-1][j-1]+1`, else `max(up, left)` |
| Edit Distance (LC 72) | Two strings | 3 operations: insert, delete, replace |
| LIS (LC 300) | Increasing subsequence | O(N log N) with binary search on tails |
| Partition Equal Subset (LC 416) | 0/1 Knapsack | `target = sum/2`, backwards loop |
| Target Sum (LC 494) | 0/1 Knapsack | Transform: `P = (sum + target) / 2` |
| Burst Balloons (LC 312) | Interval DP | Think of last balloon popped, not first |

### Pitfalls
- `dp[0] = 1` for counting (not 0!)
- `dp[0] = 0` for min cost; use `amount + 1` as infinity (not INT_MAX — overflows on +1)
- Off-by-one: `s1[i-1]` when DP table is 1-indexed
- Wrong iteration order: **draw the dependency arrows** before coding
- Interval DP: MUST loop by length (small intervals before large)
- Palindrome DP: also needs length-based iteration

---

## 7. Graphs (BFS + DFS + Topological Sort) [P: 85%]

**One-liner**: BFS for shortest path (unweighted). DFS for path finding/connectivity. Topo sort for dependencies.

### BFS Template (Shortest Path Unweighted)
```cpp
queue<int> q;
vector<int> dist(n, -1);
q.push(start);
dist[start] = 0;
while (!q.empty()) {
    int node = q.front(); q.pop();
    for (int neighbor : adj[node]) {
        if (dist[neighbor] == -1) {
            dist[neighbor] = dist[node] + 1;
            q.push(neighbor);
        }
    }
}
```

### Multi-Source BFS (Rotting Oranges, 01 Matrix)
```cpp
queue<pair<int,int>> q;
// seed ALL sources at once
for (all sources) q.push(source), dist[source] = 0;
// BFS spreads from all sources simultaneously
```

### DFS Template (Grid)
```cpp
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
void dfs(vector<vector<int>>& grid, int i, int j) {
    if (i < 0 || i >= m || j < 0 || j >= n) return;
    if (grid[i][j] != target) return;
    grid[i][j] = visited_marker;  // mark visited
    for (int d = 0; d < 4; d++)
        dfs(grid, i + dx[d], j + dy[d]);
}
```

### Topological Sort — Kahn's Algorithm (BFS)
```cpp
vector<int> indegree(n, 0);
for (each edge u→v) indegree[v]++;
queue<int> q;
for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);
vector<int> order;
while (!q.empty()) {
    int node = q.front(); q.pop();
    order.push_back(node);
    for (int neighbor : adj[node]) {
        if (--indegree[neighbor] == 0) q.push(neighbor);
    }
}
if (order.size() != n) // CYCLE EXISTS
```
**Use for**: Course Schedule, Build Order, Alien Dictionary

### Union-Find (Disjoint Set Union)
```cpp
vector<int> parent, rank_;
int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);  // path compression
    return parent[x];
}
void unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return;
    if (rank_[px] < rank_[py]) swap(px, py);
    parent[py] = px;
    if (rank_[px] == rank_[py]) rank_[px]++;
}
```
**Use for**: Connected components, redundant connection, accounts merge, MST (Kruskal's)

### Dijkstra (Weighted, Non-Negative Edges)
```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
vector<int> dist(n, INT_MAX);
dist[start] = 0;
pq.push({0, start});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;  // skip outdated
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
}
```

### Cycle Detection
- **Directed graph**: 3-color DFS (WHITE=unvisited, GRAY=in-progress, BLACK=done). Back edge to GRAY = cycle
- **Undirected graph**: DFS with parent tracking, or Union-Find (edge connects same component = cycle)

### Algorithm Selection Guide

| Scenario | Algorithm |
|----------|-----------|
| Shortest path, unweighted | BFS |
| Shortest path, weighted positive | Dijkstra O(E log V) |
| Negative edges | Bellman-Ford O(VE) |
| All pairs shortest path | Floyd-Warshall O(V³) |
| Connected components | DFS / BFS / Union-Find |
| Task ordering | Topological Sort (Kahn's) |
| Cycle detection (directed) | 3-color DFS |
| MST | Kruskal's (sort edges + UF) |

### Critical Problems
| Problem | Algorithm | Key Insight |
|---------|-----------|------------|
| Number of Islands (LC 200) | DFS/BFS on grid | Mark visited, count components |
| Rotting Oranges (LC 994) | Multi-source BFS | All rotten start in queue together |
| Course Schedule (LC 207/210) | Topological Sort | Cycle = can't finish all courses |
| Clone Graph (LC 133) | DFS + hashmap | Map old→new node |
| Network Delay (LC 743) | Dijkstra | max(all distances) = answer |
| Redundant Connection (LC 684) | Union-Find | Edge that connects same component |
| Word Ladder (LC 127) | BFS | Each word is a node, differ by 1 char |

### Pitfalls
- BFS: Mark visited **BEFORE** pushing to queue (not after popping) — avoids duplicate pushes
- Topo sort: `order.size() != n` means cycle exists
- Dijkstra: skip outdated entries (`if (d > dist[u]) continue`)
- Union-Find: always use path compression + union by rank for O(α(N)) ≈ O(1)
- Grid DFS: check bounds BEFORE accessing `grid[i][j]`
- Bellman-Ford with K stops: use temp array to prevent same-round propagation

---

## 8. Strings [P: 85%]

**One-liner**: String problems are array problems with character-specific tricks (ASCII, frequency maps, sorting).

### Most Common String Patterns

**Palindrome Check**:
```cpp
bool isPalin(string& s, int lo, int hi) {
    while (lo < hi) {
        if (s[lo++] != s[hi--]) return false;
    }
    return true;
}
```

**Expand Around Center (Longest Palindromic Substring, LC 5)**:
```cpp
for (int i = 0; i < n; i++) {
    expand(s, i, i);      // odd length
    expand(s, i, i + 1);  // even length
}
void expand(string& s, int lo, int hi) {
    while (lo >= 0 && hi < n && s[lo] == s[hi]) { lo--; hi++; }
    // palindrome is s[lo+1..hi-1]
}
```

**String Hashing (Rabin-Karp)**: For substring matching, repeated substring detection
- Hash = `sum(s[i] * base^i) % MOD`
- Rolling hash: remove left char, add right char in O(1)

### Critical String Problems
| Problem | Technique |
|---------|-----------|
| Valid Palindrome (LC 125) | Two pointers, skip non-alphanumeric |
| Longest Palindromic Substring (LC 5) | Expand around center O(N²) |
| Longest Palindromic Subsequence (LC 516) | DP on strings (reverse + LCS) |
| Group Anagrams (LC 49) | Sort as key + hashmap |
| Longest Common Subsequence (LC 1143) | 2D DP |
| Edit Distance (LC 72) | 2D DP (3 operations) |
| Valid Parentheses (LC 20) | Stack |
| Generate Parentheses (LC 22) | Backtracking with open/close count |

---

# TIER 2 — HIGH-FREQUENCY PATTERNS (Asked 70%+ of the Time)

---

## 9. Backtracking [P: 80%]

**One-liner**: Generate ALL valid solutions by trying, exploring, undoing. Three patterns cover everything.

### The Universal Framework: Try → Explore → Undo
```cpp
void backtrack(state, choices, path, result) {
    if (goalReached) { result.add(path); return; }
    for (choice in choices) {
        if (isValid(choice)) {
            make(choice);           // TRY
            backtrack(next_state);  // EXPLORE
            undo(choice);           // UNDO
        }
    }
}
```

### Pattern A: Subsets (Every State is Valid)
```cpp
void backtrack(int start, vector<int>& path) {
    result.push_back(path);  // add at every step
    for (int i = start; i < n; i++) {
        path.push_back(nums[i]);
        backtrack(i + 1, path);  // i+1 (no reuse)
        path.pop_back();
    }
}
```

### Pattern B: Combinations (Fixed Size K)
```cpp
void backtrack(int start, vector<int>& path) {
    if (path.size() == k) { result.push_back(path); return; }
    for (int i = start; i <= n - (k - path.size()) + 1; i++) {  // pruning!
        path.push_back(i);
        backtrack(i + 1, path);
        path.pop_back();
    }
}
```

### Pattern C: Permutations (Order Matters)
```cpp
void backtrack(vector<bool>& used, vector<int>& path) {
    if (path.size() == n) { result.push_back(path); return; }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = true;
        path.push_back(nums[i]);
        backtrack(used, path);
        path.pop_back();
        used[i] = false;
    }
}
```

### Handling Duplicates (Sort First!)
```cpp
sort(nums.begin(), nums.end());
// Inside the loop:
if (i > start && nums[i] == nums[i-1]) continue;  // Subsets/Combinations: i > start
// For Permutations:
if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
```

### Critical Problems
| Problem | Pattern | Output Size |
|---------|---------|------------|
| Subsets (LC 78) | Subsets | 2^N |
| Subsets II (LC 90) | Subsets + sort + skip dupes | ≤ 2^N |
| Combinations (LC 77) | Combinations | C(N,K) |
| Combination Sum (LC 39) | Combinations (reuse: `i` not `i+1`) | varies |
| Permutations (LC 46) | Permutations | N! |
| N-Queens (LC 51) | Constraint satisfaction | varies |
| Word Search (LC 79) | Grid backtracking | bool |
| Generate Parentheses (LC 22) | Custom: track open/close counts | Catalan(N) |

### Pitfalls
- Duplicates: `i > start` (NOT `i > 0`) for same-level dedup in subsets/combinations
- Reuse allowed → use `i` in recursive call. No reuse → use `i + 1`
- Grid backtracking: MUST restore cell after exploring
- Pruning is essential: remaining elements check, sorted + early termination

---

## 10. Greedy [P: 75%]

**One-liner**: Make the locally optimal choice at each step. Works when local optimum leads to global optimum.

### The Most Asked Greedy Problems

**Interval Scheduling (Non-overlapping Intervals, LC 435)**:
```cpp
sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
    return a[1] < b[1];  // sort by END time
});
int count = 0, prevEnd = INT_MIN;
for (auto& iv : intervals) {
    if (iv[0] >= prevEnd) { prevEnd = iv[1]; }  // no overlap, take it
    else count++;  // overlap, remove this one
}
```

**Jump Game (LC 55)** — Can you reach the end?
```cpp
int farthest = 0;
for (int i = 0; i < n; i++) {
    if (i > farthest) return false;
    farthest = max(farthest, i + nums[i]);
}
return true;
```

**Jump Game II (LC 45)** — Minimum jumps:
```cpp
int jumps = 0, currentEnd = 0, farthest = 0;
for (int i = 0; i < n - 1; i++) {  // n-1, not n!
    farthest = max(farthest, i + nums[i]);
    if (i == currentEnd) { jumps++; currentEnd = farthest; }
}
```

**Task Scheduler (LC 621)** — Formula approach:
```
result = max(n, (maxFreq - 1) * (interval + 1) + countOfMaxFreq)
```

**Gas Station (LC 134)** — Single pass:
```cpp
int totalGas = 0, tank = 0, start = 0;
for (int i = 0; i < n; i++) {
    totalGas += gas[i] - cost[i];
    tank += gas[i] - cost[i];
    if (tank < 0) { start = i + 1; tank = 0; }
}
return totalGas >= 0 ? start : -1;
```

### Greedy vs DP — When Does Greedy Work?
| Greedy Works | Need DP |
|-------------|---------|
| Interval scheduling (sort by end) | 0/1 Knapsack (fractional → greedy OK) |
| Activity selection | Coin Change (non-canonical coins) |
| Jump Game | Edit Distance |
| Huffman coding | LCS/LIS |

**Rule of thumb**: If greedy choice never needs to be reconsidered → greedy. If current choice depends on future choices → DP.

### Critical Problems
| Problem | Strategy | Key Insight |
|---------|----------|------------|
| Non-overlapping Intervals (LC 435) | Sort by end | Keep earliest-ending |
| Merge Intervals (LC 56) | Sort by start | Extend or add new |
| Meeting Rooms II (LC 253) | Sweep line or min-heap | Count max concurrent |
| Jump Game (LC 55) | Track farthest | `i > farthest` = unreachable |
| Task Scheduler (LC 621) | Frequency formula | Math, not simulation |
| Gas Station (LC 134) | Reset start on negative tank | Total gas ≥ total cost → solution exists |
| Candy (LC 135) | Two passes (L→R, R→L) | Satisfy both neighbors |
| Partition Labels (LC 763) | Last occurrence tracking | Extend partition to include all of current chars |

### Pitfalls
- **Merge Intervals**: sort by START. **Non-overlapping**: sort by END. Don't mix these up
- Jump Game II: loop to `n-1` (not `n`) — counting jumps when reaching `currentEnd`
- Meeting Rooms: heap approach — pop if `top <= start` (free the room)
- Greedy doesn't always work → when unsure, check with counterexample

---

## 11. Heap / Priority Queue [P: 75%]

**One-liner**: Efficiently track the max/min element. O(log N) insert/remove, O(1) peek.

### Pattern A: Kth Smallest/Largest
```cpp
// Kth SMALLEST → MAX heap of size K (top = Kth smallest)
priority_queue<int> maxHeap;
for (int num : nums) {
    maxHeap.push(num);
    if (maxHeap.size() > k) maxHeap.pop();
}
return maxHeap.top();
```
**Counter-intuitive**: Kth Smallest uses MAX heap. Kth Largest uses MIN heap.

### Pattern B: Merge K Sorted Lists (LC 23)
```cpp
auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
for (auto list : lists) if (list) pq.push(list);
while (!pq.empty()) {
    auto node = pq.top(); pq.pop();
    // add node to result
    if (node->next) pq.push(node->next);
}
```

### Pattern C: Two Heaps — Median Finder (LC 295)
```cpp
priority_queue<int> lo;                              // max heap (smaller half)
priority_queue<int, vector<int>, greater<int>> hi;   // min heap (larger half)

void addNum(int num) {
    lo.push(num);
    hi.push(lo.top()); lo.pop();   // balance through hi
    if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
}
double findMedian() {
    return lo.size() > hi.size() ? lo.top() : (lo.top() + hi.top()) / 2.0;
}
```

### Pattern D: Meeting Rooms II (LC 253)
```cpp
sort(intervals.begin(), intervals.end());
priority_queue<int, vector<int>, greater<int>> pq; // min heap of end times
for (auto& iv : intervals) {
    if (!pq.empty() && pq.top() <= iv[0]) pq.pop();  // free a room
    pq.push(iv[1]);
}
return pq.size();  // max concurrent rooms
```

### Critical Problems
| Problem | Pattern | Complexity |
|---------|---------|-----------|
| Kth Largest Element (LC 215) | Max heap size K (or quickselect O(N) avg) | O(N log K) |
| Top K Frequent (LC 347) | Freq map + min heap size K | O(N log K) |
| Merge K Sorted (LC 23) | Min heap of K heads | O(N log K) |
| Find Median (LC 295) | Two heaps | O(log N) add |
| Meeting Rooms II (LC 253) | Sort + min heap | O(N log N) |
| Reorganize String (LC 767) | Max heap, always pick most frequent | O(N log A) |

---

## 12. Monotonic Stack [P: 70%]

**One-liner**: Find next/previous greater/smaller element in O(N). Always store INDICES.

### The Four Variants

| Problem | Stack Type | Pop When | Process |
|---------|-----------|----------|---------|
| **Next Greater** | Non-Increasing (decreasing) | `stack_top < current` | INSIDE while (popped element gets answer) |
| **Previous Greater** | Strictly Decreasing | `stack_top <= current` | OUTSIDE while (current element gets answer) |
| **Next Smaller** | Non-Decreasing (increasing) | `stack_top > current` | INSIDE while |
| **Previous Smaller** | Strictly Increasing | `stack_top >= current` | OUTSIDE while |

### Template: Next Greater Element
```cpp
vector<int> nextGreater(n, -1);
stack<int> st;  // store INDICES
for (int i = 0; i < n; i++) {
    while (!st.empty() && nums[st.top()] < nums[i]) {
        nextGreater[st.top()] = nums[i];  // process INSIDE while
        st.pop();
    }
    st.push(i);
}
```

### Largest Rectangle in Histogram (LC 84)
```cpp
stack<int> st;
int maxArea = 0;
for (int i = 0; i <= n; i++) {
    int h = (i == n) ? 0 : heights[i];
    while (!st.empty() && heights[st.top()] > h) {
        int height = heights[st.top()]; st.pop();
        int width = st.empty() ? i : i - st.top() - 1;
        maxArea = max(maxArea, height * width);
    }
    st.push(i);
}
```

### Critical Problems
| Problem | Variant | Key Insight |
|---------|---------|------------|
| Daily Temperatures (LC 739) | Next Greater (distance) | `result = i - st.top()` |
| Next Greater Element I (LC 496) | Next Greater + hashmap | Precompute for nums2 |
| Largest Rectangle (LC 84) | Next+Prev Smaller | Width between smaller boundaries |
| Trapping Rain Water (LC 42) | Monotonic stack OR two pointers | Pop valley, compute water |
| Stock Span (LC 901) | Previous Greater (distance) | Online query version |
| Remove K Digits (LC 402) | Increasing stack | Remove larger digits from left |

### Memory Aid
> **GREATER → Decreasing stack** (pop smaller elements)
> **SMALLER → Increasing stack** (pop greater elements)

---

## 13. Prefix Sum [P: 70%]

**One-liner**: Precompute cumulative sums. Any subarray sum in O(1): `psum[j] - psum[i]`.

### Core Template: Subarray Sum Equals K (LC 560)
```cpp
unordered_map<int, int> mp;
mp[0] = 1;  // empty prefix
int psum = 0, count = 0;
for (int num : nums) {
    psum += num;
    if (mp.count(psum - k)) count += mp[psum - k];  // CHECK first
    mp[psum]++;  // THEN update
}
return count;
```

### Variant: Maximum Length Subarray with Sum K
```cpp
unordered_map<int, int> mp;
mp[0] = -1;  // index before array starts
int psum = 0, maxLen = 0;
for (int i = 0; i < n; i++) {
    psum += nums[i];
    if (mp.count(psum - k)) maxLen = max(maxLen, i - mp[psum - k]);
    if (!mp.count(psum)) mp[psum] = i;  // DON'T overwrite (keep earliest)
}
```

### Modulo Variant: Subarrays Divisible by K (LC 974)
```cpp
psum = ((psum + num) % k + k) % k;  // handle negative remainders in C++
```

### Brilliant Transformations
| Problem | Transformation | Then |
|---------|---------------|------|
| Equal 0s and 1s (LC 525) | Replace 0 → -1 | Subarray sum = 0 |
| K odd numbers (LC 1248) | Replace odd → 1, even → 0 | Subarray sum = K |
| Remove from edges (LC 1658) | Find max middle with `sum = total - x` | Max length subarray |

### 2D Prefix Sum
```cpp
// Build: psum[i+1][j+1] = psum[i][j+1] + psum[i+1][j] - psum[i][j] + grid[i][j]
// Query: sum = psum[r2+1][c2+1] - psum[r1][c2+1] - psum[r2+1][c1] + psum[r1][c1]
```

### Pitfalls
- Initialize `map[0] = 1` for counting, `map[0] = -1` for max length
- Check `psum - k` BEFORE updating `map[psum]` (order matters!)
- For max length, DON'T overwrite — keep earliest index
- C++ negative modulo: `((x % k) + k) % k`
- Use prefix sum (not sliding window) when array has negative numbers

---

# TIER 3 — COMMONLY ASKED (40-70% Probability)

---

## 14. Intervals [P: 60%]

### The 3 Core Patterns

**Merge Overlapping (LC 56)**: Sort by START, extend or add
```cpp
sort(intervals.begin(), intervals.end());
vector<vector<int>> result = {intervals[0]};
for (int i = 1; i < n; i++) {
    if (intervals[i][0] <= result.back()[1])
        result.back()[1] = max(result.back()[1], intervals[i][1]);
    else
        result.push_back(intervals[i]);
}
```

**Non-overlapping Selection (LC 435)**: Sort by END, keep earliest-ending

**Intersection (LC 986)**: Two pointers, advance the one ending earlier
```cpp
int lo = max(a[0], b[0]), hi = min(a[1], b[1]);
if (lo <= hi) result.push_back({lo, hi});
if (a[1] < b[1]) i++; else j++;
```

### Overlap Detection Formula
> Two intervals `[a,b]` and `[c,d]` overlap if and only if: `max(a,c) <= min(b,d)`

### Key Distinction
- **Sort by START**: Merge Intervals, Insert Interval
- **Sort by END**: Non-overlapping count, Activity Selection, Minimum Arrows

---

## 15. Design Problems (LRU, Trie) [P: 60%]

### LRU Cache (LC 146)
```cpp
// HashMap + Doubly Linked List
// get(): if exists, move to head, return value
// put(): if exists, update + move to head. If new, add to head. If over capacity, evict tail
```
- Dummy head (MRU) and dummy tail (LRU) simplify edge cases
- All operations O(1)

### Trie / Prefix Tree (LC 208)
```cpp
struct TrieNode {
    TrieNode* children[26] = {};
    bool isEnd = false;
};
void insert(string word) {
    TrieNode* node = root;
    for (char c : word) {
        if (!node->children[c - 'a'])
            node->children[c - 'a'] = new TrieNode();
        node = node->children[c - 'a'];
    }
    node->isEnd = true;
}
```
- **search** must check `isEnd`. **startsWith** just needs to reach the node
- Word Search II (LC 212): Trie + DFS backtracking on grid

### LFU Cache (LC 460) — Harder Variant
- Two hashmaps: `keyToNode` + `freqToList` (DLL per frequency)
- Track `minFreq`. On access: move from freq list to freq+1 list

---

## 16. Bit Manipulation [P: 50%]

### Must-Know Operations
```cpp
x & 1          // check if odd
x >> 1         // divide by 2
x << 1         // multiply by 2
x & (x - 1)   // remove lowest set bit (count bits, power of 2 check)
x ^ x = 0     // XOR cancels duplicates
x & (-x)       // isolate lowest set bit
```

### Key Problems
| Problem | Trick |
|---------|-------|
| Single Number (LC 136) | XOR all — duplicates cancel, single remains |
| Number of 1 Bits (LC 191) | `while(n) { count++; n &= (n-1); }` |
| Power of Two (LC 231) | `n > 0 && (n & (n-1)) == 0` |
| Missing Number (LC 268) | XOR [0..n] XOR nums — missing remains |
| Counting Bits (LC 338) | `dp[i] = dp[i >> 1] + (i & 1)` |

---

## 17. Stack (Expression & Parentheses) [P: 55%]

### Valid Parentheses (LC 20)
```cpp
stack<char> st;
for (char c : s) {
    if (c == '(' || c == '{' || c == '[') st.push(c);
    else {
        if (st.empty() || !isMatch(st.top(), c)) return false;
        st.pop();
    }
}
return st.empty();
```

### Basic Calculator II (LC 227) — No Parentheses
```cpp
// Track previous operator. On seeing new operator or end:
// +: push num, -: push -num, *: pop*num push, /: pop/num push
// Answer = sum of stack
```

### Decode String (LC 394) — Nested Brackets
```cpp
// Two stacks: one for strings, one for counts
// On '[': push current string and count
// On ']': pop count, repeat current string, append to popped string
```

---

# TIER 4 — SPECIALIZED (20-40% Probability)

---

## 18. Combinatorics & Math [P: 30%]

### Must-Know Formulas
| Concept | Formula | Use Case |
|---------|---------|----------|
| Permutations | P(n,r) = n!/(n-r)! | Order matters |
| Combinations | C(n,r) = n!/(r!(n-r)!) | Order doesn't matter |
| Catalan Numbers | C(2n,n)/(n+1) = 1,1,2,5,14,42... | Valid parentheses, BST count, triangulations |
| Stars and Bars | C(n+k-1, k-1) | Distribute n identical items into k bins |
| Inclusion-Exclusion | \|A∪B\| = \|A\|+\|B\|-\|A∩B\| | Count with overlapping conditions |

### Modular Arithmetic (for large answers)
```cpp
const int MOD = 1e9 + 7;
// Precompute factorials + inverse factorials for fast nCr
long long fact[N], inv_fact[N];
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}
// inv_fact[n] = power(fact[n], MOD-2, MOD)  (Fermat's little theorem)
// nCr(n, r) = fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD
```

---

## 19. Advanced DP Variants [P: 25%]

### Bitmask DP (N ≤ 20)
```cpp
// dp[mask] = best result using the subset represented by mask
// Iterate over all 2^N masks
for (int mask = 0; mask < (1 << n); mask++) {
    int bits = __builtin_popcount(mask);
    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) continue;  // already used
        dp[mask | (1 << j)] = best(dp[mask | (1 << j)], dp[mask] + cost[bits][j]);
    }
}
```

### Digit DP
- Build number digit-by-digit with `tight` bound
- Use for "count numbers in range [L,R] with property X"

### Tree DP
- Post-order DFS, return info from children to parent
- House Robber III: `pair<int,int> dfs(node)` returns {rob_this, skip_this}

---

# QUICK REFERENCE — CHEAT SHEETS

## Pattern Recognition Guide

| Problem Says... | Think... |
|-----------------|----------|
| "Sorted array" | Binary Search or Two Pointers |
| "Find all/generate" | Backtracking |
| "Min/max cost" | DP or Greedy |
| "Shortest path" | BFS (unweighted) or Dijkstra (weighted) |
| "Connected components" | DFS / Union-Find |
| "Task ordering / dependencies" | Topological Sort |
| "Subarray sum" | Prefix Sum + Hashmap |
| "Longest substring/subarray" | Sliding Window |
| "Kth largest/smallest" | Heap or Quickselect |
| "Next greater/smaller" | Monotonic Stack |
| "Overlapping intervals" | Sort + Greedy |
| "Top K" | Heap (size K) or Bucket Sort |
| "In-place, O(1) space" | Two Pointers |
| "Tree, recursive structure" | DFS (recursive) |
| "Level-by-level" | BFS with queue |
| "Exactly K" | Prefix Sum or atMost(K) - atMost(K-1) |
| "Contiguous subarray, negatives" | Prefix Sum (NOT sliding window) |

## Complexity Cheat Sheet

| Algorithm | Time | Space |
|-----------|------|-------|
| Binary Search | O(log N) | O(1) |
| Two Pointers | O(N) | O(1) |
| Sliding Window | O(N) | O(K) |
| Kadane's | O(N) | O(1) |
| DFS/BFS (graph) | O(V + E) | O(V) |
| DFS/BFS (grid) | O(M × N) | O(M × N) |
| Topological Sort | O(V + E) | O(V) |
| Dijkstra | O(E log V) | O(V) |
| Union-Find | O(α(N)) per op | O(N) |
| Heap push/pop | O(log N) | O(N) |
| Merge K Sorted | O(N log K) | O(K) |
| 1D DP | O(N × options) | O(N) |
| 2D DP (strings) | O(M × N) | O(M × N) |
| Interval DP | O(N³) | O(N²) |
| Bitmask DP | O(2^N × N) | O(2^N) |
| Backtracking (subsets) | O(N × 2^N) | O(N) |
| Backtracking (perms) | O(N × N!) | O(N) |
| Monotonic Stack | O(N) | O(N) |
| Prefix Sum (build) | O(N) | O(N) |
| Prefix Sum (query) | O(1) | — |

## C++ STL Quick Picks for Interviews

```cpp
// Sorting
sort(v.begin(), v.end());                    // ascending
sort(v.begin(), v.end(), greater<int>());    // descending
sort(v.begin(), v.end(), [](auto& a, auto& b) { return a[1] < b[1]; }); // custom

// Binary Search (on sorted)
lower_bound(v.begin(), v.end(), target);     // first >= target
upper_bound(v.begin(), v.end(), target);     // first > target

// Heap
priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

// Accumulate
accumulate(v.begin(), v.end(), 0LL);         // use 0LL for large sums!

// Remove duplicates
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());

// Max/Min element
*max_element(v.begin(), v.end());
*min_element(v.begin(), v.end());

// next_permutation
sort(v.begin(), v.end());
do { /* process v */ } while (next_permutation(v.begin(), v.end()));
```

## Interview Execution Template

```
1. UNDERSTAND (2 min)
   - Repeat the problem in your own words
   - Ask: Input range? Negatives? Duplicates? Empty input?

2. EXAMPLES (2 min)
   - Walk through 1-2 examples by hand
   - Include edge case (empty, single element, all same)

3. APPROACH (3 min)
   - State the pattern you'll use and WHY
   - State time/space complexity BEFORE coding
   - Mention alternatives briefly ("Brute force is O(N²), this is O(N)")

4. CODE (10-15 min)
   - Write clean, well-structured code
   - Use meaningful variable names
   - Handle edge cases at the top

5. TEST (3 min)
   - Trace through your example manually
   - Check edge cases: empty, single, duplicates, negative, overflow
   - Fix bugs if found
```

## The "I'm Stuck" Playbook

| Situation | Try This |
|-----------|----------|
| Don't know the pattern | Sort the input. Does it help? Try brute force, then optimize |
| Brute force is O(N²) on array | Can two pointers or sliding window make it O(N)? |
| Need to search efficiently | Binary search on sorted data or BS on answer |
| Counting problem with negatives | Prefix sum + hashmap |
| "Find all/generate" | Backtracking |
| Optimization problem | Try DP. Define state, transition, base case |
| Graph/connectivity | Model as graph, apply BFS/DFS/Union-Find |
| "Do in O(1)" | Hashmap, or clever data structure (LRU = HashMap + DLL) |
