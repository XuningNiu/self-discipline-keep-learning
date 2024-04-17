class Solution {
public:
    using PII = pair<int, int>;
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        int totalCost = 0;
        int connectedCount = 1;  // 已连接的顶点计数，初始为1
        vector<bool> visited(n);
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        // priority_queue<PII, vector<PII>, decltype([](auto &p1, auto &p2){
        //     return p1.first > p2.first;
        // })> pq;

        // 从第一个顶点开始
        visited[0] = true;

        // 将第一个顶点与其他顶点的边加入优先队列
        for (int j = 1; j < n; ++j) {
            int cost = abs(points[0][0] - points[j][0]) + abs(points[0][1] - points[j][1]);
            pq.push({cost, j});
        }

        // 构建最小生成树
        while (connectedCount < n) {
            int cost = pq.top().first;
            int index = pq.top().second;
            pq.pop();

            // 如果顶点已访问过，则跳过
            if (visited[index]) {
                continue;
            }

            totalCost += cost;
            visited[index] = true;
            connectedCount++;

            // 将新连接的顶点与其他未访问的顶点的边加入优先队列
            for (int j = 0; j < n; ++j) {
                if (!visited[j]) {
                    int cost = abs(points[index][0] - points[j][0]) + abs(points[index][1] - points[j][1]);
                    pq.push({cost, j});
                }
            }
        }

        return totalCost;
    }
};