#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Conductor.h"

using namespace sf;

//song information- we give this
float bmp;				 //determined by song 
int index;               //traverses the notes structure
int finishline;          //perfect end position of note
float secPerBeat;        //duration of song beat in seconds
float offset;            //acccounts for offset at beginning of mp3
float songPosition;      //song position in sec  music.getPlayingOffset().asSeconds(); could also be tried
float songPositionBeats; //song position in beats
float dspSongTime;       //time that song starts
float firstBeatOffset;   //in case there is silence before first beat

std::vector<float> notes;     //data structure to keep beat position of notes

Music music; //the song

void Conductor::conSetup() {    //would take a data file with song info
	bmp = 100;
	index = 0;
	finishline = 0;
	secPerBeat = 10;
	offset = 0;
	songPosition = 0;
	songPositionBeats = 0;
	dspSongTime = 0;
	firstBeatOffset = 0;
	//load audio source
	if (!music.openFromFile("assets/music/music.wav")) {
		std::cout << "ERROR" << std::endl; // error
	}
	std::cout << "success" << std::endl;
}


void Conductor::conStart(float time) {
		//calculated number of seconds in each beat
	secPerBeat = 60 / bmp;
		//time that music started
	dspSongTime = time;
		//start song
	music.play();
	std::cout << "success" << std::endl;

}

void Conductor::conUpdate(float time) {
		//get position in song- (current time- time song starts)
		songPosition = time - dspSongTime - firstBeatOffset;
		if (index < notes.size() && notes[index] < songPositionBeats + 1) {//(beats shown in advance
			//initialize the note
			index++;
			//add note to queue
			//initialize func of note 
		}
		songPositionBeats = songPosition / secPerBeat;
}
		

