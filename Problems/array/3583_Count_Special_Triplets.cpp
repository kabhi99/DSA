#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Problem: 3583. Count Special Triplets
Difficulty: Medium
Category: Array, Hash Table, Counting

Problem Statement:
Find triplets (i, j, k) where:
- 0 <= i < j < k < n
- nums[i] == nums[j] * 2
- nums[k] == nums[j] * 2

Return count modulo 10^9 + 7.

Key Insight:
For each middle element j:
- Count how many elements to the left equal nums[j] * 2
- Count how many elements to the right equal nums[j] * 2
- Multiply these counts (multiplication principle)

Approach:
1. For each j as middle element:
   - leftCount[nums[j]*2] = count of (nums[j]*2) to the left of j
   - rightCount[nums[j]*2] = count of (nums[j]*2) to the right of j
   - Add leftCount * rightCount to answer

2. Use hashmap to track frequencies efficiently

Time: O(n)
Space: O(n)
*/

class Solution {
public:
    int countSpecialTriplets(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        if (n < 3) return 0;
        
        // Precompute right frequencies
        unordered_map<int, int> rightFreq;
        for (int k = 0; k < n; k++) {
            rightFreq[nums[k]]++;
        }
        
        long long result = 0;
        unordered_map<int, int> leftFreq;
        
        for (int j = 0; j < n; j++) {
            // Remove current element from right
            rightFreq[nums[j]]--;
            if (rightFreq[nums[j]] == 0) {
                rightFreq.erase(nums[j]);
            }
            
            // nums[i] = nums[j] * 2 (i < j)
            // nums[k] = nums[j] * 2 (k > j)
            int target = nums[j] * 2;
            
            long long leftCount = leftFreq[target];
            long long rightCount = rightFreq[target];
            
            result = (result + (leftCount * rightCount) % MOD) % MOD;
            
            // Add current element to left
            leftFreq[nums[j]]++;
        }
        
        return result;
    }
};

/*
============================================================================
DETAILED EXPLANATION
============================================================================

Example: nums = [1, 2, 4, 2, 4]
                 0  1  2  3  4

Find triplets where nums[i] = nums[k] = nums[j] * 2


For j=1 (nums[j] = 2):
  target = 2 * 2 = 4
  Left of j=1: [1] → leftCount[4] = 0
  Right of j=1: [4, 2, 4] → rightCount[4] = 2
  Triplets: 0 * 2 = 0

For j=2 (nums[j] = 4):
  target = 4 * 2 = 8
  Left of j=2: [1, 2] → leftCount[8] = 0
  Right of j=2: [2, 4] → rightCount[8] = 0
  Triplets: 0 * 0 = 0

For j=3 (nums[j] = 2):
  target = 2 * 2 = 4
  Left of j=3: [1, 2, 4] → leftCount[4] = 1 (index 2)
  Right of j=3: [4] → rightCount[4] = 1 (index 4)
  Triplets: 1 * 1 = 1
  Valid triplet: (2, 3, 4) → nums = [4, 2, 4]

For j=4 (nums[j] = 4):
  target = 4 * 2 = 8
  Left of j=4: [1, 2, 4, 2] → leftCount[8] = 0
  Right of j=4: [] → rightCount[8] = 0
  Triplets: 0 * 0 = 0

Total: 1 triplet


============================================================================
WHY THIS WORKS - MULTIPLICATION PRINCIPLE
============================================================================

For each middle element j:
- We need to pick 1 element from left (value = nums[j]*2)
- AND pick 1 element from right (value = nums[j]*2)

By multiplication principle:
  Total ways = (ways to pick left) × (ways to pick right)
               = leftCount × rightCount

This is the SAME pattern as:
- Horizontal trapezoids problem (pick from 2 y-levels)
- Running sum pattern (but here we multiply for each j separately)


Visual Example:
---------------
nums = [4, 2, 4, 2, 4]
        i  j  k1 j2 k2

For j=1 (value 2, target 4):
  Left candidates: [4] at index 0
  Right candidates: [4, 4] at indices 2, 4
  
  Possible triplets:
    (0, 1, 2): [4, 2, 4] ✓
    (0, 1, 4): [4, 2, 4] ✓
  
  Count: 1 left × 2 right = 2


============================================================================
ALGORITHM STEPS
============================================================================

1. PRECOMPUTE right frequencies:
   rightFreq = frequency map of all elements

2. PROCESS each j from left to right:
   a. Remove nums[j] from rightFreq (it's now middle, not right)
   b. Calculate target = nums[j] * 2
   c. Get leftCount[target] and rightCount[target]
   d. Add leftCount × rightCount to result
   e. Add nums[j] to leftFreq (for future j's)

3. Return result % MOD


============================================================================
TIME & SPACE COMPLEXITY
============================================================================

Time: O(n)
- Precompute right frequencies: O(n)
- Single pass through array: O(n)
- HashMap operations: O(1) average

Space: O(n)
- rightFreq hashmap: O(n) worst case
- leftFreq hashmap: O(n) worst case


============================================================================
EDGE CASES
============================================================================

1. Array too small (n < 3): return 0
2. No valid triplets: return 0
3. All elements same: depends on relationship
4. Large counts: use MOD to prevent overflow


============================================================================
SIMILAR PROBLEMS
============================================================================

1. Count pairs/triplets with specific relationship
2. Two Sum / Three Sum variations
3. Subarray problems with constraints
4. Multiplication principle in counting


Pattern: For middle element, count left × count right
Common in: triplet counting, range queries


============================================================================
*/

// Test cases
int main() {
    Solution sol;
    
    vector<int> nums1 = {1, 2, 4, 2, 4};
    cout << "Test 1: " << sol.countSpecialTriplets(nums1) << endl;
    // Expected: 1 (triplet: (2,3,4) → [4,2,4])
    
    vector<int> nums2 = {2, 4, 8, 4, 8};
    cout << "Test 2: " << sol.countSpecialTriplets(nums2) << endl;
    // j=1 (val=4, target=8): left[8]=0, right[8]=2 → 0
    // j=3 (val=4, target=8): left[8]=1, right[8]=1 → 1
    // Expected: 1
    
    vector<int> nums3 = {1, 2, 3};
    cout << "Test 3: " << sol.countSpecialTriplets(nums3) << endl;
    // Expected: 0 (no valid triplets)
    
    vector<int> nums4 = {4, 2, 4, 2, 4};
    cout << "Test 4: " << sol.countSpecialTriplets(nums4) << endl;
    // j=1 (val=2, target=4): left[4]=1, right[4]=2 → 2
    // j=3 (val=2, target=4): left[4]=2, right[4]=1 → 2
    // Expected: 4
    
    return 0;
}

/*
============================================================================
KEY TAKEAWAYS
============================================================================

1. ✅ For triplets, fix middle and count left × right
2. ✅ Use hashmaps to track frequencies efficiently
3. ✅ Multiplication principle for independent choices
4. ✅ Process left-to-right, maintaining left and right frequencies
5. ✅ Remove from right, add to left as we progress
6. ✅ O(n) solution better than O(n²) brute force

Pattern Recognition:
- "Count triplets" → fix middle element
- "i < j < k" → process j, count left and right
- "specific relationship" → use hashmap for frequencies

This is a common competitive programming pattern!

============================================================================
*/

