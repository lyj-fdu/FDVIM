#ifndef TXT_H
#define TXT_H

#include"CursorOp.h"

#include<vector>
#include<stack>
#include<string>

using std::vector;
using std::stack;
using std::string;

class History{
private:
	stack<vector<string>> undo_txt_, redo_txt_; // 撤销与重做的文本内容
	stack<COORD> undo_cur_, redo_cur_; // 撤销与重做的光标位置

public:
	void Save(const vector<string>& txt, const COORD& cur); // 保留操作前的状态
	void Undo(vector<string>& txt, COORD& cur); // 撤销
	void Redo(vector<string>& txt, COORD& cur); // 重做
	bool CanUndo(){return static_cast<int>(undo_cur_.size()) > 0;} // Undo空否
	bool CanRedo(){return static_cast<int>(redo_cur_.size()) > 0;} // Undo空否
};

class Txt{
protected:
	vector<string> txt_; // 文本内容
	COORD cur_; // 光标位置
	History history_; // 历史操作

public:
	Txt(){}
	Txt(vector<string>& txt, COORD& cur, History& history)
		:txt_(txt), cur_(cur), history_(history){}

	virtual void HandleInput() = 0; // 控制输入
	virtual void Render() = 0; // 生成窗口

	void MoveLeft(); // 光标左移
	void MoveDown(); // 光标下移
	void MoveUp(); // 光标上移
	void MoveRight(); // 光标右移
};

#endif