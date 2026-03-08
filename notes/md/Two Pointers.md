# **TWO POINTERS - COMPLETE GUIDE**

### **TABLE OF CONTENTS**

1. Core Patterns & Templates
2. Pattern Recognition Guide
3. Key Problems with Solutions
4. Quick Revision Table

## **PART 1: FOUR CORE PATTERNS**

### **PATTERN 1: OPPOSITE ENDS (Convergence)**

 **MEMORY AID**: "**S**orted or **S**ymmetry > **S**queeze from ends"

 USE WHEN: Start from both ends, move toward center
 VISUALIZATION: <---------->

**TEMPLATE:**

```
int left = 0, right = n - 1;

while (left < right) {
// Process arr[left] and arr[right]

if (condition) {                   
    // Move based on comparison    
    left++;                        
} else {                           
    right--;                       
}                                  

}
```

**COMMON VARIATIONS:**
- Two Sum (sorted array)
- Trapping Rain Water
- Container With Most Water
- Valid Palindrome
- Reversing/Swapping

KEY INSIGHT: Array must be sorted OR you're checking symmetry

### **PATTERN 2: SLOW & FAST (Different Speeds)**

 **MEMORY AID**: "**F**ast scouts, **S**low writes" (Fast explores, Slow builds result)

 USE WHEN: One pointer moves faster than the other
 VISUALIZATION: >--> (slow > fast >>)

**TEMPLATE:**

```
int slow = 0, fast = 0;

while (fast < n) {
// Fast pointer explores ahead         
fast++;                                

// Slow pointer processes based on fast
if (condition) {                       
    slow++;                            
}                                      

}
```

