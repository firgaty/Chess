//
// Created by firgaty on 3/8/17.
//

#ifndef CHESS_DRAWBOARD_HPP
#define CHESS_DRAWBOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class DrawBoard : public sf::Drawable, public sf::Transformable {

public:
    bool load(const std::string& texture, sf::Vector2u tileSize, unsigned int width = 8, unsigned int height = 8);


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_texture;

};


#endif //CHESS_DRAWBOARD_HPP
