# **HEAP & KTH PROBLEMS - COMPLETE GUIDE**

Two powerful approaches: Heap (Priority Queue) vs Binary Search + Count Function

### **TABLE OF CONTENTS**

1. Pattern Recognition - When to Use Heap vs Binary Search
2. Heap Patterns & Templates
3. Binary Search + Count Function Pattern
4. Key Problems with Solutions
5. Quick Decision Guide
6. Problem List by Category

## **PART 1: PATTERN RECOGNITION**

### ** HOW TO IDENTIFY KTH/K-TYPE PROBLEMS?**

**STRONG SIGNALS:**

 Keywords: "kth", "nth", "top k", "k closest", "k smallest/largest"
 "Minimum of maximum" or "Maximum of minimum"
 "Find the smallest/largest that satisfies..."
 "Split into k parts such that..."
 Optimization: minimize/maximize something

**EXAMPLES OF PROBLEM STATEMENTS:**

- "Find the kth smallest element"
- "Find k pairs with smallest sums"
- "Minimum speed to arrive on time"
- "Split array into k subarrays minimizing largest sum"
- "Kth smallest product of two sorted arrays"

### ** HEAP vs BINARY SEARCH - DECISION MATRIX**

**USE HEAP WHEN:**

 Need to find actual K elements (not just kth value)
 Need to maintain K elements dynamically
 Input size is manageable (not too large)
 Problem involves streaming data
 Need top K, bottom K, or K closest elements
 Examples: "Find K pairs", "Top K Frequent", "K Closest Points"

TIME: O(N log K)  |  SPACE: O(K)

### USE BINARY SEARCH + COUNT when:

 Only need kth value (not all K elements)
 Can define a search space with bounds
 Can write a count function: "How many elements satisfy condition?"
 Input is very large (heap might TLE)
 Problem asks for "minimum of maximum" or "maximum of minimum"
 Examples: "Kth smallest in matrix", "Split array", "Capacity to ship"

TIME: O(log(range) x O(count))  |  SPACE: O(1)

**GOLDEN RULE:**

> If you need ALL K elements > Use HEAP
> If you only need the Kth value > Try BINARY SEARCH first
> If Binary Search gives TLE > Fall back to optimized approach

## **PART 2: HEAP PATTERNS & TEMPLATES**

### **PATTERN 1: KTH SMALLEST/LARGEST ELEMENT**

**CORE IDEA:**
- For Kth SMALLEST > Use MAX HEAP of size K
- For Kth LARGEST > Use MIN HEAP of size K

WHY MAX HEAP FOR KTH SMALLEST?
Keep the K smallest elements in heap. The top (maximum) is the Kth smallest!

### TEMPLATE - Kth Smallest:

```
priority_queue<int> maxHeap;  // max heap

for (int num : arr) {
maxHeap.push(num);                   

if (maxHeap.size() > k) {            
    maxHeap.pop();  // Remove largest
}                                    

}

return maxHeap.top();  // Kth smallest
```

TIME: O(N log K)  |  SPACE: O(K)

### TEMPLATE - Kth Largest:

```cpp
priority_queue<int, vector<int>, greater<int>> minHeap;  // min heap

for (int num : arr) {
minHeap.push(num);                    

if (minHeap.size() > k) {             
    minHeap.pop();  // Remove smallest
}                                     

}

return minHeap.top();  // Kth largest
```

TIME: O(N log K)  |  SPACE: O(K)

### **PATTERN 2: TOP K FREQUENT ELEMENTS**

**APPROACH:**
1. Count frequency using hashmap
2. Use min heap of size K (store {frequency, element})
3. Keep K most frequent elements

**TEMPLATE:**

```cpp
unordered_map<int, int> freq;
for (int num : nums) {
freq[num]++;

}

// Min heap based on frequency
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;

for (auto& [num, count] : freq) {
minHeap.push({count, num});

if (minHeap.size() > k) {  
    minHeap.pop();         
}                          

}

vector<int> result;
while (!minHeap.empty()) {
result.push_back(minHeap.top().second);
minHeap.pop();

}
```

TIME: O(N log K)  |  SPACE: O(N) for hashmap + O(K) for heap

### ALTERNATIVE: Bucket Sort O(N)

```cpp
// Create buckets where index = frequency
vector<vector<int>> buckets(n + 1);
for (auto& [num, count] : freq) {
buckets[count].push_back(num);

}

// Collect from highest frequency
vector<int> result;
for (int i = n; i >= 0 && result.size() < k; i--) {
for (int num : buckets[i]) {      
    result.push_back(num);        
    if (result.size() == k) break;
}                                 

}
```

### **PATTERN 3: K PAIRS WITH SMALLEST/LARGEST SUMS**

PROBLEM: Find K pairs (i, j) from two arrays with smallest sums

### APPROACH 1: Min Heap (Optimal when we need actual pairs)

```cpp
// Min heap: {sum, i, j}
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minHeap;

// Start with first element of nums1 with all of nums2
for (int j = 0; j < min(k, (int)nums2.size()); j++) {
minHeap.push({nums1[0] + nums2[j], 0, j});

}

vector<vector<int>> result;
while (k-- > 0 && !minHeap.empty()) {
auto [sum, i, j] = minHeap.top();                 
minHeap.pop();                                    

result.push_back({nums1[i], nums2[j]});           

// Add next pair from nums1                       
if (i + 1 < nums1.size()) {                       
    minHeap.push({nums1[i+1] + nums2[j], i+1, j});
}                                                 

}
```

TIME: O(K log K)  |  SPACE: O(K)

**KEY INSIGHT:**
- Start with smallest possible pairs
- Expand only promising candidates
- Avoid generating all NxM pairs

### **PATTERN 4: MERGE K SORTED LISTS/ARRAYS**

APPROACH: Min heap tracking head of each list

**TEMPLATE:**

```cpp
// Min heap: {value, list_index, element_index}
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minHeap;

// Add first element from each list
for (int i = 0; i < lists.size(); i++) {
if (!lists[i].empty()) {              
    minHeap.push({lists[i][0], i, 0});
}                                     

}

vector<int> result;
while (!minHeap.empty()) {
auto [val, listIdx, elemIdx] = minHeap.top();                     
minHeap.pop();                                                    

result.push_back(val);                                            

// Add next element from same list                                
if (elemIdx + 1 < lists[listIdx].size()) {                        
    minHeap.push({lists[listIdx][elemIdx+1], listIdx, elemIdx+1});
}                                                                 

}
```

TIME: O(N log K) where N = total elements, K = number of lists
SPACE: O(K)

### **PATTERN 5: K CLOSEST ELEMENTS**

### APPROACH 1: Max Heap (General Case)

```cpp
// Max heap: {distance, value}
priority_queue<pair<int,int>> maxHeap;

for (int num : arr) {
int dist = abs(num - x);  
maxHeap.push({dist, num});

if (maxHeap.size() > k) { 
    maxHeap.pop();        
}                         

}

vector<int> result;
while (!maxHeap.empty()) {
result.push_back(maxHeap.top().second);
maxHeap.pop();

}
sort(result.begin(), result.end());
```

TIME: O(N log K)

### APPROACH 2: Binary Search + Two Pointers (If Sorted)

```cpp
// Find closest index to x
int left = 0, right = n - 1;
while (left < right) {
int mid = left + (right - left) / 2;
if (arr[mid] >= x) right = mid;     
else left = mid + 1;                

}

// Expand window around closest point
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

// Elements are in [left+1, right-1]
vector<int> result(arr.begin() + left + 1, arr.begin() + right);
```

TIME: O(log N + K)  |  SPACE: O(1)

### **PATTERN 6: TWO HEAPS - FIND MEDIAN FROM DATA STREAM** 

PROBLEM: Maintain median as numbers are added dynamically

BRILLIANT APPROACH: Use TWO heaps!
- Max Heap (left half) - stores smaller half
- Min Heap (right half) - stores larger half
- Keep heaps balanced (size difference < 1)

**INVARIANT:**
- All elements in maxHeap < all elements in minHeap
- maxHeap.size() == minHeap.size() OR maxHeap.size() == minHeap.size() + 1

**VISUALIZATION:**
[smaller half]  MEDIAN  [larger half]
Max Heap               Min Heap

**TEMPLATE:**

```java
class MedianFinder {
priority_queue<int> maxHeap;  // Left half (smaller elements)
priority_queue<int, vector<int>, greater<int>> minHeap;  // Right half (larger)
```

public:
```
void addNum(int num) {                              
    // Always add to maxHeap first                  
    maxHeap.push(num);                              

    // Balance: move largest from maxHeap to minHeap
    minHeap.push(maxHeap.top());                    
    maxHeap.pop();                                  

    // If minHeap became larger, rebalance          
    if (minHeap.size() > maxHeap.size()) {          
        maxHeap.push(minHeap.top());                
        minHeap.pop();                              
    }                                               
}                                                   

double findMedian() {                               
    if (maxHeap.size() > minHeap.size()) {          
        return maxHeap.top();                       
    }                                               
    return (maxHeap.top() + minHeap.top()) / 2.0;   
}                                                   
```

```
};
```

TIME: O(log N) per add, O(1) per median  |  SPACE: O(N)

**KEY INSIGHT:**
Why this works? Median is always at boundary of two halves!

**VARIATIONS:**
- Sliding Window Median - Use multiset or two heaps with lazy deletion
- IPO (Maximum Capital) - Two heaps for available/unavailable projects

### **PATTERN 7: INTERVALS WITH HEAP (SWEEP LINE)**

