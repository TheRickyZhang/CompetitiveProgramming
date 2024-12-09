class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<vector<int>> adjList(n);
        vector<int> indegree(n);
        for(auto& vec : prerequisites) {
            int from = vec[1];
            int to = vec[0];
            adjList[from].push_back(to);
            indegree[to]++;
        }
        queue<int> q;
        vector<int> res;
        for(int i = 0; i < n; ++i) {
            if(indegree[i] == 0) q.push(i);
        }
        while(!q.empty()) {
            int from = q.front();
            q.pop();
            res.push_back(from);
            for(int to : adjList[from]) {
                if(--indegree[to] == 0) {
                    q.push(to);
                }
            }
        }
        return res.size() == n ? res : vector<int>();
    }
};