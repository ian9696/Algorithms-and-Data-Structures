/*

treap, pointer

*/

#include<iostream>//cin, cout
#include<string.h>//memset
#include<algorithm>//sort, swap, fill, lower_bound, upper_bound, next_permutation, prev_permutation, min, max
#include<iomanip>//setw
#include<vector>//vector
#include<queue>//queue
#include<set>//set
#include<string>//string operator
#include<stack>//stack
#include<fstream>//ifstream, ofstream
#include<bitset>//bitset
using namespace std;

struct treap
{
	struct node
	{
		node *l, *r;
		long long int key, val, pri;
		node(long long int _key, long long int _val)
		{
			l = r = nullptr;
			key = _key;
			val = _val;
			pri = rand();
		}
		~node()
		{
			if (l != nullptr)
				delete l;
			if (r != nullptr)
				delete r;
		}
	};

	node *root;

	treap()
	{
		srand(0x3FFFFFFF);
		root = nullptr;
	}
	~treap()
	{
		if (root != nullptr)
			delete root;
	}

	long long int getval(node *p)
	{
		if (p == nullptr)
			return 0;
		else
			return p->val;
	}
	void pull(node *p)
	{
		if (p == nullptr)
			return;

		p->val = 1 + getval(p->l) + getval(p->r);
	}
	node* merge(node *l, node *r)
	{
		if (l == nullptr)
			return r;
		else if (r == nullptr)
			return l;

		if (l->pri < r->pri)
		{
			r->l = merge(l, r->l);
			pull(r);
			return r;
		}
		else
		{
			l->r = merge(l->r, r);
			pull(l);
			return l;
		}
	}
	void split(node *p, long long int key, node *&l, node *&r)
	{
		if (p == nullptr)
		{
			l = r = nullptr;
		}
		else
		{
			if (p->key <= key)
			{
				l = p;
				split(l->r, key, l->r, r);
				pull(l);
			}
			else
			{
				r = p;
				split(r->l, key, l, r->l);
				pull(r);
			}

		}
	}
	long long int kth(node *p, long long int k)
	{
		if (p == nullptr || k > p->val)
			return 0x3FFFFFFF;

		if (k <= getval(p->l))
			return kth(p->l, k);
		else if (k == getval(p->l) + 1)
			return p->key;
		else
			return kth(p->r, k - getval(p->l) - 1);
	}
	long long int count(node *p, long long int x)
	{
		if (p == nullptr)
			return 0;

		if (p->key <x)
			return getval(p->l) + 1 + count(p->r, x);
		else
			return count(p->l, x);
	}
	void insert(long long int key)
	{
		node *l, *r;
		split(root, key, l, r);
		split(l, key - 1, l, root);
		if (root != nullptr)
			delete root;
		l = merge(l, new node(key, 1));
		root = merge(l, r);
	}

	void del(long long int key)
	{
		node *l, *r;
		split(root, key, l, r);
		split(l, key - 1, l, root);
		if (root != nullptr)
			delete root;
		root = merge(l, r);
	}

	void print(node *p)
	{
		if (p == nullptr)
			return;

		print(p->l);
		printf("addr:%d key:%d val:%d l:%d r:%d\n", p, p->key, p->val, p->l, p->r);
		print(p->r);
	}

};

int main()
{
	/*
	srand(time(nullptr));
	for (int j = 0; j < 10000; j++)
	{
	treap t;

	bitset<500> exist(0);
	for (int i = 0; i < j; i++)
	{
	int ran = rand();
	int ran2 = rand() % 500;
	if (ran % 2 == 0)
	{
	t.insert(ran2);
	exist[ran2] = true;
	}
	else
	{
	t.del(ran2);
	exist[ran2] = false;
	}
	}

	//cout << exist.count() << endl;
	//cout << t.count(t.root, 500) << endl;
	if (exist.count() != t.count(t.root, 500))
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	}
	*/
	/*
		for (long long int j = 0; j < 77; j++)
		{
		for (long long int i = 0; i < 100; i++)
		t.insert(i);
		for (long long int i = 0; i < 100; i++)
		t.del(i-5);
		}

		for (long long int i = 1; i <= 10; i++)
		{
		if (t.kth(t.root, i) == 0x3FFFFFFF)
		cout << "invalid" << endl;
		else
		cout << t.kth(t.root, i) << endl;
		}
		cout << endl;
		*/


	treap t;

	int Q = 0;
	scanf("%d\n", &Q);
	char com;
	int com2;
	while (Q--)
	{
		scanf("%c %d\n", &com, &com2);
		switch (com)
		{
		case 'I':
			t.insert(com2);
			break;
		case 'D':
			t.del(com2);
			break;
		case 'K':
			if (t.kth(t.root, com2) == 0x3FFFFFFF)
				printf("invalid\n");
			else
				printf("%d\n", t.kth(t.root, com2));
			break;
		case 'C':
			printf("%d\n", t.count(t.root, com2));
			break;
		}

		/*
		for (long long int i = 0; i < t.count(t.root, 0x3FFFFFFF); i++)
			cout << t.kth(t.root, i+1) << " ";
		cout << endl;
		*/
	}

	/*
	long long int Q = 0;
	cin >> Q;
	vector<long long int> v;
	while (Q--)
	{
	char com;
	long long int com2;
	cin >> com >> com2;
	switch (com)
	{
	case 'I':
	{
	sort(v.begin(), v.end());
	auto it = lower_bound(v.begin(), v.end(), com2);
	if (it != v.end() && *it==com2)
	;
	else
	v.push_back(com2);
	break;
	}
	case 'D':
	{
	sort(v.begin(), v.end());
	auto it = lower_bound(v.begin(), v.end(), com2);
	if (it != v.end() && *it == com2)
	*it = 0x3FFFFFFF;
	else
	;
	break;
	}
	case 'K':
	sort(v.begin(), v.end());
	if (lower_bound(v.begin(), v.end(), 0x3FFFFFFF) - v.begin() >= com2)
	cout << v[com2-1] << endl;
	else
	cout << "invalid" << endl;
	break;
	case 'C':
	sort(v.begin(), v.end());
	cout << (lower_bound(v.begin(), v.end(), com2) - v.begin()) << endl;
	break;
	}
	}
	*/
	return 0;
}
