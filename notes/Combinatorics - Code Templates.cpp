#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

/*
============================================================================
COMBINATORICS - ESSENTIAL CODE TEMPLATES
============================================================================
*/

// Helper: GCD function
long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// ============================================================================
// 1. PERMUTATIONS & COMBINATIONS
// ============================================================================

// Factorial (iterative)
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Permutation P(n, r) = n!/(n-r)!
long long permutation(int n, int r) {
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
    }
    return result;
}

// Combination C(n, r) = n!/(r! * (n-r)!)
long long combination(int n, int r) {
    if (r > n - r) r = n - r;  // Optimize: C(n,r) = C(n,n-r)
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

// Combination with Modulo (using factorial precomputation)
const int MOD = 1e9 + 7;
vector<long long> fact, inv_fact;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

void precomputeFactorials(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    
    // Inverse using Fermat's Little Theorem: a^(-1) = a^(p-2) mod p
    inv_fact[n] = modPow(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i+1] * (i+1)) % MOD;
    }
}

long long nCr_mod(int n, int r) {
    if (r > n || r < 0) return 0;
    return (fact[n] * inv_fact[r] % MOD) * inv_fact[n-r] % MOD;
}


// ============================================================================
// 2. PASCAL'S TRIANGLE
// ============================================================================

vector<vector<long long>> pascalTriangle(int n) {
    vector<vector<long long>> dp(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i].resize(i + 1);
        dp[i][0] = dp[i][i] = 1;
        for (int j = 1; j < i; j++) {
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }
    return dp;
}


// ============================================================================
// 3. CATALAN NUMBERS
// ============================================================================

// Method 1: Using recursion with memoization
long long catalan(int n) {
    if (n <= 1) return 1;
    vector<long long> dp(n + 1);
    dp[0] = dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] += dp[j] * dp[i-1-j];
        }
    }
    return dp[n];
}

// Method 2: Using binomial coefficient
long long catalan_formula(int n) {
    return combination(2*n, n) / (n + 1);
}


// ============================================================================
// 4. DERANGEMENTS
// ============================================================================

long long derangement(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    
    vector<long long> dp(n + 1);
    dp[0] = 1;
    dp[1] = 0;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = (i - 1) * (dp[i-1] + dp[i-2]);
    }
    return dp[n];
}


// ============================================================================
// 5. STARS AND BARS
// ============================================================================

// Distribute n identical items into k distinct bins (bins can be empty)
long long starsAndBars(int n, int k) {
    return combination(n + k - 1, k - 1);
}

// Distribute n items into k bins (each bin must have at least 1)
long long starsAndBarsNonEmpty(int n, int k) {
    if (n < k) return 0;
    return combination(n - 1, k - 1);
}


// ============================================================================
// 6. INCLUSION-EXCLUSION
// ============================================================================

// Example: Count numbers in [1,n] divisible by A or B
long long divisibleByAorB(long long n, long long a, long long b) {
    long long lcm_ab = (a * b) / gcd(a, b);
    return n/a + n/b - n/lcm_ab;
}

// Count numbers divisible by A or B or C
long long divisibleByAorBorC(long long n, long long a, long long b, long long c) {
    long long ab = (a * b) / gcd(a, b);
    long long ac = (a * c) / gcd(a, c);
    long long bc = (b * c) / gcd(b, c);
    long long abc = (ab * c) / gcd(ab, c);
    
    return n/a + n/b + n/c - n/ab - n/ac - n/bc + n/abc;
}


// ============================================================================
// 7. INTEGER PARTITIONS
// ============================================================================

int integerPartition(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[j] += dp[j - i];
        }
    }
    return dp[n];
}


// ============================================================================
// 8. RUNNING SUM PATTERN
// ============================================================================

// Sum of all pairwise products
long long pairwiseProductSum(vector<int>& arr) {
    long long result = 0, sum = 0;
    for (int val : arr) {
        result += (long long)val * sum;
        sum += val;
    }
    return result;
}


// ============================================================================
// 9. GRID PATH COUNTING
// ============================================================================

// Paths from (0,0) to (m,n) using only right and down moves
long long gridPaths(int m, int n) {
    return combination(m + n, m);
}

