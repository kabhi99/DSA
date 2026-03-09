# **TREE PATTERNS - COMPLETE GUIDE**

Master Tree Traversals, BST, LCA, Path Problems, and Construction!

### **TABLE OF CONTENTS**

1. Tree Basics & Representations
2. DFS Traversals (Preorder, Inorder, Postorder)
3. BFS Traversal (Level Order)
4. Binary Search Tree (BST) Operations
5. Lowest Common Ancestor (LCA)
6. Path Problems
7. Tree Construction
8. Tree Properties (Height, Depth, Balanced)
9. Pattern Recognition Guide
10. Problem List by Category

## **PART 1: TREE BASICS**

### **TREE NODE DEFINITION**

```
struct TreeNode {
int val;
TreeNode *left;
TreeNode *right;
TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

};
```

### **KEY TREE PROPERTIES**

HEIGHT vs DEPTH:
- Height: distance from node to farthest leaf (measured going DOWN)
- Depth: distance from root to node (measured going UP)
- Tree height = max depth of any node

**FULL BINARY TREE:**
Every node has 0 or 2 children

**COMPLETE BINARY TREE:**
All levels filled except possibly the last, filled left to right

**PERFECT BINARY TREE:**
All internal nodes have 2 children, all leaves at same level

**BALANCED BINARY TREE:**
Heights of left and right subtrees differ by at most 1

## **PART 2: DFS TRAVERSALS**

### **THE THREE DFS TRAVERSALS** 

 **MEMORY AID**: "**P**re = **P**rocess first, **I**n = **I**n between, **P**ost = **P**rocess last"

```
+----------------------------------------------------------------------------+
| Traversal      | Order              | Use Case                             |
+----------------+--------------------+--------------------------------------+
| Preorder       | Root > Left > Right| Copy tree, serialize, prefix expr    |
| Inorder        | Left > Root > Right| BST gives SORTED order!              |
| Postorder      | Left > Right > Root| Delete tree, evaluate expr, height   |
+----------------+--------------------+--------------------------------------+
```

1
/ \
2   3
/ \

4   5

Preorder:  1, 2, 4, 5, 3  (Process, then children)
Inorder:   4, 2, 5, 1, 3  (Left, process, right)
Postorder: 4, 5, 2, 3, 1  (Children first, then process)

### **PREORDER TRAVERSAL (Root > Left > Right)**

**RECURSIVE:**

```cpp
void preorder(TreeNode* root, vector<int>& result) {
if (!root) return;                           

result.push_back(root->val);  // Process root
preorder(root->left, result);  // Then left  
preorder(root->right, result); // Then right 

}
```

**ITERATIVE:**

```cpp
vector<int> preorderIterative(TreeNode* root) {
vector<int> result;                                      
if (!root) return result;                                

stack<TreeNode*> st;                                     
st.push(root);                                           

while (!st.empty()) {                                    
    TreeNode* node = st.top();                           
    st.pop();                                            

    result.push_back(node->val);                         

    // Push right first so left is processed first (LIFO)
    if (node->right) st.push(node->right);               
    if (node->left) st.push(node->left);                 
}                                                        

return result;                                           

}
```

### **INORDER TRAVERSAL (Left > Root > Right)**  BST = SORTED!

**RECURSIVE:**

```cpp
void inorder(TreeNode* root, vector<int>& result) {
if (!root) return;                            

inorder(root->left, result);   // Left first  
result.push_back(root->val);   // Process root
inorder(root->right, result);  // Then right  

}
```

**ITERATIVE:**

```cpp
vector<int> inorderIterative(TreeNode* root) {
vector<int> result;             
stack<TreeNode*> st;            
TreeNode* curr = root;          

while (curr || !st.empty()) {   
    // Go all the way left      
    while (curr) {              
        st.push(curr);          
        curr = curr->left;      
    }                           

    // Process current node     
    curr = st.top();            
    st.pop();                   
    result.push_back(curr->val);

    // Move to right subtree    
    curr = curr->right;         
}                               

return result;                  

}
```

### **POSTORDER TRAVERSAL (Left > Right > Root)**

**RECURSIVE:**

```cpp
void postorder(TreeNode* root, vector<int>& result) {
if (!root) return;                                  

postorder(root->left, result);  // Left first       
postorder(root->right, result); // Then right       
result.push_back(root->val);    // Process root last

}
```

### ITERATIVE (Using Two Stacks):

```cpp
vector<int> postorderIterative(TreeNode* root) {
vector<int> result;                         
if (!root) return result;                   

stack<TreeNode*> st1, st2;                  
st1.push(root);                             

while (!st1.empty()) {                      
    TreeNode* node = st1.top();             
    st1.pop();                              
    st2.push(node);  // Push to second stack

    if (node->left) st1.push(node->left);   
    if (node->right) st1.push(node->right); 
}                                           

while (!st2.empty()) {                      
    result.push_back(st2.top()->val);       
    st2.pop();                              
}                                           

return result;                              

}
```

### **UNIVERSAL DFS TEMPLATE** 

Most tree problems follow this structure:

