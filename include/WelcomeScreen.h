#ifndef WELCOME_SCREEN_H
#define WELCOME_SCREEN_H

#include "Screen.h"

class WelcomeScreen: public Screen{
public:
	void HandleInput() override; // 控制输入
	void Render() override; // 生成窗口
};

#endif
