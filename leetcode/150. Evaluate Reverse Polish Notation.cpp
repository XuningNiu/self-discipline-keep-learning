    class Solution {
    public:
        int evalRPN(vector<string>& tokens) {
            stack<int> stk;
            int ret = 0;
            for (string &s : tokens){
                int num = 0;
                if (s != "+" && s != "-" && s != "*" && s != "/"){
                    num = stoi(s);
                    stk.push(num);
                }
                else{
                    int tmp2 = stk.top(); stk.pop();
                    int tmp1 = stk.top(); stk.pop();
                    if (s == "+"){                    
                        stk.push(tmp1+tmp2);
                    }
                    else if (s == "-"){
                        stk.push(tmp1-tmp2);
                    }
                    else if (s == "*"){
                        stk.push(tmp1*tmp2);
                    }
                    else if (s == "/"){
                        stk.push(tmp1/tmp2);
                    }
                }
            }
            return stk.top();
        }
    };