**COMMON VARIATIONS:**
- Remove Duplicates
- Linked List Cycle Detection (Floyd's Algorithm)
- Remove Element
- Partition Array

KEY INSIGHT: Fast pointer scouts, slow pointer builds result

### **PATTERN 3: PARALLEL (Two Arrays/Lists)**

 **MEMORY AID**: "Two lists > Two pointers **P**arallel" (Merge, Intersect, Compare)

 USE WHEN: Process two arrays/lists simultaneously
 VISUALIZATION: arr1: > arr2: >

**TEMPLATE:**

```
int i = 0, j = 0;

while (i < m && j < n) {
if (arr1[i] < arr2[j]) {       
    // Process arr1[i]         
    i++;                       
} else if (arr1[i] > arr2[j]) {
    // Process arr2[j]         
    j++;                       
} else {                       
    // Both equal              
    i++;                       
    j++;                       
}                              

}
```

**COMMON VARIATIONS:**
- Merge Sorted Arrays
- Intersection of Two Arrays
- Implement strStr()
- Longest Common Subsequence

KEY INSIGHT: Usually involves sorted arrays or pattern matching

### **PATTERN 4: SPLIT & MERGE (Divide & Conquer)**

 USE WHEN: Split array, then merge back
 VISUALIZATION: [----] [----] > merge

**TEMPLATE:**

```
// Split phase
mid = (left + right) / 2;
split(left, mid);
split(mid + 1, right);

// Merge phase
int i = left, j = mid + 1, k = 0;
while (i <= mid && j <= right) {
if (arr[i] <= arr[j]) {  
    temp[k++] = arr[i++];
} else {                 
    temp[k++] = arr[j++];
}                        

}
```

**COMMON VARIATIONS:**
- Merge Sort
- Sort List (Linked List)
- Partition List

KEY INSIGHT: Recursive splitting + iterative merging

## PART 2: PATTERN RECOGNITION & APPROACH

###  HOW TO IDENTIFY WHICH PATTERN?

```
+------------------------------------------------------------------------------+
| Keywords/Clues              | Pattern                | Template              |
+-----------------------------+------------------------+-----------------------+
| "sorted array"              | Opposite Ends          | left++, right--       |
| "two sum", "pair"           | Opposite Ends          | left++, right--       |
| "palindrome", "reverse"     | Opposite Ends          | left++, right--       |
| "trapping", "container"     | Opposite Ends          | left++, right--       |
|                             |                        |                       |
| "remove duplicates"         | Slow & Fast            | slow builds result    |
| "in-place", "O(1) space"    | Slow & Fast            | fast scouts           |
| "linked list cycle"         | Slow & Fast            | Floyd's algorithm     |
| "partition", "segregate"    | Slow & Fast            | slow = boundary       |
|                             |                        |                       |
| "merge two sorted"          | Parallel               | compare & advance     |
| "intersection"              | Parallel               | two pointers          |
| "two arrays"                | Parallel               | i, j pointers         |
|                             |                        |                       |
| "merge sort"                | Split & Merge          | divide & conquer      |
| "sort linked list"          | Split & Merge          | recursive split       |
+-----------------------------+------------------------+-----------------------+
```

###  SYSTEMATIC APPROACH

### STEP 1: Identify Problem Type (30 seconds)

Ask:
o Is array sorted? > Opposite Ends
o Need in-place modification? > Slow & Fast
o Two arrays given? > Parallel
o Need to sort? > Split & Merge
o Looking for pairs/symmetry? > Opposite Ends

### STEP 2: Choose Template (30 seconds)

Decision:
- Sorted array + target > Opposite Ends
- Remove/modify in-place > Slow & Fast
- Compare two sequences > Parallel
- Sort or partition > Slow & Fast or Split & Merge

### STEP 3: Define Movement Rules (1 minute)

o When to move left pointer?
o When to move right pointer?
o When to move both?
o What's the termination condition?

### STEP 4: Implement (5 minutes)

1. Initialize pointers
2. Loop with proper condition
3. Process current elements
4. Update pointers
5. Handle remaining elements (if any)

###  GOLDEN RULES

1. OPPOSITE ENDS RULE
> Only works if array is sorted OR checking symmetry

2. SLOW & FAST RULE
> Slow builds result, fast explores
> Fast is always ahead: fast >= slow

3. PARALLEL RULE
> Process smaller element first (if sorted)
> Handle remaining elements after main loop

4. POINTER MOVEMENT RULE
> Be clear about when to move which pointer
> Avoid infinite loops: ensure progress

5. IN-PLACE MODIFICATION RULE
> Use slow pointer to track write position
> Fast pointer reads, slow pointer writes

6. CYCLE DETECTION RULE (Floyd's)
> slow moves 1 step, fast moves 2 steps
> If cycle exists, they will meet

## PART 3: KEY PROBLEMS WITH SOLUTIONS

### CATEGORY 1: OPPOSITE ENDS

### 1. Two Sum II - Input Array Is Sorted (LC 167) 

 PATTERN: Opposite Ends
 TEMPLATE: left++/right-- based on sum comparison

NOTE: This is different from Two Sum (LC 1)!
- LC 1 (Two Sum): Unsorted array > Use Hashmap O(N) (See Hashmap Patterns.txt)
- LC 167 (Two Sum II): Sorted array > Use Two Pointers O(N) (this problem)

**KEY INSIGHT:**
- Since array is sorted, we can eliminate half the search space each time
- If sum < target, need bigger numbers > left++
- If sum > target, need smaller numbers > right--

**WHY IT WORKS:**
- Sorted array allows us to make decisions about pointer movement
- Two pointers cover all possible pairs without nested loops
- O(N) instead of O(N2)

**GOLDEN RULE:**
> For sorted array + target problems, always consider opposite ends!

```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
int left = 0, right = numbers.size() - 1;          

while (left < right) {                             
    int sum = numbers[left] + numbers[right];      

    if (sum == target) {                           
        return {left + 1, right + 1};  // 1-indexed
    } else if (sum < target) {                     
        left++;   // Need larger sum               
    } else {                                       
        right--;  // Need smaller sum              
    }                                              
}                                                  

return {};  // No solution                         

}
// Time: O(N), Space: O(1)
```

### 2. Container With Most Water (LC 11) 

 PATTERN: Opposite Ends (Greedy)
 TEMPLATE: Move pointer with smaller height

**KEY INSIGHT:**
- Area = min(height[l], height[r]) x (r - l)
- To maximize area, we need to find taller lines
- Move the pointer with smaller height (bottleneck)

WHY MOVE SMALLER HEIGHT?
- Width will always decrease as pointers converge
- Only way to increase area is to find taller line
- Moving larger height won't help (limited by smaller one anyway)

**COMMON MISTAKES:**
 Moving both pointers
 Moving larger height pointer
 Always move the pointer with smaller height

```cpp
int maxArea(vector<int>& height) {
int left = 0, right = height.size() - 1;     
int maxWater = 0;                            

while (left < right) {                       
    int width = right - left;                
    int h = min(height[left], height[right]);
    maxWater = max(maxWater, width * h);     

    // Move pointer with smaller height      
    if (height[left] < height[right]) {      
        left++;                              
    } else {                                 
        right--;                             
    }                                        
}                                            

return maxWater;                             

}
// Time: O(N), Space: O(1)
```

### 3. Trapping Rain Water (LC 42)  HARD

 PATTERN: Opposite Ends + Max Height Tracking
 TEMPLATE: Move pointer with smaller max height

KEY INSIGHT (BRILLIANT!):
- Water at position i = min(maxLeft, maxRight) - height[i]
- Track leftMax and rightMax as we go
- Process side with smaller max (that's the bottleneck)

**WHY IT WORKS:**
- Water level determined by min of left/right boundaries
- If leftMax < rightMax, we KNOW water at left is limited by leftMax
- We don't need to know exact rightMax, just that it's bigger!

**GOLDEN RULE:**
> Always process the side with smaller boundary

```cpp
int trap(vector<int>& height) {
int left = 0, right = height.size() - 1;           
int leftMax = 0, rightMax = 0;                     
int water = 0;                                     

while (left < right) {                             
    if (height[left] < height[right]) {            
        // Process left side (it's the bottleneck) 
        if (height[left] >= leftMax) {             
            leftMax = height[left];                
        } else {                                   
            water += leftMax - height[left];       
        }                                          
        left++;                                    
    } else {                                       
        // Process right side (it's the bottleneck)
        if (height[right] >= rightMax) {           
            rightMax = height[right];              
        } else {                                   
            water += rightMax - height[right];     
        }                                          
        right--;                                   
    }                                              
}                                                  

return water;                                      

}
// Time: O(N), Space: O(1)
```

### 4. Valid Palindrome (LC 125)

 PATTERN: Opposite Ends (Symmetry Check)
 TEMPLATE: Compare from both ends

**KEY INSIGHT:**
- Palindrome is symmetric from both ends
- Compare characters moving inward
- Skip non-alphanumeric characters

```
bool isPalindrome(string s) {
int left = 0, right = s.size() - 1;                    

while (left < right) {                                 
    // Skip non-alphanumeric                           
    while (left < right && !isalnum(s[left])) left++;  
    while (left < right && !isalnum(s[right])) right--;

    // Compare (case-insensitive)                      
    if (tolower(s[left]) != tolower(s[right])) {       
        return false;                                  
    }                                                  

    left++;                                            
    right--;                                           
}                                                      

return true;                                           

}
// Time: O(N), Space: O(1)
```

### 5. 3Sum (LC 15)

 PATTERN: Fixed + Two Pointers
 TEMPLATE: Fix one element, two sum on remaining

**KEY INSIGHT:**
- Sort array first
- Fix first element, use two pointers for remaining two
- Skip duplicates to avoid duplicate triplets

**WHY IT WORKS:**
- 3Sum reduces to 2Sum for each fixed element
- Sorting allows duplicate skipping and two pointer approach
- O(N2) is optimal for this problem

**COMMON MISTAKES:**
 Not skipping duplicates
 Checking duplicates incorrectly
 Skip after processing, not before

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
vector<vector<int>> result;                                              
sort(nums.begin(), nums.end());                                          

for (int i = 0; i < nums.size(); i++) {                                  
    // Skip duplicates for first element                                 
    if (i > 0 && nums[i] == nums[i-1]) continue;                         

    // Two pointers on remaining array                                   
    int left = i + 1, right = nums.size() - 1;                           
    int target = -nums[i];                                               

    while (left < right) {                                               
        int sum = nums[left] + nums[right];                              

        if (sum == target) {                                             
            result.push_back({nums[i], nums[left], nums[right]});        

            // Skip duplicates                                           
            while (left < right && nums[left] == nums[left+1]) left++;   
            while (left < right && nums[right] == nums[right-1]) right--;

            left++;                                                      
            right--;                                                     
        } else if (sum < target) {                                       
            left++;                                                      
        } else {                                                         
            right--;                                                     
        }                                                                
    }                                                                    
}                                                                        

return result;                                                           

}
// Time: O(N2), Space: O(1) excluding output
```

### CATEGORY 2: SLOW & FAST

### 6. Remove Duplicates from Sorted Array (LC 26) 

 PATTERN: Slow & Fast (In-Place Modification)
 TEMPLATE: Slow = write position, Fast = read position

**KEY INSIGHT:**
- Slow pointer tracks position to write unique elements
- Fast pointer scans ahead
- When different element found, write at slow position

**WHY IT WORKS:**
- Slow always points to last unique element written
- Fast finds next unique element
- Overwriting is safe because fast is always ahead

**GOLDEN RULE:**
> slow tracks "good" elements, fast explores

```cpp
int removeDuplicates(vector<int>& nums) {
if (nums.empty()) return 0;                            

int slow = 0;  // Position to write next unique element

for (int fast = 1; fast < nums.size(); fast++) {       
    if (nums[fast] != nums[slow]) {                    
        slow++;                                        
        nums[slow] = nums[fast];                       
    }                                                  
}                                                      

return slow + 1;  // Length of unique array            

}
// Time: O(N), Space: O(1)
```

### 7. Linked List Cycle (LC 141) 

 PATTERN: Floyd's Cycle Detection (Slow & Fast)
 TEMPLATE: slow +1, fast +2, check if meet

**KEY INSIGHT:**
- If cycle exists, fast will eventually catch up to slow
- Fast moves 2x speed of slow
- They meet inside the cycle

**WHY IT WORKS (PROOF):**
- In cycle, fast gains 1 step per iteration
- Will eventually catch slow (like running on circular track)
- No cycle > fast reaches end

**GOLDEN RULE:**
> slow = 1 step, fast = 2 steps

```cpp
bool hasCycle(ListNode *head) {
ListNode *slow = head, *fast = head;        

while (fast && fast->next) {                
    slow = slow->next;       // Move 1 step 
    fast = fast->next->next; // Move 2 steps

    if (slow == fast) {                     
        return true;  // Cycle detected     
    }                                       
}                                           

return false;  // No cycle                  

}
// Time: O(N), Space: O(1)
```

### 8. Linked List Cycle II (LC 142) - Find Cycle Start

 PATTERN: Floyd's Algorithm Extended
 TEMPLATE: Two phases - detect, then find start

**KEY INSIGHT (MATHEMATICAL PROOF):**
- After meeting, distance from head to cycle start = distance from meeting to cycle start
- Move one pointer to head, both move at same speed
- They meet at cycle start!

**WHY IT WORKS:**
Let:
```
L = distance from head to cycle start
C = cycle length
k = distance from cycle start to meeting point
```

When they meet:
Slow traveled: L + k
Fast traveled: L + k + nC (n = number of cycles)

Since fast = 2 x slow:
L + k + nC = 2(L + k)
```
L = nC - k
```

This means distance from head to start = distance from meeting to start!

```cpp
ListNode *detectCycle(ListNode *head) {
ListNode *slow = head, *fast = head;

// Phase 1: Detect cycle            
while (fast && fast->next) {        
    slow = slow->next;              
    fast = fast->next->next;        

    if (slow == fast) {             
        // Phase 2: Find cycle start
        slow = head;                
        while (slow != fast) {      
            slow = slow->next;      
            fast = fast->next;      
        }                           
        return slow;  // Cycle start
    }                               
}                                   

return nullptr;  // No cycle        

}
// Time: O(N), Space: O(1)
```

### 9. Remove Element (LC 27)

 PATTERN: Slow & Fast (Filter Elements)
 TEMPLATE: Keep elements != val

```cpp
int removeElement(vector<int>& nums, int val) {
int slow = 0;                                   

for (int fast = 0; fast < nums.size(); fast++) {
    if (nums[fast] != val) {                    
        nums[slow] = nums[fast];                
        slow++;                                 
    }                                           
}                                               

return slow;                                    

}
// Time: O(N), Space: O(1)
```

### 10. Move Zeroes (LC 283)

 PATTERN: Slow & Fast (Partition)
 TEMPLATE: Move non-zeros to front

```cpp
void moveZeroes(vector<int>& nums) {
int slow = 0;  // Position for next non-zero    

for (int fast = 0; fast < nums.size(); fast++) {
    if (nums[fast] != 0) {                      
        swap(nums[slow], nums[fast]);           
        slow++;                                 
    }                                           
}                                               

}
// Time: O(N), Space: O(1)
```

### CATEGORY 3: PARALLEL (Two Arrays)

### 11. Merge Sorted Array (LC 88) 

 PATTERN: Parallel + Backward Fill
 TEMPLATE: Fill from end to avoid overwriting

**KEY INSIGHT:**
- nums1 has space at end, so fill from right to left
- Avoids need for extra space
- Compare largest elements and place at end

WHY BACKWARD?
- Forward would overwrite nums1 elements
- Backward uses the empty space first
- Elegant in-place solution

```cpp
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
int i = m - 1;  // Last element of nums1            
int j = n - 1;  // Last element of nums2            
int k = m + n - 1;  // Last position in merged array

// Fill from end                                    
while (i >= 0 && j >= 0) {                          
    if (nums1[i] > nums2[j]) {                      
        nums1[k--] = nums1[i--];                    
    } else {                                        
        nums1[k--] = nums2[j--];                    
    }                                               
}                                                   

// Copy remaining from nums2 (if any)               
while (j >= 0) {                                    
    nums1[k--] = nums2[j--];                        
}                                                   

}
// Time: O(M + N), Space: O(1)
```

### 11a. Intersection of Two Arrays (LC 349)

 PATTERN: Two Pointers (Sorted) or Hash Set
 SERIES: I (unique intersect) > II (with duplicates)

**KEY INSIGHT:**
- Sort both arrays, use two pointers
- Skip duplicates in result (unlike II which keeps them)
- Alternative: Use hash set for O(N+M) without sorting

```cpp
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
sort(nums1.begin(), nums1.end());                         
sort(nums2.begin(), nums2.end());                         

int i = 0, j = 0;                                         
vector<int> result;                                       

while (i < nums1.size() && j < nums2.size()) {            
    if (nums1[i] < nums2[j]) {                            
        i++;                                              
    } else if (nums1[i] > nums2[j]) {                     
        j++;                                              
    } else {                                              
        if (result.empty() || result.back() != nums1[i]) {
            result.push_back(nums1[i]);                   
        }                                                 
        i++;                                              
        j++;                                              
    }                                                     
}                                                         

return result;                                            

}
// Time: O(N log N + M log M), Space: O(1) excluding output
```

### 11b. Intersection of Two Arrays II (LC 350)

 PATTERN: Parallel (Sorted Arrays)
 SERIES: I (unique intersect) > II (with duplicates, keeps frequency)
 TEMPLATE: Compare and collect common elements

```cpp
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
sort(nums1.begin(), nums1.end());             
sort(nums2.begin(), nums2.end());             

