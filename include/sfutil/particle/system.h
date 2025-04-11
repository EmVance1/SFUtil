#pragma once
#include <SFML/Graphics.hpp>
#include <variant>
#include <random>
#include "fountain.h"
#include "snow.h"
#include "cullstrat.h"


namespace sfu { namespace ps {

using Behaviour = std::variant<Fountain, Snow>;

enum class BehaviourType {
    Fountain = 0,
    Snow = 1,
};


class ParticleSystem : public sf::Drawable, public sf::Transformable {
private:
    QuadArray m_quads;
    std::vector<sf::Vector2f> m_directions;
    std::vector<float> m_lifetimes;

    Behaviour m_type;
    std::mt19937 m_rng;
    Cull m_cullstrat = Cull::Standard;
    sf::FloatRect m_cullbounds;

    const sf::Texture* p_texture = nullptr;
    sf::IntRect m_texrect;

    ParticleSystem(const Behaviour& type, size_t init_size);

public:
    template<typename T>
    static ParticleSystem make(size_t init_size = 0) { return ParticleSystem(T(), init_size); }

    void reset();

    template<typename T> void setBehavoiour(bool _reset = true, size_t init_size = 0) {
        m_type = T();
        if (_reset) {
            reset();
            spawn(init_size);
        }
    }
    template<typename T> const T& getBehaviour() const { return std::get<T>(m_type); }
    template<typename T> T& getBehaviour() { return std::get<T>(m_type); }
    BehaviourType getBehaviourType() const { return (BehaviourType)m_type.index(); }

    void setNoTexture() { p_texture = nullptr; }
    void setTexture(const sf::Texture& texture);
    void setTexture(const sf::Texture& texture, const sf::IntRect& rect);

    void setCullStrategy(Cull strategy) { m_cullstrat = strategy; }
    void setCullBoundary(const sf::FloatRect& rect) { m_cullbounds = rect; }

    size_t getParticleCount() const { return m_quads.quad_count(); }

    void spawn(size_t n);
    void update(float dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

} }

