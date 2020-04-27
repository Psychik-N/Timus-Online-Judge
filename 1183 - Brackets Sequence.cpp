/*
	Idea :
	1) Its a DP problem. here dp[i][j] = minimum number of steps to create seq for i to j a regular bracket
	-- sequence. dpAns is the corresponding string.
	2) In this test case can be empty too.
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

int N = 0;
int dp[100][100];
string dpAns[100][100];
v<char> seq;

int rec(int l, int r) {
	if(l > r) return 0;
	if(dp[l][r] != -1) return dp[l][r];
	int ans = 1000;
	if((seq[l] == ')') || (seq[l] == ']')) {
		ans = 1 + rec(l+1, r);
		dpAns[l][r] = ((seq[l] == ')') ? "()" : "[]");
		if(l+1 <= r) dpAns[l][r] = dpAns[l][r] + dpAns[l+1][r];
	}
	else {
		char toMatch = ((seq[l] == '(') ? ')' : ']');
		for(int i = l+1; i <= r; i ++) {
			if(toMatch == seq[i]) {
				ans = min(ans, rec(l+1, i-1) + rec(i+1, r));
			}
		}
		ans = min(ans, 1 + rec(l+1, r));
		for(int i = l+1; i <= r; i ++) {
			if((toMatch == seq[i]) && (ans == (rec(l+1, i-1) + rec(i+1, r)))) {
				dpAns[l][r] = ((seq[l] == '(') ? "(" : "[");
				if(l+1 <= i-1) dpAns[l][r] = dpAns[l][r] + dpAns[l+1][i-1];
				dpAns[l][r] += toMatch;
				if(i+1 <= r) dpAns[l][r] = dpAns[l][r] + dpAns[i+1][r];
				break;
			}
		}
		if(ans == (1 + rec(l+1, r))) {
			dpAns[l][r] = (seq[l] == '(' ? "()" : "[]");
			if(l+1 <= r) dpAns[l][r] = dpAns[l][r] + dpAns[l+1][r];
		}
	}
	dp[l][r] = ans;
	return ans;
}

int main() {
	memset(dp, -1, sizeof(dp));

	char ch;
	while(cin >> ch) {
		seq.push_back(ch);
		N ++;
	}
	if(seq.size()) {
		rec(0, N-1);
		cout << dpAns[0][N-1] << endl;
	}
	else cout << "" << endl;

	return 0;
}
