#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <deque>

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

/// @brief 将字符串按照指定字符分割
/// @param str
/// @param delimiter
/// @return 分割后的tokens数组
vector<string> split(const string &str, char delimiter)
{
    stringstream ss(str);
    string token;
    vector<string> tokens;
    while (getline(ss, token, delimiter))
        tokens.push_back(token);
    return tokens;
}

/// @brief 判断一个字符串是否表示的是整数
/// @param str
/// @return ture or false
bool isInt(const string &str)
{
    try
    {
        int num = stoi(str);
        return true;
    }
    catch (const invalid_argument &)
    {
        return false;
    }
    catch (const out_of_range &)
    {
        return false;
    }
}

/// @brief 从字符串中解析出一棵二叉树
/// @param str
/// @return 树根指针
TreeNode* getRoot(string str)
{
    if (str.empty())
        return nullptr;
    vector<string> tokens = split(str, ',');
    queue<TreeNode *> q;
    int i = 1;
    TreeNode *root = new TreeNode(stoi(tokens[0]));
    TreeNode *cur = root;
    q.push(cur);
    while (!q.empty() && i < tokens.size())
    {
        if (isInt(tokens[i]))
        {
            q.front()->left = new TreeNode(stoi(tokens[i]));
            q.push(q.front()->left);
        }
        i++;

        if (i >= tokens.size())
            break;

        if (isInt(tokens[i]))
        {
            q.front()->right = new TreeNode(stoi(tokens[i]));
            q.push(q.front()->right);
        }
        i++;

        q.pop();
    }
    return root;
}

/// @brief 层序遍历二叉树
/// @param root
/// @return 表示每一层节点值的二维数组
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> res;
    queue<TreeNode *> q;
    if (!root)
        return res;
    q.push(root);
    while (!q.empty())
    {
        int size = q.size(); // 注意！先记录当前队长，因为之后会变
        vector<int> level;   // 当前这一层的节点值
        for (int i = 0; i < size; ++i)
        {
            level.push_back(q.front()->val);
            if (q.front()->left)
                q.push(q.front()->left);
            if (q.front()->right)
                q.push(q.front()->right);
            q.pop();
        }
        res.push_back(level);
    }
    return res;
}

/// @brief 逐层打印树的节点值
/// @param root 
void showTree(TreeNode *root)
{
    vector<vector<int>> levels = levelOrder(root);
    if (levels.empty())
        cout << "Empty tree!" << endl;
    else
    {
        cout << "------------Tree------------" << endl;
        for (auto level : levels)
        {
            for (auto val : level)
                cout << val << " ";
            cout << endl;
        }
        cout << "----------------------------" << endl;
    }
}
