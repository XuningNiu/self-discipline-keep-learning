// 1. 二分查找

int binarySearch(vector<int> &nums, int target){
    int l = 0;
    int r = nums.size();

    while (l < r){
        int mid = l + (r-l)/2;
        if (nums[mid] == target){
            return mid;
        }
        else if (nums[mid] < target){
            l = mid+1;
        }
        else{
            r = mid;
        }
    }
    if (l < nums.size() && nums[l] == target){
        return l;
    }
    return -1;
}
///
// 1.1 二分查找 upper_bound
// 1.2 二分查找 lower_bound
// 2 滑动窗口
void slidingWindow(string src, string search){
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;
    int left = 0, right = 0;
    int valid = 0;
        while (right < src.size()){
        //c 是移入窗口的字符
        char c = src[right];
        right++;
        //进行窗口内数据的操作
        while (window need shrink){
            // d 是移除窗口的字符
            char d = src[left];
            left++;
            //进行窗口内数据操作
        }
    }
}
//最小覆盖子串
class Solution{
public:
 string minWindow(string &source, string &target)  {
     unordered_map<char, int> counter_t, counter_s;
     for (char c : target) {
         counter_t[c]++;
     }
     int left = 0, valid = 0;
     int start = -1, minlen = INT_MAX;//the result substr's start and length
     for (int right = 0; right < source.size(); right++){
         //移动右边界，ch是将要移入窗口的字符
         char ch = source[right];
         if (counter_t.count(ch)){
             counter_s[ch]++;
             if (counter_s[ch] == counter_t[ch]){
                 valid++;
             }
         }
         //判断左侧窗口是否要收缩
         while (valid == counter_t.size()){
             //更新最小覆盖子串
             if (right - left < minlen){
                 start = left;
                 minlen = right - left;
             }
             //left_ch 是将要移除窗口的字符
             char left_ch = source[left];
             left++;
             if (counter_t.count(left_ch)){
                 if (counter_s[left_ch] == counter_t[left_ch]){
                     valid--;
                 }
                 counter_s[left_ch]--;
             }
         }
     }
     return start == -1 ? "" : source.substr(start, minlen+1);
 }
}
// 3 集合 排列
//回溯算法
// 回溯算法框架。解决一个回溯问题，实际上就是一个决策树的遍历过程。你只需要思考 3 个问题：

// 1、路径：也就是已经做出的选择。

// 2、选择列表：也就是你当前可以做的选择。

// 3、结束条件：也就是到达决策树底层，无法再做选择的条件。

// 如果你不理解这三个词语的解释，没关系，我们后面会用「全排列」和「N 皇后问题」这两个经典的回溯算法问题来帮你理解这些词语是什么意思，现在你先留着印象。

// 代码方面，回溯算法的框架：



// result = []
// def backtrack(路径, 选择列表):
//     if 满足结束条件:
//         result.add(路径)
//         return
//     for 选择 in 选择列表:
//         做选择
//         backtrack(路径, 选择列表)
//         撤销选择

// 核心操作详解：
//     for 选择 in 选择列表:
//     # 做选择
//     将该选择从选择列表移除
//     路径.add(选择)
//     backtrack(路径, 选择列表)
//     # 撤销选择
//     路径.remove(选择)
//     将该选择再加入选择列表


//排列组合
// 子集问题和组合问题一样的, 除了base case有点差别
// 形式 1： 元素无重复，不可复选。 即 nums 中的元素都是唯一的，每个元素最多只能被使用一次，backtrack核心代码：
 //组合/子集
