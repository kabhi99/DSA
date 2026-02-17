#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

/*
============================================================================
ESCAPE ANALYSIS & INVARIANT PATTERN - CODE EXAMPLES
============================================================================
*/

// ============================================================================
// EXAMPLE 1: Count Collisions on Road (LC 2211)
// Pattern: Boundary escape + invariant counting
// ============================================================================

int countCollisions(string directions) {
    int n = directions.length();
    
    // Find escapes
    int left = 0, right = n - 1;
    while (left < n && directions[left] == 'L') left++;
    while (right >= 0 && directions[right] == 'R') right--;
    
    if (left > right) return 0;
    
    // Count invariant: each moving car → 1 collision
    int collisions = 0;
    for (int i = left; i <= right; i++) {
        if (directions[i] != 'S') collisions++;
    }
    return collisions;
}


// ============================================================================
// EXAMPLE 2: Remove Outer Parentheses (LC 1021)
// Pattern: Depth tracking + boundary identification
// ============================================================================

string removeOuterParentheses(string s) {
    string result;
    int depth = 0;
    
    for (char c : s) {
        if (c == '(') {
            if (depth > 0) result += c;  // Not outermost
            depth++;
        } else {
            depth--;
            if (depth > 0) result += c;  // Not outermost
        }
    }
    return result;
}


// ============================================================================
// EXAMPLE 3: Min Deletions for Valid Parentheses (LC 1249)
// Pattern: Balance tracking + invariant counting
// ============================================================================

int minRemoveToMakeValid(string s) {
    int open = 0, deletions = 0;
    
    // Count unmatched ')'
    for (char c : s) {
        if (c == '(') {
            open++;
        } else if (c == ')') {
            if (open > 0) open--;
            else deletions++;  // Unmatched ')' → delete
        }
    }
    
    // Add unmatched '(' (these escape to the end)
    return deletions + open;
}


// ============================================================================
// EXAMPLE 4: Asteroid Collision (LC 735)
// Pattern: Stack for interaction + escape analysis
// ============================================================================

vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> st;
    
    for (int asteroid : asteroids) {
        bool destroyed = false;
        
        while (!st.empty() && asteroid < 0 && st.top() > 0) {
            // Collision: right-moving meets left-moving
            if (abs(asteroid) > st.top()) {
                st.pop();  // Right one destroyed
                continue;
            } else if (abs(asteroid) == st.top()) {
                st.pop();  // Both destroyed
            }
            destroyed = true;
            break;
        }
        
        if (!destroyed) st.push(asteroid);
    }
    
    // Convert stack to vector
    vector<int> result(st.size());
    for (int i = st.size() - 1; i >= 0; i--) {
        result[i] = st.top();
        st.pop();
    }
    return result;
}


// ============================================================================
// EXAMPLE 5: Remove Adjacent Duplicates (LC 1047)
// Pattern: Stack for cancellation
// ============================================================================

string removeDuplicates(string s) {
    string result;  // Use string as stack
    
    for (char c : s) {
        if (!result.empty() && result.back() == c) {
            result.pop_back();  // Cancel/remove
        } else {
            result.push_back(c);
        }
    }
    return result;
}


// ============================================================================
// EXAMPLE 6: Remove K Adjacent Duplicates (LC 1209)
// Pattern: Stack with count tracking
// ============================================================================

string removeDuplicates(string s, int k) {
    stack<pair<char, int>> st;  // {character, count}
    
    for (char c : s) {
        if (!st.empty() && st.top().first == c) {
            st.top().second++;
            if (st.top().second == k) {
                st.pop();  // Remove k duplicates
            }
        } else {
            st.push({c, 1});
        }
    }
    
    // Rebuild string
    string result;
    while (!st.empty()) {
        auto [ch, count] = st.top();
        st.pop();
        result = string(count, ch) + result;
    }
    return result;
}


// ============================================================================
// EXAMPLE 7: Cars Fleet Formation
// Pattern: Greedy with escape analysis
// ============================================================================

