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

void Solve() {
	int N;
	cin >> N;
	vector<int> a(N);
	for(int i = 0; i < N; i ++) {
		cin >> a[i];
	}
	int limit = (1 << N);
	int ans = 1e9;
	for(int i = 0; i < limit; i ++) {
		int A = 0, B = 0;
		for(int j = 0; j < N; j ++) {
			if(i & (1 << j)) A += a[j];
			else B += a[j];
		}
		ans = min(ans, abs(A-B));
	}
	cout << ans << endl;
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
