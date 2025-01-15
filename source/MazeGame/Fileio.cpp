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

void WriteFile(vector<int> data, string filename) {
    ofstream file(filename);
    for (int i = 0; i < data.size(); i++) {
        file << data[i] << endl;
    }
}