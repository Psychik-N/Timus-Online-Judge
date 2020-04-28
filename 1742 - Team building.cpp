/*
	Idea :
	1) This question is about Strongly Connected Component. maximum teams = number of components in SCC
	-- minimum teams = number of leafs in SCC.
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

struct SCC {
	using S = int;
	using T = int;
	S start, maxN, numComponents;
	vector<vector<T>> graph, graphT;
	vector<bool> isVisited;
	vector<S> order;
	vector<S> color;
	vector<set<T>> condenseGraph;
	SCC(S s, S n) {
		init(s, n);
	}
	void init(S s, S n) {
		start = s;
		maxN = n;
		numComponents = 0;
		graph.assign(maxN, vector<T>());
		graphT.assign(maxN, vector<T>());
		isVisited.assign(maxN, false);
		color.assign(maxN, -1);
		order.clear();
		condenseGraph.assign(maxN, set<T>{});
	}
	void addEdge(S a, S b) {
		graph[a].push_back(b);
		graphT[b].push_back(a);
	}
	void topoSort(S node) {
		isVisited[node] = true;
		for(auto i : graph[node]) {
			if(isVisited[i]) continue;
			topoSort(i);
		}
		order.push_back(node);
	}
	void explore(S node, S colorID) {
		color[node] = colorID;
		isVisited[node] = true;
		for(auto i : graphT[node]) {
			if(isVisited[i]) continue;
			explore(i, colorID);
		}
	}
	void condense() {
		for(S i = start; i < maxN; i ++) {
			if(!isVisited[i]) topoSort(i);
		}
		reverse(order.begin(), order.end());
		isVisited.assign(maxN, false);
		for(auto i : order) {
			if(!isVisited[i]) {
				numComponents ++;
				explore(i, numComponents);
			}
		}
		for(S i = start; i < maxN; i ++) {
			for(auto j : graph[i]) {
				if(color[i] == color[j]) continue;
				 condenseGraph[color[i]].insert(color[j]);
			}
		}
	}
};

void Solve() {
	int n;
	cin >> n;
	SCC teams(1, n+1);
	for(int i = 1; i <= n; i ++) {
		int great;
		cin >> great;
		if(i == great) continue;
		teams.addEdge(great, i);
	}
	teams.condense();
	int maxTeams = teams.numComponents;
	int minTeams = 0;
	for(int i = 1; i <= teams.numComponents; i ++) {
		if(teams.condenseGraph[i].size() == 0) {
			minTeams ++;
		}
	}
	cout << minTeams << " " << maxTeams << endl;
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