PROBLEM TYPE: Meeting Rooms II, Car Pooling, Course Schedule III

**CORE IDEA:**
- Sort by start time
- Use min heap to track end times
- Remove finished intervals as you go

**KEY INSIGHT:**
We don't need to track WHICH meetings are ongoing, just HOW MANY!
Min heap size = number of simultaneous meetings at any point.

WHY MIN HEAP?
By storing end times, heap.top() gives earliest ending meeting.
If new meeting starts after earliest end, we can reuse that room!

**INTUITION:**
Think of it as rooms at a hotel. When guest checks out (meeting ends),
room becomes available for next guest. Heap tracks checkout times!

### TEMPLATE - Meeting Rooms II:

```cpp
int minMeetingRooms(vector<vector<int>>& intervals) {
sort(intervals.begin(), intervals.end());                            

priority_queue<int, vector<int>, greater<int>> minHeap;  // End times

for (auto& interval : intervals) {                                   
    // Remove meetings that have ended                               
    if (!minHeap.empty() && minHeap.top() <= interval[0]) {          
        minHeap.pop();                                               
    }                                                                

    // Add current meeting's end time                                
    minHeap.push(interval[1]);                                       
}                                                                    

return minHeap.size();  // Max simultaneous meetings                 

}
```

TIME: O(N log N)  |  SPACE: O(N)

**COMMON MISTAKE:**
 Trying to track which specific intervals are active
 Only track count and earliest end time

### TEMPLATE - Course Schedule III (Choose K Intervals):

```cpp
// Take courses with earliest deadlines, drop longest if needed
int scheduleCourse(vector<vector<int>>& courses) {
// Sort by deadline                                
sort(courses.begin(), courses.end(),               
     [](auto& a, auto& b) { return a[1] < b[1]; });

priority_queue<int> maxHeap;  // Store durations   
int time = 0;                                      

for (auto& course : courses) {                     
    int duration = course[0];                      
    int deadline = course[1];                      

    time += duration;                              
    maxHeap.push(duration);                        

    // If we exceeded deadline, drop longest course
    if (time > deadline) {                         
        time -= maxHeap.top();                     
        maxHeap.pop();                             
    }                                              
}                                                  

return maxHeap.size();                             

}
```

KEY INSIGHT - Course Schedule III:
Greedy strategy: Take courses with earliest deadlines first.
If we exceed deadline, drop the LONGEST course taken so far.
Why longest? It frees up maximum time for future courses!

**BRILLIANT TRICK:**
Max heap stores durations, not courses. When we exceed deadline,
removing longest duration gives best chance for future success!

**SIMILAR PROBLEMS:**
- 253. Meeting Rooms II
- 1094. Car Pooling
- 630. Course Schedule III 
- 1851. Minimum Interval to Include Each Query

### **PATTERN 8: GREEDY WITH HEAP (TASK SCHEDULER / REORGANIZE STRING)**

PROBLEM: Rearrange so no two adjacent elements are same

APPROACH: Always pick most frequent element (greedy + max heap)

**KEY INSIGHT:**
Greedy works! Most frequent element is hardest to place, so use it first.
By always picking highest frequency, we minimize chance of getting stuck.

WHY MAX HEAP?
Need to quickly find most frequent remaining element.
After using element, reduce count and put back if count > 0.

### TEMPLATE - Reorganize String:

```cpp
string reorganizeString(string s) {
unordered_map<char, int> freq;                       
for (char c : s) freq[c]++;                          

// Max heap by frequency                             
priority_queue<pair<int, char>> maxHeap;             
for (auto& [ch, count] : freq) {                     
    maxHeap.push({count, ch});                       
}                                                    

string result;                                       
pair<int, char> prev = {-1, '#'};  // Previously used

while (!maxHeap.empty()) {                           
    auto [count, ch] = maxHeap.top();                
    maxHeap.pop();                                   

    result += ch;                                    

    // Add back previous if still has count          
    if (prev.first > 0) {                            
        maxHeap.push(prev);                          
    }                                                

    prev = {count - 1, ch};                          
}                                                    

return result.size() == s.size() ? result : "";      

}
```

TIME: O(N log 26) = O(N)  |  SPACE: O(1) (only 26 letters)

INTUITION - Reorganize String:
Like dealing cards from biggest pile first. If "AAA" and "BB",
we alternate A-B-A-B-A. Can't start with all A's or we're stuck!

**COMMON MISTAKE:**
 Using array/map without heap > O(26N) to find max each time
 Heap gives O(log 26) = O(1) per operation

### TEMPLATE - Task Scheduler with Cooldown:

```cpp
int leastInterval(vector<char>& tasks, int n) {
unordered_map<char, int> freq;                                
for (char task : tasks) freq[task]++;                         

priority_queue<int> maxHeap;                                  
for (auto& [task, count] : freq) {                            
    maxHeap.push(count);                                      
}                                                             

int time = 0;                                                 

while (!maxHeap.empty()) {                                    
    vector<int> temp;                                         

    // Process n+1 tasks (one cycle)                          
    for (int i = 0; i <= n; i++) {                            
        if (!maxHeap.empty()) {                               
            int count = maxHeap.top();                        
            maxHeap.pop();                                    

            if (count > 1) {                                  
                temp.push_back(count - 1);                    
            }                                                 
        }                                                     
    }                                                         

    // Add back remaining tasks                               
    for (int count : temp) {                                  
        maxHeap.push(count);                                  
    }                                                         

    // If heap empty, only count actual tasks, else full cycle
    time += maxHeap.empty() ? temp.size() + 1 : n + 1;        
}                                                             

return time;                                                  

}
```

KEY INSIGHT - Task Scheduler:
Process tasks in cycles of size (n+1). In each cycle, pick n+1 different tasks.
If not enough unique tasks, add idle time.

**BRILLIANT OBSERVATION:**
If tasks run out, we're done! Otherwise, we always use full cycle of n+1.
This greedy approach minimizes total time.

**MATHEMATICAL INSIGHT:**
Alternative O(1) approach: Most frequent task determines minimum time.
```
time = (maxFreq - 1) * (n + 1) + (number of tasks with maxFreq)
```

But heap approach is more intuitive!

**SIMILAR PROBLEMS:**
- 621. Task Scheduler
- 767. Reorganize String
- 1054. Distant Barcodes
- 358. Rearrange String k Distance Apart (Premium)

### **PATTERN 9: SMALLEST RANGE FROM K LISTS** 

PROBLEM: Find smallest range covering at least one element from each of K lists

APPROACH: Min heap + tracking current range

**KEY INSIGHT:**
- Keep one element from each list in consideration
- Track min (from heap) and max (track separately)
- Move min pointer forward

**TEMPLATE:**

```cpp
vector<int> smallestRange(vector<vector<int>>& nums) {
// Min heap: {value, list_index, element_index}                                   
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minHeap;

int currentMax = INT_MIN;                                                         

// Add first element from each list                                               
for (int i = 0; i < nums.size(); i++) {                                           
    minHeap.push({nums[i][0], i, 0});                                             
    currentMax = max(currentMax, nums[i][0]);                                     
}                                                                                 

int rangeStart = 0, rangeEnd = INT_MAX;                                           

while (minHeap.size() == nums.size()) {                                           
    auto [minVal, listIdx, elemIdx] = minHeap.top();                              
    minHeap.pop();                                                                

    // Update best range                                                          
    if (currentMax - minVal < rangeEnd - rangeStart) {                            
        rangeStart = minVal;                                                      
        rangeEnd = currentMax;                                                    
    }                                                                             

    // Move to next element in this list                                          
    if (elemIdx + 1 < nums[listIdx].size()) {                                     
        int nextVal = nums[listIdx][elemIdx + 1];                                 
        minHeap.push({nextVal, listIdx, elemIdx + 1});                            
        currentMax = max(currentMax, nextVal);                                    
    }                                                                             
}                                                                                 

return {rangeStart, rangeEnd};                                                    

}
```

TIME: O(N log K) where N = total elements  |  SPACE: O(K)

**WHY IT WORKS:**
We must have one from each list. By moving minimum forward, we explore
all possible ranges while maintaining coverage!

