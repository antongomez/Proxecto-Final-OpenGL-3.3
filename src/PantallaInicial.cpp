#include "encabezados/PantallaInicial.hpp"
#include "encabezados/definicions.h"

PantallaInicial::PantallaInicial(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
	float* limites, std::map<int, std::vector<Luz*>> luces,
	std::string rutaTexturaSuelo, std::string rutaTexturaMetalica) {
	this->personaxePrincipal = personaxePrincipal;
	this->shaderProgram = shaderProgram;
	this->shaderProgramTex = shaderProgramTex;
	this->shaderProgramBasico = shaderProgramBasico;
	this->luces = luces;

	xerarSuelo(limites, rutaTexturaSuelo);
}

PantallaInicial::PantallaInicial(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
	std::map<int, std::vector<Luz*>> luces) {
	this->personaxePrincipal = personaxePrincipal;
	this->shaderProgram = shaderProgram;
	this->shaderProgramTex = shaderProgramTex;
	this->shaderProgramBasico = shaderProgramBasico;
	this->luces = luces;
}

void PantallaInicial::iniciar(float width, float height) {
	this->camara = new Camara(9.0f, 0, PI / 8.0f, width, height);

	// colocamos ao personaxe principal sobre o chan no centro do mesmo
	personaxePrincipal->posicion = suelo->posicion;
	personaxePrincipal->angulo = -PI / 4.0f;

	this->camaraSecundaria = new Camara(10.0f, 0, 0, width, height);
}

bool PantallaInicial::mundoCompletado() {
	return false;
}

void PantallaInicial::xerarSuelo(float* limites, std::string rutaTexturaSuelo) {
	this->suelo = new Suelo(glm::vec3(0), ESCALA_SUELO, limites, shaderProgramTex, FIGURA_CADRADO, rutaTexturaSuelo);
}

void PantallaInicial::moverObxectos(float tempoTranscurrido) {
	this->personaxePrincipal->angulo += (PI / 4.0f) * tempoTranscurrido;
}

void PantallaInicial::establecerLucesShader(GLuint shader) {
	// Iluminacion
	auto iter = luces.find(LUZ_DIRECCIONAL);
	if (iter != luces.end()) {

		std::vector<Luz*>& vecDir = iter->second;

		// Establecemos a luz direccional
		unsigned int dirLight_direction = glGetUniformLocation(shader, "dirLight.direction");
		glUniform3fv(dirLight_direction, 1, glm::value_ptr(vecDir[0]->direccion));
		unsigned int dirLight_ambient = glGetUniformLocation(shader, "dirLight.ambient");
		glUniform3fv(dirLight_ambient, 1, glm::value_ptr(vecDir[0]->ambiente));
		unsigned int dirLight_diffuse = glGetUniformLocation(shader, "dirLight.diffuse");
		glUniform3fv(dirLight_diffuse, 1, glm::value_ptr(vecDir[0]->difusa));
		unsigned int dirLight_especular = glGetUniformLocation(shader, "dirLight.specular");
		glUniform3fv(dirLight_especular, 1, glm::value_ptr(vecDir[0]->especular));
	}

	iter = luces.find(LUZ_FOCAL);

	if (iter != luces.end()) {
		// El elemento se encontró en el mapa
		std::vector<Luz*>& vecLuzFocal = iter->second;

		// Marcamos no shader que utilizamos luz focal
		unsigned int spot = glGetUniformLocation(shader, "spot");
		glUniform1i(spot, 1);

		for (int i = 0; i < vecLuzFocal.size(); i++) {

			vecLuzFocal[i]->actualizarLuz(personaxePrincipal->posicion, personaxePrincipal->angulo);

			std::string base = "spotLights[" + std::to_string(i) + "].";

			std::string aux = base + "position";
			unsigned int spotLight_position = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_position, 1, glm::value_ptr(vecLuzFocal[i]->posicion));

			aux = base + "direction";
			unsigned int spotLight_direction = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_direction, 1, glm::value_ptr(vecLuzFocal[i]->direccion));

			aux = base + "innerCutOff";
			unsigned int spotLight_innerCutOff = glGetUniformLocation(shader, aux.c_str());
			glUniform1f(spotLight_innerCutOff, vecLuzFocal[i]->innerCutOff);

			aux = base + "outerCutOff";
			unsigned int spotLight_outerCutOff = glGetUniformLocation(shader, aux.c_str());
			glUniform1f(spotLight_outerCutOff, vecLuzFocal[i]->outerCutOff);

			aux = base + "diffuse";
			unsigned int spotLight_diffuse = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_diffuse, 1, glm::value_ptr(vecLuzFocal[i]->difusa));

			aux = base + "specular";
			unsigned int spotLight_specular = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_specular, 1, glm::value_ptr(vecLuzFocal[i]->especular));
		}

	}
	else {
		// Marcamos no shader que non utilizamos luz focal
		unsigned int spot = glGetUniformLocation(shader, "spot");
		glUniform1i(spot, 0);
	}
}

void PantallaInicial::renderizarEscena() {
	glViewport(0, 0, camara->width, camara->height);

	// Utilizamos o shader para os obxectos que non tenhen texturas
	glUseProgram(shaderProgram);

	camara->establecerCamara(personaxePrincipal);
	camara->actualizarMatrizProxeccion();
	camara->actualizarMatricesShader(shaderProgram);

	unsigned int viewPos = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3fv(viewPos, 1, glm::value_ptr(camara->posicionCamara));

	establecerLucesShader(shaderProgram);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	personaxePrincipal->renderizarObxecto();

	glUseProgram(shaderProgramTex);
	// Establecemos as matrices de view e projection no shader
	camara->actualizarMatricesShader(shaderProgram);
	// Establecemos as luces no shader
	establecerLucesShader(shaderProgramTex);

	// Variable do shader para determinar se estamos iluminando o skyBox ou non
	unsigned int loc_skyBox = glGetUniformLocation(shaderProgramTex, "skyBox");
	glUniform1i(loc_skyBox, 0);

	suelo->renderizarSuelo();
}

void PantallaInicial::eventoTeclado(int tecla, int accion) {}
void PantallaInicial::reescalarVenta(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	camara->width = (float)width;
	camara->height = (float)height;
	camara->actualizarMatrizProxeccion();
}


