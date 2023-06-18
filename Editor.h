#ifndef EDITOR_H
#define EDITOR_H

#include <conio.h>
#include <memory>
#include <Windows.h>
#include "Screen.h"
#include "WelcomeScreen.h"

class Editor {
private:
	static void handleInput(); // 控制输入
	static void render(); // 生成窗口

	Editor() {} // 单例模式

public:
	static std::shared_ptr<Screen> screen; // 窗口

	static void run(); // 运行
};

#endif