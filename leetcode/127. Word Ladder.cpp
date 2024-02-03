// https://leetcode.com/problems/word-ladder/description/

// A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

// Every adjacent pair of words differs by a single letter.
// Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
// sk == endWord
// Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

 

// Example 1:

// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// Output: 5
// Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
// Example 2:

// Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
// Output: 0
// Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

// Constraints:

// 1 <= beginWord.length <= 10
// endWord.length == beginWord.length
// 1 <= wordList.length <= 5000
// wordList[i].length == beginWord.length
// beginWord, endWord, and wordList[i] consist of lowercase English letters.
// beginWord != endWord
// All the words in wordList are unique.

// 方法一：
// 使用BFS，每次替换一个字符，就需要处理一层queue。所以一层queue里面要处理替换一个字符后的，所有可能字符串。
// 为了找到每个可能的分支，需要对处理的string(cur)的每个字符都做处理，将其替换一下后，看是否在wordList之内
//     如果新生成的string(tmp)在列表中，说明道路能走通，就加入queue，进入下轮循环，同时将这个新的tmp删除
//     如果不在，继续找下个候选子串
// 写法 1： 使用了unordered_map<int, unordered_set<char>> umap_i2c; 来存储word的某个index中，可能存在的字符集
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<int, unordered_set<char>> umap_i2c;
        unordered_set<string> uset_word;

        for (auto &word : wordList){
            for (int i = 0; i < word.size(); i++){
                umap_i2c[i].insert(word[i]);
            }
            uset_word.insert(word);
        }

        queue<string> q;
        int ret = 0;

        q.push(beginWord);
        while (!q.empty()){
            ret++;
            int num = q.size();
            for (int k = 0; k < num; k++){
                string cur = q.front(); q.pop();
                if (cur == endWord){
                    return ret;
                }
                for (int i = 0; i < cur.size(); i++){
                    for (auto c : umap_i2c[i]){
                        string tmp = cur;
                        tmp[i] = c;
                        if (uset_word.count(tmp)){
                            q.push(tmp);
                            uset_word.erase(tmp);
                        }
                    }                    
                }
            }
        }
        return 0;
    }
};

// 写法 2：不需要存储某个index下可能存在的字符集，直接就是 'a' -> 'z' 遍历即可
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> uset_word;

        for (auto &word : wordList){
            uset_word.insert(word);
        }

        queue<string> q;
        int ret = 0;

        q.push(beginWord);
        while (!q.empty()){
            ret++;
            int num = q.size();
            for (int k = 0; k < num; k++){
                string cur = q.front(); q.pop();
                if (cur == endWord){
                    return ret;
                }
                for (int i = 0; i < cur.size(); i++){
                    for (int c = 'a'; c <= 'z'; c++) {
                        string tmp = cur;
                        tmp[i] = c;
                        if (uset_word.count(tmp)){
                            q.push(tmp);
                            uset_word.erase(tmp);
                        }
                    }                    
                }
            }
        }
        return 0;
    }
};

//方法 二：
// 还是BFS，就是记录当前的step:

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string, int>> q;
        unordered_set<string> uset{wordList.begin(), wordList.end()};
        uset.erase(beginWord);
        q.push({beginWord, 1});

        while (!q.empty()){
            auto cur = q.front(); q.pop();
            string word = cur.first;
            int step = cur.second;
            
            if (word == endWord){
                return step;
            }
            for (int i = 0; i < word.size(); i++){
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++){
                    word[i] = ch;
                    if (uset.count(word) != 0){
                        uset.erase(word);// must remove this word, because it will be loop back 
                        q.push({word, step+1});
                    }
                }
                word[i] = original;
            }
        }
        return 0;
    }
};