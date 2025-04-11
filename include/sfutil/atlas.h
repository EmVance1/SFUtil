#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

class TextureAtlas {
private:
    const sf::Texture*  m_texture;
    sf::Vector2u m_dimensions;
    sf::Vector2u m_cellsize;

public:
    TextureAtlas(const sf::Texture& texture, const sf::Vector2u& dimensions);

    void setTexture(const sf::Texture& texture, const sf::Vector2u& dimensions);

    const sf::Texture& getTexture() const;
    const sf::Vector2u& getDimensions() const;
    const sf::Vector2u& getCellSize() const;

    sf::Sprite getInstance(const sf::Vector2u& indices) const;
    sf::IntRect getTextureRect(const sf::Vector2u& indices) const;
};

}

