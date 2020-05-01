/*
	Idea :
	1) It is the pattern based question. Simple observation will be to see the pair of flag as links
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

void Solve() {
	int N, cur = 3, toadd = 3;
	cin >> N;
	vector<vector<int>> flag = {{1, 2}, {1, 3}, {2, 3}};
	while(cur+toadd <= N) {
		flag.push_back(vector<int>());
		for(int i = cur+1; i <= cur+toadd; i ++) {
			flag[i-cur-1].push_back(i);
			flag[toadd].push_back(i);
		}
		cur += toadd;
		toadd ++;
	}
	cout << flag.size() << endl;
	for(int i = 0; i < flag.size(); i ++) {
		cout << flag[i].size() << " ";
		for(auto j : flag[i]) cout << j << " ";
		cout << endl;
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
