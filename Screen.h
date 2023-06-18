#ifndef SCREEN_H
#define SCREEN_H

class Screen{
public:
	virtual void HandleInput() = 0; // 处理输入
	virtual void Render() = 0; // 生成窗口
};

#endif