//重点是，这个一定是会形成环的 cycle
//就是一个图遍历问题，任何一个点出发，最终会形成一个环，所以只需要计算每个环中的节点个数即可。

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        unordered_set<int> uset;
        int ret = 0;

        for (int i = 0; i < nums.size(); i++){
            int count = 0;
            int tmp = nums[i];
            while (uset.count(tmp) == 0){
                uset.insert(tmp);
                count++;
                tmp = nums[tmp];
            }
            ret = max(ret, count);
        }
        return ret;
    }
};