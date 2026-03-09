# **SLIDING WINDOW - COMPLETE GUIDE**

Transforms O(N2) problems into O(N) by maintaining a dynamic range!

### **TABLE OF CONTENTS**

PART 1: Core Templates (6 Templates)
- Template 1: Shrinkable (while)
- Template 2: Non-Shrinkable (if)
- Template 3: Counting Subarrays
- Template 4: "Exactly K" Transformation
- Template 5: Fixed-Size Window
- Template 6: Dual Windows

PART 2: Template Selection Guide
PART 3: How to Identify & Approach Problems
PART 4: Key Problems with Solutions
PART 5: When NOT to Use Sliding Window
PART 6: Quick Revision Table
PART 7: Advanced Patterns (NEW!)
- Circular Array Sliding Window
- Inverse/Complement Problems
- Sorting + Sliding Window
- Sliding Window + Heap
PART 8: Complete Problem List (by Pattern)

## **PART 1: CORE TEMPLATES**

### **TEMPLATE 1: SHRINKABLE (Variable Window - Find Min/Max or Count ALL)**

 **MEMORY AID**: "**W**hile shrinks the **W**indow" (use **W**HILE loop)

USE WHEN: Need to count ALL valid subarrays OR find minimum window

```
int left = 0, ans = 0;

for (int right = 0; right < n; right++) {
addToWindow(arr[right]);                               

while (isInvalid()) {              //  MUST be while   
    removeFromWindow(arr[left++]);                     
}                                                      

ans = max(ans, right - left + 1);  // For max length   
// OR                                                  
// ans = min(ans, right - left + 1);  // For min length

}

return ans;
```

KEY: Window is ALWAYS valid after while loop

**PRACTICE PROBLEMS:**
- 3.    Longest Substring Without Repeating Characters
- 209.  Minimum Size Subarray Sum
- 904.  Fruit Into Baskets
- 1004. Max Consecutive Ones III
- 1493. Longest Subarray of 1's After Deleting One Element

### **LC 3: Longest Substring Without Repeating Characters**

PROBLEM: Find longest substring with all unique characters.

KEY INSIGHT: Window invalid when freq[char] > 1. Shrink until all unique.

```
int lengthOfLongestSubstring(string s) {
int freq[128] = {};                                              
int left = 0, maxLen = 0;                                        

for (int right = 0; right < s.size(); right++) {                 
    freq[s[right]]++;                                            

    while (freq[s[right]] > 1) {      // Invalid: duplicate found
        freq[s[left]]--;                                         
        left++;                                                  
    }                                                            

    maxLen = max(maxLen, right - left + 1);                      
}                                                                
return maxLen;                                                   

}
```

WHY TEMPLATE 1: Need exact max length, shrink until valid (no duplicates).
TIME: O(N)  |  SPACE: O(128) = O(1)

### **LC 209: Minimum Size Subarray Sum**

PROBLEM: Find minimum length subarray with sum >= target.

KEY INSIGHT: Window VALID when sum >= target. Shrink while valid to find min!

```cpp
int minSubArrayLen(int target, vector<int>& nums) {
int left = 0, sum = 0;                                         
int minLen = INT_MAX;                                          

for (int right = 0; right < nums.size(); right++) {            
    sum += nums[right];                                        

    while (sum >= target) {           // VALID! Try to minimize
        minLen = min(minLen, right - left + 1);                
        sum -= nums[left];                                     
        left++;                                                
    }                                                          
}                                                              
return minLen == INT_MAX ? 0 : minLen;                         

}
```

WHY TEMPLATE 1: Finding MINIMUM window, shrink while VALID (opposite logic!).
TIME: O(N)  |  SPACE: O(1)

### **LC 904: Fruit Into Baskets**

PROBLEM: Max fruits you can pick with only 2 baskets (2 types max).

KEY INSIGHT: Longest subarray with at most 2 distinct elements.

```cpp
int totalFruit(vector<int>& fruits) {
unordered_map<int, int> freq;                                      
int left = 0, maxLen = 0;                                          

for (int right = 0; right < fruits.size(); right++) {              
    freq[fruits[right]]++;                                         

    while (freq.size() > 2) {         // Invalid: more than 2 types
        freq[fruits[left]]--;                                      
        if (freq[fruits[left]] == 0) freq.erase(fruits[left]);     
        left++;                                                    
    }                                                              

    maxLen = max(maxLen, right - left + 1);                        
}                                                                  
return maxLen;                                                     

}
```

WHY TEMPLATE 1: Max length with constraint (<2 types), shrink when invalid.
TIME: O(N)  |  SPACE: O(1) - at most 3 entries in map

### **LC 1004: Max Consecutive Ones III**

PROBLEM: Max consecutive 1s if you can flip at most k zeros.

KEY INSIGHT: Longest subarray with at most k zeros.

```cpp
int longestOnes(vector<int>& nums, int k) {
int left = 0, zeros = 0, maxLen = 0;                            

for (int right = 0; right < nums.size(); right++) {             
    if (nums[right] == 0) zeros++;                              

    while (zeros > k) {               // Invalid: too many zeros
        if (nums[left] == 0) zeros--;                           
        left++;                                                 
    }                                                           

    maxLen = max(maxLen, right - left + 1);                     
}                                                               
return maxLen;                                                  

}
```

WHY TEMPLATE 1: Max length with constraint (<k zeros), shrink when invalid.
TIME: O(N)  |  SPACE: O(1)

### **LC 1493: Longest Subarray of 1's After Deleting One Element**

PROBLEM: Max consecutive 1s after deleting exactly one element.

KEY INSIGHT: Same as LC 1004 with k=1, but MUST delete one element.
```cpp
Answer = maxLen - 1 (or maxLen if entire array is result)

int longestSubarray(vector<int>& nums) {
int left = 0, zeros = 0, maxLen = 0;                           

for (int right = 0; right < nums.size(); right++) {            
    if (nums[right] == 0) zeros++;                             

    while (zeros > 1) {               // At most 1 zero allowed
        if (nums[left] == 0) zeros--;                          
        left++;                                                
    }                                                          

    maxLen = max(maxLen, right - left + 1);                    
}                                                              

return maxLen - 1;  // Must delete one element!                

}
```

WHY TEMPLATE 1: Same as 1004 with k=1. Subtract 1 because deletion required.
TIME: O(N)  |  SPACE: O(1)

### **TEMPLATE 2: NON-SHRINKABLE (Find Max Length ONLY)**

 **MEMORY AID**: "**IF** max only, keep **I**ncreasing **F**orward"

USE WHEN: ONLY need maximum window size (cleaner code)

```
int left = 0;

for (int right = 0; right < n; right++) {
addToWindow(arr[right]);                               

if (isInvalid()) {                //  Use if, not while
    removeFromWindow(arr[left++]);                     
}                                                      

}

return right - left;  // Final window size = answer
```

KEY: Window size is monotonic (never decreases)

**PRACTICE PROBLEMS:**
- 424.  Longest Repeating Character Replacement
- 1838. Frequency of the Most Frequent Element
- 2024. Maximize the Confusion of an Exam

### **LC 424: Longest Repeating Character Replacement**

PROBLEM: Longest substring with same letter after at most k replacements.

KEY INSIGHT: Window valid if (window_size - maxFreq) <= k
We can replace all non-majority chars with majority char.
Track maxFreq - no need to decrease it (we want MAX length)!

```
int characterReplacement(string s, int k) {
int freq[26] = {};                                                    
int left = 0, maxFreq = 0, maxLen = 0;                                

for (int right = 0; right < s.size(); right++) {                      
    freq[s[right] - 'A']++;                                           
    maxFreq = max(maxFreq, freq[s[right] - 'A']);                     

    // Window size - maxFreq = chars to replace                       
    if (right - left + 1 - maxFreq > k) {  // Invalid                 
        freq[s[left] - 'A']--;                                        
        left++;                                                       
        // Note: DON'T decrease maxFreq! We only care about max length
    }                                                                 

    maxLen = max(maxLen, right - left + 1);                           
}                                                                     
return maxLen;                                                        

}
```

WHY TEMPLATE 2: Only need MAX length. maxFreq never needs to decrease
because smaller window can't give better answer anyway!
TIME: O(N)  |  SPACE: O(26) = O(1)

### **LC 1838: Frequency of the Most Frequent Element**

PROBLEM: Max frequency achievable by incrementing elements (total ops < k).

KEY INSIGHT: Sort array. For window ending at right, cost to make all
elements equal to nums[right] = nums[right]*windowSize - sum.
Window valid if cost <= k.

