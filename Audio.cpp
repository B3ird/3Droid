#include "Audio.hpp"
#include <thread>
#include <iostream>

//WINDOWS
//#include <windows.h>
//#include <mmsystem.h>
//#pragma comment(lib, "winmm.lib")

using namespace std;

Audio::Audio(void) {}

Audio::~Audio(void) {}

void playAudio(string audioFileName, string audioFileExt, bool loop) {

	// LINUX
	// construct the command string
    std::string command = "canberra-gtk-play -f audio/" + audioFileName +".wav &";
    // execute the command using system()
    int result = system(command.c_str());

	/*
	string openCommand = "open \"audio\\" + audioFileName + '.' + audioFileExt + "\" type mpegvideo alias " + audioFileName;

	// Open the audio file
	mciSendString(openCommand.c_str(), NULL, 0, NULL);

	string playCommand;
	if (repeat) {
		playCommand = "play " + audioFileName + " repeat";
	}
	else {
		playCommand = "play " + audioFileName;
	}

	// Play the audio file
	mciSendString(playCommand.c_str(), NULL, 0, NULL);
	*/

	// Check if the audio is still playing
	/*char buffer[128];
	int error;
	do {
		error = mciSendString("status r2d2 mode", buffer, sizeof(buffer), NULL);
		if (error) {
			std::cout << "Error: " << error << std::endl;
			break;
		}
		Sleep(100); // Wait for 100 milliseconds
	} while (strcmp(buffer, "stopped") != 0);

	// Stop the audio
	mciSendString("stop r2d2", NULL, 0, NULL);

	// Close the audio file
	mciSendString("close r2d2", NULL, 0, NULL);
	*/
}

void stopAudio(string audioFileName) {
	/*
	// Stop the audio
	string stopCommand = "stop " + audioFileName;
	mciSendString(stopCommand.c_str(), NULL, 0, NULL);

	// Close the audio file
	string closeCommand = "close " + audioFileName;
	mciSendString(closeCommand.c_str(), NULL, 0, NULL);
	*/
}

void Audio::playThreadAudio(string audioFileName, string audioFileExt) {
	std::thread t(playAudio,audioFileName, audioFileExt, false);
	t.detach();
}

void Audio::stopThreadAudio(string audioFileName) {
	std::thread t(stopAudio, audioFileName);
	t.detach();
}

void Audio::playMusic() {
	stopAudio("music");
	playAudio("music", "mp3", true);
}

void Audio::stopMusic() {
	stopAudio("music");
}

/* Windows only */

#define C3 262
#define C3sus 278
#define D3 294
#define D3sus 312
#define E3 330
#define F3 350
#define F3sus 370
#define G3 392
#define G3sus 416
#define A3 440
#define A3sus 466
#define B3 494
#define C4 524
#define C4sus 554
#define D4 588
#define D4sus 622
#define E4 660
#define F4 698
#define F4sus 740
#define G4 784
#define G4sus 830
#define A4 880
#define A4sus 932
#define B4 988
#define C5 1046

void playBeep() {
	//Beep(A3, 1000);
}

void Audio::playThreadBeep() {
	std::thread t(playBeep);
	t.join();
}

void Audio::playBeepsMusic() {
	/*Beep(A3, 800);
	Sleep(3);
	Beep(A3, 800);
	Sleep(3);
	Beep(A3, 800);
	Sleep(10);
	Beep(F3, 300);
	Beep(C4, 272);
	Beep(A3, 800);
	Beep(F3, 300);
	Beep(C4, 272);
	Beep(A3, 1272);
	Sleep(10);
	Beep(E4, 700);
	Beep(E4, 700);
	Beep(E4, 700);
	Sleep(10);
	Beep(F4, 350);
	Beep(D4, 300);
	Beep(A3, 700);
	Beep(F3, 300);
	Beep(C4, 300);
	Beep(A3, 1272);
	Sleep(10);
	Beep(A4, 300);
	Sleep(1);
	Beep(D4, 800);
	Sleep(1);
	Beep(A4, 300);
	Beep(A4sus, 800);
	Sleep(1);
	Beep(A4, 800);
	Sleep(1);
	Beep(F4, 300);
	Beep(C5, 272);
	Beep(A4, 800);
	Beep(F4, 300);
	Beep(C5, 272);
	Beep(A4, 1272);
	Sleep(10);*/
}