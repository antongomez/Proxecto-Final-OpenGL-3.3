#pragma once

#include <irrKlang/irrKlang.h>
#include <string>
#include <vector>

class AudioHelper
{
public:

	// -------------- Metodos ----------------- //
	static AudioHelper* GetInstance();
	static void DeleteInstance();
	void reproducirSon(std::string rutaAudio);
	void reproducirSon(std::string rutaAudio, float volume);

	void reproducirMelodiaMundo(int i);
	void pausarMelodiaMundo(int i);

	void reproducirMelodiaVictoria();
	void pausarMelodiaVictoria();


private:

	// --------------- Atributos ------------------- //
	irrklang::ISoundEngine* soundEngine;
	std::vector<irrklang::ISound*> melodiasMundos;
	std::vector<std::string> rutasMelodiasMundos;
	irrklang::ISound* melodiaVictoria;


	// -------------- Construtores ----------------- //
	AudioHelper();

};