#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int main() {
    VideoMode vm(960, 540);
    //create window   /RenderWindow window(vm, "Basictemplate", Style::Fullscreen);
    RenderWindow window(vm, "Basictemplate");
    
    // define a texture - holds graphics on GPU
    Texture textureBg;
    // load graphic on texture
    if (textureBg.loadFromFile(".../assets/graphic/bg.png")) {
        //error
    }
    // create sprite
    Sprite spriteBg;
    // attach texture to sprite
    spriteBg.setTexture(textureBg);
    // set spriteBg to cover screen
    spriteBg.setPosition(0, 0);

    // create non-animated sprite object
    Texture textureBlock;
    //textureBlock.loadFromFile("C:\\Development\\rhythmgame\\assets\\graphics\\sprite.png");
    textureBlock.loadFromFile("sprite.png");
    Sprite vertBlock;
    vertBlock.setTexture(textureBlock);
    vertBlock.setPosition(100, 560);


    sf::Music music;
    if (!music.openFromFile("music.wav"))
        return -1; // error
    music.play();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }


        window.clear();
        window.draw(spriteBg);
        window.draw(vertBlock);
        window.display();
    }


    return 0;
}