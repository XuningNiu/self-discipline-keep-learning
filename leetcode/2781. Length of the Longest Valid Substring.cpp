//https://leetcode.com/problems/length-of-the-longest-valid-substring/
// You are given a string word and an array of strings forbidden.

// A string is called valid if none of its substrings are present in forbidden.

// Return the length of the longest valid substring of the string word.

// A substring is a contiguous sequence of characters in a string, possibly empty.

 

// Example 1:

// Input: word = "cbaaaabc", forbidden = ["aaa","cb"]
// Output: 4
// Explanation: There are 11 valid substrings in word: "c", "b", "a", "ba", "aa", "bc", "baa", "aab", "ab", "abc" and "aabc". The length of the longest valid substring is 4. 
// It can be shown that all other substrings contain either "aaa" or "cb" as a substring. 
// Example 2:

// Input: word = "leetcode", forbidden = ["de","le","e"]
// Output: 4
// Explanation: There are 11 valid substrings in word: "l", "t", "c", "o", "d", "tc", "co", "od", "tco", "cod", and "tcod". The length of the longest valid substring is 4.
// It can be shown that all other substrings contain either "de", "le", or "e" as a substring. 

// 方法一：
// sliding window，需要两层遍历，外层和内层遍历的方向需要相反。
// 基本原理是： 外层遍历每取得一个新的字符，内层就需要判断包括这个字符的所有可能被forbidden的子串，并且剔除这个可能性。
// 那么使用反方向的遍历能找到最短的匹配forbidden子串的情况。 比如：
// aaabc, "aaa"; 假如外层从左向右遍历（右指针），内层（临时指针，或者临时的子串）只需要从右向左一个个找到是否有匹配的aaa，
//               1. 如果没有就继续走外层下一个字符。
//               2. 如果匹配到了aaa，那么就需要左边指针右移一个。
// 假如外层从右向左遍历，也是一样，下面写出两种情况的代码。

//写法一：
class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        unordered_set<string> uset{forbidden.begin(), forbidden.end()};
        int ret = 0;
        int l = 0;

        //sliding window， 外层从左向右
        for (int r = 0; r < word.size(); r++){
            //内层从右向左，包括新的字符情况下，找到第一个能匹配forbidden里面的subarray
            for (int i = r; i >= l && i > r-10; i--){
                if (uset.count(word.substr(i, r-i+1)) != 0) {
                    l = i+1;
                    break;
                }
            }
            ret = max(ret, r-l+1);
        }
        return ret;
    }
};

//写法二：
class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        int ret = 0;
        int n = word.size();
        int r = n-1;
        int l = 0;
        unordered_set<string> uset{forbidden.begin(), forbidden.end()};
        
        for (l = n-1; l >= 0; l--) {
            //外层从右往左遍历，内层从左往右找
            string tmp = "";
            for (int i = l; i <= r && i < l+10; i++){
                tmp += word[i];
                if (uset.count(tmp)){
                    r = i-1;
                    break;
                }
            }
            ret = max(ret, r-l+1);
        }
        return ret;
    }
};
