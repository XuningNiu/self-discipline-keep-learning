//标准的迪杰斯特拉算法
using PII = pair<int, int>;
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int, int>>> graph;
        vector<int> dist(n+1, INT_MAX);
        priority_queue<PII, vector<PII>, greater<PII>> pq;////<<<<<<<<注意这里是 小顶堆

        //build graph
        for (auto &time : times){
            graph[time[0]].push_back({time[2], time[1]});
        }

        pq.push({0, k});
        dist[k] = 0;
        while (!pq.empty()){
            auto pa = pq.top(); pq.pop();
            for (auto &next : graph[pa.second]){
                // next.first   : the time from pa to next
                // next.second  : the node id
                int disNext = pa.first + next.first;  ////<<<<注意这里是加上, 并且要注意是first还是second
                if (disNext < dist[next.second]){
                    dist[next.second] = disNext;
                    pq.push({disNext, next.second}); /// <<<<<<< 注意这里把下一个节点放到pq中
                }
            }            
        }
        int ret = 0;
        for (int i = 1; i <= n; i++){
            if (dist[i] == INT_MAX){ ////<<<<注意判断是否全部都链接上了
                return -1;
            }
            ret = max(ret, dist[i]);
        }
        return ret;
    }
};