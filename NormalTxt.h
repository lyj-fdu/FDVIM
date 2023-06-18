#ifndef NORMAL_TXT_H
#define NORMAL_TXT_H

#include <fstream>
#include <iostream>
#include "Editor.h"
#include "EditorScreen.h"
#include "GoodbyeScreen.h"
#include "InsertTxt.h"
#include "Txt.h"

using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ios;

class NormalTxt: public Txt {
private:
	fstream file; // 文件流

	void readTxt(string& filename); // 读文件
	void writeTxt(string& filename); // 写文件
	void exeCmd(); // 读写操作

	void KMPPreProcess(const string& p, vector<int>& next); // KMP预处理
	void KMPSearch(string& pattern, COORD& cur); // KMP查找
	void searchStr(); // 搜索操作

	void delChar(); // 删除光标处的字符
	void undo(); // 撤销操作
	void redo(); // 重做操作

public:
	NormalTxt() {}
	NormalTxt(vector<string>& txt, COORD& cur, History& history):
		Txt(txt, cur, history) {}

	void handleInput(); // 控制输入
	void render(); // 生成窗口
};

#endif
