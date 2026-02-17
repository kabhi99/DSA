#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// ============================================================================
// SIDE-BY-SIDE COMPARISON OF BOTH APPROACHES
// ============================================================================

class Solution_Approach1_Nested {
public:
    // O(k²) - Nested loops approach (What you understand)
    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<int, int> yCount;
        
        // Count points at each y-level
        for (auto& p : points) {
            yCount[p[1]]++;
        }
        
        // Extract counts
        vector<long long> edges;
        for (auto& [y, count] : yCount) {
            if (count >= 2) {
                long long edge = (long long)count * (count - 1) / 2;
                edges.push_back(edge);
            }
        }
        
        long long ans = 0;
        
        // NESTED LOOPS: Compare every pair
        for (int i = 0; i < edges.size(); i++) {
            for (int j = i + 1; j < edges.size(); j++) {
                ans += edges[i] * edges[j];  // Multiply pair by pair
            }
        }
        
        return ans % (int)(1e9 + 7);
    }
};


class Solution_Approach2_RunningSum {
public:
    // O(k) - Running sum approach (The optimization)
    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<int, int> pointNum;
        const int mod = 1e9 + 7;
        long long ans = 0, sum = 0;
        
        // Count points at each y-level
        for (auto& point : points) {
            pointNum[point[1]]++;
        }
        
        // SINGLE LOOP: Multiply current edge with sum of all previous
        for (auto& [y, pNum] : pointNum) {
            long long edge = (long long)pNum * (pNum - 1) / 2;
            ans += edge * sum;  // sum contains (e1+e2+...+e(i-1))
            sum += edge;        // add current edge to sum
        }
        
        return ans % mod;
    }
};


// ============================================================================
// TEST TO SHOW BOTH GIVE SAME ANSWER
// ============================================================================

int main() {
    Solution_Approach1_Nested sol1;
    Solution_Approach2_RunningSum sol2;
    
    // Test case
    vector<vector<int>> points = {{1,1}, {2,1}, {3,1}, {1,2}, {2,2}, {1,3}, {2,3}};
    
    cout << "Test points: [[1,1], [2,1], [3,1], [1,2], [2,2], [1,3], [2,3]]\n\n";
    
    cout << "y=1: 3 points → e1 = C(3,2) = 3\n";
    cout << "y=2: 2 points → e2 = C(2,2) = 1\n";
    cout << "y=3: 2 points → e3 = C(2,2) = 1\n\n";
    
    cout << "Expected: e1*e2 + e1*e3 + e2*e3 = 3*1 + 3*1 + 1*1 = 7\n\n";
    
    cout << "Approach 1 (Nested Loops): " << sol1.countTrapezoids(points) << endl;
    cout << "Approach 2 (Running Sum):   " << sol2.countTrapezoids(points) << endl;
    
    cout << "\nBoth give same answer! But Approach 2 is faster for large k.\n";
    
    return 0;
}

/* 
============================================================================
TRACE OF APPROACH 2 FOR THIS EXAMPLE:
============================================================================

Initial: ans = 0, sum = 0

Process e1=3:
  ans += 3 * 0 = 0  →  ans = 0
  sum += 3          →  sum = 3
  (No previous edges, so no products added yet)

Process e2=1:
  ans += 1 * 3 = 3  →  ans = 3
  sum += 1          →  sum = 4
  (Added: e1*e2 = 3*1 = 3)

Process e3=1:
  ans += 1 * 4 = 4  →  ans = 7
  sum += 1          →  sum = 5
  (Added: e1*e3 + e2*e3 = 3*1 + 1*1 = 4)

Final ans = 7 ✓

Breaking down the last step:
  ans += edge * sum
  ans += 1 * 4
  
  What is sum=4? It's e1+e2 = 3+1 = 4
  
  So: 1 * (3+1) = 1*3 + 1*1 = e3*e1 + e3*e2
  
  This adds both e1*e3 and e2*e3 in ONE operation!

============================================================================
*/

