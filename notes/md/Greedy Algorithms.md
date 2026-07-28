# **GREEDY ALGORITHMS - COMPLETE INTERVIEW GUIDE**

Make locally optimal choices to find global optimum!

### **TABLE OF CONTENTS**

PART 1: Core Concepts
PART 2: The 15 Essential Greedy Patterns (with 2-3 solved problems each)
PART 3: Proof Techniques
PART 4: Quick Decision Guide
PART 5: Complete Problem List

## **PART 1: CORE CONCEPTS**

### ** WHAT IS GREEDY ALGORITHM?**

**DEFINITION:**
Build solution piece by piece, always choosing the next piece that offers
the most obvious and immediate benefit.

**KEY CHARACTERISTIC:**
- Make LOCALLY optimal choice at each step
- Hope that these local choices lead to GLOBAL optimum
- Never reconsider previous choices (no backtracking)

 **MEMORY AID**: "**S**ort, **P**ick, **P**rofit" (Greedy loves sorting!)

**TWO KEY PROPERTIES FOR GREEDY:**

1. **Greedy Choice Property**: Locally optimal → Globally optimal
2. **Optimal Substructure**: Optimal solution contains optimal subproblems

### GREEDY vs DP:

Greedy:  O(N) or O(N log N), make choice without looking back
DP:      O(N2) or more, explore multiple possibilities

- TRY GREEDY FIRST! If it doesn't work, fall back to DP

## **PART 2: THE 15 ESSENTIAL GREEDY PATTERNS**

### **PATTERN 1: INTERVAL SCHEDULING** 

CORE IDEA: Sort by END time, pick earliest ending interval
WHY: Leaves maximum room for future intervals

**TEMPLATE:**

```
// Sort by end time, greedily pick non-overlapping
sort(intervals.begin(), intervals.end(),
 [](auto& a, auto& b) { return a[1] < b[1]; });

int count = 0, lastEnd = INT_MIN;
for (auto& interval : intervals) {
if (interval[0] >= lastEnd) {
    count++;                 
    lastEnd = interval[1];   
}                            

}
```

## **SOLVED PROBLEM 1.1: Non-overlapping Intervals (LC 435)** 

PROBLEM: Given intervals, find minimum number to remove so rest don't overlap.

**EXAMPLE:**
Input: [[1,2],[2,3],[3,4],[1,3]]
Output: 1 (remove [1,3])

**APPROACH:**
Find max non-overlapping intervals. Answer = total - max.

```java
class Solution {
```

public:
```
int eraseOverlapIntervals(vector<vector<int>>& intervals) {  
    if (intervals.empty()) return 0;                         

    // Sort by end time                                      
    sort(intervals.begin(), intervals.end(),                 
         [](auto& a, auto& b) { return a[1] < b[1]; });      

    int count = 1;  // First interval always taken           
    int lastEnd = intervals[0][1];                           

    for (int i = 1; i < intervals.size(); i++) {             
        if (intervals[i][0] >= lastEnd) {  // Non-overlapping
            count++;                                         
            lastEnd = intervals[i][1];                       
        }                                                    
    }                                                        

    return intervals.size() - count;                         
}                                                            
```

```
};
```

TIME: O(N log N)  |  SPACE: O(1)

## **SOLVED PROBLEM 1.2: Merge Intervals (LC 56)** 

PROBLEM: Merge all overlapping intervals.

**EXAMPLE:**
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]

**APPROACH:**
Sort by start time. Extend current interval or start new one.

```java
class Solution {
```

public:
```
vector<vector<int>> merge(vector<vector<int>>& intervals) {           
    if (intervals.empty()) return {};                                 

    // Sort by start time                                             
    sort(intervals.begin(), intervals.end());                         

    vector<vector<int>> result;                                       
    result.push_back(intervals[0]);                                   

    for (int i = 1; i < intervals.size(); i++) {                      
        // If overlapping with last merged interval                   
        if (intervals[i][0] <= result.back()[1]) {                    
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        } else {                                                      
            result.push_back(intervals[i]);                           
        }                                                             
    }                                                                 

    return result;                                                    
}                                                                     
```

```
};
```

TIME: O(N log N)  |  SPACE: O(N)

## **SOLVED PROBLEM 1.3: Meeting Rooms II (LC 253)** 

PROBLEM: Find minimum conference rooms needed.

**EXAMPLE:**
Input: [[0,30],[5,10],[15,20]]
Output: 2

**APPROACH:**
Track start/end events. Max concurrent meetings = answer.

```java
class Solution {
```

public:
```
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<int> starts, ends;                        

    for (auto& interval : intervals) {               
        starts.push_back(interval[0]);               
        ends.push_back(interval[1]);                 
    }                                                

    sort(starts.begin(), starts.end());              
    sort(ends.begin(), ends.end());                  

    int rooms = 0, maxRooms = 0;                     
    int s = 0, e = 0;                                

    while (s < starts.size()) {                      
        if (starts[s] < ends[e]) {                   
            rooms++;  // Meeting starts              
            s++;                                     
        } else {                                     
            rooms--;  // Meeting ends                
            e++;                                     
        }                                            
        maxRooms = max(maxRooms, rooms);             
    }                                                

    return maxRooms;                                 
}                                                    
```

```java
};

// Alternative: Min Heap approach
class Solution2 {
```

