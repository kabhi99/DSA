# **STACK PATTERNS - COMPLETE GUIDE**

Master pattern for: All stack-based problems

### **TABLE OF CONTENTS**

SECTION A: BASIC STACK PATTERNS
A1. Stack Simulation (Path, State Tracking)
A2. Parentheses Matching
A3. String Processing with Stack
A4. Collision/Merging Problems

SECTION B: EXPRESSION EVALUATION
B1. Reverse Polish Notation (Postfix)
B2. Infix Expression Calculators
B3. Nested Structure Parsing (Decode String, etc.)

SECTION C: STACK DESIGN
C1. Min Stack / Max Stack
C2. Implement Stack Using Queues
C3. Implement Queue Using Stacks
C4. Frequency Stack / Special Stacks

SECTION D: MONOTONIC STACK (Next/Previous Greater/Smaller)
D1. What is Monotonic Stack?
D2. 4 Types of Monotonic Stacks
D3.  Universal Template 
D4. The 4 Core Problems
D5. Quick Reference Table
D6. Classic Problems with Solutions
D7. Pattern Recognition Guide

## **SECTION A: BASIC STACK PATTERNS**

### **A1. STACK SIMULATION (Path, State Tracking)**

**WHEN TO USE:**
- Tracking state/history that can be undone
- Processing paths (file system, directory navigation)
- Scoring systems with undo operations
- Validate sequences (push/pop order)

**PROBLEMS:**

- 1598. Crawler Log Folder 
> Track folder depth, "../" pops, "./" stays, else push

- 682. Baseball Game 
> Simulate score with undo (+, D, C operations)

- 946. Validate Stack Sequences 
> Simulate push/pop and verify if sequence is valid

- 71. Simplify Path 
> Stack for directory traversal, ".." pops, skip "."

- 1209. Find Permutation 
> Use stack to build lexicographically smallest permutation

### TEMPLATE - Path Processing:

```
string simplifyPath(string path) {
stack<string> st;                                     
stringstream ss(path);                                
string token;                                         

while (getline(ss, token, '/')) {                     
    if (token == "" || token == ".") continue;        
    if (token == "..") {                              
        if (!st.empty()) st.pop();  // Go up one level
    } else {                                          
        st.push(token);  // Enter directory           
    }                                                 
}                                                     

// Build result from stack                            
string result;                                        
while (!st.empty()) {                                 
    result = "/" + st.top() + result;                 
    st.pop();                                         
}                                                     
return result.empty() ? "/" : result;                 

}
```

### TEMPLATE - State Simulation (Baseball Game):

```cpp
int calPoints(vector<string>& ops) {
stack<int> st;                                    

for (string& op : ops) {                          
    if (op == "+") {                              
        int top = st.top(); st.pop();             
        int newTop = top + st.top();              
        st.push(top);                             
        st.push(newTop);                          
    } else if (op == "D") {                       
        st.push(2 * st.top());                    
    } else if (op == "C") {                       
        st.pop();                                 
    } else {                                      
        st.push(stoi(op));                        
    }                                             
}                                                 

int sum = 0;                                      
while (!st.empty()) { sum += st.top(); st.pop(); }
return sum;                                       

}
```

### **A2. PARENTHESES MATCHING**

**WHEN TO USE:**
- Validate balanced brackets/parentheses
- Count minimum additions to make valid
- Process nested structures

**PROBLEMS:**

- 20. Valid Parentheses 
> Push open brackets, pop and match for close brackets

- 921. Minimum Add to Make Parentheses Valid 
> Count unmatched open/close parentheses

- 1190. Reverse Substrings Between Each Pair of Parentheses 
> Stack of strings, reverse on closing paren

### TEMPLATE - Valid Parentheses:

```
bool isValid(string s) {
stack<char> st;                                                        
unordered_map<char, char> match = {{')', '('}, {']', '['}, {'}', '{'}};

for (char c : s) {                                                     
    if (c == '(' || c == '[' || c == '{') {                            
        st.push(c);                                                    
    } else {                                                           
        if (st.empty() || st.top() != match[c]) return false;          
        st.pop();                                                      
    }                                                                  
}                                                                      
return st.empty();                                                     

}
```

### TEMPLATE - Minimum Add to Make Valid:

```
int minAddToMakeValid(string s) {
int open = 0, close = 0;  // Unmatched counts    

for (char c : s) {                               
    if (c == '(') {                              
        open++;                                  
    } else {                                     
        if (open > 0) open--;  // Match with open
        else close++;          // Unmatched close
    }                                            
}                                                
return open + close;  // Total unmatched         

}
```

### **A3. STRING PROCESSING WITH STACK**

**WHEN TO USE:**
- Remove characters based on conditions
- Process adjacent duplicates
- Build result string with undo capability

**PROBLEMS:**

- 1544. Make The String Great 
> Remove adjacent chars that differ only in case (aA, Aa)

- 2390. Removing Stars From a String 
> Star removes previous character

- 1047. Remove All Adjacent Duplicates In String 
> Remove pairs of adjacent duplicates

- 1209. Remove All Adjacent Duplicates In String II 
> Remove k consecutive duplicates (need count tracking)

- 2696. Minimum String Length After Removing Substrings 
> Remove "AB" or "CD" substrings

- 3174. Clear Digits 
> Digit removes closest non-digit to its left

### TEMPLATE - Remove Adjacent (Make String Great):

```cpp
string makeGood(string s) {
string st;  // Use string as stack for easy result    

for (char c : s) {                                    
    if (!st.empty() && abs(st.back() - c) == 32) {    
        st.pop_back();  // Same letter, different case
    } else {                                          
        st.push_back(c);                              
    }                                                 
}                                                     
return st;                                            

}
```

### TEMPLATE - Remove K Adjacent Duplicates:

```
string removeDuplicates(string s, int k) {
stack<pair<char, int>> st;  // (char, count)                  

for (char c : s) {                                            
    if (!st.empty() && st.top().first == c) {                 
        st.top().second++;                                    
        if (st.top().second == k) st.pop();                   
    } else {                                                  
        st.push({c, 1});                                      
    }                                                         
}                                                             

string result;                                                
while (!st.empty()) {                                         
    result = string(st.top().second, st.top().first) + result;
    st.pop();                                                 
}                                                             
return result;                                                

}
```

### **A4. COLLISION / MERGING PROBLEMS**

**WHEN TO USE:**
- Objects moving in opposite directions may collide
- Merging based on relative properties (speed, size)
- Processing from one direction, comparing with accumulated state

