#pragma once 

#include "PantallaInicial.hpp"
#include "Suelo.hpp"
#include "SkyBox.hpp"
#include "Enemigo.hpp"
#include "PersonaxePrincipal.hpp"
#include "Camara.hpp"
#include "Luz.hpp"

#include <vector>
#include <map>
#include <glm/glm.hpp>

class Mundo : public PantallaInicial
{
public:
	// Atributos
	std::vector<Obxecto*> obxectosDecorativos;
	std::vector<Enemigo*> inimigos;
	int nivelMundo;
	SkyBox* skyBox;
	int inimigosRestantes;
	bool pitidos[4];

	double tempoRestanteEmpezar;
	double tempoInicioMundo;

	// Construtores
	Mundo(PersonaxePrincipal* personaxe, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramMiniMapa,
		float alturaMundo, float* limites,
		std::map<int, int> elementosDecorativos,
		int nivelMundo, std::map<int, std::vector<Luz*>> luces,
		std::string rutaTexturasSkyBox[],
		std::string rutaTexturaSuelo, std::string rutaTexturaMuro);

	// Metodos
	void iniciar(float width, float height) override;
	void moverObxectos(float tempoTranscurrido) override;
	void renderizarEscena(float tempoTranscurrido) override;
	void eventoTeclado(GLFWwindow* window, int tecla, int accion) override;
	bool mundoCompletado() override;
	void finalizarMundo() override;

	void colisionsBalas();
	void colisionsTanqueInimigo();
	void ataqueProducido();

	void recolocarInimigos();

	void establecerCamara();
	void moverCamara(int tipoMovemento);

private:
	void xerarSkyBox(float alturaMundo, float* limites, std::string rutaTexturas[]);
	void xerarSuelo(float alturaMundo, float* limites, std::string rutaTextura, std::string rutaTexturaMuro);
	void xerarElementosDecorativos(std::map<int, int> elementosDecorativos);
	void xerarInimigos(int nivelMundo);

	void renderizarMiniMapa();
	void emitirPitidos(double tempoRestante);
};