```cpp
int maxFrequency(vector<int>& nums, int k) {
sort(nums.begin(), nums.end());                               

long left = 0, sum = 0, maxLen = 0;                           

for (int right = 0; right < nums.size(); right++) {           
    sum += nums[right];                                       

    // Cost = target * windowSize - sum                       
    // target = nums[right], windowSize = right - left + 1    
    while ((long)nums[right] * (right - left + 1) - sum > k) {
        sum -= nums[left];                                    
        left++;                                               
    }                                                         

    maxLen = max(maxLen, right - left + 1);                   
}                                                             
return maxLen;                                                

}
```

WHY SORTED: After sorting, all elements in window can only increase to
reach nums[right] (the maximum in window).
TIME: O(N log N)  |  SPACE: O(1)

### **LC 2024: Maximize the Confusion of an Exam**

PROBLEM: Max consecutive same answers after at most k changes.

KEY INSIGHT: Same as LC 424! Run twice - once for 'T', once for 'F'.
Or: Track both counts, window invalid if min(countT, countF) > k.

```cpp
int maxConsecutiveAnswers(string answerKey, int k) {
// Helper: max consecutive 'target' with at most k flips    
auto maxConsec = [&](char target) {                         
    int left = 0, flips = 0, maxLen = 0;                    
    for (int right = 0; right < answerKey.size(); right++) {
        if (answerKey[right] != target) flips++;            

        while (flips > k) {                                 
            if (answerKey[left] != target) flips--;         
            left++;                                         
        }                                                   
        maxLen = max(maxLen, right - left + 1);             
    }                                                       
    return maxLen;                                          
};                                                          

return max(maxConsec('T'), maxConsec('F'));                 

}

// Alternative: Single pass (track min of both counts)
int maxConsecutiveAnswers_v2(string answerKey, int k) {
int left = 0, countT = 0, countF = 0, maxLen = 0;                 

for (int right = 0; right < answerKey.size(); right++) {          
    if (answerKey[right] == 'T') countT++;                        
    else countF++;                                                

    while (min(countT, countF) > k) {  // Need to flip more than k
        if (answerKey[left] == 'T') countT--;                     
        else countF--;                                            
        left++;                                                   
    }                                                             
    maxLen = max(maxLen, right - left + 1);                       
}                                                                 
return maxLen;                                                    

}
```

WHY TEMPLATE 1/2: Max length with constraint. Either approach works.
TIME: O(N)  |  SPACE: O(1)

### **TEMPLATE 3: COUNTING SUBARRAYS**

USE WHEN: Count ALL subarrays satisfying condition

```
int left = 0, count = 0;

for (int right = 0; right < n; right++) {
addToWindow(arr[right]);                                    

while (isInvalid()) {                                       
    removeFromWindow(arr[left++]);                          
}                                                           

count += right - left + 1;  // All subarrays ending at right

}

return count;
```

WHY (right - left + 1)?
If [left, right] is valid, these are ALL valid subarrays ending at right:
```
[left, right], [left+1, right], ..., [right, right]
Count = right - left + 1                           
```

**PRACTICE PROBLEMS:**
- 713.  Subarray Product Less Than K
- 1358. Number of Substrings Containing All Three Characters
- 2302. Count Subarrays With Score Less Than K

### **LC 713: Subarray Product Less Than K**

PROBLEM: Count subarrays where product of all elements < k.

KEY INSIGHT: Multiply when expanding, divide when shrinking.
All subarrays ending at right = (right - left + 1).

```cpp
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
if (k <= 1) return 0;  // Edge case: product can't be < 1 with positive nums

int left = 0, count = 0;                                                    
long product = 1;                                                           

for (int right = 0; right < nums.size(); right++) {                         
    product *= nums[right];                                                 

    while (product >= k) {            // Invalid: product too large         
        product /= nums[left];                                              
        left++;                                                             
    }                                                                       

    count += right - left + 1;        // All valid subarrays ending at right
}                                                                           
return count;                                                               

}
```

WHY TEMPLATE 3: Count ALL valid subarrays. Each position contributes
(right - left + 1) new subarrays ending there.
TIME: O(N)  |  SPACE: O(1)

### **LC 1358: Number of Substrings Containing All Three Characters**

PROBLEM: Count substrings containing at least one 'a', 'b', and 'c'.

KEY INSIGHT: Once window has all three, ALL extensions to right are valid!
```
Count = left + 1 (all starting positions from 0 to left).
```

Shrink while VALID to find minimum left for each right.

```
int numberOfSubstrings(string s) {
int freq[3] = {};                                                            
int left = 0, count = 0;                                                     

for (int right = 0; right < s.size(); right++) {                             
    freq[s[right] - 'a']++;                                                  

    // Shrink while window is VALID (has all three)                          
    while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) {                      
        freq[s[left] - 'a']--;                                               
        left++;                                                              
    }                                                                        

    // All substrings starting from [0..left-1] and ending at right are valid
    count += left;                                                           
}                                                                            
return count;                                                                

}
```

WHY THIS COUNTING: After shrinking, window [left, right] is INVALID (missing one).
So window [left-1, right] was last valid > all [0..left-1] starting points work.
TIME: O(N)  |  SPACE: O(1)

### **LC 2302: Count Subarrays With Score Less Than K**

PROBLEM: Count subarrays where (sum * length) < k.

KEY INSIGHT: Score = sum * (right - left + 1). Shrink when score >= k.

```cpp
long long countSubarrays(vector<int>& nums, long long k) {
int left = 0;                                                               
long long sum = 0, count = 0;                                               

for (int right = 0; right < nums.size(); right++) {                         
    sum += nums[right];                                                     

    while (sum * (right - left + 1) >= k) {  // Invalid: score too large    
        sum -= nums[left];                                                  
        left++;                                                             
    }                                                                       

    count += right - left + 1;        // All valid subarrays ending at right
}                                                                           
return count;                                                               

}
```

WHY TEMPLATE 3: Count subarrays with condition. Positive numbers ensure
monotonicity (larger window = larger score).
TIME: O(N)  |  SPACE: O(1)

### **TEMPLATE 4: "EXACTLY K" TRANSFORMATION** 

 **MEMORY AID**: "Exact = Almost - Almost Less"
> **exactly(K) = atMost(K) - atMost(K-1)**

USE WHEN: Problem asks for "exactly K" (hard to do directly)

FORMULA: exactly(K) = atMost(K) - atMost(K-1)

```cpp
int atMost(vector<int>& arr, int k) {
if (k < 0) return 0;  // CRITICAL edge case!      

    int left = 0, count = 0;                      
// ... state variables                            

for (int right = 0; right < arr.size(); right++) {
    // add arr[right] to window                   

    while (condition > k) {                       
        // remove arr[left] from window           
    left++;                                       
}                                                 

        count += right - left + 1;                

}

return count;
}

int exactlyK(vector<int>& arr, int k) {
return atMost(arr, k) - atMost(arr, k - 1);

}
```

**PRACTICE PROBLEMS:**
- 930.  Binary Subarrays With Sum
- 992.  Subarrays with K Different Integers 
- 1248. Count Number of Nice Subarrays
- 2062. Count Vowel Substrings of a String

### **LC 930: Binary Subarrays With Sum**

PROBLEM: Count subarrays with sum exactly equal to goal.

KEY INSIGHT: exactly(goal) = atMost(goal) - atMost(goal - 1)

```cpp
int numSubarraysWithSum(vector<int>& nums, int goal) {
return atMost(nums, goal) - atMost(nums, goal - 1);

}

int atMost(vector<int>& nums, int goal) {
if (goal < 0) return 0;                            

int left = 0, sum = 0, count = 0;                  

for (int right = 0; right < nums.size(); right++) {
    sum += nums[right];                            

    while (sum > goal) {                           
        sum -= nums[left];                         
        left++;                                    
    }                                              

    count += right - left + 1;                     
}                                                  
return count;                                      

}
```

WHY TEMPLATE 4: "Exactly K" is hard directly. Use atMost trick!
TIME: O(N)  |  SPACE: O(1)

### **LC 992: Subarrays with K Different Integers**  IMPORTANT

PROBLEM: Count subarrays with exactly k distinct integers.

KEY INSIGHT: exactly(k) = atMost(k) - atMost(k - 1)

```cpp
int subarraysWithKDistinct(vector<int>& nums, int k) {
return atMost(nums, k) - atMost(nums, k - 1);

}

int atMost(vector<int>& nums, int k) {
if (k < 0) return 0;                                         

unordered_map<int, int> freq;                                
int left = 0, count = 0;                                     

for (int right = 0; right < nums.size(); right++) {          
    freq[nums[right]]++;                                     

    while (freq.size() > k) {         // More than k distinct
        freq[nums[left]]--;                                  
        if (freq[nums[left]] == 0) freq.erase(nums[left]);   
        left++;                                              
    }                                                        

    count += right - left + 1;                               
}                                                            
return count;                                                

}
```

