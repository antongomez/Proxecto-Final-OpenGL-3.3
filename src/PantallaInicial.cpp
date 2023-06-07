#include "encabezados/PantallaInicial.hpp"
#include "encabezados/definicions.h"
#include "encabezados/AudioHelper.hpp"
#include "encabezados/TextHelper.hpp"

#include <iostream>
#include <cmath>

PantallaInicial::PantallaInicial(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
	float* limites, std::map<int, std::vector<Luz*>> luces,
	std::string rutaTexturaSuelo, std::string rutaTexturaMetalica) {
	this->personaxePrincipal = personaxePrincipal;
	this->shaderProgram = shaderProgram;
	this->shaderProgramTex = shaderProgramTex;
	this->shaderProgramBasico = shaderProgramBasico;
	this->luces = luces;
	this->musica_reproducida = false;
	this->instantes_pausa = 0;

	xerarSuelo(limites, rutaTexturaSuelo);
	this->fg = Figura::GetFigura(FIGURA_CADRADO, shaderProgramBasico, rutaTexturaMetalica);
	this->fgCentro = Figura::GetFigura(FIGURA_CADRADO, shaderProgramBasico, "recursos/texturas/textura-parte-abaixo-centro.jpg");
	this->fgEsquerda = Figura::GetFigura(FIGURA_CADRADO, shaderProgramBasico, "recursos/texturas/textura-parte-abaixo-esquerda.jpg");
	this->fgDereita = Figura::GetFigura(FIGURA_CADRADO, shaderProgramBasico, "recursos/texturas/textura-parte-abaixo-dereita.jpg");

	this->win = false;
}

PantallaInicial::PantallaInicial(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
	std::map<int, std::vector<Luz*>> luces) {
	this->personaxePrincipal = personaxePrincipal;
	this->shaderProgram = shaderProgram;
	this->shaderProgramTex = shaderProgramTex;
	this->shaderProgramBasico = shaderProgramBasico;
	this->luces = luces;
	this->musica_reproducida = false;
	this->instantes_pausa = 0;
	this->win = false;
	this->defeat = false;
}

void PantallaInicial::iniciar(float width, float height) {
	this->camara = new Camara(9.0f, 0, PI / 8.0f, width, height, MODO_CAMARA_VISTA_XERAL);

	// colocamos ao personaxe principal sobre o chan no centro do mesmo
	personaxePrincipal->posicion = suelo->posicion;
	personaxePrincipal->angulo = PI / 4.0f;

	this->camaraSecundaria = new Camara(5.0f, 0, 0, width, 250, MODO_CAMARA_VISTA_XERAL);
	this->tempoPulsoEnter = -1;
	this->mundoFinalizado = false;
	this->win = false;
	this->defeat = false;

	personaxePrincipal->vidas = 3;
}

bool PantallaInicial::mundoCompletado() {
	return mundoFinalizado;
}

void PantallaInicial::xerarSuelo(float* limites, std::string rutaTexturaSuelo) {
	this->suelo = new Suelo(glm::vec3(0), ESCALA_SUELO, limites, shaderProgramTex, FIGURA_CADRADO, rutaTexturaSuelo);
}

void PantallaInicial::moverObxectos(float tempoTranscurrido) {
	if (tempoPulsoEnter > 0) {

		double tempoTrans = glfwGetTime() - tempoPulsoEnter;

		if (tempoTrans <= SEGUNDOS_PAUSA_FIN_PANTALLA_INICIAL) {

			this->personaxePrincipal->angulo = anguloPulsoEnter + (ANGULO_PAUSA_FIN_PANTALLA_INICIAL - anguloPulsoEnter) * (tempoTrans);

		}
		else if (tempoTrans - SEGUNDOS_PAUSA_FIN_PANTALLA_INICIAL > 1) {
			this->mundoFinalizado = true;
		}
	}
	else {
		this->personaxePrincipal->sumarAngulo((PI / 4.0f) * tempoTranscurrido);
	}

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

		// Indicamos cantas luces focais utilizamos
		unsigned int nr_spot = glGetUniformLocation(shader, "nr_spot_lights");
		glUniform1i(nr_spot, vecLuzFocal.size());

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
		unsigned int nr_spot = glGetUniformLocation(shader, "nr_spot_lights");
		glUniform1i(nr_spot, 0);
	}

	iter = luces.find(LUZ_POSICIONAL);

	if (iter != luces.end()) {
		// El elemento se encontró en el mapa
		std::vector<Luz*>& vecLuzPosicionais = iter->second;

		// Indicamos cantas luces focais utilizamos
		unsigned int nr_point = glGetUniformLocation(shader, "nr_point_lights");
		glUniform1i(nr_point, vecLuzPosicionais.size());

		for (int i = 0; i < vecLuzPosicionais.size(); i++) {

			std::string base = "pointLights[" + std::to_string(i) + "].";

			std::string aux = base + "position";
			unsigned int spotLight_position = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_position, 1, glm::value_ptr(vecLuzPosicionais[i]->posicion));

			aux = base + "constant";
			unsigned int spotLight_constante = glGetUniformLocation(shader, aux.c_str());
			glUniform1f(spotLight_constante, vecLuzPosicionais[i]->constante);

			aux = base + "linear";
			unsigned int spotLight_linear = glGetUniformLocation(shader, aux.c_str());
			glUniform1f(spotLight_linear, vecLuzPosicionais[i]->linear);

			aux = base + "quadratic";
			unsigned int spotLight_cuadratico = glGetUniformLocation(shader, aux.c_str());
			glUniform1f(spotLight_cuadratico, vecLuzPosicionais[i]->cuadratico);

			aux = base + "ambient";
			unsigned int spotLight_ambient = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_ambient, 1, glm::value_ptr(vecLuzPosicionais[i]->ambiente));

			aux = base + "diffuse";
			unsigned int spotLight_diffuse = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_diffuse, 1, glm::value_ptr(vecLuzPosicionais[i]->difusa));

			aux = base + "specular";
			unsigned int spotLight_specular = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_specular, 1, glm::value_ptr(vecLuzPosicionais[i]->especular));
		}

	}
	else {
		// Marcamos no shader que non utilizamos luz focal
		unsigned int nr_point = glGetUniformLocation(shader, "nr_point_lights");
		glUniform1i(nr_point, 0);
	}
}

