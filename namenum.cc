/*
ID: sunapi31
PROG: namenum 
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> // abs
#include <utility> // pair, make_pair
#include <algorithm> // sort
#include <map> // multimap
using namespace std;

int charToNum(char c) {
    switch(c) {
        case 'A':
        case 'B':
        case 'C': return 2;
        case 'D':
        case 'E':
        case 'F': return 3;
        case 'G':
        case 'H':
        case 'I': return 4;
        case 'J':
        case 'K':
        case 'L': return 5;
        case 'M':
        case 'N':
        case 'O': return 6;
        case 'P':
        case 'R': 
        case 'S': return 7;
        case 'T':
        case 'U':
        case 'V': return 8;
        case 'W':
        case 'X':
        case 'Y': return 9;
    }
    return -1;
}
// Examples: AB => 22, JWP =>597
// works because longest number is 12 digit
long long stringToLong(string s) {
    long long num = 0;
    for(int i = 0; i < s.size(); i++) {
        num *= 10;
        char c = s.at(i);
        num += charToNum(c);
    }
    return num;
}

// problem:
// translate a 1 to 12 digit number punched into a phone to an acceptable name in 
// the dictionary or output "NONE" if no valid names.
// idea: preprocess the dictionary to map each word to its respective dial-code and
// look up the number given from our map.
int main( int argc, char *argv[] ) {
    // preprocess:
    ifstream names_in ("dict.txt");
    string name;
    typedef multimap<long long, string> Dictonary;
    Dictonary dict; // store
    // read dict deconstruct word into a number; put into map
    while(!names_in.fail()) {
        names_in >> name;
        long long dialCode = stringToLong(name);
        dict.insert(Dictonary::value_type(dialCode, name));
    }
    // show content
    // for(Dictonary::iterator it = dict.begin(); it != dict.end(); it++) {
    //     cerr << it->first << " => " << it->second << endl;
    // }
    ifstream fin ("namenum.in");
    ofstream fout ("namenum.out");
    long long N;
    fin >> N; 
    // lookup number given in our map; pair is given back, lower and higher iterators
    pair<Dictonary::iterator, Dictonary::iterator> rangePair = dict.equal_range(N);
    for(Dictonary::iterator it = rangePair.first; it != rangePair.second; it++) {
        // cerr << it->second << endl;
        fout << it->second << endl;
    }
    if(rangePair.first == rangePair.second) {
        cerr << "NONE" << endl;
        fout << "NONE" << endl;
    }

    // for each character, generate possible outcome strings

    return 0;
}

