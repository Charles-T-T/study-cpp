# 376. 摆动序列

[点此跳转题目链接](https://leetcode.cn/problems/wiggle-subsequence/description/)

## 题目描述

如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 **摆动序列 。**第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。

- 例如， `[1, 7, 4, 9, 2, 5]` 是一个 **摆动序列** ，因为差值 `(6, -3, 5, -7, 3)` 是正负交替出现的。
- 相反，`[1, 4, 7, 2, 5]` 和 `[1, 7, 4, 5, 5]` 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。

**子序列** 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。

给你一个整数数组 `nums` ，返回 `nums` 中作为 **摆动序列** 的 **最长子序列的长度** 。

 

**示例 1：**

```
输入：nums = [1,7,4,9,2,5]
输出：6
解释：整个序列均为摆动序列，各元素之间的差值为 (6, -3, 5, -7, 3) 。
```

**示例 2：**

```
输入：nums = [1,17,5,10,13,15,10,5,16,8]
输出：7
解释：这个序列包含几个长度为 7 摆动序列。
其中一个是 [1, 17, 10, 13, 10, 16, 8] ，各元素之间的差值为 (16, -7, 3, -3, 6, -8) 。
```

**示例 3：**

```
输入：nums = [1,2,3,4,5,6,7,8,9]
输出：2
```

 

**提示：**

- `1 <= nums.length <= 1000`
- `0 <= nums[i] <= 1000`

 

**进阶：** 你能否用 `O(n)` 时间复杂度完成此题?



## 题解

贪心算法解决。注意到题目中说的子序列实际上 **不是连续的** ，所以我们完全可以在一次遍历（达到进阶要求的 $O(n)$ 时间复杂度）中， **“跳过”** 那些 **没有“摆动”** 的部分，相当于只统计数组中的 **极大值和极小值** 数量即可。

> :warning: 是“极值”（局部）而不是“最值”（整体）

[代码随想录](https://programmercarl.com/0376.摆动序列.html#算法公开课) 将其描述为统计“局部峰值”（包括高峰和低谷），也很直观：

![img](./20201124174327597.png)

**代码（C++）**

```cpp
class Solution
{
public:
    int wiggleMaxLength(vector<int> &nums)
    {
        // 仅有一个元素或者含两个不等元素的序列也视作摆动序列
        if (nums.size() == 1)
            return 1;
        if (nums.size() == 2)
            return nums[0] == nums[1] ? 1 : 2;

        // 贪心算法
        int prevDiff = nums[1] - nums[0];     // 前两个数的差值
        int curDiff;                          // 当前两个数的差值
        int len = nums[0] == nums[1] ? 1 : 2; // 摆动子序列的长度
        for (int i = 2; i < nums.size(); ++i)
        {
            curDiff = nums[i] - nums[i - 1];
            if (curDiff * prevDiff < 0 || (prevDiff == 0 && curDiff != 0))
            {
                prevDiff = curDiff; // 只在“摆动”时才更新prevDiff
                len++;
            }
        }
        return len;
    }
};
```

:round_pushpin: 有几处细节需要注意：

:one: 循环中，只需要在发生了“摆动”时才更新 `prevDiff` ，否则遇到连续的相同数字组成的“平坡”会被干扰（差值总是为0）

:two: `curDiff * prevDiff < 0` 的含义：两个差值“一正一负”，发生摆动

:three: `prevDiff == 0 && curDiff != 0` 的含义：特殊情况——数组起始就有一个平坡，例如 `3, 3, 3, 2, 5` ，此时开头的 `3, 3, 3` 也相当于一个极值，需要记录。可以看到，除此之外，`prevDiff` 总是不为0的（因为除了一开始， `prevDiff` 都是由 `curDiff` 更新来的，而前一个条件判断确保了更新时 `curDiff` 不为0）。
