# **LINKED LIST - COMPLETE GUIDE**

### **TABLE OF CONTENTS**

1. Core Patterns & Templates (5 Patterns)
2. Pattern Recognition Guide
3. Key Problems with Solutions
4. Quick Revision Table
5. Golden Rules
6. Interview Cheat Codes
7. Complete Problem List by Category

## **PART 1: FIVE CORE PATTERNS**

### **PATTERN 1: REVERSAL**

 **MEMORY AID**: "**P**rev-**C**urr-**N**ext: save next, flip link, advance"

 USE WHEN: Reverse entire list, reverse in groups, palindrome check
 VISUALIZATION: 1>2>3>4  becomes  1<2<3<4

###  TEMPLATE:

```cpp
ListNode *prev = nullptr, *curr = head;

while (curr) {
ListNode* next = curr->next;  // Save next
```

curr->next = prev;            // Flip link
```
prev = curr;                  // Advance prev
curr = next;                  // Advance curr

}
```

### // prev is now the new head

**COMMON VARIATIONS:**
- Reverse entire list
- Reverse in k-groups
- Reverse between positions m and n
- Palindrome check (reverse second half)

KEY INSIGHT: Three variables - prev, curr, next - are all you need

### **PATTERN 2: SLOW & FAST POINTER**

 **MEMORY AID**: "**S**low 1x, **F**ast 2x - meet in the middle or detect a cycle"

 USE WHEN: Find middle, detect cycle, find nth from end
 VISUALIZATION: slow> fast>>

###  TEMPLATE (Find Middle):

```cpp
ListNode *slow = head, *fast = head;

while (fast && fast->next) {
slow = slow->next;
fast = fast->next->next;

}
// slow is at the middle
```

###  TEMPLATE (Gap of N):

```cpp
ListNode *slow = &dummy, *fast = &dummy;
for (int i = 0; i <= n; i++) fast = fast->next;

while (fast) {
slow = slow->next;
fast = fast->next;

}
```

### // slow is just before the target node

