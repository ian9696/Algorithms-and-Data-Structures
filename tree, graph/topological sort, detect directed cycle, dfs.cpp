/*

https://leetcode.com/problems/course-schedule-ii/description/

*/

class Solution {
public:
    bool dfs(int u, vector<vector<int>> &adj, vector<int> &state, vector<int> &ans){
        if(state[u]==1)
            return true;
        if(state[u]==-1)
            return false;
        state[u]=-1;
        for(int v: adj[u]){
            if(!dfs(v, adj, state, ans))
                return false;
        }
        state[u]=1;
        ans.push_back(u);
        return true;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> ans, state(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        for(vector<int> &e: prerequisites){
            adj[e[0]].push_back(e[1]);
        }
        for(int i=0; i<numCourses; i++){
            if(!dfs(i, adj, state, ans))
                return {};
        }
        return ans;
    }
};