int i = 0, j = 0;                             
vector<int> result;                           

while (i < nums1.size() && j < nums2.size()) {
    if (nums1[i] < nums2[j]) {                
        i++;                                  
    } else if (nums1[i] > nums2[j]) {         
        j++;                                  
    } else {                                  
        result.push_back(nums1[i]);           
        i++;                                  
        j++;                                  
    }                                         
}                                             

return result;                                

}
// Time: O(N log N + M log M), Space: O(1) excluding output
```

### 13. Implement strStr() (LC 28)

 PATTERN: Parallel (Pattern Matching)
 TEMPLATE: Two pointers for string matching

```
int strStr(string haystack, string needle) {
if (needle.empty()) return 0;                      

int m = haystack.size(), n = needle.size();        

for (int i = 0; i <= m - n; i++) {                 
    int j = 0;                                     
    while (j < n && haystack[i + j] == needle[j]) {
        j++;                                       
    }                                              
    if (j == n) return i;  // Found                
}                                                  

return -1;  // Not found                           

}
// Time: O(M * N), Space: O(1)
```

### 14. Sort Colors (LC 75) - Dutch National Flag  HARD

 PATTERN: THREE Pointers (Partition into 3 parts)
 TEMPLATE: left (0s), mid (current), right (2s)

KEY INSIGHT (BRILLIANT!):
- Use 3 pointers to partition array into 3 sections
- left: boundary for 0s, right: boundary for 2s, mid: current element
- [0...left-1]: all 0s, [left...mid-1]: all 1s, [mid...right]: unknown, [right+1...n]: all 2s

**WHY IT WORKS:**
- mid explores unknown region
- When see 0: swap with left, advance both
- When see 1: just advance mid (already in correct section)
- When see 2: swap with right, DON'T advance mid (need to check swapped element)

**COMMON MISTAKES:**
 Advancing mid when swapping with right
 Wrong initialization of pointers
 Only advance mid for 0s and 1s, NOT for 2s

**GOLDEN RULE:**
> After swap with right, DON'T move mid (might get 0 or 2)

```cpp
void sortColors(vector<int>& nums) {
int left = 0;           // Boundary for 0s                    
int mid = 0;            // Current element                    
int right = nums.size() - 1;  // Boundary for 2s              

while (mid <= right) {                                        
    if (nums[mid] == 0) {                                     
        swap(nums[left], nums[mid]);                          
        left++;                                               
        mid++;   // Can advance because left area has 0s or 1s
    } else if (nums[mid] == 1) {                              
        mid++;   // Already in correct position               
    } else {  // nums[mid] == 2                               
        swap(nums[mid], nums[right]);                         
        right--;                                              
        // DON'T advance mid! Need to check swapped element   
    }                                                         
}                                                             

}
// Time: O(N), Space: O(1)
```

### 15. Find the Duplicate Number (LC 287)  HARD

 PATTERN: Floyd's Cycle Detection (Array as Linked List!)
 TEMPLATE: Treat array indices as pointers

KEY INSIGHT (MIND-BLOWING!):
- Array with n+1 elements and values in [1, n] > must have duplicate
- Treat each value as pointer: nums[i] points to nums[nums[i]]
- Duplicate creates a cycle! Use Floyd's algorithm

**WHY IT WORKS:**
- If nums[i] = j, think of it as i > j (like linked list)
- Duplicate means two indices point to same value > cycle!
- Example: [1,3,4,2,2] > 0>1>3>2>4>2 (cycle at 2)

**MATHEMATICAL PROOF:**
- Position 0 is always outside cycle (no value can be 0)
- Duplicate value is the cycle entry point
- Apply Floyd's two-phase algorithm

**CONSTRAINTS REQUIRED:**
- Array size n+1, values in [1, n]
- Must not modify array
- O(1) extra space

```cpp
int findDuplicate(vector<int>& nums) {
// Phase 1: Find intersection point in cycle    
int slow = nums[0];                             
int fast = nums[0];                             

do {                                            
    slow = nums[slow];           // Move 1 step 
    fast = nums[nums[fast]];     // Move 2 steps
} while (slow != fast);                         

// Phase 2: Find cycle entry (duplicate)        
slow = nums[0];                                 
while (slow != fast) {                          
    slow = nums[slow];                          
    fast = nums[fast];                          
}                                               

return slow;  // The duplicate number           

}
// Time: O(N), Space: O(1)
```

### 16. 4Sum (LC 18)

 PATTERN: Fixed Two + Two Pointers
 TEMPLATE: Two nested loops + two pointers

**KEY INSIGHT:**
- Extension of 3Sum: fix TWO elements, then two-pointer for remaining two
- Careful with duplicate skipping at multiple levels
- Same principle: sorted array enables pruning

WHY O(N3) not O(N⁴):
- Fix first: O(N)
- Fix second: O(N)
- Two pointers: O(N)
- Total: O(N3)

**OPTIMIZATION TRICKS:**
- Skip early if nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target
- Skip early if nums[i] + nums[n-3] + nums[n-2] + nums[n-1] < target

```cpp
vector<vector<int>> fourSum(vector<int>& nums, int target) {
vector<vector<int>> result;                                                   
int n = nums.size();                                                          
if (n < 4) return result;                                                     

sort(nums.begin(), nums.end());                                               

for (int i = 0; i < n - 3; i++) {                                             
    if (i > 0 && nums[i] == nums[i-1]) continue;  // Skip duplicates          

    for (int j = i + 1; j < n - 2; j++) {                                     
        if (j > i + 1 && nums[j] == nums[j-1]) continue;  // Skip duplicates  

        int left = j + 1, right = n - 1;                                      
        long long target2 = (long long)target - nums[i] - nums[j];            

        while (left < right) {                                                
            int sum = nums[left] + nums[right];                               

            if (sum == target2) {                                             
                result.push_back({nums[i], nums[j], nums[left], nums[right]});

                while (left < right && nums[left] == nums[left+1]) left++;    
                while (left < right && nums[right] == nums[right-1]) right--; 

                left++;                                                       
                right--;                                                      
            } else if (sum < target2) {                                       
                left++;                                                       
            } else {                                                          
                right--;                                                      
            }                                                                 
        }                                                                     
    }                                                                         
}                                                                             

return result;                                                                

}
// Time: O(N3), Space: O(1) excluding output
```

### 17. Next Permutation (LC 31)  HARD

 PATTERN: Multi-stage Two Pointers
 TEMPLATE: Find pivot, find swap, reverse

**KEY INSIGHT (ALGORITHM DESIGN):**
1. Find rightmost ascending pair (pivot)
2. Find smallest element > pivot from right
3. Swap them
4. Reverse everything after pivot position

**WHY IT WORKS:**
- Example: [1,3,5,4,2] > pivot=3 (index 1)
- Find smallest > 3 from right: 4
- Swap: [1,4,5,3,2]
- Reverse after pivot: [1,4,2,3,5] Y

**EDGE CASES:**
- Descending array > reverse entire array
- [3,2,1] > [1,2,3]

**GOLDEN RULE:**
> Find first decrease from right, that's where change happens

```cpp
void nextPermutation(vector<int>& nums) {
int n = nums.size();                                     

// Step 1: Find pivot (rightmost ascending pair)         
int pivot = -1;                                          
for (int i = n - 2; i >= 0; i--) {                       
    if (nums[i] < nums[i + 1]) {                         
        pivot = i;                                       
        break;                                           
    }                                                    
}                                                        

// If no pivot, array is descending > reverse all        
if (pivot == -1) {                                       
    reverse(nums.begin(), nums.end());                   
    return;                                              
}                                                        

// Step 2: Find smallest element > nums[pivot] from right
for (int i = n - 1; i > pivot; i--) {                    
    if (nums[i] > nums[pivot]) {                         
        swap(nums[i], nums[pivot]);                      
        break;                                           
    }                                                    
}                                                        

// Step 3: Reverse everything after pivot                
reverse(nums.begin() + pivot + 1, nums.end());           

}
// Time: O(N), Space: O(1)
```

### 18. Partition List (LC 86)

 PATTERN: Split & Merge (Two Separate Lists)
 TEMPLATE: Build two lists, then connect

**KEY INSIGHT:**
- Create two separate lists: less than x, greater/equal to x
- Maintain relative order within each list
- Connect them at the end

**WHY TWO DUMMY NODES:**
- Dummy nodes simplify edge cases (empty lists)
- Easy to connect lists: less_tail > greater_head

```cpp
ListNode* partition(ListNode* head, int x) {
ListNode lessHead(0), greaterHead(0);               
ListNode *less = &lessHead, *greater = &greaterHead;

while (head) {                                      
    if (head->val < x) {                            
        less->next = head;                          
        less = less->next;                          
    } else {                                        
        greater->next = head;                       
        greater = greater->next;                    
    }                                               
    head = head->next;                              
}                                                   

greater->next = nullptr;  // Important! Avoid cycle 
less->next = greaterHead.next;  // Connect two lists

return lessHead.next;                               

}
// Time: O(N), Space: O(1)
```

### 19. Squares of a Sorted Array (LC 977)

 PATTERN: Opposite Ends + Build Result Backwards
 TEMPLATE: Compare absolute values from both ends

**KEY INSIGHT:**
- Array sorted, but can have negative numbers
- Largest square is at one of the ends!
- Build result array from end to start (largest to smallest)

**WHY IT WORKS:**
- [-4,-1,0,3,10] > squares: [0,1,9,16,100]
- Compare |nums[left]| vs |nums[right]|
- Larger absolute value > larger square > place at end

**GOLDEN RULE:**
> Fill result backwards, comparing absolute values from ends

```cpp
vector<int> sortedSquares(vector<int>& nums) {
int n = nums.size();                        
vector<int> result(n);                      
int left = 0, right = n - 1;                
int pos = n - 1;  // Fill from end          

while (left <= right) {                     
    int leftSq = nums[left] * nums[left];   
    int rightSq = nums[right] * nums[right];

    if (leftSq > rightSq) {                 
        result[pos--] = leftSq;             
        left++;                             
    } else {                                
        result[pos--] = rightSq;            
        right--;                            
    }                                       
}                                           

return result;                              

}
// Time: O(N), Space: O(N)
```

### 20. Valid Triangle Number (LC 611) 

 PATTERN: Fixed Largest + Two Pointers
 TEMPLATE: Sort, fix largest side, two pointers for other two

**KEY INSIGHT (TRIANGLE INEQUALITY):**
- For triangle: a + b > c (where c is largest)
- After sorting, if a + b > c, then ALL pairs between them work!
- If nums[i] + nums[j] > nums[k], count = j - i

**WHY IT WORKS:**
- Fix largest side (k)
- For any i < j < k where nums[i] + nums[j] > nums[k]
- ALL pairs (i, i+1), (i, i+2), ..., (i, j) also satisfy condition!
- Because array is sorted

**BRILLIANT OPTIMIZATION:**
- When condition satisfied, count (j - i) triangles at once!

```cpp
int triangleNumber(vector<int>& nums) {
sort(nums.begin(), nums.end());                                  
int count = 0;                                                   

// Fix largest side                                              
for (int k = nums.size() - 1; k >= 2; k--) {                     
    int left = 0, right = k - 1;                                 

    while (left < right) {                                       
        if (nums[left] + nums[right] > nums[k]) {                
            // All pairs (left, left+1), ..., (left, right) work!
            count += right - left;                               
            right--;                                             
        } else {                                                 
            left++;                                              
        }                                                        
    }                                                            
}                                                                

return count;                                                    

}
// Time: O(N2), Space: O(1)
```

### 21. Boats to Save People (LC 881)

 PATTERN: Opposite Ends (Greedy Pairing)
 TEMPLATE: Pair heaviest with lightest

**KEY INSIGHT (GREEDY STRATEGY):**
- Each boat holds at most 2 people
- Always try to pair heaviest person with lightest
- If can't pair, heaviest goes alone

**WHY GREEDY WORKS:**
- Pairing heaviest with lightest maximizes boat utilization
- If heaviest can't pair with lightest, can't pair with anyone!
- Optimal to send them alone

**PROOF OF CORRECTNESS:**
- If heavy + light > limit, heavy must go alone
- If heavy + light < limit, this is best use of boat
- Any other pairing wastes opportunity

```cpp
int numRescueBoats(vector<int>& people, int limit) {
sort(people.begin(), people.end());                      
int left = 0, right = people.size() - 1;                 
int boats = 0;                                           

while (left <= right) {                                  
    if (people[left] + people[right] <= limit) {         
        left++;   // Pair them                           
    }                                                    
    right--;  // Heaviest person boards (alone or paired)
    boats++;                                             
}                                                        

return boats;                                            

}
// Time: O(N log N), Space: O(1)
```

### 22. Reorder List (LC 143)  HARD

 PATTERN: Multiple Techniques Combined
 TEMPLATE: Find middle + Reverse + Merge

**KEY INSIGHT:**
- Combine THREE two-pointer techniques:
1. Find middle (slow & fast)
2. Reverse second half
3. Merge two lists (parallel)

**WHY THIS APPROACH:**
- Can't use extra space (must be in-place)
- Pattern: L0 > Ln > L1 > Ln-1 > L2 > Ln-2...
- Split, reverse second, then alternate merge

**COMMON MISTAKES:**
 Not breaking connection at middle
 Forgetting to handle odd/even length differently
 Careful with null checks during merge

```cpp
void reorderList(ListNode* head) {
if (!head || !head->next) return;              

// Step 1: Find middle using slow & fast       
ListNode *slow = head, *fast = head;           
while (fast->next && fast->next->next) {       
    slow = slow->next;                         
    fast = fast->next->next;                   
}                                              

// Step 2: Reverse second half                 
ListNode *second = slow->next;                 
slow->next = nullptr;  // Break list           

ListNode *prev = nullptr;                      
while (second) {                               
    ListNode *temp = second->next;             
    second->next = prev;                       
    prev = second;                             
    second = temp;                             
}                                              
second = prev;  // Head of reversed second half

// Step 3: Merge two lists alternately         
ListNode *first = head;                        
while (second) {                               
    ListNode *temp1 = first->next;             
    ListNode *temp2 = second->next;            

    first->next = second;                      
    second->next = temp1;                      

    first = temp1;                             
    second = temp2;                            
}                                              

}
// Time: O(N), Space: O(1)
```

### 23. 3Sum Closest (LC 16)

 PATTERN: Fixed + Two Pointers (Track Minimum Distance)
 TEMPLATE: Similar to 3Sum, but track closest

**KEY INSIGHT:**
- Same structure as 3Sum, but track closest sum instead
- Update result when found closer sum
- No need to skip duplicates (looking for closest, not unique)

```cpp
int threeSumClosest(vector<int>& nums, int target) {
sort(nums.begin(), nums.end());                         
int closest = nums[0] + nums[1] + nums[2];              

for (int i = 0; i < nums.size() - 2; i++) {             
    int left = i + 1, right = nums.size() - 1;          

    while (left < right) {                              
        int sum = nums[i] + nums[left] + nums[right];   

        if (abs(sum - target) < abs(closest - target)) {
            closest = sum;                              
        }                                               

        if (sum < target) {                             
            left++;                                     
        } else if (sum > target) {                      
            right--;                                    
        } else {                                        
            return sum;  // Exact match                 
        }                                               
    }                                                   
}                                                       

return closest;                                         

}
// Time: O(N2), Space: O(1)
```

### 24. Remove Nth Node From End (LC 19) 

 PATTERN: Two Pass with Gap
 TEMPLATE: Maintain gap of n between pointers

**KEY INSIGHT:**
- Use two pointers with fixed gap of n
- When fast reaches end, slow is at (n+1)th from end
- Delete slow->next

**WHY IT WORKS:**
- Gap of n means when fast at end, slow at target's previous node
- Single pass through list
- Dummy node handles edge case of removing head

**EDGE CASES:**
- Remove head (use dummy node)
- List size = n

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
ListNode dummy(0);                      
dummy.next = head;                      
ListNode *slow = &dummy, *fast = &dummy;

// Move fast n+1 steps ahead            
for (int i = 0; i <= n; i++) {          
    fast = fast->next;                  
}                                       

// Move both until fast reaches end     
while (fast) {                          
    slow = slow->next;                  
    fast = fast->next;                  
}                                       

// Remove nth node                      
ListNode *toDelete = slow->next;        
slow->next = slow->next->next;          
delete toDelete;                        

return dummy.next;                      

}
// Time: O(N), Space: O(1)
```

