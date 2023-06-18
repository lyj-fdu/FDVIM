#include"EditorScreen.h"
#include"NormalTxt.h"

std::shared_ptr<Txt> EditorScreen::text_ = std::make_shared<NormalTxt>();

void EditorScreen::handleInput(){
	text_->handleInput();
}

void EditorScreen::render(){
	text_->render();
}