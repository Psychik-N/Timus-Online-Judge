#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

void type1(int n) {
	if(n == 1) {
			int ta, tb;
			cin >> ta >> tb;
			cout << ta << " " << tb << "\n.";
			return;
	}
	int i, m[11][11] = {0}, x, y, a, b, j, s = 0, te = 0;
	for(i = 1; i <= n; i ++) {
		cin >> a >> b;
		m[a][b] = 1;
	}
	for(i = 1; i <= 10; i ++) {
		for(j = 1; j <= 10; j ++) {
			if(m[i][j] == 1) {
				x = i;
				y = j;
				te = 1;
				break;
			}
		}
		if(te == 1) break;
	}
	cout << x << " " << y << "\n";
	int list[101][2][2] = {0}, qlen[2] = {1}, on = 0, f[11][11] = {0}, dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
	list[1][0][0] = x;
	list[1][1][0] = y;
	char d[4] = {'R', 'T', 'L', 'B'};
	while((qlen[on]) != 0) {
		qlen[!on] = 0;
		for(i = 1; i <= qlen[on]; i ++) {
			x = list[i][0][on];
			y = list[i][1][on];
			for(j = 0; j < 4; j ++) {
				if(x+dx[j] >= 1 && x+dx[j] <= 10 && y+dy[j] >= 1 && y+dy[j] <= 10) {
					if(f[x+dx[j]][y+dy[j]] == 0 && m[x+dx[j]][y+dy[j]] == 1) {
						qlen[!on] ++;
						list[qlen[!on]][0][!on] = x+dx[j];
						list[qlen[!on]][1][!on] = y+dy[j];
						cout << d[j];
						f[x+dx[j]][y+dy[j]] = 1;
					}
				}
			}
			f[x][y] = 1;
			s ++;
			if(s != n) {
				cout << ",\n";
			}
			else {
				cout << ".";
				return;
			}
		}
		on = !on;
	}
}

void type2(int a, int b) {
	int x = a, y = b;
	int i, m[11][11] = {0}, j, s = 0;
	int list[101][2][2] = {0}, qlen[2] = {1}, on = 0, f[11][11] = {0}, dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
	list[1][0][0] = x;
	list[1][1][0] = y;
	char c;
	while((qlen[on]) != 0) {
		qlen[!on] = 0;
		f[x][y] = 1;
		for(i = 1; i <= qlen[on]; i ++) {
			x = list[i][0][on];
			y = list[i][1][on];
			do {
				cin >> c;
				if(c == ',' || c == '.') break;
				if(c == 'R') j = 0; 
				if(c == 'T') j = 1;
				if(c == 'L') j = 2;
				if(c == 'B') j = 3;
				qlen[!on] ++;
				list[qlen[!on]][0][!on] = x+dx[j];
				list[qlen[!on]][1][!on] = y+dy[j];
				f[x+dx[j]][y+dy[j]] = 1;
				s ++;
			} while(1);
		}
		on = !on;
	}
	cout << s+1 << "\n";
	for(i = 1; i <= 10; i ++) {
		for(j = 1; j <= 10; j ++) {
			if(f[i][j] == 1) {
				cout << i << " " << j << "\n";
			}
		}
	}
};

int main() {
	char c[1000] = {0};
	gets(c);
	int i, m = 1, t[2] = {0}, s = 0, n = 0;
	for(i = 1; i < 1000; i ++) {
		if(c[i] == 32)
			m = 2;
	};
	i = 0;
	while(i < 1000) {
		if(c[i] != 32 && c[i] != 0) {
			s = s*10 + int(c[i])-48;
		}
		else {
			t[n] = s;
			s = 0;
			n ++;
			if(n == 2) break;
		}
		i ++;
	}
	if(m == 1) {
		type1(t[0]);
	}
	else {
		type2(t[0], t[1]);
	}
	system("pause");
}
