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
	mmLoadEffect(SFX_CHOMP);
	mmLoadEffect(SFX_OUCH);
	mmLoadEffect(SFX_GAME_OVER);
	mmLoad(MOD_TECHNO_MOZART);
}

void AudioManager::playSound(int soundRef)
{
	mmEffect(soundRef);
}

void AudioManager::playMusic(int musicRef)
{
	mmStart(musicRef, MM_PLAY_LOOP);
	mmSetModuleVolume(1024);
}

void AudioManager::pauseMusic()
{
	// pause or stop kills all sound :-(
	mmSetModuleVolume(0);
}
