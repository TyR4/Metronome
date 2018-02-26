#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include "metronome.h"

using namespace std;
using this_thread::sleep_for;     // sleep_for, sleep_until
using chrono::milliseconds;

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
	string bpmBuffer = "000";
	int bufferIdx = 0;
	while ((input = _getch()) != 27) {
		if (input == 0 || input == -32)
			input = _getch();
		processInput(input, ref(bpmBuffer), &bufferIdx);
	}
	exit(0);
}

void Metronome::processInput(int input, string & bpmBuffer, int* bufferIdx) {
	cout << "Buffer: " << bpmBuffer << endl;
	cout << "Index: " << *bufferIdx << ", buffer value: " << bpmBuffer[*bufferIdx] << endl;
	lock_guard<mutex> guard(bpmMutex);
	if (input == 32) // SPACE
		cout << "Pause" << endl;
	else if (input > 47 && input < 58) {
		bpmBuffer[(*bufferIdx)++] = (char)input;
		if (*bufferIdx >= 3) {
			*bufferIdx = 0;
			setBPMFromBuffer(bpmBuffer);
			bpmBuffer = "000";
		}
	}
	else if (input == 13) { // ENTER
		cout << "Current buffer is the new BPM: " << bpmBuffer << endl;
		setBPMFromBuffer(bpmBuffer);
	}
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

void Metronome::setBPMFromBuffer(string bpmBuffer) {
	int newBPM = stoi(bpmBuffer);
	if (newBPM < 60)
		newBPM = 60;
	else if (newBPM > 240)
		newBPM = 240;
	setBPM(newBPM);
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
