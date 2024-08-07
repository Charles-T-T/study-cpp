# 134. 加油站

[点此跳转题目链接](https://leetcode.cn/problems/gas-station/description/)

## 题目描述

在一条环路上有 `n` 个加油站，其中第 `i` 个加油站有汽油 `gas[i]` 升。

你有一辆油箱容量无限的的汽车，从第 `i` 个加油站开往第 `i+1` 个加油站需要消耗汽油 `cost[i]` 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 `gas` 和 `cost` ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 `-1` 。如果存在解，则 **保证** 它是 **唯一** 的。

 

**示例 1:**

```
输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
输出: 3
解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
```

**示例 2:**

```
输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。
```

 

**提示:**

- `gas.length == n`
- `cost.length == n`
- `1 <= n <= 105`
- `0 <= gas[i], cost[i] <= 104`



## 题解

贪心算法解决。直觉上，容易考虑一种暴力方法：

依次以每个加油站为起点，每次将当前剩余油量加上 `gas[i]` 、再减去 `cost[i]` ，就得到了新的剩余油量；如果直到循环一圈回到起点加油站时，剩余油量每次都不为负，则说明有解、返回该起点加油站编号；否则，返回-1。

其实这已经比较符合贪心算法的思维了（局部最优推整体最优）。我们可以进一步简化：

**如果从加油站 `i` 出发，到加油站 `j` 时，剩余油量第一次不足，则说明从 `i` 到 `j` 内的任意加油站出发，到 `j` 时剩余油量都会不足，于是类似地考虑以 `j + 1` 为起点的情况** ......由于题目说了，要么有唯一解要么无解，我们这样遍历一次之后就能找到目标起点。

上面的结论证明起来也并不复杂：


$$
\begin{array}{l}
上述条件下，假设从[i, j]中某个加油站 \space k \space 出发，到 \space j \space 时剩余油量充足 \enspace (G_{kj} \ge 0) \\
由于从 \space i \space 出发，到 \space j \space 时剩余油量第一次不足 \enspace (G_{ij} < 0) \\
且 \enspace G_{ij} = G_{ik} + G_{kj} \\
所以 \enspace G_{ik} < 0，即 \enspace 从 \space i \space 出发，到 \space k \space 时剩余油量就不足了，矛盾 \\
所以 \enspace 从[i, j]中任意加油站出发，到j时，剩余油量都会不足
\end{array}
$$


**代码（C++）**

```cpp
int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    int curGasLeft = 0;   // 当前剩余的油量
    int totalGasLeft = 0; // 总剩余油量（= 总gas - 总cost）
    int start = 0;
    for (int i = 0; i < gas.size(); ++i)
    {
        curGasLeft += gas[i] - cost[i];
        totalGasLeft += gas[i] - cost[i];
        if (curGasLeft < 0)
        {
            start = i + 1; // 尝试新的起点
            curGasLeft = 0;
        }
    }
    if (totalGasLeft < 0)
        return -1;
    return start;
}
```