**INTUITION:**
Imagine K pointers, one per list. Current range = [min_pointer, max_pointer].
To shrink range, move min_pointer forward (can't move max without breaking coverage).

Example: [1, 5, 8], [2, 10], [3, 6, 9]
Start: min=1, max=3, range=[1,3]
Move 1>5: min=2, max=5, range=[2,5]
Move 2>10: min=3, max=10, range=[3,10] (worse!)
Move 3>6: min=5, max=10, range=[5,10] (worse!)
Best was [1,3]!

**GOLDEN RULE:**
At each step, we MUST move minimum. Moving anything else breaks coverage!

### **PATTERN 10: GREEDY RESOURCE ALLOCATION (Ladders/Bricks)**

PROBLEM TYPE: Furthest Building You Can Reach, Limited Resources

KEY INSIGHT: Use heap to track K "best" uses of scarce resource

## **SOLVED: Furthest Building You Can Reach (LC 1642)**

PROBLEM: Have bricks and ladders. Ladders cover any height, bricks limited.

 **INSIGHT**: Use ladders for K largest climbs, bricks for rest

```cpp
int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
priority_queue<int, vector<int>, greater<int>> minHeap;  // Climbs using ladders

for (int i = 0; i < heights.size() - 1; i++) {                                  
    int climb = heights[i + 1] - heights[i];                                    

    if (climb <= 0) continue;  // Going down, no cost                           

    // Initially use ladder for this climb                                      
    minHeap.push(climb);                                                        

    // If used too many ladders, convert smallest climb to bricks               
    if (minHeap.size() > ladders) {                                             
        bricks -= minHeap.top();                                                
        minHeap.pop();                                                          

        if (bricks < 0) return i;  // Can't proceed                             
    }                                                                           
}                                                                               

return heights.size() - 1;                                                      

}
```

TIME: O(N log L)  |  SPACE: O(L) where L = ladders

**WHY IT WORKS:**
Ladders are "unlimited height" resource - use for biggest climbs.
Min heap tracks L smallest among ladder-assigned climbs.
When we have too many, smallest gets converted to bricks.

### **PATTERN 11: SIMULATION WITH HEAP**

PROBLEM TYPE: Repeatedly pick max/min, apply operation, put back

## **SOLVED: Last Stone Weight (LC 1046)**

```cpp
int lastStoneWeight(vector<int>& stones) {
priority_queue<int> maxHeap(stones.begin(), stones.end());

while (maxHeap.size() > 1) {                              
    int y = maxHeap.top(); maxHeap.pop();                 
    int x = maxHeap.top(); maxHeap.pop();                 

    if (y != x) {                                         
        maxHeap.push(y - x);                              
    }                                                     
}                                                         

return maxHeap.empty() ? 0 : maxHeap.top();               

}
```

TIME: O(N log N)  |  SPACE: O(N)

## **SOLVED: Take Gifts From the Richest Pile (LC 2558)**

```cpp
long long pickGifts(vector<int>& gifts, int k) {
priority_queue<int> maxHeap(gifts.begin(), gifts.end());

while (k-- > 0) {                                       
    int top = maxHeap.top();                            
    maxHeap.pop();                                      
    maxHeap.push((int)sqrt(top));                       
}                                                       

long long sum = 0;                                      
while (!maxHeap.empty()) {                              
    sum += maxHeap.top();                               
    maxHeap.pop();                                      
}                                                       
return sum;                                             

}
```

TIME: O((N + K) log N)  |  SPACE: O(N)

## **SOLVED: Final Array State After K Multiplication Operations I (LC 3264)**

```cpp
vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
// Min heap: {value, index}                                             
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;

for (int i = 0; i < nums.size(); i++) {                                 
    minHeap.push({nums[i], i});                                         
}                                                                       

while (k-- > 0) {                                                       
    auto [val, idx] = minHeap.top();                                    
    minHeap.pop();                                                      
    nums[idx] = val * multiplier;                                       
    minHeap.push({nums[idx], idx});                                     
}                                                                       

return nums;                                                            

}
```

TIME: O((N + K) log N)  |  SPACE: O(N)

### **PATTERN 12: SORT + HEAP FOR OPTIMIZATION**

PROBLEM TYPE: Optimize score = f(selected) x min/max(selected)

 **KEY INSIGHT**: Sort by one factor, use heap to track best K for other

## **SOLVED: Maximum Subsequence Score (LC 2542)**

PROBLEM: Select k indices. Score = sum(nums1[selected]) x min(nums2[selected])

 **INSIGHT**: Sort by nums2 descending. As we go, min is fixed, maximize sum.

```cpp
long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
int n = nums1.size();                                                           
vector<pair<int, int>> pairs(n);                                                

for (int i = 0; i < n; i++) {                                                   
    pairs[i] = {nums2[i], nums1[i]};                                            
}                                                                               

// Sort by nums2 descending                                                     
sort(pairs.rbegin(), pairs.rend());                                             

priority_queue<int, vector<int>, greater<int>> minHeap;  // Track k nums1 values
long long sum = 0, maxScore = 0;                                                

for (auto& [minVal, num1Val] : pairs) {                                         
    sum += num1Val;                                                             
    minHeap.push(num1Val);                                                      

    if (minHeap.size() > k) {                                                   
        sum -= minHeap.top();                                                   
        minHeap.pop();                                                          
    }                                                                           

    if (minHeap.size() == k) {                                                  
        maxScore = max(maxScore, sum * minVal);                                 
    }                                                                           
}                                                                               

return maxScore;                                                                

}
```

TIME: O(N log N)  |  SPACE: O(N)

## **SOLVED: Maximum Performance of a Team (LC 1383)**

PROBLEM: Select at most k engineers. Performance = sum(speed) x min(efficiency)

```cpp
long long maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
vector<pair<int, int>> engineers(n);                   
for (int i = 0; i < n; i++) {                          
    engineers[i] = {efficiency[i], speed[i]};          
}                                                      

// Sort by efficiency descending                       
sort(engineers.rbegin(), engineers.rend());            

priority_queue<int, vector<int>, greater<int>> minHeap;
long long sumSpeed = 0, maxPerf = 0;                   

for (auto& [eff, spd] : engineers) {                   
    sumSpeed += spd;                                   
    minHeap.push(spd);                                 

    if (minHeap.size() > k) {                          
        sumSpeed -= minHeap.top();                     
        minHeap.pop();                                 
    }                                                  

    maxPerf = max(maxPerf, sumSpeed * eff);            
}                                                      

return maxPerf;                                        

}
```

TIME: O(N log N)  |  SPACE: O(K)

## **SOLVED: Minimum Cost to Hire K Workers (LC 857)**  HARD

PROBLEM: Hire k workers. Each has quality and wage.
Pay ratio must be same, at least minimum wage.

 **INSIGHT**: Sort by wage/quality ratio. Use heap to track k smallest qualities.

```cpp
double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
int n = quality.size();                                     
vector<pair<double, int>> workers(n);                       

for (int i = 0; i < n; i++) {                               
    workers[i] = {(double)wage[i] / quality[i], quality[i]};
}                                                           

// Sort by wage/quality ratio                               
sort(workers.begin(), workers.end());                       

priority_queue<int> maxHeap;  // Track k smallest qualities 
int sumQuality = 0;                                         
double minCost = DBL_MAX;                                   

for (auto& [ratio, q] : workers) {                          
    sumQuality += q;                                        
    maxHeap.push(q);                                        

    if (maxHeap.size() > k) {                               
        sumQuality -= maxHeap.top();                        
        maxHeap.pop();                                      
    }                                                       

    if (maxHeap.size() == k) {                              
        minCost = min(minCost, ratio * sumQuality);         
    }                                                       
}                                                           

return minCost;                                             

}
```

TIME: O(N log N)  |  SPACE: O(N)

### **PATTERN 13: HEAP WITH TRANSFORMATIONS**

PROBLEM TYPE: Transform elements to minimize/maximize something

## **SOLVED: Minimize Deviation in Array (LC 1675)**  HARD

PROBLEM: Can double odd numbers (once), halve even numbers (many times).
Minimize max - min.

 **INSIGHT**: First make all odd numbers even (double them).
Then only operation is halving (decreasing max).

```cpp
int minimumDeviation(vector<int>& nums) {
priority_queue<int> maxHeap;                         
int minVal = INT_MAX;                                

// Make all numbers even (double odds), track minimum
for (int num : nums) {                               
    if (num % 2 == 1) num *= 2;                      
    maxHeap.push(num);                               
    minVal = min(minVal, num);                       
}                                                    

int minDev = maxHeap.top() - minVal;                 

// Keep halving maximum while it's even              
while (maxHeap.top() % 2 == 0) {                     
    int maxVal = maxHeap.top();                      
    maxHeap.pop();                                   

    maxVal /= 2;                                     
    minVal = min(minVal, maxVal);                    
    maxHeap.push(maxVal);                            

    minDev = min(minDev, maxHeap.top() - minVal);    
}                                                    

return minDev;                                       

}
```

TIME: O(N log N log M)  |  SPACE: O(N)

### **PATTERN 14: DESIGN PROBLEMS WITH HEAP**

## **SOLVED: Design Twitter (LC 355)**

```java
class Twitter {
int timestamp = 0;
unordered_map<int, vector<pair<int, int>>> tweets;  // userId -> [(time, tweetId)]
unordered_map<int, unordered_set<int>> following;   // userId -> set of followees
```

public:
```
void postTweet(int userId, int tweetId) {                                                   
    tweets[userId].push_back({timestamp++, tweetId});                                       
}                                                                                           

vector<int> getNewsFeed(int userId) {                                                       
    // Merge K sorted lists (user's tweets + followees' tweets)                             
    priority_queue<tuple<int, int, int, int>> maxHeap;  // {time, tweetId, userId, idx}     

    auto addTweets = [&](int uid) {                                                         
        if (!tweets[uid].empty()) {                                                         
            int idx = tweets[uid].size() - 1;                                               
            maxHeap.push({tweets[uid][idx].first, tweets[uid][idx].second, uid, idx});      
        }                                                                                   
    };                                                                                      

    addTweets(userId);                                                                      
    for (int followee : following[userId]) {                                                
        addTweets(followee);                                                                
    }                                                                                       

    vector<int> feed;                                                                       
    while (!maxHeap.empty() && feed.size() < 10) {                                          
        auto [time, tweetId, uid, idx] = maxHeap.top();                                     
        maxHeap.pop();                                                                      

        feed.push_back(tweetId);                                                            

        if (idx > 0) {                                                                      
            maxHeap.push({tweets[uid][idx-1].first, tweets[uid][idx-1].second, uid, idx-1});
        }                                                                                   
    }                                                                                       

    return feed;                                                                            
}                                                                                           

void follow(int followerId, int followeeId) {                                               
    if (followerId != followeeId) {                                                         
        following[followerId].insert(followeeId);                                           
    }                                                                                       
}                                                                                           

void unfollow(int followerId, int followeeId) {                                             
    following[followerId].erase(followeeId);                                                
}                                                                                           
```

```
};
```

## **SOLVED: Seat Reservation Manager (LC 1845)**

```java
class SeatManager {
priority_queue<int, vector<int>, greater<int>> available;
```

public:
```
SeatManager(int n) {              
    for (int i = 1; i <= n; i++) {
        available.push(i);        
    }                             
}                                 

int reserve() {                   
    int seat = available.top();   
    available.pop();              
    return seat;                  
}                                 

void unreserve(int seatNumber) {  
    available.push(seatNumber);   
}                                 
```

```
};
```

TIME: O(log N) per operation  |  SPACE: O(N)

### **PATTERN 15: MINIMUM COST TO CONNECT/MERGE (GREEDY HEAP)**

PROBLEM: Connect ropes/sticks with minimum cost

KEY INSIGHT: Always merge smallest two (Huffman coding!)

### TEMPLATE - Minimum Cost to Connect Sticks:

```cpp
int connectSticks(vector<int>& sticks) {
priority_queue<int, vector<int>, greater<int>> minHeap(sticks.begin(), sticks.end());

int totalCost = 0;                                                                   

while (minHeap.size() > 1) {                                                         
    int first = minHeap.top(); minHeap.pop();                                        
    int second = minHeap.top(); minHeap.pop();                                       

    int cost = first + second;                                                       
    totalCost += cost;                                                               

    minHeap.push(cost);  // Merged stick                                             
}                                                                                    

return totalCost;                                                                    

}
```

TIME: O(N log N)  |  SPACE: O(N)

**WHY GREEDY WORKS:**
Smaller elements appear in more merges. By merging smallest first,
we minimize total cost (like building optimal binary tree)!

**INTUITION:**
Sticks [2, 4, 3]:

Wrong way (merge largest first):
(4+3)=7, then (7+2)=9, total = 7+9 = 16

Right way (merge smallest first):
(2+3)=5, then (5+4)=9, total = 5+9 = 14 Y

Why? Merged stick appears in ALL future merges. Keep merged values small!

**MATHEMATICAL PROOF:**
This is Huffman Coding! Proven optimal for minimizing weighted path length.
Always merge two smallest = optimal binary tree = minimum total cost.

**COMMON MISTAKE:**
 Trying to plan all merges upfront
 Greedy: just merge smallest two, repeat

**SIMILAR:**
- 1167. Minimum Cost to Connect Sticks (Premium)
- 1046. Last Stone Weight
- 264. Ugly Number II (can use heap or DP)

### **PATTERN 11: UGLY NUMBER II - GENERATING SEQUENCE**

PROBLEM: Find nth number whose only prime factors are 2, 3, 5

### APPROACH 1: Min Heap

```cpp
int nthUglyNumber(int n) {
priority_queue<long, vector<long>, greater<long>> minHeap;
unordered_set<long> seen;                                 

minHeap.push(1);                                          
seen.insert(1);                                           

long ugly = 1;                                            
vector<int> primes = {2, 3, 5};                           

for (int i = 0; i < n; i++) {                             
    ugly = minHeap.top();                                 
    minHeap.pop();                                        

    for (int prime : primes) {                            
        long next = ugly * prime;                         
        if (!seen.count(next)) {                          
            seen.insert(next);                            
            minHeap.push(next);                           
        }                                                 
    }                                                     
}                                                         

return (int)ugly;                                         

}
```

TIME: O(N log N)  |  SPACE: O(N)

### APPROACH 2: Three Pointers (DP) - BETTER!

```cpp
int nthUglyNumber(int n) {
vector<int> ugly(n);                     
ugly[0] = 1;                             

int i2 = 0, i3 = 0, i5 = 0;              

for (int i = 1; i < n; i++) {            
    int next2 = ugly[i2] * 2;            
    int next3 = ugly[i3] * 3;            
    int next5 = ugly[i5] * 5;            

    ugly[i] = min({next2, next3, next5});

    if (ugly[i] == next2) i2++;          
    if (ugly[i] == next3) i3++;          
    if (ugly[i] == next5) i5++;          
}                                        

return ugly[n-1];                        

}
```

TIME: O(N)  |  SPACE: O(N)

**KEY INSIGHT:**
Each ugly number comes from previous ugly number x {2, 3, or 5}
Use 3 pointers to track candidates!

**BRILLIANT INTUITION:**
Imagine 3 separate streams:
Stream1: 1x2, 2x2, 3x2, 4x2, 5x2...
Stream2: 1x3, 2x3, 3x3, 4x3, 5x3...
Stream3: 1x5, 2x5, 3x5, 4x5, 5x5...

Merge these 3 streams! Each pointer tracks position in its stream.
Pick minimum from 3 candidates, advance that pointer.

WHY ADVANCE ALL TIES?
If ugly[i] == next2 == next3, both i2 and i3 must advance.
Otherwise we'd add same number twice! (e.g., 6 = 2x3 = 3x2)

COMPARISON - Heap vs DP:
Heap: O(N log N), needs set to avoid duplicates, more space
DP:   O(N), no duplicates naturally, less space
DP is clearly better here!

## **PART 3: BINARY SEARCH + COUNT FUNCTION PATTERN**

### ** THE UNIVERSAL TEMPLATE**

**WHEN TO USE:**
- Can't find all K elements efficiently
- Only need Kth value
- Can define search space [lo, hi]
- Can write count function

**THE TEMPLATE:**

STEP 1: Establish bounds (lo, hi)
STEP 2: Write count function: "How many elements < guess?"
STEP 3: Binary search until lo == hi

```
// For "Find Kth smallest"
while (lo < hi) {
int mid = lo + (hi - lo) / 2;          

if (count(mid) >= k) {                 
    hi = mid;        // Answer is < mid
} else {                               
    lo = mid + 1;    // Answer is > mid
}                                      

}
return lo;

// For "Find maximum value such that constraint satisfied"
while (lo < hi) {
int mid = lo + (hi - lo + 1) / 2;  // Note: +1 to avoid infinite loop

if (isPossible(mid)) {                                               
    lo = mid;        // This works, try bigger                       
} else {                                                             
    hi = mid - 1;    // Too big, try smaller                         
}                                                                    

}
return lo;
```

**KEY POINTS:**

1. For MINIMUM problems: use (lo + hi) / 2, update hi = mid
2. For MAXIMUM problems: use (lo + hi + 1) / 2, update lo = mid
3. The "+1" prevents infinite loop when lo and hi differ by 1

### **PATTERN: KTH SMALLEST IN SORTED MATRIX**

PROBLEM: Matrix with sorted rows and columns. Find kth smallest.

### APPROACH: Binary Search + Staircase Count

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

// Count elements < target using staircase method
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

WHY STAIRCASE?
Start from top-right corner. Move left if too large, move down if too small.
This counts efficiently without checking every element!

### **PATTERN: KTH SMALLEST PAIR DISTANCE**

PROBLEM: Array of numbers. Find kth smallest distance between any two elements.

### APPROACH: Binary Search + Sliding Window Count

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

// Count pairs with distance < target
int countPairs(vector<int>& nums, int target) {
int count = 0;                                                   
int left = 0;                                                    

for (int right = 0; right < nums.size(); right++) {              
    while (nums[right] - nums[left] > target) {                  
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
For each right pointer, find how many left pointers form valid pairs.

### **PATTERN: SPLIT ARRAY - MINIMIZE MAXIMUM SUBARRAY SUM**

PROBLEM: Split array into k subarrays, minimize the largest sum

### APPROACH: Binary Search on Answer

```cpp
int splitArray(vector<int>& nums, int k) {
int lo = *max_element(nums.begin(), nums.end());  // Min possible max 
int hi = accumulate(nums.begin(), nums.end(), 0);  // Max possible max

while (lo < hi) {                                                     
    int mid = lo + (hi - lo) / 2;                                     

    if (canSplit(nums, k, mid)) {                                     
        hi = mid;        // Can do better                             
    } else {                                                          
        lo = mid + 1;    // Need larger max                           
    }                                                                 
}                                                                     
return lo;                                                            

}

// Can we split into < k subarrays with max sum < maxSum?
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

**SIMILAR PROBLEMS:**
- Capacity To Ship Packages Within D Days
- Divide Chocolate (maximize minimum sweetness)
- Koko Eating Bananas
- Minimum Number of Days to Make m Bouquets

## **PART 4: KEY PROBLEMS WITH SOLUTIONS**

### **PROBLEM: Maximum Running Time of N Computers (LC 2141)**

IDEA: Binary search on running time. Can we run all N computers for T minutes?

**KEY INSIGHT:**
- If battery > T: Can only power ONE computer for T minutes (wasted capacity)
- If battery < T: Can be swapped between computers (fully utilized)

FORMULA: sum(min(battery[i], T)) >= N x T

```cpp
bool canRun(vector<int>& batteries, int n, long long time) {
long long totalPower = 0;                       

for (int battery : batteries) {                 
    totalPower += min((long long)battery, time);
}                                               

return totalPower >= (long long)n * time;       

}

long long maxRunTime(int n, vector<int>& batteries) {
long long lo = 0;                                             
long long hi = 0;                                             
for (int b : batteries) hi += b;                              
hi /= n;                                                      

while (lo < hi) {                                             
    long long mid = lo + (hi - lo + 1) / 2;  // +1 for maximum

    if (canRun(batteries, n, mid)) {                          
        lo = mid;                                             
    } else {                                                  
        hi = mid - 1;                                         
    }                                                         
}                                                             
return lo;                                                    

}
```

### **PROBLEM: Koko Eating Bananas (LC 875)**

IDEA: Find minimum eating speed K such that all bananas eaten within H hours

```cpp
bool canEatAll(vector<int>& piles, int k, int h) {
int hours = 0;                                       
for (int pile : piles) {                             
    hours += (pile + k - 1) / k;  // Ceiling division
    if (hours > h) return false;                     
}                                                    
return true;                                         

}

int minEatingSpeed(vector<int>& piles, int h) {
int lo = 1;                                       
int hi = *max_element(piles.begin(), piles.end());

while (lo < hi) {                                 
    int mid = lo + (hi - lo) / 2;                 

    if (canEatAll(piles, mid, h)) {               
        hi = mid;        // Can go slower         
    } else {                                      
        lo = mid + 1;    // Need faster speed     
    }                                             
}                                                 
return lo;                                        

}
```

### **PROBLEM: Nth Magical Number (LC 878)**

IDEA: Number divisible by A or B. Use Inclusion-Exclusion Principle.

KEY FORMULA: count(x) = x/A + x/B - x/LCM(A,B)

```
int nthMagicalNumber(int n, int a, int b) {
const long MOD = 1e9 + 7;                
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
return lo % MOD;                         

}
```

### **PROBLEM: Kth Smallest Amount With Single Denomination (LC 3116)**

IDEA: Use Inclusion-Exclusion Principle with power set of coins

WHY POWER SET?
- Single coin: count = n / coin
- Two coins: avoid double counting using LCM
- Multiple coins: alternate add/subtract based on subset size

```cpp
long long findKthSmallest(vector<int>& coins, int k) {
long long left = 1;                           
long long right = 1e11;                       

while (left < right) {                        
    long long mid = left + (right - left) / 2;

    if (countAmount(mid, coins) >= k) {       
        right = mid;                          
    } else {                                  
        left = mid + 1;                       
    }                                         
}                                             
return left;                                  

}

long long countAmount(long long n, vector<int>& coins) {
int m = coins.size();                                              
long long total = 0;                                               

// Iterate all subsets (power set)                                 
for (int mask = 1; mask < (1 << m); mask++) {                      
    long long lcm = 1;                                             
    int setBits = 0;                                               

    // Calculate LCM of selected coins                             
    for (int i = 0; i < m; i++) {                                  
        if (mask & (1 << i)) {                                     
            lcm = lcm / __gcd(lcm, (long long)coins[i]) * coins[i];
            setBits++;                                             
            if (lcm > n) break;  // Optimization                   
        }                                                          
    }                                                              

    // Inclusion-Exclusion: add if odd, subtract if even           
    if (setBits % 2 == 1) {                                        
        total += n / lcm;                                          
    } else {                                                       
        total -= n / lcm;                                          
    }                                                              
}                                                                  
return total;                                                      

}
```

### **PROBLEM: Longest Repeating Substring (LC 1062)**

IDEA: Binary search on substring length. Check if any substring of length L repeats.

```
int longestRepeatingSubstring(string s) {
int lo = 0;                             
int hi = s.size() - 1;                  

while (lo < hi) {                       
    int mid = lo + (hi - lo + 1) / 2;   

    if (hasRepeatingSubstring(s, mid)) {
        lo = mid;                       
    } else {                            
        hi = mid - 1;                   
    }                                   
}                                       
return lo;                              

}

bool hasRepeatingSubstring(string& s, int len) {
unordered_set<string> seen;                

for (int i = 0; i <= s.size() - len; i++) {
    string sub = s.substr(i, len);         
    if (seen.count(sub)) return true;      
    seen.insert(sub);                      
}                                          
return false;                              

}
```

TIME: O(N2 log N)  |  Can optimize to O(N log2 N) using rolling hash

### **PROBLEM: Kth Smallest Product of Two Sorted Arrays (LC 2040)**

TRICKY: Arrays can have negative numbers!

**KEY INSIGHT:**
- Split arrays into positive and negative parts
- Keep reversed copies for easier counting
- Count differently based on guess sign

If guess > 0:
```
count = pos1xpos2 + neg1_revxneg2_rev + neg1.size()xpos2.size() + pos1.size()xneg2.size()
```

If guess < 0:
```
count = pos1_revxneg2 + neg1xpos2_rev
```

WHY REVERSE?
For negative arrays, kth smallest is actually (n-k+1)th from end.
Reversing makes indexing consistent!

### **PROBLEM: Divide Chocolate (LC 1231) - Premium**

IDEA: Maximize minimum sweetness when dividing into K+1 pieces

```cpp
int maximizeSweetness(vector<int>& sweetness, int k) {
k++;  // K+1 pieces (you keep one)                         

int lo = *min_element(sweetness.begin(), sweetness.end()); 
int hi = accumulate(sweetness.begin(), sweetness.end(), 0);

while (lo < hi) {                                          
    int mid = lo + (hi - lo + 1) / 2;  // +1 for maximum   

    if (canDivide(sweetness, k, mid)) {                    
        lo = mid;                                          
    } else {                                               
        hi = mid - 1;                                      
    }                                                      
}                                                          
return lo;                                                 

}

bool canDivide(vector<int>& arr, int k, int minSweet) {
int pieces = 0;                    
int currentSweet = 0;              

for (int sweet : arr) {            
    currentSweet += sweet;         
    if (currentSweet >= minSweet) {
        pieces++;                  
        currentSweet = 0;          
    }                              
}                                  
return pieces >= k;                

}
```

### **PROBLEM: Trapping Rain Water II (LC 407)**  HARD

PROBLEM: 2D elevation map - how much water can be trapped?

BRILLIANT APPROACH: Min heap + boundary processing (like Dijkstra!)

**KEY INSIGHT:**
- Water level at a cell = minimum height of surrounding boundaries
- Process from outside to inside (like peeling an onion)
- Use min heap to always process lowest boundary first

**VISUALIZATION:**
Start from edges (boundaries), move inward
Water fills to height of lowest surrounding wall

**TEMPLATE:**

```cpp
int trapRainWater(vector<vector<int>>& heightMap) {
if (heightMap.empty()) return 0;                                                  

int m = heightMap.size(), n = heightMap[0].size();                                

// Min heap: {height, row, col}                                                   
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minHeap;
vector<vector<bool>> visited(m, vector<bool>(n, false));                          

// Add all boundary cells                                                         
for (int i = 0; i < m; i++) {                                                     
    for (int j = 0; j < n; j++) {                                                 
        if (i == 0 || i == m-1 || j == 0 || j == n-1) {                           
            minHeap.push({heightMap[i][j], i, j});                                
            visited[i][j] = true;                                                 
        }                                                                         
    }                                                                             
}                                                                                 

int water = 0;                                                                    
int maxHeight = 0;                                                                
int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};                                  

while (!minHeap.empty()) {                                                        
    auto [height, row, col] = minHeap.top();                                      
    minHeap.pop();                                                                

    maxHeight = max(maxHeight, height);                                           

    // Check all 4 neighbors                                                      
    for (auto& dir : dirs) {                                                      
        int newRow = row + dir[0];                                                
        int newCol = col + dir[1];                                                

        if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n                
            && !visited[newRow][newCol]) {                                        

            visited[newRow][newCol] = true;                                       

            // Water trapped = max boundary height - current cell height          
            if (heightMap[newRow][newCol] < maxHeight) {                          
                water += maxHeight - heightMap[newRow][newCol];                   
            }                                                                     

            minHeap.push({heightMap[newRow][newCol], newRow, newCol});            
        }                                                                         
    }                                                                             
}                                                                                 

return water;                                                                     

}
```

TIME: O(MxN log(MxN))  |  SPACE: O(MxN)

WHY MIN HEAP?
Process cells from lowest boundary first. This ensures water level
is correctly determined by surrounding walls!

INTUITION - THE "PEELING ONION" APPROACH:
1. Start from outer boundary (like shoreline)
2. Water can't go higher than boundary walls
3. Process lowest boundary cell first
4. Move inward, layer by layer
5. Each new cell's water level = max(current_height, boundary_max)

**VISUAL EXAMPLE:**
Boundary: [3, 5, 2, 4] (edges of grid)
Start with 2 (lowest boundary)
Process neighbors of 2:
- If neighbor is 1, water fills to level 2 (traps 1 unit)
- If neighbor is 3, no water trapped, becomes new boundary

Always process LOWEST boundary to ensure water doesn't leak!

WHY LIKE DIJKSTRA?
Both find optimal path/level by processing minimum first.
Dijkstra: shortest distance from source
This: minimum boundary height determines water level

**COMMON MISTAKE:**
 Processing cells in row/column order
 Process by height (lowest boundary first) using min heap

**GOLDEN RULE:**
Water level at a cell = minimum height among ALL surrounding boundaries.
By processing lowest first, we guarantee correct water level!

### **PROBLEM: IPO / Maximum Capital (LC 502)** 

PROBLEM: Start with capital W, do at most K projects to maximize capital

**BRILLIANT TWO-HEAP APPROACH:**
- Min heap: Projects by capital requirement (not yet affordable)
- Max heap: Affordable projects by profit

STRATEGY: At each step, pick highest profit among affordable projects

**TEMPLATE:**

```cpp
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
int n = profits.size();                                      
vector<pair<int, int>> projects;  // {capital, profit}       

for (int i = 0; i < n; i++) {                                
    projects.push_back({capital[i], profits[i]});            
}                                                            

// Sort by capital requirement                               
sort(projects.begin(), projects.end());                      

priority_queue<int> maxHeap;  // Available projects by profit
int idx = 0;                                                 

for (int i = 0; i < k; i++) {                                
    // Add all newly affordable projects                     
    while (idx < n && projects[idx].first <= w) {            
        maxHeap.push(projects[idx].second);                  
        idx++;                                               
    }                                                        

    // If no projects available, break                       
    if (maxHeap.empty()) break;                              

    // Take most profitable project                          
    w += maxHeap.top();                                      
    maxHeap.pop();                                           
}                                                            

return w;                                                    

}
```

TIME: O(N log N)  |  SPACE: O(N)

**KEY INSIGHT:**
Don't need min heap if we pre-sort! Just track index.
Greedy works: always maximize profit now to unlock more projects later.

**INTUITION:**
You're an investor with capital W. Some projects need minimum capital.

Strategy:
1. Look at all affordable projects (capital < W)
2. Pick most profitable one
3. Do it! Now you have more capital
4. More projects become affordable, repeat

Why greedy works? More capital now = more options later!

**EXAMPLE:**
```
W=0, profits=[1,2,3], capital=[0,1,1]
```

Step 1: Affordable=[project0], pick it, W=0+1=1
Step 2: Affordable=[project1,project2], pick project2 (max profit), W=1+3=4
Step 3: Can pick project1, W=4+2=6

Total: 6 (optimal!)

WHY TWO HEAPS IDEA?
Original: minHeap(unavailable by capital) + maxHeap(available by profit)
Optimized: Pre-sort + index > no need for unavailable heap!

**COMMON MISTAKE:**
 Trying all K! permutations
 Greedy: pick best available, repeat

### **PROBLEM: Minimum Interval to Include Each Query (LC 1851)**  HARD

PROBLEM: For each query, find smallest interval containing it

APPROACH: Sort queries + intervals, use min heap

**STRATEGY:**
1. Sort intervals by start time
2. Sort queries (but remember original index)
3. For each query, add relevant intervals, remove expired ones

**TEMPLATE:**

```cpp
vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
int n = queries.size();                                                 
vector<pair<int, int>> sortedQueries;                                   

for (int i = 0; i < n; i++) {                                           
    sortedQueries.push_back({queries[i], i});                           
}                                                                       
sort(sortedQueries.begin(), sortedQueries.end());                       
sort(intervals.begin(), intervals.end());                               

// Min heap: {size, end}                                                
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;

vector<int> result(n, -1);                                              
int idx = 0;                                                            

for (auto& [query, originalIdx] : sortedQueries) {                      
    // Add all intervals that start before or at query                  
    while (idx < intervals.size() && intervals[idx][0] <= query) {      
        int start = intervals[idx][0];                                  
        int end = intervals[idx][1];                                    
        int size = end - start + 1;                                     
        minHeap.push({size, end});                                      
        idx++;                                                          
    }                                                                   

    // Remove intervals that end before query                           
    while (!minHeap.empty() && minHeap.top().second < query) {          
        minHeap.pop();                                                  
    }                                                                   

    // Answer for this query                                            
    if (!minHeap.empty()) {                                             
        result[originalIdx] = minHeap.top().first;                      
    }                                                                   
}                                                                       

return result;                                                          

}
```

TIME: O((N+M) log N)  |  SPACE: O(N)

**WHY IT WORKS:**
By processing queries in sorted order, we incrementally build
valid interval set without redundant work!

**INTUITION - THE SWEEP LINE APPROACH:**
Imagine sweeping left to right across number line:

Queries: [1, 5, 10, 15]
Intervals: [[1,4], [7,10], [3,9]]

At query=1: Consider intervals starting < 1: [[1,4]]
Remove intervals ending < 1: none
Answer: size of [1,4] = 4

At query=5: Add intervals starting < 5: [[3,9], [7,10]] (already have [1,4])
Remove intervals ending < 5: [[1,4]]
Heap has: [[3,9], [7,10]]
Answer: size 7 (from [3,9])

**KEY OPTIMIZATION:**
Sort queries! Otherwise can't incrementally add intervals.
Sorting enables O(N+M) sweeping instead of O(NxM) brute force.

**BRILLIANT TRICK:**
Remember original query indices! Sort queries but return in original order.
This is a common pattern for "answer queries in different order than given."

**SIMILAR PATTERN:**
Many "offline query" problems benefit from sorting queries first!

### **PROBLEM: Find K-th Smallest Prime Fraction (LC 786)**  HARD

PROBLEM: Array sorted in ascending order. Find kth smallest fraction arr[i]/arr[j] where i < j

### APPROACH 1: Min Heap (Similar to K Pairs)

```cpp
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
int n = arr.size();                                                                     