// With DP (useful if there are obstacles)
long long gridPathsDP(int m, int n) {
    vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 && j == 0) continue;
            if (i > 0) dp[i][j] += dp[i-1][j];
            if (j > 0) dp[i][j] += dp[i][j-1];
        }
    }
    return dp[m][n];
}


// ============================================================================
// 10. SUBSET COUNTING
// ============================================================================

// Count all non-empty subsets
long long countSubsets(int n) {
    return (1LL << n) - 1;  // 2^n - 1
}

// Count subsets with specific sum (0-1 knapsack variation)
int countSubsetsWithSum(vector<int>& arr, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    
    for (int num : arr) {
        for (int j = target; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }
    return dp[target];
}


// ============================================================================
// 11. ARRANGEMENT WITH REPETITIONS
// ============================================================================

// Arrange n items where n1 of type1, n2 of type2, etc.
// Formula: n! / (n1! * n2! * ... * nk!)
long long arrangeWithRepetitions(vector<int>& frequencies) {
    int total = 0;
    for (int freq : frequencies) total += freq;
    
    long long result = factorial(total);
    for (int freq : frequencies) {
        result /= factorial(freq);
    }
    return result;
}


// ============================================================================
// TEST CASES
// ============================================================================

int main() {
    cout << "=== COMBINATORICS TEMPLATES TESTS ===\n\n";
    
    // Test 1: Combinations
    cout << "C(5, 2) = " << combination(5, 2) << " (Expected: 10)\n";
    cout << "C(10, 3) = " << combination(10, 3) << " (Expected: 120)\n\n";
    
    // Test 2: Permutations
    cout << "P(5, 3) = " << permutation(5, 3) << " (Expected: 60)\n";
    cout << "5! = " << factorial(5) << " (Expected: 120)\n\n";
    
    // Test 3: Catalan Numbers
    cout << "Catalan(0) = " << catalan(0) << " (Expected: 1)\n";
    cout << "Catalan(3) = " << catalan(3) << " (Expected: 5)\n";
    cout << "Catalan(4) = " << catalan(4) << " (Expected: 14)\n\n";
    
    // Test 4: Derangements
    cout << "Derangement(3) = " << derangement(3) << " (Expected: 2)\n";
    cout << "Derangement(4) = " << derangement(4) << " (Expected: 9)\n\n";
    
    // Test 5: Stars and Bars
    cout << "Stars and Bars (5 items, 3 bins) = " << starsAndBars(5, 3) 
         << " (Expected: 21)\n\n";
    
    // Test 6: Running Sum
    vector<int> arr = {2, 3, 5, 7};
    cout << "Pairwise product sum [2,3,5,7] = " << pairwiseProductSum(arr)
         << " (Expected: 101)\n\n";
    
    // Test 7: Grid Paths
    cout << "Grid paths 2x3 = " << gridPaths(2, 3) << " (Expected: 10)\n\n";
    
    // Test 8: Inclusion-Exclusion
    cout << "Divisible by 2 or 3 in [1,100] = " << divisibleByAorB(100, 2, 3)
         << " (Expected: 67)\n\n";
    
    // Test 9: Integer Partitions
    cout << "Partitions of 4 = " << integerPartition(4) << " (Expected: 5)\n";
    cout << "Partitions of 5 = " << integerPartition(5) << " (Expected: 7)\n\n";
    
    // Test 10: Modular Combinations
    precomputeFactorials(100);
    cout << "C(10, 5) mod " << MOD << " = " << nCr_mod(10, 5) << " (Expected: 252)\n";
    
    return 0;
}

/*
============================================================================
QUICK REFERENCE
============================================================================

Problem Type                          Template to Use
────────────────                      ───────────────
Choose k from n (order doesn't matter) → combination(n, k)
Arrange k from n (order matters)       → permutation(n, k)
Distribute identical items             → starsAndBars(n, k)
Valid parentheses                      → catalan(n)
No element in position                 → derangement(n)
At least one property                  → inclusion-exclusion
Pairwise products/combinations         → running sum pattern
Paths in grid                          → combination(m+n, m) or DP
Subsets with property                  → DP or 2^n enumeration
Arrangements with repetitions          → n!/(n1!*n2!*...*nk!)

============================================================================
*/

