这个与930非常类似，可以转化为930来做。
https://leetcode.com/problems/count-number-of-nice-subarrays/description/

方法一：
class Solution {
private:
    int at_most(vector<int>& nums, int k){//算小于等于K个的数据
        int count = 0;
        int l = 0;
        int ret = 0;
        for(int r = 0; r < nums.size(); r++){
            if (nums[r] % 2 != 0){
                count++;
                while (count > k){
                    if (nums[l++] % 2 != 0){
                        count--;
                    }
                }
            }
            ret += r-l+1;
        }
        return ret;
    }
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return at_most(nums, k) - at_most(nums, k-1);
    }
};

方法二： 
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> umap{{0, 1}};
        
        int sum = 0;
        int ret = 0;
        for (int i = 0; i < nums.size(); i++){
            if (nums[i] % 2){
                sum++;
            }
            if (umap.count(sum - k)){
                ret += umap[sum-k];
            }
            umap[sum]++;
        }
        return ret;
    }
};