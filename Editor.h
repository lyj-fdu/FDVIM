#ifndef EDITOR_H
#define EDITOR_H

#include <conio.h>
#include <memory>
#include <Windows.h>
#include "Screen.h"
#include "WelcomeScreen.h"

class Editor {
private:
	void handleInput(); // 控制输入
	void render(); // 生成窗口

public:
	Editor();
	static std::shared_ptr<Screen> screen; // 窗口
	void run(); // 运行
};

#endif