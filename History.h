#ifndef HISTORY_H
#define HISTORY_H

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
	bool canUndo(); // undo空否
	bool canRedo(); // redo空否
};

#endif