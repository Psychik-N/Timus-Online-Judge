/*
	Idea :
	1) Question uses 3D Binary Index Tree and application of Inclusion and Exclusion Principle.
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

struct BIT3D {
	using T = long long;
	T XX, YY, ZZ;
	vector<vector<vector<T>>> grid;
	BIT3D(T x, T y, T z) {
		XX = x;
		YY = y;
		ZZ = z;
		grid.assign(x+1, vector<vector<T>>(y+1, vector<T>(z+1, 0)));
	}
	void update(T x, T y, T z, T val) {
		while(x <= XX) {
			T yy = y;
			while(yy <= YY) {
				T zz = z;
				while(zz <= ZZ) {
					grid[x][yy][zz] += val;
					zz = zz + (zz & (-zz));
				}
				yy = yy + (yy & (-yy));
			}
			x = x + (x & (-x));
		}
	}
	T sum(T x, T y, T z) {
		T ans = 0;
		while(x > 0) {
			T yy = y;
			while(yy > 0) {
				T zz = z;
				while(zz > 0) {
					ans += grid[x][yy][zz];
					zz = zz - (zz & (-zz));
				}
				yy = yy - (yy & (-yy));
			}
			x = x - (x & (-x));
		}
		return ans;
	}
};

void Solve() {
	int N;
	cin >> N;
	BIT3D bit(N, N, N);
	while(true) {
		int type;
		cin >> type;
		if(type == 3) break;
		if(type == 1) {
			ll x, y, z, val;
			cin >> x >> y >> z >> val;
			x ++, y ++, z ++;
			bit.update(x, y, z, val);
		}
		else {
			ll x[2], y[2], z[2];
			cin >> x[0] >> y[0] >> z[0] >> x[1] >> y[1] >> z[1];
			ll ans = 0;
			x[1] ++, y[1] ++, z[1] ++;
			for(ll i = 0; i < 2; i ++) {
				for(ll j = 0; j < 2; j ++) {
					for(ll k = 0; k < 2; k ++) {
						if((i+j+k) % 2) ans += bit.sum(x[i], y[j], z[k]);
						else ans -= bit.sum(x[i], y[j], z[k]);
					}
				}
			}
			cout << ans << endl;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ll tt = 1;
	while(tt --) {
		Solve();
	}

	return 0;
}
