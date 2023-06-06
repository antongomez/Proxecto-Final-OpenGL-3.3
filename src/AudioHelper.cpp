#include "encabezados/AudioHelper.hpp"
#include "encabezados/definicions.h"

static AudioHelper* ah = nullptr;

AudioHelper::AudioHelper() {
	this->soundEngine = irrklang::createIrrKlangDevice();
	// Cragamos as melodias dos mundos
	rutasMelodiasMundos.push_back("recursos/audio/musica-fondo.ogg");
	rutasMelodiasMundos.push_back("recursos/audio/game-music-loop-3.ogg");
	rutasMelodiasMundos.push_back("recursos/audio/lifelike.ogg");
	rutasMelodiasMundos.push_back("recursos/audio/game-music-loop-4.ogg");
	rutasMelodiasMundos.push_back("recursos/audio/game-music-loop-5.ogg");
	for (int i = 0; i < rutasMelodiasMundos.size();i++) {
		melodiasMundos.push_back(soundEngine->play2D(rutasMelodiasMundos[i].c_str(), true, true));
	}

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
		melodiasMundos[i]->setVolume(0.4f);
	}
	
	melodiasMundos[i]->setIsPaused(false);
}

void AudioHelper::pausarMelodiaMundo(int i) {
	melodiasMundos[i]->setIsPaused(true);
}
