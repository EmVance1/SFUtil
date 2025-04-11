#include "particle/snow.h"
#include "num_maps.h"
#include "cull.h"


#define EPSILON 0.0001f

namespace sfu { namespace ps {

void Snow::spawn(QuadArray& quads, std::vector<sf::Vector2f>& directions, std::vector<float>& lifetimes, std::mt19937& rng, const sf::IntRect& texrect, size_t n) const {
    const auto begin_index = quads.quad_count();
    quads.resize(begin_index + n);
    directions.resize(begin_index + n);
    lifetimes.resize(begin_index + n);
    for (size_t i = 0; i < n; i++) {
        const auto actual_pos = source + falldir.perpendicular().normalized() * large_to_signed_normal(rng()) * (width * 0.5f);
        const auto depth = large_to_scalar(rng(), randdepth_factor);
        const auto actual_size = size * depth;
        quads[begin_index + i].setPosition(actual_pos);
        quads[begin_index + i].setSize(actual_size);
        quads[begin_index + i].setTextureRect(texrect);
        // quads[begin_index + i].set_fill_color(sf::Color::Red);
        directions[begin_index + i] = falldir * depth;
        lifetimes[begin_index + i] = lifetime;
    }
}

void Snow::update(QuadArray& quads, std::vector<sf::Vector2f>& directions, std::vector<float>& lifetimes, std::mt19937& rng, float dt) const {
    for (size_t i = 0; i < quads.quad_count(); i++) {
        if (std::fabs(fade_factor - 1.f) > EPSILON) {
            const auto col = quads[i].getColor();
            const auto alpha = (uint8_t)((float)col.a * std::pow(bias_func(fade_factor, -4.f), dt * 60.f));
            quads[i].setColor(sf::Color(col.r, col.b, col.g, alpha));
        }
        if (std::fabs(grow_factor - 1.f) > EPSILON) {
            quads[i].setSize(quads[i].getSize() * std::pow(bias_func(grow_factor, -4.f), dt * 60.f));
        }
        quads[i].move(directions[i] * dt * 60.f);
        lifetimes[i] -= dt;
    }
}

void Snow::cull(QuadArray& quads, std::vector<sf::Vector2f>& directions, std::vector<float>& lifetimes, const sf::FloatRect& bounds, Cull strategy) const {
    auto list = std::vector<size_t>();

    for (size_t i = 0; i < quads.quad_count(); i++) {
        if (!bounds.findIntersection(sf::FloatRect(quads[i].getPosition(), quads[i].getSize())).has_value() 
                || quads[i].getSize().x < 1.f || quads[i].getColor().a < 1 || (lifetimes[i] < 0.f && lifetimes[i] > -1.f)) {
            list.push_back(i);
        }
    }

    if (strategy == Cull::Standard) {
        quads.remove(list);
        remove_many(directions, list);
        remove_many(lifetimes, list);
    } else {
        quads.swap_remove(list);
        swap_remove(directions, list);
        swap_remove(lifetimes, list);
    }
}

} }

