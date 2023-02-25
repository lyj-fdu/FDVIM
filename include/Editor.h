#ifndef EDITOR_H
#define EDITOR_H

#include "Screen.h"

#include <memory>

class Editor{
public:
	static std::shared_ptr<Screen> screen_; // 窗口

public:
	Editor();

	void Run(); // 运行

	void HandleInput(); // 控制输入
	void Render(); // 生成窗口
};

#endif
