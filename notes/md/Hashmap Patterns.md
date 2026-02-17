# **HASHMAP PATTERNS - COMPLETE GUIDE**

### **TABLE OF CONTENTS**

1. Core Concepts & When to Use Hashmap
2. Pattern 1: Frequency Counting
3. Pattern 2: Pair/Complement Lookup
4. Pattern 3: Anagram Detection
5. Pattern 4: Set Operations (Uniqueness & Sequences)
6. Pattern 5: State Encoding
7. Pattern 6: Top K Elements
8. Pattern 7: Design Problems (LRU Cache)
9. Quick Revision Table

## **PART 1: CORE CONCEPTS**

### ** WHEN TO USE HASHMAP/HASHSET?**

**STRONG SIGNALS:**

 Need O(1) lookup/insert/delete
 "Find if X exists"
 "Count frequency"
 "Find pair/complement"
 "Group by some property"
 "Check for duplicates"
 "Store state/index mapping"

**KEYWORDS TO WATCH FOR:**

- "two sum", "pair sum"
- "anagram"
- "frequency"
- "unique", "distinct"
- "most frequent"
- "group by"
- "contains duplicate"

###  HASHMAP vs HASHSET

USE HASHMAP (key > value):
- Need to store associated data (frequency, index, etc.)
- Example: {num > frequency}, {word > anagram_key}
- C++: unordered_map<K, V>

USE HASHSET (key only):
- Only need to check existence
- Example: seen elements, unique values
- C++: unordered_set<T>

**GOLDEN RULE:**
> If you need "count" or "index", use map
> If you only need "exists", use set

### ⚡ TIME & SPACE COMPLEXITY

**OPERATIONS:**
- Insert: O(1) average, O(N) worst case
- Lookup: O(1) average, O(N) worst case
- Delete: O(1) average, O(N) worst case

**SPACE:**
- O(N) for storing N elements
- Trade space for time!

WHY "AVERAGE" O(1)?
- Hash collisions can degrade to O(N)
- Good hash functions make collisions rare
- In practice, treated as O(1)

## **PART 2: PATTERN 1 - FREQUENCY COUNTING**

### **PATTERN OVERVIEW**

**CORE IDEA:**
Count how many times each element appears using a hashmap

**TEMPLATE:**

```
unordered_map<T, int> freq;

for (auto element : collection) {
freq[element]++;

}

// Now you can:
// - Find most/least frequent element
// - Check if element appears K times
// - Count elements with frequency > K
```

**WHEN TO USE:**
- "Find the most/least frequent element"
- "Count elements appearing K times"
- "Remove duplicates"

### 1. How Many Numbers Are Smaller Than Current Number (LC 1365)

 PATTERN: Frequency counting + cumulative sum
 TEMPLATE: Count frequencies, then compute prefix sum

**KEY INSIGHT:**
- Brute force: O(N2) - compare each with all others
- Optimization: Sort + count OR frequency + cumulative
- Use frequency map to avoid sorting

APPROACH 1: Sort + Binary Search (O(N log N))
APPROACH 2: Frequency + Cumulative Sum (O(N + range))

**WHY FREQUENCY MAP WORKS:**
- Count frequency of each number
- Build cumulative count from smallest to largest
- For each number, cumulative[num-1] = count of smaller numbers

```cpp
vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
// Find range                                       
int maxNum = *max_element(nums.begin(), nums.end());

// Frequency count                                  
vector<int> freq(maxNum + 1, 0);                    
for (int num : nums) {                              
    freq[num]++;                                    
}                                                   

// Build cumulative count                           
vector<int> cumulative(maxNum + 1, 0);              
for (int i = 1; i <= maxNum; i++) {                 
    cumulative[i] = cumulative[i-1] + freq[i-1];    
}                                                   

// Build result                                     
vector<int> result;                                 
for (int num : nums) {                              
    result.push_back(cumulative[num]);              
}                                                   

return result;                                      

}
// Time: O(N + M) where M is range
// Space: O(M)
```

