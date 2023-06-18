#ifndef NORMAL_TXT_H
#define NORMAL_TXT_H

#include"Txt.h"

#include<fstream>

using std::fstream;

class NormalTxt: public Txt{
private:
	fstream file_; // 文件流

	void ReadTxt(string& filename); // 读文件
	void ExtractTxt(); // 将文件内容储存进向量中
	void WriteTxt(string& filename); // 写文件

	void PreProcess(const string& p, vector<int>& next); // KMP预处理
	void KMPSearch(string& pattern, COORD& cur); // KMP查找

public:
	NormalTxt(){}
	NormalTxt(vector<string>& txt, COORD& cur, History& history):Txt(txt, cur, history){}

	void handleInput(); // 控制输入
	void render(); // 生成窗口

	void RWTxt(); // 读写操作
	void Delete(); // 删除光标处的字符
	void undo(); // 撤销操作
	void redo(); // 重做操作
	void Search(); // 搜索操作

};

#endif