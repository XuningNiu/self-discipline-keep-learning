//从左向右扫描，
//   如果遇到start，就入栈；
//   如果遇到end，就计算，并把栈中的start去掉组成一对。（前面一定是个start，因为都是成对消除的）

  

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<int> stk;
        int pre_time;
        vector<int> ret(n, 0);

        for (string log : logs){
            int find1 = log.find(':');
            int find2 = log.find(':', find1+1);
            int id = stoi(log.substr(0, find1));
            string exe = log.substr(find1+1, find2-find1-1);
            int time = stoi(log.substr(find2+1));
            if (exe == "end"){
                int pre_id = stk.top(); stk.pop();
////----》 千万注意，这里的end表示当前的id 是end（只有1）,而pre_id是从pre_time到当前的时间在执行。pre_id可以与id相同也可以不同
                ret[id] += 1;       
                ret[pre_id] += time - pre_time;
                pre_time = time + 1;
            }
            else{
                if (!stk.empty()){
                    int pre_id = stk.top();
                    ret[pre_id] += time - pre_time;
                }
                stk.push(id);
                pre_time = time;
            }
        }
        return ret;
    }
};