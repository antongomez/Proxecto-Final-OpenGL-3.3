#pragma once 

#include "Suelo.hpp"
#include "SkyBox.hpp"
#include "Enemigo.hpp"
#include "PersonaxePrincipal.hpp"
#include "Camara.hpp"
#include "Luz.hpp"

#include <vector>
#include <map>
#include <glm/glm.hpp>

class Mundo
{
public:
	// Atributos
	Suelo* suelo;
	std::vector<Obxecto*> obxectosDecorativos;
	std::vector<Enemigo*> inimigos;
	PersonaxePrincipal* personaxePrincipal;
	std::map<int, std::vector<Luz*>> luces;
	Camara* camara;
	int nivelMundo;
	SkyBox* skyBox;

	GLuint shaderProgram;
	GLuint shaderProgramTex;

	// Construtores
	Mundo(PersonaxePrincipal* personaxe, GLuint shaderProgram, GLuint shaderProgramTex,
		float alturaMundo, float* limites,
		std::map<int, int> elementosDecorativos,
		int nivelMundo, std::map<int, std::vector<Luz*>> luces,
		std::string rutaTexturasSkyBox[],
		std::string rutaTexturaSuelo);

	// Destructor

	// Metodos
	void iniciarMundo(float width, float height);

	void moverObxectos(float tempoTranscurrido);
	void renderizarEscena();
	void eventoTeclado(int tecla, int accion);
	void reescalarVenta(GLFWwindow* window, int width, int height);
	void establecerCamara();
	void moverCamara(int tipoMovemento);

private:
	void xerarSkyBox(float alturaMundo, float* limites, std::string rutaTexturas[]);
	void xerarSuelo(float alturaMundo, float* limites, std::string rutaTextura);
	void xerarElementosDecorativos(std::map<int, int> elementosDecorativos);
	void xerarInimigos(int nivelMundo);

	void establecerLucesShader(GLuint shader);

	void renderizarSkyBox();
};