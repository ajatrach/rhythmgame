#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Note.h"
#include "Conductor.h"




float starty=1080;    //where note spawns
float endy;      //point where note needs to be hit
float killy=0;   //where note despawns (not hit)
float beat;      //position of note in song
float track;     //which track the note will be
float posy;      //current y position
Texture notetex;
Sprite notesprite;


void Note::noteInitialize(){
	//set init position and spawn
	notetex.loadFromFile("assets/graphics/note.png");
	notesprite.setTexture(notetex);
	notesprite.setPosition(700, 120);
	//window.draw(notesprite);
	std::cout << "initialized" << std::endl;
	
}

//based on song position provided by conductor
void Note::noteUpdate() {
	//std::cout << "updated" << std::endl;
	notesprite.setPosition(notesprite.getPosition().x, notesprite.getPosition().y+100);
	if (notesprite.getPosition().y > killy) {
		//die 
	}
}