**COMMON VARIATIONS:**
- Middle of linked list
- Cycle detection (Floyd's algorithm) > See Two Pointers.txt
- Remove nth from end (fixed gap)
- Palindrome linked list (find middle + reverse)

KEY INSIGHT: When fast reaches end, slow is at middle (or n behind)

### **PATTERN 3: MERGE / SORT**

 **MEMORY AID**: "**D**ummy node + **T**ail pointer - compare, append, advance"

 USE WHEN: Merge two sorted lists, interleave lists, sort a linked list
 VISUALIZATION: L1: >  L2: > ... merged: >

###  TEMPLATE (Merge Two Sorted):

```cpp
ListNode dummy(0);
ListNode* tail = &dummy;

while (l1 && l2) {
if (l1->val <= l2->val) {
    tail->next = l1;     
    l1 = l1->next;       
} else {                 
    tail->next = l2;     
    l2 = l2->next;       
}                        
tail = tail->next;       

}
tail->next = l1 ? l1 : l2;
return dummy.next;
```

###  TEMPLATE (Merge Sort on Linked List):

```cpp
ListNode* sortList(ListNode* head) {
if (!head || !head->next) return head;                                    
// Find middle using slow/fast                                            
ListNode *slow = head, *fast = head->next;                                
while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
ListNode* mid = slow->next;                                               
slow->next = nullptr;         // Split into two halves                    
return merge(sortList(head), sortList(mid));                              

}
```

**COMMON VARIATIONS:**
- Merge two sorted lists
- Sort list (merge sort)
- Add two numbers (digit by digit with carry)
- Intersection point of two lists
- Merge K sorted lists (with heap) > See Heap & Kth Problems.txt

KEY INSIGHT: Dummy node eliminates all edge cases for the head

### **PATTERN 4: IN-PLACE MANIPULATION**

 **MEMORY AID**: "Rewire pointers, don't copy values (except the delete trick)"

 USE WHEN: Delete node, rotate, remove nth, odd-even rearrange
 VISUALIZATION: A>B>C  becomes  A>C  (delete B)

###  TEMPLATE (Delete Without Head Access):

```cpp
node->val = node->next->val;
ListNode* toDelete = node->next;
node->next = node->next->next;
delete toDelete;
```

###  TEMPLATE (Make Circular, Then Break):

```cpp
// Find tail
ListNode* tail = head;
while (tail->next) tail = tail->next;

// Make circular
tail->next = head;

// Walk to new break point, then break
for (int i = 0; i < steps; i++) tail = tail->next;
head = tail->next;
```

### tail->next = nullptr;

**COMMON VARIATIONS:**
- Delete node without head access
- Rotate list by k places
- Remove nth from end
- Remove duplicates from sorted/unsorted list
- Odd-even linked list

KEY INSIGHT: Linked list surgery - save references before cutting links

### **PATTERN 5: COMPLEX POINTER**

 **MEMORY AID**: "Extra pointers (random, child) > interleave or DFS to handle"

 USE WHEN: Copy with random pointer, flatten multilevel list
 VISUALIZATION: A>A'>B>B'>C>C' (interleave copies into original)

###  TEMPLATE (Interleave Copy):

```cpp
// Step 1: Insert copy after each original
Node* curr = head;
while (curr) {
Node* copy = new Node(curr->val);
copy->next = curr->next;
curr->next = copy;
curr = copy->next;

}

// Step 2: Set extra pointers using interleaved structure
curr = head;
while (curr) {
if (curr->random) curr->next->random = curr->random->next;
curr = curr->next->next;                                  

}

// Step 3: Separate the two lists
```

###  TEMPLATE (DFS Flatten):

```cpp
Node* curr = head;
while (curr) {
if (curr->child) {                         
    Node* next = curr->next;               
    Node* child = flatten(curr->child);    
    curr->next = child; child->prev = curr;
    curr->child = nullptr;                 
    Node* tail = child;                    
    while (tail->next) tail = tail->next;  
    tail->next = next;                     
    if (next) next->prev = tail;           
}                                          
curr = curr->next;                         

}
```

**COMMON VARIATIONS:**
- Copy list with random pointer (interleave OR hash map)
- Flatten a multilevel doubly linked list (DFS)

KEY INSIGHT: Interleaving embeds a mapping in the list itself - O(1) space

## PART 2: PATTERN RECOGNITION & APPROACH

###  HOW TO IDENTIFY WHICH PATTERN?

```
+------------------------------------------------------------------------------+
| Keywords/Clues              | Pattern                | Template              |
+-----------------------------+------------------------+-----------------------+
| "reverse list"              | Reversal               | prev-curr-next        |
| "reverse in k-group"        | Reversal               | count k, then flip    |
| "palindrome list"           | Reversal + Slow/Fast   | find mid, reverse     |
|                             |                        |                       |
| "middle of list"            | Slow & Fast            | slow 1x, fast 2x      |
| "nth from end"              | Slow & Fast (Gap)      | gap of n              |
| "cycle detection"           | Slow & Fast (Floyd's)  | See Two Pointers.txt  |
|                             |                        |                       |
| "merge sorted lists"        | Merge / Sort           | dummy + tail          |
| "sort linked list"          | Merge / Sort           | split + merge sort    |
| "add two numbers"           | Merge (with carry)     | dummy + carry         |
| "intersection point"        | Merge (equalize)       | switch heads          |
|                             |                        |                       |
| "delete node"               | In-Place Manipulation  | copy next, skip       |
| "rotate list"               | In-Place Manipulation  | circular + break      |
| "remove duplicates"         | In-Place Manipulation  | prev + skip dups      |
| "odd-even rearrange"        | In-Place Manipulation  | two chains + join     |
|                             |                        |                       |
| "copy random pointer"       | Complex Pointer        | interleave            |
| "flatten list"              | Complex Pointer        | DFS rewire            |
+-----------------------------+------------------------+-----------------------+
```

###  SYSTEMATIC APPROACH

### STEP 1: Identify Problem Type (30 seconds)

Ask:
o Need to reverse all or part of the list? > Reversal
o Need middle, cycle, or nth from end? > Slow & Fast
o Two lists to combine, compare, or sort one? > Merge / Sort
o Restructure pointers in-place? > In-Place Manipulation
o Extra pointers (random, child)? > Complex Pointer
o Combination (e.g., palindrome, reorder)? > Multiple patterns

### STEP 2: Choose Template (30 seconds)

Decision:
- Do I need a dummy node? (yes for merge, delete head, remove nth)
- Do I need prev/curr/next? (yes for reversal)
- Do I need slow/fast? (yes for middle, cycle, palindrome)
- Do I need carry? (yes for add two numbers)
- Do I need interleaving? (yes for copy random pointer)

### STEP 3: Handle Edge Cases (30 seconds)

o Empty list (head == nullptr)
o Single node
o Two nodes
o Removing the head node (use dummy!)
o Cycle present
o k > list length (for rotate/k-group)

### STEP 4: Implement (5 minutes)

1. Set up dummy/sentinel if needed
2. Initialize pointers
3. Traverse and rewire
4. Return correct head (often dummy.next)

## PART 3: KEY PROBLEMS WITH SOLUTIONS

### CATEGORY 1: REVERSAL

### 1. Reverse Linked List (LC 206) 

 PATTERN: Reversal (Iterative)
 TEMPLATE: prev-curr-next trio

**KEY INSIGHT:**
- At each node: save next, flip link to prev, advance both pointers
- prev starts as nullptr (new tail), curr starts as head
- After loop, prev is the new head

**WHY IT WORKS:**
- Each iteration reverses exactly one link
- We save next before flipping so we don't lose the rest of the list
- After N iterations, all links are flipped

**COMMON MISTAKES:**
 Forgetting to save next before flipping
 Returning curr instead of prev (curr is nullptr at end)
 Always return prev

```cpp
ListNode* reverseList(ListNode* head) {
ListNode* prev = nullptr;       
ListNode* curr = head;          
while (curr) {                  
    ListNode* next = curr->next;
    curr->next = prev;          
    prev = curr;                
    curr = next;                
}                               
return prev;                    

}
// Time: O(N), Space: O(1)
```

### 2. Reverse Nodes in k-Group (LC 25)  HARD

 PATTERN: Reversal (Recursive k-Group)
 TEMPLATE: Count k nodes, reverse group, recurse on rest

**KEY INSIGHT:**
- First check if k nodes remain - if not, return head unchanged
- Reverse exactly k nodes using the standard reversal
- The old head (now tail of reversed group) links to the result of recursing on the rest

**WHY IT WORKS:**
- Recursive structure: reverse one group > connect to next group
- Base case: fewer than k nodes > no reversal
- After reversing k nodes, head->next points to reverseKGroup(remaining)

**EDGE CASES:**
- Last group has fewer than k nodes > leave as-is
- k = 1 > no change
- k = list length > reverse entire list

```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
ListNode* curr = head;                                   
int count = 0;                                           
while (curr && count < k) { curr = curr->next; count++; }
if (count < k) return head;                              

ListNode* prev = reverseKGroup(curr, k);                 
curr = head;                                             
for (int i = 0; i < k; i++) {                            
    ListNode* next = curr->next;                         
    curr->next = prev;                                   
    prev = curr;                                         
    curr = next;                                         
}                                                        
return prev;                                             

}
// Time: O(N), Space: O(N/k) recursion stack
```

### 3. Palindrome Linked List (LC 234) 

 PATTERN: Slow & Fast + Reversal (Two Patterns Combined!)
 TEMPLATE: Find middle > reverse second half > compare

**KEY INSIGHT:**
- Can't index backwards in a singly linked list
- Solution: reverse the second half, then compare both halves
- Uses BOTH slow/fast (to find middle) AND reversal

**WHY IT WORKS:**
- Slow/fast gives us the midpoint in one pass
- Reversing second half lets us compare from both ends
- For odd length, middle node is skipped naturally

**COMMON MISTAKES:**
 Not handling odd-length lists correctly
 Forgetting that slow stops at second middle for even-length
 Compare until reversed half (prev) runs out

```cpp
bool isPalindrome(ListNode* head) {
ListNode* slow = head, *fast = head;                                      
while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }

ListNode* prev = nullptr;                                                 
while (slow) {                                                            
    ListNode* next = slow->next;                                          
    slow->next = prev;                                                    
    prev = slow;                                                          
    slow = next;                                                          
}                                                                         

while (prev) {                                                            
    if (head->val != prev->val) return false;                             
    head = head->next;                                                    
    prev = prev->next;                                                    
}                                                                         
return true;                                                              

}
// Time: O(N), Space: O(1)
```

### CATEGORY 2: SLOW & FAST POINTER

### 4. Middle of Linked List (LC 876) 

 PATTERN: Slow & Fast
 TEMPLATE: slow +1, fast +2, slow lands on middle

**KEY INSIGHT:**
- Fast moves at 2x speed of slow
- When fast reaches the end, slow is at the midpoint
- For even-length list, returns the SECOND middle node

**WHY IT WORKS:**
- fast travels 2N steps while slow travels N steps
- N = half the list length = the middle position

**GOLDEN RULE:**
> "while (fast && fast->next)" - check BOTH to avoid null dereference

```cpp
ListNode* middleNode(ListNode* head) {
ListNode* slow = head, *fast = head;
while (fast && fast->next) {        
    slow = slow->next;              
    fast = fast->next->next;        
}                                   
return slow;                        

}
// Time: O(N), Space: O(1)
```

### 5. Remove Nth Node From End of List (LC 19) 

 PATTERN: Two Pointer with Fixed Gap
 TEMPLATE: Advance fast n+1 steps, then move both until fast is null
↗ CROSS-REFERENCE: See Two Pointers.txt for the general two-pointer framework

**KEY INSIGHT:**
- Maintain a gap of exactly n+1 between fast and slow
- When fast reaches nullptr, slow is just BEFORE the target
- Dummy node handles the edge case of removing the head

**WHY IT WORKS:**
- Gap of (n+1) means slow ends up at position (length - n - 1)
- That's the node right before the one we want to delete
- Single pass through the list

**EDGE CASES:**
- Remove head > dummy node saves us
- n = list length > remove first node

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
ListNode dummy(0);                             
dummy.next = head;                             
ListNode *fast = &dummy, *slow = &dummy;       
for (int i = 0; i <= n; i++) fast = fast->next;
while (fast) {                                 
    slow = slow->next;                         
    fast = fast->next;                         
}                                              
ListNode* toDelete = slow->next;               
slow->next = slow->next->next;                 
delete toDelete;                               
return dummy.next;                             

}
// Time: O(N), Space: O(1)
```

### 6. Intersection of Two Linked Lists (LC 160) 

 PATTERN: Two Pointer (Length Equalization)
 TEMPLATE: Swap to other head on reaching null

KEY INSIGHT (BRILLIANT!):
- Two pointers traverse both lists
- When one reaches null, redirect it to the OTHER list's head
- They meet at intersection because total distance becomes equal!

**WHY IT WORKS:**
- Pointer A travels: lenA + lenB (A's list then B's list)
- Pointer B travels: lenB + lenA (B's list then A's list)
- lenA + lenB == lenB + lenA > they align at the intersection
- If no intersection, both become nullptr at the same time

**MATHEMATICAL PROOF:**
Let a = unique part of A, b = unique part of B, c = shared part
- A travels: a + c + b
- B travels: b + c + a
- Both equal a + b + c > they meet at start of c!

```cpp
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
ListNode* a = headA, *b = headB;
while (a != b) {                
    a = a ? a->next : headB;    
    b = b ? b->next : headA;    
}                               
return a;                       

}
// Time: O(N+M), Space: O(1)
```

### 7. Linked List Cycle (LC 141) - CROSS-REFERENCE

 PATTERN: Floyd's Cycle Detection (Slow & Fast)
 FULL SOLUTION: See Two Pointers.txt > Problem 7

**QUICK RECAP:**
- slow moves 1 step, fast moves 2 steps
- If they meet > cycle exists
- If fast hits null > no cycle

```cpp
bool hasCycle(ListNode *head) {
ListNode *slow = head, *fast = head;
while (fast && fast->next) {        
    slow = slow->next;              
    fast = fast->next->next;        
    if (slow == fast) return true;  
}                                   
return false;                       

}
// Time: O(N), Space: O(1)
```

### 8. Linked List Cycle II (LC 142) - CROSS-REFERENCE

 PATTERN: Floyd's Algorithm Extended
 FULL SOLUTION: See Two Pointers.txt > Problem 8

**QUICK RECAP:**
- Phase 1: Detect meeting point with slow/fast
- Phase 2: Reset slow to head, move both at same speed
- They meet at cycle start (L = nC - k proof)

```cpp
ListNode *detectCycle(ListNode *head) {
ListNode *slow = head, *fast = head;
while (fast && fast->next) {        
    slow = slow->next;              
    fast = fast->next->next;        
    if (slow == fast) {             
        slow = head;                
        while (slow != fast) {      
            slow = slow->next;      
            fast = fast->next;      
        }                           
        return slow;                
    }                               
}                                   
return nullptr;                     

}
// Time: O(N), Space: O(1)
```

### 9. Reorder List (LC 143) - CROSS-REFERENCE

 PATTERN: Slow & Fast + Reversal + Merge (Three Patterns Combined!)
 FULL SOLUTION: See Two Pointers.txt > Problem 22

**QUICK RECAP:**
- Step 1: Find middle using slow/fast
- Step 2: Reverse second half
- Step 3: Merge two halves alternately

```cpp
void reorderList(ListNode* head) {
if (!head || !head->next) return;                  
ListNode *slow = head, *fast = head;               
while (fast->next && fast->next->next) {           
    slow = slow->next;                             
    fast = fast->next->next;                       
}                                                  
ListNode *second = slow->next;                     
slow->next = nullptr;                              
ListNode *prev = nullptr;                          
while (second) {                                   
    ListNode *temp = second->next;                 
    second->next = prev;                           
    prev = second;                                 
    second = temp;                                 
}                                                  
second = prev;                                     
ListNode *first = head;                            
while (second) {                                   
    ListNode *t1 = first->next, *t2 = second->next;
    first->next = second;                          
    second->next = t1;                             
    first = t1;                                    
    second = t2;                                   
}                                                  

}
// Time: O(N), Space: O(1)
```

### CATEGORY 3: MERGE / SORT

### 10. Merge Two Sorted Lists (LC 21) 

 PATTERN: Merge (Dummy + Tail)
 TEMPLATE: Compare heads, append smaller, advance

**KEY INSIGHT:**
- Dummy node as sentinel - avoids special-casing the first node
- Tail pointer always points to the last node of the merged list
- After main loop, attach whichever list has remaining nodes

**WHY IT WORKS:**
- Both lists are sorted > smallest unprocessed element is always at a head
- Appending the smaller head maintains sorted order
- tail->next = l1 ? l1 : l2 handles remaining elements in one line

**GOLDEN RULE:**
> Dummy node is the #1 trick for linked list merge problems

```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
ListNode dummy(0);                                             
ListNode* tail = &dummy;                                       
while (l1 && l2) {                                             
    if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
    else { tail->next = l2; l2 = l2->next; }                   
    tail = tail->next;                                         
}                                                              
tail->next = l1 ? l1 : l2;                                     
return dummy.next;                                             

}
// Time: O(N+M), Space: O(1)
```

### 11. Sort List (LC 148) 

 PATTERN: Merge / Sort (Merge Sort on Linked List)
 TEMPLATE: Find middle (slow/fast) > split > recurse > merge

**KEY INSIGHT:**
- Merge sort is ideal for linked lists - no random access needed
- Find middle with slow/fast, split at middle
- Recursively sort both halves, then merge
- fast starts at head->next (not head) to get the FIRST middle for even-length

**WHY IT WORKS:**
- Splitting at the middle gives balanced halves > O(log N) depth
- Merge of two sorted lists is O(N) using the merge template
- Total: O(N log N) - same as array merge sort

**EDGE CASES:**
- Empty list or single node > return as-is (base case)
- Two nodes > split into two singles, merge them

```cpp
ListNode* sortList(ListNode* head) {
if (!head || !head->next) return head;                                    
ListNode* slow = head, *fast = head->next;                                
while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
ListNode* mid = slow->next;                                               
slow->next = nullptr;                                                     
ListNode* left = sortList(head);                                          
ListNode* right = sortList(mid);                                          
return mergeTwoLists(left, right);                                        

}
// Time: O(N log N), Space: O(log N) recursion stack
```

### 12. Add Two Numbers (LC 2) 

 PATTERN: Merge (with Carry)
 TEMPLATE: Traverse both lists, sum digits + carry, create new nodes

**KEY INSIGHT:**
- Numbers are stored in reverse order > process left to right = least significant first
- Carry propagation is natural (just like hand addition)
- Loop continues while ANY of l1, l2, or carry is non-zero

**WHY IT WORKS:**
- Reverse storage means we add digits in the correct order
- carry = sum / 10, digit = sum % 10 - standard arithmetic
- "while (l1 || l2 || carry)" handles unequal lengths and final carry

**COMMON MISTAKES:**
 Forgetting the final carry (e.g., 999 + 1 = 1000)
 Not checking l1/l2 before accessing val
 Always include carry in the loop condition

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
ListNode dummy(0);                            
ListNode* curr = &dummy;                      
int carry = 0;                                
while (l1 || l2 || carry) {                   
    int sum = carry;                          
    if (l1) { sum += l1->val; l1 = l1->next; }
    if (l2) { sum += l2->val; l2 = l2->next; }
    carry = sum / 10;                         
    curr->next = new ListNode(sum % 10);      
    curr = curr->next;                        
}                                             
return dummy.next;                            

}
// Time: O(max(N,M)), Space: O(max(N,M))
```

