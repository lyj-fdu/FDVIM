#include"WelcomeScreen.h"
#include"EditorScreen.h"
#include"Editor.h"
#include"CursorOp.h"

#include<iostream>

using std::cout;

void WelcomeScreen::handleInput(){
	Editor::getScreen() = std::make_shared<EditorScreen>(); // 进入编辑器界面
}

void WelcomeScreen::render(){
	// 设置欢迎文字
	GotoXY(33, 10);
	cout << "Welcome to FDVIM Editor!";
	GotoXY(33, 12);
	cout << "Author: Lin Yanjun:)";
	GotoXY(33, 14);
	system("pause"); // 暂停
	system("cls"); // 刷新
	// 设置使用提示
	GotoXY(27, 10);
	cout << "WARNING: Please Follow README.md Instructions!";
	GotoXY(27, 12);
	system("pause"); // 暂停
	system("cls"); // 刷新
}