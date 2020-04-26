/*
	Idea :
	1) DP problem.
	2) If the back attack of coins of resistence level k is more than P then we can't distroy any coin with power level more
	-- than or equal to k
	3) dp[i] = minimum number of spells required to be destroy till ith index. For the ith index we have to get the spell
	-- of power level = resistence of coins in ith index.
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

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ll N, P;
	cin >> N >> P;
	map<ll, ll> coins;
	for(int i = 0; i < N; i ++) {
		ll inp;
		cin >> inp;
		coins[inp] += inp;
	}
	vector<int> a = {0}, b = {0};
	int ans = 0;
	for(auto i : coins) {
		if(i.second > P) break;
		ans += i.second/i.first;
		b.push_back(i.second/i.first);
		a.push_back(i.first);
	}
	vector<int> dp(a.size(), 1e9);
	dp[0] = 0;
	for(int i = 1; i < a.size(); i ++) {
		ll val = 0;
		for(int j = i; j > 0; j --) {
			val += a[i]*b[j];
			if(val > P) break;
			dp[i] = min(dp[i], 1+dp[j-1]);
		}
	}
	cout << ans << " " << dp[a.size()-1] << endl;
	
	return 0;
}
