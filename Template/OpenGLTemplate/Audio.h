#pragma once
#include <windows.h>									// Header File For The Windows Library
#include "./include/fmod/fmod.hpp"
#include "./include/fmod/fmod_errors.h"
#include "include/glm/glm.hpp"


class CAudio
{
public:
	CAudio();
	~CAudio();
	bool Initialise();
	bool LoadEventSound(char *filename);
	bool PlayEventSound();
	bool LoadMusicStream(char *filename);
	bool PlayMusicStream();
	void Update();
	void SetCameraPositionInfo(glm::vec3 lP, glm::vec3 lV, glm::vec3 uV, glm::vec3 vV);

private:
		

	void FmodErrorCheck(FMOD_RESULT result);

	FMOD_RESULT result;
	FMOD::System* m_pFmodSystem;	// the global variable for talking to FMOD
	FMOD::Sound *m_pEventSound;

	
	FMOD::Sound *m_pMusic;
	FMOD::Channel* m_pMusicChannel;

	boolean m_initialised;
	FMOD_VECTOR listenerPosition, listenerVelocity, upVector, viewVector;
};