### 2. First Unique Character in a String (LC 387)

 PATTERN: Frequency counting + linear scan
 TEMPLATE: Count frequencies, find first with freq=1

**KEY INSIGHT:**
- Need TWO passes: count, then find
- First unique = first character with frequency 1

```
int firstUniqChar(string s) {
unordered_map<char, int> freq;      

// Count frequencies                
for (char c : s) {                  
    freq[c]++;                      
}                                   

// Find first unique                
for (int i = 0; i < s.size(); i++) {
    if (freq[s[i]] == 1) {          
        return i;                   
    }                               
}                                   

return -1;                          

}
// Time: O(N), Space: O(1) - at most 26 chars
```

### 3. Sort Characters By Frequency (LC 451)

 PATTERN: Frequency counting + sorting by frequency
 TEMPLATE: Count, sort by frequency, build result

**KEY INSIGHT:**
- Count frequencies
- Sort by frequency (can use vector of pairs or priority queue)
- Build result string

```cpp
string frequencySort(string s) {
unordered_map<char, int> freq;                 

// Count frequencies                           
for (char c : s) {                             
    freq[c]++;                                 
}                                              

// Create vector of pairs and sort by frequency
vector<pair<int, char>> freqPairs;             
for (auto& [ch, count] : freq) {               
    freqPairs.push_back({count, ch});          
}                                              
sort(freqPairs.rbegin(), freqPairs.rend());    

// Build result                                
string result;                                 
for (auto& [count, ch] : freqPairs) {          
    result.append(count, ch);                  
}                                              

return result;                                 

}
// Time: O(N log N), Space: O(N)
```

## **PART 3: PATTERN 2 - PAIR/COMPLEMENT LOOKUP**

### PATTERN OVERVIEW

**CORE IDEA:**
For each element X, check if complement (target - X) exists in hashmap

**TEMPLATE:**

```
unordered_map<int, int> seen;

for (int i = 0; i < nums.size(); i++) {
int complement = target - nums[i];

if (seen.count(complement)) {     
    // Found pair!                
    return {seen[complement], i}; 
}                                 

seen[nums[i]] = i;                

}
```

**GOLDEN RULE:**
> Check BEFORE inserting (to avoid using same element twice)

### 4. Two Sum (LC 1)  FUNDAMENTAL

 PATTERN: Complement lookup
 TEMPLATE: Most fundamental hashmap problem!

**KEY INSIGHT:**
- Brute force: O(N2) - check all pairs
- Optimization: For each num, check if (target - num) exists
- Store seen numbers with their indices

**WHY IT WORKS:**
- If we need A + B = target
- When we see B, we check if A (= target - B) was seen before
- Hashmap gives O(1) lookup!

**COMMON MISTAKES:**
 Using same element twice
 Not handling duplicates correctly
 Check before inserting

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
unordered_map<int, int> numToIndex;        

for (int i = 0; i < nums.size(); i++) {    
    int complement = target - nums[i];     

    if (numToIndex.count(complement)) {    
        return {numToIndex[complement], i};
    }                                      

    numToIndex[nums[i]] = i;               
}                                          