### CATEGORY 4: IN-PLACE MANIPULATION

### 13. Delete Node in a Linked List (LC 237)

 PATTERN: In-Place Manipulation (Copy & Skip)
 TEMPLATE: Copy next node's value, then bypass it

KEY INSIGHT (CLEVER TRICK!):
- You are NOT given access to head - only the node to delete
- Can't find the previous node > can't do normal deletion
- Instead: copy the NEXT node's value into this node, then delete next

**WHY IT WORKS:**
- Effectively "becomes" the next node by copying its value
- Then removes the actual next node (which we CAN access)
- The node "to delete" lives on with a new value

**CONSTRAINTS:**
- Won't work on the LAST node (no next to copy from)
- Problem guarantees the node is NOT the tail

```cpp
void deleteNode(ListNode* node) {
node->val = node->next->val;
node->next = node->next->next;

}
// Time: O(1), Space: O(1)
```

### 14. Rotate List (LC 61)

 PATTERN: In-Place Manipulation (Circular + Break)
 TEMPLATE: Find length, make circular, walk to break point, break

**KEY INSIGHT:**
- Rotating right by k is the same as: make circular > break at (len - k)
- First normalize k (k %= len) to handle k > len
- New head is at position (len - k) from current head

**WHY IT WORKS:**
- Making the list circular removes the "end" concept
- Walking (len - k) from the current tail finds the new tail
- Breaking the circle there gives the rotated list

