#pragma once

#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "encabezados/PersonaxePrincipal.hpp"

class Camara
{
public: 
	const static unsigned int SCR_WIDTH;
	const static unsigned int SCR_HEIGHT;

	GLuint shaderProgram;
	float radio;
	float alpha;
	float beta;
	float width;
	float height;
	int modo;
	glm::vec3 posicionCamara;

	Camara(float radio, float alpha, float beta, GLuint shaderprogram);
	void establecerCamara(PersonaxePrincipal* p);
	void vistaPrimeiraPersoa(PersonaxePrincipal* p);
	void vistaXeral(PersonaxePrincipal* p);
	void vistaTerceiraPersoa(PersonaxePrincipal* p);
	void actualizarMatrizProxeccion();
};

