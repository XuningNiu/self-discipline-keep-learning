class TrieNode{
public:
    unordered_map<char, TrieNode *> children;
    string word;
    bool isword;

    TrieNode(): isword(false), word(""){
    }
};
class Trie{
public:
    TrieNode root;

    void insert(string word){
        auto tmp = &root;
        for (auto c : word){
            if (tmp->children.count(c) == 0){
                tmp->children[c] = new TrieNode();
            }
            tmp = tmp->children[c];
        }
        tmp->isword = true;
        tmp->word = word;
    }
};
class Solution {
public:
    Trie wordTrie;
    vector<string> ret;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int m = board.size();
        int n = board[0].size();
        for (auto word : words){
            wordTrie.insert(word);
        }
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                dfs(board, i, j, &wordTrie.root);
            }
        }
        return ret;
    }
    void dfs(vector<vector<char>> & board, int x, int y, TrieNode *cur){
        int m = board.size();
        int n = board[0].size();

        if (cur->isword){
            ret.push_back(cur->word);
            cur->isword = false;
        }
        if (0 <= x && x < m && 0 <= y && y < n){
            int c = board[x][y];
            if (cur->children.count(c) == 0){
                return;
            }
            board[x][y] = '*';
            dfs(board, x, y+1, cur->children[c]);
            dfs(board, x, y-1, cur->children[c]);
            dfs(board, x+1, y, cur->children[c]);
            dfs(board, x-1, y, cur->children[c]);
            board[x][y] = c;
        }
        return;
    }
};