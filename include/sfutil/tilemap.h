#pragma once
#include "atlas.h"
#include "quadarray.h"


namespace sfu {

class TileMap : public sf::Drawable, public sf::Transformable {
private:
    TextureAtlas m_atlas;
    QuadArray m_quads;
    sf::Vector2u m_dimensions;

public:
    TileMap(const TextureAtlas& atlas);
    TileMap(const TextureAtlas& atlas, const sf::Vector2u& dimensions);

    void loadFromMemory(const sf::Vector2u& dimensions, const uint32_t* indices);

    void setDimensions(const sf::Vector2u& dimensions);

    void setTile(const sf::Vector2u& map_index, const sf::Vector2u& atlas_index);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