**EDGE CASES:**
- k == 0 or k % len == 0 > no rotation needed
- Single node > return as-is

```cpp
ListNode* rotateRight(ListNode* head, int k) {
if (!head || !head->next || k == 0) return head;    
int len = 1;                                        
ListNode* tail = head;                              
while (tail->next) { tail = tail->next; len++; }    
k %= len;                                           
if (k == 0) return head;                            
tail->next = head;                                  
for (int i = 0; i < len - k; i++) tail = tail->next;
head = tail->next;                                  
tail->next = nullptr;                               
return head;                                        

}
// Time: O(N), Space: O(1)
```

### CATEGORY 5: COMPLEX POINTER

### 15. Copy List with Random Pointer (LC 138) 

 PATTERN: Complex Pointer (Interleave Technique)
 TEMPLATE: Interleave copies > set random > separate lists

KEY INSIGHT (BRILLIANT - O(1) Space Without HashMap!):
- Step 1: Insert a copy of each node right after it
Original: A > B > C
After:    A > A' > B > B' > C > C'

- Step 2: Set random pointers using the interleaved structure
If A.random = C, then A'.random = C.next (which is C')

- Step 3: Separate the two interleaved lists

**WHY IT WORKS:**
- Interleaving creates a mapping: original.next = its copy
- This acts as a "hash map" embedded in the list itself
- Random pointers can be set in O(1) per node: curr.next.random = curr.random.next

