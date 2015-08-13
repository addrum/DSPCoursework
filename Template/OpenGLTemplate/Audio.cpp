#include "Audio.h"

#pragma comment(lib, "lib/fmodex_vc.lib")

CAudio::CAudio()
{
	m_pFmodSystem = NULL;
	m_pEventSound = NULL;
	m_pMusic = NULL;
	m_pMusicChannel = NULL;
	m_initialised = false;
}

CAudio::~CAudio()
{}

bool CAudio::Initialise()
{
	// Create an FMOD system
	result = FMOD::System_Create(&m_pFmodSystem);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	// Initialise the system
	result = m_pFmodSystem->init(32, FMOD_INIT_NORMAL, 0);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	// Set the 3d settings of the fmod system
	result = m_pFmodSystem->set3DSettings(1.0f, 1.0f, 1.0f);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
		return false;

	m_initialised = true;

	return true;
	
}

// Load an event sound
bool CAudio::LoadEventSound(char *filename)
{
	if (!m_initialised)
		return false;

	result = m_pFmodSystem->createSound(filename, FMOD_3D, 0, &m_pEventSound);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	result = m_pEventSound->set3DMinMaxDistance(0.5f, 5000.0f);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
		return false;

	return true;
}

// Play an event sound
bool CAudio::PlayEventSound()
{
	if (!m_initialised)
		return false;

	result = m_pFmodSystem->playSound(FMOD_CHANNEL_FREE, m_pEventSound, false, &m_pEventChannel);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
		return false;

	FMOD_VECTOR channelPosition = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR channelVelocity = { 0.0f, 0.0f, 0.0f };

	result = m_pEventChannel->set3DAttributes(&channelPosition, &channelVelocity);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
		return false;

	result = m_pEventChannel->setMode(FMOD_LOOP_NORMAL);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
		return false;

	return true;
}

// Just sound below - add 3d sound, set listener position, in main game loop call function here, function tells fmod current data, listener position (camera)
// direction of listener, up vector 
// Sound source, set 3d parameters


// Load a music stream
bool CAudio::LoadMusicStream(char *filename)
{
	if (!m_initialised)
		return false;

	result = m_pFmodSystem->createStream(filename, FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &m_pMusic);
	FmodErrorCheck(result);

	if (result != FMOD_OK) 
		return false;

	return true;
}

// Play a music stream
bool CAudio::PlayMusicStream()
{
	if (!m_initialised)
		return false;

	result = m_pFmodSystem->playSound(FMOD_CHANNEL_FREE, m_pMusic, false, &m_pMusicChannel);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
		return false;

	return true;
}

// Check for error
void CAudio::FmodErrorCheck(FMOD_RESULT result)
{						
	if (result != FMOD_OK) {
		// Warning: error message commented out -- if headphones not plugged into computer in lab, error occurs
		// const char *errorString = FMOD_ErrorString(result);
		// MessageBox(NULL, errorString, "FMOD Error", MB_OK);
	}
}

bool CAudio::CreateListener(const FMOD_VECTOR* listenerPos, const FMOD_VECTOR* listenerVel, const FMOD_VECTOR* listenerFor, const FMOD_VECTOR* listenerUp)
{
	result = m_pFmodSystem->set3DListenerAttributes(0, listenerPos, listenerVel, listenerFor, listenerUp);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
		return false;

	return true;
}


// Initial attempt at setting FMOD vectors
void CAudio::SetCameraPositionInfo(glm::vec3 lP, glm::vec3 lV, glm::vec3 uV, glm::vec3 vV)
{
	listenerPosition.x = lP.x;
	listenerPosition.y = lP.y;
	listenerPosition.z = lP.z;

	listenerVelocity.x = lV.x;
	listenerVelocity.y = lV.y;
	listenerVelocity.z = lV.z;

	upVector.x = uV.x;
	upVector.y = uV.y;
	upVector.z = uV.z;

	viewVector.x = vV.x;
	viewVector.y = vV.y;
	viewVector.z = vV.z;
}

void CAudio::Update()
{
	if (!m_initialised)
		return;

	if (m_pFmodSystem) 
		m_pFmodSystem->update();
}