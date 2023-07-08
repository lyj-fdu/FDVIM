#include "WelcomeScreen.h"

void WelcomeScreen::handleInput() {
	Editor::screen = std::make_shared<EditScreen>(); // 进入编辑器界面
}

void WelcomeScreen::render() {
	// 欢迎文字
	/* http://patorjk.com/software/taag/#p=display&h=1&f=3D-ASCII&t=FDVIM
	 ________  ________   ___      ___  ___   _____ ______      
	|\  _____\|\   ___ \ |\  \    /  /||\  \ |\   _ \  _   \    
	\ \  \__/ \ \  \_|\ \\ \  \  /  / /\ \  \\ \  \\\__\ \  \   
	 \ \   __\ \ \  \ \\ \\ \  \/  / /  \ \  \\ \  \\|__| \  \  
	  \ \  \_|  \ \  \_\\ \\ \    / /    \ \  \\ \  \    \ \  \ 
	   \ \__\    \ \_______\\ \__/ /      \ \__\\ \__\    \ \__\
	    \|__|     \|_______| \|__|/        \|__| \|__|     \|__|
	*/
	Cursor::setPos(20, 10);
	cout << " ________  ________   ___      ___  ___   _____ ______      ";
	Cursor::setPos(20, 11);
	cout << "|\\  _____\\|\\   ___ \\ |\\  \\    /  /||\\  \\ |\\   _ \\  _   \\    ";
	Cursor::setPos(20, 12);
	cout << "\\ \\  \\__/ \\ \\  \\_|\\ \\\\ \\  \\  /  / /\\ \\  \\\\ \\  \\\\\\__\\ \\  \\   ";
	Cursor::setPos(20, 13);
	cout << " \\ \\   __\\ \\ \\  \\ \\\\ \\\\ \\  \\/  / /  \\ \\  \\\\ \\  \\\\|__| \\  \\  ";
	Cursor::setPos(20, 14);
	cout << "  \\ \\  \\_|  \\ \\  \\_\\\\ \\\\ \\    / /    \\ \\  \\\\ \\  \\    \\ \\  \\ ";
	Cursor::setPos(20, 15);
	cout << "   \\ \\__\\    \\ \\_______\\\\ \\__/ /      \\ \\__\\\\ \\__\\    \\ \\__\\";
	Cursor::setPos(20, 16);
	cout << "    \\|__|     \\|_______| \\|__|/        \\|__| \\|__|     \\|__|";
	Cursor::setPos(20, 18);
	system("pause"); // 暂停
	system("cls"); // 刷新
	// 使用提示
	Cursor::setPos(20, 10);
	cout << "AUTHOR : Lin-Yanjun";
	Cursor::setPos(20, 12);
	cout << "EMAIL  : 20307130136@fudan.edu.cn";
	Cursor::setPos(20, 14);
	cout << "HINT   : Please Follow README.md Instructions!";
	Cursor::setPos(20, 16);
	system("pause"); // 暂停
	system("cls"); // 刷新
}
