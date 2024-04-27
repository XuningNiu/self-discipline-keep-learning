//有点像个数学题。两个方法，第二个方法会超时
//方法一： unordered_map计算所有的出现次数 count
//对于 count == 1， 失败
//对于count >= 2 操作是 count/3 + (count % 3? 0 : 1) 
//也就是不能整除3，就增加一个操作，因为可以选择2 或者 3
//count == 2 , 操作 + 1
//count == 3 , 操作 + 1 ===> 3
//count == 4 , 操作 + 1 ===> 3 + 1
//count == 5 , 操作 + 2  --》3 + 2
//count == 6 , 操作 + 2 ===> 3 + 3
//count == 7 , 操作 + 3 ===》 3 + 3 + 1
//count == 8 , 操作 + 3 ===> 3 + 3 + 2
//count == 9 , 操作 + 3 ===> 3 + 3 + 3
class Solution {
public:
    int minOperations(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        unordered_map<int, int> umap;
        for (auto num : nums){
            umap[num]++;
        }
        
        int ret = 0;
        for (auto [_, c] : umap){
            if (c == 1){
                return -1;
            }
            ret += c/3;
            if (c%3){
                ret++;
            }
        }
        return ret;
    }
};

// 方法二、 超时

class Solution {
private:
    int ret = INT_MAX;
    void dfs(unordered_map<int, int> umap, int count){
        if (umap.empty()){
            ret = min(ret, count);
            return;
        }
        auto it = umap.begin();
        if (it->second > 3){
            it->second -= 3;
            dfs(umap, count+1);
            it->second += 1;
            dfs(umap, count+1);
        }
        else if (it->second == 2 || it->second == 3){
            umap.erase(it->first);
            dfs(umap, count + 1);
        }
        return;
    }

public:
    int minOperations(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        unordered_map<int, int> umap;
        for (auto num : nums){
            umap[num]++;
        }
        dfs(umap, 0);
        if (ret == INT_MAX) {
            return -1;
        }
        return ret;
    }
};