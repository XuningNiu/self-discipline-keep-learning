class Solution {
private:
    unordered_set<int> visited;
    void dfs(vector<vector<int>>& isConnected, int cur){
        visited.insert(cur);
        for (int i = 0; i < isConnected[cur].size(); i++){
            if (isConnected[cur][i] == 1 && visited.count(i) == 0){
                dfs(isConnected, i);
            }
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int count = 0;
        for (int i = 0; i < isConnected.size(); i++){
            if (!visited.count(i)){
                count++;
                dfs(isConnected, i);
            }
        }
        return count;
    }
};