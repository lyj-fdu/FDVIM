#ifndef GOODBYE_SCREEN_H
#define GOODBYE_SCREEN_H

#include <conio.h>
#include <iostream>
#include "CursorOp.h"
#include "Screen.h"

using std::cout;

class GoodbyeScreen: public Screen {
public:
	void handleInput() override; // 控制输入
	void render() override; // 生成窗口
};

#endif
