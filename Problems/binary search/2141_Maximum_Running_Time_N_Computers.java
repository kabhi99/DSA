/*
2141. Maximum Running Time of N Computers
https://leetcode.com/problems/maximum-running-time-of-n-computers/description/

APPROACH: Binary Search on Answer

KEY POINTS:
1. Binary search on running time T (0 to sum/n)
2. For each T, check feasibility: Can all N computers run for T minutes?

FORMULA: sum(min(battery[i], T)) >= N * T

WHY min(battery[i], T)?
- Battery > T: Can only use T minutes (dedicated to 1 computer entire time)
- Battery ≤ T: Use all of it (can swap between computers)

EXAMPLE: n=2, batteries=[3,3,3], T=4
- Available: min(3,4) + min(3,4) + min(3,4) = 9
- Needed: 2 * 4 = 8
- 9 >= 8 ✓ Works!

TIME: O(m * log(sum/n)), SPACE: O(1)
*/

class Solution {
    public long maxRunTime(int n, int[] batteries) {
        long left = 0, right = 0;
        
        for (int battery : batteries) {
            right += battery;
        }
        right /= n;
        
        long result = 0;
        
        while (left <= right) {
            long mid = left + (right - left) / 2;
            
            if (canRunForTime(n, batteries, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    private boolean canRunForTime(int n, int[] batteries, long targetTime) {
        long totalUsablePower = 0;
        
        for (int battery : batteries) {
            totalUsablePower += Math.min(battery, targetTime);
        }
        
        return totalUsablePower >= (long) n * targetTime;
    }
}


/*
TEST CASES:
Input: n = 2, batteries = [3,3,3]  → Output: 4
Input: n = 2, batteries = [1,1,1,1] → Output: 2
Input: n = 3, batteries = [10,10,3,5] → Output: 8
*/