## PART 4: QUICK REVISION TABLE

```
+-----------------------------------------------------------------------------+
|                         PATTERN SELECTION GUIDE                             |
+-------------------------+-----------------------+---------------------------+
| Problem Clue            | Pattern               | Template                  |
+-------------------------+-----------------------+---------------------------+
| Sorted array + target   | Opposite Ends         | l++, r--                  |
| Palindrome/reverse      | Opposite Ends         | Compare from ends         |
| Container/trapping      | Opposite Ends         | Move smaller boundary     |
|                         |                       |                           |
| Remove/filter in-place  | Slow & Fast           | slow=write, fast=read     |
| Linked list cycle       | Slow & Fast           | Floyd's (1x, 2x)          |
| Partition array         | Slow & Fast           | slow=boundary             |
|                         |                       |                           |
| Merge sorted arrays     | Parallel              | Compare smaller           |
| Intersection            | Parallel              | Two pointers              |
| Pattern matching        | Parallel              | String comparison         |
+-------------------------+-----------------------+---------------------------+

+-----------------------------------------------------------------------------+
|                         CRITICAL PATTERNS                                   |
+-----------------------------------------------------------------------------+
|                                                                             |
| 1. OPPOSITE ENDS (Two Sum Pattern)                                          |
|    ----------------------------------------------------------------         |
|    int l = 0, r = n - 1;                                                    |
|    while (l < r) {                                                          |
|        if (sum < target) l++;                                               |
|        else if (sum > target) r--;                                          |
|        else return {l, r};                                                  |
|    }                                                                        |
|                                                                             |
| 2. SLOW & FAST (Remove Duplicates Pattern)                                  |
|    ----------------------------------------------------------------         |
|    int slow = 0;                                                            |
|    for (int fast = 0; fast < n; fast++) {                                   |
|        if (keep_condition) {                                                |
|            arr[slow++] = arr[fast];                                         |
|        }                                                                    |
|    }                                                                        |
|                                                                             |
| 3. FLOYD'S CYCLE DETECTION                                                  |
|    ----------------------------------------------------------------         |
|    slow = head, fast = head;                                                |
|    while (fast && fast->next) {                                             |
|        slow = slow->next;                                                   |
|        fast = fast->next->next;                                             |
|        if (slow == fast) return true;                                       |
|    }                                                                        |
|                                                                             |
| 4. PARALLEL MERGE (Sorted Arrays)                                           |
|    ----------------------------------------------------------------         |
|    int i = 0, j = 0;                                                        |
|    while (i < m && j < n) {                                                 |
|        if (arr1[i] < arr2[j]) process(arr1[i++]);                           |
|        else process(arr2[j++]);                                             |
|    }                                                                        |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                         COMMON MISTAKES                                     |
+-----------------------------------------------------------------------------+
|                                                                             |
|  MISTAKE 1: Wrong termination condition                                     |
|    while (l <= r)  //  Should be l < r for opposite ends                    |
|    FIX: while (l < r) for opposite ends pattern                             |
|                                                                             |
|  MISTAKE 2: Not handling remaining elements                                 |
|    // After parallel merge, forgot to copy remaining                        |
|    FIX: while (i < m) copy remaining from first array                       |
|         while (j < n) copy remaining from second array                      |
|                                                                             |
|  MISTAKE 3: Moving wrong pointer                                            |
|    if (height[l] < height[r]) r--;  //  Wrong!                              |
|    FIX: Move pointer with smaller value                                     |
|                                                                             |
|  MISTAKE 4: Fast pointer not checking null                                  |
|    while (fast->next)  //  May crash                                        |
|    FIX: while (fast && fast->next)                                          |
|                                                                             |
|  MISTAKE 5: Overwriting before reading (merge)                              |
|    Merge forward in-place  //  Overwrites data                              |
|    FIX: Merge backward from end                                             |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                       GOLDEN RULES - MEMORIZE!                              |
+-----------------------------------------------------------------------------+
|                                                                             |
|  1⃣  Opposite ends ONLY works on sorted arrays or symmetry checks           |
|                                                                             |
|  2⃣  Slow pointer = write position, Fast pointer = read position            |
|                                                                             |
|  3⃣  Floyd's: slow moves 1, fast moves 2 (for cycle detection)              |
|                                                                             |
|  4⃣  For two sum on sorted array: move left if sum too small                |
|                                                                             |
|  5⃣  Move pointer with smaller value/height (greedy problems)               |
|                                                                             |
|  6⃣  In-place merge: fill from END to avoid overwriting                     |
|                                                                             |
|  7⃣  Always check: null pointers, empty arrays, out of bounds               |
|                                                                             |
|  8⃣  Parallel pattern: handle remaining elements after main loop            |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                        INTERVIEW CHEAT CODES                                |
+-----------------------------------------------------------------------------+
|                                                                             |
|   "Since the array is sorted, I can use two pointers from both ends."       |
|                                                                             |
|   "I'll use slow and fast pointers where slow tracks the write position."   |
|                                                                             |
|   "For cycle detection, I'll use Floyd's algorithm with 1x and 2x speed."   |
|                                                                             |
|   "I'll merge backward to avoid overwriting elements in-place."             |
|                                                                             |
|   "I need to move the pointer with the smaller value to explore better      |
|      options."                                                              |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
                    ADDITIONAL PATTERNS & PROBLEMS                             
===============================================================================
```