```cpp
int dfs(TreeNode* root) {
// Base case                                          
if (!root) return BASE_VALUE;                         

// Recursive calls                                    
int left = dfs(root->left);                           
int right = dfs(root->right);                         

// Process current node (using left and right results)
int result = COMBINE(left, right, root->val);         

// Optional: Update global variable                   
// globalAnswer = UPDATE(globalAnswer, ...);          

return result;                                        

}
```

## **PART 3: BFS TRAVERSAL (LEVEL ORDER)**

### **LEVEL ORDER TRAVERSAL** 

**USE WHEN:**
- Need to process level by level
- Find width, rightmost node per level
- Connect nodes at same level

**TEMPLATE:**

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
vector<vector<int>> result;                        
if (!root) return result;                          

queue<TreeNode*> q;                                
q.push(root);                                      

while (!q.empty()) {                               
    int size = q.size();  // Nodes at current level
    vector<int> level;                             

    for (int i = 0; i < size; i++) {               
        TreeNode* node = q.front();                
        q.pop();                                   

        level.push_back(node->val);                

        if (node->left) q.push(node->left);        
        if (node->right) q.push(node->right);      
    }                                              

    result.push_back(level);                       
}                                                  

return result;                                     

}
```

### **PROBLEM: Binary Tree Right Side View (LC 199)** 

 PATTERN: Level Order, take last node of each level
 TEMPLATE: BFS, collect last node per level

```cpp
vector<int> rightSideView(TreeNode* root) {
vector<int> result;                            
if (!root) return result;                      

queue<TreeNode*> q;                            
q.push(root);                                  

while (!q.empty()) {                           
    int size = q.size();                       

    for (int i = 0; i < size; i++) {           
        TreeNode* node = q.front();            
        q.pop();                               

        if (i == size - 1) {  // Rightmost node
            result.push_back(node->val);       
        }                                      

        if (node->left) q.push(node->left);    
        if (node->right) q.push(node->right);  
    }                                          
}                                              

return result;                                 

}
```

### **PROBLEM: Zigzag Level Order (LC 103)**

 PATTERN: Level Order with alternating direction
 TEMPLATE: Use deque or reverse alternate levels

```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
vector<vector<int>> result;                      
if (!root) return result;                        

queue<TreeNode*> q;                              
q.push(root);                                    
bool leftToRight = true;                         

while (!q.empty()) {                             
    int size = q.size();                         
    vector<int> level(size);                     

    for (int i = 0; i < size; i++) {             
        TreeNode* node = q.front();              
        q.pop();                                 

        // Place at correct position             
        int idx = leftToRight ? i : size - 1 - i;
        level[idx] = node->val;                  

        if (node->left) q.push(node->left);      
        if (node->right) q.push(node->right);    
    }                                            

    result.push_back(level);                     
    leftToRight = !leftToRight;                  
}                                                

return result;                                   

}
```

## **PART 4: BINARY SEARCH TREE (BST)**

### **BST PROPERTY** 

**FOR EVERY NODE:**
- All values in LEFT subtree < node.val
- All values in RIGHT subtree > node.val

**CRITICAL INSIGHT:**
- Inorder traversal of BST gives SORTED order!
- This is used in many BST problems

### **BST SEARCH**

```cpp
TreeNode* searchBST(TreeNode* root, int val) {
if (!root || root->val == val) return root;

if (val < root->val) {                     
    return searchBST(root->left, val);     
} else {                                   
    return searchBST(root->right, val);    
}                                          

}
```

TIME: O(H) where H is height (O(log N) balanced, O(N) worst)

### **BST INSERT**

```cpp
TreeNode* insertIntoBST(TreeNode* root, int val) {
if (!root) return new TreeNode(val);              

if (val < root->val) {                            
    root->left = insertIntoBST(root->left, val);  
} else {                                          
    root->right = insertIntoBST(root->right, val);
}                                                 

return root;                                      

}
```

### **BST DELETE** 

**THREE CASES:**
1. Node is leaf > just delete
2. Node has one child > replace with child
3. Node has two children > replace with inorder successor (or predecessor)

```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
if (!root) return nullptr;                                                

if (key < root->val) {                                                    
    root->left = deleteNode(root->left, key);                             
} else if (key > root->val) {                                             
    root->right = deleteNode(root->right, key);                           
} else {                                                                  
    // Found node to delete                                               

    // Case 1 & 2: One or no child                                        
    if (!root->left) return root->right;                                  
    if (!root->right) return root->left;                                  

    // Case 3: Two children                                               
    // Find inorder successor (smallest in right subtree)                 
    TreeNode* succ = root->right;                                         
    while (succ->left) {                                                  
        succ = succ->left;                                                
    }                                                                     

    root->val = succ->val;  // Replace value                              
    root->right = deleteNode(root->right, succ->val);  // Delete successor
}                                                                         

return root;                                                              

}
```

### **PROBLEM: Validate BST (LC 98)** 

 PATTERN: Pass valid range to each node
 TEMPLATE: Each node must be within (min, max) bounds

**KEY INSIGHT:**
- Not enough to check root > left and root < right
- Must check against ALL ancestors
- Solution: Pass valid range down recursively

**COMMON MISTAKE:**
```cpp
 if (root->val > root->left->val && root->val < root->right->val)
