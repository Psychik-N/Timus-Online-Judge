/*
	Idea :
	1) Use DSU in reverse order of query.
*/
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define v vector
#define ALL(x) x.begin(),x.end()
#define rALL(x) x.rbegin(),x.rend()
#define endl '\n'
#define DEBUG

template<typename T> void DBG(const char* name, T&& H) {
	cerr << name << " = " << H << ')' << endl;
}

template<typename T, typename... Args> void DBG(const char* names, T&& H, Args&&... args) {
	const char* NEXT = strchr(names+1, ',');
	cerr.write(names, NEXT-names) << " = " << H << " |";
	DBG(NEXT+1, args...);
}

#ifdef DEBUG
	#define dbg(...) cerr << __FUNCTION__ << ' ' <<__LINE__ << " : (", DBG(#__VA_ARGS__, __VA_ARGS__)
#else
	#define dbg(...)
#endif

using ll = long long;
using ld = long double;

const ll mod = 1e9 + 7;
const ld PI = acos(-1.0);

struct DSU {
	using T = int;
	vector<T> parent;
	vector<T> size;
	T numComponents = 0;
	DSU(T n = 0) {
		if(n >= 0)
			init(n);
	}
	void init(T n = 0) {
		parent.resize(n);
		size.assign(n, 1);
		numComponents = n;
		for (T i = 0; i < n; i++)
			parent[i] = i;
	}
	T getParent(T x) {
		return (x == parent[x]) ? x : parent[x] = getParent(parent[x]);
	}
	bool merge(T x, T y) {
		x = getParent(x);
		y = getParent(y);
		if (x == y) {
			return false;
		} 
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
		numComponents--;
		return true;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, M, Q;
	cin >> N >> M;
	DSU uf(N+1);
	vector<pair<int, int>> connect(M);
	for(int i = 0; i < M; i ++) {
		int a, b;
		cin >> a >> b;
		connect[i] = {a, b};
	}
	cin >> Q;
	set<int> query;
	vector<int> qOrder(Q);
	for(int i = 0; i < Q; i ++) {
		int a;
		cin >> a;
		query.insert(a-1);
		qOrder[i] = a-1;
	}
	vector<int> ans(Q);
	for(int i = 0; i < M; i ++) {
		if(query.count(i)) continue;
		uf.merge(connect[i].first, connect[i].second); 
	}
	for(int i = Q-1; i >= 0; i --) {
		ans[i] = uf.numComponents-1;
		uf.merge(connect[qOrder[i]].first, connect[qOrder[i]].second);
	}
	for(auto i : ans) cout << i << " ";
	cout << endl;

	return 0;
}
