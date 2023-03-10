#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "conductor.h"

class note {
public:
	float starty;    //where note spawns
	float endy;      //point where note needs to be hit
	float removey;   //where note despawns (not hit)
	float beat;      //position of note in song
	float track;     //which track the note will be

	void noteInitialize(){
		
	}

	//based on song position provided by conductor
	void noteUpdate() {

	}
};