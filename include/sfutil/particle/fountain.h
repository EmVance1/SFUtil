#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "../quadarray.h"
#include "cullstrat.h"


namespace sfu { namespace ps {

struct Fountain {
    sf::Vector2f source;
    sf::Vector2f size;
    sf::Vector2f falldir;

    float start_speed = 10.f;
    float randspeed_factor = 0.f;
    float randsize_factor = 0.f;
    float grow_factor = 1.f;
    float damp_factor = 1.f;
    float fade_factor = 1.f;
    float lifetime = -1.f;

    bool spawn_center = true;

private:
    void spawn (QuadArray& quads, std::vector<sf::Vector2f>& directions, std::vector<float>& lifetimes, std::mt19937& rng, const sf::IntRect& texrect, size_t n) const;
    void update(QuadArray& quads, std::vector<sf::Vector2f>& directions, std::vector<float>& lifetimes, std::mt19937& rng, float dt) const;
    void cull  (QuadArray& quads, std::vector<sf::Vector2f>& directions, std::vector<float>& lifetimes, const sf::FloatRect& bounds, Cull cullstrat = Cull::Standard) const;

    friend class ParticleSystem;
};

} }

