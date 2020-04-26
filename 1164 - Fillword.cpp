/*
	Idea : 
	1) You can find all the words as problem statement says it always possible but you don't 
	-- have to find all the words. Note! the count of each letter is constant so all we need to
	-- do is subtract the total count of a letter and sigma(count of letter in all P words) and
	-- print it lexographically. Simple question just a bit tricky.
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

	int N, M, P;
	cin >> N >> M >> P;
	vector<int> Grid(26, 0);
	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < M; j ++) {
			char ch;
			cin >> ch;
			Grid[ch-'A'] ++;
		}
	}
	for(int i = 0; i < P; i ++) {
		string s;
		cin >> s;
		for(int j = 0; j < s.size(); j ++) {
			Grid[s[j]-'A'] --;
		}
	}
	for(int i = 0; i < 26; i ++) {
		while(Grid[i] --) {
			cout << char('A'+i);
		}
	}
	cout << endl;
	
	return 0;
}