### **PATTERN: VALID PALINDROME II (Skip One Character)**

```
bool validPalindrome(string s) {
int l = 0, r = s.size() - 1;                                          

while (l < r) {                                                       
    if (s[l] != s[r]) {                                               
        // Try skipping either left or right character                
        return isPalindrome(s, l + 1, r) || isPalindrome(s, l, r - 1);
    }                                                                 
    l++; r--;                                                         
}                                                                     
return true;                                                          

}

bool isPalindrome(string& s, int l, int r) {
while (l < r) {                        
    if (s[l++] != s[r--]) return false;
}                                      
return true;                           

}
```

### **PATTERN: MERGE STRINGS ALTERNATELY**

```
string mergeAlternately(string word1, string word2) {
string result;                                 
int i = 0, j = 0;                              

while (i < word1.size() || j < word2.size()) { 
    if (i < word1.size()) result += word1[i++];
    if (j < word2.size()) result += word2[j++];
}                                              

return result;                                 

}
```

### **PATTERN: STRING COMPRESSION**

```cpp
int compress(vector<char>& chars) {
int write = 0, read = 0;                              

while (read < chars.size()) {                         
    char ch = chars[read];                            
    int count = 0;                                    

    // Count consecutive characters                   
    while (read < chars.size() && chars[read] == ch) {
        read++;                                       
        count++;                                      
    }                                                 

    // Write character                                
    chars[write++] = ch;                              

    // Write count if > 1                             
    if (count > 1) {                                  
        for (char c : to_string(count)) {             
            chars[write++] = c;                       
        }                                             
    }                                                 
}                                                     

return write;                                         

}
```

