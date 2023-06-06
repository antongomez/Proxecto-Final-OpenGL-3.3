#include "encabezados/PersonaxePrincipal.hpp"
#include "encabezados/definicions.h"
#include "encabezados/AudioHelper.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include <glad.h>

PersonaxePrincipal::PersonaxePrincipal(glm::vec3 posicion, glm::vec3 escalado, float angulo,
	unsigned int shaderProgram, int tipoFigura, std::vector<std::string> rutasPersonaxes, 
	std::vector<std::pair<float, float>> dimensionsTanques, std::vector<std::string> nomesTanques) :
	Obxecto(posicion, escalado, angulo, shaderProgram) {
	for (int i = 0; i < rutasPersonaxes.size(); i++) {
		this->fgPersonaxes.push_back(new Figura(FIGURA_CARGADA, shaderProgram, rutasPersonaxes[i]));
	}
	this->fg = fgPersonaxes[0];
	this->fgActual = 0;
	this->angulo = angulo;
	this->moverse = false;
	this->marcha_atras = false;
	this->xirar_dereita = false;
	this->xirar_esquerda = false;
	this->nPersonaxes = rutasPersonaxes.size();

	this->dimensionsTanques = dimensionsTanques;
	this->largo = dimensionsTanques[0].first;
	this->ancho = dimensionsTanques[0].second;

	this->nomesTanques = nomesTanques;
}

void PersonaxePrincipal::moverPersonaxe(double tempoTranscurrido) {

	if (xirar_dereita) {
		angulo -= INCREMENTO_XIRO_PERSONAXE * tempoTranscurrido;
	}
	
	if (xirar_esquerda) {
		angulo += INCREMENTO_XIRO_PERSONAXE * tempoTranscurrido;
	}

	if (moverse || marcha_atras) {
		// Calculamos a direccion de desprazamento (normalizada)
		glm::vec3 direccion = glm::vec3(sin(angulo), 0, cos(angulo));
		// Calculamos o desprazamento en funcion do tempo que transcurriu dende a ultima vez que o movimos
		float desprazamento = (float)tempoTranscurrido * VELOCIDADE_BASE_PERSONAXE;

		if (marcha_atras) {
			desprazamento *= -1;
		}

		// Actualizamos a posicion do tanque
		posicion += desprazamento * direccion;
	}


	moverBalas(tempoTranscurrido);
}

void PersonaxePrincipal::moverBalas(double tempoTranscurrido)
{
	for (const auto& bala : balas) {
		bala->moverBala(tempoTranscurrido);
	}

}

void PersonaxePrincipal::calcularMatrizModelo() {
	matrizModelo = glm::mat4(); // Matriz identidade
	matrizModelo = glm::translate(matrizModelo, posicion);
	matrizModelo = glm::rotate(matrizModelo, angulo, glm::vec3(0, 1, 0));
	matrizModelo = glm::scale(matrizModelo, escalado);
}

void PersonaxePrincipal::disparar() {
	// Calculamos a direccion da bala
	glm::vec3 direccion = glm::vec3(sin(angulo), 0, cos(angulo));

	glm::vec3 posicionBala = posicion + glm::vec3(0, 1.2, 0) + (2.8f * direccion);

	balas.push_back(new Bala(posicionBala, glm::vec3(1), 0, shaderProgram, "recursos/modelos/bala.obj", direccion));

	// Emitimos o sonido do disparo
	AudioHelper::GetInstance()->reproducirSon("recursos/audio/shotgun-firing.ogg");
}

void PersonaxePrincipal::renderizarBalas() {
	for (const auto& bala : balas) {
		bala->renderizarObxecto();
	}
}

void PersonaxePrincipal::cambiarPersonaxe(bool seguinte) {
	if (seguinte) {
		if (fgActual == (nPersonaxes - 1)) {
			fgActual = 0;
		}
		else {
			fgActual++;
		}
	}
	else {
		if (fgActual == 0) {
			fgActual = (nPersonaxes - 1);
		}
		else {
			fgActual--;
		}
	}

	fg = fgPersonaxes[fgActual];
	largo = dimensionsTanques[fgActual].first;
	ancho = dimensionsTanques[fgActual].second;
}

std::string PersonaxePrincipal::nomeTanqueActual() {
	return nomesTanques[fgActual];
}
