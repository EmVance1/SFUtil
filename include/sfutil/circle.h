#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

template<typename T>
struct Circle {
    sf::Vector2<T> position;
    T radius;

    bool contains(const sf::Vector2<T>& point) const {
        return (point - position).lengthSquared() <= radius * radius;
    }

    bool intersects(const Circle& other) const {
        return (other.position - position).lengthSquared() <= (radius + other.radius) * (radius + other.radius);
    }

    bool intersects(const sf::Rect<T>& other) const {
        const auto a = other.position;
        const auto b = other.position + sf::Vector2<T>(other.size.x, 0);
        const auto c = other.position + other.size;
        const auto d = other.position + sf::Vector2<T>(0, other.size.y);
        return sf::Rect<T>({other.position.x - radius, other.position.y}, {other.size.x + 2 * radius, other.size.y}).contains(position) ||
               sf::Rect<T>({other.position.x, other.position.y - radius}, {other.size.x, other.size.y + 2 * radius}).contains(position) ||
               (contains(a) || contains(b) || contains(c) || contains(d));
    }

};

using FloatCircle = Circle<float>;
using IntCircle = Circle<int32_t>;

}

