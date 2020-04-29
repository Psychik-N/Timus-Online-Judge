/*
	Idea :
	1) We will root the tree on two different vertices and these two vertices will be our end points of our diameter. 
	2) We will also use binary lifting to travel the distance in log(N).
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

const ll mod = 1e9;
const ld PI = acos(-1.0);
const ll LOGN = 17;
const ll maxN = 2e4+1;

vector<vector<int>> graph(maxN);
vector<vector<vector<int>>> binaryLift(2, vector<vector<int>>(LOGN, vector<int>(maxN, -1)));
vector<vector<int>> depth(2, vector<int>(maxN, 0));

template<typename T> vector<T> Diameter(T root = 1) {
	T diameter = -1, vertex = -1;
	T a, b;
	vector<T> parent(maxN, -1);
	function<void(T, T, T, bool)> dfs = [&](T node, T dist, T p, bool take = false) {
		if(take) parent[node] = p;
		if(diameter <= dist) {
			diameter = dist, vertex = node;
		}
		for(auto i : graph[node]) {
			if(i == p) continue;
			dfs(i, dist+1, node, take);
		}
	};
	dfs(root, 0, -1, 0);
	a = vertex;
	dfs(vertex, 0, -1, 1);
	b = vertex;
	return {a, b};
}

void dfs(int node, int parent, int id, int lvl) {
	depth[id][node] = lvl;
	binaryLift[id][0][node] = parent;
	for(int i = 1; i < LOGN; i ++) {
		if(binaryLift[id][i-1][node] == -1) break;
		binaryLift[id][i][node] = binaryLift[id][i-1][binaryLift[id][i-1][node]];
	}
	for(auto i : graph[node]) {
		if(i == parent) continue;
		dfs(i, node, id, lvl+1);
	}
}

int computeNode(int id, int node, int distance) {
	int x = node;
	for(int i = LOGN-1; i >= 0; i --) {
		if(x == -1) return x;
		if(distance & (1LL << i)) {
			x = binaryLift[id][i][x];
		}
	}
	return x;
}

void Solve() {
	int N, q;
	cin >> N >> q;
	for(int i = 1; i < N; i ++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	vector<int> endPoints = Diameter<int>(1);
	dfs(endPoints[0], -1, 0, 0);
	dfs(endPoints[1], -1, 1, 0);
	while(q --) {
		int ver, d;
		cin >> ver >> d;
		int node1 = computeNode(0, ver, d);
		int node2 = computeNode(1, ver, d);
		if(node1 != -1) {
			cout << node1 << endl;
			continue;
		}
		if(node2 != -1) {
			cout << node2 << endl;
			continue;
		}
		cout << 0 << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int tt = 1;

	while(tt --) {
		Solve();
	}

	return 0;
}