// Min heap: {fraction_value, numerator_idx, denominator_idx}                           
priority_queue<tuple<double,int,int>, vector<tuple<double,int,int>>, greater<>> minHeap;

// Start with smallest fractions: arr[i]/arr[n-1] for all i                             
for (int i = 0; i < n - 1; i++) {                                                       
    minHeap.push({(double)arr[i] / arr[n-1], i, n-1});                                  
}                                                                                       

// Pop k-1 times                                                                        
for (int i = 0; i < k - 1; i++) {                                                       
    auto [val, numIdx, denIdx] = minHeap.top();                                         
    minHeap.pop();                                                                      

    // Add next fraction with same numerator                                            
    if (denIdx - 1 > numIdx) {                                                          
        minHeap.push({(double)arr[numIdx] / arr[denIdx-1], numIdx, denIdx-1});          
    }                                                                                   
}                                                                                       

auto [val, numIdx, denIdx] = minHeap.top();                                             
return {arr[numIdx], arr[denIdx]};                                                      

}
```

TIME: O(K log N)  |  SPACE: O(N)

**INTUITION - HEAP APPROACH:**
Think of it like finding K-th smallest in multiplication table:
[1/n, 2/n, ..., (n-1)/n] (row 1, denominator = last element)
[1/(n-1), 2/(n-1), ...] (row 2)
...

Start with smallest from each row: i/arr[n-1]
Pop K times, each time add next in same row
Similar to merging K sorted lists!

### APPROACH 2: Binary Search on Fraction Value (MORE EFFICIENT!)

```cpp
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
int n = arr.size();                                         
double lo = 0.0, hi = 1.0;                                  

