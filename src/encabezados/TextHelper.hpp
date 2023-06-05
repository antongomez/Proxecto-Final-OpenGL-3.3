#pragma once

#include <string>
#include <glm/glm.hpp>

#include <glad.h>

#define GLT_IMPLEMENTATION
#define GLT_MANUAL_VIEWPORT
#include "gltext.h"

class TextHelper
{ 
public:
	
	// -------------- Metodos ----------------- //
	static TextHelper* GetInstance();
	static void DeleteInstance();
	void escribir(float x, float y, float scale, int horizontal, int vertical);
	void cambiarViewport(int width, int height);
	float getAnchoTexto(float fontScale); 
	float getAltoTexto(float fontScale);
	void setTexto(std::string texto);

private:

	// --------------- Atributos ------------------- //
	glm::vec4 cor;
	GLTtext* text;


	// -------------- Construtores ----------------- //
	TextHelper();
	
};