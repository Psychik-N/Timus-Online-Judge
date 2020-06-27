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
const double eps = 1e-8;
const int INF = 1e9;
const int maxN = 2e6+1;

void Solve() {
	double P, Q;
	cin >> P >> Q;
	P /= 100.0;
	Q /= 100.0;
	for(int i = 1; ; i ++) {
		int Y = (int)ceil(P*i);
		if((Y-eps > P*i) && (Y+eps < Q*i)) {
			cout << i << endl;
			return;
		}
		if((Y+1-eps > P*i) && (Y+1+eps < Q*i)) {
			cout << i << endl;
			return;
		}
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
