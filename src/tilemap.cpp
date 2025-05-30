#include "tilemap.h"


namespace sfu {

TileMap::TileMap(const TextureAtlas& atlas)
    : m_atlas(&atlas)
{}

TileMap::TileMap(const TextureAtlas& atlas, const sf::Vector2u& dimensions)
    : m_atlas(&atlas)
{
    setDimensions(dimensions);
}


void TileMap::loadFromMemory(const sf::Vector2u& dimensions, const uint32_t* indices) {
    setDimensions(dimensions);
    for (size_t i = 0; i < m_quads.quad_count(); i++) {
        m_quads[i].setTextureRect(m_atlas->getTextureRect(sf::Vector2u(indices[i * 2], indices[i * 2 + 1])));
    }
}

void TileMap::setDimensions(const sf::Vector2u& dimensions) {
    m_dimensions = dimensions;
    m_quads.resize(dimensions.x * dimensions.y);
    for (size_t i = 0; i < m_quads.quad_count(); i++) {
        const auto index = sf::Vector2u((uint32_t)i % dimensions.x, (uint32_t)i / dimensions.x);
        const auto position = index.componentWiseMul(m_atlas->getCellSize());
        m_quads[i].setPosition(sf::Vector2f(position));
        m_quads[i].setSize(sf::Vector2f(m_atlas->getCellSize()));
    }
}

void TileMap::setTile(const sf::Vector2u& map_index, const sf::Vector2u& atlas_index) {
    m_quads[map_index.x + map_index.y * m_dimensions.x].setTextureRect(m_atlas->getTextureRect(atlas_index));
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.combine(getTransform());
    states.texture = &m_atlas->getTexture();
    target.draw(m_quads, states);
}

}