```

 Must track range from all ancestors!

```cpp
bool isValidBST(TreeNode* root) {
return validate(root, LONG_MIN, LONG_MAX);

}

bool validate(TreeNode* node, long minVal, long maxVal) {
if (!node) return true;                          

if (node->val <= minVal || node->val >= maxVal) {
    return false;                                
}                                                

return validate(node->left, minVal, node->val) &&
       validate(node->right, node->val, maxVal); 

}
```

### **PROBLEM: Kth Smallest Element in BST (LC 230)** 

 PATTERN: Inorder traversal = sorted order
 TEMPLATE: Inorder, count until k

```cpp
int kthSmallest(TreeNode* root, int k) {
int count = 0, result = 0;      
inorder(root, k, count, result);
return result;                  

}

void inorder(TreeNode* node, int k, int& count, int& result) {
if (!node) return;                     

inorder(node->left, k, count, result); 

count++;                               
if (count == k) {                      
    result = node->val;                
    return;                            
}                                      

inorder(node->right, k, count, result);

}
```

### **PROBLEM: Convert Sorted Array to BST (LC 108)** 

 PATTERN: Divide and conquer, middle element is root
 TEMPLATE: Recursive construction using mid point

```cpp
TreeNode* sortedArrayToBST(vector<int>& nums) {
return build(nums, 0, nums.size() - 1);

}

TreeNode* build(vector<int>& nums, int left, int right) {
if (left > right) return nullptr;         

int mid = left + (right - left) / 2;      
TreeNode* root = new TreeNode(nums[mid]); 

root->left = build(nums, left, mid - 1);  
root->right = build(nums, mid + 1, right);

return root;                              

}
```

## **PART 5: LOWEST COMMON ANCESTOR (LCA)**

### **LCA IN BINARY TREE (LC 236)** 

 PATTERN: Post-order DFS, bubble up found nodes
 TEMPLATE: Return node if found, combine results from children

**KEY INSIGHT:**
- If both p and q are found in different subtrees, current node is LCA
- If one is found, bubble it up
- If current node is p or q, return it

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
// Base case                                              
if (!root || root == p || root == q) {                    
    return root;                                          
}                                                         

// Search in both subtrees                                
TreeNode* left = lowestCommonAncestor(root->left, p, q);  
TreeNode* right = lowestCommonAncestor(root->right, p, q);

// If both found in different subtrees, root is LCA       
if (left && right) return root;                           

// Otherwise, return the one that was found               
return left ? left : right;                               

}
```

TIME: O(N)
SPACE: O(H)

### **LCA IN BST (LC 235)** 

 PATTERN: Use BST property to guide search
 TEMPLATE: If both smaller, go left; if both larger, go right; else current is LCA

**KEY INSIGHT:**
- In BST, we can use values to decide direction
- LCA is first node where p and q split into different subtrees

```cpp
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
while (root) {                                            
    if (p->val < root->val && q->val < root->val) {       
        root = root->left;  // Both in left subtree       
    } else if (p->val > root->val && q->val > root->val) {
        root = root->right; // Both in right subtree      
    } else {                                              
        return root;  // Split point = LCA                
    }                                                     
}                                                         
return nullptr;                                           

}
```

TIME: O(H)

## **PART 6: PATH PROBLEMS**

### **PROBLEM: Path Sum (LC 112)** 

 PATTERN: DFS with running sum
 TEMPLATE: Check if leaf with remaining sum = 0

```cpp
bool hasPathSum(TreeNode* root, int targetSum) {
if (!root) return false;                               

// Check if leaf node with correct sum                 
if (!root->left && !root->right) {                     
    return targetSum == root->val;                     
}                                                      

// Recurse with remaining sum                          
return hasPathSum(root->left, targetSum - root->val) ||
       hasPathSum(root->right, targetSum - root->val); 

}
```

### **PROBLEM: Path Sum II (LC 113)** 

 PATTERN: DFS with path tracking (backtracking)
 TEMPLATE: Build path, add to result at leaf, backtrack

```cpp
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
vector<vector<int>> result;        
vector<int> path;                  
dfs(root, targetSum, path, result);
return result;                     

}

void dfs(TreeNode* node, int remaining, vector<int>& path,
     vector<vector<int>>& result) {                         
if (!node) return;                                          

path.push_back(node->val);                                  

// If leaf with correct sum, save path                      
if (!node->left && !node->right && remaining == node->val) {
    result.push_back(path);                                 
}                                                           

dfs(node->left, remaining - node->val, path, result);       
dfs(node->right, remaining - node->val, path, result);      

path.pop_back();  // Backtrack!                             

}
```

### **PROBLEM: Binary Tree Maximum Path Sum (LC 124)**  HARD

 PATTERN: DFS with global max, two different values
 TEMPLATE: Return single path sum, update global with complete path

KEY INSIGHT (CRITICAL!):
- Two different values:
1. Return value: max single path from node (can only go one direction)
2. Global update: complete path through node (left + node + right)

- Return vs Update is different!