public:
```
int minMeetingRooms(vector<vector<int>>& intervals) {               
    sort(intervals.begin(), intervals.end());                       

    priority_queue<int, vector<int>, greater<int>> pq;  // End times

    for (auto& interval : intervals) {                              
        if (!pq.empty() && pq.top() <= interval[0]) {               
            pq.pop();  // Room freed up                             
        }                                                           
        pq.push(interval[1]);                                       
    }                                                               

    return pq.size();                                               
}                                                                   
```

```
};
```

TIME: O(N log N)  |  SPACE: O(N)

### **PATTERN 2: SORTING + GREEDY DECISION** 

CORE IDEA: Sort by key property, make greedy assignments
KEY: Figure out WHAT to sort by!

**TEMPLATE:**

```
sort(items.begin(), items.end(), [](auto& a, auto& b) {
return /* sorting criterion */;

});
// Then make greedy choices
```

## **SOLVED PROBLEM 2.2: Queue Reconstruction by Height (LC 406)** 

PROBLEM: People with [height, k] where k = people taller in front.
Reconstruct the queue.

**EXAMPLE:**
Input: [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]

**APPROACH:**
Sort tallest first (k ascending for same height).
Insert at position k - shorter people don't affect taller ones!

```java
class Solution {
```

public:
```
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    // Sort: height DESC, then k ASC                               
    sort(people.begin(), people.end(), [](auto& a, auto& b) {      
        return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);       
    });                                                            

    vector<vector<int>> result;                                    

    for (auto& person : people) {                                  
        // Insert at position k                                    
        result.insert(result.begin() + person[1], person);         
    }                                                              

    return result;                                                 
}                                                                  
```

```
};
```

TIME: O(N2) due to insertions  |  SPACE: O(N)

## **SOLVED PROBLEM 2.3: Two City Scheduling (LC 1029)** 

PROBLEM: 2N people, costs[i] = [costA, costB]. Send N to each city.
Minimize total cost.

**EXAMPLE:**
Input: [[10,20],[30,200],[400,50],[30,20]]
Output: 110 (person 0,1 to A, person 2,3 to B)

**APPROACH:**
Sort by (costA - costB). Send first N to A (they save most by going to A).

```java
class Solution {
```

public:
```
int twoCitySchedCost(vector<vector<int>>& costs) {         
    // Sort by cost difference (benefit of going to A vs B)
    sort(costs.begin(), costs.end(), [](auto& a, auto& b) {
        return (a[0] - a[1]) < (b[0] - b[1]);              
    });                                                    

    int total = 0;                                         
    int n = costs.size() / 2;                              

    // First N go to city A, rest go to city B             
    for (int i = 0; i < n; i++) {                          
        total += costs[i][0];      // City A               
        total += costs[i + n][1];  // City B               
    }                                                      

    return total;                                          
}                                                          
```

```
};
```

TIME: O(N log N)  |  SPACE: O(1)

### **PATTERN 3: FRACTIONAL KNAPSACK / VALUE RATIO** 

CORE IDEA: Sort by value/weight ratio, pick highest ratio first
KEY: Works when we can take fractions. 0/1 version needs DP!

## **SOLVED PROBLEM 3.3: Maximum Units on a Truck (LC 1710)**

PROBLEM: Load boxes onto truck. boxTypes[i] = [count, unitsPerBox].
Maximize units with truckSize limit.

**EXAMPLE:**
Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
Output: 8 (1 box of 3 units + 2 boxes of 2 units + 1 box of 1 unit)

**APPROACH:**
Sort by units per box DESC. Pick boxes with most units first.

```java
class Solution {
```

public:
```
int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    // Sort by units per box (descending)                       
    sort(boxTypes.begin(), boxTypes.end(),                      
         [](auto& a, auto& b) { return a[1] > b[1]; });         

    int totalUnits = 0;                                         

    for (auto& box : boxTypes) {                                
        int count = min(box[0], truckSize);                     
        totalUnits += count * box[1];                           
        truckSize -= count;                                     

        if (truckSize == 0) break;                              
    }                                                           

    return totalUnits;                                          
}                                                               
```

```
};
```

TIME: O(N log N)  |  SPACE: O(1)

### **PATTERN 4: JOB SEQUENCING / DEADLINE SCHEDULING** 

CORE IDEA: Sort by deadline, use heap to replace worst choice if needed
KEY: When over capacity, drop the least valuable commitment

## **SOLVED PROBLEM 4.1: Course Schedule III (LC 630)** 

PROBLEM: courses[i] = [duration, lastDay]. Maximize courses taken.

**EXAMPLE:**
Input: [[100,200],[200,1300],[1000,1250],[2000,3200]]
Output: 3

**APPROACH:**
Sort by deadline. If can take, take it. If not, replace longest course if shorter.

```java
class Solution {
```

public:
```
int scheduleCourse(vector<vector<int>>& courses) {                
    // Sort by deadline                                           
    sort(courses.begin(), courses.end(),                          
         [](auto& a, auto& b) { return a[1] < b[1]; });           

    priority_queue<int> maxHeap;  // Durations of taken courses   
    int time = 0;                                                 

    for (auto& course : courses) {                                
        int duration = course[0], deadline = course[1];           

        if (time + duration <= deadline) {                        
            time += duration;                                     
            maxHeap.push(duration);                               
        } else if (!maxHeap.empty() && maxHeap.top() > duration) {
            // Replace longest course with this shorter one       
            time -= maxHeap.top();                                
            maxHeap.pop();                                        
            time += duration;                                     
            maxHeap.push(duration);                               
        }                                                         
    }                                                             

    return maxHeap.size();                                        
}                                                                 
```

