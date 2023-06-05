#include "encabezados/AudioHelper.hpp"

static AudioHelper* ah = nullptr;

AudioHelper::AudioHelper() {
	this->soundEngine = irrklang::createIrrKlangDevice();

	
}

AudioHelper* AudioHelper::GetInstance() {
	if(ah == nullptr) {
		ah = new AudioHelper();
	}

	return ah;
}

void AudioHelper::DeleteInstance() {
	ah->soundEngine->drop();
}

void AudioHelper::reproducir2D(std::string rutaAudio, bool repetir) {
	soundEngine->play2D(rutaAudio.c_str(), repetir);
}