return {};                                 

}
// Time: O(N), Space: O(N)
```

**VARIATIONS:**
- Two Sum II (sorted array) > Use two pointers
- Two Sum III (design data structure) > Store frequencies
- Two Sum IV (BST) > Inorder + two pointers

### 5. 3Sum (LC 15) > See Two Pointers.txt

 PATTERN: Sort + Two pointers (primarily a TWO POINTERS problem)
 NOTE: Full solution in "Two Pointers.txt"

**KEY INSIGHT:**
- Fix one element, use two-pointer technique for remaining two
- Requires sorting for duplicate handling
- While you CAN use hashmap, two pointers is more efficient for 3Sum
- O(N2) time complexity

**WHY TWO POINTERS IS BETTER:**
- Easier duplicate handling after sorting
- O(1) space (excluding result)
- More intuitive for multiple elements

> See "Two Pointers.txt" for complete solution and detailed walkthrough

### 6. 4Sum II (LC 454) 

 PATTERN: Split into two groups, use hashmap
 TEMPLATE: Brilliant optimization using complement

KEY INSIGHT (BRILLIANT!):
- A + B + C + D = 0
- Rewrite as: (A + B) = -(C + D)
- Compute all sums from first two arrays
- For each sum from last two, check if complement exists

**WHY THIS WORKS:**
- Brute force: O(N⁴) - try all combinations
- Optimization: Split problem in half
- O(N2) to compute all A+B sums
- O(N2) to check all C+D sums
- Total: O(N2)!

```cpp
int fourSumCount(vector<int>& A, vector<int>& B,
             vector<int>& C, vector<int>& D) {
unordered_map<int, int> sumCount;             

// Count all sums from A and B                
for (int a : A) {                             
    for (int b : B) {                         
        sumCount[a + b]++;                    
    }                                         
}                                             

int count = 0;                                

// For each sum from C and D, check complement
for (int c : C) {                             
    for (int d : D) {                         
        int target = -(c + d);                
        if (sumCount.count(target)) {         
            count += sumCount[target];        
        }                                     
    }                                         
}                                             

return count;                                 

}
// Time: O(N2), Space: O(N2)
```

## **PART 4: PATTERN 3 - ANAGRAM DETECTION**

### PATTERN OVERVIEW

**CORE IDEA:**
Anagrams have same character frequency > use sorted string or frequency as key

**TEMPLATE:**

```cpp
unordered_map<string, vector<string>> groups;

for (string word : words) {
string key = word;
sort(key.begin(), key.end());  // Canonical form
groups[key].push_back(word);

}
```

### ALTERNATIVE (Frequency as Key):

```
string getKey(string s) {
int freq[26] = {};                                     
for (char c : s) freq[c - 'a']++;                      

string key;                                            
for (int i = 0; i < 26; i++) {                         
    if (freq[i] > 0) {                                 
        key += string(1, 'a' + i) + to_string(freq[i]);
    }                                                  
}                                                      
return key;                                            

}
```

### 7. Valid Anagram (LC 242)

 PATTERN: Frequency comparison
 TEMPLATE: Count and compare OR sort and compare

### APPROACH 1: Frequency Count (O(N))

```
bool isAnagram(string s, string t) {
if (s.size() != t.size()) return false;

int freq[26] = {};                     

for (int i = 0; i < s.size(); i++) {   
    freq[s[i] - 'a']++;                
    freq[t[i] - 'a']--;                
}                                      

for (int i = 0; i < 26; i++) {         
    if (freq[i] != 0) return false;    
}                                      

return true;                           

}
// Time: O(N), Space: O(1)
```

### APPROACH 2: Sort and Compare (O(N log N))

```
bool isAnagram(string s, string t) {
sort(s.begin(), s.end());
sort(t.begin(), t.end());
return s == t;           

}
```

### 8. Group Anagrams (LC 49) 

 PATTERN: Group by canonical form (sorted string)
 TEMPLATE: Use sorted string as key

**KEY INSIGHT:**
- All anagrams share the same sorted form
- Use sorted string as hashmap key
- Group all words with same key together

WHY SORTED STRING AS KEY?
- "eat", "tea", "ate" all sort to "aet"
- Canonical representation ensures grouping

```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
unordered_map<string, vector<string>> groups;

for (string str : strs) {                    
    string key = str;                        
    sort(key.begin(), key.end());            
    groups[key].push_back(str);              
}                                            

vector<vector<string>> result;               
for (auto& [key, group] : groups) {          
    result.push_back(group);                 
}                                            

