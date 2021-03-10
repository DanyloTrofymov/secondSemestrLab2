#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>
#include <io.h>
#include <iomanip>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    double average;

};



string getDirectory();      
vector<string> findCsv(string dir); // Finds all .csv files in directiry 
void deleteFile(string dir, string name); 
vector<Student> sortScores(vector<Student> list);
vector <Student> record_structures(string, vector<string> );
bool compareTwoStudents(Student, Student);


void main() {
    setlocale(LC_ALL, "Russian");
    string dir = getDirectory();
    vector<string> csvFiles = findCsv(dir);

    vector<Student> list = record_structures(dir, csvFiles);
    sortScores(list);

}

string getDirectory() {
    string dir;
    cout << "enter directory:" << endl;
    getline(cin, dir);
    return dir;
}

vector<Student> record_structures(string dir, vector<string> allFiles) {
    vector <Student> list;
    string number;
    string line;
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
                    line.erase(pos-1);
                    double average = 0;
                    for (int k = 0; k < 5; k++)
                    {
                        pos = line.find_last_of(',') + 1;
                        string score = line.substr(pos, line.length());
                        average += stod(score);
                        line.erase(pos-1);
                    }
                    average /= 5;
                    string name = line.substr(0, line.find_first_of(','));
                    Student s;
                    s.name = name;
                    s.average = average;
                    list.push_back(s);

                }
            }
        
        }
    }
    return list;
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
        if (allFiles[i] == "rating.csv") {
            deleteFile(dir, "\\rating.csv");
            allFiles.erase(allFiles.begin() + i);
        }
        else i++;
    } while (_findnext(handle, &data) == 0);
    _findclose(handle);

    return allFiles;
}

bool compareTwoStudents(Student a, Student b) {

    return a.average < b.average;  
}

vector<Student> sortScores(vector<Student> list) {
    ofstream out("\\rating.csv");
    vector<Student> rating;
    sort(list.rbegin(), list.rend(), compareTwoStudents);
    for (int i = 0; i < (list.size())*40/100; i++) {
        out << list[i].name << "," << list[i].average<<endl;
    
    }
   
    return rating;
}



void deleteFile(string dir, string name) {
    char charDir[200];
    for (int i = 0; i < dir.length(); i++) // writes directory in const char
    {
        charDir[i] = dir[i];
    }

    int j = 0;
    for (int i = dir.length(); i < dir.length() + name.length() + 1; i++)   // writes files in const char
    {
        charDir[i] = name[j];
        j++;
    }
    remove(charDir);
}