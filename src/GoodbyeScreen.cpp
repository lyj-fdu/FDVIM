#include "../include/CursorOp.h"
#include "../include/GoodbyeScreen.h"

#include <iostream>

using std::cout;

void GoodbyeScreen::HandleInput(){}

void GoodbyeScreen::Render(){
	system("cls"); // ˢ��
	GotoXY(36, 12);
	cout << "Thanks for Using!";
	GotoXY(36, 14);
	system("pause"); // ��ͣ
	exit(0);
}
