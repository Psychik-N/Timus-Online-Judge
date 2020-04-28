/*
	Idea :
	1) Number will be in the form of 2^a * 3^b * 5^c ... . a >= b >= c >= d and soon.
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

ll N, ans, numDivisor;
vector<ll> p;

template<typename T> vector<T> Sieve(T N) {
	vector<T> primes;
	vector<bool> isPrime(N+1, 0);
	for(T i = 2; i < N+1; i ++) {
		if(isPrime[i] == 0) {
			primes.push_back(i);
			for(T j = i+i; j < N+1; j += i) {
				isPrime[j] = 1;
			}
		}
	}
	return primes; 
}

void rec(ll idx, ll cur, ll curDiv, ll maxLimit) {
	if((curDiv > numDivisor) && (cur <= N)) {
		numDivisor = curDiv;
		ans = cur;
	}
	if((curDiv == numDivisor) && (cur < ans)) {
		ans = cur;
	}
	if(idx == 35) return;
	for(ll i = 1; (i <= maxLimit) && (cur <= (N/p[idx])); i ++) {
		cur *= p[idx];
		rec(idx+1, cur, curDiv*(i+1), i);
	}
}

void Solve() {
	cin >> N;
	ans = 1, numDivisor = 1;
	rec(0, 1, 1, 62);
	cout << ans << " " << numDivisor << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ll tt = 1;
	cin >> tt;

	p = Sieve<ll>(1000);

	while(tt --) {
		Solve();
	}

	return 0;
}
