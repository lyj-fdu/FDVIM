#include"NormalTxt.h"
#include"Editor.h"
#include"GoodbyeScreen.h"
#include"EditorScreen.h"
#include"InsertTxt.h"

#include<iostream>

using std::cout;
using std::cin;
using std::endl;
using std::ios;

void NormalTxt::HandleInput(){
	cin.sync(); // 清空输入缓冲区
	char cmd = _getch(); // 读取字符
	if(!isascii(cmd)) // 将字符转换为键盘指令
		cmd = _getch();
	switch(cmd){
	case ':': // 文件读写
		RWTxt();
		break;
	case 'x': // 删除光标处的字符
		Delete();
		break;
	case 'u': // 撤销操作
		Undo();
		break;
	case 'r': // 重做操作
		Redo();
		break;
	case 'h': // 光标左移
		MoveLeft();
		break;
	case 'j': // 光标下移
		MoveDown();
		break;
	case 'k': // 光标上移
		MoveUp();
		break;
	case 'l': // 光标右移
		MoveRight();
		break;
	case 'i': // 插入模式
		EditorScreen::text_ = std::make_shared<InsertTxt>(txt_, cur_, history_);
		break;
	case '/': // 寻字模式
		Search();
		break;
	}
}

void NormalTxt::Render(){
	// 清屏
	system("cls");
	// 底部栏目
	GotoXY(0, 27);
	cout << "______________________________________________Command______________________________________________";
	GotoXY(0, 28);
	cout << "<Normal> ";
	// 显示文本
	GotoXY(0, 0);
	if(txt_.size() == 0) return;
	int len = txt_.size();
	for(int i = 0; i < len - 1; i++)
		cout << txt_[i] << endl;
	cout << txt_[len - 1];
	// 显示光标
	GotoXY(cur_.X, cur_.Y);
}

void NormalTxt::ReadTxt(string& filename){
	file_.close(); // 关闭上一个文件
	file_.open(filename.data(), ios::in); // 打开新文件，读模式
	if(!file_.is_open()){

		Render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "File Not Found!";
		GotoXY(cur_.X, cur_.Y);

		return;
	}

	Render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << "Opening...";

	ExtractTxt(); // 提取文件内容到向量中
	// 获取光标位置
	cur_.Y = static_cast<int>(txt_.size()) - 1;
	cur_.X = static_cast<int>(txt_[cur_.Y].size()) - 1;
	history_.Save(txt_, cur_); // 保留历史操作
}

void NormalTxt::ExtractTxt(){
	txt_.resize(0); txt_.shrink_to_fit(); // 初始化txt
	if(file_.is_open()){ // 文件打开时读入
		file_.seekg(0, ios::beg); // 将文件指针指向开头
		while(!file_.eof()){ // 读到文件末尾
			string line;
			getline(file_,line);
			txt_.push_back(line);
		}
		file_.seekg(0, ios::beg); // 将文件指针指向开头
	}
}

void NormalTxt::WriteTxt(string& filename){
	Render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << "Saving...";

	file_.close(); // 关闭上一个文件
	file_.open(filename.data(), ios::out); // 打开新文件，写模式
	if(txt_.size() == 0) return;
	int len = txt_.size();
	for(int i = 0; i < len - 1; i++)
		file_ << txt_[i] << endl;
	file_ << txt_[len - 1];
}

void NormalTxt::PreProcess(const string& p, vector<int>& next){
	int len = p.size(); // p长度
	next.resize(len); next.shrink_to_fit(); // next容量
	int i(0), j = next[0] = -1; // 初始化
	while(i < len - 1){
		while(j > -1 && p[i] != p[j])
			j = next[j];
		i++; j++;
		if(p[i] == p[j]) next[i] = next[j];
		else next[i] = j;
	}
}

