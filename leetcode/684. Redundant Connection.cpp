class Solution {
class UnionFind{
private:
    unordered_map<int, int> father;
public:
    void add(int x){
        if (father.count(x)){
            return;
        }
        father[x] = x;
    }
    int find(int x){
        int root = father[x];
        while (root != father[root]){
            root = father[root];
        }
        while (x != father[x]){
            int origin = father[x];
            father[x] = root;
            x = origin;
        }
        return root;
    }
    void merge(int x, int y){
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty){
            father[rooty] = rootx;
        }
    }
    bool isConnected(int x, int y){
        int rootx = find(x);
        int rooty = find(y);
        if (rootx == rooty){
            return true;
        }
        return false;
    }
};
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        UnionFind uf;
        int n = edges.size();

        for (int i = 1; i <= n; i++){
            uf.add(i);
        }
        for (auto edge : edges){
            if (uf.isConnected(edge[0], edge[1])){
                return {edge[0], edge[1]};
            }
            uf.merge(edge[0], edge[1]);
        }
        return {};
    }
};