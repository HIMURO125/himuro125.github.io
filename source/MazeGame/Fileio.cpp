#pragma once
#include "header.h"

vector<int> ReadFile(string filename) {
	ifstream file(filename);
	string line = "";
	vector<int> data;
    while (getline(file, line)) {
        stringstream ss;
        int num = 0;
        ss.str("");
        ss << line;
        ss >> num;
        data.push_back(num);
    }
    sort(data.begin(), data.end());
    return data;
}

void WriteFile(long long data, string filename) {
    ofstream file(filename, ios::app);
    file << endl << data;
}

void CheckFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        ofstream newfile(filename);
        newfile << 100 << endl;
        newfile << 200 << endl;
        newfile << 300;
        newfile.close();
    }
}