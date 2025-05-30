#pragma once
#include <SFML/Graphics.hpp>
#include "atlas.h"


namespace sfu {

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
private:
    sf::Vertex m_vertices[4];
    const TextureAtlas* m_atlas;
    sf::Vector2u m_index;
    sf::IntRect m_textureRect;

    float m_frametime = 0.25f;
    float m_time = 0.f;
    bool m_playing = true;

    void updateFrame();

public:
    explicit AnimatedSprite(const TextureAtlas& atlas);

    void setAnimation(const TextureAtlas& atlas);
    void setColor(const sf::Color& color);
    void setIsPlaying(bool playing);
    void setFramerate(float framerate);
    void setRow(uint32_t row);
    void setFrame(uint32_t frame);

    const sf::Texture& getTexture() const;
    const sf::Color& getColor() const;
    bool getIsPlaying() const;
    float getFramerate() const;
    uint32_t getRow() const;
    uint32_t getFrame() const;

    sf::Vector2f getSize() const;
    sf::Vector2u getDimensions() const;

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

