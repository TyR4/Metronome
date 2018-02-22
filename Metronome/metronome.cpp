#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include "metronome.h"

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono;
//using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

void Metronome::run(int bpm) {
	outputBPM(bpm);
	while(1)
		makeSound(bpm);
}

void Metronome::warmupOpenCloseOpen() {
	int start = 60, end = 200;

	countIn(start);

	for (int i = start; i <= end; i += 10) {
		outputBPM(i);
		playNumberOfBeats(4, i);
	}

	for (int i = end; i >= start; i -= 10) {
		outputBPM(i);
		playNumberOfBeats(4, i);
	}
}

/**********************************
 *
 *		PRIVATE FUNCTIONS
 *
 **********************************/

void Metronome::makeSound(int bpm) {
	int mili = (60 * 1000) / bpm;
	int soundLength = 100;

	Beep(880, soundLength);
	sleep_for(milliseconds(mili - soundLength));
}

void Metronome::outputBPM(int bpm) {
	cout << bpm << endl;
}

void Metronome::countIn(int bpm) {
	int beats = bpm < 120 ? 4 : 8; // one bar or two bar count in
	playNumberOfBeats(beats, bpm);
}

// this is purely a utility function, to be used when one or two bars are needed
void Metronome::playNumberOfBeats(int beats, int bpm) {
	for (int j = 0; j < beats; ++j)
		makeSound(bpm);
}
