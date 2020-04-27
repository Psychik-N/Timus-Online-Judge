/*
	Idea :
	1) Number will be in format of (x*(10^N) + y). So if we want it to be divisible by x then y % x = 0.
	2) Use Big Integer to solve this.
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

struct bigint {
	string a;
	int sign;
	bigint() {}
	bigint(string b) { 
		(*this) = b;
	}
	int size() {
		return a.size();
	}
	bigint inverseSign() {
		sign *= -1;
		return (*this);
	}
	bigint normalize(int newSign) {
		for(int i = a.size() - 1; (i > 0) && (a[i] == '0'); i --)
			a.erase(a.begin() + i);
		sign = ( a.size() == 1 && a[0] == '0' ) ? 1 : newSign;
		return (*this);
	}
	void operator = (string b) {
		a = (b[0] == '-') ? b.substr(1) : b;
		reverse(a.begin(), a.end());
		this->normalize(b[0] == '-' ? -1 : 1 );
	}
	bool operator < (const bigint &b) const {
		if(sign != b.sign) return sign < b.sign;
		if(a.size() != b.a.size())
			return (sign == 1) ? (a.size() < b.a.size()) : (a.size() > b.a.size());
		for(int i = a.size() - 1; i >= 0; i --) if(a[i] != b.a[i])
			return (sign == 1) ? (a[i] < b.a[i]) : (a[i] > b.a[i]);
		return false;
	}
	bool operator == (const bigint &b) const {
		return (a == b.a) && (sign == b.sign);
	}
	bigint operator + (bigint b) {
		if(sign != b.sign) return (*this) - b.inverseSign();
		bigint c;
		for(int i = 0, carry = 0; (i < a.size()) || (i < b.size()) || carry; i ++) {
			carry += ((i < a.size()) ? a[i]-48 : 0) + ((i < b.a.size()) ? b.a[i]-48 : 0);
			c.a += (carry % 10 + 48);
			carry /= 10;
		}
		return c.normalize(sign);
	}
	bigint operator - (bigint b) {
		if(sign != b.sign) return (*this) + b.inverseSign();
		int s = sign; sign = b.sign = 1;
		if( (*this) < b ) return ((b - (*this)).inverseSign()).normalize(-s);
		bigint c;
		for(int i = 0, borrow = 0; i < a.size(); i ++) {
			borrow = a[i] - borrow - (i < b.size() ? b.a[i] : 48);
			c.a += borrow >= 0 ? borrow + 48 : borrow + 58;
			borrow = borrow >= 0 ? 0 : 1;
		}
		return c.normalize(s);
	}
	bigint operator * (bigint b) {
		bigint c("0");
		for(int i = 0, k = a[i] - 48; i < a.size(); i ++, k = a[i] - 48) {
			while(k--) c = c + b;
			b.a.insert(b.a.begin(), '0');
		}
		return c.normalize(sign * b.sign);
	}

	bigint operator / (bigint b) {
		if((b.size() == 1) && (b.a[0] == '0')) b.a[0] /= (b.a[0] - 48);
		bigint c("0"), d;
		for(int j = 0; j < a.size(); j ++) d.a += "0";
		int dSign = sign * b.sign; b.sign = 1;
		for( int i = a.size() - 1; i >= 0; i --) {
			c.a.insert(c.a.begin(), '0');
			c = c + a.substr( i, 1 );
			while(!(c < b)) c = c - b, d.a[i]++;
		}
		return d.normalize(dSign);
	}
	bigint operator % (bigint b) {
		if((b.size() == 1) && (b.a[0] == '0')) b.a[0] /= (b.a[0] - 48);
		bigint c("0");
		b.sign = 1;
		for(int i = a.size() - 1; i >= 0; i --) {
			c.a.insert(c.a.begin(), '0');
			c = c + a.substr(i, 1);
			while(!(c < b)) c = c - b;
		}
		return c.normalize(sign);
	}
	void print() {
		if(sign == -1) cout << '-';
		for(int i = a.size() - 1; i >= 0; i --) cout << a[i];
	}
};

string getPow(ll n) {
	string res = "1";
	for(ll i = 0; i < n; i ++) {
		res += "0";
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ll N;
	cin >> N;
	string zero = "0", one = "1", two = "2", three = "3", four = "4", five = "5", eight = "8";
	bigint ans = zero;
	bigint num = getPow(N);
	bigint red = getPow(N-1);
	bigint One = one, Two = two, Three = three, Four = four, Five = five, Eight = eight;
	red = red - One;
	num = num - One;
	ans = ans + (num / One) + (num / Two) + (num / Five) - (Three * red);
	if(N > 1) ans = ans + (num / Four) - red;
	if(N > 2) ans = ans + (num / Eight) - red;
	ans.print();
	cout << endl;

	return 0;
}