**PROBLEMS:**

- 735. Asteroid Collision 
> Positive = right, Negative = left; larger wins collision

- 2751. Robot Collisions 
> Similar to asteroids but with health tracking

- 853. Car Fleet 
> Cars merge into fleet when faster catches slower

 **KEY INSIGHT**:
Stack represents "active/surviving" elements from one direction.
New element may collide with stack elements until it survives or dies.

### TEMPLATE - Asteroid Collision:

```cpp
vector<int> asteroidCollision(vector<int>& asteroids) {
stack<int> st;                                               

for (int ast : asteroids) {                                  
    bool alive = true;                                       

    // Collision: current going left, stack top going right  
    while (alive && ast < 0 && !st.empty() && st.top() > 0) {
        if (st.top() < -ast) {                               
            st.pop();  // Stack asteroid destroyed           
        } else if (st.top() == -ast) {                       
            st.pop();  // Both destroyed                     
            alive = false;                                   
        } else {                                             
            alive = false;  // Current asteroid destroyed    
        }                                                    
    }                                                        

    if (alive) st.push(ast);                                 
}                                                            

vector<int> result(st.size());                               
for (int i = st.size() - 1; i >= 0; i--) {                   
    result[i] = st.top(); st.pop();                          
}                                                            
return result;                                               

}
```

### TEMPLATE - Car Fleet:

```cpp
int carFleet(int target, vector<int>& position, vector<int>& speed) {
int n = position.size();                                         
vector<pair<int, double>> cars(n);                               

for (int i = 0; i < n; i++) {                                    
    double time = (double)(target - position[i]) / speed[i];     
    cars[i] = {position[i], time};                               
}                                                                

sort(cars.rbegin(), cars.rend());  // Sort by position descending

stack<double> st;  // Stack of fleet arrival times               
for (auto& [pos, time] : cars) {                                 
    if (st.empty() || time > st.top()) {                         
        st.push(time);  // New fleet (slower or first)           
    }                                                            
    // If time <= st.top(), car joins existing fleet             
}                                                                

return st.size();                                                

}
```

## **SECTION B: EXPRESSION EVALUATION**

### **B1. REVERSE POLISH NOTATION (POSTFIX)**

**WHEN TO USE:**
- Expression already in postfix form
- Operands come before operators

**PROBLEMS:**

- 150. Evaluate Reverse Polish Notation 

**TEMPLATE:**

```cpp
int evalRPN(vector<string>& tokens) {
stack<long long> st;                                                   

for (string& token : tokens) {                                         
    if (token == "+" || token == "-" || token == "*" || token == "/") {
        long long b = st.top(); st.pop();                              
        long long a = st.top(); st.pop();                              

        if (token == "+") st.push(a + b);                              
        else if (token == "-") st.push(a - b);                         
        else if (token == "*") st.push(a * b);                         
        else st.push(a / b);                                           
    } else {                                                           
        st.push(stoll(token));                                         
    }                                                                  
}                                                                      
return st.top();                                                       

}
```

### **B2. INFIX EXPRESSION CALCULATORS**

**WHEN TO USE:**
- Infix expressions with operator precedence
- May include parentheses

**PROBLEMS:**

- 224. Basic Calculator I  (+, -, parentheses only)
- 227. Basic Calculator II  (no parentheses, +,-,*,/)
- 772. Basic Calculator III  (with parentheses)
- 439. Ternary Expression Parser 

 **KEY INSIGHT**:
Two stacks: one for numbers, one for operators
Process operators based on precedence

### **SOLVED: Basic Calculator I (LC 224)** 

 PATTERN: Stack for parentheses + running sum
 SERIES: Calculator I (+ - parens) > II (+ - * /) > III (all + parens)

**KEY INSIGHT:**
- Process digits to form numbers
- Track sign (+1 or -1) and running result
- On '(': push result and sign to stack, reset
- On ')': pop and combine with saved result

```
int calculate(string s) {
stack<int> stk;                        
int result = 0, num = 0, sign = 1;     

for (char c : s) {                     
    if (isdigit(c)) {                  
        num = num * 10 + (c - '0');    
    } else if (c == '+' || c == '-') { 
        result += sign * num;          
        num = 0;                       
        sign = (c == '+') ? 1 : -1;    
    } else if (c == '(') {             
        stk.push(result);              
        stk.push(sign);                
        result = 0;                    
        sign = 1;                      
    } else if (c == ')') {             
        result += sign * num;          
        num = 0;                       
        result *= stk.top(); stk.pop();
        result += stk.top(); stk.pop();
    }                                  
}                                      

return result + sign * num;            

}
// Time: O(N), Space: O(N)
```

### TEMPLATE - Basic Calculator II (No Parentheses):

```
int calculate(string s) {
stack<long long> st;                                 
char op = '+';                                       
long long num = 0;                                   

for (int i = 0; i <= s.size(); i++) {                
    char c = (i < s.size()) ? s[i] : '+';            

    if (isdigit(c)) {                                
        num = num * 10 + (c - '0');                  
    } else if (c != ' ') {                           
        // Process previous operator                 
        if (op == '+') st.push(num);                 
        else if (op == '-') st.push(-num);           
        else if (op == '*') { st.top() *= num; }     
        else if (op == '/') { st.top() /= num; }     

        op = c;                                      
        num = 0;                                     
    }                                                
}                                                    

long long result = 0;                                
while (!st.empty()) { result += st.top(); st.pop(); }
return result;                                       

}
```

### TEMPLATE - Basic Calculator III (With Parentheses):

```
// Use recursion for parentheses, or two stacks approach
int calculate(string s) {
int i = 0;        
return calc(s, i);

}

int calc(string& s, int& i) {
stack<long long> st;                                       
char op = '+';                                             
long long num = 0;                                         

while (i < s.size()) {                                     
    char c = s[i++];                                       

    if (isdigit(c)) {                                      
        num = num * 10 + (c - '0');                        
    } else if (c == '(') {                                 
        num = calc(s, i);  // Recurse for nested expression
    } else if (c == ')') {                                 
        break;  // End of current level                    
    } else if (c != ' ') {                                 
        if (op == '+') st.push(num);                       
        else if (op == '-') st.push(-num);                 
        else if (op == '*') { st.top() *= num; }           
        else if (op == '/') { st.top() /= num; }           
        op = c;                                            
        num = 0;                                           
    }                                                      
}                                                          

// Process last number                                     
if (op == '+') st.push(num);                               
else if (op == '-') st.push(-num);                         
else if (op == '*') { st.top() *= num; }                   
else if (op == '/') { st.top() /= num; }                   

long long result = 0;                                      
while (!st.empty()) { result += st.top(); st.pop(); }      
return result;                                             

}
```

