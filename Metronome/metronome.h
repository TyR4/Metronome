#pragma once
#include <mutex>
#include <string>

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
	void processInput(int, std::string&, int*);
	void setBPMFromBuffer(std::string);
	void makeSound() const;
	void displayBPM() const;
	void countIn() const;
	void playNumberOfBeats(int beats) const;

};