while (hi - lo > 1e-9) {                                    
    double mid = lo + (hi - lo) / 2.0;                      

    auto [count, numIdx, denIdx] = countFractions(arr, mid);

    if (count < k) {                                        
        lo = mid;                                           
    } else if (count > k) {                                 
        hi = mid;                                           
    } else {                                                
        return {arr[numIdx], arr[denIdx]};                  
    }                                                       
}                                                           

auto [count, numIdx, denIdx] = countFractions(arr, lo);     
return {arr[numIdx], arr[denIdx]};                          

}

// Count fractions < target, also track largest such fraction
```

tuple<int, int, int> countFractions(vector<int>& arr, double target) {
```
int n = arr.size();                                             
int count = 0;                                                  
int numIdx = 0, denIdx = n - 1;                                 
int i = -1;                                                     

for (int j = 1; j < n; j++) {                                   
    // Find largest i such that arr[i]/arr[j] <= target         
    while (i + 1 < j && arr[i + 1] < arr[j] * target) {         
        i++;                                                    
    }                                                           

    count += (i + 1);                                           

    // Track largest fraction < target                          
    if (i >= 0 && arr[i] * arr[denIdx] > arr[numIdx] * arr[j]) {
        numIdx = i;                                             
        denIdx = j;                                             
    }                                                           
}                                                               

