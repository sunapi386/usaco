/*
ID: sunapi31
PROG: beads 
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> // abs
using namespace std;
const bool DEBUG = false;

// problem:
// collect beads of same color (red, blue, white), with white being paintable
// find max number of beads that can be collected from cutting, on both sides
// e.g. bwrwrrbwwwbbr is paintable to brrrrrbbbbbbr, thus 11 total (5xr, 6xb)

void printTable(vector<int> table) {
    for(int i=0; i<table.size();++i) { if(DEBUG) cerr << table.at(i) << " "; }
    if(DEBUG) cerr << endl;
}
bool colorable(char &startingColor, const char currentColor) {
    if(DEBUG) {
        cerr << "[" << startingColor << "," << currentColor << "]";
    }
    if(currentColor == 'w') { return true; } // white beads are always colorable
    if(currentColor == startingColor) { return true; } // same color are always colorable
    if(startingColor == 'w' && currentColor != 'w') { 
        startingColor = currentColor; 
        return true;
    }

    return false;
}

int main( int argc, char *argv[] ) {
    ifstream fin ("beads.in");
    ofstream fout ("beads.out");
    int n;
    string beads;
    fin >> n >> beads;
    vector<int> table(beads.size(), 0);

    // conceptually simple: table records maximum number of beads that can be collected
    // from cutting at that bead location then traverse the table to find a maximum
    // note we can just keep a "max" int, but keeping a table makes verification easier
    for (int i_bead = 0; i_bead < beads.size(); ++i_bead) { // iterate forwards
        const char startingColor = beads[i_bead];
        if(DEBUG) cerr << "bead " << i_bead << " color " << startingColor;
        // for each bead, try to match backwards and fowards as far as possible

        // itrate forwards
        if(DEBUG) cerr << " fwd: ";
        int extlen_fwd = 1; // assume current bead is used to match forwards
        int i_fwd = i_bead; // for indexing into the beads array; always 0 <= i_rev < beads.size()
        char fwdColor = startingColor;
        if(DEBUG) cerr << fwdColor;
        for(int dontUse = 0; dontUse < beads.size() - 1; ++dontUse) {
            i_fwd = (i_fwd + 1) % beads.size(); 
            // check wether we got different color and stop matching
            const char currentColor = beads.at(i_fwd);
            if(!colorable(fwdColor, currentColor)) { break; }
            extlen_fwd++;
            if(DEBUG) cerr << currentColor;
        }

        // iterate backwards (reverse) 
        int i_rev = i_bead; // for indexing into the beads array; always 0 <= i_rev < beads.size()
        int extlen_rev = 1;
        char revColor = ' ';
        if(DEBUG) cerr << " (" << extlen_fwd << ") "; 
        for(int dontUse = 0; dontUse < beads.size() - 1; ++dontUse) {
            i_rev--;
            if(i_rev < 0) {i_rev += beads.size();}
            if(revColor == ' ') { 
                revColor = beads[i_rev]; 
                if(DEBUG) cerr<< "rev color: " << revColor;
                continue; 
            }
            // check wether we got different color and stop matching
            const char currentColor = beads.at(i_rev);
            if(!colorable(revColor, currentColor)) { break; }
            if(i_rev == i_fwd - 1) {break;} // we have looped around, stop checking.
            extlen_rev++;
            if(DEBUG) cerr << currentColor;
        }
        if(DEBUG) cerr << " (" << extlen_rev << ") ";
        // record length forwards and reverse the current bead matches with
        int both = extlen_rev + extlen_fwd;
        table.at(i_bead) = both; // + 1 for the current bead usage
        if(DEBUG) cerr << "     " << both << endl;
    }

    // traverse the table to find a maximum
    int max = -1;
    for(int i = 0; i < table.size(); i++) { 
        max = table.at(i) > max ? table.at(i) : max;
    }
    int ans = max > beads.size() ? beads.size() : max;
    if(DEBUG) cerr << ans << endl;
    fout << ans << endl;

    return 0;
}

