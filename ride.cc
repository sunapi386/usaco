/*
ID: sunapi31
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string a, b;
    fin >> a >> b;
    int sum1 = 1, sum2 = 1;
    for(int i=0; i<a.length(); i++) { 
	sum1 *= a[i] - 'A' + 1;
	sum1 %= 47;
	cout << (char) a[i] << ' ' << sum1 << ' ';
    }
    cout << endl;
    for(int i=0; i<b.length(); i++) {
	sum2 *= b[i] - 'A' + 1;
	sum2 %= 47;
	cout << (char) b[i] << ' ' << sum2 << ' ';
}
    fout << ((sum1 == sum2) ? "GO" : "STAY" ) << endl;
    return 0;
}

