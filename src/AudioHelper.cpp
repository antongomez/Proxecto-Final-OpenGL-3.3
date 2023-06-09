#include "encabezados/AudioHelper.hpp"
#include "encabezados/definicions.h"

static AudioHelper* ah = nullptr;

AudioHelper::AudioHelper() {
	this->soundEngine = irrklang::createIrrKlangDevice();
	// Cragamos as melodias dos mundos
	rutasMelodiasMundos.push_back(MUSICA_MUNDO_0);
	rutasMelodiasMundos.push_back(MUSICA_MUNDO_1);
	rutasMelodiasMundos.push_back(MUSICA_MUNDO_2);
	rutasMelodiasMundos.push_back(MUSICA_MUNDO_3);
	rutasMelodiasMundos.push_back(MUSICA_MUNDO_4);
	for (int i = 0; i < rutasMelodiasMundos.size();i++) {
		melodiasMundos.push_back(soundEngine->play2D(rutasMelodiasMundos[i].c_str(), true, true));
	}

	melodiaVictoria = soundEngine->play2D(MUSICA_VICTORIA, true, true);
	melodiaDerrota = soundEngine->play2D(MUSICA_DERROTA, true, true);

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

void AudioHelper::reproducirSon(std::string rutaAudio, float volume) {
	irrklang::ISound* sound = soundEngine->play2D(rutaAudio.c_str(), false, true);
	sound->setVolume(volume);
	sound->setIsPaused(false);
}

void AudioHelper::reproducirMelodiaMundo(int i) {
	melodiasMundos[i]->setPlayPosition(0);
	if (i == 0) {
		melodiasMundos[i]->setVolume(0.75f);
	}
	else {
		melodiasMundos[i]->setVolume(0.6f);
	}

	melodiasMundos[i]->setIsPaused(false);
}

void AudioHelper::pausarMelodiaMundo(int i) {
	melodiasMundos[i]->setIsPaused(true);
}

void AudioHelper::reproducirMelodiaVictoria() {
	melodiaVictoria->setPlayPosition(0);
	melodiaVictoria->setVolume(0.75f);
	melodiaVictoria->setIsPaused(false);
}

void AudioHelper::pausarMelodiaVictoria() {
	melodiaVictoria->setIsPaused(true);
}

void AudioHelper::reproducirMelodiaDerrota() {
	melodiaDerrota->setPlayPosition(0);
	melodiaDerrota->setVolume(0.35f);
	melodiaDerrota->setIsPaused(false);
}

void AudioHelper::pausarMelodiaDerrota() {
	melodiaDerrota->setIsPaused(true);
}
