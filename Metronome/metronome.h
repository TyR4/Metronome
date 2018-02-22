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
	void outputBPM(int);
	void countIn(int);
	void playNumberOfBeats(int beats, int bpm);

};
