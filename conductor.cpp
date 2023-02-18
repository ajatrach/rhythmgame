#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>


class conductor {
public:
	//song information- we give this
	float bmp;         //determined by song 
	std::vector<float> notes;     //data structure to keep beat position of notes
	int index;                   //traverses the notes structure


	float secPerBeat;        //duration of song beat in seconds
	float offset;            //acccounts for offset at beginning of mp3
	float songPosition;      //song position in sec  music.getPlayingOffset().asSeconds(); could also be tried
	float songPositionBeats; //song position in beats
	float dspSongTime;       //time that song starts
	float firstBeatOffset;   //in case there is silence before first beat
	sf::Music music;      //the song
	sf::Clock clock;     // clock

	void start() {
		//load audio source
		if (!music.openFromFile("music.wav"))
			std::cout << "ERROR" <<std::endl; // error
		//calculated number of seconds in each beat
		secPerBeat = 60 / bmp;
		//time that music started
		dspSongTime = clock.getElapsedTime().asMilliseconds(); 
			//start song
		music.play();
	}
	void update() {
		//get position in song- (current time- time song starts)
		songPosition = clock.getElapsedTime().asMilliseconds() - dspSongTime - firstBeatOffset;
		if (index < notes.size() && notes[index] < songPositionBeats + 1) {//(beats shown in advance
			//initialize the note
			index++;
		}
		songPositionBeats = songPosition / secPerBeat;
	}
		

};

