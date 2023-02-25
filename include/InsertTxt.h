#ifndef INSERT_TXT_H
#define INSERT_TXT_H

#include "Txt.h"

class InsertTxt: public Txt{
public:
	InsertTxt(vector<string>& txt, COORD& cur, History& history):Txt(txt, cur, history){}

	void HandleInput(); // ��������
	void Render(); // ���ɴ���

	void Insert(char& cmd); // �����ַ�
};

#endif
