#ifndef INSERT_TXT_H
#define INSERT_TXT_H

#include"Txt.h"

class InsertTxt: public Txt{
public:
	InsertTxt(vector<string>& txt, COORD& cur, History& history):Txt(txt, cur, history){}

	void handleInput(); // 控制输入
	void render(); // 生成窗口

	void Insert(char& cmd); // 插入字符

};

#endif