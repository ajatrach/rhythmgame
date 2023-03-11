#pragma once
using namespace sf;
class Note {
public:
	float starty;    //where note spawns
	float endy;      //point where note needs to be hit
	float killy;   //where note despawns (not hit)
	float beat;      //position of note in song
	float track;     //which track the note will be
	float posy;      //current y position
	void noteInitialize();
	void noteUpdate();
	Texture notetex;
	Sprite notesprite;
};