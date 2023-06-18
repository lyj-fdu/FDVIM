#ifndef SCREEN_H
#define SCREEN_H

class Screen{
public:
	virtual void handleInput() = 0; // 处理输入
	virtual void render() = 0; // 生成窗口
};

#endif