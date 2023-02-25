#include "../include/Editor.h"
#include "../include/WelcomeScreen.h"

std::shared_ptr<Screen> Editor::screen_ = std::make_shared<WelcomeScreen>();

Editor::Editor(){
	system("mode con cols=100 lines=30"); // ���ô��ڵ�������
	system("title Simple Vim"); // ���ô�������
}

void Editor::Run(){
	while(1){
		Render();
		HandleInput();
	}
}

void Editor::HandleInput(){
	screen_->HandleInput();
}

void Editor::Render(){
	screen_->Render();
}
