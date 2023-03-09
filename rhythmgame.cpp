#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

using namespace sf;
//player position
enum class side { LEFT, RIGHT, NONE };

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
    Texture textureBlock;
    textureBlock.loadFromFile("assets/graphics/square.png");
    Sprite vertBlock;
    vertBlock.setTexture(textureBlock);
    vertBlock.setPosition(100, 100);

    Sprite vertBlock2;
    vertBlock2.setTexture(textureBlock);
    vertBlock2.setPosition(250, 100);

    Sprite vertBlock3;
    vertBlock3.setTexture(textureBlock);
    vertBlock3.setPosition(400, 100);

    Sprite vertBlock4;
    vertBlock4.setTexture(textureBlock);
    vertBlock4.setPosition(550, 100);

    // create sprite for animate object
    Sprite key;
    key.setTexture(textureBlock);
    key.setPosition(50, 20);

    float speed = 0;
    Clock clock;

    // status bar for time
    RectangleShape statusBar;
    float barStartWidth = 400;
    float barHeight = 80;
    statusBar.setSize(Vector2f(barStartWidth, barHeight));
    statusBar.setFillColor(Color::Blue);
    statusBar.setPosition((1920 / 2) - barStartWidth / 2, 20);

    // manage game timer
    Time totalTime;
    float timeRemaining = 20.0f;
    float barWidthPerSec = barStartWidth / timeRemaining;

    // declare and initialise score
    int score = 1;

    // reset timer and game score
    score = 0;
    timeRemaining = 20;

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

    sf::Music music;
    if (!music.openFromFile("assets/music/music.wav"))
        return -1; // error
    music.play();

    //ball initialization
    bool keysactive = false;

    //input intitialization
    bool acceptInput = false;


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
            // subtract from time remaining
            timeRemaining -= dt.asSeconds();
            // size the status bar relative to timer
            statusBar.setSize(Vector2f(barWidthPerSec * timeRemaining, barHeight));

            // check when timer ends
            if (timeRemaining <= 0.0f) {
                // pause the game
                paused = true;
                // update message shown to player
                msgText.setString("That's enough time...");
                // reposition msgText bounding box relative to new text
                FloatRect textRect = msgText.getLocalBounds();
                msgText.setOrigin(textRect.left +
                    textRect.width / 2.0f,
                    textRect.top +
                    textRect.height / 2.0f);
                msgText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            scoreText.setPosition(20, 20);
            //for updating score
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());


            // handle player input - up arrow key
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                acceptInput = false;
            }
            // check game window boundary - right edge
                // - x value includes width of sprite obj
            //if (spritePlayer.getPosition().x > 2020) {
                // reset player posn to left edge of game window
                // start sprite obj outside of window boundary to avoid sprite jumping
                // - i.e. sprite smoothly scrolls onto window instead of
                // automatically resetting to start of visible window
            //    spritePlayer.setPosition(-40, spritePlayer.getPosition().y);
           // }
            // check game window boundary - left edge
           // if (spritePlayer.getPosition().x < 0) {
                // reset player posn to right edge of game window
            //    spritePlayer.setPosition(40, spritePlayer.getPosition().y);
          //  }


            // set up the keys
            if (!keysactive) {
                // how fast is the ball
                speed = (rand() % 200) + 200;
                // how high is the ball
                float height = 1080;
                key.setPosition(100, height);
                keysactive = true;
            }
            else {
                //value of dt.asSeconds() will be a fraction of 1
                //represents time previous frame of animation took to complete
                //calculation ensures rate of animation is same regardless of potential differences in underlying system performance
                key.setPosition(key.getPosition().x, key.getPosition().y- speed *(dt.asSeconds()));
                // check if ball has reached left window edge
                if (key.getPosition().y < -100) {
                    // reset ball ready for next frame
                    keysactive = false;
                }
            }

        
            window.draw(spriteBg);
            window.draw(vertBlock);
            window.draw(vertBlock);
            window.draw(vertBlock2);
            window.draw(vertBlock3);
            window.draw(vertBlock4);
            window.draw(key);
            window.draw(scoreText);
            // draw status bar
            window.draw(statusBar);


        }
        window.display();


    }


    return 0;
}