return {count, numIdx, denIdx};                                 
```

```
}
```

TIME: O(N log(max/min))  |  SPACE: O(1)

**KEY TRICK:**
Compare fractions without division: a/b < c/d > axd < bxc

**INTUITION - BINARY SEARCH APPROACH:**
Search space: [0.0, 1.0] (all possible fraction values)

For each guess (mid = 0.5):
- Count how many fractions < 0.5
- If count > k, answer is < 0.5 (search left)
- If count < k, answer is > 0.5 (search right)

**WHY THIS IS BRILLIANT:**
Instead of generating all N2 fractions, we:
1. Guess the answer (a value between 0 and 1)
2. Count in O(N) how many fractions < guess
3. Binary search on the value space!

**COUNTING TRICK:**
For fixed denominator arr[j], find largest i where arr[i]/arr[j] < target
Since sorted: arr[i] < arr[j] x target
Use two pointers! i doesn't reset between j iterations.

**COMMON MISTAKE:**
 Floating point precision issues
 Run binary search until error < 1e-9, also track actual fraction indices

### **PROBLEM: Process Tasks Using Servers (LC 1882)** 

PROBLEM: Assign tasks to servers with minimum weight/index, track when they free up

APPROACH: Two heaps!
- availableHeap: {weight, index} - free servers
- busyHeap: {free_time, weight, index} - busy servers

**TEMPLATE:**

```cpp
vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
int n = servers.size(), m = tasks.size();                                      

// Min heap for available: {weight, index}                                     
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> available;     

// Min heap for busy: {free_time, weight, index}                               
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> busy;

// Initialize all servers as available                                         
for (int i = 0; i < n; i++) {                                                  
    available.push({servers[i], i});                                           
}                                                                              

vector<int> result(m);                                                         
int time = 0;                                                                  

