#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

struct CubicBezier {
    sf::Vector2f a;
    sf::Vector2f b;
    sf::Vector2f c0;
    sf::Vector2f c1;

    sf::Vector2f getPoint(double t) const;
    sf::Vector2f derivative(double t) const;
    sf::Vector2f doubleDerivative(double t) const;
    bool contains(const sf::Vector2f& point) const;
    double distSquared(double t, const sf::Vector2f& p) const;
};

}

