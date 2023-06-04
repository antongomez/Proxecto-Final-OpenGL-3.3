#pragma once

#include <irrKlang/irrKlang.h>
#include <string>

class AudioHelper
{
public:
	

	// -------------- Construtores ----------------- //
	
	// -------------- Metodos ----------------- //
	static AudioHelper* GetInstance();
	static void DeleteInstance();
	void reproducir2D(std::string rutaAudio, bool repetir);


private:

	// --------------- Atributos ------------------- //
	irrklang::ISoundEngine* soundEngine;

	// -------------- Construtores ----------------- //
	AudioHelper();
	
};