#include "Editor.h"

std::shared_ptr<Screen> Editor::screen_ = std::make_shared<WelcomeScreen>();

std::shared_ptr<Screen>& Editor::getScreen() {
	return screen_;
}

void Editor::run() {
	system("mode con cols=100 lines=30"); // 设置窗口的行与列
	system("title FDVIM"); // 设置窗口名称
	while(1) {
		render();
		handleInput();
	}
}

void Editor::handleInput() {
	screen_->handleInput();
}

void Editor::render() {
	screen_->render();
}