### **B3. NESTED STRUCTURE PARSING**

**WHEN TO USE:**
- Nested brackets with operations at each level
- Need to "unwind" structure on closing bracket
- Each level has its own state

**PROBLEMS:**

- 394. Decode String  (e.g., "3[a2[c]]" > "accaccacc")
- 1106. Parsing A Boolean Expression 
- 726. Number of Atoms 
- 341. Flatten Nested List Iterator 

 **KEY INSIGHT**:
Stack saves "outer state" when entering nested level.
Pop and merge when exiting nested level.

### TEMPLATE - Decode String:

```
string decodeString(string s) {
stack<string> strStack;                              
stack<int> numStack;                                 
string curr = "";                                    
int num = 0;                                         

for (char c : s) {                                   
    if (isdigit(c)) {                                
        num = num * 10 + (c - '0');                  
    } else if (c == '[') {                           
        strStack.push(curr);   // Save current string
        numStack.push(num);    // Save repeat count  
        curr = "";                                   
        num = 0;                                     
    } else if (c == ']') {                           
        string temp = curr;                          
        curr = strStack.top(); strStack.pop();       
        int repeat = numStack.top(); numStack.pop(); 
        while (repeat--) curr += temp;               
    } else {                                         
        curr += c;                                   
    }                                                
}                                                    
return curr;                                         

}
```

### TEMPLATE - Parsing Boolean Expression:

```
bool parseBoolExpr(string expression) {
stack<char> st;                                                        

for (char c : expression) {                                            
    if (c == ',' || c == '(') continue;                                

    if (c != ')') {                                                    
        st.push(c);                                                    
    } else {                                                           
        bool hasTrue = false, hasFalse = false;                        
        while (st.top() != '!' && st.top() != '&' && st.top() != '|') {
            if (st.top() == 't') hasTrue = true;                       
            else hasFalse = true;                                      
            st.pop();                                                  
        }                                                              
        char op = st.top(); st.pop();                                  

        if (op == '!') st.push(hasFalse ? 't' : 'f');                  
        else if (op == '&') st.push(hasFalse ? 'f' : 't');             
        else st.push(hasTrue ? 't' : 'f');                             
    }                                                                  
}                                                                      
return st.top() == 't';                                                

}
```

## **SECTION C: STACK DESIGN**

### **C1. MIN STACK / MAX STACK**

**PROBLEMS:**

- 155. Min Stack 
- 716. Max Stack  (with popMax operation - needs more complex structure)

 **KEY INSIGHT**:
Store (value, current_min) pairs, or use auxiliary stack for min values.

### TEMPLATE - Min Stack:

```java
class MinStack {
stack<pair<int, int>> st;  // (value, min_so_far)
```

public:
```
void push(int val) {                                          
    int minVal = st.empty() ? val : min(val, st.top().second);
    st.push({val, minVal});                                   
}                                                             

void pop() { st.pop(); }                                      
int top() { return st.top().first; }                          
int getMin() { return st.top().second; }                      
```

```
};
```

### **C2-C3. IMPLEMENT STACK/QUEUE USING EACH OTHER**

**PROBLEMS:**

- 225. Implement Stack Using Queues 
- 232. Implement Queue Using Stacks 

### TEMPLATE - Stack Using Queues (One Queue):

```java
class MyStack {
queue<int> q;
```

public:
```
void push(int x) {                                     
    q.push(x);                                         
    // Rotate so new element is at front               
    for (int i = 0; i < q.size() - 1; i++) {           
        q.push(q.front());                             
        q.pop();                                       
    }                                                  
}                                                      
int pop() { int val = q.front(); q.pop(); return val; }
int top() { return q.front(); }                        
bool empty() { return q.empty(); }                     
```

```
};
```

### TEMPLATE - Queue Using Stacks (Amortized O(1)):

```java
class MyQueue {
stack<int> in, out;            

void transfer() {              
    if (out.empty()) {         
        while (!in.empty()) {  
            out.push(in.top());
            in.pop();          
        }                      
    }                          
}                              
```

public:
```
void push(int x) { in.push(x); }
int pop() { transfer(); int val = out.top(); out.pop(); return val; }
int peek() { transfer(); return out.top(); }
bool empty() { return in.empty() && out.empty(); }

};
```

### **C4. FREQUENCY STACK / ITERATOR DESIGN**

**PROBLEMS:**

- 895. Maximum Frequency Stack 
> Pop element with highest frequency (most recent if tie)

- 341. Flatten Nested List Iterator 
> Use stack to flatten nested structure lazily

### TEMPLATE - Maximum Frequency Stack:

```java
class FreqStack {
unordered_map<int, int> freq;           // value -> frequency
unordered_map<int, stack<int>> groups;  // frequency -> stack of values
int maxFreq = 0;
```

public:
```
void push(int val) {                       
    freq[val]++;                           
    maxFreq = max(maxFreq, freq[val]);     
    groups[freq[val]].push(val);           
}                                          

int pop() {                                
    int val = groups[maxFreq].top();       
    groups[maxFreq].pop();                 
    freq[val]--;                           
    if (groups[maxFreq].empty()) maxFreq--;
    return val;                            
}                                          
```

```
};
```

## **SECTION D: MONOTONIC STACK**

### **D1. WHAT IS MONOTONIC STACK?**

### **DEFINITION**

A stack that maintains elements in sorted order (increasing or decreasing).

WHY USE IT?
 Find next greater/smaller element > O(N) instead of O(N2)
 Find previous greater/smaller element > O(N)
 Solve rectangle/histogram problems efficiently

### **WHEN TO USE?** 

KEYWORDS in problem:
- "Next greater element"
- "Previous smaller element"
- "First element to the right/left that is..."
- "Maximum rectangle"
- "Trapping rain water"
- "Stock span"
- "Visibility" (who can see whom)

**PATTERN:**
For each element, need to find:
> First larger/smaller element to the right
> First larger/smaller element to the left

### **D2. 4 TYPES OF MONOTONIC STACKS**

Assumption: Stack grows from LEFT to RIGHT (right = top)

