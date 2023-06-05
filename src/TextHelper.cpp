#include "encabezados/TextHelper.hpp"

static TextHelper* th = nullptr;

TextHelper::TextHelper() {
	this->cor = glm::vec4(1.0f);
	gltInit();
	this->text = gltCreateText();
}

TextHelper* TextHelper::GetInstance() {
	if(th == nullptr) {
		th = new TextHelper();
	}

	return th;
}

void TextHelper::DeleteInstance() {
	gltDeleteText(th->text);
	gltTerminate();
}

void TextHelper::escribir(float x, float y, float scale, int horizontal, int vertical) {

	gltBeginDraw();

	gltColor(cor.x, cor.y, cor.z, cor.a);
	gltDrawText2DAligned(text, x, y, scale, horizontal, vertical);

	gltEndDraw();
}

void TextHelper::cambiarViewport(int width, int height) {
	gltViewport(width, height);
}

float TextHelper::getAnchoTexto(float fontScale) {
	return gltGetTextWidth(text, fontScale);
}

float TextHelper::getAltoTexto(float fontScale) {
	return gltGetTextHeight(text, fontScale);
}

void TextHelper::setTexto(std::string texto) {
	gltSetText(text, texto.c_str());
}