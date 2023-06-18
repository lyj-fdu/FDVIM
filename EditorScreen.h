#ifndef EDITOR_SCREEN_H
#define EDITOR_SCREEN_H

#include"Screen.h"
#include"Txt.h"

#include<fstream>
#include<memory>

using std::fstream;

class EditorScreen: public Screen{
public:
	static std::shared_ptr<Txt> text;

	void handleInput() override; // 控制输入
	void render() override; // 生成窗口
};

#endif