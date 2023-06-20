#ifndef EDIT_SCREEN_H
#define EDIT_SCREEN_H

#include <fstream>
#include <memory>
#include "NormalTxt.h"
#include "Screen.h"
#include "Txt.h"

using std::fstream;

class EditScreen: public Screen {
public:
	static std::shared_ptr<Txt> text;

	void handleInput() override; // 控制输入
	void render() override; // 生成窗口
};

#endif
