//主要使用 2*n来实现循环策略
//取临近的第一个大的数字，就是用单调递减，从栈里面退出的就是可能记录的选择

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> stk;
        int n = nums.size();
        vector<int> ret(n, -1);

        for (int i = 0; i < n*2; i++){
            int j = i % n;
            while (!stk.empty() && nums[stk.top()] < nums[j]){
                ret[stk.top()] = nums[j];
                stk.pop();
            }
            stk.push(j);
        }
        return ret;
    }
};