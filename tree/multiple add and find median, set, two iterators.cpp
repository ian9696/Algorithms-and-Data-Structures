/*

https://leetcode.com/problems/find-median-from-data-stream/

*/

#include <iostream>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
using namespace std;

class MedianFinder {
public:
    MedianFinder() {

    }
    multiset<pair<int, int>> s;
    set<pair<int, int>>::iterator li, ri;
    int l, r;
    void next() {
        set<pair<int, int>>::iterator* p;
        int* q;
        if (li == ri && l == r)
            p = &ri, q = &r;
        else
            p = &li, q = &l;
        if (*q == (*p)->second)
            (*p)++, (*q) = 1;
        else
            (*q)++;
    }
    void prev() {
        set<pair<int, int>>::iterator* p;
        int* q;
        if (li == ri && l == r)
            p = &li, q = &l;
        else
            p = &ri, q = &r;
        if (*q == 1)
            (*p)--, (*q) = (*p)->second;
        else
            (*q)--;
    }
    void addNum(int num) {
        printf("add %d\n", num);
        if (s.empty()) {
            li = ri = s.insert({ num, 1 });
            l = r = 1;
            return;
        }
        auto p = s.lower_bound({ num, 0 });
        if (p != s.end() && p->first == num) {
            auto t = *p;
            t.second++;
            bool ul = li == p, ur = ri == p;
            s.erase(p);
            p = s.insert(t);
            if (ul)
                li = p;
            if (ur)
                ri = p;
        }
        else
            s.insert({ num, 1 });
        if (num < li->first)
            prev();
        else if (ri->first < num)
            next();
        else if (num == ri->first)
            next();
        else {
            next();
            prev();
        }
    }
    double findMedian() {
        printf("l %d %d  %d\n", li->first, li->second, l);
        printf("r %d %d  %d\n", ri->first, ri->second, r);
        return (double)(li->first + ri->first) / 2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

int main()
{
	vector<string> u = { "addNum", "findMedian" };
	vector<int> v = { 18, 1000000 };
	int n = u.size();

    MedianFinder obj;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
		if (u[i] == "findMedian") {
            double t=obj.findMedian();
            printf("findMedian %lf\n", t);
            sort(ans.begin(), ans.end());
            int m = ans.size();
            int l = (m - 1) / 2, r = m / 2;
            double a = (double)(ans[l] + ans[r]) / 2;
            if (obj.li->first!=ans[l] || obj.ri->first!=ans[r]) {
                printf("i=%d, l=%d ans[l]=%d, r=%d ans[r]=%d\n", i, l, ans[l], r, ans[r]);
                break;
            }
		}
		else {
            obj.addNum(v[i]);
            ans.push_back(v[i]);
		}
	}
	printf("done\n");
}