WHY TEMPLATE 4: Classic "exactly K" problem. Can't do directly because
adding element might keep same distinct count (if already present).
TIME: O(N)  |  SPACE: O(K)

### **LC 1248: Count Number of Nice Subarrays**

PROBLEM: Count subarrays with exactly k odd numbers.

KEY INSIGHT: Transform odd>1, even>0. Now it's "subarrays with sum = k".
```cpp
exactly(k) = atMost(k) - atMost(k - 1)

int numberOfSubarrays(vector<int>& nums, int k) {
return atMost(nums, k) - atMost(nums, k - 1);

}

int atMost(vector<int>& nums, int k) {
if (k < 0) return 0;                                       

int left = 0, odds = 0, count = 0;                         

for (int right = 0; right < nums.size(); right++) {        
    if (nums[right] % 2 == 1) odds++;  // Count odd numbers

    while (odds > k) {                                     
        if (nums[left] % 2 == 1) odds--;                   
        left++;                                            
    }                                                      

    count += right - left + 1;                             
}                                                          
return count;                                              

}
```

WHY TEMPLATE 4: "Exactly k odds" = "Exactly k sum" after transformation.
TIME: O(N)  |  SPACE: O(1)

### **LC 2062: Count Vowel Substrings of a String**

PROBLEM: Count substrings with ALL 5 vowels and ONLY vowels.

KEY INSIGHT: exactly(5 vowels) = atMost(5) - atMost(4)
But also need "only vowels" constraint!

```cpp
int countVowelSubstrings(string word) {
return atMost(word, 5) - atMost(word, 4);

}

int atMost(string& word, int k) {
if (k < 0) return 0;                                                   

string vowels = "aeiou";                                               
auto isVowel = [&](char c) {                                           
    return vowels.find(c) != string::npos;                             
};                                                                     

unordered_map<char, int> freq;                                         
int left = 0, count = 0;                                               

for (int right = 0; right < word.size(); right++) {                    
    if (!isVowel(word[right])) {      // Reset: consonant breaks window
        freq.clear();                                                  
        left = right + 1;                                              
        continue;                                                      
    }                                                                  

    freq[word[right]]++;                                               

    while (freq.size() > k) {         // More than k distinct vowels   
        freq[word[left]]--;                                            
        if (freq[word[left]] == 0) freq.erase(word[left]);             
        left++;                                                        
    }                                                                  

    count += right - left + 1;                                         
}                                                                      
return count;                                                          

}
```

WHY TEMPLATE 4: "Exactly 5 distinct vowels" with added constraint.
Consonant acts as barrier - reset window completely.
TIME: O(N)  |  SPACE: O(5) = O(1)

### **TEMPLATE 5: FIXED-SIZE WINDOW** 

USE WHEN: Window size k is FIXED/given

APPROACH: Add right element, remove left element when window exceeds size k

```
// Basic Template
int windowSum = 0, maxSum = 0;

// Build initial window of size k
for (int i = 0; i < k; i++) {
windowSum += arr[i];

}
maxSum = windowSum;

// Slide window
for (int i = k; i < n; i++) {
windowSum += arr[i] - arr[i - k];  // Add right, remove left
maxSum = max(maxSum, windowSum);

}

return maxSum;
```

**KEY INSIGHT:**
- Window always has exactly k elements
- Add arr[right], remove arr[right - k] simultaneously
- No while loop needed - just maintain size k

## **SOLVED: Maximum Average Subarray I (LC 643)**

PROBLEM: Find contiguous subarray of length k with maximum average.

```cpp
double findMaxAverage(vector<int>& nums, int k) {
double sum = 0;                        

// Initial window                      
for (int i = 0; i < k; i++) {          
    sum += nums[i];                    
}                                      

double maxSum = sum;                   

// Slide window                        
for (int i = k; i < nums.size(); i++) {
    sum += nums[i] - nums[i - k];      
    maxSum = max(maxSum, sum);         
}                                      

return maxSum / k;                     

}
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED: Maximum Sum of Distinct Subarrays With Length K (LC 2461)**

PROBLEM: Find max sum of subarray of length k with ALL DISTINCT elements.

```cpp
long long maximumSubarraySum(vector<int>& nums, int k) {
unordered_map<int, int> freq;                   
long long sum = 0, maxSum = 0;                  

for (int i = 0; i < nums.size(); i++) {         
    // Add right element                        
    sum += nums[i];                             
    freq[nums[i]]++;                            

    // Remove left element when window exceeds k
    if (i >= k) {                               
        sum -= nums[i - k];                     
        freq[nums[i - k]]--;                    
        if (freq[nums[i - k]] == 0) {           
            freq.erase(nums[i - k]);            
        }                                       
    }                                           

    // Check if window is valid (all distinct)  
    if (i >= k - 1 && freq.size() == k) {       
        maxSum = max(maxSum, sum);              
    }                                           
}                                               

return maxSum;                                  

}

class Solution {
```

public:
```
long long maximumSubarraySum(vector<int>& nums, int k) {       
    unordered_map<int, int> freq;                              
    long long sum = 0, maxSum = 0;                             
    int left = 0;                                              

    for (int right = 0; right < nums.size(); right++) {        
        // Add right element                                   
        sum += nums[right];                                    
        freq[nums[right]]++;                                   

        // Shrink window when size exceeds k                   
        while (right - left + 1 > k) {                         
            sum -= nums[left];                                 
            freq[nums[left]]--;                                
            if (freq[nums[left]] == 0) {                       
                freq.erase(nums[left]);                        
            }                                                  
            left++;                                            
        }                                                      

        // Check if window is valid (size = k AND all distinct)
        if (right - left + 1 == k && freq.size() == k) {       
            maxSum = max(maxSum, sum);                         
        }                                                      
    }                                                          

    return maxSum;                                             
}                                                              
```

```
};
```

TIME: O(N)  |  SPACE: O(K)

## **SOLVED: Contains Duplicate II (LC 219)**

PROBLEM: Check if duplicate exists within distance k.

```cpp
bool containsNearbyDuplicate(vector<int>& nums, int k) {
unordered_set<int> window;             

for (int i = 0; i < nums.size(); i++) {
    // Remove element outside window   
    if (i > k) {                       
        window.erase(nums[i - k - 1]); 
    }                                  

    // Check for duplicate             
    if (window.count(nums[i])) {       
        return true;                   
    }                                  

    window.insert(nums[i]);            
}                                      

return false;                          

}
```

TIME: O(N)  |  SPACE: O(K)

### PRACTICE PROBLEMS - Fixed-Size Window:

- 643.  Maximum Average Subarray I
- 1004. Max Consecutive Ones III
- 2461. Maximum Sum of Distinct Subarrays With Length K
- 219.  Contains Duplicate II
- 1493. Longest Subarray of 1's After Deleting One Element
- 2090. K Radius Subarray Averages
- 1423. Maximum Points You Can Obtain from Cards

### **TEMPLATE 6: DUAL WINDOWS (Two Simultaneous Windows)** 

**USE WHEN:**
- Two separate windows track different conditions
- Need to count by difference: exactly(K) = atMost(K) - atMost(K-1)
- Problem requires tracking multiple states simultaneously

APPROACH: Maintain two window states in parallel OR use the atMost trick

## **SOLVED: Substring With Concatenation of All Words (LC 30)**  HARD

PROBLEM: Find all starting indices where substring is concatenation of all words.

```cpp
vector<int> findSubstring(string s, vector<string>& words) {
vector<int> result;                                                             
if (words.empty() || s.empty()) return result;                                  

int wordLen = words[0].size();                                                  
int totalLen = wordLen * words.size();                                          

if (s.size() < totalLen) return result;                                         

unordered_map<string, int> wordCount;                                           
for (const string& word : words) {                                              
    wordCount[word]++;                                                          
}                                                                               

// Try each starting offset (0 to wordLen-1)                                    
for (int offset = 0; offset < wordLen; offset++) {                              
    unordered_map<string, int> window;                                          
    int matched = 0;                                                            
    int left = offset;                                                          

    for (int right = offset; right + wordLen <= s.size(); right += wordLen) {   
        string word = s.substr(right, wordLen);                                 

        if (wordCount.count(word)) {                                            
            window[word]++;                                                     
            if (window[word] == wordCount[word]) matched++;                     
            else if (window[word] == wordCount[word] + 1) matched--;            

            // Shrink if window too large                                       
            while (right - left + wordLen > totalLen) {                         
                string leftWord = s.substr(left, wordLen);                      
                if (window[leftWord] == wordCount[leftWord]) matched--;         
                else if (window[leftWord] == wordCount[leftWord] + 1) matched++;
                window[leftWord]--;                                             
                left += wordLen;                                                
            }                                                                   

            if (matched == wordCount.size()) {                                  
                result.push_back(left);                                         
            }                                                                   
        } else {                                                                
            // Reset window                                                     
            window.clear();                                                     
            matched = 0;                                                        
            left = right + wordLen;                                             
        }                                                                       
    }                                                                           
}                                                                               

return result;                                                                  

}
```

TIME: O(N * wordLen)  |  SPACE: O(words.size())

## **SOLVED: Longest Nice Subarray (LC 2401)**

PROBLEM: Find longest subarray where AND of any two elements is 0.

```cpp
int longestNiceSubarray(vector<int>& nums) {
int left = 0, usedBits = 0, maxLen = 0;            

for (int right = 0; right < nums.size(); right++) {
    // Shrink while there's bit conflict           
    while (usedBits & nums[right]) {               
        usedBits ^= nums[left];  // Remove bits    
        left++;                                    
    }                                              

    usedBits |= nums[right];  // Add bits          
    maxLen = max(maxLen, right - left + 1);        
}                                                  

return maxLen;                                     

}
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED: Substring With Largest Variance (LC 2272)**  HARD

