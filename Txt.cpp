#include "Txt.h"

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

void Txt::moveLeft() {
	if (cur.X == 0 && cur.Y == 0) return;
	history.save(txt, cur); // 保留历史操作
	if (cur.X > 0) // 本行左移
		cur.X--;
	else { // 移到上一行的末尾
		cur.Y--;
		cur.X = static_cast<int>(txt[cur.Y].size()) > 0 ?
		        static_cast<int>(txt[cur.Y].size()) - 1 : 0;
	}
}

void Txt::moveDown() {
	if (cur.Y >= 26) return;
	history.save(txt, cur); // 保留历史操作
	cur.Y++; // 下移
	if (cur.Y < static_cast<int>(txt.size())) {
		if (cur.X > static_cast<int>(txt[cur.Y].size())) // 超过这一行太多就定位到这一行多一个字的地方
			cur.X = static_cast<int>(txt[cur.Y].size());
	} else { // 另起一行
		txt.insert(txt.begin() + cur.Y, string()); // 插入空行
		cur.X = 0; // 头
	}
}

void Txt::moveUp() {
	if (cur.Y == 0) return;
	history.save(txt, cur); // 保留历史操作
	if (cur.Y == static_cast<int>(txt.size() - 1) &&
	    static_cast<int>(txt[cur.Y].size()) == 0) // 最底下是空行
		txt.erase(txt.begin() + cur.Y); // 删除空行
	cur.Y--;
	if (cur.X > static_cast<int>(txt[cur.Y].size())) // 超过这一行太多就定位到这一行多一个字的地方
		cur.X = static_cast<int>(txt[cur.Y].size());
}

void Txt::moveRight() {
	if (cur.X == static_cast<int>(txt[cur.Y].size()) &&
	    cur.Y == static_cast<int>(txt.size()) - 1) return; // 文本末尾，不能再右移
	history.save(txt, cur); // 保留历史操作
	if (cur.X < static_cast<int>(txt[cur.Y].size()))
		cur.X++; // 本行右移，可以比这一行多1个字，但不能再出去
	else { // 下一行开头
		cur.Y++;
		cur.X = 0;
	}
}