/*
Cars at positions going to target.
Cars catching up form a fleet (move together).
Count number of fleets reaching target.

Key: Car ahead acts as barrier. Cars behind merge into fleet.
Invariant: Slower car ahead → all behind merge into one fleet
*/

int carFleet(int target, vector<int>& position, vector<int>& speed) {
    int n = position.size();
    vector<pair<int, double>> cars;
    
    // Calculate time to reach target for each car
    for (int i = 0; i < n; i++) {
        double time = (double)(target - position[i]) / speed[i];
        cars.push_back({position[i], time});
    }
    
    // Sort by position (rightmost first)
    sort(cars.begin(), cars.end(), greater<>());
    
    int fleets = 0;
    double lastTime = 0;
    
    for (auto [pos, time] : cars) {
        if (time > lastTime) {
            // This car reaches later, forms new fleet
            fleets++;
            lastTime = time;
        }
        // Else: catches up to previous fleet
    }
    
    return fleets;
}


// ============================================================================
// PATTERN TEMPLATE
// ============================================================================

/*
GENERAL TEMPLATE FOR ESCAPE + INVARIANT PROBLEMS:

Step 1: Identify boundaries/escapes
───────────────────────────────────
int left = 0, right = n - 1;
while (left < n && escapes_left(arr[left])) left++;
while (right >= 0 && escapes_right(arr[right])) right--;

Step 2: Process active zone
────────────────────────────
int result = 0;
for (int i = left; i <= right; i++) {
    if (participates(arr[i])) {
        result += invariant_contribution(arr[i]);
    }
}

Step 3: Return result
─────────────────────
return result;


WHEN TO USE STACK:
──────────────────
- Elements cancel each other
- Need to track most recent
- Process in order but match/remove pairs
- Example: parentheses, asteroids, duplicates


WHEN TO USE SIMPLE COUNTING:
────────────────────────────
- Fixed contribution per element
- No complex interactions
- Just sum up contributions
- Example: collisions, deletions needed
*/


// ============================================================================
// TEST ALL EXAMPLES
// ============================================================================

int main() {
    cout << "=== ESCAPE ANALYSIS & INVARIANT PATTERN EXAMPLES ===\n\n";
    
    // Test 1: Collisions
    cout << "1. Collisions 'RLRSLL': " << countCollisions("RLRSLL") << endl;
    // Expected: 5
    
    // Test 2: Outer parentheses
    cout << "2. Remove Outer '(()())(())': " << removeOuterParentheses("(()())(())") << endl;
    // Expected: "()()()"
    
    // Test 3: Min deletions
    cout << "3. Min Remove 'lee(t(c)o)de)': " << minRemoveToMakeValid("lee(t(c)o)de)") << endl;
    // Expected: 1 (one extra ')')
    
    // Test 4: Asteroids
    vector<int> asteroids = {5, 10, -5};
    vector<int> result = asteroidCollision(asteroids);
    cout << "4. Asteroids [5,10,-5]: ";
    for (int a : result) cout << a << " ";
    cout << endl;
    // Expected: [5, 10]
    
    // Test 5: Remove duplicates
    cout << "5. Remove Duplicates 'abbaca': " << removeDuplicates("abbaca") << endl;
    // Expected: "ca"
    
    // Test 6: Remove K duplicates
    cout << "6. Remove K=2 'deeedbbcccbdaa': " << removeDuplicates("deeedbbcccbdaa", 2) << endl;
    // Expected: "aa" (or similar based on implementation)
    
    return 0;
}

/*
============================================================================
KEY TAKEAWAYS
============================================================================

1. RECOGNIZE THE PATTERN:
   - Simulation can be simplified
   - Escape analysis possible
   - Invariant exists

2. CHOOSE RIGHT TECHNIQUE:
   - Boundary trimming for escapes
   - Counting for invariants
   - Stack for cancellation
   - Balance for depth tracking

3. COMPLEXITY IMPROVEMENT:
   - O(n²) simulation → O(n) counting
   - Multiple passes → single pass
   - Complex state → simple counter

4. COMMON IN:
   - String manipulation
   - Collision problems
   - Matching/cancellation
   - Process optimization

Master this pattern and solve problems 10x faster! 🚀

============================================================================
*/




