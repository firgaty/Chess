//
// Created by firgaty on 06/03/17.
//

#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>


class Board : public sf::Drawable, public sf::Transformable {

public:
    bool load(const std::string& texture, sf::Vector2u tileSize, unsigned int width, unsigned int height);


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_texture;

};



#endif //CHESS_BOARD_HPP
