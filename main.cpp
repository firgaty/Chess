#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PiecesOnBoard.hpp"
#include "DrawBoard.hpp"
#include "Board.hpp"

sf::Sprite plateau() {


}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,800), "Chess");

    DrawBoard board;

    if(!board.load("images/textures/boardTiles.png", sf::Vector2u(96, 96), 8, 8))
        return -1;

    PiecesOnBoard pOBoard;

    int pieces[] =
            {
                    10,  9,  8,  7,  6,  8,  9, 10,
                    11, 11, 11, 11, 11, 11, 11, 11,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                    -1, -1, -1, -1, -1, -1, -1, -1,
                     5,  5,  5,  5,  5,  5,  5,  5,
                     4,  3,  2,  1,  0,  2,  3,  4,
            };

    Board pBoard;
    pBoard.setAt(5, 4, 3);
    pBoard.reset(1);
    /* test pieces :
     * (1,1) :  4 - Rook;
     * (3,2) :  3 - Knight;
     * (1,5) :  0 - King;
     * (5,5) :  5 - Pawn;
     * (6,4) : 11 - Black Pawn;
     * (6,3) :  1 - Queen;
     * (3,6) :  5 - Pawn;
     */
    pBoard.moves(3,2);

    if(!pOBoard.load("images/textures/pieces.png", sf::Vector2u(96, 96), pBoard.getBoard(),8, 8))
        return -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(board);
        window.draw(pOBoard);
        window.display();


/*
        // create a 500x500 render-texture
        sf::RenderTexture renderTexture;
        if (!renderTexture.create(800, 800))
        {
            // error...
        }

        sf::Texture tex_dark_wood;
        sf::Texture tex_light_wood;

        sf::Image img_dark_wood;
        sf::Image img_light_wood;

        if (!img_dark_wood.loadFromFile("images/textures/dark-wood.jpg")) {}
        if (!img_light_wood.loadFromFile("images/textures/light-wood.jpg")) {}


        // load a 32x32 rectangle that starts at (10, 10)
        if (!tex_dark_wood.loadFromImage(img_dark_wood, sf::IntRect(10, 10, 96, 96))){}
        if (!tex_light_wood.loadFromImage(img_light_wood, sf::IntRect(10, 10, 96, 96))){}

        // drawing uses the same functions


        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                sf::Sprite sprite;
                if((i+j) % 2 == 0) {
                    sprite.setTexture(tex_light_wood);
                } else {
                    sprite.setTexture(tex_dark_wood);
                }
                sprite.setPosition(sf::Vector2f(((float) i) * 96, ((float) j) * 96));
                if(!((i+j) % 2 == 0)) sprite.setRotation(90);

                renderTexture.draw(sprite);
            }
        }
        renderTexture.display();


        const sf::Texture& texture2 = renderTexture.getTexture();

        sf::Sprite sprite2(texture2);

        window.draw(sprite2);




        window.display();

        */
    }
    return 0;
}