/*
	Idea :
	1) It requires Heavy Light Decomposition.
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

using ll = int;
using ld = long double;

const ll mod = 1e9;
const ld PI = acos(-1.0);
const long long maxN = 1e5+1;

template<typename T> struct node {
	T mx;
	node(T y = 0) : mx(y) {};
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
		pt.mx = max(lc.mx, rc.mx);
	}
	void push(S pt, S lc, S rc, S l, S r) {
		if(!isLazy[pt]) return;
		if(l != r) {
			isLazy[lc] = 1;
			isLazy[rc] = 1;
			lazy[lc].val += lazy[pt].val;
			lazy[rc].val += lazy[pt].val;
		}
		data[pt].mx += lazy[pt].val;
		lazy[pt].val = 0;
		isLazy[pt] = 0;
	}
	void build(S x, S l, S r, vector<T>& a) {
		if(l == r) {
			data[x].mx = a[l];
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

SGT hldSGT(maxN);

struct LCA {
	using S = int;
	using T = int;
	S start, timer, K, N;
	vector<vector<T>> graph;
	vector<S> tIn, tOut, depth, subtree;
	vector<vector<S>> binaryLift;
	LCA(S s, S nodes) {
		N = nodes;
		K = ceil(log2(nodes*1.0));
		start = s;
		timer = 0;
		graph.resize(nodes);
		depth.resize(nodes);
		subtree.resize(nodes);
		tIn.resize(nodes);
		tOut.resize(nodes);
		binaryLift.assign(K+1, vector<S>(nodes, -1));
	}
	void addEdge(T a, T b) {
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	void computeLift(S node, S parent, S lvl) {
		depth[node] = lvl;
		tIn[node] = ++timer;
		subtree[node] = 1;
		binaryLift[0][node] = parent;
		for(S i = 1; i <= K; i ++) {
			if(binaryLift[i-1][node] == -1) break;
			binaryLift[i][node] = binaryLift[i-1][binaryLift[i-1][node]];
		}
		for(auto i : graph[node]) {
			if(i == parent) continue;
			computeLift(i, node, lvl+1);
			subtree[node] += subtree[i];
		}
		tOut[node] = ++timer;
	}
	bool isAncestor(S a, S b) {
		if(a < start) return true;
		return ((tIn[a] <= tIn[b]) && (tOut[a] >= tOut[b]));
	}
	S getLCA(S a, S b) {
		if(isAncestor(a, b)) return a;
		if(isAncestor(b, a)) return b;
		for(S i = K; i >= 0; i --) {
			if(!isAncestor(binaryLift[i][a], b)) {
				a = binaryLift[i][a];
			}
		}
		return binaryLift[0][a];
	}
	S distance(S a, S b) {
		return (depth[a] + depth[b] - 2*depth[getLCA(a, b)]);
	}
};

LCA hldLCA(1, maxN);

struct HLD {
	using T = int;
	T curID, curChain;
	vector<T> chainHead, chainID, posInSGT;
	HLD(T nodes) {
		curChain = 0;
		curID = 0;
		chainHead.assign(nodes, -1);
		chainID.assign(nodes, -1);
		posInSGT.assign(nodes, 0);
	}
	void computeHLD(T node, T parent) {
		if(chainHead[curChain] == -1) chainHead[curChain] = node;
		chainID[node] = curChain;
		posInSGT[node] = curID ++;
		T bigChild = -1, maxSize = -1;
		for(auto i : hldLCA.graph[node]) {
			if(i == parent) continue;
			if(maxSize < hldLCA.subtree[i]) {
				maxSize = hldLCA.subtree[i];
				bigChild = i;
			}
		}
		if(bigChild != -1) computeHLD(bigChild, node);
		for(auto i : hldLCA.graph[node]) {
			if((i == parent) || (i == bigChild)) continue;
			curChain ++;
			computeHLD(i, node);
		}
	}
	T queryUp(T a, T b) {
		T chainA = chainID[a], chainB = chainID[b], ans = 0;
		while(true) {
			if(chainA == chainB) {
				T res = hldSGT.query(1, 0, maxN-1, posInSGT[b], posInSGT[a]).mx;
				ans = max(ans, res);
				break;
			}
			T curHead = chainHead[chainA];
			T res = hldSGT.query(1, 0, maxN-1, posInSGT[curHead], posInSGT[a]).mx;
			ans = max(ans, res);
			a = hldLCA.binaryLift[0][curHead];
			chainA = chainID[a];
		}
		return ans;
	}
	T query(T a, T b) {
		T lca = hldLCA.getLCA(a, b);
		return max(queryUp(a, lca), queryUp(b, lca));
	}
	void updateUp(T a, T b, T val) {
		T chainA = chainID[a], chainB = chainID[b];
		while(true) {
			if(chainA == chainB) {
				hldSGT.update(1, 0, maxN-1, posInSGT[b], posInSGT[a], val);
				break;
			}
			T curHead = chainHead[chainA];
			hldSGT.update(1, 0, maxN-1, posInSGT[curHead], posInSGT[a], val);
			a = hldLCA.binaryLift[0][curHead];
			chainA = chainID[a];
		}
	}
	T update(T a, T b, T val) {
		T lca = hldLCA.getLCA(a, b);
		updateUp(a, lca, val);
		updateUp(b, lca, val);
		updateUp(lca, lca, -val);
	}
};


void Solve() {
	int N, Q;
	cin >> N;
	for(int i = 1; i < N; i ++) {
		int a, b;
		cin >> a >> b;
		hldLCA.addEdge(a, b);
	}
	hldLCA.computeLift(1, -1, 0);
	HLD hld(N+1);
	hld.computeHLD(1, -1);
	cin >> Q;
	while(Q --) {
		char type;
		int U, V;
		cin >> type >> U >> V;
		if(type == 'I') {
			hld.update(U, U, V);
		}
		else {
			cout << hld.query(U, V) << endl;
		}
	}
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
