#include <bits/stdc++.h>
using namespace std;

char code[20000];
int n;
int sum = 0;
int calcsum() {
	sum = 0; 
	for(int i = 0; i < n; i ++) { 
		if(code[i] == '1')
			sum += i+1;
	}
	return sum;
}

int main() {
	cin>>n;
	memset(code, 0, n*sizeof(char));
	int i = 0; 
	int sum = 0;
	while(cin >> code) {
		if(code[n-1] == 0)
			goto step2;
		if(code[n] != 0)
			goto step3;
		step1 :
		{
			sum = calcsum();
			if(sum%(n+1) == 0) {
				for(i = 0; i < n; i ++) {
					cout << code[i];
				}
				cout << endl;
				memset(code, 0, n*sizeof(int));
				continue;
			}
			for(i = 0; i < n; i ++) {
				if(code[i] == '1') {
					code[i] = '0';
					sum -= i+1;
					if(sum%(n+1) == 0) {
						cout << code;
						break;
					}
					code[i] = '1';
					sum += i+1;
				}
			}
			cout << endl;
			memset(code, 0, n*sizeof(int));
		}
		continue;
		step2 : 
		{
			for(i = n-1; i >= 0; i --) {
				code[i] = '0';
				sum = calcsum();
				if(sum%(n+1) == 0) {
					cout << code;
					break;
				}
				else {
					code[i] = '1';
					sum = calcsum();
					if(sum%(n+1) == 0) {
						cout << code;
						break;
					}
				}
				code[i] = code[i-1];
			}
			cout << endl;
			memset(code, 0, n*sizeof(int));
		}
		continue;
		step3 : 
		{
			for(i = 0; i <= n; i ++) {
				char temp = code[i];
				for(int j = i; j <= n-1; j ++)
					code[j] = code[j+1];
				sum = calcsum();
				if(sum%(n+1) == 0) {
					for(int k = 0; k <= n-1; k ++)
						cout << code[k];
					break;
				}
				else {
					for(int j = n-1; j >= i; j --)
						code[j+1] = code[j];
					code[i] = temp;
				}
			}
			cout << endl;
			memset(code, 0, n*sizeof(int));
		}
		continue;
	}
}
