#include <iostream>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
给定一个二叉树 root ，返回其最大深度。

二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。

示例 1：
输入：root = [3,9,20,null,null,15,7]
输出：3

示例 2：
输入：root = [1,null,2]
输出：2
*/

class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        /**
         * 利用递归
         * 递归出口：无左右孩子
        */
        if (!root)
            return 0;
        TreeNode *leftSub = root->left;
        TreeNode *rightSub = root->right;
        return max(maxDepth(leftSub), maxDepth(rightSub)) + 1;
    }

    int maxDepthII(TreeNode *root){
        /**
         * 非递归
         * 利用栈实现
         * 入栈：深度++
         * 出栈：深度--
        */
        if (!root)
            return 0;
        
        stack<TreeNode *> nodeStack;
        TreeNode *curNode = root;
        int curDepth = 1, maxDepth = 1;
        unordered_map<TreeNode *, int> visited;

        nodeStack.push(root);
        visited[root] = 1;
        while (!nodeStack.empty())
        {
            curNode = nodeStack.top();
            if (curNode->left && !visited[curNode->left])
            {
                nodeStack.push(curNode->left);
                visited[curNode->left] = 1;
                maxDepth = max(++curDepth, maxDepth);
                continue;
            }
            if (curNode->right && !visited[curNode->right])
            {
                nodeStack.push(curNode->right);
                visited[curNode->right] = 1;
                maxDepth = max(++curDepth, maxDepth);
                continue;
            }
            nodeStack.pop();
            maxDepth = max(--curDepth, maxDepth);
        }

        return maxDepth;
    }
};
