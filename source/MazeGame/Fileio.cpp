/*******************************************************
* ファイル名：Fileio.cpp
* 概要　　　：ファイルの読み込み、書き込みを実行する
********************************************************/
#pragma once
#include "header.h"

/*******************************************************
* ファイルの読み込みを行う関数
* 返り値としてソートした読み込んだデータを返す
* 引数
* filename:ファイル名
********************************************************/
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

/*******************************************************
* ファイルの書き込みを行う関数
* 引数
* data:書き込むデータ
* filename:ファイル名
********************************************************/
void WriteFile(long long data, string filename) {
    ofstream file(filename, ios::app);
    file << endl << data;
}

/*******************************************************
* ファイルが存在するかの確認を行う関数
* 存在しない場合新たにファイルを作成する
* 引数
* filename:ファイル名
********************************************************/
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