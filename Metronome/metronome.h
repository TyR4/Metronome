#pragma once

class Metronome
{
public:
	//Metronome() {};
	//~Metronome() {};

	void run(int bpm);
	void warmupOpenCloseOpen();

private:

	void makeSound(int);
	void displayBPM(int);
	void countIn(int);
	void playNumberOfBeats(int beats, int bpm);

};
