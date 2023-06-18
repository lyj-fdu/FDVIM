#ifndef INSERT_TXT_H
#define INSERT_TXT_H

#include <iostream>
#include "EditorScreen.h"
#include "NormalTxt.h"
#include "Txt.h"

using std::cin;
using std::cout;
using std::endl;

class InsertTxt: public Txt {
private:
	void insert(char& cmd); // 插入字符

public:
	InsertTxt(vector<string>& txt, COORD& cur, History& history):
		Txt(txt, cur, history) {}

	void handleInput(); // 控制输入
	void render(); // 生成窗口
};

#endif