void backtrack(vector<int> & nums, int start, vector<int> &track){
    //回溯算法标准框架
    //track 就是一个 组合/子集
    for (int i = start; i < nums.size(); i++){
        //做选择
        track.push_back(nums[i]);
        //参数+1， 注意
        backtrack(nums, i+1);
        //撤销选择
        track.pop_back();
    }
}
//代码实现：
// https://leetcode.com/problems/subsets/submissions/
vector<vector<int>> ret;
void back_trace(vector<int> &nums, int start, vector<int> &track){
    ret.push_back(track);
        for (int i = start; i < nums.size(); i++){
        track.push_back(nums[i]);
        back_trace(nums, i + 1, track);
        track.pop_back();
    }
    return;
}

vector<vector<int>> subsets(vector<int> &nums){
    vector<int> track;
    back_trace(nums, 0, track);
    return ret;
}
// 排列
void backtrack(vector<int> &nums, vector<bool> &used, vector<int> &track){
    for (int i = 0; i < nums.size(); i++){
        //剪枝逻辑
        if (used[i]){
            continue;
        }
        //做选择
        used[i] = true;
        track.push_back(nums[i]);
        backtrack(nums);
        //取消选择
        track.pop_back();
        used[i] = false;
    }
}


// 调用方式
vector<int> nums = {1, 2, 3};
vector<bool> used(nums.size(), false);
vector<int> track;
backtrack(nums, used, track);

// 形式 2：元素 （可重复， 不可复选），即 nums 中的元素可以存在重复，每个元素最多只能被使用一次，其关键在于排序和剪枝
// 组合/子集
sort(nums.begin(), nums.end());
void backtrack(vector<int> & nums, int start, vector<int> &track){
    //回溯算法标准框架
    for (int i = start; i < nums.size(); i++) {
        //剪枝逻辑，跳过值相同的相邻树枝
        if (i > start && nums[i] == nums[i - 1]){
            continue;
        }
        //做选择
        track.push_back(nums[i]);
        //注意参数 + 1
        backtrack(nums, i+1, track);
        //撤销选择
        track.pop_back();
    }
}
//调用方式
vector<int> nums = {3, 1, 2, 2};
sort(nums.begin(), nums.end());
vector<int> track;
backtrack(nums, 0, track);

//排列
sort(nums.begin(), nums.end());
void backtrack(vector<int> &nums, vector<int> &used, vector<int> &track){
    for (int i = 0; i < nums.size(); i++){
        //剪枝逻辑1
        if (used[i]){
            continue;
        }
        //剪枝逻辑2, 固定相同的元素在排列中的相对位置
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]){
            continue;
        }
        //做选择
        used[i] = true;
        track.push_back(nums[i]);
        backtrack(nums, track);
        //取消选择
        track.pop_back();
        used[i] = false;
    }
}
//调用方式
vector<int> nums = {3, 1, 2, 2};
sort(nums.begin(), nums.end());
vector<int> track;
vector<bool> used(nums.size(), false);
backtrack(nums, used, track);

// 形式 3. 元素 （无重复，可复选），即 nums 中的元素都是唯一的，每个元素可以被使用若干次，只要删除去重逻辑即可。
// 组合/子集
void backtrack(vector<int> nums, int start, vector<int> &track){
    for (int i = start, i < nums.size(); i++){
        //做选择
        track.pushback(nums[i]);
        //参数+1
        backtrack(nums, i+1, track);
        //撤销选择
        track.pop_back();
    }
}

//排列
void backtrack(vector<int> &nums){
    for (int i = 0; i < nums.length; i++){
        track.push_back(nums[i]);
        backtrack(nums);
        track.pop_back();
    }
}

// 4 BFS DFS
// 5 循环数组
// 6 二叉树
// 7 图
// 7.1 最短路径
// 7.2 双色问题
// 7.3 合法的树
/*思路：要判断一个图是否为树，首先要知道树的定义。
    一棵树必须具备如下特性：

    （1）是一个全连通图（所有节点相通）

    （2）无回路 =====》 等价于：（3）图的边数=节点数-1
    */
