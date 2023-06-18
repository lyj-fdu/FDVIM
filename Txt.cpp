#include "Txt.h"

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
