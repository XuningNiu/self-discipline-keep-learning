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
方法二：
 at_most
 at_most(goal) - at_most(goal-1)