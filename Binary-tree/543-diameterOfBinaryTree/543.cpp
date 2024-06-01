#include <iostream> 
#include <algorithm>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
给你一棵二叉树的根节点，返回该树的 直径 。

二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。

两节点之间路径的 长度 由它们之间边数表示。

示例 1：
输入：root = [1,2,3,4,5]
输出：3
解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。

示例 2：
输入：root = [1,2]
输出：1
*/

class Solution {
public:
    int res = 0;
    int helper(TreeNode *root){
        // 递归出口：根节点
        if (!root)
            return 0;

        res = max(res, helper(root->left) + helper(root->right));

        return max(helper(root->left), helper(root->right)) + 1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        // 思路：递归，返回根节点左右子树的路径之和
        // 每个节点都可以看作左子树到右子树的一条路的中间节点
        // 找到每个节点作为中间节点时，对应路径长度的最大值即可
        // 路径长度 = 路径节点数 - 1

        helper(root);
        
        return res; 
    }
};