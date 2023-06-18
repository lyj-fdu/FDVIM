#ifndef TXT_H
#define TXT_H

#include <stack>
#include <string>
#include <vector>
#include "CursorOp.h"

using std::stack;
using std::string;
using std::vector;

class History {
private:
	stack<vector<string>> undo_txt, redo_txt; // 撤销与重做的文本内容
	stack<COORD> undo_cur, redo_cur; // 撤销与重做的光标位置

public:
	void save(const vector<string>& txt, const COORD& cur); // 保留操作前的状态
	void undo(vector<string>& txt, COORD& cur); // 撤销
	void redo(vector<string>& txt, COORD& cur); // 重做
	bool canUndo() {return static_cast<int>(undo_cur.size()) > 0;} // Undo空否
	bool canRedo() {return static_cast<int>(redo_cur.size()) > 0;} // Undo空否
};

class Txt{
protected:
	vector<string> txt; // 文本内容
	COORD cur; // 光标位置
	History history; // 历史操作

	void moveLeft(); // 光标左移
	void moveDown(); // 光标下移
	void moveUp(); // 光标上移
	void moveRight(); // 光标右移

public:
	Txt() {}
	Txt(vector<string>& txt, COORD& cur, History& history)
		:txt(txt), cur(cur), history(history) {}

	virtual void handleInput() = 0; // 控制输入
	virtual void render() = 0; // 生成窗口
};

#endif