#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>
#include <io.h>
#include <iomanip>
#include <cstdio>
using namespace std;
string getDirectory();      //gets directory 
//void createFiles(string dir);
int discardContract(string dir, vector <string> allFiles); // writes all students with attribute FALSE in csv, returns count of non-contract students
vector<string> findCsv(string dir); // Finds all .csv files in directiry 
void averageScore(string dir, int count); // counts the avarage score of every student
void deleteFile(string dir, string name);
//void sort(); // sotrs list of students by avarage score
//void ratingOut();

void main() {
    setlocale(LC_ALL, "Russian");
    string dir = getDirectory();
    vector<string> csvFiles = findCsv(dir);
    int budget = discardContract(dir, csvFiles);
    averageScore(dir, budget);
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

int discardContract(string dir, vector<string> allFiles) {
    int count = 0; // counts not contract students
    string number;
    string line;
    ofstream out(dir + "\\ratingTemp.csv");
    
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
                    count++;
                }
            }
            
        }
        in.close();
    }
    out.close();
    return count;
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
    int i = 0;
    do {
        allFiles.push_back(data.name);
        if (allFiles[i] == "ratingTemp2.csv") {
            deleteFile(dir, "\\ratingTemp2.csv");
            allFiles.erase(allFiles.begin() + i);
        }
        else i++;
    } while (_findnext(handle, &data) == 0);
    _findclose(handle);

    return allFiles;
}

void averageScore(string dir, int count) {
    ifstream in(dir + "\\ratingTemp.csv");
    ofstream out(dir + "\\ratingTemp2.csv");
    string line;
    double average = 0;
    for (int i = 0; i < count; i++) {
        getline(in, line);
        for (int j = 0; j < 5; j++)
        {
            int pos = line.find_last_of(',');
            string score = line.substr(pos + 1);
            average += stod(score);
            line.erase(pos);
        }
        average /= 5;
        string result = to_string(average);
        out << line << "," << result.substr(0, 6) << endl;
        average = 0;
    }
    in.close();
    out.close();
    deleteFile(dir, "\\ratingTemp.csv");
}

void deleteFile(string dir, string name) {
    char charDir[200];
    for (int i = 0; i < dir.length(); i++) // writes directory in const char
    {
        charDir[i] = dir[i];
    }

    int j = 0;
    for (int i = dir.length(); i < dir.length() + name.length() + 1; i++)   // writes file type in const char
    {
        charDir[i] = name[j];
        j++;
    }
    remove(charDir);
}