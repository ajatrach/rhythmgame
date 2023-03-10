#pragma once
#include <vector>
#include <deque>
#include "Note.h"

using namespace sf;
class Conductor {
public:
	float bmp;               //determined by song 
	int index;               //traverses the notes structure
	int finishline;          //perfect end position of note
	float secPerBeat;        //duration of song beat in seconds
	float offset;            //acccounts for offset at beginning of mp3
	float songPosition;      //song position in sec  music.getPlayingOffset().asSeconds(); could also be tried
	float songPositionBeats; //song position in beats
	float dspSongTime;       //time that song starts
	float firstBeatOffset;   //in case there is silence before first beat
	void conStart(float time);
	void conUpdate(float time);
	void conSetup();
	std::deque<Note> notesshown;     //queue to hold notes
	std::vector<double> notes;        //track of notes
	std::vector<Note> track;  //track 
};