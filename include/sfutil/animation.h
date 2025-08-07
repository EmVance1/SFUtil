#pragma once
#include <SFML/Graphics.hpp>
#include "atlas.h"


namespace sfu {

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
private:
    const TextureAtlas* m_atlas;
    sf::Vertex m_vertices[4];
    sf::Vector2u m_index;
    sf::IntRect m_textureRect;

    float m_frametime = 0.25f;
    float m_time = 0.f;
    bool m_playing = false;
    bool m_looping = false;

    void updateFrame();

public:
    explicit AnimatedSprite(const TextureAtlas& atlas);

    void setAnimation(const TextureAtlas& atlas);
    void setColor(const sf::Color& color);
    void setIsLooped(bool loop);
    void setIsPlaying(bool playing);
    void setFramerate(float framerate);
    void setRow(uint32_t row);
    void setFrame(uint32_t frame);

    const sfu::TextureAtlas& getAnimation() const;
    const sf::Color& getColor() const;
    bool getIsLooped() const;
    bool getIsPlaying() const;
    float getFramerate() const;
    uint32_t getRow() const;
    uint32_t getFrame() const;

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;

    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