```cpp
int maxSum;

int maxPathSum(TreeNode* root) {
maxSum = INT_MIN;
dfs(root);       
return maxSum;   

}

int dfs(TreeNode* node) {
if (!node) return 0;                                           

// Get max path from children (0 if negative - don't use)      
int left = max(0, dfs(node->left));                            
int right = max(0, dfs(node->right));                          

// Update global max (complete path through this node)         
maxSum = max(maxSum, left + right + node->val);                

// Return max single path from this node (can only go one way!)
return max(left, right) + node->val;                           

}
```

WHY TWO VALUES?
Complete path: can curve (left > node > right)
Return value: can only continue in one direction (for parent to use)

### **PROBLEM: Diameter of Binary Tree (LC 543)** 

 PATTERN: Same as Max Path Sum concept
 TEMPLATE: Return height, update global diameter

```cpp
int diameter;

int diameterOfBinaryTree(TreeNode* root) {
diameter = 0;   
height(root);   
return diameter;

}

int height(TreeNode* node) {
if (!node) return 0;                       

int left = height(node->left);             
int right = height(node->right);           

// Update diameter (path through this node)
diameter = max(diameter, left + right);    

// Return height (for parent to use)       
return max(left, right) + 1;               

}
```

## **PART 7: TREE CONSTRUCTION**

### **PROBLEM: Construct from Preorder + Inorder (LC 105)** 

 PATTERN: Preorder gives root, Inorder gives left/right split
 TEMPLATE: Use hashmap for inorder index lookup

**KEY INSIGHT:**
- Preorder: [root, ...left subtree..., ...right subtree...]
- Inorder: [...left subtree..., root, ...right subtree...]
- First element of preorder is always root
- Find root in inorder > everything left is left subtree

```cpp
unordered_map<int, int> inorderIdx;
int preIdx = 0;

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
for (int i = 0; i < inorder.size(); i++) {    
    inorderIdx[inorder[i]] = i;               
}                                             
return build(preorder, 0, inorder.size() - 1);

}

TreeNode* build(vector<int>& preorder, int left, int right) {
if (left > right) return nullptr;                           

int rootVal = preorder[preIdx++];                           
TreeNode* root = new TreeNode(rootVal);                     

int inIdx = inorderIdx[rootVal];  // Root's index in inorder

root->left = build(preorder, left, inIdx - 1);              
root->right = build(preorder, inIdx + 1, right);            

return root;                                                

}
```

### **PROBLEM: Construct from Inorder + Postorder (LC 106)**

 PATTERN: Similar, but postorder gives root at END
 TEMPLATE: Process postorder from right to left

```cpp
unordered_map<int, int> inorderIdx;
int postIdx;

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
postIdx = postorder.size() - 1;                
for (int i = 0; i < inorder.size(); i++) {     
    inorderIdx[inorder[i]] = i;                
}                                              
return build(postorder, 0, inorder.size() - 1);

}

TreeNode* build(vector<int>& postorder, int left, int right) {
if (left > right) return nullptr;                                      

int rootVal = postorder[postIdx--];                                    
TreeNode* root = new TreeNode(rootVal);                                

int inIdx = inorderIdx[rootVal];                                       

// Build RIGHT first! (postorder: left, right, root > process reversed)
root->right = build(postorder, inIdx + 1, right);                      
root->left = build(postorder, left, inIdx - 1);                        

return root;                                                           

}
```

### **PROBLEM: Serialize and Deserialize Binary Tree (LC 297)** 

 PATTERN: Preorder traversal with null markers
 TEMPLATE: Use "null" for empty nodes, split by comma

```java
class Codec {
```

public:
```
// Serialize: Preorder traversal with null markers
string serialize(TreeNode* root) {                
    if (!root) return "null";                     

    return to_string(root->val) + ","            +
           serialize(root->left) + ","           +
           serialize(root->right);                
}                                                 

// Deserialize: Reconstruct using queue           
TreeNode* deserialize(string data) {              
    queue<string> nodes;                          
    stringstream ss(data);                        
    string item;                                  

    while (getline(ss, item, ',')) {              
        nodes.push(item);                         
    }                                             

    return buildTree(nodes);                      
}                                                 

TreeNode* buildTree(queue<string>& nodes) {       
    string val = nodes.front();                   
    nodes.pop();                                  

    if (val == "null") return nullptr;            

    TreeNode* root = new TreeNode(stoi(val));     
    root->left = buildTree(nodes);                
    root->right = buildTree(nodes);               

    return root;                                  
}                                                 
```

```
};
```

## **PART 8: TREE PROPERTIES**

### **MAX DEPTH / HEIGHT (LC 104)**

```cpp
int maxDepth(TreeNode* root) {
if (!root) return 0;                                        
return 1 + max(maxDepth(root->left), maxDepth(root->right));

}
```

### **MIN DEPTH (LC 111)**

 TRICKY: Must be path to LEAF (not just any null)

```cpp
int minDepth(TreeNode* root) {
if (!root) return 0;                                        

// If one child is null, must go to other child             
if (!root->left) return 1 + minDepth(root->right);          
if (!root->right) return 1 + minDepth(root->left);          

return 1 + min(minDepth(root->left), minDepth(root->right));

}
```

