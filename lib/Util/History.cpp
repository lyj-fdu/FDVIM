#include "History.h"

void History::save(const vector<string>& txt, const COORD& cur) {
	undo_txt.push(txt); // 保留这次操作的文本
	undo_cur.push(cur); // 保留这次操作的光标位置
}

void History::undo(vector<string>& txt, COORD& cur) {
	if (!undo_txt.empty() && !undo_cur.empty()) {
		// 文本操作
		txt = undo_txt.top(); // 获取上一次的txt
		undo_txt.pop(); // 删除
		redo_txt.push(txt); // 插入
		// 光标操作
		cur.X = undo_cur.top().X;
		cur.Y = undo_cur.top().Y; // 获取上一次的光标位置
		undo_cur.pop(); // 删除
		redo_cur.push(cur); // 插入
	}
}

void History::redo(vector<string>& txt, COORD& cur) {
	if (!redo_txt.empty() && !redo_cur.empty()) {
		// 文本操作
		txt = redo_txt.top(); // 获取上一次的txt
		redo_txt.pop(); // 删除
		undo_txt.push(txt); // 插入
		// 光标操作
		cur.X = redo_cur.top().X;
		cur.Y = redo_cur.top().Y; // 获取上一次的光标位置
		redo_cur.pop(); // 删除
		undo_cur.push(cur); // 插入
	}
}

bool History::canUndo() {
	return static_cast<int>(undo_cur.size()) > 0;   // undo空否
}

bool History::canRedo() {
	return static_cast<int>(redo_cur.size()) > 0;   // redo空否
}