PROBLEM: Max difference between frequency of any two chars in any substring.

APPROACH: For each pair (a, b), find max(freq_a - freq_b) using Kadane's variant.

```
int largestVariance(string s) {
int maxVariance = 0;                                            

// Try all pairs of characters                                  
for (char a = 'a'; a <= 'z'; a++) {                             
    for (char b = 'a'; b <= 'z'; b++) {                         
        if (a == b) continue;                                   

        int countA = 0, countB = 0;                             
        bool hasB = false;                                      

        for (char c : s) {                                      
            if (c == a) countA++;                               
            if (c == b) {                                       
                countB++;                                       
                hasB = true;                                    
            }                                                   

            if (countB > countA) {                              
                countA = 0;                                     
                countB = 0;                                     
                hasB = false;                                   
            }                                                   

            if (hasB) {                                         
                maxVariance = max(maxVariance, countA - countB);
            }                                                   
        }                                                       
    }                                                           
}                                                               

return maxVariance;                                             

}
```

TIME: O(26 * 26 * N)  |  SPACE: O(1)

### PRACTICE PROBLEMS - Dual Windows:

- 30.   Substring With Concatenation of All Words 
- 2401. Longest Nice Subarray
- 2272. Substring With Largest Variance 
- 1358. Number of Substrings Containing All Three Characters
- 2953. Count Complete Substrings

## **PART 2: WHEN TO USE WHICH TEMPLATE**

```
+-----------------------------------------------------------------------------+
| Problem Type              | Template              | Key Pattern             |
+---------------------------+-----------------------+-------------------------+
| Count ALL subarrays       | Shrinkable (while)    | count += j-i+1          |
| Find MINIMUM window       | Shrinkable (while)    | min(ans, len)           |
| Find MAXIMUM length       | Non-shrinkable (if)   | return j-i              |
| "Exactly K" problem       | atMost(K) - (K-1)     | Two helper calls        |
| Window size k (fixed)     | Fixed-Size            | Add right, remove left  |
| Two conditions tracking   | Dual Windows          | Multiple states         |
| Sum=K with NEGATIVES      | > See Prefix Sum.txt  | SW doesn't work here!   |
+---------------------------+-----------------------+-------------------------+

+-----------------------------------------------------------------------------+
|                     SHRINKABLE vs NON-SHRINKABLE                            |
+-------------------------+-----------------------+---------------------------+
| Aspect                  | Shrinkable (while)    | Non-Shrinkable (if)       |
+-------------------------+-----------------------+---------------------------+
| Use for counting        |  YES (REQUIRED)     |  NO (wrong results)         |
| Use for minimum         |  YES (REQUIRED)     |  NO (wrong results)         |
| Use for maximum         |  YES (works)        |  YES (cleaner!)             |
| Window validity         | Always valid at end   | May be invalid            |
| Code simplicity         | Need extra variable   | Final window = answer     |
+-------------------------+-----------------------+---------------------------+

===============================================================================
          **PART 3: HOW TO IDENTIFY & APPROACH PROBLEMS**                      
===============================================================================
```

### ** RECOGNITION: WHEN TO USE SLIDING WINDOW?**

### STRONG SIGNALS (High Confidence):

 "Contiguous" subarray/substring
 "Longest/Shortest/Maximum/Minimum" length
 "At most K" / "At least K" / "Exactly K"
 Can define clear window validity condition
 Brute force would be O(N2) nested loops
 Fixed window size k given

**KEYWORDS TO WATCH FOR:**

- "consecutive" / "contiguous"
- "subarray" / "substring"
- "window" / "window size k"
- "without repeating"
- "at most K distinct"
- "flip at most K"
- "sum/product less than K"
- "maximum average"

### ** SYSTEMATIC APPROACH (Follow These Steps)**

### STEP 1: Identify the Pattern (30 seconds)

Ask yourself:
o Is it asking for contiguous subarray/substring?
o What are we optimizing? (max/min/count)
o What makes a window valid/invalid?
o Is it "at most", "at least", or "exactly"?
o Is window size fixed or variable?
o Are there negative numbers? (affects which template)

### STEP 2: Choose the Template (30 seconds)

Decision tree:
- Has NEGATIVE numbers + sum=K? > Use Prefix Sum.txt (not SW!)
- Fixed window size k? > Template 5 (Fixed-Size)
- "Exactly K" problem? > Template 4 (atMost trick)
- Count ALL valid subarrays? > Template 3 (Counting)
- Find MINIMUM window? > Template 1 (Shrinkable)
- Find MAXIMUM length? > Template 2 (Non-shrinkable)
- Two conditions tracking? > Template 6 (Dual Windows)

### STEP 3: Define the State (1 minute)

Determine:
o What variables track window properties?
o How to add element to window? (O(1) update)
o How to remove element from window? (O(1) update)
o How to check validity? (O(1) check)

Common states:
- Frequency: int cnt[128] = {} or unordered_map<int,int>
- Sum/Product: long sum = 0
- Distinct count: int distinct = 0
- Special: maxFreq, zeros count, etc.

### STEP 4: Implement (5 minutes)

Follow template:
1. Initialize: left = 0, state variables
2. Expand: for (right = 0 to n-1)
3. Update state: add arr[right]
4. Shrink: while/if (invalid)
5. Update answer
6. Return result

### STEP 5: Test Edge Cases (1 minute)

o Empty array
o Single element
o All same elements
o k = 0, k = 1, k >= n
o All valid or all invalid

### ** GOLDEN RULES - APPLY TO EVERY PROBLEM**

1. TEMPLATE SELECTION RULE
> Counting/Minimum: use while (shrinkable)
> Maximum only: use if (non-shrinkable)
> Fixed size: no while/if, just add/remove

2. WINDOW SIZE RULE
> Inclusive [i, j]: size = j - i + 1
> Never: size = j - i (unless exclusive right)

3. COUNTING RULE
> Add (j - i + 1) at each step, not window size

4. "EXACTLY K" RULE
> Transform to: atMost(K) - atMost(K-1)

5. NEGATIVE NUMBERS RULE
> SW won't work! Use Prefix Sum.txt instead

6. STATE UPDATE RULE
> Add: arr[j] (expand right)
> Remove: arr[i] (shrink left)
> Update BEFORE or AFTER moving pointer consistently

7. COMPLEXITY RULE
> Each element enters once, leaves once > O(2N) = O(N)

8. OVERFLOW RULE
> Use long for sum/product calculations

## **PART 4: KEY PROBLEMS WITH SOLUTIONS**

### **1. Longest Substring Without Repeating Characters (LC 3)**

 PATTERN: Variable-Size Window - Maximum length
 TEMPLATE: Shrinkable

```
int lengthOfLongestSubstring(string s) {
int left = 0, ans = 0;                          
int cnt[128] = {};                              

for (int right = 0; right < s.size(); right++) {
    cnt[s[right]]++;                            

    while (cnt[s[right]] > 1) {                 
        cnt[s[left]]--;                         
            left++;                             
        }                                       

        ans = max(ans, right - left + 1);       
    }                                           

    return ans;                                 
}                                               
```

