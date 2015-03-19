/*
ID: sunapi31
PROG: milk2 
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

// problem: longest milking time, and longest time idle time
// we read the list of times, sort it by start time, 
// and then walk over the list once, merging overlapping times. 
// Then we walk the list watching for long milking periods and long non-milking periods.

bool paircomp(pair<int,int> a, pair<int,int> b) { return a.first < b.first; }

int main( int argc, char *argv[] ) {
    ifstream fin ("milk2.in");
    ofstream fout ("milk2.out");
    int N, start, end;
    fin >> N;
    vector<pair<int,int> > table(N);
    for (int i = 0; i < N; ++i) {
        fin >> start >> end;
        table.push_back(make_pair(start, end));
        // cerr << "pair " << table.back().first << " " << table.back().second << endl;
    }
    sort(table.begin(), table.end(), paircomp);

    // collapse the table into interlaping time intervals
    vector<pair<int, int> > greedy;
    greedy.push_back(table.front());
    for(int i = 1; i < table.size(); i++) {
        // let [a,b] be current greedy and [c,d] be current table
        int a = greedy.back().first, b = greedy.back().second;
        int c = table.at(i).first, d = table.at(i).second;
        // if c <= b and d > b then we can update [a,b] to [a,d]
        if(c <= b && d > b) {
            greedy.back().second = table.at(i).second;
        }
        // if c > b then make that a new entry
        else if(c > b) {
            greedy.push_back(table.at(i));
        }
    }
    greedy.erase(greedy.begin());

    // greedy table records times that the farm is being used; 
    // build table of durations active and inactive, used/unused
    int longestActive = greedy.front().second - greedy.front().first;
    int longestInactive = 0;
    int lastEndingTime = greedy.front().second;
    for(int i = 0; i < greedy.size(); i++) {
        // if the current duration is larger then set it to be the longest active
        int currentDuration = greedy.at(i).second - greedy.at(i).first;
        if(currentDuration > longestActive) {
            longestActive = currentDuration;
        }
        // this starting time - last ending time is the duration of inactivity
        int thisStartingTime = greedy.at(i).first;
        int currentInactivityDuration = thisStartingTime - lastEndingTime;
        if(currentInactivityDuration > longestInactive) {
            longestInactive = currentInactivityDuration;
        }
        // update last ending time
        lastEndingTime = greedy.at(i).second;
        // cerr << "greedy " << greedy.at(i).first << " " << greedy.at(i).second << endl;
    }

    // cerr << "longestActive " << longestActive << " longestInactive " << longestInactive << endl;

    fout << longestActive << " " << longestInactive << endl;
    return 0;
}

