#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <deque>
#include "Conductor.h"
#include "Note.h"

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
float notesontrack = 4; //how many notes displayed at a time per track
float totalhitoffset = 10;  //largest hit offset to consider when notes are hit

std::deque<Note> notesshown;     //queue to hold notes
std::vector<double> notes;        //track of notes
std::vector<Note> track;  //track 

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
	//testing loading notes
	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			notes.push_back(1);
		}
		else {
			notes.push_back(0);
		}
	}
	std::cout << "con setup" << std::endl;
}


void Conductor::conStart(float time) {
		//calculated number of seconds in each beat
	secPerBeat = 60 / bmp;
		//time that music started
	dspSongTime = time;
		//start song
	music.play();
}

void Conductor::conUpdate(float time) {
		//get position in song- (current time- time song starts)
		songPosition = time - dspSongTime - firstBeatOffset;
		songPositionBeats = songPosition / secPerBeat;
		float notetoshow = songPositionBeats + notesontrack;
		//check if notes are left to display and note is within bounds
		//std::cout << notetoshow << std::endl;
		//std::cout << notes[index] << std::endl;
		if (index < notes.size()){ //&& notes[index] < notetoshow) {
			//initialize the note
			Note note;
			std::cout << "init" << std::endl;
			note.noteInitialize();
			index++;
			//add note to queue  (notes shown queue)
			notesshown.push_back(note);
			//initialize func of note 
		}
		//check what notes are on screen
		if (notesshown.size() > 0) {
			Note currnote = notesshown.front();
			//update all the notes
			for (int i = 0; i < notesshown.size(); i++) {
				notesshown.at(i).noteUpdate();
			}
			if (currnote.posy >= currnote.endy + totalhitoffset) {
				notesshown.pop_front();
				std::cout << "note missed" << std::endl;
			}
		}
		
}
		

