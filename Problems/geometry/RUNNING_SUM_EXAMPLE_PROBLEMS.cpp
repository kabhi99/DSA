#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

/*
============================================================================
RUNNING SUM PATTERN - EXAMPLE PROBLEMS
============================================================================

Pattern: Computing pairwise products/combinations in O(n) instead of O(n²)

Key Insight: 
  result += current * sum
  sum += current

This computes ALL pairwise products efficiently!
============================================================================
*/


// ============================================================================
// PROBLEM 1: Sum of All Pairwise Products
// ============================================================================
/*
Given: array = [2, 3, 5, 7]
Find: 2*3 + 2*5 + 2*7 + 3*5 + 3*7 + 5*7
*/

long long pairwiseProductSum(vector<int>& arr) {
    long long result = 0;
    long long sum = 0;
    
    for (int val : arr) {
        result += (long long)val * sum;
        sum += val;
    }
    
    return result;
}


// ============================================================================
// PROBLEM 2: Count Ways to Pick From Different Groups
// ============================================================================
/*
Given: groups with sizes [3, 2, 4, 5]
Find: Number of ways to pick 1 item from one group and 1 from another
Answer: 3*2 + 3*4 + 3*5 + 2*4 + 2*5 + 4*5
*/

long long countPicksAcrossGroups(vector<int>& groupSizes) {
    long long result = 0;
    long long sum = 0;
    
    for (int size : groupSizes) {
        result += (long long)size * sum;
        sum += size;
    }
    
    return result;
}


// ============================================================================
// PROBLEM 3: Shipping Cost Calculation
// ============================================================================
/*
Given: Items at locations with quantities [q1, q2, q3, ...]
Cost to ship between any two locations = product of their quantities
Find: Total shipping cost for all pairs

Example: quantities = [5, 3, 4]
Cost = 5*3 + 5*4 + 3*4 = 15 + 20 + 12 = 47
*/

long long totalShippingCost(vector<int>& quantities) {
    long long totalCost = 0;
    long long sum = 0;
    
    for (int qty : quantities) {
        totalCost += (long long)qty * sum;
        sum += qty;
    }
    
    return totalCost;
}


// ============================================================================
// PROBLEM 4: Count Pairs of Different Elements
// ============================================================================
/*
Given: array = [1, 1, 1, 2, 2, 3]
Count: pairs of DIFFERENT elements
Answer: pairs of (1,2) + pairs of (1,3) + pairs of (2,3)
      = 3*2 + 3*1 + 2*1 = 6 + 3 + 2 = 11
*/

long long countDifferentPairs(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int val : arr) {
        freq[val]++;
    }
    
    long long result = 0;
    long long sum = 0;
    
    for (auto& [val, count] : freq) {
        result += (long long)count * sum;
        sum += count;
    }
    
    return result;
}


// ============================================================================
// PROBLEM 5: Horizontal Trapezoids (LC 3623)
// ============================================================================
/*
Given: 2D points
Count: horizontal trapezoids (parallel sides on different y-levels)

For each pair of y-levels:
  - Pick 2 points from level i: C(count[i], 2) ways
  - Pick 2 points from level j: C(count[j], 2) ways
  - Total: C(count[i], 2) * C(count[j], 2)
*/

int countHorizontalTrapezoids(vector<vector<int>>& points) {
    const int MOD = 1e9 + 7;
    
    // Count points at each y-coordinate
    map<int, int> yCount;
    for (auto& point : points) {
        yCount[point[1]]++;
    }
    
    long long result = 0;
    long long sum = 0;
    
    for (auto& [y, count] : yCount) {
        // C(count, 2) = count * (count-1) / 2
        long long edges = (long long)count * (count - 1) / 2;
        result = (result + edges * sum) % MOD;
        sum += edges;
    }
    
    return result;
}


// ============================================================================
// PROBLEM 6: Revenue from Product Interactions
// ============================================================================
/*
Given: Products with sales [s1, s2, s3]
Revenue from interaction between products i and j = sales[i] * sales[j]
Find: Total revenue from all product interactions

Example: sales = [100, 200, 150]
Revenue = 100*200 + 100*150 + 200*150 = 20000 + 15000 + 30000 = 65000
*/

