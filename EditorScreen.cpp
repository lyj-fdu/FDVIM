#include "EditorScreen.h"

std::shared_ptr<Txt> EditorScreen::text = std::make_shared<NormalTxt>();

void EditorScreen::handleInput() {
	text->handleInput();
}

void EditorScreen::render() {
	text->render();
}