for (int i = 0; i < m; i++) {                                                  
    time = max(time, i);                                                       

    // Free up servers that finished by current time                           
    while (!busy.empty() && get<0>(busy.top()) <= time) {                      
        auto [freeTime, weight, idx] = busy.top();                             
        busy.pop();                                                            
        available.push({weight, idx});                                         
    }                                                                          

    // If no server available, jump to next free time                          
    if (available.empty()) {                                                   
        auto [freeTime, weight, idx] = busy.top();                             
        busy.pop();                                                            
        time = freeTime;                                                       
        available.push({weight, idx});                                         
    }                                                                          

    // Assign task to best available server                                    
    auto [weight, idx] = available.top();                                      
    available.pop();                                                           

    result[i] = idx;                                                           
    busy.push({time + tasks[i], weight, idx});                                 
}                                                                              

return result;                                                                 

}
```

TIME: O((M+N) log N)  |  SPACE: O(N)

**KEY PATTERN:**
Two heaps to track state transitions (available - busy)
Common in simulation problems!

**INTUITION - RESOURCE ALLOCATION OVER TIME:**
Think of servers at a restaurant:
- Available heap: Waiters ready to serve (pick best available)
- Busy heap: Waiters serving customers (track when they finish)

When customer arrives:
1. Check if any waiter finished (free them up)
2. Pick best available waiter (min weight/index)
3. Assign to customer, move to busy heap
4. If all busy, wait for earliest to finish

WHY TWO HEAPS?
Available: Need best available (min weight, then min index)
Busy: Need earliest to finish (min finish_time)
Different priorities = different heaps!

**REAL-WORLD ANALOGY:**
- CPU scheduling (processes waiting vs running)
- Airport gates (available vs occupied)
- Uber drivers (free vs on trip)

**COMMON MISTAKE:**
 Simulating time tick-by-tick (too slow!)
 Jump to next event (task arrival or server free)

**GOLDEN RULE:**
When resources have TWO states with different priorities,
use TWO heaps to track each state!

## **PART 5: QUICK DECISION GUIDE**

### **DECISION TREE**

START: Is this a Kth/K-type problem?
```
                                                 |
+- YES > Do you need ALL K elements?              
|                                                |
|   +- YES > Use HEAP                             
|   |   +- Kth smallest? > Max Heap of size K     
|   |   +- Kth largest? > Min Heap of size K      
|                                                |
|   +- NO > Only need Kth value?                  
|       +- Can you define [lo, hi] bounds?        
|                                                |
|           +- YES > Can you write count function?
|                                            |   |
|           |   +- YES > Use BINARY SEARCH + COUNT
|                                            |   |
|           |   +- NO > Try different approach    
|                                                |
|           +- NO > Use HEAP or other approach    
                                                 |
+- NO > Not a Kth problem, use other techniques   
```

### **COMMON COUNT FUNCTIONS**

### Problem Type              Count Function               Time Complexity

Sorted Matrix            Staircase from top-right     O(N)
Pair Distance            Sliding window               O(N)
Split Array              Greedy grouping              O(N)
Eating Bananas           Ceiling division sum         O(N)
Magical Number           x/A + x/B - x/LCM            O(1)
Running Computers        sum(min(battery, T))         O(N)
Repeating Substring      Hash set check               O(N) or O(N2)

### **COMPLEXITY CHEAT SHEET**

### Approach                     Time                    Space       When to Use

Max Heap (Kth Smallest)     O(N log K)              O(K)        Need all K elements
Min Heap (Kth Largest)      O(N log K)              O(K)        Need all K elements
Binary Search + Count       O(log(R) x O(count))    O(1)        Only need Kth value
Merge K Lists               O(N log K)              O(K)        K sorted streams
Bucket Sort (Frequency)     O(N)                    O(N)        Frequency problems
QuickSelect                 O(N) avg, O(N2) worst   O(1)        Kth element in array

## **PART 6: PROBLEM LIST BY CATEGORY**

**PATTERN 1: BASIC KTH ELEMENT**

- 215.  Kth Largest Element in Array 
- 347.  Top K Frequent Elements 
- 692.  Top K Frequent Words 
- 703.  Kth Largest Element in Stream 
- 973.  K Closest Points to Origin 
- 1985. Find the Kth Largest Integer in the Array 
- 1086. High Five 

**PATTERN 2: TOP K FREQUENT**

- 347.  Top K Frequent Elements 
- 692.  Top K Frequent Words 
- 1481. Least Number of Unique Integers after K Removals 

**PATTERN 4: MERGE K SORTED**

- 23.   Merge K Sorted Lists 
- 373.  Find K Pairs with Smallest Sums 
- 378.  Kth Smallest Element in Sorted Matrix 
- 658.  Find K Closest Elements 
- 1508. Range Sum of Sorted Subarray Sums 

**PATTERN 6: TWO HEAPS (Median)**

- 295.  Find Median from Data Stream 
- 480.  Sliding Window Median 
- 502.  IPO (Maximum Capital) 

**PATTERN 7: INTERVALS / SWEEP LINE**

- 253.  Meeting Rooms II 
- 630.  Course Schedule III 
- 1094. Car Pooling 
- 1851. Minimum Interval to Include Each Query 
- 2251. Number of Flowers in Full Bloom 

**PATTERN 8: GREEDY + HEAP (Reorganize/Schedule)**

- 621.  Task Scheduler 
- 767.  Reorganize String 
- 984.  Longest Happy String 
- 358.  Rearrange String k Distance Apart 
- 1054. Distant Barcodes 

**PATTERN 9: SMALLEST RANGE / MERGE K LISTS**

- 632.  Smallest Range Covering Elements from K Lists 

**PATTERN 10: GREEDY RESOURCE ALLOCATION**

- 1642. Furthest Building You Can Reach 

**PATTERN 11: SIMULATION WITH HEAP**

- 1046. Last Stone Weight 
- 2558. Take Gifts From the Richest Pile 
- 3264. Final Array State After K Multiplication Operations I 

**PATTERN 12: SORT + HEAP OPTIMIZATION**

- 857.  Minimum Cost to Hire K Workers 
- 1383. Maximum Performance of a Team 
- 2542. Maximum Subsequence Score 

**PATTERN 13: HEAP WITH TRANSFORMATIONS**

- 1675. Minimize Deviation in Array 

**PATTERN 14: DESIGN PROBLEMS**

- 355.  Design Twitter 
- 1845. Seat Reservation Manager 

**PATTERN 15: GREEDY MERGE (Huffman)**

- 1046. Last Stone Weight 
- 1167. Minimum Cost to Connect Sticks 

**TWO HEAPS / RESOURCE ALLOCATION OVER TIME**

- 1834. Single-Threaded CPU 
- 1882. Process Tasks Using Servers 
- 2402. Meeting Rooms III 

**ADVANCED HEAP**

- 264.  Ugly Number II 
- 407.  Trapping Rain Water II 
- 1057. Campus Bikes 
- 2940. Find Building Where Alice and Bob Can Meet 
- 1499. Constrained Subsequence Sum  (Heap/Deque + DP)

**BINARY SEARCH APPROACH (Only Need Kth Value)**

- 410. Split Array Largest Sum  HARD
- 668. Kth Smallest Number in Multiplication Table HARD
- 719. Find K-th Smallest Pair Distance  HARD
- 786. K-th Smallest Prime Fraction HARD
- 875. Koko Eating Bananas
- 878. Nth Magical Number HARD
- 1011. Capacity To Ship Packages Within D Days
- 1044. Longest Duplicate Substring HARD
- 1062. Longest Repeating Substring
- 1231. Divide Chocolate HARD (Premium)
- 1439. Find the Kth Smallest Sum of Matrix HARD
- 1482. Minimum Number of Days to Make m Bouquets
- 1552. Magnetic Force Between Two Balls
- 1760. Minimum Limit of Balls in Bag
- 1870. Minimum Speed to Arrive on Time
- 1918. Kth Smallest Subarray Sum HARD
- 1970. Last Day Where You Can Still Cross HARD
- 1986. Minimum Number of Work Sessions HARD
- 2040. Kth Smallest Product of Two Sorted Arrays  HARD
- 2141. Maximum Running Time of N Computers HARD
- 2187. Minimum Time to Complete Trips
- 2226. Maximum Candies Allocated to K Children
- 2187. Minimum Time to Complete Trips
- 2528. Maximize the Minimum Powered City HARD
- 2563. Count Fair Pairs
- 2594. Minimum Time to Repair Cars
- 3007. Maximum Number (Sum of Prices < K) HARD
- 3116. Kth Smallest Amount With Single Denomination  HARD

**ADVANCED PATTERNS**

**Two Heaps Pattern:**
- 295. Find Median from Data Stream
- 480. Sliding Window Median
- 502. IPO

**Interval Sweep Line:**
- 253. Meeting Rooms II
- 630. Course Schedule III
- 1851. Minimum Interval to Include Each Query

**Greedy with Heap:**
- 621. Task Scheduler
- 767. Reorganize String
- 1167. Minimum Cost to Connect Sticks

**Mathematical Count Functions:**
- Inclusion-Exclusion: 878, 3116
- Power Set: 3116
- Staircase: 378, 668
- Negative Handling: 2040

**String/Sequence Generation:**
- 264. Ugly Number II (3-pointer DP)
- 1044. Longest Duplicate Substring (Rolling Hash)

**2D/Multi-dimensional:**
- 407. Trapping Rain Water II
- 632. Smallest Range from K Lists

**Floating Point Binary Search:**
- 786. K-th Smallest Prime Fraction

## **PART 7: ADVANCED TIPS & TRICKS**

**TIP 1: Avoid Integer Overflow**

```
// BAD
int mid = (lo + hi) / 2;  // Can overflow!

