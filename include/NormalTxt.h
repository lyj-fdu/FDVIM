#ifndef NORMAL_TXT_H
#define NORMAL_TXT_H

#include "Txt.h"

#include <fstream>

class NormalTxt: public Txt{
private:
	std::fstream file_; // �ļ���

	void ReadTxt(string& filename); // ���ļ�
	void ExtractTxt(); // ���ļ����ݴ����������
	void WriteTxt(string& filename); // д�ļ�

	void PreProcess(const string& p, vector<int>& next); // KMPԤ����
	void KMPSearch(string& pattern, COORD& cur); // KMP����

public:
	NormalTxt(){}
	NormalTxt(vector<string>& txt, COORD& cur, History& history):Txt(txt, cur, history){}

	void HandleInput(); // ��������
	void Render(); // ���ɴ���

	void RWTxt(); // ��д����
	void Delete(); // ɾ����괦���ַ�
	void Undo(); // ��������
	void Redo(); // ��������
	void Search(); // ��������
};

#endif