```
+----------------------------------------------------------------------------+
| Type 1: Strictly Increasing                                                |
|   Every element > previous element                                         |
|   [1, 4, 5, 8, 9]  < Top                                                   |
|                                                                            |
| Type 2: Non-Decreasing (Increasing with equals)                            |
|   Every element >= previous element                                        |
|   [1, 4, 5, 5, 8, 9, 9]  < Top                                             |
|                                                                            |
| Type 3: Strictly Decreasing                                                |
|   Every element < previous element                                         |
|   [9, 8, 5, 4, 1]  < Top                                                   |
|                                                                            |
| Type 4: Non-Increasing (Decreasing with equals)                            |
|   Every element <= previous element                                        |
|   [9, 9, 8, 5, 5, 4, 1]  < Top                                             |
+----------------------------------------------------------------------------+
```

### **D3. UNIVERSAL TEMPLATE** 

ONE template for all 4 problems! Change OPERATOR only.

```cpp
vector<int> monoStack(vector<int>& arr) {
stack<int> st;  // Store indices, not values!             
vector<int> result(arr.size(), -1);                       

for (int i = 0; i < arr.size(); i++) {                    
    // OPERATOR determines stack type!                    
    while (!st.empty() && arr[st.top()] OPERATOR arr[i]) {
        int idx = st.top();                               
        st.pop();                                         

        // NEXT processing: happens inside while loop     
        result[idx] = i;  // or arr[i]                    
    }                                                     

    // PREVIOUS processing: happens outside while loop    
    if (!st.empty()) {                                    
        // result[i] = st.top(); // or arr[st.top()]      
    }                                                     

    st.push(i);                                           
}                                                         

return result;                                            

}
```

**KEY POINTS:**

 Store INDICES in stack (not values) > easier to calculate distances
 NEXT problems > process inside while loop
 PREVIOUS problems > process outside while loop (after while)
 Change OPERATOR to change behavior

### **D4. THE 4 CORE PROBLEMS**

### **1. NEXT GREATER ELEMENT** 

PROBLEM: For each element, find first element to the RIGHT that is GREATER

**EXAMPLE:**
```
arr = [13, 8, 1, 5, 2, 5, 9, 7, 6, 12]
NGE = [-1, 9, 5, 9, 5, 9, 12, 12, 12, -1]
```

 **KEY INSIGHT**:
When we see a LARGER element, all smaller elements in stack have found
their "next greater". Pop them all and record the answer!

 **WHY IT WORKS**:
- Stack keeps elements in decreasing order (waiting for their answer)
- When current > stack top > stack top found its next greater!
- Pop and record answer for all smaller elements
- Current element joins the queue (waiting for ITS next greater)

**INTUITION:**
Think of people standing in line waiting to see who's taller to their right.
When a tall person arrives, everyone shorter in front can see them!

**TEMPLATE:**

```cpp
vector<int> nextGreater(vector<int>& arr) {
stack<int> st;                                       
vector<int> result(arr.size(), -1);                  

for (int i = 0; i < arr.size(); i++) {               
    // Pop elements SMALLER than current             
    while (!st.empty() && arr[st.top()] < arr[i]) {  
        int idx = st.top();                          
        st.pop();                                    
        result[idx] = arr[i];  // Next greater found!
    }                                                
    st.push(i);                                      
}                                                    

return result;                                       

}
```

STACK TYPE: Non-Increasing (Type 4)
OPERATOR: <
PROCESS: Inside while loop
TIME: O(N)  |  SPACE: O(N)

**COMMON MISTAKE:**
 Nested loops: O(N2) - checking every element to the right
 Monotonic stack: O(N) - each element pushed/popped once!

### **2. PREVIOUS GREATER ELEMENT**

PROBLEM: For each element, find first element to the LEFT that is GREATER

**EXAMPLE:**
```
arr = [13, 8, 1, 5, 2, 5, 9, 7, 6, 12]
PGE = [-1, 13, 8, 8, 5, 8, 13, 9, 7, 13]
```

 **KEY INSIGHT**:
After popping smaller/equal elements, whatever remains in stack is
the PREVIOUS greater element!

 **WHY IT WORKS**:
