#include <iostream>
#include "metronome.h"

using namespace std; 

int main() {
	Metronome metronome;

	//cout << "Enter speed: ";

	//int bpm;
	//cin >> bpm;
	//while (bpm < 60) {
	//	cout << "Do not enter a tempo below 60, that's just cruel" << endl;
	//	cin >> bpm;
	//}


	//metronome.run(bpm);
	metronome.warmupOpenCloseOpen();

	return 0;
}
