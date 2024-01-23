//https://leetcode.com/problems/binary-subarrays-with-sum/description/

// 方法一：
// Hash table + prefix
// 从左向右遍历，使用umap记录的sum对应的sub array的个数，{这是相当于左侧的遍历}
// 而每次遍历的处理中，如果存在满足umap[sum-goal]条件的记录，就增加到结果中，{这是相当于右侧的遍历}
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> umap;
        int n = nums.size();
        int sum = 0;
        int ret = 0;

        umap[0] = 1;
        for (int i = 0; i < n; i++){
            sum += nums[i];
            if (umap.count(sum-goal) != 0){
                ret += umap[sum-goal];
            }
            umap[sum]++;
        }
        return ret;
    }
};

// 方法二：sliding window
//  at_most(nums, goal)函数解释：
//  获取nums的所有子数组中，和从0~goal之间的所有子数组的个数
//  举例来说，101的所有子数组个数是 3*(1+3)/2 = 6 个，
//  1,10,101,01,0,1
//  其中at_most(2) 就是所有6个
//  at_most(1)就是除了101之外的5个
//  所以包括两个1的子数组就是at_most(2)-at_most(1)

/*
在一个长度为 N 的数组中，生成所有可能的子数组，可以观察到以下规律：

包含数组中第 N 个元素的子数组，是由长度为 N-1 的子数组加上第 N 个元素构成的。
不包含数组中第 N 个元素的子数组，仍然是由长度为 N-1 的子数组构成的。
因此，长度为 N 的数组的所有子数组个数，等于长度为 N-1 的数组的所有子数组个数，再加上包含第 N 个元素的子数组。这样就形成了一个递推关系。

具体来说，对于长度为 N 的数组，它的所有子数组个数为：
子数组个数(N)=子数组个数(N−1)+N

这就解释了为什么数组长度为 N 的子数组个数要比数组长度为 N-1 的子数组个数多 N 个。
*/
class Solution {
public:
    int at_most(vector<int> &nums, int goal){
        if (goal < 0){
            return 0;
        }
        int l = 0, r = 0;
        int n = nums.size();
        int sum = 0;
        int count = 0;
        for (r = 0; r < n; r++){
            sum += nums[r];
            while (sum > goal){
                sum -= nums[l++];
            }
            count += r - l + 1;// (r-l+1) 就是符合条件的新增子数组的个数，就是[l-r]之间包括nums[r]在内的子数组个数。
            //个数为N的数组，新增一个N+1节点，会增加N+1个子数组, 也就是 sub_number(N+1) = sub_number(N) + (N+1)
        }
        return count;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return at_most(nums, goal) - at_most(nums, goal-1);
    }
};