void NormalTxt::KMPSearch(string& pattern, COORD& cur){
	vector<int> next; PreProcess(pattern, next); // 预处理
	int plen = pattern.size(), ylen = static_cast<int>(txt_.size()), xlen(0);
	for(int p = cur.Y; p < ylen; p++){ // 从这行找到末尾
		int q = (p == cur.Y) ? cur.X : 0, k(0); // 起始行q赋值x，否则赋值0
		xlen = static_cast<int>(txt_[p].size()); // 本行的长度
		while(q < xlen){ // q遍历本行查找
			while(k > -1 && pattern[k] != txt_[p][q])
				k = next[k];
			q++; k++;
			if(k == plen){ // 找到
				history_.Save(txt_, cur); // 保留历史操作
				cur.X = q - k; // 定位x
				cur.Y = p; // 定位y
				GotoXY(9, 28); // 移动光标到"<Normal> "之后
				cout << "Found! Locate cursor to first \"" << pattern << "\"!"; // 输出找到信息
				GotoXY(cur.X, cur.Y); // 定位光标
				Sleep(1000); // 休眠1秒
				return;
			}
		}
	}
	// 没找到
	Render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << "Not Found! Do you want to find \"" << pattern << "\" from begnning?(y/n)"; // 输出没找到信息
	char choice;
	cin >> choice;
	if(choice == 'y'){
		Render();
		history_.Save(txt_, cur); // 保留历史操作
		cur.X = 0; cur.Y = 0; // 定位至开头
		KMPSearch(pattern, cur);
	}
}

void NormalTxt::RWTxt(){
	string op, filename;
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << ":";
	cin >> op;
	if (op == "q")
		Editor::screen_ = std::make_shared<GoodbyeScreen>();
	if(op == "open") { // 读
		cin >> filename;
		filename = "assets/" + filename;
		ReadTxt(filename);
	} else if(op == "w") { // 写
		cin >> filename;
		filename = "assets/" + filename;
		WriteTxt(filename);
	}
}

void NormalTxt::Delete(){
	if(cur_.X == 0 && cur_.Y == 0 && static_cast<int>(txt_.size()) == 0) return; // 第一行开头且无字

	Render();
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << "Delete!";
	GotoXY(cur_.X, cur_.Y);

	history_.Save(txt_, cur_); // 保留历史操作

	if(cur_.X == 0 && cur_.Y == 0){ // 第一行开头且文本有字
		if(static_cast<int>(txt_[0].size()) == 0) // 空行
			txt_.erase(txt_.begin()); // 删除空行
		else // 有字
			txt_[0].erase(txt_[0].begin()); // 删除第一个字
		return;
	}
	
	if(cur_.X == 0){ // 仅有1字
		txt_[cur_.Y].erase(txt_[cur_.Y].begin() + cur_.X); // 删除
		if(static_cast<int>(txt_[cur_.Y].size()) == 0) // 空行
			txt_.erase(txt_.begin() + cur_.Y); // 删除空行
		cur_.Y--; // 移到上一行
		cur_.X = static_cast<int>(txt_[cur_.Y].size()) > 0 ? 
			static_cast<int>(txt_[cur_.Y].size()) - 1 : 0; // 移到末尾
	}else 
		if(cur_.X < static_cast<int>(txt_[cur_.Y].size())) // 有效删除区域内，不在该行末尾之外
			txt_[cur_.Y].erase(txt_[cur_.Y].begin() + cur_.X--); // 删除并左移
		else // 在该行末尾之外
			cur_.X--; // 直接左移
}

void NormalTxt::Undo(){
	if(history_.CanUndo()){
		history_.Undo(txt_, cur_);

		Render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "Undo!";
	}else{
		Render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "No more Undo!";
	}
	GotoXY(cur_.X, cur_.Y);
}

void NormalTxt::Redo(){
	if(history_.CanRedo()){
		history_.Redo(txt_, cur_);

		Render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "Redo!";
	}else{
		Render();
		GotoXY(9, 28); // 移动光标到"<Normal> "之后
		cout << "No more Redo!";
	}
	GotoXY(cur_.X, cur_.Y);
}

void NormalTxt::Search(){
	GotoXY(9, 28); // 移动光标到"<Normal> "之后
	cout << '/';
	string pattern;
	cin.sync(); // 清空读入缓冲区
	std::getline(cin, pattern);
	KMPSearch(pattern, cur_);
}