void PantallaInicial::renderizarEscena(float tempoTranscurrido) {

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

	// Renderizar Texto
	TextHelper* t = TextHelper::GetInstance();
	t->cambiarViewport(camara->width, camara->height);
	t->setTexto("ENDGAME");
	t->escribir(camara->width / 2.0f, 30, 7.0f, 1, 0);

	glViewport(0, 0, camaraSecundaria->width, camaraSecundaria->height);
	// Utilizamos o shader para os obxectos que non tenhen texturas
	glUseProgram(shaderProgramBasico);

	camaraSecundaria->establecerCamara(personaxePrincipal);
	camaraSecundaria->actualizarMatrizProxeccionOrtho();
	camaraSecundaria->actualizarMatricesShader(shaderProgram);



	unsigned int loc_cor = glGetUniformLocation(shaderProgramBasico, "cor");
	glUniform1i(loc_cor, 0);

	for (int i = -10; i <= 10; i += 2) {
		glm::mat4 matrizModelo = glm::mat4();
		matrizModelo = glm::translate(matrizModelo, glm::vec3(i, 0, 0));
		matrizModelo = glm::scale(matrizModelo, glm::vec3(2.0f));
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrizModelo));

		if (i == 0) {
			glBindTexture(GL_TEXTURE_2D, fgCentro->textura);
			fgCentro->renderizar();
		}
		else if (i == -2) {
			glBindTexture(GL_TEXTURE_2D, fgEsquerda->textura);
			fgEsquerda->renderizar();
		}
		else if (i == 2) {
			glBindTexture(GL_TEXTURE_2D, fgDereita->textura);
			fgDereita->renderizar();
		}
		else {
			glBindTexture(GL_TEXTURE_2D, fg->textura);
			fg->renderizar();
		}

	}

	// Renderizar Texto
	t->cambiarViewport(camaraSecundaria->width, camaraSecundaria->height);
	t->setTexto(personaxePrincipal->nomeTanqueActual());
	t->escribir(camaraSecundaria->width / 2.0f, camaraSecundaria->height / 2.0f, 3.0f, 1, 1);

	t->setTexto("Pulsa ENTER para comezar");
	t->escribir(camaraSecundaria->width / 2.0f, camaraSecundaria->height - camaraSecundaria->height / 6.0f, 1.5f, 1, 1);

}

void PantallaInicial::eventoTeclado(GLFWwindow* window, int tecla, int accion) {

	// Fechas
	if ((tecla == 262 || tecla == 263) && accion != GLFW_RELEASE) {
		AudioHelper::GetInstance()->reproducirSon(SON_CAMBIO_PERSONAXE);
		personaxePrincipal->cambiarPersonaxe(tecla == 262);
	}

	if (tecla == GLFW_MOUSE_BUTTON_LEFT && accion == GLFW_PRESS) {
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		if (
			(ypos <= (camara->height - camaraSecundaria->height / 2.0f) + 39)
			&& (ypos >= (camara->height - camaraSecundaria->height / 2.0f) - 39))
		{
			if ((xpos > camaraSecundaria->width / 2.0f + 142)
				&& (xpos <= camaraSecundaria->width / 2.0f + 198)) {
				AudioHelper::GetInstance()->reproducirSon(SON_CAMBIO_PERSONAXE);
				personaxePrincipal->cambiarPersonaxe(true);
			}
			else if ((xpos < camaraSecundaria->width / 2.0f - 142)
				&& (xpos >= camaraSecundaria->width / 2.0f - 198)) {
				AudioHelper::GetInstance()->reproducirSon(SON_CAMBIO_PERSONAXE);
				personaxePrincipal->cambiarPersonaxe(false);
			}
		}

	}
}

void PantallaInicial::reescalarVenta(GLFWwindow* window, int width, int height) {
	camara->width = (float)width;
	camara->height = (float)height;
	camaraSecundaria->width = (float)width;
}

void PantallaInicial::finalizarMundo() {
	musica_reproducida = false;
	instantes_pausa = 0;
}


