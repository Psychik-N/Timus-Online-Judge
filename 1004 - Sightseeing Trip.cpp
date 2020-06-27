#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define v vector
#define ALL(x) x.begin(),x.end()
#define rALL(x) x.rbegin(),x.rend()
#define endl '\n'
#define F first
#define S second
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

const long long mod = 1e9+7;
const long double PI = acos(-1.0);
const int INF = 1e9;
const int maxN = 2e6+1;

void Solve(int N) {
	int M;
	cin >> M;
	vector<vector<int>> adjmat(N+1, vector<int>(N+1, -1));
	vector<pair<int, int>> graph[N+1];
	for(int i = 0; i < M; i ++) {
		int a, b, l;
		cin >> a >> b >> l;
		if(adjmat[a][b] == -1) {
			adjmat[a][b] = l;
			adjmat[b][a] = l;
		}
		else {
			adjmat[a][b] = min(adjmat[a][b], l);
			adjmat[b][a] = min(adjmat[b][a], l);
		}
	}
	for(int i = 1; i < N; i ++) {
		for(int j = i+1; j <= N; j ++) {
			if(adjmat[i][j] == -1) continue;
			graph[i].push_back({j, adjmat[i][j]});
			graph[j].push_back({i, adjmat[i][j]});
		}
	}
	int best = INF;
	vector<int> ans;
	for(int i = 1; i <= N; i ++) {
		if(graph[i].size() <= 1) continue;
		vector<int> dist(N+1, INF);
		vector<int> parent(N+1, -1);
		vector<int> color(N+1, -1);
		set<pair<int, int>> q;
		for(auto to : graph[i]) {
			dist[to.first] = to.second;
			color[to.first] = to.first;
			q.insert({to.second, to.first});
		}
		while(q.size()) {
			pair<int, int> aux = *q.begin();
			int from = aux.second;
			int len = aux.first;
			q.erase(q.begin());
			if(len != dist[from]) continue;
			for(auto to : graph[from]) {
				if(to.first == i) continue;
				if(dist[to.first] > len + to.second) {
					dist[to.first] = len + to.second;
					parent[to.first] = from;
					color[to.first] = color[from];
					q.insert({dist[to.first], to.first});
				}
			}
		}
		int edge[2];
		edge[0] = edge[1] = -1;
		for(int a = 1; a < N; a ++) {
			for(int b = a+1; b <= N; b ++) {
				if(a == i) continue;
				if(b == i) continue;
				if((adjmat[a][b] != -1) && (color[a] != color[b])){
					int tour = adjmat[a][b] + dist[a] + dist[b];
					if(tour < best) {
						edge[0] = a;
						edge[1] = b;
						best = tour;
					}
				}
			}
		}
		for(auto to : graph[i]) {
			if(color[to.first] != to.first) {
				int tour = adjmat[i][to.first] + dist[to.first];
				if(tour < best) {
					edge[0] = to.first;
					edge[1] = -1;
					best = tour;
				}
			}
		}
		if(edge[0] != -1) {
			if(edge[1] != -1) {
				vector<int> a;
				int cur = edge[0];
				while(cur != -1) {
					a.push_back(cur);
					cur = parent[cur];
				}
				a.push_back(i);
				reverse(ALL(a));
				ans = a;
				cur = edge[1];
				while(cur != -1) {
					ans.push_back(cur);
					cur = parent[cur];
				}
			}
			else {
				int cur = edge[0];
				vector<int> a;
				while(cur != -1) {
					a.push_back(cur);
					cur = parent[cur];
				}
				a.push_back(i);
				ans = a;
			}
		}
	}
	if(best == INF) {
		cout << "No solution.\n";
	}
	else {
		for(auto i : ans) cout << i << " ";
		cout << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while(true) {
		int N;
		cin >> N;
		if(N == -1) break;
		Solve(N);
	}
	
	return 0;
}