### **PATTERN: BACKSPACE STRING COMPARE (Reverse Traversal)**

 **KEY INSIGHT**: Process from RIGHT to handle backspaces in O(1) space

```
bool backspaceCompare(string s, string t) {
int i = s.size() - 1, j = t.size() - 1;  

while (i >= 0 || j >= 0) {               
    i = getNextValidChar(s, i);          
    j = getNextValidChar(t, j);          

    if (i >= 0 && j >= 0) {              
        if (s[i] != t[j]) return false;  
    } else if (i >= 0 || j >= 0) {       
        return false;  // One ended early
    }                                    
    i--; j--;                            
}                                        
return true;                             

}

int getNextValidChar(string& s, int idx) {
int skip = 0;                            
while (idx >= 0) {                       
    if (s[idx] == '#') { skip++; idx--; }
    else if (skip > 0) { skip--; idx--; }
    else break;                          
}                                        
return idx;                              

}
```

### **PATTERN: BAG OF TOKENS (Opposite Ends Greedy)**

 **KEY INSIGHT**: Play smallest tokens face-up, largest face-down

```cpp
int bagOfTokensScore(vector<int>& tokens, int power) {
sort(tokens.begin(), tokens.end());               
int l = 0, r = tokens.size() - 1;                 
int score = 0, maxScore = 0;                      

while (l <= r) {                                  
    if (power >= tokens[l]) {                     
        // Play face-up (spend power, gain score) 
        power -= tokens[l++];                     
        score++;                                  
        maxScore = max(maxScore, score);          
    } else if (score > 0) {                       
        // Play face-down (gain power, lose score)
        power += tokens[r--];                     
        score--;                                  
    } else {                                      
        break;                                    
    }                                             
}                                                 

return maxScore;                                  

}
```

