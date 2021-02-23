#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <vector>;
#include <direct.h>
#include <io.h>
using namespace std;

string getDirectory();
void createFiles(string dir);
void discardContract();

vector<string> findCsv(string dir);
//void discardContract();
//void averageScore();
//void sort();
//void ratingOut();


void main() {
    string dir = getDirectory();
    createFiles(dir);
    discardContract();
    vector<string> csvFiles = findCsv(dir);
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

    ifstream in("C:\\Users\\OlhaShevel\\Desktop\\new_folder\\students1.csv");
    ofstream out("C:\\Users\\OlhaShevel\\Desktop\\new_folder\\temp.csv");
  

    if (in.is_open()) {
        getline(in, number);
        int num = stoi(number);
        cout << num;
        for (int i = 1; i < num; i++) {
            getline(in, line);
            int pos = line.find_last_of(',') + 1;

            string status = line.substr(pos, line.length());
            cout << status;
            if (status == "FALSE") {
                out << line << endl;
            }
        }



    }
}
       // in.close();


vector<string> findCsv(string dir) {
    vector<string> allFiles;
    string csv = "\\*.csv";
    char charDir[200];

    for (int i = 0; i < dir.length(); i++)
    {
        charDir[i] = dir[i];
    }

    int j = 0;
    for (int i = dir.length(); i < dir.length()+7; i++)
    {
        charDir[i] = csv[j];
        j++;
    }

    _finddata_t data;
    intptr_t handle = _findfirst(charDir, &data);
    do {
        allFiles.push_back(data.name);
    } while (_findnext(handle, &data) == 0);
    _findclose(handle);

    return allFiles;
}