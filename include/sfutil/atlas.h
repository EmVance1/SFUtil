#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

class TextureAtlas {
private:
    sf::Texture m_texture;
    sf::Vector2u m_dimensions;
    sf::Vector2u m_cellsize;

public:
    TextureAtlas() = default;
    TextureAtlas(const sf::Image& image, const sf::Vector2u& dimensions);
    TextureAtlas(const std::string& filename, const sf::Vector2u& dimensions);

    [[nodiscard]] bool loadFromImage(const sf::Image& image, const sf::Vector2u& dimensions);
    [[nodiscard]] bool loadFromFile(const std::string& filename, const sf::Vector2u& dimensions);

    void setSmooth(bool smooth);
    bool isSmooth() const;

    const sf::Texture& getTexture() const;
    const sf::Vector2u& getDimensions() const;
    const sf::Vector2u& getCellSize() const;

    sf::Sprite getInstance(const sf::Vector2u& indices) const;
    sf::IntRect getTextureRect(const sf::Vector2u& indices) const;
};

}

