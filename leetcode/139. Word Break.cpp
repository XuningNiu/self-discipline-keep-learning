//这个是经典问题。 动态规划是最好的选择，DFS也是动态规划的一种
//动态规划 说到底就是尝试所有可能性
//我比较习惯于 DFS 

//方法一：从0开始出发，对于每个可能的word去除，然后递归当前位置+1继续寻找。 要使用memo来提高效率

class Solution {
    unordered_map<int, bool> umap;

    bool helper(string &s, unordered_set<string> &uset, int start){
        if (start == s.size()){
            return true;
        }
        if (umap.count(start)){
            return umap[start];
        }
        for (int i = start; i <s.size(); i++){
            string tmp = s.substr(start, i-start+1);
            if (uset.count(tmp)){
                if (helper(s, uset, i+1)){
                    umap[start] = true;
                    return true;
                }
            }
        }
        umap[start] = false;
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> uset;
        uset.insert(wordDict.begin(), wordDict.end());

        return helper(s, uset, 0);
    }
};

//方法二：也是从0开始出发，只不过把递归变成了dp的数组
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1, false);
        unordered_set<string> uset;
        
        uset.insert(wordDict.begin(), wordDict.end());
        dp[0] = true;
        for (int i = 1; i <= s.size(); i++){
            for (int j = 0; j < i; j++){
                if (dp[j] && uset.count(s.substr(j, i-j))){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};

//方法三：抄一个自上而下DP的答案