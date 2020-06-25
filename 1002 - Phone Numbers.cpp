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
const long long INF = 1e18;
const int maxN = 2e6+1;

map<char, string> mp = {
	{'1' , "ij"},
	{'2' , "abc"},
	{'3' , "def"},
	{'4' , "gh"},
	{'5' , "kl"},
	{'6' , "mn"},
	{'7' , "prs"},
	{'8' , "tuv"},
	{'9' , "wxy"},
	{'0' , "oqz"},
};

void Solve(string s) {
	int N;
	cin >> N;
	map<string, string> present;
	for(int i = 0; i < N; i ++) {
		string in;
		cin >> in;
		string num = "";
		for(auto j : in) {
			for(auto k : mp) {
				bool pos = false;
				for(auto l : k.second) {
					if(l == j) pos = true;
				}
				if(pos) {
					num += k.first;
					break;
				}
			}
		}
		reverse(ALL(num));
		present[num] = in;
	}
	vector<int> parent(s.size(), -1);
	vector<int> dp(s.size(), int(1e9));
	for(int i = 0; i < s.size(); i ++) {
		string aux = "";
		int ans = 1e9;
		int prev = -1;
		for(int j = i; j >= 0; j --) {
			aux += s[j];
			if(present.count(aux)) {
				if(ans > 1 + ((j > 0) ? dp[j-1] : 0)) {
					ans = 1 + ((j > 0) ? dp[j-1] : 0);
					prev = ((j > 0) ? j-1 : -1);
				}
			}
		}
		dp[i] = min(dp[i], ans);
		parent[i] = prev;
	}
	if(dp[s.size()-1] == 1e9) {
		cout << "No solution." << endl;
	}
	else {
		vector<string> ans;
		int it = s.size()-1;
		while(it != -1) {
			string t = "";
			for(int i = it; i > parent[it]; i --) {
				t += s[i];
			}
			ans.push_back(present[t]);
			it = parent[it];
		}
		reverse(ALL(ans));
		for(auto i : ans) cout << i << " ";
		cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while(true) {
		string s;
		cin >> s;
		if(s[0] == '-') break;
		Solve(s);
	}
	
	return 0;
}
