/*
ID: sunapi31
PROG: gift1 
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;
typedef pair<string, int> account;

int main() {
    ifstream fin ("gift1.in");
    ofstream fout ("gift1.out");
    int np;
    map<string,int> bank;
    vector<string> order;
    fin >> np;
    for(int i=0; i<np; i++) {
        string name;
        fin >> name;
        bank.insert( account(name,0) );
        order.push_back( name );
    }

    // simulate
    while(!fin.fail()) {
        string gifter;
        int money, people;
        fin >> gifter >> money >> people;
        bank.find(gifter)->second -= money;
        for(int p=0; p<people; p++) {
            string giftee;
            fin >> giftee;
            bank.find(giftee)->second += (money / people);
        }
        if (people != 0) {
            bank.find(gifter)->second += (money % people);
        }
    }
    
    // output
    for (int i=0; i<order.size(); i++) {
        fout << order[i]  << " " << bank.find( order[i] )->second << '\n';
    }
    return 0;
}

