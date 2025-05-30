#include "atlas.h"


namespace sfu {

TextureAtlas::TextureAtlas(const sf::Image& image, const sf::Vector2u& dimensions)
    : m_texture(image), m_dimensions(dimensions), m_cellsize(m_texture.getSize().componentWiseDiv(dimensions))
{}

TextureAtlas::TextureAtlas(const std::string& filename, const sf::Vector2u& dimensions)
    : m_texture(filename), m_dimensions(dimensions), m_cellsize(m_texture.getSize().componentWiseDiv(dimensions))
{}


bool TextureAtlas::loadFromImage(const sf::Image& image, const sf::Vector2u& dimensions) {
    const auto ok = m_texture.loadFromImage(image);
    m_dimensions = dimensions;
    m_cellsize = m_texture.getSize().componentWiseDiv(dimensions);
    return ok;
}

bool TextureAtlas::loadFromFile(const std::string& filename, const sf::Vector2u& dimensions) {
    const auto ok = m_texture.loadFromFile(filename);
    m_dimensions = dimensions;
    m_cellsize = m_texture.getSize().componentWiseDiv(dimensions);
    return ok;
}


void TextureAtlas::setSmooth(bool smooth) {
    m_texture.setSmooth(smooth);
}

bool TextureAtlas::isSmooth() const {
    return m_texture.isSmooth();
}


const sf::Texture& TextureAtlas::getTexture() const {
    return m_texture;
}

const sf::Vector2u& TextureAtlas::getDimensions() const {
    return m_dimensions;
}

const sf::Vector2u& TextureAtlas::getCellSize() const {
    return m_cellsize;
}


sf::Sprite TextureAtlas::getInstance(const sf::Vector2u& indices) const {
    return sf::Sprite(m_texture, getTextureRect(indices));
}

sf::IntRect TextureAtlas::getTextureRect(const sf::Vector2u& indices) const {
    return sf::IntRect((sf::Vector2i)m_cellsize.componentWiseMul(indices), (sf::Vector2i)m_cellsize);
}

}

