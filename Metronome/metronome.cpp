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


void initialTest() {
	int bpm;

	cout << "Enter speed: ";
	cin >> bpm;

	int mili = (60 * 1000) / bpm;
	int soundLength = 100;
	printf("Pausing for %d miliseconds\n", mili);

	for (int i = 0; i < 5; ++i) {
		sleep_for(milliseconds(mili - soundLength));
		Beep(880, soundLength);
	}
}
