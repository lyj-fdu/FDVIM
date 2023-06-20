#include "Editor.h"

std::shared_ptr<Screen> Editor::screen = std::make_shared<WelcomeScreen>();

Editor::Editor() {
	system("mode con cols=100 lines=30"); // 设置窗口的行与列
	system("title FDVIM"); // 设置窗口名称
}

void Editor::run() {
	while(true) {
		render();
		handleInput();
	}
}

void Editor::handleInput() {
	screen->handleInput();
}

void Editor::render() {
	screen->render();
}