/*
	Idea :
	1) Let range L to R has some parity then it implies. If parity is even then sumOfOne(R+1) % 2 == sumOfOne(L) % 2, and in case of odd it is not equal.
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

struct DSU {
	using T = int;
	vector<T> parent;
	vector<T> size;
	T numComponents = 0;
	DSU(T n = 0) {
		if(n >= 0)
			init(n);
	}
	void init(T n = 0) {
		parent.resize(n);
		size.assign(n, 1);
		numComponents = n;
		for (T i = 0; i < n; i++)
			parent[i] = i;
	}
	T getParent(T x) {
		return (x == parent[x]) ? x : parent[x] = getParent(parent[x]);
	}
	bool merge(T x, T y) {
		x = getParent(x);
		y = getParent(y);
		if (x == y) {
			return false;
		} 
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
		numComponents--;
		return true;
	}
};

void Solve(int Range) {
	DSU uf(30001);
	map<int, int> done;
	int ans = 0, ID = 0, q;
	cin >> q;
	bool pos = true;
	while(q --) {
		int L, R;
		string parity;
		cin >> L >> R >> parity;
		bool even = (parity == "even");
		int LID = 0, RID = 0, LLID = 0, RRID = 0;
		if(!((L >= 1) && (L <= Range) && (R >= 1) && (R <= Range) && (L <= R))) pos = false;
		R ++;
		if(!pos) continue;
		if(done.count(L)) {
			LID = done[L];
			LLID = done[-L];
		}
		else {
			LID = ID;
			done[L] = ID;
			ID ++;
			LLID = ID;
			done[-L] = ID;
			ID ++;
		}
		if(done.count(R)) {
			RID = done[R];
			RRID = done[-R];
		}
		else {
			RID = ID;
			done[R] = ID;
			ID ++;
			RRID = ID;
			done[-R] = ID;
			ID ++;
		}
		if(even) {
			if(uf.getParent(LID) == uf.getParent(RRID)) pos = false;
			if(uf.getParent(LLID) == uf.getParent(RID)) pos = false;
			uf.merge(LID, RID);
			uf.merge(LLID, RRID);
		}
		else {
			if(uf.getParent(LID) == uf.getParent(RID)) pos = false;
			if(uf.getParent(LLID) == uf.getParent(RRID)) pos = false;
			uf.merge(LID, RRID);
			uf.merge(LLID, RID);
		}
		if(pos) ans ++;
	}
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while(true) {
		int N;
		cin >> N;
		if(N == -1) break;
		Solve(N);
	}
	
	return 0;
}
