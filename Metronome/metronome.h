#pragma once
#include <mutex>

class Metronome
{
public:
	Metronome();
	//~Metronome() {};

	void run();
	void warmupOpenCloseOpen();

	void setBPM(int);
	int getCurrentBPM() const;

private:

	int bpm;
	std::mutex bpmMutex;

	void userInputHandler();
	void processInput(int);
	void makeSound() const;
	void displayBPM() const;
	void countIn() const;
	void playNumberOfBeats(int beats) const;

};