ALTERNATIVE: HashMap approach is simpler (O(N) space)
```
map<Node*, Node*> copies;  // original > copy
```

Node* copyRandomList(Node* head) {
```
if (!head) return nullptr;                                    
// Step 1: Interleave copies                                  
Node* curr = head;                                            
while (curr) {                                                
    Node* copy = new Node(curr->val);                         
    copy->next = curr->next;                                  
    curr->next = copy;                                        
    curr = copy->next;                                        
}                                                             
// Step 2: Set random pointers                                
curr = head;                                                  
while (curr) {                                                
    if (curr->random) curr->next->random = curr->random->next;
    curr = curr->next->next;                                  
}                                                             
// Step 3: Separate lists                                     
Node dummy(0);                                                
Node* copyTail = &dummy;                                      
curr = head;                                                  
while (curr) {                                                
    copyTail->next = curr->next;                              
    copyTail = copyTail->next;                                
    curr->next = curr->next->next;                            
    curr = curr->next;                                        
}                                                             
return dummy.next;                                            
```

```
}
// Time: O(N), Space: O(1) excluding output
```

### 16. Flatten a Multilevel Doubly Linked List (LC 430)

 PATTERN: Complex Pointer (DFS Flattening)
 TEMPLATE: When child found > flatten child, splice into main list

**KEY INSIGHT:**
- Whenever a node has a child, recursively flatten that child list
- Insert the flattened child between the current node and its next
- Walk to the tail of the flattened child to reconnect with next

**WHY IT WORKS:**
- DFS naturally processes deepest children first
- Splicing maintains the correct order: parent > child subtree > next
- After flattening, all child pointers are null

REWIRING STEPS (when curr has a child):
1. Save curr->next
2. Flatten child recursively
3. curr->next = child, child->prev = curr
4. Find tail of flattened child
5. tail->next = saved next, next->prev = tail
6. curr->child = nullptr

Node* flatten(Node* head) {
```
Node* curr = head;                           
while (curr) {                               
    if (curr->child) {                       
        Node* next = curr->next;             
        Node* child = flatten(curr->child);  
        curr->next = child;                  
        child->prev = curr;                  
        curr->child = nullptr;               
        Node* tail = child;                  
        while (tail->next) tail = tail->next;
        tail->next = next;                   
        if (next) next->prev = tail;         
    }                                        
    curr = curr->next;                       
}                                            
return head;                                 
```

```
}
// Time: O(N), Space: O(depth) recursion stack
```

## PART 4: QUICK REVISION TABLE

```
+-----------------------------------------------------------------------------+
|                         PATTERN SELECTION GUIDE                             |
+-------------------------+-----------------------+---------------------------+
| Problem Clue            | Pattern               | Template                  |
+-------------------------+-----------------------+---------------------------+
| Reverse list/part       | Reversal              | prev-curr-next            |
| Reverse in groups       | Reversal              | count k, flip, recurse    |
| Palindrome list         | Reversal + Slow/Fast  | mid > reverse > compare   |
|                         |                       |                           |
| Find middle             | Slow & Fast           | slow 1x, fast 2x          |
| Nth from end            | Slow & Fast (Gap)     | gap of n+1                |
| Cycle detect            | Slow & Fast (Floyd's) | See Two Pointers.txt      |
| Intersection point      | Two Pointer (Switch)  | swap to other head        |
|                         |                       |                           |
| Merge sorted lists      | Merge / Sort          | dummy + tail              |
| Sort linked list        | Merge / Sort          | split + merge sort        |
| Add two numbers         | Merge (carry)         | sum + carry, new nodes    |
|                         |                       |                           |
| Delete without head     | In-Place Manipulation | copy next, skip next      |
| Rotate list             | In-Place Manipulation | circular + break          |
| Remove duplicates       | In-Place Manipulation | prev + skip               |
|                         |                       |                           |
| Copy random pointer     | Complex Pointer       | interleave + separate     |
| Flatten multilevel      | Complex Pointer       | DFS splice                |
+-------------------------+-----------------------+---------------------------+

+-----------------------------------------------------------------------------+
|                         CRITICAL TEMPLATES                                  |
+-----------------------------------------------------------------------------+
|                                                                             |
| 1. REVERSAL (Three-Variable Dance)                                          |
|    ----------------------------------------------------------------         |
|    ListNode *prev = nullptr, *curr = head;                                  |
|    while (curr) {                                                           |
|        ListNode* next = curr->next;                                         |
|        curr->next = prev;                                                   |
|        prev = curr; curr = next;                                            |
|    }                                                                        |
|    return prev;                                                             |
|                                                                             |
| 2. SLOW & FAST (Find Middle)                                                |
|    ----------------------------------------------------------------         |
|    ListNode *slow = head, *fast = head;                                     |
|    while (fast && fast->next) {                                             |
|        slow = slow->next;                                                   |
|        fast = fast->next->next;                                             |
|    }                                                                        |
|    // slow = middle                                                         |
|                                                                             |
| 3. MERGE (Dummy + Tail)                                                     |
|    ----------------------------------------------------------------         |
|    ListNode dummy(0);                                                       |
|    ListNode* tail = &dummy;                                                 |
|    while (l1 && l2) {                                                       |
|        if (l1->val <= l2->val) { tail->next=l1; l1=l1->next; }              |
|        else { tail->next=l2; l2=l2->next; }                                 |
|        tail = tail->next;                                                   |
|    }                                                                        |
|    tail->next = l1 ? l1 : l2;                                               |
|                                                                             |
| 4. DUMMY NODE (Edge Case Eliminator)                                        |
|    ----------------------------------------------------------------         |
|    ListNode dummy(0);                                                       |
|    dummy.next = head;                                                       |
|    // ... operate on dummy.next chain ...                                   |
|    return dummy.next;                                                       |
|                                                                             |
| 5. INTERLEAVE COPY (Complex Pointer)                                        |
|    ----------------------------------------------------------------         |
|    // Insert copies: A>A'>B>B'>C>C'                                         |
|    // Set extra pointers via interleaved structure                          |
|    // Separate into two lists                                               |
|                                                                             |
+-----------------------------------------------------------------------------+

+-----------------------------------------------------------------------------+
|                         COMMON MISTAKES                                     |
+-----------------------------------------------------------------------------+
|                                                                             |
|  MISTAKE 1: Losing the rest of the list during reversal                     |
|    curr->next = prev;  //  Didn't save curr->next first!                    |
|    FIX: ListNode* next = curr->next; THEN curr->next = prev;                |
|                                                                             |
|  MISTAKE 2: Not using dummy node for head-deletion problems                 |
|    slow->next = slow->next->next;  //  Crashes if removing head             |
|    FIX: Use dummy node > dummy.next = head                                  |
|                                                                             |
|  MISTAKE 3: Null pointer dereference with fast pointer                      |
|    while (fast->next)  //  fast might be null                               |
|    FIX: while (fast && fast->next)                                          |
|                                                                             |
|  MISTAKE 4: Creating cycles by not breaking old links                       |
|    // After merge/rotate, old next pointers may form cycles                 |
|    FIX: Set tail->next = nullptr after every restructure                    |
|                                                                             |
|  MISTAKE 5: Returning head instead of prev after reversal                   |
|    return head;  //  head is now the TAIL                                   |
|    FIX: return prev; (prev is the new head)                                 |
|                                                                             |
|  MISTAKE 6: Wrong middle for merge sort split                               |
|    fast = head;  //  Even-length: splits unevenly, infinite recursion       |
|    FIX: fast = head->next; (for sort list, start fast one ahead)            |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
                    PART 5: GOLDEN RULES                                       
===============================================================================

+-----------------------------------------------------------------------------+
|                       GOLDEN RULES - MEMORIZE!                              |
+-----------------------------------------------------------------------------+
|                                                                             |
|  1⃣  DUMMY NODE: Use whenever the head might change (delete, merge, etc.)   |
|                                                                             |
|  2⃣  REVERSAL: Always save next BEFORE flipping the link                    |
|                                                                             |
|  3⃣  SLOW/FAST: "while (fast && fast->next)" - double null check            |
|                                                                             |
|  4⃣  FLOYD'S: slow 1 step, fast 2 steps > cycle detection in O(1) space     |
|      (Full details in Two Pointers.txt)                                     |
|                                                                             |
|  5⃣  MERGE: dummy + tail pattern eliminates all head edge cases             |
|                                                                             |
|  6⃣  ADD NUMBERS: Include carry in loop condition (while l1||l2||carry)     |
|                                                                             |
|  7⃣  INTERSECTION: Swap heads on null > both travel same total distance     |
|                                                                             |
|  8⃣  BREAK CYCLES: After any pointer surgery, ensure no accidental loops    |
|                                                                             |
|  9⃣  MERGE SORT: Use fast = head->next to get correct split for even len    |
|                                                                             |
|    INTERLEAVE: For complex pointers, embed the copy mapping in the list     |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
                    PART 6: INTERVIEW CHEAT CODES                              
===============================================================================

+-----------------------------------------------------------------------------+
|                        INTERVIEW CHEAT CODES                                |
+-----------------------------------------------------------------------------+
|                                                                             |
|   "I'll use a dummy node to simplify edge cases with the head."             |
|                                                                             |
|   "I'll reverse using the prev-curr-next pattern in O(1) space."            |
|                                                                             |
|   "I'll find the middle with slow/fast pointers - slow moves 1 step,        |
|      fast moves 2 steps."                                                   |
|                                                                             |
|   "For the intersection, I'll have both pointers switch to the other        |
|      list's head - they'll meet at the intersection."                       |
|                                                                             |
|   "For copying with random pointers, I'll interleave copies into the        |
|      original list to avoid a hash map."                                    |
|                                                                             |
|   "This palindrome check combines three techniques: find middle,            |
|      reverse second half, then compare."                                    |
|                                                                             |
|   "For rotation, I'll make the list circular, walk to the new break         |
|      point, and break."                                                     |
|                                                                             |
|   "Merge sort is ideal for linked lists - no random access needed,          |
|      split with slow/fast, merge with dummy+tail."                          |
|                                                                             |
|   "For k-group reversal, I'll count k nodes first, then reverse the         |
|      group and recurse on the rest."                                        |
|                                                                             |
|   "The delete-without-head trick: copy next node's value, then skip         |
|      it - effectively erasing the target node."                             |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
              PART 7: COMPLETE PROBLEM LIST BY CATEGORY                        
===============================================================================
```

**REVERSAL**

- 206.  Reverse Linked List 
- 92.   Reverse Linked List II (reverse between positions m and n)
- 234.  Palindrome Linked List  (Reversal + Slow/Fast)
- 25.   Reverse Nodes in k-Group  HARD

**SLOW & FAST POINTER**

- 876.  Middle of Linked List 
- 19.   Remove Nth Node From End of List 
- 160.  Intersection of Two Linked Lists 
- 141.  Linked List Cycle  > See Two Pointers.txt
- 142.  Linked List Cycle II  > See Two Pointers.txt
- 143.  Reorder List  > See Two Pointers.txt

**MERGE / SORT**

- 21.   Merge Two Sorted Lists 
- 148.  Sort List  (Merge Sort)
- 2.    Add Two Numbers 
- 445.  Add Two Numbers II (most significant digit first - use stack or reverse)
- 23.   Merge K Sorted Lists  HARD > See Heap & Kth Problems.txt

**IN-PLACE MANIPULATION**

- 237.  Delete Node in a Linked List
- 203.  Remove Linked List Elements (remove all nodes with given value)
- 83.   Remove Duplicates from Sorted List (keep one of each)
- 82.   Remove Duplicates from Sorted List II (remove ALL duplicates)
- 1836. Remove Duplicates From an Unsorted Linked List (hash set)
- 61.   Rotate List
- 328.  Odd Even Linked List (rearrange odd/even indices)
- 725.  Split Linked List in Parts

**COMPLEX POINTER**

- 138.  Copy List with Random Pointer 
- 430.  Flatten a Multilevel Doubly Linked List

## **MASTER PROBLEM MAPPING TABLE**

```
+-------------------------------------------------+----------------------------+
| Problem                                         | Pattern                    |
+-------------------------------------------------+----------------------------+
| Reverse Linked List (206)                       | Reversal                   |
| Reverse Linked List II (92)                     | Reversal (Partial)         |
| Reverse Nodes in k-Group (25)                   | Reversal (Recursive)       |
| Palindrome Linked List (234)                    | Reversal + Slow/Fast       |
| Middle of Linked List (876)                     | Slow & Fast                |
| Remove Nth Node From End (19)                   | Slow & Fast (Gap)          |
| Intersection of Two Linked Lists (160)          | Two Pointer (Switch)       |
| Linked List Cycle (141)                         | Floyd's (Two Ptrs.txt)     |
| Linked List Cycle II (142)                      | Floyd's (Two Ptrs.txt)     |
| Reorder List (143)                              | Combined (Two Ptrs.txt)    |
| Merge Two Sorted Lists (21)                     | Merge (Dummy + Tail)       |
| Sort List (148)                                 | Merge Sort (Split+Merge)   |
| Add Two Numbers (2)                             | Merge (with Carry)         |
| Add Two Numbers II (445)                        | Merge (Stack/Reverse)      |
| Merge K Sorted Lists (23)                       | Heap (Heap.txt)            |
| Delete Node in a Linked List (237)              | In-Place (Copy+Skip)       |
| Remove Linked List Elements (203)               | In-Place (Dummy+Skip)      |
| Remove Duplicates Sorted (83)                   | In-Place (Skip Dups)       |
| Remove Duplicates Sorted II (82)                | In-Place (Skip All Dups)   |
| Remove Duplicates Unsorted (1836)               | In-Place (Hash Set)        |
| Rotate List (61)                                | In-Place (Circular)        |
| Odd Even Linked List (328)                      | In-Place (Two Chains)      |
| Split Linked List in Parts (725)                | In-Place (Partition)       |
| Copy List with Random Pointer (138)             | Complex Ptr (Interleave)   |
| Flatten Multilevel Doubly LL (430)              | Complex Ptr (DFS Splice)   |
+-------------------------------------------------+----------------------------+

+------------------------------------------------------------------------------+
|                  LINKED LIST PATTERN DECISION FLOWCHART                      |
+------------------------------------------------------------------------------+
|                                                                              |
|  Need to REVERSE all or part of the list?                                    |
|    YES > REVERSAL (prev-curr-next)                                           |
|                                                                              |
|  Need to find MIDDLE, detect CYCLE, or find Nth from END?                    |
|    YES > SLOW & FAST (or fixed gap)                                          |
|                                                                              |
|  Need to combine two lists (merge, add, intersect) or SORT?                  |
|    YES > MERGE / SORT (dummy + tail, merge sort)                             |
|                                                                              |
|  Need to RESTRUCTURE pointers (delete, rotate, remove dups, rearrange)?      |
|    YES > IN-PLACE MANIPULATION (save refs, rewire, break cycles)             |
|                                                                              |
|  Have EXTRA pointers (random, child)?                                        |
|    YES > COMPLEX POINTER (interleave or DFS)                                 |
|                                                                              |
|  Problem combines multiple operations (e.g., palindrome, reorder)?           |
|    YES > COMBINE PATTERNS (find mid + reverse + merge/compare)               |
|                                                                              |
|  Is it a CYCLE problem?                                                      |
|    YES > FLOYD'S ALGORITHM > See Two Pointers.txt                            |
|                                                                              |
|  Involves K sorted lists?                                                    |
|    YES > MIN HEAP > See Heap & Kth Problems.txt                              |
|                                                                              |
+------------------------------------------------------------------------------+

================================================================================
                                   END                                          
================================================================================
```