return result;                               

}
// Time: O(N * K log K) where K is max string length
// Space: O(N * K)
```

### 9. Find All Anagrams in a String (LC 438) > See Sliding Window.txt

 PATTERN: Sliding window + frequency comparison (primarily SLIDING WINDOW)
 NOTE: Full solution in "Sliding Window.txt" (Problem 10)

**KEY INSIGHT:**
- This problem combines anagram detection with sliding window technique
- Use fixed window size = p.length()
- Track frequency matches incrementally for O(N) time
- Uses "matches" counter optimization to avoid O(26) comparison each step

WHY SLIDING WINDOW?
- Need to check EVERY substring of length p.size()
- Fixed-size window slides through string
- Frequency comparison is the anagram check

> See "Sliding Window.txt" for complete solution with frequency matching optimization

## **PART 5: PATTERN 4 - SET OPERATIONS**

### PATTERN OVERVIEW

**CORE IDEA:**
Use hashset for O(1) existence checks, uniqueness, and sequence building

**TEMPLATE:**

```
unordered_set<int> seen(nums.begin(), nums.end());

// Check existence
if (seen.count(target)) { ... }

// Check duplicates
for (int num : nums) {
if (seen.count(num)) return true;  // Duplicate!
seen.insert(num);                               

}
```

### 10. Contains Duplicate (LC 217)

 PATTERN: Set for uniqueness check
 TEMPLATE: Simplest hashset application

```cpp
bool containsDuplicate(vector<int>& nums) {
unordered_set<int> seen;  

for (int num : nums) {    
    if (seen.count(num)) {
        return true;      
    }                     
    seen.insert(num);     
}                         

return false;             

}
// Time: O(N), Space: O(N)
```

### 11. Contains Duplicate II (LC 219)

 PATTERN: Sliding window + hashset
 TEMPLATE: Maintain set of size K

**KEY INSIGHT:**
- Need duplicates within distance K
- Maintain sliding window of size K
- Use set to check duplicates in window

```cpp
bool containsNearbyDuplicate(vector<int>& nums, int k) {
unordered_set<int> window;             

for (int i = 0; i < nums.size(); i++) {
    // Check if duplicate in window    
    if (window.count(nums[i])) {       
        return true;                   
    }                                  

    window.insert(nums[i]);            

    // Maintain window size            
    if (window.size() > k) {           
        window.erase(nums[i - k]);     
    }                                  
}                                      

return false;                          

}
// Time: O(N), Space: O(K)
```

### 12. Longest Consecutive Sequence (LC 128) 

 PATTERN: Set for O(1) lookup + sequence building
 TEMPLATE: Brilliant algorithm using set cleverly

KEY INSIGHT (GENIUS!):
- Brute force: Sort O(N log N)
- Optimization: Use set for O(1) checks
- Only start counting from BEGINNING of sequence
- How to detect beginning? Check if (num - 1) exists

**WHY THIS IS O(N):**
- Each number is visited at most twice:
1. Once in outer loop
2. Once as part of a sequence (starting from sequence start)

- Key: Only count from sequence start!

**BRILLIANT TRICK:**
```
if (!numSet.count(num - 1)) > This is sequence start!
```

Then count how long the sequence is

```cpp
int longestConsecutive(vector<int>& nums) {
unordered_set<int> numSet(nums.begin(), nums.end());
int maxLen = 0;                                     

for (int num : nums) {                              
    // Only start counting from sequence beginning  
    if (!numSet.count(num - 1)) {                   
        int currNum = num;                          
        int currStreak = 1;                         

        // Count consecutive sequence               
        while (numSet.count(currNum + 1)) {         
            currNum++;                              
            currStreak++;                           
        }                                           

        maxLen = max(maxLen, currStreak);           
    }                                               
}                                                   

return maxLen;                                      

}
// Time: O(N), Space: O(N)
```

**EXAMPLE WALKTHROUGH:**
```
nums = [100, 4, 200, 1, 3, 2]
set = {1, 2, 3, 4, 100, 200}

num=100: 99 not in set > sequence start! Count: 100 (length 1)
num=4: 3 in set > not sequence start, skip
num=200: 199 not in set > sequence start! Count: 200 (length 1)
num=1: 0 not in set > sequence start! Count: 1,2,3,4 (length 4) Y
```

Result: 4

### 13. Intersection of Two Arrays (LC 349)

 PATTERN: Set intersection
 TEMPLATE: Convert to sets and intersect

```cpp
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
unordered_set<int> set1(nums1.begin(), nums1.end());
unordered_set<int> result;                          

