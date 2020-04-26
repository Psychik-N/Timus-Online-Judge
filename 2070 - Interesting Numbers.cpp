/*
	Idea :
	1) All Prime Numbers and Composite numbers will contribute to answer. Only numbers in the form of 
	-- P^k where P is a prime number and (k+1) is a prime number will not contribute to the answer. Note!
	-- number should also belong in the range. 
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

template<typename T> vector<bool> Sieve(T N) {
	vector<T> primes;
	vector<bool> isPrime(N+1, 1);
	for(T i = 2; i < N+1; i ++) {
		if(isPrime[i]) {
			primes.push_back(i);
			for(T j = i+i; j < N+1; j += i) {
				isPrime[j] = 0;
			}
		}
	}
	return isPrime;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ll L, R;
	cin >> L >> R;
	ll ans = R-L+1;
	vector<bool> isPrime = Sieve<ll>(sqrt(R)+5);
	for(ll i = 2; i*i <= R; i ++) {
		if(!isPrime[i]) continue;
		ll num = i*i;
		ll count = 3;
		while(num <= R) {
			if((num >= L) && (num <= R) && isPrime[count]) {
				ans --;
			}
			count ++;
			num = (num*i);
		}
	}
	cout << ans << endl;

	return 0;
}
