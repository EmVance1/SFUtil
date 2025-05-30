#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

template<typename T>
struct RotatedRect;

template<typename T>
struct Circle {
    sf::Vector2<T> position;
    T radius = (T)0;

    Circle() = default;
    Circle(sf::Vector2<T> _position, T _radius) : position(_position), radius(_radius) {}

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

    bool intersects(const RotatedRect<T>& other) const {
        return other.intersects(*this);
    }
};

using FloatCircle = Circle<float>;
using IntCircle = Circle<int32_t>;


template<typename T>
struct RotatedRect {
    sf::Vector2<T> position;
    sf::Vector2<T> size;
    sf::Angle angle = sf::degrees(0);

    RotatedRect() = default;
    RotatedRect(sf::Vector2<T> _position, sf::Vector2<T> _size) : position(_position), size(_size) {}
    RotatedRect(sf::Vector2<T> _position, sf::Vector2<T> _size, sf::Angle _angle) : position(_position), size(_size), angle(_angle) {}
    explicit RotatedRect(sf::FloatRect other) : position(other.position), size(other.size) {}

    bool contains(const sf::Vector2<T>& point) const {
        const auto center_of_mass = position + size * 0.5f;
        const auto rotated = sf::Transform().rotate(-angle, center_of_mass).transformPoint(point);
        return sf::Rect<T>(position, size).contains(rotated);
    }

    bool intersects(const Circle<T>& other) const {
        const auto center_of_mass = position + size * 0.5f;
        const auto rotated = sf::Transform().rotate(-angle, center_of_mass).transformPoint(other.position);
        return Circle<T>(rotated, other.radius).intersects(sf::Rect<T>(position, size));
    }

    bool intersects(const RotatedRect<T>& other) const {
        {
            const auto inv = sf::Rect<T>(position, size);
            const auto center_of_mass = position + size * 0.5f;
            const auto a = sf::Transform().rotate(angle, center_of_mass).transformPoint(position);
            const auto b = sf::Transform().rotate(angle, center_of_mass).transformPoint(position + sf::Vector2f(size.y, 0.f));
            const auto c = sf::Transform().rotate(angle, center_of_mass).transformPoint(position + size);
            const auto d = sf::Transform().rotate(angle, center_of_mass).transformPoint(position + sf::Vector2f(0.f, size.x));
            if (other.contains(a) || other.contains(b) || other.contains(c) || other.contains(d)) { return true; }
        }
        {
            const auto inv = sf::Rect<T>(other.position, other.size);
            const auto center_of_mass = other.position + other.size * 0.5f;
            const auto a = sf::Transform().rotate(other.angle, center_of_mass).transformPoint(other.position);
            const auto b = sf::Transform().rotate(other.angle, center_of_mass).transformPoint(other.position + sf::Vector2f(other.size.y, 0.f));
            const auto c = sf::Transform().rotate(other.angle, center_of_mass).transformPoint(other.position + other.size);
            const auto d = sf::Transform().rotate(other.angle, center_of_mass).transformPoint(other.position + sf::Vector2f(0.f, other.size.x));
            if (contains(a) || contains(b) || contains(c) || contains(d)) { return true; }
        }
        return false;
    }

    bool intersects(const sf::Rect<T>& other) {
        return intersects(RotatedFloatRect<T>(other));
    }
};

using RotatedFloatRect = RotatedRect<float>;
using RotatedIntCircle = RotatedRect<int32_t>;

}

