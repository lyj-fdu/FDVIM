#include "../include/CursorOp.h"
#include "../include/WelcomeScreen.h"
#include "../include/EditorScreen.h"
#include "../include/Editor.h"

#include <iostream>

using std::cout;

void WelcomeScreen::HandleInput(){
	Editor::screen_ = std::make_shared<EditorScreen>(); // ����༭������
}

void WelcomeScreen::Render(){
	// ���û�ӭ����
	GotoXY(33, 10);
	cout << "Welcome to Simple Vim Editor!";
	GotoXY(42, 12);
	cout << "Author: Lin Yanjun:)";
	GotoXY(33, 14);
	system("pause"); // ��ͣ
	system("cls"); // ˢ��
	// ����ʹ����ʾ
	// GotoXY(27, 10);
	// cout << "Please Read The Instructions Before Using!";
	// GotoXY(27, 12);
	// cout << "Text Cannot Be Wider Or Higher Than The Window!";
	// GotoXY(27, 14);
	// cout << "Don't Resize The Window!";
	// GotoXY(27, 16);
	// system("pause"); // ��ͣ
	// system("cls"); // ˢ��
}
