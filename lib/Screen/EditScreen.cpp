#include "EditScreen.h"

std::shared_ptr<Txt> EditScreen::text = std::make_shared<NormalTxt>();

void EditScreen::handleInput() {
	text->handleInput();
}

void EditScreen::render() {
	text->render();
}