// GOOD
int mid = lo + (hi - lo) / 2;
```

**TIP 2: The +1 Trick for Maximum Problems**

```
// For MAXIMUM problems to avoid infinite loop
while (lo < hi) {
int mid = lo + (hi - lo + 1) / 2;  // +1 here!
if (isPossible(mid)) {                        
    lo = mid;    // Not mid + 1               
} else {                                      
    hi = mid - 1;                             
}                                             

}
```

**TIP 3: Ceiling Division Trick**

```
// Calculate ceil(a / b) without floating point
int ceilDiv = (a + b - 1) / b;
```

**TIP 4: LCM from GCD**

```
long long lcm = (long long)a * b / __gcd(a, b);
```

**TIP 5: Comparing Fractions Without Division**

```
// To check if a/b < c/d without division
if (a * d < b * c) { ... }  // Cross multiply
```

**TIP 6: Optimization - Early Exit in Count**

```cpp
int count(vector<int>& arr, int target, int k) {
int cnt = 0;                                
for (int num : arr) {                       
    cnt += ...;                             
    if (cnt > k) return cnt;  // Early exit!
}                                           
return cnt;                                 

}
```

## **PART 8: UNIQUE PATTERNS SUMMARY** 

### ** MUST-KNOW UNIQUE PATTERNS**

**1. TWO HEAPS - Median Finding**

Pattern: Max heap (left) + Min heap (right)
Use Case: Dynamic median, balanced partitions
Problems: 295, 480, 502
Key: Keep heaps balanced, median at boundary

**2. INTERVAL SWEEP LINE**

Pattern: Sort intervals + min heap for end times
Use Case: Overlapping intervals, resource allocation
Problems: 253, 630, 1094, 1851
Key: Remove finished intervals as you go

**3. GREEDY WITH HEAP**

Pattern: Max heap by frequency/value + greedy selection
Use Case: Reorganize sequence, task scheduling
Problems: 621, 767, 1167
Key: Always pick best available option

**4. SMALLEST RANGE FROM K LISTS**

Pattern: Min heap + tracking max value
Use Case: Coverage problems across multiple sources
Problems: 632
Key: Move minimum forward while tracking range

**5. 2D BOUNDARY PROCESSING**

Pattern: Min heap starting from boundaries (like Dijkstra)
Use Case: 2D elevation/water problems
Problems: 407
Key: Process from outside to inside, track max height

**6. MULTIPLE HEAP COORDINATION**

Pattern: Available heap + Busy heap (state transitions)
Use Case: Server/resource allocation over time
Problems: 1882, 502
Key: Track state changes with multiple heaps

**7. UGLY NUMBER / SEQUENCE GENERATION**

Pattern: Min heap OR multi-pointer DP
Use Case: Generate sequence with specific properties
Problems: 264, 313
Key: Build sequence incrementally, avoid duplicates

**8. BINARY SEARCH ON FRACTIONS**

Pattern: Binary search [0.0, 1.0] + count function
Use Case: Kth smallest fraction
Problems: 786
Key: Compare fractions without division (cross multiply)

### ** PATTERN SELECTION CHEAT SHEET**

### Problem Keyword                   >  Pattern to Use

"Median" / "Middle element"       >  Two Heaps
"Meeting rooms" / "Intervals"     >  Sweep Line + Min Heap
"Reorganize" / "No adjacent same" >  Greedy + Max Heap (frequency)
"K lists" / "Multiple sources"    >  Min Heap (merge/range)
"2D water" / "Elevation"          >  Boundary Min Heap
"Servers" / "Resource over time"  >  Multiple Heaps (available/busy)
"Kth smallest pair/product"       >  Binary Search + Count
"Split into K parts"              >  Binary Search (min/max optimization)
"Ugly/Prime/Magical numbers"      >  Heap or Multi-pointer DP
"Connect ropes/sticks"            >  Min Heap (greedy merge)

### **⚡ INTERVIEW TIPS**

1. **Start with Heap if unclear**: O(N log K) is usually acceptable

2. **Recognize Binary Search signals**:
- "Minimum of maximum"
- "Maximum of minimum"
- Can define bounds [lo, hi]

3. **Two Heaps = Partitioning**: When you need to split data dynamically

4. **Sort first if possible**: Makes heap logic simpler

5. **Lazy deletion**: For sliding window median, mark as deleted instead of removing

6. **Custom comparators**: Practice writing for different orderings

7. **Space-time tradeoff**: Heap uses O(K), Binary Search uses O(1)

8. **Edge cases to check**:
- K = 0 or K = N
- Empty input
- All elements same
- Single element
- Ties in heap

## **MASTER PROBLEM MAPPING TABLE**

```
+---------------------------------------------------------+----------------------------+
| Problem                                                 | Pattern                    |
+---------------------------------------------------------+----------------------------+
| Kth Largest Element In a Stream                         | 1 - Basic Kth (Min Heap)   |
| Last Stone Weight                                       | 11/15 - Simulation/Merge   |
| Take Gifts From the Richest Pile                        | 11 - Simulation            |
| Final Array State After K Multiplication Operations I   | 11 - Simulation            |
| High Five                                               | 1 - Top K per group        |
| K Closest Points to Origin                              | 5 - K Closest              |
| Kth Largest Element In An Array                         | 1 - Basic Kth (Min Heap)   |
| Task Scheduler                                          | 8 - Greedy + Heap          |
| Design Twitter                                          | 14 - Design (Merge K)      |
| Least Number of Unique Integers after K Removal         | 2 - Frequency + Greedy     |
| Furthest Building You Can Reach                         | 10 - Resource Allocation   |
| Minimize Deviation in Array                             | 13 - Transformations       |
| Maximum Subsequence Score                               | 12 - Sort + Heap           |
| Single Threaded CPU                                     | Two Heaps (Busy/Available) |
| Seat Reservation Manager                                | 14 - Design (Min Heap)     |
| Process Tasks Using Servers                             | Two Heaps (Busy/Available) |
| Find The Kth Largest Integer In The Array               | 1 - Basic Kth              |
| Reorganize String                                       | 8 - Greedy + Heap          |
| Longest Happy String                                    | 8 - Greedy + Heap          |
| Car Pooling                                             | 7 - Sweep Line             |
| Range Sum of Sorted Subarray Sums                       | 4 - Generate + Sort/Heap   |
| Minimum Cost to Connect Sticks                          | 15 - Greedy Merge          |
| Campus Bikes                                            | Multi-criteria Heap        |
| Find Median From Data Stream                            | 6 - Two Heaps              |
| Maximum Performance of a Team                           | 12 - Sort + Heap           |
| IPO                                                     | 6 - Two Heaps              |
| Minimum Cost to Hire K Workers                          | 12 - Sort + Heap           |
| Number of Flowers in Full Bloom                         | 7 - Sweep Line / BS        |
| Constrained Subsequence Sum                             | Heap/Deque + DP            |
| Find Building Where Alice and Bob Can Meet              | Monotonic Stack + Heap     |
| Rearrange String k Distance Apart                       | 8 - Greedy + Heap          |
+---------------------------------------------------------+----------------------------+

+--------------------------------------------------------------------------------------+
|                     HEAP PATTERN DECISION FLOWCHART                                  |
+--------------------------------------------------------------------------------------+
|                                                                                      |
|  Need Kth smallest/largest element?                                                  |
|    YES > Pattern 1 (Max/Min Heap of size K)                                          |
|                                                                                      |
|  Need to find median dynamically?                                                    |
|    YES > Pattern 6 (Two Heaps)                                                       |
|                                                                                      |
|  Reorganize / No adjacent same elements?                                             |
|    YES > Pattern 8 (Greedy + Max Heap by frequency)                                  |
|                                                                                      |
|  Resource allocation over time (servers, CPUs)?                                      |
|    YES > Two Heaps (Available + Busy)                                                |
|                                                                                      |
|  Merge K sorted lists/arrays?                                                        |
|    YES > Pattern 4 (Min Heap with K elements)                                        |
|                                                                                      |
|  Intervals / Meeting rooms / Concurrent events?                                      |
|    YES > Pattern 7 (Sweep Line + Heap)                                               |
|                                                                                      |
|  Simulation: repeatedly pick max/min, operate, put back?                             |
|    YES > Pattern 11 (Simulation with Heap)                                           |
|                                                                                      |
|  Optimize score = sum x min? (or similar)                                            |
|    YES > Pattern 12 (Sort by one factor, Heap for other)                             |
|                                                                                      |
|  Transform elements to minimize deviation?                                           |
|    YES > Pattern 13 (Heap with Transformations)                                      |
|                                                                                      |
|  Connect/Merge with minimum cost?                                                    |
|    YES > Pattern 15 (Greedy Merge - Huffman style)                                   |
|                                                                                      |
+--------------------------------------------------------------------------------------+

+--------------------------------------------------------------------------------------+
|                         HEAP GOLDEN RULES                                            |
+--------------------------------------------------------------------------------------+
|                                                                                      |
|  1⃣  Kth SMALLEST > Use MAX heap of size K                                           |
|  2⃣  Kth LARGEST > Use MIN heap of size K                                            |
|  3⃣  Median > Two heaps (max for left, min for right)                                |
|  4⃣  Merge K lists > Min heap with K elements                                        |
|  5⃣  Greedy frequency > Max heap by count                                            |
|  6⃣  Resource over time > Two heaps (available + busy)                               |
|  7⃣  Greedy merge > Always merge smallest two (Huffman)                              |
|  8⃣  Sort + Heap > Sort by constraint, heap for optimization                         |
|                                                                                      |
+--------------------------------------------------------------------------------------+

================================================================================        
                                **END**                                                 
================================================================================        
```
