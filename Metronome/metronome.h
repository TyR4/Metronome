#pragma once

class Metronome
{
public:
	//Metronome() {};
	//~Metronome() {};

	void run();
	void warmupOpenCloseOpen();

private:

	void makeSound(int);
	void outputBPM(int);
	void countIn(int);

};
