/*
 * AudioManager.h
 *
 *  Created on: Nov 1, 2012
 *      Author: jcontemp
 */

#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include "soundbank.h"

class AudioManager {
public:
	AudioManager();
	virtual ~AudioManager();

	void initialize();
	void playSound(int soundRef);
	void playMusic(int musicRef);
	void pauseMusic();
};

extern AudioManager audioManager;

#endif /* AUDIOMANAGER_H_ */
