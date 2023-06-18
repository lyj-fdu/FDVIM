#ifndef WELCOME_SCREEN_H
#define WELCOME_SCREEN_H

#include <iostream>
#include "CursorOp.h"
#include "Editor.h"
#include "EditorScreen.h"
#include "Screen.h"

using std::cout;

class WelcomeScreen: public Screen {
public:
	void handleInput() override; // 控制输入
	void render() override; // 生成窗口
};

#endif
