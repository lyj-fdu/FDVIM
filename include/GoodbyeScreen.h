#ifndef GOODBYE_SCREEN_H
#define GOODBYE_SCREEN_H

#include "Screen.h"

class GoodbyeScreen: public Screen{
public:
	void HandleInput() override; // ��������
	void Render() override; // ���ɴ���
};

#endif
