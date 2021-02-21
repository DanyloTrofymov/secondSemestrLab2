#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

string getDirectory();
void createFiles(string dir);
void discardContract();

//void averageScore();
//void sort();
//void ratingOut();


void main() {
 /*   string dir = getDirectory();
    createFiles(dir);*/
    discardContract();
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

void discardContract() {
    string number;
    string line;
  
    ifstream in("C:\\Users\OlhaShevel\Desktop\New folder\students1.csv");
   
        if (in.is_open()) {
            getline(in, number);
            int num = stoi(number);
            cout << num;
            for (int i = 1; i = num; i++) {
                getline(in, line);
                int pos = line.find_last_not_of(',');
                
                cout<< line.substr(pos, line.length());
            }

        
        }
       // in.close();
}