### **BALANCED BINARY TREE (LC 110)** 

 PATTERN: Return -1 if unbalanced, otherwise return height
 TEMPLATE: Check balance while computing height

```cpp
bool isBalanced(TreeNode* root) {
return checkHeight(root) != -1;

}

int checkHeight(TreeNode* node) {
if (!node) return 0;                                             

int left = checkHeight(node->left);                              
if (left == -1) return -1;  // Left subtree unbalanced           

int right = checkHeight(node->right);                            
if (right == -1) return -1;  // Right subtree unbalanced         

if (abs(left - right) > 1) return -1;  // Current node unbalanced

return 1 + max(left, right);                                     

}
```

### **SYMMETRIC TREE (LC 101)** 

 PATTERN: Compare mirror images
 TEMPLATE: Compare left of left with right of right

```cpp
bool isSymmetric(TreeNode* root) {
return isMirror(root, root);

}

bool isMirror(TreeNode* t1, TreeNode* t2) {
if (!t1 && !t2) return true;           
if (!t1 || !t2) return false;          

return t1->val == t2->val &&           
       isMirror(t1->left, t2->right) &&
       isMirror(t1->right, t2->left);  

}
```

### **SAME TREE (LC 100)**

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
if (!p && !q) return true;            
if (!p || !q) return false;           

return p->val == q->val &&            
       isSameTree(p->left, q->left) &&
       isSameTree(p->right, q->right);

}
```

### **SUBTREE OF ANOTHER TREE (LC 572)** 

```cpp
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
if (!root) return false;                   

if (isSameTree(root, subRoot)) return true;

return isSubtree(root->left, subRoot) |  |
       isSubtree(root->right, subRoot);    

}
```

## **SOLVED: Symmetric Tree (LC 101)** 

 KEY INSIGHT: Compare left subtree with mirror of right subtree

```cpp
bool isSymmetric(TreeNode* root) {
return isMirror(root, root);

}

bool isMirror(TreeNode* t1, TreeNode* t2) {
if (!t1 && !t2) return true;           
if (!t1 || !t2) return false;          

return t1->val == t2->val &&           
       isMirror(t1->left, t2->right) &&
       isMirror(t1->right, t2->left);  

}
```

## **SOLVED: Flatten Binary Tree to Linked List (LC 114)** 

 KEY INSIGHT: Post-order traversal in reverse (right, left, node)
Or: Morris-like threading

```cpp
// Method 1: Reverse post-order with prev pointer
TreeNode* prev = nullptr;

void flatten(TreeNode* root) {
if (!root) return;   

flatten(root->right);
flatten(root->left); 

root->right = prev;  
root->left = nullptr;
prev = root;         

}

// Method 2: Iterative
void flattenIterative(TreeNode* root) {
while (root) {                                
    if (root->left) {                         
        // Find rightmost node in left subtree
        TreeNode* rightmost = root->left;     
        while (rightmost->right) {            
            rightmost = rightmost->right;     
        }                                     

        // Connect rightmost to root's right  
        rightmost->right = root->right;       
        root->right = root->left;             
        root->left = nullptr;                 
    }                                         
    root = root->right;                       
}                                             

}
```

## **SOLVED: Vertical Order Traversal (LC 987)** 

 KEY INSIGHT: Track (column, row, value) and sort appropriately

```cpp
vector<vector<int>> verticalTraversal(TreeNode* root) {
// {column, row, value}                                                          
vector<tuple<int, int, int>> nodes;                                              

function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int col, int row) {
    if (!node) return;                                                           
    nodes.push_back({col, row, node->val});                                      
    dfs(node->left, col - 1, row + 1);                                           
    dfs(node->right, col + 1, row + 1);                                          
};                                                                               

dfs(root, 0, 0);                                                                 

// Sort by column, then row, then value                                          
sort(nodes.begin(), nodes.end());                                                

vector<vector<int>> result;                                                      
int prevCol = INT_MIN;                                                           

for (auto& [col, row, val] : nodes) {                                            
    if (col != prevCol) {                                                        
        result.push_back({});                                                    
        prevCol = col;                                                           
    }                                                                            
    result.back().push_back(val);                                                
}                                                                                

return result;                                                                   

}
```

## **SOLVED: Binary Tree Top View / Bottom View** 

 KEY INSIGHT: BFS with column tracking, first/last node per column

```cpp
// TOP VIEW: First node encountered at each column
vector<int> topView(TreeNode* root) {
if (!root) return {};                                

map<int, int> columnMap;  // column -> node value    
queue<pair<TreeNode*, int>> q;  // {node, column}    

q.push({root, 0});                                   

while (!q.empty()) {                                 
    auto [node, col] = q.front();                    
    q.pop();                                         

    // Only add if column not seen (first node = top)
    if (columnMap.find(col) == columnMap.end()) {    
        columnMap[col] = node->val;                  
    }                                                

    if (node->left) q.push({node->left, col - 1});   
    if (node->right) q.push({node->right, col + 1}); 
}                                                    

vector<int> result;                                  
for (auto& [col, val] : columnMap) {                 
    result.push_back(val);                           
}                                                    
return result;                                       

}

