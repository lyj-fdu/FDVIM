#include"InsertTxt.h"
#include"EditorScreen.h"
#include"NormalTxt.h"

#include<iostream>

using std::cout;
using std::endl;
using std::cin;

enum Dir{Up = 72, Down = 80, Left = 75, Right = 77, ESC = 27};

void InsertTxt::HandleInput(){
	cin.sync(); // 清空输入缓冲区
	char cmd = _getch(); // 读取字符
	if(!isascii(cmd)) // 将字符转换为键盘指令
		cmd = _getch();
	switch(cmd){
	case Left: // 光标左移
		MoveLeft();
		break;
	case Down: // 光标下移
		MoveDown();
		break;
	case Up: // 光标上移
		MoveUp();
		break;
	case Right: // 光标右移
		MoveRight();
		break;
	case ESC: // 普通模式
		EditorScreen::text_ = std::make_shared<NormalTxt>(txt_, cur_, history_);
		break;
	default: // 输入字符
		Insert(cmd);
		break;
	}
}

void InsertTxt::Render(){
	// 清屏
	system("cls");
	// 底部栏目
	GotoXY(0, 28);
	cout << "<Insert>";
	// 显示文本
	if(txt_.size() == 0) return;
	GotoXY(0, 0);
	if(txt_.size() == 0) return;
	int len = txt_.size();
	for(int i = 0; i < len - 1; i++)
		cout << txt_[i] << endl;
	cout << txt_[len - 1];
	// 显示光标
	GotoXY(cur_.X, cur_.Y);
}

void InsertTxt::Insert(char& cmd){
	if(isprint(cmd)){
		if(cur_.Y < static_cast<int>(txt_.size()) && 
			cur_.X <= static_cast<int>(txt_[cur_.Y].size())){ // 在某一现有的行插入
			history_.Save(txt_, cur_); // 保留历史操作
			txt_[cur_.Y].insert(txt_[cur_.Y].begin() + cur_.X++, cmd); // 插入并更新x

			Render();
			GotoXY(9, 28); // 移动光标到"<Normal> "之后
			cout << "Insert!";
			GotoXY(cur_.X, cur_.Y);
		}
	}
}