### **PATTERN: MINIMUM LENGTH AFTER DELETING SIMILAR ENDS**

```
int minimumLength(string s) {
int l = 0, r = s.size() - 1;              

while (l < r && s[l] == s[r]) {           
    char c = s[l];                        
    // Skip all same characters from left 
    while (l <= r && s[l] == c) l++;      
    // Skip all same characters from right
    while (l <= r && s[r] == c) r--;      
}                                         

return r - l + 1;                         

}
```

### **PATTERN: SENTENCE SIMILARITY III**

 **KEY INSIGHT**: Match words from both ends, check if remaining is contiguous

```cpp
bool areSentencesSimilar(string s1, string s2) {
vector<string> w1 = split(s1), w2 = split(s2);             
if (w1.size() < w2.size()) swap(w1, w2);                   

int i = 0, j = 0;                                          
int n1 = w1.size(), n2 = w2.size();                        

// Match from start                                        
while (i < n2 && w1[i] == w2[i]) i++;                      

// Match from end                                          
while (j < n2 - i && w1[n1 - 1 - j] == w2[n2 - 1 - j]) j++;

return i + j >= n2;                                        

}
```

### **PATTERN: NUMBER OF SUBSEQUENCES (Sorted + Two Pointers + Counting)**

 **KEY INSIGHT**: Sort array, fix minimum, count valid maximums

```cpp
int numSubseq(vector<int>& nums, int target) {
const int MOD = 1e9 + 7;                                           
sort(nums.begin(), nums.end());                                    
int n = nums.size();                                               

// Precompute powers of 2                                          
vector<long> pow2(n);                                              
pow2[0] = 1;                                                       
for (int i = 1; i < n; i++) {                                      
    pow2[i] = (pow2[i-1] * 2) % MOD;                               
}                                                                  

int l = 0, r = n - 1;                                              
long count = 0;                                                    

while (l <= r) {                                                   
    if (nums[l] + nums[r] <= target) {                             
        // All 2^(r-l) subsequences starting with nums[l] are valid
        count = (count + pow2[r - l]) % MOD;                       
        l++;                                                       
    } else {                                                       
        r--;                                                       
    }                                                              
}                                                                  

return count;                                                      

}
```

### **PATTERN: ROTATE ARRAY (Reverse Trick)**

 **KEY INSIGHT**: Three reverses = rotation!

