#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。

对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

示例 1:
输入: g = [1,2,3], s = [1,1]
输出: 1
解释:
你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
所以你应该输出1。

示例 2:
输入: g = [1,2], s = [1,2,3]
输出: 2
解释:
你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
你拥有的饼干数量和尺寸都足以让所有孩子满足。
所以你应该输出2.
*/

class Solution
{
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        /**
         * 思路：
         * 贪心算法
         * 先把s[]和g[]按照升序排列，然后依次尝试满足各个孩子的胃口
         */
        int res = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int curChild = 0, curCookie = 0;
        while (curCookie < s.size() && curChild < g.size())
        {
            if (s[curCookie] >= g[curChild])
            {
                res++;
                curCookie++;
                curChild++;
            }
            else
            {
                curCookie++;
            }
        }

        return res;
    }
};

class Solution2 // 二刷
{
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        // 贪心算法：能满足就先满足
        // 先将胃口数组和尺寸数组都先从小到大排序
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int child = 0, cookie = 0;
        while (child < g.size() && cookie < s.size()) {
            if (s[cookie] >= g[child]) // 每次尝试满足当前胃口最小的孩子
                cookie++, child++;
            else // 满足不了，就换下一块饼干
                cookie++;
        }
        return child;
    }
};

int main() {
    vector<int> g = {1, 2, 3};
    vector<int> s = {1, 1};
    Solution2 obj;
    cout << obj.findContentChildren(g, s) << endl;
    return 0;
}