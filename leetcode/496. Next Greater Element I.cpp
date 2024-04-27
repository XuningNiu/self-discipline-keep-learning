//找寻右侧第一个更大的数字，使用单调递减 的单调栈 monotonic(单调) stack
// 例如 栈里面存着 9,8,6,5 现在下一个数字是7，那么就：
// 判断top是否比7小，如果是。 先存储 5 --> 7 表示5的下一个更大的数字是7， pop 5
// 继续判断top。 先存储 6 --> 7 表示6的下一个更大的数字是7， pop 6
// 继续判断top。发现top已经比7大了，那么就符合单调递减的规律，可以直接push进去即可。

//单调 递减 栈s
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> umap;
        stack<int> stk;

        for (auto num : nums2){
            while (!stk.empty() && stk.top() < num){
                umap[stk.top()] = num;
                stk.pop();
            }
            stk.push(num);
        }
        vector<int> ret;
        for (auto num : nums1){
            if (umap.count(num)){
                ret.push_back(umap[num]);
            }
            else{
                ret.push_back(-1);
            }
        }
        return ret;
    }
};