bool validTree(int n, vector<vector<int>> &edges){
    if (n == 0) return false;
    if (edges.size() != n-1) return false;
    if (n == 1) return true;

    queue<int> q;
    unordered_set<int> visited;
    unordered_map<int, unordered_set<int>> umap;

    for (auto &edge:edges){
        umap[edge[0]].insert(edge[1]);
        umap[edge[1]].insert(edge[0]);
    }
    q.push(0);
    visited.insert(0);
    while (!q.empty()){
        int size = q.size()
        for (int i = 0; i < size; i++){
            int cur = q.front(); q.pop();
            for (auto &node : umap[cur]){
                if (!visited.count(node)){
                    visited.insert(node);
                    q.push(node);
                }
            }
        }
    }
    if (visited.size() == n){
        return true;
    }
    return false;
}
// 7.4 最小生成树
// 7.5 拓扑排序

// 8 双指针
// 8.1
// 9 计算器
class Solution{
public:
    int helper(string &s, int start, int &end){
        char sign = '+';
        int num = 0;
        int ret = 0;
        stack<int> stk;
        int tmp = 0;

        for (int i = start; i < s.size(); i++){
            auto c = [i];
            if (c = '('){
                int next = 0;
                num = helper(s, i+1, next);
                i = next;
            }
            if (isdigit(c)){
                num = num*10 + (c - '0');
            }
            if (i == s.size()-1 || (!isdigit(c) && c != ' ')){
                switch(sign){
                    case '+':
                        stk.push(num);
                        break;
                    case '-':
                        stk.push(-num);
                        break;
                    case '*':
                        tmp = stk.top()*num;
                        stk.pop();
                        stk.push(tmp);
                        break;
                    case '/':
                        tmp = stk.top()/num;
                        stk.pop();
                        stk.push(tmp);
                        break;
                    default:
                        break;
                }
                sign = c;
                num = 0;
            }
           if (c == ')'){
                end = i;
                break;
            }
        }
        while (!stk.empty()){
            ret += stk.top();
            stk.pop();
        }
        return ret;
    }
    int calculate(string s){
        int index = 0;
        return helper(s, 0, index);
    }
}

// 10 LRU LFU
// 11 LCA 最近公共祖先
   236. lowest Common Ancestor of a Binary Tree
class Solution{
public:
    TreeNode * LCA(TreeNode *root, TreeNode *p, TreeNode *q){
        if (root == NULL || root == p || root == q){
            return root;
        }
        TreeNode *left = LCA(root->left, p, q);
        TreeNode *right = LCA(root->right, p, q);

        if (left == nullptr){
            return right;
        }
        else if (right == nullptr){
            return left;
        }
        else{
            return root;
        }
    }
    TreeNode * lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q){
        return LCA(root, p, q);
    }
}

// 12. 并查集
class Solution{
public:
    class UnionFind{
        public:
            unordered_map<int, int> father;
            unordered_map<int, unordered_set<int>> f2s;//father to set

            void add(int x){
                if (father.count(x) == 0){
                    father[x] = x;
                    f2s[x].insert(x);
                }
            }
            int find(int x){
                int root = father[x];
                while (root != father[root]){
                    root = father[root];
                }
                while (x != father[x]){
                    int origin = father[x];
                    father[x] = root;
                    x = father[x];
                }
                return root;
            }
            void connect(int x, int y){
                int root_x = find(x);
                int root_y = find(y);
                if (root_x != root_y){
                    father[root_y] = root_x;
                    f2s[root_x].insert(f2s[root_y].begin(), f2s[root_y].end());
                    f2s.erase(root_y);
                }
            }
            bool isConnect(int x, int y){
                return find(x) == find(y);
            }
            int numOfSet(){
                return f2s.size();
            }
    }
}

// 13. 字典树

class TrieNode{
public:
    unordered_map<char, TrieNode *> children;
    bool isWord;
    string word;
    TrieNode(){
        isWord = false;
        word = "";
    }
}
// 14. 各种排序算法
// merge sort

// 15. 分类，一个名字，后面一堆邮箱