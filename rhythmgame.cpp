#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Conductor.h"

using namespace sf;

int main() {
    VideoMode vm(1920, 1080);
    //create window   /RenderWindow window(vm, "Basictemplate", Style::Fullscreen);
    RenderWindow window(vm, "Basictemplate");
    
    // define a texture - holds graphics on GPU
    Texture textureBg;
    // load graphic on texture
    if (textureBg.loadFromFile("assets/graphics/forest.jpg")) {
        //error
    }
    // create background sprite
    Sprite spriteBg;
    // attach texture to sprite
    spriteBg.setTexture(textureBg);
    // set spriteBg to cover screen
    spriteBg.setPosition(0, 0);

    // create 4 squares
    Texture notepadtex;
    notepadtex.loadFromFile("assets/graphics/square.png");
    Sprite notepads[4];
    int xposnotepad = 120;
    int yposnotepad = 100;
    for (int i = 0; i < 4; i++) {
        notepads[i].setTexture(notepadtex);
        notepads[i].setPosition(xposnotepad, yposnotepad);
        xposnotepad = xposnotepad + 180;
    }
 
    // create moving sprites
    //notes initialization
    bool notesactive = false;
    Texture notetex;
    notetex.loadFromFile("assets/graphics/square.png");
    Sprite notes[4];
    for (int i = 0; i < 4; i++) {
        notes[i].setTexture(notetex);
        notes[i].setPosition(50, 20);
    }
    

    float speed = 0;
    Clock clock;


    // declare and initialise score
    int score = 1;

    // reset game score
    score = 0;

    // record if game is active or paused
    bool paused = true;

    Font font;
    font.loadFromFile("assets/fonts/ATTFShinGoProRegular.ttf");
    // declare score text object
    Text scoreText;
    // set font for rendered text
    scoreText.setFont(font);
    // define initial string for text object
    scoreText.setString("Score = 0");
    // set size for rendered text
    scoreText.setCharacterSize(55);
    // set color for rendered text
    scoreText.setFillColor(Color::White);

    Text msgText;
    msgText.setFont(font);
    msgText.setString("Press ENTER to start...");
    msgText.setCharacterSize(55);
    msgText.setFillColor(Color::White);

    FloatRect textRect = msgText.getLocalBounds();
    msgText.setOrigin(textRect.left +
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
    msgText.setPosition(1920 / 2.0f, 1080 / 2.0f);

   
    //input intitialization
    bool acceptInput = false;
    bool songstarted = false;

    Conductor conductor;

    while (window.isOpen())
    {
        // start the game - check for Return keypress
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            // update game active state
            paused = false;
            acceptInput = true;

        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            // if event is key relased by user & game active
            if (event.type == Event::KeyReleased && !paused) {
                // update user input again
                acceptInput = true;
                if (event.key.code == Keyboard::Up) {
                    
                }
            }
        
        }

        window.clear();

        if (paused) {
           window.draw(msgText);
        }

        if (!paused) {
            // measure delta time - time between two updates
            Time dt = clock.restart();

            scoreText.setPosition(20, 20);
            //for updating score
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());


            // handle player input - up arrow key
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                acceptInput = false;
            }


            // set up the moving notes
            if (!notesactive) {
                speed = (rand() % 200) + 200;
                float height = 1080;
                int notexpos = 120;
                for (int i = 0; i < 4; i++) {
                    notes[i].setPosition(notexpos, height);
                    notexpos = notexpos + 180;
                }
                notesactive = true;
            }
            else {
                //value of dt.asSeconds() will be a fraction of 1
                //represents time previous frame of animation took to complete
                //calculation ensures rate of animation is same regardless of potential differences in underlying system performance
                for (int i = 0; i < 4; i++) {
                    notes[i].setPosition(notes[i].getPosition().x, notes[i].getPosition().y - speed * (dt.asSeconds()));
                    // check if notes have reached top
                    if (notes[i].getPosition().y < -100) {
                        // reset notes ready for next frame
                        notesactive = false;
                    }
                }
            }

            if (!songstarted) {
                conductor.conSetup();      //would take a data file with song info
                //clock.getElapsedTime().asMilliseconds()
                conductor.conStart();         //starting the conductor class
                songstarted = true;
            }
            //conductor.conUpdate(1);            //update conductor class
        
            window.draw(spriteBg);
            for (int i = 0; i < 4; i++) {
                window.draw(notepads[i]);
            }
            for (int i = 0; i < 4; i++) {
                window.draw(notes[i]);
            }
            window.draw(scoreText);

        }
        window.display();


    }


    return 0;
}