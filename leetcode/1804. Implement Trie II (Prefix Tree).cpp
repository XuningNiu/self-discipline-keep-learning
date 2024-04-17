class Trie {
private:
    struct TrieNode{
        vector<TrieNode*> children;
        int wordCount;
        int prefixCount;
        
        TrieNode():wordCount(0), prefixCount(0){
            children.resize(26, nullptr);
        }
    };
    TrieNode root;
public:
    Trie() {

    }
    
    void insert(string word) {
        TrieNode *cur = &root;
        for (int i = 0; i < word.size(); i++){
            char c = word[i];
            if (cur->children[c - 'a'] == nullptr){
                cur->children[c - 'a'] = new TrieNode();
            }
            
            cur = cur->children[c - 'a'];
            cur->prefixCount++;
        }
        cur->wordCount++;
    }
    
    int countWordsEqualTo(string word) {
        TrieNode *cur = &root;
        for (int i = 0; i < word.size(); i++){
            char c = word[i];
            if (cur->children[c - 'a'] == nullptr){
                return 0;
            }
            cur = cur->children[c - 'a'];
        }
        return cur->wordCount;
    }
    
    int countWordsStartingWith(string prefix) {
        TrieNode *cur = &root;
        for (int i = 0; i < prefix.size(); i++){
            char c = prefix[i];
            if (cur->children[c - 'a'] == nullptr){
                return 0;
            }
            cur = cur->children[c - 'a'];
        }
        return cur->prefixCount;
    }
    
    void erase(string word) {
        TrieNode *cur = &root;
        TrieNode *pre = nullptr;
        vector<TrieNode*> needFree;

        for (int i = 0; i < word.size(); i++){
            char c = word[i];
            if (cur->children[c - 'a'] == nullptr){
                return;
            }
            pre = cur;
            cur = pre->children[c - 'a'];
            if (cur->prefixCount > 0){
                cur->prefixCount--;
            }
            if (cur->prefixCount == 0){
                pre->children[c - 'a'] = nullptr;
                needFree.push_back(cur);
            }
        }
        cur->wordCount--;
        for (auto node : needFree){   ///===> 可以delete也可以留着最后自动删除
            delete(node);
        }
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */