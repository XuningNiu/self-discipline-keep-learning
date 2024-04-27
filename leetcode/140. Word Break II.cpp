class Solution {
private:
    int wordMaxLen;
    vector<string> ret;
    unordered_set<string> uset;
    void dfs(string &s, string trace, int start){
        for (int i = start; i < s.size() && i < start + wordMaxLen; i++){
            string tmp = s.substr(start, i-start+1);
            if (uset.count(tmp)){
                if (i == s.size()-1){
                    ret.push_back(trace+tmp);
                }
                else{
                    dfs(s, trace+tmp + " ", i+1);
                }
            }
        }
    }  
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        //uset.insert(wordDict.begin(), wordDict.end());
        wordMaxLen = 0;
        for (auto word : wordDict){
            wordMaxLen = max(wordMaxLen, static_cast<int>(word.size()));
            uset.insert(word);
        }
        string tmp;
        dfs(s, tmp, 0);
        return ret;
    }
};