```
};
```

TIME: O(N log N)  |  SPACE: O(N)

## **SOLVED PROBLEM 4.2: Task Scheduler (LC 621)** 

PROBLEM: Tasks with cooldown n between same tasks. Return min intervals.

**EXAMPLE:**
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8 (A -> B -> idle -> A -> B -> idle -> A -> B)

**APPROACH:**
Most frequent task determines frame size.
Formula: (maxFreq - 1) * (n + 1) + tasksWithMaxFreq

```java
class Solution {
```

public:
```
int leastInterval(vector<char>& tasks, int n) {                     
    vector<int> freq(26, 0);                                        
    for (char c : tasks) {                                          
        freq[c - 'A']++;                                            
    }                                                               

    int maxFreq = *max_element(freq.begin(), freq.end());           
    int maxCount = count(freq.begin(), freq.end(), maxFreq);        

    // (maxFreq - 1) full cycles + partial cycle with maxCount tasks
    int intervals = (maxFreq - 1) * (n + 1) + maxCount;             

    // At minimum, we need tasks.size() intervals                   
    return max((int)tasks.size(), intervals);                       
}                                                                   
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 4.3: Earliest Possible Day of Full Bloom (LC 2136)**

PROBLEM: plantTime[i] days to plant, growTime[i] days to bloom.
Find earliest day when all flowers bloom.

**EXAMPLE:**
Input: plantTime = [1,4,3], growTime = [2,3,1]
Output: 9

**APPROACH:**
Sort by growTime DESC. Plant longest-growing flowers first!

```java
class Solution {
```

public:
```
int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
    int n = plantTime.size();                                         
    vector<int> idx(n);                                               
    iota(idx.begin(), idx.end(), 0);                                  

    // Sort indices by grow time (descending)                         
    sort(idx.begin(), idx.end(), [&](int a, int b) {                  
        return growTime[a] > growTime[b];                             
    });                                                               

    int currentDay = 0;                                               
    int maxBloomDay = 0;                                              

    for (int i : idx) {                                               
        currentDay += plantTime[i];  // Finish planting               
        maxBloomDay = max(maxBloomDay, currentDay + growTime[i]);     
    }                                                                 

    return maxBloomDay;                                               
}                                                                     
```

```
};
```

TIME: O(N log N)  |  SPACE: O(N)

### **PATTERN 5: FREQUENCY MERGING / HUFFMAN-TYPE** 

CORE IDEA: Always merge two smallest elements first
WHY: Smaller items contribute to cost fewer times (deeper in tree)

## **SOLVED PROBLEM 5.1: Minimum Cost to Connect Sticks (LC 1167)**

PROBLEM: Connect sticks, cost = sum of two sticks. Minimize total cost.

**EXAMPLE:**
Input: [2,4,3]
Output: 14 (2+3=5, cost=5; 5+4=9, cost=9; total=14)

**APPROACH:**
Min heap. Always merge two smallest.

```java
class Solution {
```

public:
```
int connectSticks(vector<int>& sticks) {                   
    priority_queue<int, vector<int>, greater<int>> minHeap(
        sticks.begin(), sticks.end());                     

    int totalCost = 0;                                     

    while (minHeap.size() > 1) {                           
        int first = minHeap.top(); minHeap.pop();          
        int second = minHeap.top(); minHeap.pop();         

        int cost = first + second;                         
        totalCost += cost;                                 
        minHeap.push(cost);                                
    }                                                      

    return totalCost;                                      
}                                                          
```

```
};
```

TIME: O(N log N)  |  SPACE: O(N)

## **SOLVED PROBLEM 5.2: Reorganize String (LC 767)** 

PROBLEM: Rearrange string so no two adjacent chars are same.

**EXAMPLE:**
Input: "aab"
Output: "aba"

**APPROACH:**
Always pick most frequent char that isn't same as previous.

```java
class Solution {
```

public:
```
string reorganizeString(string s) {                
    vector<int> freq(26, 0);                       
    for (char c : s) freq[c - 'a']++;              

    // Max heap: {count, char}                     
    priority_queue<pair<int, char>> maxHeap;       
    for (int i = 0; i < 26; i++) {                 
        if (freq[i] > 0) {                         
            maxHeap.push({freq[i], 'a' + i});      
        }                                          
    }                                              

    string result;                                 
    pair<int, char> prev = {0, '#'};               

    while (!maxHeap.empty()) {                     
        auto [cnt, ch] = maxHeap.top();            
        maxHeap.pop();                             
        result += ch;                              

        if (prev.first > 0) {                      
            maxHeap.push(prev);                    
        }                                          
        prev = {cnt - 1, ch};                      
    }                                              

    return result.size() == s.size() ? result : "";
}                                                  
```

```
};
```

TIME: O(N log 26) = O(N)  |  SPACE: O(26) = O(1)

### **PATTERN 6: COIN CHANGE (GREEDY VARIANT)** 

CORE IDEA: Use largest denomination first
WARNING: Only works for canonical coin systems! DP needed otherwise.

## **SOLVED PROBLEM 6.1: Lemonade Change (LC 860)** 

PROBLEM: Customers pay $5, $10, or $20. Can you make correct change?

**EXAMPLE:**
Input: [5,5,5,10,20]
Output: true

**APPROACH:**
Track $5 and $10 bills. For $20, prefer $10+$5 over $5+$5+$5.

```java
class Solution {
```

public:
```
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;               