for (int num : nums2) {                             
    if (set1.count(num)) {                          
        result.insert(num);                         
    }                                               
}                                                   

return vector<int>(result.begin(), result.end());   

}
// Time: O(N + M), Space: O(N + M)
```

## **PART 6: PATTERN 5 - STATE ENCODING**

### 14. Valid Sudoku (LC 36) 

 PATTERN: Encode state as string, use set to detect duplicates
 TEMPLATE: Creative string encoding

KEY INSIGHT (BRILLIANT ENCODING!):
- Need to check 3 constraints: row, column, 3x3 box
- Instead of 3 separate data structures, use ONE set
- Encode state as string: "r<row><digit>", "c<col><digit>", "b<box><digit>"
- If string already in set > invalid!

WHY STRING ENCODING?
- Elegant: one set instead of multiple arrays
- Clear: state is self-documenting
- Efficient: O(1) lookups

**BOX INDEX CALCULATION:**
- box_index = (row / 3) * 3 + (col / 3)
- OR: "b" + to_string(row/3) + to_string(col/3)

```cpp
bool isValidSudoku(vector<vector<char>>& board) {
unordered_set<string> seen;                                             

for (int i = 0; i < 9; i++) {                                           
    for (int j = 0; j < 9; j++) {                                       
        char curr = board[i][j];                                        

        if (curr != '.') {                                              
            // Encode three constraints as strings                      
            string row = "r" + to_string(i) + curr;                     
            string col = "c" + to_string(j) + curr;                     
            string box = "b" + to_string(i/3) + to_string(j/3) + curr;  

            // Check if any constraint violated                         
            if (seen.count(row) || seen.count(col) || seen.count(box)) {
                return false;                                           
            }                                                           

            seen.insert(row);                                           
            seen.insert(col);                                           
            seen.insert(box);                                           
        }                                                               
    }                                                                   
}                                                                       

return true;                                                            

}
// Time: O(1) - board is fixed 9x9
// Space: O(1) - at most 81 cells
```

**EXAMPLE:**
```
board[0][0] = '5'
```

> Encodes as:
"r05" (row 0, digit 5)
"c05" (col 0, digit 5)
"b005" (box (0,0), digit 5)

## **PART 7: PATTERN 6 - TOP K ELEMENTS**

### 15. Top K Frequent Elements (LC 347) 

 PATTERN: Frequency map + heap OR bucket sort
 TEMPLATE: Count frequencies, then extract top K

**KEY INSIGHT:**
- Step 1: Count frequencies with hashmap
- Step 2: Find top K frequent

### APPROACH 1: Max Heap (O(N log K))

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
unordered_map<int, int> freq;              
for (int num : nums) {                     
    freq[num]++;                           
}                                          

// Max heap: {frequency, number}           
priority_queue<pair<int, int>> maxHeap;    
for (auto& [num, count] : freq) {          
    maxHeap.push({count, num});            
}                                          

vector<int> result;                        
for (int i = 0; i < k; i++) {              
    result.push_back(maxHeap.top().second);
    maxHeap.pop();                         
}                                          

return result;                             

}
// Time: O(N log N), Space: O(N)
```

### APPROACH 2: Min Heap (O(N log K)) - BETTER!

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
unordered_map<int, int> freq;                          
for (int num : nums) {                                 
    freq[num]++;                                       
}                                                      

// Min heap of size K                                  
priority_queue<pair<int, int>, vector<pair<int, int>>, 
               greater<pair<int, int>>> minHeap;       

for (auto& [num, count] : freq) {                      
    minHeap.push({count, num});                        
    if (minHeap.size() > k) {                          
        minHeap.pop();  // Remove least frequent       
    }                                                  
}                                                      

