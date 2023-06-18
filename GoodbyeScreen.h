#ifndef GOODBYE_SCREEN_H
#define GOODBYE_SCREEN_H

#include"Screen.h"

class GoodbyeScreen: public Screen{
public:
	void handleInput() override; // 控制输入
	void render() override; // 生成窗口
};

#endif