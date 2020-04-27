/*
	Idea :
	1) Just Google the topic LCA and learn about binary Lifting. By this you will be able to this.
	2) Note it doesn't matter where you root the tree as there is always one path from node a to b.
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

struct LCA {
	using S = long long;
	using T = long long;
	S start, timer, K, N;
	vector<vector<pair<T, T>>> graph;
	vector<S> tIn, tOut, depth;
	vector<vector<S>> binaryLift;
	LCA(S s, S nodes) {
		N = nodes;
		K = ceil(log2(nodes*1.0));
		start = s;
		timer = 0;
		graph.resize(nodes);
		depth.resize(nodes);
		tIn.resize(nodes);
		tOut.resize(nodes);
		binaryLift.assign(K+1, vector<S>(nodes, -1));
	}
	void addEdge(T a, T b, T w) {
		graph[a].push_back({b, w});
		graph[b].push_back({a, w});
	}
	void computeLift(S node, S parent, S lvl) {
		depth[node] = lvl;
		tIn[node] = ++timer;
		binaryLift[0][node] = parent;
		for(S i = 1; i <= K; i ++) {
			if(binaryLift[i-1][node] == -1) break;
			binaryLift[i][node] = binaryLift[i-1][binaryLift[i-1][node]];
		}
		for(auto i : graph[node]) {
			if(i.first == parent) continue;
			computeLift(i.first, node, lvl+i.second);
		}
		tOut[node] = ++timer;
	}
	bool isAncestor(S a, S b) {
		if(a < start) return true;
		return ((tIn[a] <= tIn[b]) && (tOut[a] >= tOut[b]));
	}
	S getLCA(S a, S b) {
		if(isAncestor(a, b)) return a;
		if(isAncestor(b, a)) return b;
		for(S i = K; i >= 0; i --) {
			if(!isAncestor(binaryLift[i][a], b)) {
				a = binaryLift[i][a];
			}
		}
		return binaryLift[0][a];
	}
	S distance(S a, S b) {
		return (depth[a] + depth[b] - 2*depth[getLCA(a, b)]);
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ll n;
	cin >> n;
	LCA getDistance(0, n);
	for(int i = 0; i < n-1; i ++) {
		ll a, b, w;
		cin >> a >> b >> w;
		getDistance.addEdge(a, b, w);
	}
	getDistance.computeLift(0, -1, 0);
	ll m;
	cin >> m;
	while(m --) {
		ll a, b;
		cin >> a >> b;
		cout << getDistance.distance(a, b) << endl;
	}

	return 0;
}
