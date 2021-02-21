#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string getDirectory();
void createFiles(string dir);
//void discardContract();
//void averageScore();
//void sort();
//void ratingOut();

void main() {
    string dir = getDirectory();
    createFiles(dir);
}

string getDirectory() {
    string dir;
    cout << "enter directory:" << endl;
    getline(cin, dir);
    return dir;
}

void createFiles(string dir) {
    ofstream fout(dir + "rating.csv");
    ofstream temp(dir + "temp.csv");
}