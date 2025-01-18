/*******************************************************
* �t�@�C�����FFileio.cpp
* �T�v�@�@�@�F�t�@�C���̓ǂݍ��݁A�������݂����s����
********************************************************/
#pragma once
#include "header.h"

/*******************************************************
* �t�@�C���̓ǂݍ��݂��s���֐�
* �Ԃ�l�Ƃ��ă\�[�g�����ǂݍ��񂾃f�[�^��Ԃ�
* ����
* filename:�t�@�C����
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
* �t�@�C���̏������݂��s���֐�
* ����
* data:�������ރf�[�^
* filename:�t�@�C����
********************************************************/
void WriteFile(long long data, string filename) {
    ofstream file(filename, ios::app);
    file << endl << data;
}

/*******************************************************
* �t�@�C�������݂��邩�̊m�F���s���֐�
* ���݂��Ȃ��ꍇ�V���Ƀt�@�C�����쐬����
* ����
* filename:�t�@�C����
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