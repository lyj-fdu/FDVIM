#ifndef EDITOR_H
#define EDITOR_H

#include "Screen.h"

#include <memory>

class Editor{
public:
	static std::shared_ptr<Screen> screen_; // ����

public:
	Editor();

	void Run(); // ����

	void HandleInput(); // ��������
	void Render(); // ���ɴ���
};

#endif
