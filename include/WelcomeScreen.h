#ifndef WELCOME_SCREEN_H
#define WELCOME_SCREEN_H

#include "Screen.h"

class WelcomeScreen: public Screen{
public:
	void HandleInput() override; // ��������
	void Render() override; // ���ɴ���
};

#endif
