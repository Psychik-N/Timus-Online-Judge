/*
	Idea :
	1) Use the segment tree of gcd. In case of minus query just simply set that number to zero.
	-- if the resultant gcd = 0(all element deleted), set it to 1.
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

template<typename T> struct node {
	T g;
	node(T x = 0) : g(x) {};
};
template<typename T> struct lazyNode {
	T val;
	lazyNode(T x = 0) : val(x) {};
};
struct SGT {
	using S = int;
	using T = int;
	S size;
	vector<node<T>> data;
	vector<lazyNode<T>> lazy;
	vector<bool> isLazy;
	SGT(S sz = 1e6+1) {
		size = sz;
		data.resize(4 * sz);
		lazy.resize(4 * sz);
		isLazy.assign(4 * sz, false);
	}  
	void merge(node<T>& pt, node<T>& lc, node<T>& rc) {
		pt.g = __gcd(lc.g, rc.g);
	}
	void push(S pt, S lc, S rc, S l, S r) {
		data[pt].g = lazy[pt].val;
		lazy[pt].val = 0;
		isLazy[pt] = 0;
	}
	void build(S x, S l, S r, vector<T>& a) {
		if(l == r) {
			data[x].g = a[l];
		}
		else {
			S mid = ((l + r) >> 1);
			build(2*x, l, mid, a);
			build(2*x+1, mid+1, r, a);
			merge(data[x], data[2*x], data[2*x+1]);
		}
	}
	node<T> query(S x, S l, S r, S qL, S qR) {
		if(isLazy[x]) {
			push(x, 2*x, 2*x+1, l, r);
		}
		if(qL > qR) {
			return node<T>(0);
		}
		if((l == qL) && (r == qR)) {
			return data[x];
		}
		S mid = ((l + r) >> 1);
		node<T> res;
		node<T> lc = query(2*x, l, mid, qL, min(mid, qR));
		node<T> rc = query(2*x+1, mid+1, r, max(mid+1, qL), qR);
		merge(res, lc, rc);
		return res;
	}
	void update(S x, S l, S r, S qL, S qR, T val) {
		if(isLazy[x]) {
			push(x, 2*x, 2*x+1, l, r);
		}
		if(qL > qR) {
			return;
		}
		if((l == qL) && (r == qR)) {
			isLazy[x] = 1;
			lazy[x].val = val;
			push(x, 2*x, 2*x+1, l, r);
			return;
		}
		S mid = ((l + r) >> 1);
		update(2*x, l, mid, qL, min(mid, qR), val);
		update(2*x+1, mid+1, r, max(mid+1, qL), qR, val);
		merge(data[x], data[2*x], data[2*x+1]);
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n, tt, idx = 0;
	map<int, vector<int>> indices;
	cin >> tt;
	n = tt;
	SGT st(n);
	while(tt --) {
		char ch;
		int num;
		cin >> ch >> num;
		if(ch == '+') {
			st.update(1, 0, n-1, idx, idx, num);
			indices[num].push_back(idx);
		}
		else {
			int id = indices[num].back();
			indices[num].pop_back();
			st.update(1, 0, n-1, id, id, 0);
		}
		idx ++;
		int res = st.data[1].g;
		if(res == 0) res = 1;
		cout << res << endl; 
	}

	return 0;
}
