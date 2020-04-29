/*
	Idea :
	1) iterate in increasing order of a[i] and use DP + BIT calculate number of ways.
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

struct BIT {
	using T = int;
	vector<T> arr;
	BIT(T s = 2e4) {
		arr.assign(s+1 , 0);
	}
	T sum(T pos) {
		T ans = 0;
		while(pos > 0) {
			ans = (ans + arr[pos]) % mod;
			pos = pos - (pos & (-pos));
		}
		return ans;
	}
	void update(T pos, T val) {
		while((pos > 0) && (pos < arr.size())) {
			arr[pos] = (arr[pos] + val) % mod;
			pos = pos + (pos & (-pos));
		}
	}
};

void Solve() {
	int N, k;
	cin >> N >> k;
	vector<BIT> dp(k+1);
	vector<int> a(N);
	for(int i = 0; i < N; i ++) cin >> a[i];
	for(int i = N-1; i >= 0; i --) {
		dp[1].update(a[i], 1);
		for(int j = 2; j <= k; j ++) {
			ll val = dp[j-1].sum(a[i]-1);
			dp[j].update(a[i], val);
		}
	}
	ll ans = dp[k].sum(N);
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