vector<int> result;                                    
while (!minHeap.empty()) {                             
    result.push_back(minHeap.top().second);            
    minHeap.pop();                                     
}                                                      

return result;                                         

}
// Time: O(N log K), Space: O(N)
```

### APPROACH 3: Bucket Sort (O(N)) - OPTIMAL!

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
unordered_map<int, int> freq;                                      
for (int num : nums) {                                             
    freq[num]++;                                                   
}                                                                  

// Bucket: index = frequency, value = list of numbers              
vector<vector<int>> bucket(nums.size() + 1);                       
for (auto& [num, count] : freq) {                                  
    bucket[count].push_back(num);                                  
}                                                                  

// Collect top K from highest frequency                            
vector<int> result;                                                
for (int i = bucket.size() - 1; i >= 0 && result.size() < k; i--) {
    for (int num : bucket[i]) {                                    
        result.push_back(num);                                     
        if (result.size() == k) break;                             
    }                                                              
}                                                                  

return result;                                                     

}
// Time: O(N), Space: O(N)
```

## **PART 8: PATTERN 7 - DESIGN PROBLEMS**

### 16. LRU Cache (LC 146)  HARD

 PATTERN: Hashmap + Doubly Linked List
 TEMPLATE: Classic data structure design problem

**KEY INSIGHT:**
- Need O(1) get AND O(1) put
- Hashmap: O(1) access by key
- Doubly linked list: O(1) insert/delete
- Map stores: key > list_node

WHY DOUBLY LINKED LIST?
- Need to move nodes to front (recently used)
- Need to remove from end (least recently used)
- Both operations are O(1) with doubly linked list

**DATA STRUCTURE:**
- Map: {key > iterator/pointer to list node}
- List: Stores {key, value} pairs in usage order
- Front = most recently used
- Back = least recently used

**OPERATIONS:**
- get(key): Move to front, return value
- put(key, value): Update or insert at front, evict if needed

```java
class LRUCache {
```

private:
```
int capacity;                                          
list<pair<int, int>> cache;  // {key, value}           
unordered_map<int, list<pair<int, int>>::iterator> map;

void moveToFront(int key, int value) {                 
    // Remove old position                             
    cache.erase(map[key]);                             
    // Insert at front                                 
    cache.push_front({key, value});                    
    // Update map                                      
    map[key] = cache.begin();                          
}                                                      
```

public:
```
LRUCache(int capacity) {                    
    this->capacity = capacity;              
}                                           

int get(int key) {                          
    if (map.find(key) == map.end()) {       
        return -1;                          
    }                                       

    // Move to front (mark as recently used)
    int value = map[key]->second;           
    moveToFront(key, value);                
    return value;                           
}                                           

void put(int key, int value) {              
    if (map.find(key) != map.end()) {       
        // Key exists, update               
        moveToFront(key, value);            
    } else {                                
        // New key                          
        if (cache.size() >= capacity) {     
            // Evict LRU (back of list)     
            int oldKey = cache.back().first;
            cache.pop_back();               
            map.erase(oldKey);              
        }                                   

        // Insert at front                  
        cache.push_front({key, value});     
        map[key] = cache.begin();           
    }                                       
}                                           
```

```
};
// Time: O(1) for both get and put
// Space: O(capacity)
```

**VISUALIZATION:**
```
Capacity = 2

put(1, 1): [1:1]
put(2, 2): [2:2, 1:1]
get(1):    [1:1, 2:2] (1 moved to front)
put(3, 3): [3:3, 1:1] (2 evicted)
```

### 17. Insert Delete GetRandom O(1) (LC 380)

 PATTERN: Hashmap + Vector for random access
 TEMPLATE: Combine two data structures

**KEY INSIGHT:**
- Insert/Delete: O(1) with hashmap
- GetRandom: O(1) needs array/vector
- Solution: Use BOTH!
- Vector stores values
- Map stores: value > index in vector

**DELETE TRICK:**
- Swap element with last element
- Pop last element (O(1))
- Update map for swapped element