    for (int bill : bills) {             
        if (bill == 5) {                 
            five++;                      
        }                                
        else if (bill == 10) {           
            if (five == 0) return false; 
            five--;                      
            ten++;                       
        }                                
        else {  // $20                   
            if (ten > 0 && five > 0) {   
                ten--;                   
                five--;                  
            } else if (five >= 3) {      
                five -= 3;               
            } else {                     
                return false;            
            }                            
        }                                
    }                                    

    return true;                         
}                                        
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 6.2: Minimum Deletions to Make Character Frequencies Unique (LC 1647)**

PROBLEM: Delete min chars so all remaining chars have unique frequencies.

**EXAMPLE:**
Input: "aaabbbcc"
Output: 2 (delete 2 b's → "aaabcc" with freq a=3, b=1, c=2)

**APPROACH:**
Sort frequencies descending. Greedily reduce if duplicate exists.

```java
class Solution {
```

public:
```
int minDeletions(string s) {                                
    vector<int> freq(26, 0);                                
    for (char c : s) freq[c - 'a']++;                       

    sort(freq.rbegin(), freq.rend());                       

    int deletions = 0;                                      
    int maxAllowed = freq[0];  // Maximum frequency allowed 

    for (int f : freq) {                                    
        if (f > maxAllowed) {                               
            deletions += f - maxAllowed;                    
            f = maxAllowed;                                 
        }                                                   
        maxAllowed = max(0, f - 1);  // Next must be smaller
    }                                                       

    return deletions;                                       
}                                                           
```

```
};
```

TIME: O(N + 26 log 26) = O(N)  |  SPACE: O(26) = O(1)

### **PATTERN 7: PREFIX/SUFFIX GREEDY (JUMP GAME)** 

CORE IDEA: Track farthest reachable position
KEY: Each position, update farthest we can reach

## **SOLVED PROBLEM 7.1: Jump Game (LC 55)** 

PROBLEM: Can you reach the last index?

**EXAMPLE:**
Input: [2,3,1,1,4]
Output: true

```java
class Solution {
```

public:
```
bool canJump(vector<int>& nums) {                           
    int farthest = 0;                                       

    for (int i = 0; i < nums.size(); i++) {                 
        if (i > farthest) return false;  // Can't reach here

        farthest = max(farthest, i + nums[i]);              

        if (farthest >= nums.size() - 1) return true;       
    }                                                       

    return true;                                            
}                                                           
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 7.2: Jump Game II (LC 45)** 

PROBLEM: Minimum jumps to reach last index.

**EXAMPLE:**
Input: [2,3,1,1,4]
Output: 2 (jump 1 step to index 1, then 3 steps to end)

**APPROACH:**
Track current jump's end. When reached, we must jump.

```java
class Solution {
```

public:
```
int jump(vector<int>& nums) {                   
    int jumps = 0;                              
    int currentEnd = 0;                         
    int farthest = 0;                           

    for (int i = 0; i < nums.size() - 1; i++) { 
        farthest = max(farthest, i + nums[i]);  

        if (i == currentEnd) {  // Must jump now
            jumps++;                            
            currentEnd = farthest;              
        }                                       
    }                                           

    return jumps;                               
}                                               
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 7.3: Maximum Subarray (LC 53)** 

PROBLEM: Find contiguous subarray with maximum sum.

**EXAMPLE:**
Input: [-2,1,-3,4,-1,2,1,-5,4]
Output: 6 (subarray [4,-1,2,1])

APPROACH (Kadane's Algorithm):
If current sum < 0, start fresh. Negative prefix hurts more than helps.

```java
class Solution {
```

public:
```
int maxSubArray(vector<int>& nums) {                    
    int maxSum = nums[0];                               
    int currentSum = nums[0];                           

    for (int i = 1; i < nums.size(); i++) {             
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);               
    }                                                   

    return maxSum;                                      
}                                                       
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 7.7: Jump Game VI (LC 1696)** 

PROBLEM: Max score reaching last index. Jump at most k steps. DP + Monotonic Deque.

**EXAMPLE:**
Input: nums = [1,-1,-2,4,-7,3], k = 2
Output: 7 (0>3>5)

```java
class Solution {
```

public:
```
int maxResult(vector<int>& nums, int k) {                           
    int n = nums.size();                                            
    deque<int> dq;                                                  
    vector<int> dp(n);                                              
    dp[0] = nums[0];                                                
    dq.push_back(0);                                                

    for (int i = 1; i < n; i++) {                                   
        while (!dq.empty() && dq.front() < i - k) dq.pop_front();   
        dp[i] = nums[i] + dp[dq.front()];                           
        while (!dq.empty() && dp[dq.back()] <= dp[i]) dq.pop_back();
        dq.push_back(i);                                            
    }                                                               

    return dp[n - 1];                                               
}                                                                   
```

```
};
```

TIME: O(N)  |  SPACE: O(N)

### **PATTERN 8: PRIORITY QUEUE GREEDY** 

CORE IDEA: Use heap to always pick best available option
KEY: Dynamic set of choices, pick optimal at each step

## **SOLVED PROBLEM 8.1: IPO (LC 502)** 

PROBLEM: Do at most k projects. Need capital[i] to start, gain profits[i].
Maximize final capital.

**EXAMPLE:**
Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4 (project 0 → w=1, project 2 → w=4)

```java
class Solution {
```

public:
```
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();                                                         
    vector<pair<int, int>> projects(n);                                             
    for (int i = 0; i < n; i++) {                                                   
        projects[i] = {capital[i], profits[i]};                                     
    }                                                                               

    sort(projects.begin(), projects.end());                                         

    priority_queue<int> maxHeap;  // Available profits                              
    int idx = 0;                                                                    

    for (int i = 0; i < k; i++) {                                                   
        // Add all affordable projects                                              
        while (idx < n && projects[idx].first <= w) {                               
            maxHeap.push(projects[idx].second);                                     
            idx++;                                                                  
        }                                                                           

        if (maxHeap.empty()) break;                                                 

        w += maxHeap.top();                                                         
        maxHeap.pop();                                                              
    }                                                                               

    return w;                                                                       
}                                                                                   
```

```
};
```

TIME: O(N log N)  |  SPACE: O(N)

## **SOLVED PROBLEM 8.3: Single-Threaded CPU (LC 1834)**

PROBLEM: Process tasks. Pick available task with shortest processing time.

**EXAMPLE:**
Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]

```java
class Solution {
```

public:
```
vector<int> getOrder(vector<vector<int>>& tasks) {                     
    int n = tasks.size();                                              
    vector<array<int, 3>> indexed(n);                                  
    for (int i = 0; i < n; i++) {                                      
        indexed[i] = {tasks[i][0], tasks[i][1], i};                    
    }                                                                  

    sort(indexed.begin(), indexed.end());                              

    // Min heap: {processing time, index}                              
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    vector<int> result;                                                
    long long time = 0;                                                
    int i = 0;                                                         

    while (i < n || !pq.empty()) {                                     
        if (pq.empty() && i < n) {                                     
            time = max(time, (long long)indexed[i][0]);                
        }                                                              

        while (i < n && indexed[i][0] <= time) {                       
            pq.push({indexed[i][1], indexed[i][2]});                   
            i++;                                                       
        }                                                              

        auto [proc, idx] = pq.top();                                   
        pq.pop();                                                      
        time += proc;                                                  
        result.push_back(idx);                                         
    }                                                                  

    return result;                                                     
}                                                                      
```

```
};
```

TIME: O(N log N)  |  SPACE: O(N)

### **PATTERN 9: GREEDY IN GRAPH ALGORITHMS** 

CORE IDEA: Process closest/cheapest node first
ALGORITHMS: Dijkstra, Prim's MST

## **SOLVED PROBLEM 9.1: Network Delay Time (LC 743)** 

PROBLEM: Time for signal to reach all nodes from source k.

**EXAMPLE:**
Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2

```java
class Solution {
```

public:
```
int networkDelayTime(vector<vector<int>>& times, int n, int k) {       
    vector<vector<pair<int,int>>> adj(n + 1);                          
    for (auto& t : times) {                                            
        adj[t[0]].push_back({t[1], t[2]});                             
    }                                                                  

    vector<int> dist(n + 1, INT_MAX);                                  
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[k] = 0;                                                       
    pq.push({0, k});                                                   

    while (!pq.empty()) {                                              
        auto [d, u] = pq.top();                                        
        pq.pop();                                                      

        if (d > dist[u]) continue;                                     

        for (auto [v, w] : adj[u]) {                                   
            if (dist[u] + w < dist[v]) {                               
                dist[v] = dist[u] + w;                                 
                pq.push({dist[v], v});                                 
            }                                                          
        }                                                              
    }                                                                  

    int maxDist = 0;                                                   
    for (int i = 1; i <= n; i++) {                                     
        if (dist[i] == INT_MAX) return -1;                             
        maxDist = max(maxDist, dist[i]);                               
    }                                                                  

    return maxDist;                                                    
}                                                                      
```

```
};
```

TIME: O((V + E) log V)  |  SPACE: O(V + E)

## **SOLVED PROBLEM 9.2: Path With Minimum Effort (LC 1631)** 

PROBLEM: Find path from top-left to bottom-right minimizing max abs difference.

**EXAMPLE:**
Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2

**APPROACH:**
Modified Dijkstra. Effort = max diff along path.

```java
class Solution {
```

public:
```
int minimumEffortPath(vector<vector<int>>& heights) {                            
    int m = heights.size(), n = heights[0].size();                               
    vector<vector<int>> effort(m, vector<int>(n, INT_MAX));                      
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;

    int dx[] = {0, 0, 1, -1};                                                    
    int dy[] = {1, -1, 0, 0};                                                    

    effort[0][0] = 0;                                                            
    pq.push({0, 0, 0});                                                          

    while (!pq.empty()) {                                                        
        auto [e, x, y] = pq.top();                                               
        pq.pop();                                                                

        if (x == m - 1 && y == n - 1) return e;                                  
        if (e > effort[x][y]) continue;                                          

        for (int d = 0; d < 4; d++) {                                            
            int nx = x + dx[d], ny = y + dy[d];                                  
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {                        
                int newEffort = max(e, abs(heights[nx][ny] - heights[x][y]));    
                if (newEffort < effort[nx][ny]) {                                
                    effort[nx][ny] = newEffort;                                  
                    pq.push({newEffort, nx, ny});                                
                }                                                                
            }                                                                    
        }                                                                        
    }                                                                            

    return 0;                                                                    
}                                                                                
```

```
};
```

TIME: O(MN log MN)  |  SPACE: O(MN)

## **SOLVED PROBLEM 9.3: Min Cost to Connect All Points (LC 1584)**

PROBLEM: Connect all points with minimum total Manhattan distance.

**EXAMPLE:**
Input: [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20

APPROACH: Prim's MST

```java
class Solution {
```

public:
```
int minCostConnectPoints(vector<vector<int>>& points) {             
    int n = points.size();                                          
    vector<bool> inMST(n, false);                                   
    vector<int> minDist(n, INT_MAX);                                

    minDist[0] = 0;                                                 
    int totalCost = 0;                                              

    for (int i = 0; i < n; i++) {                                   
        // Find closest node not in MST                             
        int u = -1;                                                 
        for (int j = 0; j < n; j++) {                               
            if (!inMST[j] && (u == -1 || minDist[j] < minDist[u])) {
                u = j;                                              
            }                                                       
        }                                                           

        inMST[u] = true;                                            
        totalCost += minDist[u];                                    

        // Update distances                                         
        for (int v = 0; v < n; v++) {                               
            if (!inMST[v]) {                                        
                int dist = abs(points[u][0] - points[v][0])       +
                           abs(points[u][1] - points[v][1]);        
                minDist[v] = min(minDist[v], dist);                 
            }                                                       
        }                                                           
    }                                                               

    return totalCost;                                               
}                                                                   
```

```
};
```

TIME: O(N2)  |  SPACE: O(N)

### **PATTERN 10: EXCHANGE ARGUMENT / PROOF-BASED GREEDY** 

CORE IDEA: Prove greedy by showing exchanges don't improve solution
KEY: If swapping doesn't help, greedy is optimal

## **SOLVED PROBLEM 10.1: Gas Station (LC 134)** 

PROBLEM: Can you complete circuit? If yes, return starting station.

**EXAMPLE:**
Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3

PROOF: If you can't reach j from i, you can't from any station between either!

```java
class Solution {
```

public:
```
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalGas = 0, totalCost = 0;                         
    int tank = 0, start = 0;                                 

    for (int i = 0; i < gas.size(); i++) {                   
        totalGas += gas[i];                                  
        totalCost += cost[i];                                
        tank += gas[i] - cost[i];                            

        if (tank < 0) {                                      
            start = i + 1;                                   
            tank = 0;                                        
        }                                                    
    }                                                        

    return (totalGas >= totalCost) ? start : -1;             
}                                                            
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 10.2: Candy (LC 135)** 

PROBLEM: Distribute candies. Higher rating gets more than neighbors. Min total.

**EXAMPLE:**
Input: [1,0,2]
Output: 5 (candies: [2,1,2])

APPROACH: Two passes - satisfy left neighbor, then right neighbor.

```java
class Solution {
```

public:
```
int candy(vector<int>& ratings) {                          
    int n = ratings.size();                                
    vector<int> candies(n, 1);                             

    // Left to right                                       
    for (int i = 1; i < n; i++) {                          
        if (ratings[i] > ratings[i-1]) {                   
            candies[i] = candies[i-1] + 1;                 
        }                                                  
    }                                                      

    // Right to left                                       
    for (int i = n - 2; i >= 0; i--) {                     
        if (ratings[i] > ratings[i+1]) {                   
            candies[i] = max(candies[i], candies[i+1] + 1);
        }                                                  
    }                                                      

    return accumulate(candies.begin(), candies.end(), 0);  
}                                                          
```

```
};
```

TIME: O(N)  |  SPACE: O(N)

## **SOLVED PROBLEM 10.3: Valid Parenthesis String (LC 678)** 

PROBLEM: String with '(', ')', '*'. * can be '(', ')' or empty. Valid?

**EXAMPLE:**
Input: "(*))"
Output: true

APPROACH: Track range of possible open counts [low, high].

```java
class Solution {
```

public:
```
bool checkValidString(string s) {                          
    int low = 0, high = 0;  // Range of possible open count

    for (char c : s) {                                     
        if (c == '(') {                                    
            low++;                                         
            high++;                                        
        } else if (c == ')') {                             
            low--;                                         
            high--;                                        
        } else {  // '*'                                   
            low--;   // Treat as ')'                       
            high++;  // Treat as '('                       
        }                                                  

        if (high < 0) return false;  // Too many ')'       
        low = max(low, 0);  // Can't go negative           
    }                                                      

    return low == 0;                                       
}                                                          
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

### **PATTERN 11: GREEDY DIGIT/NUMBER CONSTRUCTION** 

CORE IDEA: Build smallest/largest number digit by digit
TOOL: Monotonic stack

## **SOLVED PROBLEM 11.1: Remove K Digits (LC 402)** 

PROBLEM: Remove k digits to get smallest number.

**EXAMPLE:**
Input: num = "1432219", k = 3
Output: "1219"

```java
class Solution {
```

public:
```
string removeKdigits(string num, int k) {                          
    string result;                                                 

    for (char digit : num) {                                       
        while (!result.empty() && k > 0 && result.back() > digit) {
            result.pop_back();                                     
            k--;                                                   
        }                                                          
        result.push_back(digit);                                   
    }                                                              

    // Remove remaining k from end                                 
    while (k > 0) {                                                
        result.pop_back();                                         
        k--;                                                       
    }                                                              

    // Remove leading zeros                                        
    int i = 0;                                                     
    while (i < result.size() && result[i] == '0') i++;             

    result = result.substr(i);                                     
    return result.empty() ? "0" : result;                          
}                                                                  
```

```
};
```

TIME: O(N)  |  SPACE: O(N)

## **SOLVED PROBLEM 11.2: Maximum Swap (LC 670)** 

PROBLEM: Swap at most two digits to get maximum number.

**EXAMPLE:**
Input: 2736
Output: 7236

APPROACH: Find leftmost digit smaller than a digit to its right.

```java
class Solution {
```

public:
```
int maximumSwap(int num) {                                     
    string s = to_string(num);                                 
    int n = s.size();                                          

    // For each position, find rightmost max digit to the right
    vector<int> rightMax(n);                                   
    rightMax[n-1] = n-1;                                       

    for (int i = n - 2; i >= 0; i--) {                         
        if (s[i] > s[rightMax[i+1]]) {                         
            rightMax[i] = i;                                   
        } else {                                               
            rightMax[i] = rightMax[i+1];                       
        }                                                      
    }                                                          

    // Find first digit smaller than rightMax                  
    for (int i = 0; i < n; i++) {                              
        if (s[i] < s[rightMax[i]]) {                           
            swap(s[i], s[rightMax[i]]);                        
            break;                                             
        }                                                      
    }                                                          

    return stoi(s);                                            
}                                                              
```

```
};
```

TIME: O(N)  |  SPACE: O(N)

### **PATTERN 12: GREEDY STRING CONSTRUCTION** 

CORE IDEA: Build lexicographically smallest/largest string
TOOL: Monotonic stack with "can I see this char again?" check

## **SOLVED PROBLEM 12.1: Remove Duplicate Letters (LC 316)** 

PROBLEM: Remove duplicates to get lexicographically smallest result.

**EXAMPLE:**
Input: "bcabc"
Output: "abc"

```java
class Solution {
```

public:
```
string removeDuplicateLetters(string s) {                 
    vector<int> lastIdx(26);                              
    vector<bool> inStack(26, false);                      

    for (int i = 0; i < s.size(); i++) {                  
        lastIdx[s[i] - 'a'] = i;                          
    }                                                     

    string result;                                        

    for (int i = 0; i < s.size(); i++) {                  
        int c = s[i] - 'a';                               

        if (inStack[c]) continue;                         

        while (!result.empty() && result.back() > s[i] && 
               lastIdx[result.back() - 'a'] > i) {        
            inStack[result.back() - 'a'] = false;         
            result.pop_back();                            
        }                                                 

        result.push_back(s[i]);                           
        inStack[c] = true;                                
    }                                                     

    return result;                                        
}                                                         
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 12.2: Longest Happy String (LC 1405)** 

PROBLEM: Build longest string using at most a 'a's, b 'b's, c 'c's.
No 3 consecutive same chars.

**EXAMPLE:**
Input: a = 1, b = 1, c = 7
Output: "ccaccbcc" or similar

```java
class Solution {
```

public:
```
string longestDiverseString(int a, int b, int c) {                  
    string result;                                                  
    vector<pair<int, char>> counts = {{a, 'a'}, {b, 'b'}, {c, 'c'}};

    while (true) {                                                  
        sort(counts.rbegin(), counts.rend());                       

        bool added = false;                                         
        for (auto& [cnt, ch] : counts) {                            
            if (cnt == 0) continue;                                 

            int n = result.size();                                  
            if (n >= 2 && result[n-1] == ch && result[n-2] == ch) { 
                continue;                                           
            }                                                       

            result += ch;                                           
            cnt--;                                                  
            added = true;                                           
            break;                                                  
        }                                                           

        if (!added) break;                                          
    }                                                               

    return result;                                                  
}                                                                   
```

```
};
```

TIME: O(a + b + c)  |  SPACE: O(1)

### **PATTERN 13: OPTIMAL PARTITIONING** 

CORE IDEA: Find optimal way to partition array/string
COMMON: Track last occurrence, binary search + greedy validation

## **SOLVED PROBLEM 13.1: Partition Labels (LC 763)** 

PROBLEM: Partition string so each letter appears in at most one part.

**EXAMPLE:**
Input: "ababcbacadefegdehijhklij"
Output: [9,7,8]

```java
class Solution {
```

public:
```
vector<int> partitionLabels(string s) {       
    vector<int> last(26);                     
    for (int i = 0; i < s.size(); i++) {      
        last[s[i] - 'a'] = i;                 
    }                                         

    vector<int> result;                       
    int start = 0, end = 0;                   

    for (int i = 0; i < s.size(); i++) {      
        end = max(end, last[s[i] - 'a']);     

        if (i == end) {                       
            result.push_back(end - start + 1);
            start = i + 1;                    
        }                                     
    }                                         

    return result;                            
}                                             
```

```
};
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED PROBLEM 13.2: Split Array Largest Sum (LC 410)** 

PROBLEM: Split array into k parts minimizing max sum of any part.

**EXAMPLE:**
Input: nums = [7,2,5,10,8], k = 2
Output: 18 (split: [7,2,5] and [10,8])

APPROACH: Binary search on answer + greedy validation.

```java
class Solution {
```

public:
```
int splitArray(vector<int>& nums, int k) {                   
    long long lo = *max_element(nums.begin(), nums.end());   
    long long hi = accumulate(nums.begin(), nums.end(), 0LL);

    while (lo < hi) {                                        
        long long mid = lo + (hi - lo) / 2;                  

        if (canSplit(nums, k, mid)) {                        
            hi = mid;                                        
        } else {                                             
            lo = mid + 1;                                    
        }                                                    
    }                                                        

    return lo;                                               
}                                                            

bool canSplit(vector<int>& nums, int k, long long maxSum) {  
    int count = 1;                                           
    long long curSum = 0;                                    

    for (int num : nums) {                                   
        if (curSum + num > maxSum) {                         
            count++;                                         
            curSum = num;                                    
        } else {                                             
            curSum += num;                                   
        }                                                    
    }                                                        

    return count <= k;                                       
}                                                            
```

```
};
```

TIME: O(N log sum)  |  SPACE: O(1)

### **PATTERN 14: GREEDY BASED ON PARITY/CONTRIBUTION** 

CORE IDEA: Use parity invariant or contribution analysis
KEY: Count negatives, track what stays invariant

## **SOLVED PROBLEM 14.1: Maximize Sum After K Negations (LC 1005)** 

PROBLEM: Negate elements k times. Maximize sum.

**EXAMPLE:**
Input: nums = [4,2,3], k = 1
Output: 5 (negate 2)

```java
class Solution {
```

public:
```
int largestSumAfterKNegations(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());                      

    int i = 0;                                           
    // Negate negatives first                            
    while (i < nums.size() && nums[i] < 0 && k > 0) {    
        nums[i] = -nums[i];                              
        i++;                                             
        k--;                                             
    }                                                    

    // If k remaining and odd, negate smallest           
    if (k % 2 == 1) {                                    
        sort(nums.begin(), nums.end());                  
        nums[0] = -nums[0];                              
    }                                                    

    return accumulate(nums.begin(), nums.end(), 0);      
}                                                        
```

```
};
```

TIME: O(N log N)  |  SPACE: O(1)

### **PATTERN 15: GREEDY SELECTION WITH CONSTRAINTS** 

CORE IDEA: Pick best option satisfying constraints
TOOL: Two pointers, state tracking

## **SOLVED PROBLEM 15.1: Boats to Save People (LC 881)** 

PROBLEM: Each boat fits 2 people with weight limit. Minimize boats.

**EXAMPLE:**
Input: people = [3,2,2,1], limit = 3
Output: 3

```java
class Solution {
```

public:
```
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());             

    int left = 0, right = people.size() - 1;        
    int boats = 0;                                  

    while (left <= right) {                         
        if (people[left] + people[right] <= limit) {
            left++;  // Both fit                    
        }                                           
        right--;  // Heaviest always goes           
        boats++;                                    
    }                                               

    return boats;                                   
}                                                   
```

```
};
```

TIME: O(N log N)  |  SPACE: O(1)

## **SOLVED PROBLEM 15.2: Bag of Tokens (LC 948)** 

PROBLEM: Play tokens face-up (lose power, gain score) or face-down (opposite).
Maximize score.

**EXAMPLE:**
Input: tokens = [100,200,300,400], power = 200
Output: 2

```java
class Solution {
```

public:
```
int bagOfTokensScore(vector<int>& tokens, int power) {
    sort(tokens.begin(), tokens.end());               

    int left = 0, right = tokens.size() - 1;          
    int score = 0, maxScore = 0;                      

    while (left <= right) {                           
        if (power >= tokens[left]) {                  
            power -= tokens[left++];                  
            score++;                                  
            maxScore = max(maxScore, score);          
        } else if (score > 0) {                       
            power += tokens[right--];                 
            score--;                                  
        } else {                                      
            break;                                    
        }                                             
    }                                                 

    return maxScore;                                  
}                                                     
```

```
};
```

TIME: O(N log N)  |  SPACE: O(1)

## **PART 3: PROOF TECHNIQUES FOR GREEDY**

METHOD 1: GREEDY STAYS AHEAD
Show greedy is no worse than optimal at every step.

METHOD 2: EXCHANGE ARGUMENT
Show swapping choices doesn't improve solution.

METHOD 3: STRUCTURAL
Show problem structure guarantees greedy is safe.

METHOD 4: CONTRADICTION
Assume greedy isn't optimal, derive contradiction.

## **PART 4: QUICK DECISION GUIDE**

### Pattern                      Keywords                    Sort By

1.  Interval Scheduling     intervals, meetings         End time
2.  Sorting + Greedy        assign, pair                Problem-specific
3.  Fractional Knapsack     value/weight, maximize      Ratio
4.  Job Sequencing          deadline, schedule          Deadline
5.  Frequency Merging       combine, cost               Use min heap
6.  Coin Change             change, bills               N/A (canonical only)
7.  Prefix/Suffix           jump, reach, subarray       Track farthest
8.  Priority Queue          best available              Use heap
9.  Graph Greedy            shortest path, MST          Distance/weight
10. Exchange Argument       circular, prove             Problem-specific
11. Digit Construction      smallest/largest number     Monotonic stack
12. String Construction     lexicographic               Monotonic stack
13. Optimal Partitioning    split, partition            Binary search
14. Parity/Contribution     negations, parity           Count negatives
15. Selection + Constraint  capacity, limit             Two pointers
