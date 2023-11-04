/*

KMP algorithm

https://leetcode.com/problems/substring-with-concatenation-of-all-words/

*/

class Solution {
public:
    void update(const string &s, int n, const string &t, int w,
                int id, vector<int> &has){
        vector<int> f(w, 0);
        for(int i=1, p=0; i<w; i++){
            while(p>0 && t[p]!=t[i]){
                p=f[p-1];
            }
            if(t[p]==t[i]){
                p++;
            }
            f[i]=p;
        }
        for(int i=0, p=0; i<n; i++){
            while(p>0 && s[i]!=t[p]){
                p=f[p-1];
            }
            if(s[i]==t[p]){
                p++;
            }
            if(p==w){
                has[i-w+1]=id;
                p=f[p-1];
            }
        }
    }
    void add(int id, int &cnt2, vector<int> &expect){
        if(id==-1)
            return;
        expect[id]--;
        if(expect[id]==0){
            cnt2++;
        }
    }
    void del(int id, int &cnt2, vector<int> &expect){
        if(id==-1)
            return;
        expect[id]++;
        if(expect[id]==1){
            cnt2--;
        }
    }
    vector<int> findSubstring(string s, vector<string>& words) {
        int n=s.size(), m=words.size(), w=words[0].size();
        map<string, int> id;
        for(string &t: words){
            id[t]=1;
        }
        int m2=0;
        for(map<string, int>::iterator it=id.begin(); it!=id.end(); it++){
            it->second=m2++;
        }
        vector<int> has(n, -1);
        for(map<string, int>::iterator it=id.begin(); it!=id.end(); it++){
            update(s, n, it->first, w, it->second, has);
        }
        vector<int> ans;
        for(int i=0; i<w; i++){
            vector<int> expect(m2, 0);
            for(string &t: words){
                expect[id[t]]++;
            }
            int cnt2=0;
            for(int j=i; j+m*w<=n; j+=w){
                if(j==i){
                    for(int k=j; k<j+m*w; k+=w){
                        add(has[k], cnt2, expect);
                    }
                }
                else{
                    del(has[j-w], cnt2, expect);
                    add(has[j+(m-1)*w], cnt2, expect);
                }
                if(cnt2==m2){
                    ans.push_back(j);
                }
            }
        }
        return ans;
    }
};