// BOTTOM VIEW: Last node at each column
vector<int> bottomView(TreeNode* root) {
if (!root) return {};                               

map<int, int> columnMap;                            
queue<pair<TreeNode*, int>> q;                      

q.push({root, 0});                                  

while (!q.empty()) {                                
    auto [node, col] = q.front();                   
    q.pop();                                        

    // Always update (last node = bottom)           
    columnMap[col] = node->val;                     

    if (node->left) q.push({node->left, col - 1});  
    if (node->right) q.push({node->right, col + 1});
}                                                   

vector<int> result;                                 
for (auto& [col, val] : columnMap) {                
    result.push_back(val);                          
}                                                   
return result;                                      

}
```

## **SOLVED: Recover Binary Search Tree (LC 99)** 

PROBLEM: Two nodes swapped in BST, recover it.

 KEY INSIGHT: Inorder traversal should be sorted.
Find two violations (prev > curr) to identify swapped nodes.

```cpp
TreeNode* first = nullptr;
TreeNode* second = nullptr;
TreeNode* prev = nullptr;

void recoverTree(TreeNode* root) {
inorder(root);
swap(first->val, second->val);

}

void inorder(TreeNode* node) {
if (!node) return;                                           

inorder(node->left);                                         

if (prev && prev->val > node->val) {                         
    if (!first) {                                            
        first = prev;  // First violation                    
    }                                                        
    second = node;     // Second violation (or same as first)
}                                                            
prev = node;                                                 

inorder(node->right);                                        

}
```

## **SOLVED: BST Iterator (LC 173)** 

 KEY INSIGHT: Controlled inorder traversal using stack

```java
class BSTIterator {
stack<TreeNode*> st;           

void pushLeft(TreeNode* node) {
    while (node) {             
        st.push(node);         
        node = node->left;     
    }                          
}                              
```

public:
```
BSTIterator(TreeNode* root) { 
    pushLeft(root);           
}                             

int next() {                  
    TreeNode* node = st.top();
    st.pop();                 
    pushLeft(node->right);    
    return node->val;         
}                             

bool hasNext() {              
    return !st.empty();       
}                             
```

```
};

// TIME: O(1) average for next()
// SPACE: O(h) where h = height
```

## **SOLVED: Convert Sorted List to BST (LC 109)** 

 KEY INSIGHT: Use slow/fast pointers to find middle

```cpp
TreeNode* sortedListToBST(ListNode* head) {
if (!head) return nullptr;                                  
if (!head->next) return new TreeNode(head->val);            

// Find middle and its previous node                        
ListNode* slow = head;                                      
ListNode* fast = head;                                      
ListNode* prev = nullptr;                                   

while (fast && fast->next) {                                
    prev = slow;                                            
    slow = slow->next;                                      
    fast = fast->next->next;                                
}                                                           

// Disconnect left half                                     
if (prev) prev->next = nullptr;                             

// slow is the middle node (root)                           
TreeNode* root = new TreeNode(slow->val);                   

// Build subtrees                                           
root->left = sortedListToBST(head == slow ? nullptr : head);
root->right = sortedListToBST(slow->next);                  

return root;                                                

}
```

## **SOLVED: Binary Tree Cameras (LC 968)** 

 KEY INSIGHT: Greedy post-order. States: 0=needs coverage, 1=has camera, 2=covered

```cpp
int cameras = 0;

int minCameraCover(TreeNode* root) {
if (dfs(root) == 0) cameras++;  // Root needs coverage
return cameras;                                       

}

// Returns: 0=needs camera, 1=has camera, 2=covered by child
int dfs(TreeNode* node) {
if (!node) return 2;  // Null is considered covered

int left = dfs(node->left);                        
int right = dfs(node->right);                      

// If any child needs coverage, place camera here  
if (left == 0 || right == 0) {                     
    cameras++;                                     
    return 1;  // Has camera                       
}                                                  

// If any child has camera, this node is covered   
if (left == 1 || right == 1) {                     
    return 2;  // Covered                          
}                                                  

// Both children are covered but no camera nearby  
return 0;  // Needs coverage from parent           

}
```

## **PART 9: PATTERN RECOGNITION GUIDE**

```
+-----------------------------------------------------------------------------+
|                         TREE PATTERN SELECTION                              |
+-----------------------------+-----------------------------------------------+
| Problem Clue                | Pattern / Template                            |
+-----------------------------+-----------------------------------------------+
| "Level order", "width"      | BFS with queue                                |
| "Height", "depth"           | DFS, return max of children + 1               |
| "Path to leaf"              | DFS with path tracking                        |
| "Any path" (not root-leaf)  | DFS with global variable                      |
| "BST", "sorted"             | Inorder traversal                             |
| "Validate BST"              | Pass range bounds                             |
| "Kth smallest/largest BST"  | Inorder with count                            |
| "LCA"                       | Post-order DFS, bubble up                     |
| "Serialize/Deserialize"     | Preorder with null markers                    |
| "Construct tree"            | Preorder root + Inorder split                 |
| "Symmetric", "mirror"       | Compare (left,right) with (right,left)        |
| "Subtree"                   | DFS + Same tree check                         |
| "Balanced"                  | Height with -1 for unbalanced                 |
+-----------------------------+-----------------------------------------------+

