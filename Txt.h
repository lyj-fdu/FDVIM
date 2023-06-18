#ifndef TXT_H
#define TXT_H

#include <string>
#include <vector>
#include "CursorOp.h"
#include "History.h"

using std::string;
using std::vector;

class Txt {
protected:
	vector<string> txt; // 文本内容
	COORD cur; // 光标位置
	History history; // 历史操作

	void moveLeft(); // 光标左移
	void moveDown(); // 光标下移
	void moveUp(); // 光标上移
	void moveRight(); // 光标右移

public:
	Txt(vector<string>& txt, COORD& cur, History& history)
		: txt(txt), cur(cur), history(history) {}

	virtual void handleInput() = 0; // 控制输入
	virtual void render() = 0; // 生成窗口
};

#endif