long long totalRevenue(vector<int>& sales) {
    long long revenue = 0;
    long long sum = 0;
    
    for (int s : sales) {
        revenue += (long long)s * sum;
        sum += s;
    }
    
    return revenue;
}


// ============================================================================
// PROBLEM 7: Count Valid Combinations (With Condition)
// ============================================================================
/*
Given: array of integers
Count: pairs (i,j) where i < j and arr[i] + arr[j] is even

Insight: Sum is even if both are even or both are odd
Use running sum separately for even and odd!
*/

long long countEvenSumPairs(vector<int>& arr) {
    long long result = 0;
    long long evenSum = 0, oddSum = 0;
    
    for (int val : arr) {
        if (val % 2 == 0) {
            result += evenSum;  // Even pairs with even
            evenSum++;
        } else {
            result += oddSum;   // Odd pairs with odd
            oddSum++;
        }
    }
    
    return result;
}


// ============================================================================
// PROBLEM 8: Product of Array Except Self (Related)
// ============================================================================
/*
Not exactly running sum, but similar idea of cumulative operations
Given: [2, 3, 4, 5]
Output: product of all elements except self

This uses prefix and suffix products (related to running sum idea)
*/

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    
    // Left to right (prefix product)
    int prefix = 1;
    for (int i = 0; i < n; i++) {
        result[i] = prefix;
        prefix *= nums[i];
    }
    
    // Right to left (suffix product)
    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= suffix;
        suffix *= nums[i];
    }
    
    return result;
}


// ============================================================================
// TEST CASES
// ============================================================================

int main() {
    // Test 1: Pairwise product sum
    vector<int> arr1 = {2, 3, 5, 7};
    cout << "Test 1 - Pairwise Products: " << pairwiseProductSum(arr1) << endl;
    // Expected: 2*3 + 2*5 + 2*7 + 3*5 + 3*7 + 5*7 = 6+10+14+15+21+35 = 101
    
    // Test 2: Pick from groups
    vector<int> groups = {3, 2, 4};
    cout << "Test 2 - Pick from Groups: " << countPicksAcrossGroups(groups) << endl;
    // Expected: 3*2 + 3*4 + 2*4 = 6+12+8 = 26
    
    // Test 3: Shipping cost
    vector<int> quantities = {5, 3, 4};
    cout << "Test 3 - Shipping Cost: " << totalShippingCost(quantities) << endl;
    // Expected: 5*3 + 5*4 + 3*4 = 15+20+12 = 47
    
    // Test 4: Different pairs
    vector<int> arr2 = {1, 1, 1, 2, 2, 3};
    cout << "Test 4 - Different Pairs: " << countDifferentPairs(arr2) << endl;
    // Expected: 3*2 + 3*1 + 2*1 = 6+3+2 = 11
    
    // Test 5: Horizontal trapezoids
    vector<vector<int>> points = {{1,1}, {2,1}, {3,1}, {1,2}, {2,2}, {3,2}};
    cout << "Test 5 - Horizontal Trapezoids: " << countHorizontalTrapezoids(points) << endl;
    // Expected: C(3,2) * C(3,2) = 3 * 3 = 9
    
    // Test 6: Revenue
    vector<int> sales = {100, 200, 150};
    cout << "Test 6 - Total Revenue: " << totalRevenue(sales) << endl;
    // Expected: 100*200 + 100*150 + 200*150 = 65000
    
    // Test 7: Even sum pairs
    vector<int> arr3 = {2, 4, 6, 1, 3, 5};
    cout << "Test 7 - Even Sum Pairs: " << countEvenSumPairs(arr3) << endl;
    // Even: {2,4,6} → C(3,2) = 3 pairs
    // Odd: {1,3,5} → C(3,2) = 3 pairs
    // Total: 6
    
    return 0;
}

/*
============================================================================
KEY PATTERN RECOGNITION
============================================================================

When you see:
  ✓ "Count pairs/combinations"
  ✓ "Sum of products of pairs"
  ✓ "Ways to pick from different groups"
  ✓ "Total interaction/cost between items"
  ✓ O(n²) nested loops that can be avoided

Think: RUNNING SUM PATTERN!

Template:
  result = 0
  sum = 0
  for each element:
      result += element * sum
      sum += element

============================================================================
*/





