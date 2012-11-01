#include <nds.h>
#include "audiomanager.h"
#include <maxmod9.h>
#include "soundbank_bin.h"


AudioManager audioManager;


AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{
}


void AudioManager::initialize()
{
	mmInitDefaultMem((mm_addr)soundbank_bin);

	mmLoadEffect(SFX_DOG_BARK);
	mmLoadEffect(SFX_R2D2);
	mmLoad(MOD_TECHNO_MOZART);
}

void AudioManager::playSound(int soundRef)
{
	mmEffect(soundRef);
}

void AudioManager::playMusic(int musicRef)
{
	mmStart(musicRef, MM_PLAY_LOOP);
}

void AudioManager::pauseMusic()
{
	mmPause();
}
