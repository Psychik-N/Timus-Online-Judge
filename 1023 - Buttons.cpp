/*
	Idea : 
	1) We put L = K-1, I f first player take minimum one button then that will leave are second 
	-- player to take all the remaining coins all at once. So answer is always possible now to 
	-- reduce it. Now notice it is similar to a nim game so if we fix a L so are winning and 
	-- losing state will look like (W, W, W ... (L times), L) [then repeat]. So we just have to 
	-- compute smallest divisor X of K such that X-1 >= 2
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

	ll K;
	cin >> K;
	set<ll> divisor;
	for(ll i = 1; i*i <= K; i ++) {
		if(K % i) continue;
		divisor.insert(i);
		divisor.insert(K/i);
	}
	while((*divisor.begin()) <= 2) divisor.erase(divisor.begin());
	cout << (*divisor.begin())-1 << endl;

	return 0;
}