TIME: O(N)  |  SPACE: O(1)

### **2. Minimum Window Substring (LC 76)**  HARD

 PATTERN: Frequency Map - Minimum window
 TEMPLATE: Shrinkable (shrink while VALID!)

```
string minWindow(string s, string t) {
if (t.empty() || s.empty()) return "";                    

unordered_map<char, int> required;                        
for (char c : t) required[c]++;                           

int left = 0, formed = 0;                                 
int minLen = INT_MAX, minLeft = 0;                        
unordered_map<char, int> window;                          

for (int right = 0; right < s.size(); right++) {          
    char c = s[right];                                    
    window[c]++;                                          

    if (required.count(c) && window[c] == required[c]) {  
        formed++;                                         
    }                                                     

    // Shrink while valid                                 
    while (formed == required.size()) {                   
        if (right - left + 1 < minLen) {                  
            minLen = right - left + 1;                    
            minLeft = left;                               
        }                                                 

        char leftChar = s[left];                          
        window[leftChar]--;                               
        if (required.count(leftChar) &&                   
            window[leftChar] < required[leftChar]) {      
            formed--;                                     
        }                                                 
            left++;                                       
        }                                                 
    }                                                     

return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);

}
```

TIME: O(|S| + |T|)  |  SPACE: O(|S| + |T|)

### **3. Longest Substring with At Most K Distinct Characters (LC 340)**

 PATTERN: At Most K Distinct
 TEMPLATE: Shrinkable

```
int lengthOfLongestSubstringKDistinct(string s, int k) {
unordered_map<char, int> freq;                      
    int left = 0, ans = 0;                          

    for (int right = 0; right < s.size(); right++) {
    freq[s[right]]++;                               

    while (freq.size() > k) {                       
        freq[s[left]]--;                            
        if (freq[s[left]] == 0) {                   
            freq.erase(s[left]);                    
        }                                           
            left++;                                 
        }                                           

        ans = max(ans, right - left + 1);           
    }                                               

    return ans;                                     
}                                                   
```

TIME: O(N)  |  SPACE: O(K)

### **4. Longest Repeating Character Replacement (LC 424)**

 PATTERN: Maximum length with K operations
 TEMPLATE: Shrinkable (can use non-shrinkable)

KEY: window_length - max_frequency < k

```
int characterReplacement(string s, int k) {
int left = 0, maxFreq = 0, ans = 0;                 
int freq[26] = {};                                  

    for (int right = 0; right < s.size(); right++) {
    freq[s[right] - 'A']++;                         
    maxFreq = max(maxFreq, freq[s[right] - 'A']);   

    while ((right - left + 1) - maxFreq > k) {      
        freq[s[left] - 'A']--;                      
        left++;                                     
    }                                               

        ans = max(ans, right - left + 1);           
    }                                               

    return ans;                                     
}                                                   
```

TIME: O(N)  |  SPACE: O(1)

### **5. Subarray Product Less Than K (LC 713)**

 PATTERN: Counting subarrays
 TEMPLATE: Counting (while + count += j-i+1)

```
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
if (k <= 1) return 0;                                      

    int left = 0, count = 0;                               
    long prod = 1;                                         

    for (int right = 0; right < nums.size(); right++) {    
        prod *= nums[right];                               

        while (prod >= k) {                                
            prod /= nums[left];                            
            left++;                                        
        }                                                  

        count += right - left + 1;                         
    }                                                      

    return count;                                          
}                                                          
```

TIME: O(N)  |  SPACE: O(1)

### **6. Subarrays with K Different Integers (LC 992)**  HARD

 PATTERN: Exactly K (using atMost transformation)
 TEMPLATE: exactly(K) = atMost(K) - atMost(K-1)

```cpp
int atMostK(vector<int>& nums, int k) {
if (k == 0) return 0;                                  

unordered_map<int, int> freq;                          
int left = 0, count = 0;                               

    for (int right = 0; right < nums.size(); right++) {
    freq[nums[right]]++;                               

    while (freq.size() > k) {                          
        freq[nums[left]]--;                            
        if (freq[nums[left]] == 0) {                   
            freq.erase(nums[left]);                    
        }                                              
            left++;                                    
        }                                              

    count += right - left + 1;                         
}                                                      

return count;                                          

}

int subarraysWithKDistinct(vector<int>& nums, int k) {
return atMostK(nums, k) - atMostK(nums, k - 1);

}
```

TIME: O(N)  |  SPACE: O(K)

### **7. Permutation in String (LC 567) / Find All Anagrams (LC 438)** 

 PATTERN: Fixed-Size + Frequency Map
 TEMPLATE: Fixed window with "matches" optimization

```
bool checkInclusion(string s1, string s2) {
if (s1.size() > s2.size()) return false;               

int cnt1[26] = {}, cnt2[26] = {};                      
for (char c : s1) cnt1[c - 'a']++;                     

int left = 0, matches = 0;                             

for (int right = 0; right < s2.size(); right++) {      
    int idx = s2[right] - 'a';                         
    cnt2[idx]++;                                       
    if (cnt2[idx] == cnt1[idx]) matches++;             
    else if (cnt2[idx] == cnt1[idx] + 1) matches--;    

    if (right >= s1.size()) {                          
        idx = s2[left] - 'a';                          
        if (cnt2[idx] == cnt1[idx]) matches--;         
        else if (cnt2[idx] == cnt1[idx] + 1) matches++;
        cnt2[idx]--;                                   
            left++;                                    
        }                                              

    if (matches == 26) return true;                    
}                                                      

return false;                                          

}
```

TIME: O(N)  |  SPACE: O(1)

### **8. Sliding Window Maximum (LC 239)**  HARD

 PATTERN: Fixed-Size + Monotonic Deque
 TEMPLATE: Deque stores indices in decreasing order of values

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
deque<int> dq;  // Store indices                      
vector<int> result;                                   

for (int i = 0; i < nums.size(); i++) {               
    // Remove indices outside window                  
    while (!dq.empty() && dq.front() <= i - k) {      
        dq.pop_front();                               
    }                                                 

    // Remove smaller elements (they're useless)      
    while (!dq.empty() && nums[dq.back()] < nums[i]) {
        dq.pop_back();                                
    }                                                 

    dq.push_back(i);                                  

    if (i >= k - 1) {                                 
        result.push_back(nums[dq.front()]);           
    }                                                 
}                                                     

