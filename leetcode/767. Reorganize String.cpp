class Solution {
public:
    string reorganizeString(string s) {
        int n = s.size();
        unordered_map<char, int> umap;
        int max_count = 0;
        char max_char;

        for (auto c : s){
            umap[c]++;
            if (max_count < umap[c]){
                max_count = umap[c];
                max_char = c;
            }
        }
        if (max_count > (n - max_count) + 1){
            return "";
        }

        string ret(n, '0');
        int i = 0;
        while (max_count > 0){
            ret[i] = max_char;
            i += 2;
            max_count--;
        }

        for (auto node : umap){
            if (node.first == max_char){
                continue;
            }
            int count = node.second;
            while (count > 0){
                if (i >= n) {
                    i = 1;
                }
                ret[i] = node.first;
                i += 2;
                count--;
            }
        }
        return ret;
    }
};