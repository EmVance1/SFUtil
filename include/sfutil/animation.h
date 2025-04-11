#pragma once
#include <SFML/Graphics.hpp>
#include "atlas.h"


namespace sfu {

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
private:
    sf::Vertex m_vertices[4];
    TextureAtlas m_atlas;
    sf::Vector2u m_index;
    sf::IntRect m_textureRect;

    float m_frametime = 0.25f;
    float m_time = 0.f;
    bool m_playing = true;

    void updateFrame();

public:
    explicit AnimatedSprite(const sf::Texture& texture, const sf::Vector2u& dimensions);

    void setAnimation(const sf::Texture& texture, const sf::Vector2u& dimensions);
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

    void setHorizontalShear(float factor) {
        for (int i = 0; i < 4; i++) {
            m_vertices[i].position = sf::Vector2f(
                    m_vertices[i].position.x + m_vertices[i].position.y * factor,
                    m_vertices[i].position.y
                );
        }
    }
    void setVerticalShear(float factor) {
        for (int i = 0; i < 4; i++) {
            m_vertices[i].position = sf::Vector2f(
                    m_vertices[i].position.x,
                    m_vertices[i].position.x * factor + m_vertices[i].position.y
                );
        }
    }

    // sf::FloatRect getLocalBounds() const;
    // sf::FloatRect getGlobalBounds() const;

    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