```java
class RandomizedSet {
```

private:
```cpp
vector<int> nums;
unordered_map<int, int> valToIndex;
```

public:
```
bool insert(int val) {                       
    if (valToIndex.count(val)) return false; 

    nums.push_back(val);                     
    valToIndex[val] = nums.size() - 1;       
    return true;                             
}                                            

bool remove(int val) {                       
    if (!valToIndex.count(val)) return false;

    // Swap with last element                
    int lastElement = nums.back();           
    int idxToRemove = valToIndex[val];       

    nums[idxToRemove] = lastElement;         
    valToIndex[lastElement] = idxToRemove;   

    // Remove last                           
    nums.pop_back();                         
    valToIndex.erase(val);                   

    return true;                             
}                                            

int getRandom() {                            
    int randomIndex = rand() % nums.size();  
    return nums[randomIndex];                
}                                            
```

```
};
// Time: O(1) for all operations
// Space: O(N)
```

## **PART 9: QUICK REVISION TABLE**

```
+-----------------------------------------------------------------------------+
|                         PATTERN SELECTION GUIDE                             |
+---------------------------+---------------------+---------------------------+
| Problem Type              | Data Structure      | Key Technique             |
+---------------------------+---------------------+---------------------------+
| Count frequencies         | map<T, int>         | freq[element]++           |
| Find pair/complement      | map<T, index>       | Check target - num        |
| Group anagrams            | map<key, vector>    | Sorted string as key      |
| Check existence           | set<T>              | set.count(element)        |
| Longest consecutive       | set<T>              | Only start from beginning |
| Top K frequent            | map + heap/bucket   | Count then extract top K  |
| Valid Sudoku              | set<string>         | Encode state as string    |
| LRU Cache                 | map + list          | Map to list iterator      |
+---------------------------+---------------------+---------------------------+

+-----------------------------------------------------------------------------+
|                         CRITICAL PATTERNS                                   |
+-----------------------------------------------------------------------------+
|                                                                             |
| 1. FREQUENCY COUNTING                                                       |
|    unordered_map<T, int> freq;                                              |
|    for (auto x : collection) freq[x]++;                                     |
|                                                                             |
| 2. COMPLEMENT LOOKUP (Two Sum)                                              |
|    complement = target - nums[i];                                           |
|    if (map.count(complement)) return {map[complement], i};                  |
|    map[nums[i]] = i;                                                        |
|                                                                             |
| 3. ANAGRAM GROUPING                                                         |
|    string key = word; sort(key.begin(), key.end());                         |
|    groups[key].push_back(word);                                             |
|                                                                             |
| 4. CONSECUTIVE SEQUENCE                                                     |
|    if (!set.count(num - 1)) { /* start of sequence */ }                     |
|    while (set.count(num + 1)) num++;                                        |
|                                                                             |
| 5. STATE ENCODING                                                           |
|    string state = "r" + to_string(row) + digit;                             |
|    if (seen.count(state)) return false;                                     |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                         COMMON MISTAKES & FIXES                             |
+-----------------------------------------------------------------------------+
|                                                                             |
|  MISTAKE 1: Using same element twice in Two Sum                             |
|    FIX: Check for complement BEFORE inserting current element               |
|                                                                             |
|  MISTAKE 2: Not handling duplicates in 3Sum/4Sum                            |
|    FIX: Sort array and skip duplicates explicitly                           |
|                                                                             |
|  MISTAKE 3: Counting every sequence in Longest Consecutive                  |
|    FIX: Only start counting if (num - 1) not in set                         |
|                                                                             |
|  MISTAKE 4: Using map when set is sufficient                                |
|    FIX: If only checking existence, use set not map                         |
|                                                                             |
|  MISTAKE 5: Not removing from set in sliding window                         |
|    FIX: When window exceeds size k, erase nums[i-k]                         |
|                                                                             |
|  MISTAKE 6: Forgetting to update map in LRU after move                      |
|    FIX: After moving to front, update map[key] = cache.begin()              |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                       GOLDEN RULES - MEMORIZE!                              |
+-----------------------------------------------------------------------------+
|                                                                             |
|  1⃣  Hashmap/Set operations are O(1) average                                |
|                                                                             |
|  2⃣  Two Sum: Check complement BEFORE inserting                             |
|                                                                             |
|  3⃣  Anagrams: Use sorted string or frequency as key                        |
|                                                                             |
|  4⃣  Longest Consecutive: Only count from sequence start                    |
|                                                                             |
|  5⃣  4Sum II: Split into two groups (A+B) = -(C+D)                          |
|                                                                             |
|  6⃣  Top K: Bucket sort is O(N), heap is O(N log K)                         |
|                                                                             |
|  7⃣  LRU Cache: Hashmap + Doubly Linked List                                |
|                                                                             |
|  8⃣  State Encoding: Creative strings as keys for complex state             |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                        INTERVIEW CHEAT CODES                                |
+-----------------------------------------------------------------------------+
|                                                                             |
|   "I'll use a hashmap to achieve O(1) lookup instead of O(N) search."       |
|                                                                             |
|   "For Two Sum, I'll store each number and check if the complement          |
|      exists before inserting the current number."                           |
|                                                                             |
|   "To group anagrams, I'll use the sorted string as a canonical key."       |
|                                                                             |
|   "For Longest Consecutive Sequence, I'll only start counting when          |
|      num-1 doesn't exist, making it O(N) not O(N2)."                        |
|                                                                             |
|   "For LRU Cache, I need O(1) access and O(1) eviction, so I'll             |
|      combine a hashmap with a doubly linked list."                          |
|                                                                             |
|   "I'll encode the state as a string to elegantly track multiple            |
|      constraints with a single set."                                        |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                    COMPLEXITY QUICK REFERENCE                               |
+-----------------------------------------------------------------------------+
|                                                                             |
| Hashmap Insert/Lookup/Delete: O(1) average                                  |
| Frequency Counting: O(N) time, O(N) space                                   |
| Two Sum: O(N) time, O(N) space                                              |
| Group Anagrams: O(N * K log K) time, O(N * K) space                         |
| Longest Consecutive: O(N) time, O(N) space                                  |
| Top K Frequent (bucket): O(N) time, O(N) space                              |
| Top K Frequent (heap): O(N log K) time, O(N) space                          |
| Valid Sudoku: O(1) time (fixed 9x9), O(1) space                             |
| LRU Cache get/put: O(1) time, O(capacity) space                             |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
                        **PROBLEM LIST**                                       
===============================================================================
```

