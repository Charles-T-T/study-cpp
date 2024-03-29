#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/*
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

示例 1：
输入：root = [1,null,2,3]
输出：[1,2,3]

示例 2：
输入：root = []
输出：[]

示例 3：
输入：root = [1]
输出：[1]

示例 4：
输入：root = [1,2]
输出：[1,2]

示例 5：
输入：root = [1,null,2]
输出：[1,2]
*/

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
private:
    vector<int> resVec;

public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        // 递归法
        if (root == nullptr)
            return resVec;

        postorderTraversal(root->left);
        postorderTraversal(root->right);
        resVec.push_back(root->val);

        return resVec;
    }

    vector<int> postorderTraversal_II(TreeNode *root)
    {
        /**
         * 迭代法
         * 参考Q144，但是修改一些顺序
         */
        if (!root)
            return resVec;

        stack<TreeNode *> nodeStack;
        TreeNode *curNode;

        nodeStack.push(root);
        while (!nodeStack.empty())
        {
            curNode = nodeStack.top();
            resVec.push_back(curNode->val);
            nodeStack.pop();

            if (curNode->left)
                nodeStack.push(curNode->left);

            if (curNode->right)
                nodeStack.push(curNode->right);
        }
        reverse(resVec.begin(), resVec.end());

        return resVec;
    }

    vector<int> postorderTraversal_II(TreeNode *root)
    {
        /**
         * 统一迭代法
         * 要得到“左右中”的顺序
         * 则按照“中右左”的顺序入栈
         */
        if (!root)
            return resVec;

        stack<TreeNode *> nodeStack;
        TreeNode *curNode;

        nodeStack.push(root);
        while (!nodeStack.empty())
        {
            curNode = nodeStack.top();
            if (curNode)
            {
                nodeStack.push(nullptr);
                if (curNode->right)
                    nodeStack.push(curNode->right);
                if (curNode->left)
                    nodeStack.push(curNode->left);
            }
            else
            {
                nodeStack.pop();
                resVec.push_back(nodeStack.top()->val);
                nodeStack.pop();
            }
        }

        return resVec;
    }
};