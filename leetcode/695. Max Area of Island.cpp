方法一： BFS:

class Solution {
public:
    int ret = 0;
    void bfs(vector<vector<int>>& grid, int x, int y){
        int m = grid.size();
        int n = grid[0].size();
        int num = 0;
        queue<pair<int, int>> q;
        vector<vector<int>> offset = {{0, 1},{0, -1},{1, 0},{-1, 0}};
        q.push({x, y});
        grid[x][y] = 0;
        auto is_valid = [&](int next_x, int next_y){
            if (0 <= next_x && next_x < m && 0 <= next_y && next_y < n){
               return true; 
            }
            return false;
        };
        while (!q.empty()){
            auto pa = q.front(); q.pop();
            num++;
            for (int i = 0; i < offset.size(); i++){
                int new_x = pa.first + offset[i][0];
                int new_y = pa.second + offset[i][1];
                if (is_valid(new_x, new_y) && grid[new_x][new_y] == 1){
                    q.push({new_x, new_y});
                    grid[new_x][new_y] = 0;
                }
            }
        }
        ret = max(ret, num);
        return;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
         int m = grid.size();
         int n = grid[0].size();
         for (int i = 0; i < m; i++){
             for (int j = 0; j < n; j++){
                 if (grid[i][j] == 1){
                    bfs(grid, i, j);
                 }                 
             }
         }
         return ret;
    }
};

方法二：
DFS:


//dfs
class Solution {
public:
    void dfs(vector<vector<int>>& grid, int i, int j, int &count){
        int m = grid.size();
        if (!m) return;
        int n = grid[0].size();
        
        if (0 <= i && i < m && 0 <= j && j < n &&
           grid[i][j] == 1){
            grid[i][j] = 0;
            count++;
            dfs(grid, i-1, j, count);
            dfs(grid, i+1, j, count);
            dfs(grid, i, j-1, count);
            dfs(grid, i, j+1, count);
        }
        return;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        if (!m) return 0;
        int n = grid[0].size();
        int ret = 0;
        
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                int count = 0;
                
                dfs(grid, i, j, count);
                
                ret = max(ret, count);
            }
        }
        return ret;
    }
};

方法三：union find:

//UnionFind disjoint set
//注意，这种做法不需要visited记录是否访问过
class UnionFind{
private:
    vector<int> parent;    
    unordered_map<int, int> parentToArea;
    
public:
    UnionFind(vector<vector<int>> &grid){
        int m = grid.size();        
        int n = grid[0].size();
        
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    parent.push_back(i*n+j);
                    parentToArea[i*n+j] = 1;
                }
                else{
                    parent.push_back(-1);
                }
            }
        }
    }
    int Find (int x){
        if (parent[x] != x){
            parent[x] = Find(parent[x]);//注意，这里又写错了，必须要是Find(parent[x]);
        }
        return parent[x];
    }
    void Union(int x, int y){
        int rootx = Find(x);
        int rooty = Find(y);
        if (rootx != rooty){
            parent[rootx] = rooty;// 注意，这里是parent[rootx] 赋值为rooty
            parentToArea[rooty] += parentToArea[rootx];
            parentToArea.erase(rootx);            
        }
    }
    int GetMaxArea(){
        int ret = 0;
        for (auto iter : parentToArea){//注意这里 遍历不是指针，只能用 '.'
            ret = max(iter.second, ret);// 可以用.first 和 .second
        }
        return ret;
    }
};

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        if (!m) return 0;
        int n = grid[0].size();
        UnionFind uf(grid);
        
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (grid[i][j] == 1){  //每次访问后，不需要修改grid数组                  
                    if (0 <= i-1 && grid[i-1][j] == 1){                        
                        uf.Union(i*n+j, (i-1)*n+j);
                    }
                    if (i+1 < m && grid[i+1][j] == 1){                        
                        uf.Union(i*n+j, (i+1)*n+j);
                    }
                    if (0 <= j-1 && grid[i][j-1] == 1){                        
                        uf.Union(i*n+j, i*n+j-1);
                    }
                    if (j+1 < n && grid[i][j+1] == 1){                        
                        uf.Union(i*n+j, i*n+j+1);
                    }
                }
            }
        }    
        
        return uf.GetMaxArea();;
    }
};