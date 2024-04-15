#pragma once
#include <iostream>

class Audio {
	public:

	Audio(void);
	~Audio(void);

	void playMusic();

	void stopMusic();

	void playThreadAudio(std::string audioFileName, std::string audioFileExt);

	void stopThreadAudio(std::string audioFileName);

	void playThreadBeep();

	void playBeepsMusic();
};

