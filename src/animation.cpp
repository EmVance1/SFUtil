#include "animation.h"


namespace sfu {

void AnimatedSprite::updateFrame() {
    m_textureRect = m_atlas->getTextureRect(m_index);
    m_vertices[0].texCoords = sf::Vector2f(m_textureRect.position);
    m_vertices[1].texCoords = sf::Vector2f(m_textureRect.position) + sf::Vector2f((float)m_textureRect.size.x, 0.f);
    m_vertices[2].texCoords = sf::Vector2f(m_textureRect.position) + sf::Vector2f(0.f, (float)m_textureRect.size.y);
    m_vertices[3].texCoords = sf::Vector2f(m_textureRect.position) + sf::Vector2f(m_textureRect.size);
}


AnimatedSprite::AnimatedSprite(const TextureAtlas& atlas)
    : m_atlas(&atlas), m_index(0, 0), m_textureRect(m_atlas->getTextureRect(m_index))
{
    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f((float)m_textureRect.size.x, 0.f);
    m_vertices[2].position = sf::Vector2f(0.f, (float)m_textureRect.size.y);
    m_vertices[3].position = sf::Vector2f(m_textureRect.size);
    updateFrame();
}


void AnimatedSprite::setAnimation(const TextureAtlas& atlas) {
    m_atlas = &atlas;
    m_index = sf::Vector2u(0, 0);
    m_textureRect = m_atlas->getTextureRect(m_index);
    m_vertices[0].position = sf::Vector2f(0.f, 0.f);
    m_vertices[1].position = sf::Vector2f((float)m_textureRect.size.x, 0.f);
    m_vertices[2].position = sf::Vector2f(0.f, (float)m_textureRect.size.y);
    m_vertices[3].position = sf::Vector2f(m_textureRect.size);
    updateFrame();
}

void AnimatedSprite::setColor(const sf::Color& color) {
    for (int i = 0; i < 4; i++) {
        m_vertices[i].color = color;
    }
}

void AnimatedSprite::setIsPlaying(bool playing) {
    m_playing = playing;
}

void AnimatedSprite::setFramerate(float framerate) {
    m_frametime = 1.f / framerate;
}

void AnimatedSprite::setRow(uint32_t row) {
    m_index.y = row;
    updateFrame();
}

void AnimatedSprite::setFrame(uint32_t frame) {
    m_index.x = frame;
    updateFrame();
}


const sf::Texture& AnimatedSprite::getTexture() const {
    return m_atlas->getTexture();
}

const sf::Color& AnimatedSprite::getColor() const {
    return m_vertices[0].color;
}

bool AnimatedSprite::getIsPlaying() const {
    return m_playing;
}

float AnimatedSprite::getFramerate() const {
    return 1.f / m_frametime;
}

uint32_t AnimatedSprite::getRow() const {
    return m_index.y;
}

uint32_t AnimatedSprite::getFrame() const {
    return m_index.x;
}


sf::Vector2f AnimatedSprite::getSize() const {
    return ((sf::Vector2f)m_atlas->getCellSize()).componentWiseMul(getScale());
}

sf::Vector2u AnimatedSprite::getDimensions() const {
    return m_atlas->getDimensions();
}


sf::FloatRect AnimatedSprite::getLocalBounds() const {
    return sf::FloatRect(m_vertices[0].position, m_vertices[2].position - m_vertices[0].position);
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const {
    return getTransform().transformRect(getLocalBounds());
}


void AnimatedSprite::update(float dt) {
    if (m_playing) {
        m_time += dt;
        if (m_time >= m_frametime) {
            m_time -= m_frametime;
            m_index.x = (m_index.x + 1) % m_atlas->getDimensions().x;
            updateFrame();
        }
    }
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.combine(getTransform());
    states.texture = &getTexture();
    target.draw(m_vertices, 4, sf::PrimitiveType::TriangleStrip, states);
}

}

