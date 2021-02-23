#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>
#include <io.h>
using namespace std;
string getDirectory();      //gets directory 
//void createFiles(string dir);
void discardContract(string dir, vector <string> allFiles); // writes all students with attribute FALSE in csv

vector<string> findCsv(string dir); // Finds all .csv files in directiry 
//void averageScore(); // counts the avarage score of every student
//void sort(); // sotrs list of students by avarage score
//void ratingOut();


void main() {
    setlocale(LC_ALL, " ");
    string dir = getDirectory();
    vector<string> csvFiles = findCsv(dir);
    discardContract(dir, csvFiles);
}

string getDirectory() {
    string dir;
    cout << "enter directory:" << endl;
    getline(cin, dir);
    return dir;
}

//void createFiles(string dir) {
//    ofstream fout(dir + "\\rating.csv");
//    ofstream temp(dir + "\\temp.csv");
//}

void discardContract(string dir, vector<string> allFiles) {
    string number;
    string line;
    ofstream out(dir + "\\temp.csv");
    
    for (int i = 0; i < allFiles.size(); i++)
    {
        ifstream in(dir + "\\" + allFiles[i]);
        if (in.is_open()) {
            getline(in, number);
            int num = stoi(number);
            for (int j = 1; j < num; j++) {
                getline(in, line);
                int pos = line.find_last_of(',') + 1;

                string status = line.substr(pos, line.length());
                if (status == "FALSE") {
                    out << line.substr(0, pos-1) << endl;
                }
            }
            
        }
        in.close();
    }
    out.close();
}



vector<string> findCsv(string dir) {
    vector<string> allFiles;
    string csv = "\\*.csv";     // file type
    char charDir[200];  // makes const char for using on searching files function 

    for (int i = 0; i < dir.length(); i++) // writes directory in const char
    {
        charDir[i] = dir[i];
    }

    int j = 0; 
    for (int i = dir.length(); i < dir.length()+ csv.length()+1; i++)   // writes file type in const char
    {
        charDir[i] = csv[j];
        j++;
    }

    //searching .csv files function
    _finddata_t data;
    intptr_t handle = _findfirst(charDir, &data);
    do {
        allFiles.push_back(data.name);
    } while (_findnext(handle, &data) == 0);
    _findclose(handle);

    return allFiles;
}