```cpp
void rotate(vector<int>& nums, int k) {
k %= nums.size();
reverse(nums.begin(), nums.end());           // Reverse all
reverse(nums.begin(), nums.begin() + k);     // Reverse first k
reverse(nums.begin() + k, nums.end());       // Reverse rest

}

// Example: [1,2,3,4,5], k=2
// Reverse all: [5,4,3,2,1]
// Reverse first 2: [4,5,3,2,1]
// Reverse rest: [4,5,1,2,3] Y
```

## COMPLETE PROBLEM LIST BY CATEGORY

**OPPOSITE ENDS (Sorted / Symmetry / Greedy)**

- 125.  Valid Palindrome 
- 167.  Two Sum II (Sorted Array) 
- 344.  Reverse String 
- 680.  Valid Palindrome II 
- 977.  Squares of a Sorted Array 
- 11.   Container With Most Water 
- 42.   Trapping Rain Water 
- 407.  Trapping Rain Water II  (3D version > See Heap & Kth Problems.txt)
- 15.   3Sum 
- 18.   4Sum 
- 881.  Boats to Save People 
- 948.  Bag of Tokens 
- 1750. Minimum Length of String after Deleting Similar Ends 
- 1855. Sentence Similarity III 
- 1498. Number of Subsequences That Satisfy Given Sum 
- 2491. Divide Players Into Teams of Equal Skill 

**SLOW & FAST (In-Place Modification)**

- 26.   Remove Duplicates from Sorted Array 
- 27.   Remove Element 
- 80.   Remove Duplicates from Sorted Array II 
- 283.  Move Zeroes 
- 443.  String Compression 
- 905.  Sort Array by Parity 
- 2149. Rearrange Array Elements by Sign 
- 2161. Partition Array According to Given Pivot 
- 2460. Apply Operations to an Array 

**PARALLEL (Two Arrays/Strings)**

- 88.   Merge Sorted Array 
- 1768. Merge Strings Alternately 
- 2570. Merge Two 2D Arrays by Summing Values 
- 408.  Valid Word Abbreviation 
- 1662. Check If Two String Arrays are Equivalent 
- 349.  Intersection of Two Arrays 
- 2109. Adding Spaces to a String 

**STRING MANIPULATION**

- 557.  Reverse Words in a String III 
- 844.  Backspace String Compare 
- 1578. Minimum Time to Make Rope Colorful 

**GREEDY + TWO POINTERS**

- 455.  Assign Cookies 
- 611.  Valid Triangle Number 

**REVERSE TRICK / ROTATION**

- 189.  Rotate Array 

**SPECIAL PATTERNS**

- 2149. Array With Elements Not Equal to Average of Neighbors 
- 2108. Find First Palindromic String in the Array 

## **MASTER PROBLEM MAPPING TABLE**

```
+---------------------------------------------------------+------------------------+
| Problem                                                 | Pattern                |
+---------------------------------------------------------+------------------------+
| Reverse String                                          | Opposite Ends          |
| Valid Palindrome                                        | Opposite Ends          |
| Valid Palindrome II                                     | Opposite Ends + Skip   |
| Valid Word Abbreviation                                 | Parallel               |
| Merge Strings Alternately                               | Parallel               |
| Merge Sorted Array                                      | Parallel (Backward)    |
| Merge Two 2D Arrays by Summing Values                   | Parallel               |
| Move Zeroes                                             | Slow & Fast            |
| Remove Duplicates From Sorted Array                     | Slow & Fast            |
| Squares of a Sorted Array                               | Opposite Ends          |
| Assign Cookies                                          | Greedy + Two Pointers  |
| Find First Palindromic String in the Array              | Simple + Opposite Ends |
| Sort Array by Parity                                    | Slow & Fast            |
| Reverse Words in a String III                           | Reverse Each Word      |
| Backspace String Compare                                | Reverse Traversal      |
| Check If Two String Arrays are Equivalent               | Parallel               |
| Apply Operations to an Array                            | Slow & Fast            |
| Adding Spaces to a String                               | Parallel               |
| String Compression                                      | Slow & Fast            |
| Remove Duplicates From Sorted Array II                  | Slow & Fast            |
| Partition Array According to Given Pivot                | Three Pointers         |
| Two Sum II Input Array Is Sorted                        | Opposite Ends          |
| 3Sum                                                    | Fixed + Two Pointers   |
| 4Sum                                                    | Fixed Two + Two Ptrs   |
| Rotate Array                                            | Reverse Trick          |
| Container With Most Water                               | Opposite Ends          |
| Number of Subsequences That Satisfy Sum Condition       | Opposite Ends + Count  |
| Array With Elements Not Equal to Average of Neighbors   | Wiggle Sort            |
| Divide Players Into Teams of Equal Skill                | Opposite Ends          |
| Boats to Save People                                    | Opposite Ends          |
| K-th Symbol in Grammar                                  | Recursion (Not 2P)     |
| Minimum Time To Make Rope Colorful                      | Consecutive Groups     |
| Rearrange Array Elements by Sign                        | Two Pointers           |
| Bag of Tokens                                           | Opposite Ends Greedy   |
| Minimum Length of String after Deleting Similar Ends    | Opposite Ends          |
| Sentence Similarity III                                 | Match From Both Ends   |
| Trapping Rain Water                                     | Opposite Ends + Max    |
+---------------------------------------------------------+------------------------+

+----------------------------------------------------------------------------------+
|                  TWO POINTERS PATTERN DECISION FLOWCHART                         |
+----------------------------------------------------------------------------------+
|                                                                                  |
|  Is the array SORTED or checking SYMMETRY (palindrome)?                          |
|    YES > OPPOSITE ENDS (left++, right--)                                         |
|                                                                                  |
|  Need to REMOVE/FILTER elements in-place?                                        |
|    YES > SLOW & FAST (slow writes, fast reads)                                   |
|                                                                                  |
|  Working with TWO arrays/strings simultaneously?                                 |
|    YES > PARALLEL (compare and advance)                                          |
|                                                                                  |
|  Need to PARTITION into groups (0s, 1s, 2s)?                                     |
|    YES > THREE POINTERS (Dutch National Flag)                                    |
|                                                                                  |
|  Looking for PAIRS that sum to target (unsorted)?                                |
|    NO! > Use HASHMAP instead (see Hashmap Patterns.txt)                          |
|                                                                                  |
|  Need to REVERSE or ROTATE array?                                                |
|    YES > REVERSE TRICK (three reverses)                                          |
|                                                                                  |
|  Processing BACKSPACES or need reverse order?                                    |
|    YES > REVERSE TRAVERSAL (process from end)                                    |
|                                                                                  |
+----------------------------------------------------------------------------------+

===============================================================================     
                                   END                                              
===============================================================================     
```