+-----------------------------------------------------------------------------+
|                         RETURN vs UPDATE                                    |
+-----------------------------------------------------------------------------+
|                                                                             |
|  SAME VALUE: Height, depth, count                                           |
|    > Return the value directly                                              |
|                                                                             |
|  DIFFERENT VALUES: Diameter, max path sum                                   |
|    > RETURN: single direction value (for parent to use)                     |
|    > UPDATE: complete value through node (global answer)                    |
|                                                                             |
|  EXAMPLE (Diameter):                                                        |
|    Return: max(left, right) + 1  (height for parent)                        |
|    Update: left + right  (diameter through this node)                       |
|                                                                             |
+-----------------------------------------------------------------------------+
```

### **PROBLEM: Populating Next Right Pointers (LC 116)**

 PATTERN: Level order connection using O(1) space
 TEMPLATE: Use established next pointers to traverse levels

Node* connect(Node* root) {
```
if (!root) return nullptr;                                   
Node* leftmost = root;                                       
while (leftmost->left) {                                     
    Node* curr = leftmost;                                   
    while (curr) {                                           
        curr->left->next = curr->right;                      
        if (curr->next) curr->right->next = curr->next->left;
        curr = curr->next;                                   
    }                                                        
    leftmost = leftmost->left;                               
}                                                            
return root;                                                 
```

```
}
// Time: O(N), Space: O(1)
```

### **PROBLEM: BST Iterator (LC 173)** 

 PATTERN: Controlled inorder traversal using stack
 TEMPLATE: Push all left nodes, pop and push right's left chain

```java
class BSTIterator {
stack<TreeNode*> stk;                                  
void pushLeft(TreeNode* node) {                        
    while (node) { stk.push(node); node = node->left; }
}                                                      
```

public:
```
BSTIterator(TreeNode* root) { pushLeft(root); }
int next() {                                   
    TreeNode* node = stk.top(); stk.pop();     
    pushLeft(node->right);                     
    return node->val;                          
}                                              
bool hasNext() { return !stk.empty(); }        
```

```
};
// next(): O(1) amortized, Space: O(H)
```

### **PROBLEM: Inorder Successor in BST (LC 285)**

 PATTERN: BST search with successor tracking
 TEMPLATE: Go left when p < root (update successor), go right otherwise

```cpp
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
TreeNode* successor = nullptr;
while (root) {                
    if (p->val < root->val) { 
        successor = root;     
        root = root->left;    
    } else {                  
        root = root->right;   
    }                         
}                             
return successor;             

}
// Time: O(H), Space: O(1)
```

### **PROBLEM: Largest BST Subtree (LC 333)** 

 PATTERN: Post-order DFS returning {size, min, max}
 TEMPLATE: Validate BST bottom-up, track max size globally

```cpp
int largestBSTSubtree(TreeNode* root) {
int maxSize = 0;                                                     
auto dfs = [&](auto& self, TreeNode* node) -> tuple<int, int, int> { 
    // returns {size, min, max}. size = -1 means not a BST           
    if (!node) return {0, INT_MAX, INT_MIN};                         
    auto [ls, lmin, lmax] = self(self, node->left);                  
    auto [rs, rmin, rmax] = self(self, node->right);                 
    if (ls >= 0 && rs >= 0 && lmax < node->val && node->val < rmin) {
        int size = ls + rs + 1;                                      
        maxSize = max(maxSize, size);                                
        return {size, min(lmin, node->val), max(rmax, node->val)};   
    }                                                                
    return {-1, 0, 0};                                               
};                                                                   
dfs(dfs, root);                                                      
return maxSize;                                                      

}
// Time: O(N), Space: O(H)
```

### **PROBLEM: Boundary of Binary Tree (LC 545)** 

 PATTERN: Three-pass traversal (left boundary + leaves + right boundary reversed)
 TEMPLATE: Separate functions for left, leaves, right

```cpp
vector<int> boundaryOfBinaryTree(TreeNode* root) {
if (!root) return {};                                                        
vector<int> result = {root->val};                                            

auto addLeft = [&](TreeNode* node) {                                         
    while (node) {                                                           
        if (node->left || node->right) result.push_back(node->val);          
        node = node->left ? node->left : node->right;                        
    }                                                                        
};                                                                           
auto addLeaves = [&](auto& self, TreeNode* node) -> void {                   
    if (!node) return;                                                       
    if (!node->left && !node->right) { result.push_back(node->val); return; }
    self(self, node->left);                                                  
    self(self, node->right);                                                 
};                                                                           
auto addRight = [&](TreeNode* node) {                                        
    vector<int> tmp;                                                         
    while (node) {                                                           
        if (node->left || node->right) tmp.push_back(node->val);             
        node = node->right ? node->right : node->left;                       
    }                                                                        
    for (int i = tmp.size() - 1; i >= 0; i--) result.push_back(tmp[i]);      
};                                                                           

addLeft(root->left);                                                         
addLeaves(addLeaves, root->left);                                            
addLeaves(addLeaves, root->right);                                           
addRight(root->right);                                                       
return result;                                                               

}
// Time: O(N), Space: O(N)
```

### **PROBLEM: Two Sum IV - Input is a BST (LC 653)**

 PATTERN: BFS/DFS with hash set for complement lookup
 TEMPLATE: Traverse tree, check if (k - node->val) seen

```cpp
bool findTarget(TreeNode* root, int k) {
unordered_set<int> seen;                       
queue<TreeNode*> q;                            
q.push(root);                                  
while (!q.empty()) {                           
    TreeNode* node = q.front(); q.pop();       
    if (seen.count(k - node->val)) return true;
    seen.insert(node->val);                    
    if (node->left) q.push(node->left);        
    if (node->right) q.push(node->right);      
}                                              
return false;                                  

}
// Time: O(N), Space: O(N)
```

### **PROBLEM: Construct BST from Preorder Traversal (LC 1008)** 

 PATTERN: Preorder traversal with upper bound constraint
 TEMPLATE: Use bound to determine subtree boundaries

```cpp
TreeNode* bstFromPreorder(vector<int>& preorder) {
int idx = 0;                         
return build(preorder, idx, INT_MAX);

}
TreeNode* build(vector<int>& preorder, int& idx, int bound) {
if (idx == preorder.size() || preorder[idx] > bound) return nullptr;
TreeNode* root = new TreeNode(preorder[idx++]);                     
root->left = build(preorder, idx, root->val);                       
root->right = build(preorder, idx, bound);                          
return root;                                                        

}
// Time: O(N), Space: O(N)
```

## **PART 10: PROBLEM LIST BY CATEGORY**

**TRAVERSALS:**
- 94.  Binary Tree Inorder Traversal
- 144. Binary Tree Preorder Traversal
- 145. Binary Tree Postorder Traversal
Y 102. Binary Tree Level Order Traversal 
Y 103. Zigzag Level Order Traversal
Y 199. Binary Tree Right Side View 
Y 987. Vertical Order Traversal 
Y Binary Tree Top View (common interview)
Y Binary Tree Bottom View (common interview)

**BST OPERATIONS:**
- 700. Search in a BST
- 701. Insert into a BST
- 450. Delete Node in a BST 
Y 98.  Validate Binary Search Tree 
Y 230. Kth Smallest Element in BST 
Y 108. Convert Sorted Array to BST 
Y 109. Convert Sorted List to BST 
Y 173. BST Iterator 
Y 99.  Recover Binary Search Tree 
Y 116. Populating Next Right Pointers
Y 285. Inorder Successor in BST
Y 333. Largest BST Subtree 
Y 545. Boundary of Binary Tree 
Y 653. Two Sum IV - Input is a BST
Y 1008. Construct BST from Preorder Traversal 

**LCA & ANCESTORS:**
Y 236. Lowest Common Ancestor of Binary Tree 
Y 235. Lowest Common Ancestor of BST 

**PATH PROBLEMS:**
Y 112. Path Sum 
Y 113. Path Sum II 
- 437. Path Sum III 
Y 124. Binary Tree Maximum Path Sum  HARD
Y 543. Diameter of Binary Tree 

**TREE CONSTRUCTION:**
Y 105. Construct from Preorder + Inorder 
Y 106. Construct from Inorder + Postorder
Y 297. Serialize and Deserialize 

**TREE PROPERTIES:**
Y 104. Maximum Depth
Y 111. Minimum Depth
Y 110. Balanced Binary Tree 
Y 101. Symmetric Tree  (SOLVED)
Y 100. Same Tree
Y 572. Subtree of Another Tree 
- 226. Invert Binary Tree

**TREE MODIFICATION:**
Y 114. Flatten Binary Tree to Linked List  (SOLVED)
- 226. Invert Binary Tree

**ADVANCED:**
- 236. LCA Binary Tree
- 1644. LCA II (nodes may not exist)
- 1650. LCA III (parent pointers)
- 863. All Nodes Distance K 
- 662. Maximum Width of Binary Tree 
Y 968. Binary Tree Cameras  (SOLVED - Tree DP/Greedy)

```
+-----------------------------------------------------------------------------+
|                         GOLDEN RULES - MEMORIZE!                            |
+-----------------------------------------------------------------------------+
|                                                                             |
|  1⃣  Inorder of BST = SORTED array                                          |
|                                                                             |
|  2⃣  Validate BST: pass range (min, max), not just compare with children    |
|                                                                             |
|  3⃣  Diameter/Max Path: RETURN height, UPDATE global with full path         |
|                                                                             |
|  4⃣  Preorder first = root; find root in Inorder for split                  |
|                                                                             |
|  5⃣  LCA: post-order DFS, bubble up found nodes                             |
|                                                                             |
|  6⃣  Path problems: add to path, recurse, backtrack (pop)                   |
|                                                                             |
|  7⃣  Level order: process queue.size() nodes per level                      |
|                                                                             |
|  8⃣  Min depth must go to LEAF (not just any null)                          |
|                                                                             |
+-----------------------------------------------------------------------------+

===============================================================================
                                   END                                         
===============================================================================
```
