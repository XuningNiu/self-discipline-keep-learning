//772. Basic Calculator III

// Implement a basic calculator to evaluate a simple expression string.

// The expression string contains only non-negative integers, '+', '-', '*', '/' operators, and open '(' and closing parentheses ')'. The integer division should truncate toward zero.

// You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

// Example 1:

// Input: s = "1+1"
// Output: 2
// Example 2:

// Input: s = "6-4/2"
// Output: 4
// Example 3:

// Input: s = "2*(5+5*2)/3+(6/2+8)"
// Output: 21
方法一：堆栈

class Solution {
private:
    struct Node{
        int ret;
        int preSum;        
        char sign;
    };
    void helper(int num, int sign, int &ret, int & preSum){
        switch(sign){
            case '+':{
                ret += preSum;
                preSum = num;
                break;
            }
            case '-':{
                ret += preSum;
                preSum = -num; // <<<<< 注意这里是把sign的符号吸过来，所以变减号。 目的是为了乘除法运行带符号
                break;
            }
            case '*':{
                preSum *= num;
                break;
            }
            case '/':{
                preSum /= num;
                break;
            }
        }
    }
public:
    int calculate(string s) {
        int num = 0;
        int preSum = 0;
        int ret = 0;
        char sign = '+';
        stack<Node> stk;

        for (auto c : s){
            if (isdigit(c)){
                num = num*10 + (c - '0');
            }
            else if (c == '('){
                stk.push({ret, preSum, sign});
                ret = 0; preSum = 0; sign = '+';
            }
            else if (c == ')'){
                helper(num, sign, ret, preSum);
                auto node = stk.top(); stk.pop();
                num = ret + preSum; // <<<<< 注意这里要计算出来完整的ret作为括号内部的返回值
                preSum = node.preSum;
                sign = node.sign;
                ret = node.ret;
            }
            else if (c != ' '){
                helper(num, sign, ret, preSum);
                num = 0;
                sign = c;
            }
        }
        helper(num, sign, ret, preSum);
        return ret + preSum;
    }
};

方法二： 递归
class Solution {
public:
    int helper(string &s, int start, int &end){
        char sign = '+';
        int num = 0;
        int pre_sum = 0;
        int ret = 0;

        for (int i = start; i < s.size(); i++){
            char c = s[i];

            if (isdigit(c)){
                num = num*10 + (c - '0');
            }
            if (c == '('){
                int next = 0;
                num = helper(s, i+1, next);
                i = next;
                //// 错误continue
                //// <<<<<<<<<<<<============== 这里千万不能continue，而是需要下面的switch case来处理新得到的num,更新ret和preSum 
            }            

            if ((!isdigit(c) && c != ' ') || i == s.size()-1){
                switch(sign){
                    case '+':{
                        ret += pre_sum;
                        pre_sum = num;
                        break;
                    }
                    case '-':{
                        ret += pre_sum;
                        pre_sum = -num;
                        break;
                    }
                    case '*':{
                        pre_sum *= num;
                        break;
                    }
                    case '/':{
                        pre_sum /= num;
                        break;
                    }
                }
                num = 0;
                sign = c;
            }

            if (c == ')'){ ///<<<<<<这里不能放到switch case前面，因为必须要经过那一步来更新ret 和 preSum
                end = i;
                break;
            }
        }
        ret += pre_sum;
        return ret;
    }

    int calculate(string s) {
        int end;
        return helper(s, 0, end);
    }
};
https://leetcode.com/problems/basic-calculator/description/
// 224. Basic Calculator
// Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.

// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

// Example 1:

// Input: s = "1 + 1"
// Output: 2
// Example 2:

// Input: s = " 2-1 + 2 "
// Output: 3
// Example 3:

