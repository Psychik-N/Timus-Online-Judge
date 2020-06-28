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

long long N;
long long dp[501][501];

long long rec(int prevLen, int left) {
	if(left == 0) return 1;
	if(prevLen >= left) return 0;
	if(dp[prevLen][left] != -1) return dp[prevLen][left];
	long long ans = 0;
	for(int i = prevLen+1; i <= left; i ++) {
		ans += rec(i, left-i);
	}
	dp[prevLen][left] = ans;
	return ans;
}

void Solve() {
	cin >> N;
	for(int i = 0; i < 501; i ++) {
		for(int j = 0; j < 501; j ++) {
			dp[i][j] = -1;
		}
	}
	cout << rec(0, N)-1 << endl;
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
