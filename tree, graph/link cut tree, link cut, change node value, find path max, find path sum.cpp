/*

link cut tree, link cut, change node value, find path max, find path sum

https://oi.men.ci/link-cut-tree-notes/

*/

#include <cstdio>
#include <climits>
#include <algorithm>

const int MAXN = 30000;

void print(void *p);

template <typename T>
struct LinkCutTree {
	enum Relation {
		L = 0, R = 1
	};
	struct Node {
		Node *child[2], *parent, *pathParent;
		T value, sum, max;
		bool reversed;
		Node(const T &value) : reversed(false), value(value), sum(value), max(value), parent(NULL), pathParent(NULL) {
			child[L] = child[R] = NULL;
		}
		Relation relation() {
			return this == parent->child[L] ? L : R;
		}
		void pushDown() {
			if (reversed) {
				std::swap(child[L], child[R]);
				if (child[L]) child[L]->reversed ^= 1;
				if (child[R]) child[R]->reversed ^= 1;
				reversed = false;
			}
		}
		void maintain() {
			sum = value;
			if (child[L]) sum += child[L]->sum;
			if (child[R]) sum += child[R]->sum;

			max = value;
			if (child[L]) max = std::max(max, child[L]->max);
			if (child[R]) max = std::max(max, child[R]->max);
		}
		void rotate() {
			if (parent->parent) parent->parent->pushDown();
			parent->pushDown(), pushDown();
			std::swap(pathParent, parent->pathParent);

			Relation x = relation();
			Node *oldParent = parent;

			if (oldParent->parent) oldParent->parent->child[oldParent->relation()] = this;
			parent = oldParent->parent;

			oldParent->child[x] = child[x ^ 1];
			if (child[x ^ 1]) child[x ^ 1]->parent = oldParent;

			child[x ^ 1] = oldParent;
			oldParent->parent = this;

			oldParent->maintain(), maintain();
		}
		void splay() {
			while (parent) {
				if (!parent->parent) rotate();
				else {
					parent->parent->pushDown(), parent->pushDown();
					if (relation() == parent->relation()) parent->rotate(), rotate();
					else rotate(), rotate();
				}
			}
		}
		void evert() {
			access();
			splay();
			reversed ^= 1;
		}
		void expose() {
			splay();
			pushDown();
			if (child[R]) {
				child[R]->parent = NULL;
				child[R]->pathParent = this;
				child[R] = NULL;
				maintain();
			}
		}
		bool splice() {
			splay();
			if (!pathParent) return false;

			pathParent->expose();
			pathParent->child[R] = this;
			parent = pathParent;
			pathParent = NULL;
			parent->maintain();
			return true;
		}
		void access() {
			expose();
			while (splice());
		}
		const T &querySum() {
			access();
			splay();
			return sum;
		}
		const T &queryMax() {
			access();
			splay();
			return max;
		}
	};
	Node *nodes[MAXN];
	void makeTree(int u, const T &value) {
		nodes[u - 1] = new Node(value);
	}
	void link(int u, int v) {
		nodes[v - 1]->evert();
		nodes[v - 1]->pathParent = nodes[u - 1];
	}
	void cut(int u, int v) {
		nodes[u - 1]->evert();
		nodes[v - 1]->access();
		nodes[v - 1]->splay();
		nodes[v - 1]->pushDown();
		nodes[v - 1]->child[L]->parent = NULL;
		nodes[v - 1]->child[L] = NULL;
		nodes[v - 1]->maintain();
	}
	const T &querySum(int u, int v) {
		nodes[u - 1]->evert();
		return nodes[v - 1]->querySum();
	}
	const T &queryMax(int u, int v) {
		nodes[u - 1]->evert();
		return nodes[v - 1]->queryMax();
	}
	void update(int u, const T &value) {
		nodes[u - 1]->splay();
		nodes[u - 1]->value = value;
		nodes[u - 1]->maintain();
	}
};

struct UndirectedEdge {
	int u, v;
	UndirectedEdge(int u = 0, int v = 0) : u(u), v(v) {}
} edges[MAXN - 1];

int n, q;
LinkCutTree<int> lct;

void dfs(LinkCutTree<int>::Node *v, int depth) {
	if (!v) return;
	dfs(v->child[LinkCutTree<int>::L], depth + 1);
	for (int i = 0; i < depth; i++) putchar(' ');
	printf("%d, max = %d, sum = %d\n", v->value, v->max, v->sum);
	dfs(v->child[LinkCutTree<int>::R], depth + 1);
}

void print(void *p) {
	dfs((LinkCutTree<int>::Node *)p, 0);
}

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		edges[i] = UndirectedEdge(u, v);
	}

	for (int i = 1; i <= n; i++) {
		int value;
		scanf("%d", &value);
		lct.makeTree(i, value);
	}

	for (int i = 0; i < n - 1; i++) {
		lct.link(edges[i].u, edges[i].v);
	}

	scanf("%d", &q);

	for (int i = 0; i < q; i++) {
		char str[6 + 1];
		scanf("%s", str);
		if (str[0] == 'A') {
			int u, t;
			scanf("%d %d", &u, &t);
			lct.update(u, t);
		}
		else if (str[0] == 'B') {
			int u, v;
			scanf("%d %d", &u, &v);
			printf("%d\n", lct.queryMax(u, v));
		}
		else if (str[0] == 'C') {
			int u, v;
			scanf("%d %d", &u, &v);
			printf("%d\n", lct.querySum(u, v));
		}
		else if (str[0] == 'D') {
			int u, v;
			scanf("%d %d", &u, &v);
			lct.link(u, v);
		}
		else if (str[0] == 'E') {
			int u, v;
			scanf("%d %d", &u, &v);
			lct.cut(u, v);
		}
	}
	return 0;
}
