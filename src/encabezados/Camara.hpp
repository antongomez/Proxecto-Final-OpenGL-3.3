#pragma once

#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	Camara(float radio, float alpha, float beta);
	void vistaPrimeiraPersoa(float x, float y, float z, float angulo);
	void vistaXeral(glm::vec3 target);
	void vistaTerceiraPersoa(float x, float y, float z, float angulo);
	void actualizarMatrizProxeccion();
};

