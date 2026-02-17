import java.util.*;

/**
 * Problem: 3583. Count Special Triplets
 * Difficulty: Medium
 * Category: Array, Hash Table, Counting
 * 
 * Problem Statement:
 * Find triplets (i, j, k) where:
 * - 0 <= i < j < k < n
 * - nums[i] == nums[j] * 2
 * - nums[k] == nums[j] * 2
 * 
 * Return count modulo 10^9 + 7.
 * 
 * Key Insight:
 * For each middle element j:
 * - Count elements to left equal nums[j] * 2
 * - Count elements to right equal nums[j] * 2
 * - Multiply counts (multiplication principle)
 * 
 * Time: O(n)
 * Space: O(n)
 */

class Solution {
    private static final int MOD = 1_000_000_007;
    
    public int countSpecialTriplets(int[] nums) {
        int n = nums.length;
        if (n < 3) return 0;
        
        // Precompute right frequencies
        Map<Integer, Integer> rightFreq = new HashMap<>();
        for (int num : nums) {
            rightFreq.put(num, rightFreq.getOrDefault(num, 0) + 1);
        }
        
        long result = 0;
        Map<Integer, Integer> leftFreq = new HashMap<>();
        
        for (int j = 0; j < n; j++) {
            // Remove current from right
            rightFreq.put(nums[j], rightFreq.get(nums[j]) - 1);
            if (rightFreq.get(nums[j]) == 0) {
                rightFreq.remove(nums[j]);
            }
            
            // Calculate target value
            int target = nums[j] * 2;
            
            long leftCount = leftFreq.getOrDefault(target, 0);
            long rightCount = rightFreq.getOrDefault(target, 0);
            
            result = (result + (leftCount * rightCount) % MOD) % MOD;
            
            // Add current to left
            leftFreq.put(nums[j], leftFreq.getOrDefault(nums[j], 0) + 1);
        }
        
        return (int) result;
    }
}

/**
 * Test Cases
 */
class TestSpecialTriplets {
    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] nums1 = {1, 2, 4, 2, 4};
        System.out.println("Test 1: " + sol.countSpecialTriplets(nums1));
        // Expected: 1
        
        int[] nums2 = {2, 4, 8, 4, 8};
        System.out.println("Test 2: " + sol.countSpecialTriplets(nums2));
        // Expected: 1
        
        int[] nums3 = {1, 2, 3};
        System.out.println("Test 3: " + sol.countSpecialTriplets(nums3));
        // Expected: 0
        
        int[] nums4 = {4, 2, 4, 2, 4};
        System.out.println("Test 4: " + sol.countSpecialTriplets(nums4));
        // Expected: 4
    }
}

/*
============================================================================
VISUAL EXPLANATION
============================================================================

Example: nums = [4, 2, 4, 2, 4]
                 0  1  2  3  4

Process each j as middle element:

j=1 (nums[j]=2, target=4):
  ┌─────────┐     ┌─────────┐
  │ Left: 4 │  2  │Right:4,4│
  │ Count=1 │     │ Count=2 │
  └─────────┘     └─────────┘
  Triplets: 1 × 2 = 2
  
  Valid triplets:
    (0, 1, 2): [4, 2, 4] ✓
    (0, 1, 4): [4, 2, 4] ✓

j=3 (nums[j]=2, target=4):
  ┌───────────┐     ┌───────┐
  │Left: 4,4  │  2  │Right:4│
  │ Count=2   │     │Count=1│
  └───────────┘     └───────┘
  Triplets: 2 × 1 = 2
  
  Valid triplets:
    (0, 3, 4): [4, 2, 4] ✓
    (2, 3, 4): [4, 2, 4] ✓

Total: 2 + 2 = 4 triplets


============================================================================
ALGORITHM VISUALIZATION
============================================================================

Step-by-step for nums = [4, 2, 4, 2, 4]:

Initial:
  leftFreq = {}
  rightFreq = {4:3, 2:2}

j=0 (val=4):
  Remove 4 from right: rightFreq = {4:2, 2:2}
  target = 8
  leftCount[8] = 0, rightCount[8] = 0
  result += 0
  Add 4 to left: leftFreq = {4:1}

j=1 (val=2):
  Remove 2 from right: rightFreq = {4:2, 2:1}
  target = 4
  leftCount[4] = 1, rightCount[4] = 2
  result += 1*2 = 2 ✓
  Add 2 to left: leftFreq = {4:1, 2:1}

j=2 (val=4):
  Remove 4 from right: rightFreq = {4:1, 2:1}
  target = 8
  leftCount[8] = 0, rightCount[8] = 0
  result += 0
  Add 4 to left: leftFreq = {4:2, 2:1}

j=3 (val=2):
  Remove 2 from right: rightFreq = {4:1}
  target = 4
  leftCount[4] = 2, rightCount[4] = 1
  result += 2*1 = 2 ✓
  Add 2 to left: leftFreq = {4:2, 2:2}

j=4 (val=4):
  Remove 4 from right: rightFreq = {}
  target = 8
  leftCount[8] = 0, rightCount[8] = 0
  result += 0

Final result: 2 + 2 = 4 ✓


============================================================================
PATTERN: FIX MIDDLE ELEMENT
============================================================================

This pattern appears in many triplet counting problems:

1. Fix middle element (j)
2. Count valid elements to the left (i < j)
3. Count valid elements to the right (k > j)
4. Multiply counts (multiplication principle)

Similar problems:
- Count triplets with sum = target
- Count triplets with product = target
- Count triplets with specific relationship

Key technique:
- Maintain left and right frequency maps
- Process from left to right
- Update maps as you go


============================================================================
COMPLEXITY ANALYSIS
============================================================================

Time Complexity: O(n)
- Precompute right frequencies: O(n)
- Single pass through array: O(n)
- HashMap operations: O(1) average per operation

Space Complexity: O(n)
- rightFreq map: O(n) in worst case
- leftFreq map: O(n) in worst case

Much better than brute force O(n³)!


============================================================================
KEY INSIGHTS
============================================================================

1. ✅ Fix middle element instead of trying all combinations
2. ✅ Use hashmaps for O(1) frequency lookups
3. ✅ Multiplication principle: leftCount × rightCount
4. ✅ Process left-to-right maintaining both frequency maps
5. ✅ Remove from right, add to left as we progress

This is a fundamental competitive programming pattern!

============================================================================
*/

