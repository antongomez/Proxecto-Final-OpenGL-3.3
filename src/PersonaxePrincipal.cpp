#include "encabezados/PersonaxePrincipal.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include <glad.h>

PersonaxePrincipal::PersonaxePrincipal(glm::vec3 posicion, glm::vec3 escalado, float angulo,
	unsigned int shaderProgram, int tipoFigura) : 
	Obxecto(posicion, escalado, angulo, shaderProgram){
	this->fg = new Figura(FIGURA_CARGADA, shaderProgram, "recursos/modelos/Chieftain_tanque.obj");
	this->angulo = angulo;
	this->moverse = false;
}

void PersonaxePrincipal::moverPersonaxe(double tempoTranscurrido) {
	if (moverse) {
		// Calculamos a direccion de desprazamento (normalizada)
		glm::vec3 direccion = glm::vec3(sin(angulo), 0, cos(angulo));
		// Calculamos o desprazamento en funcion do tempo que transcurriu dende a ultima vez que o movimos
		float desprazamento = (float)tempoTranscurrido * VELOCIDADE_BASE_PERSONAXE;

		// Actualizamos a posicion do enemigo
		posicion += desprazamento * direccion;
	}
}

void PersonaxePrincipal::calcularMatrizModelo() {
	matrizModelo = glm::mat4(); // Matriz identidade
	matrizModelo = glm::translate(matrizModelo, posicion);
	matrizModelo = glm::rotate(matrizModelo, angulo, glm::vec3(0, 1, 0));
	matrizModelo = glm::scale(matrizModelo, escalado);
}
