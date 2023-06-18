#ifndef EDITOR_H
#define EDITOR_H

#include"Screen.h"
#include<memory>

class Editor{
private:
	static std::shared_ptr<Screen> screen_; // 窗口

	Editor() {} // 单例模式

	static void handleInput(); // 控制输入
	static void render(); // 生成窗口

public:
	static std::shared_ptr<Screen>& getScreen(); // 获取窗口
	static void run(); // 运行
};

#endif