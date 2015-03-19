/*
ID: sunapi31
PROG: palsquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> // abs
#include <utility> // pair, make_pair
#include <algorithm> // sort
using namespace std;

bool palindrome(string str) {
    string reversed(str);
    reverse(str.begin(), str.end());
    return reversed.compare(str) == 0;
}

char numToCharBase2_20(int num) {
    switch(num) {
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        case 16: return 'G';
        case 17: return 'H';
        case 18: return 'I';
        case 19: return 'J';
        case 20: return 'K';
        default: return (char)(num + '0');
    }
}

// takes a base 10 number and formats it to a number in the desired base
string rebase2_20(int num, int base) {
    int remdr;
    string str;
    while(num != 0) {
        remdr = num % base;
        char c = numToCharBase2_20(remdr);
        str += c;
        num /= base;
    }
    reverse(str.begin(), str.end());
    return str;
}


// problem:
int main( int argc, char *argv[] ) {
    ifstream fin ("palsquare.in");
    ofstream fout ("palsquare.out");
    const int N = 300;
    int B;
    fin >> B;
    for(int i = 1; i <= N; i++) {
        string numberInBase = rebase2_20(i, B);
        string squaredBase2_20 = rebase2_20(i*i, B);
        if(palindrome(squaredBase2_20)) {
            cerr << numberInBase << " " << squaredBase2_20 << endl;
            fout << numberInBase << " " << squaredBase2_20 << endl;
        }
    }

    return 0;
}

