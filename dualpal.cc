/*
ID: sunapi31
PROG: dualpal
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
// valid 2 <= base <= 20
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


// problem: find and print (in base 10) the first N numbers strictly greater than S
// that are palidromic when written in two or more number bases
int main( int argc, char *argv[] ) {
    ifstream fin ("dualpal.in");
    ofstream fout ("dualpal.out");
    int N, S;
    fin >> N >> S;
    for(int i = S+1;; i++) { // strictly greater than S
        int atLeastTwoBases = 0; // counter to break out of checking loop if at least two
        for(int base = 2; base <= 10; base++) {
            if(palindrome(rebase2_20(i, base))) {
                atLeastTwoBases++;
            }
            if(atLeastTwoBases == 2) {
                N--;
                cerr << i << endl;
                fout << i << endl;
                break;
            }

        }
        if(N == 0) { // we have the first N numbers
            break;
        }
    }

    return 0;
}

