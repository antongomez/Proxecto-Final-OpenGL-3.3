#include "encabezados/AudioHelper.hpp"
#include "encabezados/definicions.h"

static AudioHelper* ah = nullptr;

AudioHelper::AudioHelper() {
	this->soundEngine = irrklang::createIrrKlangDevice();
	this->melodiaInicial = nullptr;
	this->melodiaMundos = nullptr;
}

AudioHelper* AudioHelper::GetInstance() {
	if (ah == nullptr) {
		ah = new AudioHelper();
	}

	return ah;
}

void AudioHelper::DeleteInstance() {
	ah->soundEngine->drop();
}

void AudioHelper::reproducirSon(std::string rutaAudio) {
	soundEngine->play2D(rutaAudio.c_str());
}



void AudioHelper::reproducirMelodiaInicial() {
	melodiaInicial = soundEngine->play2D(MELODIA_INICIAL, true, false, true);
}

void AudioHelper::pausarMelodiaInicial() {
	melodiaInicial->setIsPaused(true);
}



void AudioHelper::reproducirMelodiaMundos() {
	melodiaMundos = soundEngine->play2D(MELODIA_MUNDOS, true, false, true);
}

void AudioHelper::pausarMelodiaMundos() {
	melodiaMundos->setIsPaused(true);
}

void AudioHelper::continuarMelodiaMundos() {
	melodiaMundos->setIsPaused(false);
}
