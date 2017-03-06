#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

sf::Sprite plateau() {
    // create a 500x500 render-texture
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(500, 500))
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
            sprite.setPosition(sf::Vector2f(((float) i) * 96 + 1, ((float) j) * 96 + 1));
            renderTexture.draw(sprite);
        }
    }
    renderTexture.display();


    const sf::Texture& texture2 = renderTexture.getTexture();

    sf::Sprite sprite(texture2);

}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Chess");


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


        window.draw(plateau());

        window.display();
    }
    return 0;
}