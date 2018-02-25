#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <conio.h>
#include <Windows.h>
#include "metronome.h"

using namespace std;
using std::this_thread::sleep_for;     // sleep_for, sleep_until
using std::chrono::milliseconds;

Metronome::Metronome() : bpm(60) {}

void Metronome::setBPM(int newBPM) {
	this->bpm = newBPM;
}

int Metronome::getCurrentBPM() const {
	return this->bpm;
}

void Metronome::run() {
	displayBPM();
	thread t(&Metronome::userInputHandler, this);
	while(1)
		makeSound();
	t.join();
}

void Metronome::warmupOpenCloseOpen() {
	int start = 60, end = 200;

	countIn();

	for (int i = start; i <= end; i += 10) {
		setBPM(i);
		displayBPM();
		playNumberOfBeats(4);
	}

	for (int i = end; i >= start; i -= 10) {
		setBPM(i);
		displayBPM();
		playNumberOfBeats(4);
	}
}

/**********************************
 *
 *		PRIVATE FUNCTIONS
 *
 **********************************/

void Metronome::userInputHandler() {
	char input;
	while ((input = _getch()) != 27) {
		if (input == 0 || input == -32)
			input = _getch();
		processInput(input);
	}
	exit(0);
}

void Metronome::processInput(int input) {
	lock_guard<mutex> guard(bpmMutex);
	int inputBuffer[3];
	if (input == 32) // SPACE
		cout << "Pause" << endl;
	else if (input > 47 && input < 58)
		cout << "Entering a new BPM, add to buffer\n";
	else if (input == 13) // ENTER
		cout << "Current buffer is the new BPM: " << *inputBuffer << endl;
	else if (input == 72) { // UP Arrow 
		if (getCurrentBPM() < 240) {
			setBPM(getCurrentBPM() + 1);
			displayBPM();
		}
	}
	else if (input == 80) { // DOWN Arrow
		if (getCurrentBPM() > 60) {
			setBPM(getCurrentBPM() - 1);
			displayBPM();
		}
	}
	else if (input == 75) {// LEFT Arrow
		if (getCurrentBPM() > 60) {
			setBPM(getCurrentBPM() - 10);
			displayBPM();
		}
	}
	else if (input == 77) { // RIGHT Arrow
		if (getCurrentBPM() < 240) {
			setBPM(getCurrentBPM() + 10);
			displayBPM();
		}
	}
	else
		cout << "Invalid Character" << endl;
}

void Metronome::makeSound() const {
	int mili = (60 * 1000) / getCurrentBPM();
	int soundLength = 100;

	Beep(880, soundLength);
	sleep_for(milliseconds(mili - soundLength));
}

void Metronome::displayBPM() const {
	cout << getCurrentBPM() << endl;
}

void Metronome::countIn()  const{
	int bpm = getCurrentBPM();
	int beats = bpm < 120 ? 4 : 8; // one bar or two bar count in
	playNumberOfBeats(beats);
}

// this is purely a utility function, to be used when one or two bars are needed
void Metronome::playNumberOfBeats(int beats) const {
	for (int j = 0; j < beats; ++j)
		makeSound();
}