return result;                                        

}
```

TIME: O(N)  |  SPACE: O(K)

### **9. Longest Subarray with Absolute Diff < Limit (LC 1438)**

 PATTERN: Two Monotonic Deques (max + min)
 TEMPLATE: Maintain both max and min efficiently

```cpp
int longestSubarray(vector<int>& nums, int limit) {
deque<int> maxQ, minQ;                                        
int left = 0, ans = 0;                                        

for (int right = 0; right < nums.size(); right++) {           
    // Maintain decreasing deque for max                      
    while (!maxQ.empty() && nums[maxQ.back()] < nums[right]) {
        maxQ.pop_back();                                      
    }                                                         
    maxQ.push_back(right);                                    

    // Maintain increasing deque for min                      
    while (!minQ.empty() && nums[minQ.back()] > nums[right]) {
        minQ.pop_back();                                      
    }                                                         
    minQ.push_back(right);                                    

    // Shrink if violated                                     
    while (nums[maxQ.front()] - nums[minQ.front()] > limit) { 
        if (maxQ.front() == left) maxQ.pop_front();           
        if (minQ.front() == left) minQ.pop_front();           
        left++;                                               
    }                                                         

    ans = max(ans, right - left + 1);                         
}                                                             

return ans;                                                   

}
```

TIME: O(N)  |  SPACE: O(N)

## **PART 5: WHEN SLIDING WINDOW DOES NOT WORK** 

### **DECISION CHECKLIST: CAN I USE SLIDING WINDOW?**

 YES - USE SLIDING WINDOW if ALL these are true:
o Contiguous subarray/substring
o Clear "valid window" condition
o Adding element: O(1) state update
o Removing element: O(1) state update
o Validity check: O(1)
o State is MONOTONIC (no negatives for sum problems)

 USE PREFIX SUM.txt INSTEAD if:
o Array has NEGATIVE numbers AND need sum=K
o Divisibility problems (sum % K)
o XOR subarray problems
o 2D matrix range queries

 USE MONOTONIC DEQUE (within SW) if:
o Need max AND min efficiently in window

 USE DIFFERENT ALGORITHM if:
o Non-contiguous subsequence
o Need exact median/mode
o Palindrome/symmetry checking

## **PART 6: QUICK REVISION TABLE**

```
+-----------------------------------------------------------------------------+
|                       GOLDEN RULES - MEMORIZE!                              |
+-----------------------------------------------------------------------------+
|                                                                             |
|  1⃣  Counting/Minimum > Shrinkable (while) - NON-NEGOTIABLE!                |
|  2⃣  Maximum length only > Non-shrinkable (if) - Cleaner!                   |
|  3⃣  Fixed size k > Add right, remove arr[i-k]                              |
|  4⃣  "Exactly K" = atMost(K) - atMost(K-1)                                  |
|  5⃣  Negatives + sum=K > Use Prefix Sum.txt (SW won't work!)                |
|  6⃣  Window [L,R] size = R - L + 1 (inclusive)                              |
|  7⃣  For counting: count += (j - i + 1) at each step                        |
|  8⃣  Time: O(N) because each element enters/leaves once                     |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                         STATE MANAGEMENT                                    |
+---------------------------+-------------------------------------------------+
| State Type                | Implementation                                  |
+---------------------------+-------------------------------------------------+
| Character frequency       | int cnt[128] = {};                              |
| Lowercase letters only    | int cnt[26] = {};                               |
| Distinct count            | unordered_map + check size()                    |
| Sum/Product               | long sum = 0; (Use long!)                       |
| Max/Min in window         | Monotonic deque                                 |
| Bit conflicts (AND)       | int usedBits = 0; (XOR/OR)                      |
+---------------------------+-------------------------------------------------+

===============================================================================
              **PART 7: ADVANCED PATTERNS**                                    
===============================================================================
```

### **PATTERN A: CIRCULAR ARRAY SLIDING WINDOW**

USE WHEN: Array wraps around (last element connects to first)

 **KEY INSIGHT**: Double the array OR use modulo indexing

### APPROACH 1: Double the array (simpler)

```
// For array of size n, create virtual array of size 2n
// Access arr[i % n] instead of duplicating
```

### APPROACH 2: Process twice

```
// First pass: normal sliding window
// Second pass: handle wrap-around cases
```

## **SOLVED: Defuse the Bomb (LC 1652)**

PROBLEM: Replace each element with sum of next/previous k elements (circular).

```cpp
vector<int> decrypt(vector<int>& code, int k) {
int n = code.size();                
vector<int> result(n, 0);           

if (k == 0) return result;          

int start = (k > 0) ? 1 : n + k;    
int end = (k > 0) ? k : n - 1;      

// Initial window sum               
int sum = 0;                        
for (int i = start; i <= end; i++) {
    sum += code[i % n];             
}                                   

// Slide window                     
for (int i = 0; i < n; i++) {       
    result[i] = sum;                
    sum -= code[start % n];         
    start++;                        
    end++;                          
    sum += code[end % n];           
}                                   

return result;                      

}
```

TIME: O(N)  |  SPACE: O(1) (excluding output)

## **SOLVED: Minimum Number of Flips to Make Binary String Alternating (LC 1888)**

PROBLEM: Type-1 (rotate) + Type-2 (flip) to make alternating.

 **KEY INSIGHT**: Rotate = Circular array! Double the string.

```
int minFlips(string s) {
int n = s.size();                                  
s += s;  // Double for circular                    

string alt1, alt2;                                 
for (int i = 0; i < s.size(); i++) {               
    alt1 += (i % 2 == 0) ? '0' : '1';  // 010101...
    alt2 += (i % 2 == 0) ? '1' : '0';  // 101010...
}                                                  

int diff1 = 0, diff2 = 0, minFlips = INT_MAX;      

for (int i = 0; i < s.size(); i++) {               
    // Add right element                           
    if (s[i] != alt1[i]) diff1++;                  
    if (s[i] != alt2[i]) diff2++;                  

    // Remove left element when window exceeds n   
    if (i >= n) {                                  
        if (s[i - n] != alt1[i - n]) diff1--;      
        if (s[i - n] != alt2[i - n]) diff2--;      
    }                                              

    // Check window of size n                      
    if (i >= n - 1) {                              
        minFlips = min({minFlips, diff1, diff2});  
    }                                              
}                                                  

return minFlips;                                   

}
```

TIME: O(N)  |  SPACE: O(N)

### PRACTICE PROBLEMS - Circular Array:

- 1652. Defuse the Bomb 
- 1888. Minimum Number of Flips to Make Binary String Alternating 
- 3208. Alternating Groups II 
- 1423. Maximum Points You Can Obtain from Cards

### **PATTERN B: INVERSE/COMPLEMENT PROBLEM**

USE WHEN: Remove from BOTH ends > Find longest MIDDLE subarray

 **KEY INSIGHT**:
"Remove elements from edges with sum X"
= "Find longest middle subarray with sum (total - X)"

## **SOLVED: Minimum Operations to Reduce X to Zero (LC 1658)**

PROBLEM: Remove from left/right ends to get sum = x. Find minimum operations.

 **TRANSFORMATION**: Find LONGEST middle subarray with sum = (total - x)

```cpp
int minOperations(vector<int>& nums, int x) {
int n = nums.size();                                
int total = accumulate(nums.begin(), nums.end(), 0);
int target = total - x;                             

if (target < 0) return -1;                          
if (target == 0) return n;  // Remove everything    

// Find longest subarray with sum = target          
int left = 0, sum = 0, maxLen = -1;                 

for (int right = 0; right < n; right++) {           
    sum += nums[right];                             

    while (sum > target) {                          
        sum -= nums[left++];                        
    }                                               

    if (sum == target) {                            
        maxLen = max(maxLen, right - left + 1);     
    }                                               
}                                                   

return maxLen == -1 ? -1 : n - maxLen;              

}
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED: Take K of Each Character From Left and Right (LC 2516)**

PROBLEM: Take chars from left/right such that at least k of each 'a','b','c'.

 **TRANSFORMATION**: Find LONGEST middle we can KEEP (has at most (count[c]-k) of each)

```
int takeCharacters(string s, int k) {
int n = s.size();                                                   
int total[3] = {};                                                  
for (char c : s) total[c - 'a']++;                                  

// Check if possible                                                
for (int i = 0; i < 3; i++) {                                       
    if (total[i] < k) return -1;                                    
}                                                                   

// Find longest middle to KEEP (can have at most total[c]-k of each)
int maxKeep = 0, left = 0;                                          
int window[3] = {};                                                 

for (int right = 0; right < n; right++) {                           
    window[s[right] - 'a']++;                                       

    // Shrink if any char exceeds allowed in middle                 
    while (window[0] > total[0] - k |                             |
           window[1] > total[1] - k |                             |
           window[2] > total[2] - k) {                              
        window[s[left] - 'a']--;                                    
        left++;                                                     
    }                                                               

    maxKeep = max(maxKeep, right - left + 1);                       
}                                                                   

return n - maxKeep;  // What we must take from edges                

}
```

TIME: O(N)  |  SPACE: O(1)

### PRACTICE PROBLEMS - Inverse/Complement:

- 1658. Minimum Operations to Reduce X to Zero 
- 2516. Take K of Each Character From Left and Right 
- 1423. Maximum Points You Can Obtain from Cards 

### **PATTERN C: SORTING + SLIDING WINDOW**

**USE WHEN:**
- Order doesn't matter (can rearrange/choose elements)
- Need min/max difference in window
- Need "closest" elements

 **KEY INSIGHT**: Sort first, then sliding window on sorted array

## **SOLVED: Minimum Difference Between Highest and Lowest of K Scores (LC 1984)**

PROBLEM: Choose k scores, minimize (max - min) among chosen.

 **KEY INSIGHT**: After sorting, optimal k elements are consecutive!

```cpp
int minimumDifference(vector<int>& nums, int k) {
sort(nums.begin(), nums.end());                       

int minDiff = INT_MAX;                                
for (int i = 0; i + k - 1 < nums.size(); i++) {       
    minDiff = min(minDiff, nums[i + k - 1] - nums[i]);
}                                                     

return minDiff;                                       

}
```

TIME: O(N log N)  |  SPACE: O(1)

## **SOLVED: Find K Closest Elements (LC 658)**

PROBLEM: Find k closest elements to x in sorted array.

 **APPROACH**: Binary search start position + sliding window concept

```cpp
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
int left = 0, right = arr.size() - k;                          

while (left < right) {                                         
    int mid = left + (right - left) / 2;                       
    // Compare distances: x - arr[mid] vs arr[mid+k] - x       
    if (x - arr[mid] > arr[mid + k] - x) {                     
        left = mid + 1;                                        
    } else {                                                   
        right = mid;                                           
    }                                                          
}                                                              

return vector<int>(arr.begin() + left, arr.begin() + left + k);

}
```

TIME: O(log(N-K) + K)  |  SPACE: O(1)

## **SOLVED: Maximum Beauty of an Array After Applying Operation (LC 2779)**

PROBLEM: Each element can change to [nums[i]-k, nums[i]+k]. Find max identical elements.

 **KEY INSIGHT**: After sorting, find longest window where max-min <= 2*k

```cpp
int maximumBeauty(vector<int>& nums, int k) {
sort(nums.begin(), nums.end());                                  

int left = 0, maxLen = 0;                                        

for (int right = 0; right < nums.size(); right++) {              
    // All elements in window can become same if max - min <= 2*k
    while (nums[right] - nums[left] > 2 * k) {                   
        left++;                                                  
    }                                                            
    maxLen = max(maxLen, right - left + 1);                      
}                                                                

return maxLen;                                                   

}
```

TIME: O(N log N)  |  SPACE: O(1)

## **SOLVED: Minimum Number of Operations to Make Array Continuous (LC 2009)**

PROBLEM: Make array continuous (consecutive unique elements). Find min ops.

 **KEY INSIGHT**: Sort + dedupe, find max elements fitting in range [x, x+n-1]

```cpp
int minOperations(vector<int>& nums) {
int n = nums.size();                              

// Sort and remove duplicates                     
set<int> s(nums.begin(), nums.end());             
vector<int> arr(s.begin(), s.end());              

int maxKeep = 0, left = 0;                        

for (int right = 0; right < arr.size(); right++) {
    // Valid range: [arr[left], arr[left] + n - 1]
    while (arr[right] > arr[left] + n - 1) {      
        left++;                                   
    }                                             
    maxKeep = max(maxKeep, right - left + 1);     
}                                                 

return n - maxKeep;                               

}
```

TIME: O(N log N)  |  SPACE: O(N)

### PRACTICE PROBLEMS - Sorting + Sliding Window:

- 1984. Minimum Difference Between Highest and Lowest of K Scores 
- 658.  Find K Closest Elements 
- 2779. Maximum Beauty of an Array After Applying Operation 
- 2009. Minimum Number of Operations to Make Array Continuous 
- 1838. Frequency of the Most Frequent Element 

### **PATTERN D: SLIDING WINDOW + HEAP / MULTISET**

USE WHEN: Need median, k-th element, or sorted order within window

 **KEY INSIGHT**: Use ordered data structure for O(log N) updates

## **SOLVED: Smallest Range Covering Elements from K Lists (LC 632)**

PROBLEM: Find smallest range that includes at least one element from each list.

 **APPROACH**: Min-heap tracks current element from each list

```cpp
vector<int> smallestRange(vector<vector<int>>& nums) {
// Min-heap: {value, list_idx, element_idx}                    
priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;

int maxVal = INT_MIN;                                          
for (int i = 0; i < nums.size(); i++) {                        
    pq.push({nums[i][0], i, 0});                               
    maxVal = max(maxVal, nums[i][0]);                          
}                                                              

int rangeStart = 0, rangeEnd = INT_MAX;                        

while (pq.size() == nums.size()) {                             
    auto [minVal, listIdx, elemIdx] = pq.top();                
    pq.pop();                                                  

    if (maxVal - minVal < rangeEnd - rangeStart) {             
        rangeStart = minVal;                                   
        rangeEnd = maxVal;                                     
    }                                                          

    if (elemIdx + 1 < nums[listIdx].size()) {                  
        int nextVal = nums[listIdx][elemIdx + 1];              
        pq.push({nextVal, listIdx, elemIdx + 1});              
        maxVal = max(maxVal, nextVal);                         
    }                                                          
}                                                              

return {rangeStart, rangeEnd};                                 

}
```

TIME: O(N log K)  |  SPACE: O(K) where N = total elements, K = number of lists

### PRACTICE PROBLEMS - Heap + Sliding Window:

- 632.  Smallest Range Covering Elements from K Lists 
- 480.  Sliding Window Median 
- 295.  Find Median from Data Stream (related)

### **PATTERN E: COUNTING SUBARRAYS WITH CONDITIONS**

USE WHEN: Count subarrays where specific element/condition appears at least k times

## **SOLVED: Count Subarrays Where Max Element Appears at Least K Times (LC 2962)**

PROBLEM: Count subarrays where max element of array appears >= k times.

```cpp
long long countSubarrays(vector<int>& nums, int k) {
int maxVal = *max_element(nums.begin(), nums.end());                             
int n = nums.size();                                                             
long long count = 0;                                                             
int left = 0, maxCount = 0;                                                      

for (int right = 0; right < n; right++) {                                        
    if (nums[right] == maxVal) maxCount++;                                       

    while (maxCount >= k) {                                                      
        // All subarrays starting at left and ending at right or beyond are valid
        count += n - right;                                                      
        if (nums[left] == maxVal) maxCount--;                                    
        left++;                                                                  
    }                                                                            
}                                                                                

return count;                                                                    

}
```

TIME: O(N)  |  SPACE: O(1)

## **SOLVED: Count of Substrings Containing Every Vowel and K Consonants II (LC 3306)**

PROBLEM: Count substrings with all 5 vowels and exactly k consonants.

 **KEY INSIGHT**: Use atLeast(k) - atLeast(k+1) for exactly k consonants

```cpp
long long countOfSubstrings(string word, int k) {
return atLeast(word, k) - atLeast(word, k + 1);

}

long long atLeast(string& word, int k) {
int n = word.size();                                                
long long count = 0;                                                
int left = 0, consonants = 0;                                       
unordered_map<char, int> vowels;                                    
string vow = "aeiou";                                               

auto isVowel = [](char c) {                                         
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
};                                                                  

for (int right = 0; right < n; right++) {                           
    if (isVowel(word[right])) {                                     
        vowels[word[right]]++;                                      
    } else {                                                        
        consonants++;                                               
    }                                                               

    // Shrink while valid (all vowels present AND consonants >= k)  
    while (vowels.size() == 5 && consonants >= k) {                 
        count += n - right;  // All extensions are valid            
        if (isVowel(word[left])) {                                  
            vowels[word[left]]--;                                   
            if (vowels[word[left]] == 0) vowels.erase(word[left]);  
        } else {                                                    
            consonants--;                                           
        }                                                           
        left++;                                                     
    }                                                               
}                                                                   

return count;                                                       

}
```

TIME: O(N)  |  SPACE: O(1)

### PRACTICE PROBLEMS - Counting with Conditions:

- 2962. Count Subarrays Where Max Element Appears at Least K Times 
- 3306. Count of Substrings Containing Every Vowel and K Consonants II 
- 1358. Number of Substrings Containing All Three Characters 
- 2799. Count Complete Subarrays in an Array 

## **PART 8: COMPLETE PROBLEM LIST BY PATTERN**

**PATTERN 1: FIXED-SIZE WINDOW**

- 219.  Contains Duplicate II 
- 643.  Maximum Average Subarray I 
- 1052. Grumpy Bookstore Owner 
- 1176. Diet Plan Performance
- 1343. Number of Sub-arrays of Size K and Avg >= Threshold 
- 1456. Maximum Number of Vowels in a Substring of Given Length 
- 1652. Defuse the Bomb 
- 1984. Minimum Difference Between Highest and Lowest of K Scores 
- 2090. K Radius Subarray Averages
- 2269. Find the K-Beauty of a Number
- 2379. Minimum Recolors to Get K Consecutive Black Blocks 
- 2461. Maximum Sum of Distinct Subarrays With Length K 
- 3254. Find the Power of K-Size Subarrays I 

**PATTERN 2: VARIABLE-SIZE (Expand + Shrink)**

- 3.    Longest Substring Without Repeating Characters 
- 209.  Minimum Size Subarray Sum 
- 485.  Max Consecutive Ones  (Simple counting, no window needed)
- 487.  Max Consecutive Ones II 
- 904.  Fruit Into Baskets 
- 1004. Max Consecutive Ones III 
- 1208. Get Equal Substrings Within Budget 
- 1100. Find K-Length Substrings With No Repeated Characters 
- 2024. Maximize the Confusion of an Exam
- 2958. Length of Longest Subarray With at Most K Frequency 

**PATTERN 3: FREQUENCY MAP (Anagrams/Permutations)**

- 567.  Permutation in String 
- 438.  Find All Anagrams in a String 
- 76.   Minimum Window Substring 
- 159.  Longest Substring with At Most Two Distinct Characters 
- 340.  Longest Substring with At Most K Distinct Characters 

**PATTERN 4: LONGEST/SHORTEST WITH CONDITION**

- 121.  Best Time to Buy and Sell Stock  (One-Pass, not classic SW)
- 424.  Longest Repeating Character Replacement 
- 487.  Max Consecutive Ones II 
- 1004. Max Consecutive Ones III 
- 1493. Longest Subarray of 1's After Deleting One Element
- 1838. Frequency of the Most Frequent Element 

**PATTERN 5: EXACTLY K / AT MOST K**

- 930.  Binary Subarrays With Sum 
- 992.  Subarrays with K Different Integers 
- 1248. Count Number of Nice Subarrays 
- 3.    Longest Substring Without Repeating Characters 
- 159.  Longest Substring with At Most Two Distinct Characters 
- 340.  Longest Substring with At Most K Distinct Characters 
- 904.  Fruit Into Baskets 

**PATTERN 6: COUNTING SUBARRAYS**

- 713.  Subarray Product Less Than K 
- 1358. Number of Substrings Containing All Three Characters 
- 2302. Count Subarrays With Score Less Than K
- 2962. Count Subarrays Where Max Element Appears at Least K Times 
- 3306. Count of Substrings Containing Every Vowel and K Consonants II 
 For sum=K with negatives > See Prefix Sum.txt

**PATTERN 7: MONOTONIC DEQUE (Max/Min in Window)**

- 239.  Sliding Window Maximum 
- 480.  Sliding Window Median (Multiset) 
- 862.  Shortest Subarray with Sum at Least K 
- 1438. Longest Continuous Subarray With Absolute Diff <= Limit 

**PATTERN 8: CIRCULAR ARRAY**

- 1652. Defuse the Bomb 
- 1888. Minimum Number of Flips to Make Binary String Alternating 
- 3208. Alternating Groups II 
- 1423. Maximum Points You Can Obtain from Cards 

**PATTERN 9: INVERSE/COMPLEMENT**

- 1658. Minimum Operations to Reduce X to Zero 
- 2516. Take K of Each Character From Left and Right 
- 1423. Maximum Points You Can Obtain from Cards 

**PATTERN 10: SORTING + SLIDING WINDOW**

- 658.  Find K Closest Elements 
- 1984. Minimum Difference Between Highest and Lowest of K Scores 
- 1838. Frequency of the Most Frequent Element 
- 2009. Minimum Number of Operations to Make Array Continuous 
- 2779. Maximum Beauty of an Array After Applying Operation 

**PATTERN 11: SLIDING WINDOW + HEAP**

- 632.  Smallest Range Covering Elements from K Lists 
- 480.  Sliding Window Median 

## **MASTER PROBLEM MAPPING TABLE**

```
+---------------------------------------------------------+------------------------+
| Problem                                                 | Pattern                |
+---------------------------------------------------------+------------------------+
| Contains Duplicate II                                   | 1 - Fixed-Size         |
| Best Time to Buy And Sell Stock                         | 4 - One-Pass/Greedy    |
| Minimum Recolors to Get K Consecutive Black Blocks      | 1 - Fixed-Size         |
| Minimum Difference Between Highest/Lowest of K Scores   | 10 - Sorting + SW      |
| Number of Sub Arrays Size K and Avg >= Threshold        | 1 - Fixed-Size         |
| Grumpy Bookstore Owner                                  | 1 - Fixed-Size         |
| Max Consecutive Ones II                                 | 2 - Variable (flip 1)  |
| Alternating Groups II                                   | 8 - Circular           |
| Longest Substring Without Repeating Characters          | 2/5 - Variable/AtMost  |
| Longest Substring with At Most Two Distinct Characters  | 5 - At Most K          |
| Longest Repeating Character Replacement                 | 4 - Longest            |
| Permutation In String                                   | 3 - Frequency Map      |
| Longest Substring with At Most K Distinct Characters    | 5 - At Most K          |
| Frequency of The Most Frequent Element                  | 10 - Sorting + SW      |
| Fruits into Basket                                      | 5 - At Most 2 Distinct |
| Maximum Number of Vowels in a Substring of Given Length | 1 - Fixed-Size         |
| Minimum Number of Flips Binary String Alternating       | 8 - Circular           |
| Defuse the Bomb                                         | 8 - Circular           |
| Minimum Size Subarray Sum                               | 2 - Variable           |
| Find K Closest Elements                                 | 10 - Sorting + SW      |
| Minimum Operations to Reduce X to Zero                  | 9 - Inverse            |
| Find K-Length Substrings With No Repeated Characters    | 2 - Variable + Fixed   |
| Get Equal Substrings Within Budget                      | 2 - Variable           |
| Number of Substrings Containing All Three Characters    | 6 - Counting           |
| Binary Subarrays with Sum                               | 5 - Exactly K          |
| Count Number of Nice Subarrays                          | 5 - Exactly K          |
| Subarray Product Less Than K                            | 6 - Counting           |
| Max Consecutive Ones III                                | 2 - Variable (flip k)  |
| Find the Power of K-Size Subarrays I                    | 1 - Fixed-Size         |
| Maximum Sum of Distinct Subarrays With Length K         | 1 - Fixed-Size         |
| Length of Longest Subarray With at Most K Frequency     | 2 - Variable           |
| Count Subarrays Where Max Element Appears >= K Times    | 6 - Counting           |
| Maximum Beauty of an Array After Applying Operation     | 10 - Sorting + SW      |
| Take K of Each Character From Left and Right            | 9 - Inverse            |
| Count Substrings Every Vowel and K Consonants II        | 6 - Counting + Exactly |
| Minimum Window Substring                                | 3 - Frequency Map      |
| Sliding Window Maximum                                  | 7 - Monotonic Deque    |
| Subarrays with K Different Integers                     | 5 - Exactly K          |
| Minimum Number of Operations to Make Array Continuous   | 10 - Sorting + SW      |
| Longest Subarray With Absolute Diff <= Limit            | 7 - Monotonic Deque    |
| Smallest Range Covering Elements from K Lists           | 11 - SW + Heap         |
+---------------------------------------------------------+------------------------+

================================================================================    
                     **11 PATTERNS QUICK REFERENCE**                                
================================================================================    
```

Pattern 1:  Fixed-Size Window      > Window size k fixed, slide add/remove
Pattern 2:  Variable-Size          > Expand+Shrink based on condition
Pattern 3:  Frequency Map          > Anagrams, permutations, char matching
Pattern 4:  Longest/Shortest       > Max/min length with constraints
Pattern 5:  Exactly K / At Most K  > atMost(K) - atMost(K-1) trick
Pattern 6:  Counting Subarrays     > count += (j - i + 1) at each step
Pattern 7:  Monotonic Deque        > Max/min in each window efficiently
Pattern 8:  Circular Array         > Double array or modulo indexing
Pattern 9:  Inverse/Complement     > Remove from edges = Keep middle
Pattern 10: Sorting + SW           > Sort first when order doesn't matter
Pattern 11: SW + Heap              > For median, k-th element in window

```
  Sum=K with NEGATIVES > Use Prefix Sum.txt (Sliding Window doesn't work!)
```

```
+------------------------------------------------------------------------------+
|                     PATTERN DECISION FLOWCHART                               |
+------------------------------------------------------------------------------+
|                                                                              |
|  Is window size FIXED (k given)?                                             |
|    YES > Pattern 1 (Fixed-Size)                                              |
|    Is it circular? > Pattern 8 (Circular)                                    |
|                                                                              |
|  Do you need to COUNT subarrays?                                             |
|    YES > Pattern 6 (Counting) > count += (right - left + 1)                  |
|    "Exactly K"? > Pattern 5 (atMost(K) - atMost(K-1))                        |
|                                                                              |
|  Remove from BOTH ends?                                                      |
|    YES > Pattern 9 (Inverse) > Find longest MIDDLE instead                   |
|                                                                              |
|  Order doesn't matter / Need closest elements?                               |
|    YES > Pattern 10 (Sorting + SW)                                           |
|                                                                              |
|  Need MAX or MIN within window?                                              |
|    YES > Pattern 7 (Monotonic Deque)                                         |
|                                                                              |
|  Need MEDIAN / k-th element in window?                                       |
|    YES > Pattern 11 (Heap/Multiset)                                          |
|                                                                              |
|  Anagrams / Permutations / Character matching?                               |
|    YES > Pattern 3 (Frequency Map)                                           |
|                                                                              |
|  Otherwise > Pattern 2 (Variable-Size) with appropriate shrink condition     |
|                                                                              |
+------------------------------------------------------------------------------+

================================================================================
                                   END                                          
================================================================================
```
