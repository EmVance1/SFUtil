#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "bezier.h"


namespace sfu {

struct Spline {
    std::vector<CubicBezier> segments;

    bool loadFromMemory(const sf::Vector2f* data, size_t count) {
        if (count < 4 || count % 2 != 0) { return false; }

        segments.push_back(CubicBezier{ data[0], data[3], data[1], data[2] });
        for (size_t i = 4; i < count; i += 2) {
            addSegment(data[i], data[i + 1]);
        }

        return true;
    }

    void addSegment(const sf::Vector2f& newcontrol, const sf::Vector2f& newpoint) {
        if (!segments.empty()) {
            const auto p = segments.back().b;
            const auto c = segments.back().c1;
            const auto newc0 = p + (p - c);
            segments.push_back(CubicBezier{ p, newpoint, newc0, newcontrol });
        }
    }
};

}

