/*
ID: sunapi31
PROG: transform 
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

// problem: read in a square, figure out if it is: 
// (1) rotated 90 degrees
// (2) rotated 180 degrees
// (3) rotated 270 degrees
// (4) reflected horizontally (vertical axis)
// (5) combination of reflection + any rotation
// (6) no change
// (7) invalid rotation
//
// example: 
// @-@
// ---
// @@-
// transforms to:
// @-@
// @--
// --@
// and it is (3)
bool isSame(vector<string> vs1, vector<string> vs2) {
    if(vs1.size() == vs2.size()) {
        for(int i = 0; i < vs1.size(); i++) {
            if(vs1.at(i).compare(vs2.at(i)) != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

vector<string> rotate90(vector<string> v) {
    const int N = v.size();
    vector<string> rotated(N);
    for(int i = N-1; i >= 0; i--) { // starting from the very bottom of original
        const string originalString = v.at(i);
        for(int j = 0; j < N; j++) { // each makes it vertical
            rotated.at(j) += (originalString.at(j));
        }
    }
    return rotated;
}

vector<string> reflect(vector<string> v) {
    vector<string> reflected;
    for(int i = 0; i < v.size(); i++) {
        string tmp = v.at(i);
        reverse(tmp.begin(), tmp.end());
        reflected.push_back(tmp);
    }
    return reflected;
}

void print(vector<string> v, string label) {
    cerr << label << endl;
    for(int i = 0; i < v.size(); i++) {
        cerr << v.at(i) << endl;
    }
}

// the idea is to read in the square as a vector of strings
// then figure out which it is
int main( int argc, char *argv[] ) {
    ifstream fin ("transform.in");
    ofstream fout ("transform.out");
    int N;
    string line; 
    fin >> N; 
    vector<string> original, transform;

    // read in the original square
    for(int i = 0; i < N; i++) {
        fin >> line;
        original.push_back(line);
    }
    // read in the transform square
    for(int i = 0; i < N; i++) {
        fin >> line;
        transform.push_back(line);
    }

    vector<string> rot90 = rotate90(original);
    vector<string> rot180 = rotate90(rot90);
    vector<string> rot270 = rotate90(rot180);
    vector<string> rftd = reflect(original);
    vector<string> rftd90 = rotate90(rftd);
    vector<string> rftd180 = rotate90(rftd90);
    vector<string> rftd270 = rotate90(rftd180);

    // figure out which kind of transformation it is
    int retcode;
    if(isSame(transform, rot90)) { retcode = 1; }
    else if(isSame(transform, rot180)) { retcode = 2; }
    else if(isSame(transform, rot270)) { retcode = 3; }
    else if(isSame(transform, rftd)) { retcode = 4; }
    else if(isSame(transform, rftd90)) { retcode = 5; }
    else if(isSame(transform, rftd180)) { retcode = 5; }
    else if(isSame(transform, rftd270)) { retcode = 5; }
    else if(isSame(transform, original)) { retcode = 6; }
    else { retcode = 7; }
    
    // cerr << "retcode " << retcode << endl;
    fout << retcode << endl;
    return 0;
}