- We pop elements < current (they can't be previous greater)
- After popping, stack contains only elements > current
- Top of stack = closest (most recent) element that's greater

**INTUITION:**
Stack remembers "potential answers" from the left.
When current element arrives, we clean out everything that's too small.
What's left at the top is the answer!

**TEMPLATE:**

```cpp
vector<int> previousGreater(vector<int>& arr) {
stack<int> st;                                      
vector<int> result(arr.size(), -1);                 

for (int i = 0; i < arr.size(); i++) {              
    // Pop elements SMALLER OR EQUAL to current     
    while (!st.empty() && arr[st.top()] <= arr[i]) {
        st.pop();                                   
    }                                               

    // After while: top has previous greater element
    if (!st.empty()) {                              
        result[i] = arr[st.top()];                  
    }                                               

    st.push(i);                                     
}                                                   

return result;                                      

}
```

STACK TYPE: Strictly Decreasing (Type 3)
OPERATOR: <=
PROCESS: Outside while loop
TIME: O(N)  |  SPACE: O(N)

 **MEMORY AID**:
NEXT > Answer found INSIDE while (when popping)
PREVIOUS > Answer found OUTSIDE while (what remains)

### **3. NEXT SMALLER ELEMENT**

PROBLEM: For each element, find first element to the RIGHT that is SMALLER

 **KEY INSIGHT**:
Same logic as Next Greater, just flip the comparison!
Pop elements that are LARGER (they found their next smaller).

**TEMPLATE:**

```cpp
vector<int> nextSmaller(vector<int>& arr) {
stack<int> st;                                     
vector<int> result(arr.size(), -1);                

for (int i = 0; i < arr.size(); i++) {             
    // Pop elements GREATER than current           
    while (!st.empty() && arr[st.top()] > arr[i]) {
        int idx = st.top();                        
        st.pop();                                  
        result[idx] = arr[i];                      
    }                                              
    st.push(i);                                    
}                                                  

return result;                                     

}
```

STACK TYPE: Non-Decreasing (Type 2)
OPERATOR: >
PROCESS: Inside while loop

### **4. PREVIOUS SMALLER ELEMENT**

PROBLEM: For each element, find first element to the LEFT that is SMALLER

**TEMPLATE:**

```cpp
vector<int> previousSmaller(vector<int>& arr) {
stack<int> st;                                      
vector<int> result(arr.size(), -1);                 

for (int i = 0; i < arr.size(); i++) {              
    // Pop elements GREATER OR EQUAL to current     
    while (!st.empty() && arr[st.top()] >= arr[i]) {
        st.pop();                                   
    }                                               

    // After while: top has previous smaller element
    if (!st.empty()) {                              
        result[i] = arr[st.top()];                  
    }                                               

    st.push(i);                                     
}                                                   

return result;                                      

}
```

STACK TYPE: Strictly Increasing (Type 1)
OPERATOR: >=
PROCESS: Outside while loop

### **D5. QUICK REFERENCE TABLE** 

```
+--------------------+-----------------+----------+------------------+
| Problem            | Stack Type      | Operator | Process Where?   |
+--------------------+-----------------+----------+------------------+
| Next Greater       | Non-Increasing  | <        | Inside while     |
| Previous Greater   | Strict Decrease | <=       | Outside while    |
| Next Smaller       | Non-Decreasing  | >        | Inside while     |
| Previous Smaller   | Strict Increase | >=       | Outside while    |
+--------------------+-----------------+----------+------------------+
```

**MEMORY AID:**
NEXT > Process INSIDE while loop (when popping)
PREVIOUS > Process OUTSIDE while loop (after popping)

GREATER > Use Decreasing stack (pop smaller elements)
SMALLER > Use Increasing stack (pop greater elements)

### **D6. CLASSIC MONOTONIC STACK PROBLEMS**

### **PROBLEM: Next Greater Element II (LC 503)** - Circular Array

TWIST: Array is circular (last element wraps to first)

 **KEY INSIGHT**: Circular = Process array twice!
First pass handles most cases, second pass handles wrap-around.

 **WHY 2 PASSES WORK**:
Pass 1: Find NGE for elements whose answer is to their right
Pass 2: Handle elements whose NGE wrapped around from the start

SOLUTION: Run loop TWICE!

```cpp
vector<int> nextGreaterElements(vector<int>& nums) {
int n = nums.size();                                     
vector<int> result(n, -1);                               
stack<int> st;                                           

// Run loop twice for circular behavior                  
for (int j = 0; j < 2; j++) {                            
    for (int i = 0; i < n; i++) {                        
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];                  
            st.pop();                                    
        }                                                
        st.push(i);                                      
    }                                                    
}                                                        

return result;                                           

}
```

### **SOLVED: Next Greater Element III (LC 556)** 

 PATTERN: Next Permutation on digits of a number
 SERIES: NGE I (two arrays) > II (circular) > III (digit rearrangement)

**KEY INSIGHT:**
- Convert number to string of digits
- Apply Next Permutation algorithm (see Two Pointers)
- Check for 32-bit overflow

```
int nextGreaterElement(int n) {
string s = to_string(n);                                 
int len = s.size();                                      

int pivot = -1;                                          
for (int i = len - 2; i >= 0; i--) {                     
    if (s[i] < s[i + 1]) { pivot = i; break; }           
}                                                        
if (pivot == -1) return -1;                              

for (int i = len - 1; i > pivot; i--) {                  
    if (s[i] > s[pivot]) { swap(s[i], s[pivot]); break; }
}                                                        

reverse(s.begin() + pivot + 1, s.end());                 

long long result = stoll(s);                             
return result > INT_MAX ? -1 : result;                   

}
// Time: O(D), Space: O(D)  where D = number of digits
```

### **PROBLEM: Daily Temperatures (LC 739)** 

PROBLEM: How many days until warmer temperature?

 **KEY INSIGHT**: This is Next Greater Element with a twist!
Instead of returning the VALUE, return the DISTANCE (i - idx).

 **PATTERN RECOGNITION**:
"How many days/steps until..." > Next Greater/Smaller + Distance
Always think: Can I use monotonic stack here?

```cpp
vector<int> dailyTemperatures(vector<int>& temperatures) {
int n = temperatures.size();                                         
vector<int> result(n, 0);                                            
stack<int> st;                                                       

for (int i = 0; i < n; i++) {                                        
    while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
        int idx = st.top();                                          
        st.pop();                                                    
        result[idx] = i - idx;  // Number of days!                   
    }                                                                
    st.push(i);                                                      
}                                                                    

return result;                                                       

}
```

TIME: O(N)  |  SPACE: O(N)

**VARIATIONS OF THIS PATTERN:**
- Stock Span Problem > Previous Greater + Count
- Online Stock Span > Same with streaming data
- Sum of Subarray Minimums > Next/Prev Smaller

### **PROBLEM: Buildings With Ocean View (LC 1762)**

PROBLEM: Which buildings have no taller building to the right?

 **KEY INSIGHT**: Elements that remain in stack = NO next greater exists!

 **WHY IT WORKS**:
If a building gets popped > it has a taller building to the right
If it stays in stack > no taller building exists
Stack at end = all buildings with ocean view!

**CLEVER TRICK:**
We don't need to store result separately. The stack IS the answer!

```cpp
vector<int> findBuildings(vector<int>& heights) {
stack<int> st;                                              

for (int i = 0; i < heights.size(); i++) {                  
    // Pop buildings that are blocked by current building   
    while (!st.empty() && heights[st.top()] <= heights[i]) {
        st.pop();                                           
    }                                                       
    st.push(i);                                             
}                                                           

// Stack contains all buildings with ocean view!            
return vector<int>(st.begin(), st.end());                   

}
```

### **PROBLEM: Trapping Rain Water (LC 42)**  HARD

PROBLEM: Calculate trapped water between bars

 **KEY INSIGHT**: Water fills between left and right boundaries!
For each "valley", left boundary = previous greater, right = next greater.

 **WHY IT WORKS**:
When we pop element X:
- Previous greater (stack top) = left wall
- Current element = right wall
- Water fills the valley between walls, above height[X]

**BRILLIANT TRICK:**
Process valleys LAYER BY LAYER as we pop from stack!
Each pop calculates water for one "horizontal slice"

**VISUALIZATION:**
[0,1,0,2,1,0,1,3,2,1,2,1]
v       <water>

When at 2: Pop 0, left=1, right=2 > water fills here!

**ALTERNATIVE APPROACH:**
Two pointers (easier to understand): Track max_left, max_right

```cpp
int trap(vector<int>& height) {
stack<int> st;                                                     
int water = 0;                                                     

for (int i = 0; i < height.size(); i++) {                          
    while (!st.empty() && height[st.top()] <= height[i]) {         
        int mid = st.top();                                        
        st.pop();                                                  

        if (!st.empty()) {                                         
            // Left boundary = st.top()                            
            // Right boundary = i                                  
            // Bottom = height[mid]                                
            int h = min(height[st.top()], height[i]) - height[mid];
            int w = i - st.top() - 1;                              
            water += h * w;                                        
        }                                                          
    }                                                              
    st.push(i);                                                    
}                                                                  

return water;                                                      

}
```

TIME: O(N)  |  SPACE: O(N)

### **PROBLEM: Largest Rectangle in Histogram (LC 84)**  HARD

PROBLEM: Find largest rectangle area in histogram

 **KEY INSIGHT**: For each bar, extend left/right until shorter bar!
Previous/Next SMALLER define how far we can extend.

 **WHY IT WORKS**:
For bar at index i:
- Can extend left until first shorter bar > previous smaller
- Can extend right until first shorter bar > next smaller
- Width = (next_smaller - prev_smaller - 1)
- Area = height[i] x width

**BRILLIANT OBSERVATION:**
We want SMALLER (not greater) because we're finding boundaries!
Rectangle height limited by shortest bar in range.

**VISUALIZATION:**
```
heights = [2,1,5,6,2,3]
```

^

For bar 5: prev_smaller=1(idx 1), next_smaller=2(idx 4)
```
Width = 4-1-1 = 2, Area = 5x2 = 10
```

**COMMON MISTAKE:**
 Using next/previous GREATER (wrong direction!)
 Using next/previous SMALLER (boundaries!)

```cpp
int largestRectangleArea(vector<int>& heights) {
int n = heights.size();                                    
vector<int> nextSmaller(n, n);                             
vector<int> prevSmaller(n, -1);                            
stack<int> st;                                             

// Find next smaller and previous smaller                  
for (int i = 0; i < n; i++) {                              
    while (!st.empty() && heights[st.top()] > heights[i]) {
        nextSmaller[st.top()] = i;                         
        st.pop();                                          
    }                                                      
    if (!st.empty()) {                                     
        prevSmaller[i] = st.top();                         
    }                                                      
    st.push(i);                                            
}                                                          

// Calculate max area                                      
int maxArea = 0;                                           
for (int i = 0; i < n; i++) {                              
    int width = nextSmaller[i] - prevSmaller[i] - 1;       
    int area = heights[i] * width;                         
    maxArea = max(maxArea, area);                          
}                                                          

return maxArea;                                            

}
```

TIME: O(N)  |  SPACE: O(N)

**RELATED PROBLEMS:**
- Maximal Rectangle (2D version using this as subroutine!)
- Maximum Rectangle in Binary Matrix

### **PROBLEM: 132 Pattern (LC 456)**  HARD

PROBLEM: Find i < j < k where arr[i] < arr[k] < arr[j]

 **KEY INSIGHT**: Reframe as: "Find previous greater J for K, check if min before J < K"

 **WHY IT WORKS**:
Pattern 1-3-2 means: small, BIG, medium
- J = previous greater element (the "3")
- K = current element (the "2")
- I = minimum before J (the "1")
- Check: arr[I] < arr[K] < arr[J]

**CLEVER PREPROCESSING:**
Precompute minimum-so-far array!
```
minLeft[j] tells us the smallest element before index j.
```

**TRANSFORMATION:**
"132 pattern" > Previous Greater + Min Tracking
This shows monotonic stack's versatility!

```cpp
bool find132pattern(vector<int>& nums) {
int n = nums.size();                                  
vector<int> minLeft(n);                               
stack<int> st;                                        

// Precompute minimum to the left                     
minLeft[0] = nums[0];                                 
for (int i = 1; i < n; i++) {                         
    minLeft[i] = min(minLeft[i-1], nums[i]);          
}                                                     

// Find previous greater                              
for (int i = 0; i < n; i++) {                         
    while (!st.empty() && nums[st.top()] <= nums[i]) {
        st.pop();                                     
    }                                                 

    if (!st.empty()) {                                
        int j = st.top();                             
        // Check if minLeft[j] < nums[i] < nums[j]    
        if (minLeft[j] < nums[i]) {                   
            return true;                              
        }                                             
    }                                                 
    st.push(i);                                       
}                                                     

return false;                                         

}
```

### **PROBLEM: Number of Visible People (LC 1944)**

PROBLEM: How many people can each person see to their right?

 **KEY INSIGHT**: Count in TWO places!
1. Inside while: People you BLOCK (they see you before getting popped)
2. Outside while: First TALLER person (they can see you)

 **WHY IT WORKS**:
When person X arrives:
- All shorter people in stack can see X (inside while)
- First taller person in stack can see X (outside while)

**INTUITION:**
You block everyone shorter, but first taller person can see over you!

**BRILLIANT COUNTING:**
Each visibility is counted exactly once from the viewer's perspective.

```cpp
vector<int> canSeePersonsCount(vector<int>& heights) {
int n = heights.size();                                     
vector<int> result(n, 0);                                   
stack<int> st;                                              

for (int i = 0; i < n; i++) {                               
    // Count people blocked by current person (next greater)
    while (!st.empty() && heights[st.top()] <= heights[i]) {
        result[st.top()]++;  // They can see current person 
        st.pop();                                           
    }                                                       

    // Previous greater can also see current person         
    if (!st.empty()) {                                      
        result[st.top()]++;                                 
    }                                                       

    st.push(i);                                             
}                                                           

return result;                                              

}
```

### **D7. WHY O(N) TIME?** 

CONFUSION: "Nested loops = O(N2), right?"

 **KEY INSIGHT**: Each element is touched AT MOST TWICE!

**AMORTIZED ANALYSIS:**

For each element:
1. Pushed onto stack once > O(1)
2. Popped from stack once > O(1)
3. Compared when pushing > O(1)
4. Compared when popping > O(1)

Total operations per element = 4 (constant!)
Total for N elements = 4N = O(N) Y

**THE TRICK:**
While loop runs variable times, BUT total pops across ALL iterations = N
Each element is born once (pushed) and dies once (popped).

**PROOF BY COUNTING:**
Stack size < N always
Total pushes = N (one per element)
Total pops < N (can't pop more than pushed)
Total operations = 2N = O(N)

### **D8. PATTERN RECOGNITION GUIDE**

### **DECISION FLOWCHART**

Problem mentions "next/first to the right"?
```
                                                     |
+- YES > NEXT problem                                 
|        * Process inside while loop                  
|        * result[stackTop] = i (or arr[i])           
                                                     |
+- NO > "previous/first to the left"?                 
                                                     |
    +- YES > PREVIOUS problem                         
             * Process outside while loop             
             * result[i] = st.top() (or arr[st.top()])
```

Looking for GREATER or LARGER?
> Use DECREASING stack
> Pop SMALLER elements

Looking for SMALLER?
> Use INCREASING stack
> Pop GREATER elements

### **PROBLEM TO PATTERN MAPPING**

```
+----------------------------------+------------------------------------+
| Problem Type                     | Pattern                            |
+----------------------------------+------------------------------------+
| Next warmer day                  | Next Greater                       |
| Stock span                       | Previous Greater or Equal          |
| Buildings with view              | No Next Greater                    |
| Trapping water                   | Next + Previous Greater            |
| Largest rectangle                | Next + Previous Smaller            |
| Remove K digits                  | Monotonic Increasing               |
| 132 pattern                      | Previous Greater + Min tracking    |
| Visibility (who sees whom)       | Next + Previous Greater counting   |
+----------------------------------+------------------------------------+
```

### **COMMON VARIATIONS**

**Circular Array:**
> Run loop twice (2 x n iterations)
> LC 503: Next Greater Element II

**Distance/Count Instead of Value:**
> Return `i - idx` instead of `arr[i]`
> LC 739: Daily Temperatures

**Elements Remaining in Stack:**
> Those with no next greater/smaller
> LC 1762: Buildings with Ocean View

**Both Next AND Previous:**
> Combine both patterns in one loop
> LC 84: Largest Rectangle
> LC 42: Trapping Rain Water

### **COMMON PITFALLS & HOW TO AVOID** 

### MISTAKE 1: Storing values instead of indices

```
 stack.push(arr[i]);
 stack.push(i);
```

WHY: Need indices to calculate distances, handle duplicates correctly

### MISTAKE 2: Wrong operator (< vs <=)

For STRICT next greater:  Use <  (pop when equal)
For next greater or equal: Use <= (keep when equal)

### MISTAKE 3: Processing in wrong place

NEXT > Process INSIDE while (when popping)
PREVIOUS > Process OUTSIDE while (after popping)

### MISTAKE 4: Forgetting to push current element

Always push current index at the end of each iteration!

### MISTAKE 5: Wrong stack type

GREATER > Use DECREASING stack
SMALLER > Use INCREASING stack

Think: "I want greater, so I pop smaller" > decreasing stack

## **QUICK REFERENCE CHEAT SHEET** 

```
+-----------------------------------------------------------------------------+
|                          NEXT GREATER                                       |
+-----------------------------------------------------------------------------+
|  while (!st.empty() && arr[st.top()] < arr[i]) {                            |
|      result[st.top()] = arr[i];  // or i                                    |
|      st.pop();                                                              |
|  }                                                                          |
|  st.push(i);                                                                |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                       PREVIOUS GREATER                                      |
+-----------------------------------------------------------------------------+
|  while (!st.empty() && arr[st.top()] <= arr[i]) {                           |
|      st.pop();                                                              |
|  }                                                                          |
|  if (!st.empty()) result[i] = arr[st.top()];  // or st.top()                |
|  st.push(i);                                                                |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                        NEXT SMALLER                                         |
+-----------------------------------------------------------------------------+
|  while (!st.empty() && arr[st.top()] > arr[i]) {                            |
|      result[st.top()] = arr[i];                                             |
|      st.pop();                                                              |
|  }                                                                          |
|  st.push(i);                                                                |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                      PREVIOUS SMALLER                                       |
+-----------------------------------------------------------------------------+
|  while (!st.empty() && arr[st.top()] >= arr[i]) {                           |
|      st.pop();                                                              |
|  }                                                                          |
|  if (!st.empty()) result[i] = arr[st.top()];                                |
|  st.push(i);                                                                |
+-----------------------------------------------------------------------------+

===============================================================================
              **COMPLETE PROBLEM LIST BY CATEGORY**                            
===============================================================================

+-----------------------------------------------------------------------------+
|                     SECTION A: BASIC STACK PATTERNS                         |
+-----------------------------------------------------------------------------+
```

**A1. STACK SIMULATION (Path, State Tracking)**

- 1598. Crawler Log Folder 
- 682. Baseball Game 
- 946. Validate Stack Sequences 
- 71. Simplify Path 
- 484. Find Permutation 

**A2. PARENTHESES MATCHING**

- 20. Valid Parentheses 
- 921. Minimum Add to Make Parentheses Valid 
- 1190. Reverse Substrings Between Each Pair of Parentheses 

**A3. STRING PROCESSING WITH STACK**

- 1544. Make The String Great 
- 2390. Removing Stars From a String 
- 1047. Remove All Adjacent Duplicates In String 
- 1209. Remove All Adjacent Duplicates In String II 
- 2696. Minimum String Length After Removing Substrings 
- 3174. Clear Digits 

**A4. COLLISION / MERGING PROBLEMS**

- 735. Asteroid Collision 
- 2751. Robot Collisions 
- 853. Car Fleet 

```
+-----------------------------------------------------------------------------+
|                   SECTION B: EXPRESSION EVALUATION                          |
+-----------------------------------------------------------------------------+
```

**B1. REVERSE POLISH NOTATION (POSTFIX)**

- 150. Evaluate Reverse Polish Notation 

**B2. INFIX EXPRESSION CALCULATORS**

- 224. Basic Calculator I 
- 227. Basic Calculator II 
- 772. Basic Calculator III 
- 439. Ternary Expression Parser 

**B3. NESTED STRUCTURE PARSING**

- 394. Decode String 
- 1106. Parsing A Boolean Expression 
- 726. Number of Atoms 

```
+-----------------------------------------------------------------------------+
|                       SECTION C: STACK DESIGN                               |
+-----------------------------------------------------------------------------+
```

**C1. MIN STACK / MAX STACK**

- 155. Min Stack 
- 716. Max Stack 

**C2-C3. IMPLEMENT STACK/QUEUE**

- 225. Implement Stack Using Queues 
- 232. Implement Queue Using Stacks 

**C4. SPECIAL STACK DESIGNS**

- 895. Maximum Frequency Stack 
- 341. Flatten Nested List Iterator 

```
+-----------------------------------------------------------------------------+
|                    SECTION D: MONOTONIC STACK                               |
+-----------------------------------------------------------------------------+
```

**NEXT GREATER ELEMENT** 

- 496. Next Greater Element I 
- 503. Next Greater Element II (Circular) 
- 556. Next Greater Element III  (Next Permutation on digits)
- 739. Daily Temperatures 
- 901. Online Stock Span 
- 1019. Next Greater Node In Linked List 

**NEXT SMALLER ELEMENT (Discounts, Remove Digits)** 

- 1475. Final Prices With a Special Discount in a Shop 
- 402. Remove K Digits 
- 316. Remove Duplicate Letters 
- 962. Maximum Width Ramp 

**PREVIOUS SMALLER/GREATER** 

- 84. Largest Rectangle in Histogram 
- 85. Maximal Rectangle 
- 907. Sum of Subarray Minimums 
- 1856. Maximum Subarray Min-Product 

**TRAPPING WATER / AREA** 

- 42. Trapping Rain Water 
- 11. Container With Most Water  (Two Pointers preferred)
- 84. Largest Rectangle in Histogram 

**PATTERN MATCHING (132 Pattern)** 

- 456. 132 Pattern 

**SLIDING WINDOW + MONOTONIC** 

- 239. Sliding Window Maximum  (Monotonic Deque)
- 1438. Longest Continuous Subarray With Abs Diff < Limit 
- 862. Shortest Subarray with Sum at Least K 

**VISIBILITY / COUNTING** 

- 1944. Number of Visible People in a Queue 
- 1762. Buildings with Ocean View 

## **MASTER PROBLEM MAPPING TABLE**

```
+-------------------------------------------------+--------------------------------+
| Problem                                         | Category / Pattern             |
+-------------------------------------------------+--------------------------------+
| Crawler Log Folder                              | A1 - Path Simulation           |
| Baseball Game                                   | A1 - State Simulation          |
| Valid Parentheses                               | A2 - Parentheses Matching      |
| Implement Stack Using Queues                    | C2 - Stack Design              |
| Implement Queue using Stacks                    | C3 - Stack Design              |
| Final Prices With a Special Discount in a Shop  | D - Next Smaller               |
| Make The String Great                           | A3 - String Processing         |
| Min Stack                                       | C1 - Stack Design              |
| Evaluate Reverse Polish Notation                | B1 - Postfix Evaluation        |
| Removing Stars From a String                    | A3 - String Processing         |
| Validate Stack Sequences                        | A1 - Stack Simulation          |
| Asteroid Collision                              | A4 - Collision                 |
| Daily Temperatures                              | D - Next Greater               |
| Online Stock Span                               | D - Previous Greater           |
| Car Fleet                                       | A4 - Collision/Merging         |
| Simplify Path                                   | A1 - Path Processing           |
| Decode String                                   | B3 - Nested Parsing            |
| Remove K Digits                                 | D - Monotonic Increasing       |
| Remove All Adjacent Duplicates In String II     | A3 - String Processing         |
| Reverse Substrings Between Each Pair of Parens  | A2 - Parentheses               |
| Ternary Expression Parser                       | B2 - Expression Evaluation     |
| Find Permutation                                | A1 - Stack Simulation          |
| Minimum String Length After Removing Substrings | A3 - String Processing         |
| Clear Digits                                    | A3 - String Processing         |
| Minimum Add to Make Parentheses Valid           | A2 - Parentheses Matching      |
| Maximum Width Ramp                              | D - Monotonic Stack            |
| Basic Calculator I                              | B2 - Infix Evaluation          |
| Basic Calculator II                             | B2 - Infix Evaluation          |
| 132 Pattern                                     | D - Prev Greater + Min         |
| Flatten Nested List Iterator                    | C4 - Iterator Design           |
| Sum of Subarray Minimums                        | D - Next/Prev Smaller          |
| Maximum Frequency Stack                         | C4 - Frequency Stack           |
| Robot Collisions                                | A4 - Collision                 |
| Number of Visible People in a Queue             | D - Visibility/Counting        |
| Largest Rectangle In Histogram                  | D - Next/Prev Smaller          |
| Shortest Subarray with Sum at Least K           | D - Monotonic Deque            |
| Parsing A Boolean Expression                    | B3 - Nested Parsing            |
| Number of Atoms                                 | B3 - Nested Parsing            |
| Basic Calculator III                            | B2 - Infix + Parentheses       |
| Next Greater Element III                        | D - Next Permutation on Digits |
| Max Stack                                       | C1 - Stack Design              |
+-------------------------------------------------+--------------------------------+

+----------------------------------------------------------------------------------+
|                    MONOTONIC STACK GOLDEN RULES                                  |
+----------------------------------------------------------------------------------+
|                                                                                  |
|  1⃣  NEXT > Process INSIDE while loop (when popping)                             |
|  2⃣  PREVIOUS > Process OUTSIDE while loop (after popping)                       |
|  3⃣  GREATER > Use DECREASING stack (pop smaller)                                |
|  4⃣  SMALLER > Use INCREASING stack (pop greater)                                |
|  5⃣  Always store INDICES, not values!                                           |
|  6⃣  Circular array? Process 2*n elements with i % n                             |
|                                                                                  |
+----------------------------------------------------------------------------------+

+----------------------------------------------------------------------------------+
|                      STACK PATTERN DECISION TREE                                 |
+----------------------------------------------------------------------------------+
|                                                                                  |
|  Is it about Next/Previous Greater/Smaller?                                      |
|    YES > SECTION D: Monotonic Stack                                              |
|                                                                                  |
|  Is it about matching brackets/parentheses?                                      |
|    YES > SECTION A2: Parentheses Matching                                        |
|                                                                                  |
|  Is it about evaluating expressions (calculator)?                                |
|    YES > SECTION B: Expression Evaluation                                        |
|                                                                                  |
|  Is it about nested structures like "3[a2[b]]"?                                  |
|    YES > SECTION B3: Nested Structure Parsing                                    |
|                                                                                  |
|  Is it about collisions/merging (asteroids, cars)?                               |
|    YES > SECTION A4: Collision Problems                                          |
|                                                                                  |
|  Is it about path/directory navigation?                                          |
|    YES > SECTION A1: Path Processing                                             |
|                                                                                  |
|  Is it about removing adjacent duplicates/chars?                                 |
|    YES > SECTION A3: String Processing                                           |
|                                                                                  |
|  Is it about designing a special stack (Min/Max/Freq)?                           |
|    YES > SECTION C: Stack Design                                                 |
|                                                                                  |
+----------------------------------------------------------------------------------+

================================================================================    
                                **END**                                             
================================================================================    
```
