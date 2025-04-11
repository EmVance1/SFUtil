#include "particle/system.h"
#include "SFML/Graphics/Rect.hpp"
#include <chrono>


namespace sfu { namespace ps {

ParticleSystem::ParticleSystem(const Behaviour& type, size_t init_size)
    : m_type(type), m_rng(std::chrono::system_clock::now().time_since_epoch().count())
{
    spawn(init_size);
}

void ParticleSystem::reset() {
    m_rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    m_quads.clear();
}


void ParticleSystem::setTexture(const sf::Texture& texture) {
    p_texture = &texture;
    m_texrect = sf::IntRect({0, 0}, (sf::Vector2i)texture.getSize());
    for (size_t i = 0; i < m_quads.quad_count(); i++) {
        m_quads[i].setTextureRect(m_texrect);
    }
}

void ParticleSystem::setTexture(const sf::Texture& texture, const sf::IntRect& rect) {
    p_texture = &texture;
    m_texrect = rect;
    for (size_t i = 0; i < m_quads.quad_count(); i++) {
        m_quads[i].setTextureRect(m_texrect);
    }
}


void ParticleSystem::spawn(size_t n) {
    switch (getBehaviourType()) {
    case BehaviourType::Fountain:
        getBehaviour<Fountain>().spawn(m_quads, m_directions, m_lifetimes, m_rng, m_texrect, n);
        break;
    case BehaviourType::Snow:
        getBehaviour<Snow>().spawn(m_quads, m_directions, m_lifetimes, m_rng, m_texrect, n);
        break;
    }
}


void ParticleSystem::update(float dt) {
    switch (getBehaviourType()) {
    case BehaviourType::Fountain:
        getBehaviour<Fountain>().update(m_quads, m_directions, m_lifetimes, m_rng, dt);
        getBehaviour<Fountain>().cull(m_quads, m_directions, m_lifetimes, m_cullbounds, m_cullstrat);
        break;
    case BehaviourType::Snow: {
        getBehaviour<Snow>().update(m_quads, m_directions, m_lifetimes, m_rng, dt);
        getBehaviour<Snow>().cull(m_quads, m_directions, m_lifetimes, m_cullbounds, m_cullstrat);
        break; }
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.combine(getTransform());
    states.texture = p_texture;
    target.draw(m_quads, states);
}

} }

