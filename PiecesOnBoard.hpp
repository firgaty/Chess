//
// Created by firgaty on 07/03/17.
//

#ifndef CHESS_PIECESONBOARD_HPP
#define CHESS_PIECESONBOARD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class PiecesOnBoard : public sf::Drawable, public sf::Transformable {

public:
    bool load(const std::string& texture, sf::Vector2u tileSize, int* tiles, unsigned int width, unsigned int height);


private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_texture;

};


#endif //CHESS_PIECESONBOARD_HPP
