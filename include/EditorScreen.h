#ifndef EDITOR_SCREEN_H
#define EDITOR_SCREEN_H

#include "Screen.h"
#include "Txt.h"

#include <memory>

class EditorScreen: public Screen{
public:
	static std::shared_ptr<Txt> text_;

	void HandleInput() override; // ��������
	void Render() override; // ���ɴ���
};

#endif
