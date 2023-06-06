#pragma once

#include <irrKlang/irrKlang.h>
#include <string>

class AudioHelper
{
public:

	// -------------- Metodos ----------------- //
	static AudioHelper* GetInstance();
	static void DeleteInstance();
	void reproducirSon(std::string rutaAudio);
	void reproducirMelodiaInicial();
	void reproducirMelodiaMundos();


private:

	// --------------- Atributos ------------------- //
	irrklang::ISoundEngine* soundEngine;
	irrklang::ISound* melodiaInicial;
	irrklang::ISound* melodiaMundos;


	// -------------- Construtores ----------------- //
	AudioHelper();

};