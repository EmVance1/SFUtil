#include "atlas.h"


namespace sfu {

TextureAtlas::TextureAtlas(const sf::Texture& texture, const sf::Vector2u& dimensions)
    : m_texture(&texture), m_dimensions(dimensions), m_cellsize(texture.getSize().componentWiseDiv(dimensions))
{}


void TextureAtlas::setTexture(const sf::Texture& texture, const sf::Vector2u& dimensions) {
    m_texture = &texture;
    m_dimensions = dimensions;
    m_cellsize = texture.getSize().componentWiseDiv(dimensions);
}

const sf::Texture& TextureAtlas::getTexture() const {
    return *m_texture;
}

const sf::Vector2u& TextureAtlas::getDimensions() const {
    return m_dimensions;
}

const sf::Vector2u& TextureAtlas::getCellSize() const {
    return m_cellsize;
}


sf::Sprite TextureAtlas::getInstance(const sf::Vector2u& indices) const {
    return sf::Sprite(*m_texture, getTextureRect(indices));
}

sf::IntRect TextureAtlas::getTextureRect(const sf::Vector2u& indices) const {
    return sf::IntRect((sf::Vector2i)m_cellsize.componentWiseMul(indices), (sf::Vector2i)m_cellsize);
}

}