// Input: s = "(1+(4+5+2)-3)+(6+8)"
// Output: 23
方法一： 堆栈
class Solution {
public:
    int calculate(string s) {
        int num = 0;
        int ret = 0;
        int sign = 1;
        stack<pair<int, int>> stk; //ret, sign

        for (int i = 0; i < s.size(); i++){
            char c = s[i];
            if (isdigit(c)){
                num = num*10 + (c - '0');
            }
            if (!isdigit(c) && c != ' '){ //这里也可以使用else if (c != ' ')
                ret += sign*num;
                num = 0;
                switch(c){
                    case '+':{
                        sign = 1;
                        break;
                    }
                    case '-':{                        
                        sign = -1;
                        break;
                    }
                    case '(':{
                        stk.push({ret, sign});
                        sign = 1;
                        ret = 0;   //===> 千万注意这里要置零
                        break;
                    }
                    case ')':{
                        auto preRet = stk.top().first;
                        auto preSign = stk.top().second;
                        stk.pop();
                        ret = preRet + preSign*ret;
                        break;
                    }
                }
            }
        }
        return ret + sign * num; //如果上面没有处理最后字符，这里要再加一次
    }
};

方法二： 递归
递归写法一：
class Solution {
private:
    int helper(string &s, int start, int &end){
        int num = 0;
        int ret = 0;
        int sign = 1;
        
        for (int i = start; i < s.size(); i++){
            char c = s[i];
            if (isdigit(c)){
                num = num*10 + (c - '0');
            }
            else if (c == '('){
                int next;
                num = helper(s, i+1, next);
                i = next;
            }
            else if (c == ')'){
                end = i;
                break;
            }
            else if (c != ' '){
                ret += sign * num;
                num = 0;
                sign = (c == '+')? 1 : -1;
            }
        }
        return ret + sign * num;
    }
public:
    int calculate(string s) {
        int end;
        return helper(s, 0, end);
    }
};
递归写法二：
class Solution {
private:
    int helper(string &s, int start, int &end){
        int num = 0;
        int ret = 0;
        int sign = 1;

        for (int i = start; i < s.size(); i++){
            char c = s[i];
            if (isdigit(c)){
                num = num*10 + (c - '0');
            }
            if (c == '('){
                int end;
                num = helper(s, i+1, end);
                i = end;
                continue;
            }
            if (!isdigit(c) && c != ' '){
                ret += sign*num;
                num = 0;
                switch(c){
                    case '+':{
                        sign = 1;
                        break;
                    }
                    case '-':{
                        sign = -1;
                        break;
                    }
                }
            }
            if (c == ')'){
                ret += sign*num;
                end = i;
                return ret;
            }
        }
        return ret + sign*num;
    }
public:
    int calculate(string s) {
        int end;
        return helper(s, 0, end);
    }
};


https://leetcode.com/problems/basic-calculator-ii/description/
// 227. Basic Calculator II

// Given a string s which represents an expression, evaluate this expression and return its value. 

// The integer division should truncate toward zero.

// You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

// Example 1:

// Input: s = "3+2*2"
// Output: 7
// Example 2:

// Input: s = " 3/2 "
// Output: 1
// Example 3:

// Input: s = " 3+5 / 2 "
// Output: 5

class Solution {
public:
    int calculate(string s) {
        int num = 0;
        int ret = 0;
        int preNum = 0;
        char sign = '+';

        for (int i = 0; i < s.size(); i++){
            char c = s[i];
            if (isdigit(c)){
                num = num*10 + (c-'0');
            }
            if ((!isdigit(c) && c != ' ') || i == s.size()-1){// 注意这里必须要处理最后一个字符 “i == s.size()-1”
                switch(sign){
                    case '+':{
                        ret += preNum;
                        preNum = num;
                        break;
                    }
                    case '-':{
                        ret += preNum;
                        preNum = -num;
                        break;
                    }
                    case '*':{
                        preNum *= num;
                        break;
                    }
                    case '/':{
                        preNum /= num;
                        break;
                    }
                }
                sign = c;
                num = 0;
            }
        }
        ret += preNum;
        return ret;
    }
};