#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>

using namespace std;

// 树节点的定义
struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
    // 构造函数，初始化value，left，right，其中left和right初始化为nullptr
};

TreeNode* buildTree(const vector<int>& preorder) {
    
}