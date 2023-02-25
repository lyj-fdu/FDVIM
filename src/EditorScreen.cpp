#include "../include/EditorScreen.h"
#include "../include/NormalTxt.h"

std::shared_ptr<Txt> EditorScreen::text_ = std::make_shared<NormalTxt>();

void EditorScreen::HandleInput(){
	text_->HandleInput();
}

void EditorScreen::Render(){
	text_->Render();
}
