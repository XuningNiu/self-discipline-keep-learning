class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> unset(nums.begin(), nums.end());
        int ret = 0;
        
        for (int i = 0; i < nums.size(); i++){
            if (unset.count(nums[i]) == 0){
                continue;
            }
            int left = nums[i];
            int right = nums[i]+1;
            int count = 0;
            while (unset.count(left)){
                unset.erase(left);
                left--;
                count++;
            }
            while (unset.count(right)){
                unset.erase(right);
                right++;
                count++;
            }
            ret = max(ret, count);
        }
        return ret;
    }
};