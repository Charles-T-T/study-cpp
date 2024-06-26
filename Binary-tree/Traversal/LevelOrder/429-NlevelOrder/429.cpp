#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

/*
给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）。

树的序列化输入是用层序遍历，每组子节点都由 null 值分隔（参见示例）。

示例 1：
输入：root = [1,null,3,2,4,null,5,6]
输出：[[1],[3,2,4],[5,6]]

示例 2：
输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：[[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
*/

class Solution
{
public:
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> res;
        if (!root)
            return res;

        // 思路：用队列实现
        queue<Node *> qn;
        qn.push(root);

        while (!qn.empty())
        {
            int curSize = qn.size();
            vector<int> curVec;
            for (int i = 0; i < curSize; i++)
            {
                Node *curNode = qn.front();
                curVec.push_back(curNode->val);
                for (Node *child : curNode->children)
                    qn.push(child);
                qn.pop();
            }
            res.push_back(curVec);
        }
        return res;
    }
};