FUNDAMENTAL (Must Know):
Y 1.   Two Sum  MOST ASKED
Y 217. Contains Duplicate
Y 242. Valid Anagram
Y 387. First Unique Character

**FREQUENCY COUNTING:**
Y 1365. How Many Numbers Smaller Than Current
Y 347.  Top K Frequent Elements 
Y 451.  Sort Characters By Frequency

**PAIR/COMPLEMENT LOOKUP:**
Y 1.   Two Sum  (Hashmap approach)
> 15.  3Sum (See Two Pointers.txt - better with two pointers)
Y 454. 4Sum II  (Brilliant split optimization)

**ANAGRAM DETECTION:**
Y 242. Valid Anagram
Y 49.  Group Anagrams 
> 438. Find All Anagrams (See Sliding Window.txt - fixed window)

**SET OPERATIONS:**
Y 217. Contains Duplicate
Y 219. Contains Duplicate II
Y 128. Longest Consecutive Sequence 
Y 349. Intersection of Two Arrays

**STATE ENCODING:**
Y 36.  Valid Sudoku 

**DESIGN PROBLEMS:**
Y 146. LRU Cache  HARD
Y 380. Insert Delete GetRandom O(1)

RELATED (Advanced):
- 705. Design HashSet
- 706. Design HashMap
- 981. Time Based Key-Value Store
- 895. Maximum Frequency Stack

## END
