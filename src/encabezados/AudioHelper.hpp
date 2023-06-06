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


private:

	// --------------- Atributos ------------------- //
	irrklang::ISoundEngine* soundEngine;
	std::vector<irrklang::ISound*> melodiasMundos;
	std::vector<std::string> rutasMelodiasMundos;


	// -------------- Construtores ----------------- //
	AudioHelper();

};