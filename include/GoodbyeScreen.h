#ifndef GOODBYE_SCREEN_H
#define GOODBYE_SCREEN_H

#include "Screen.h"

class GoodbyeScreen: public Screen{
public:
	void HandleInput() override; // 控制输入
	void Render() override; // 生成窗口
};

#endif
