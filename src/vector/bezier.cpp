#include "vector/bezier.h"


#define EPSILON 0.00001f

namespace sf { using Vector2d = Vector2<double>; }

namespace sfu {

struct LinearFunc {
    float m = 0;
    float q = 0;
    float posx = 0;
    bool vert = false;

    LinearFunc() = default;
    LinearFunc(float _m, float _q, float _posx, bool _vert)
        : m(_m), q(_q), posx(_posx), vert(_vert)
    {}
    LinearFunc(sf::Vector2f vec) {
        if (std::abs(vec.x) < EPSILON) {
            vert = true;
        } else {
            m = vec.y / vec.x;
            q = vec.y - m * vec.x;
        }
    }
    LinearFunc(sf::Vector2f begin, sf::Vector2f end) {
        if (std::abs(end.x - begin.x) < EPSILON) {
            posx = end.x;
            vert = true;
        } else {
            m = (end.y - begin.y) / (end.x - begin.x);
            q = begin.y - m * begin.x;
        }
    }

    sf::Vector2f intersect(LinearFunc other) const {
        if (vert && other.vert) {
            return {};
        }
        if (vert) {
            return sf::Vector2f(posx, other.m * posx + other.q);
        }
        if (other.vert) {
            return sf::Vector2f(other.posx, m * other.posx + q);
        }

        float x = (q - other.q) / (other.m - m);
        return sf::Vector2f(x, m * x + q);
    }

    float operator()(float x) const {
        return m * x + q;
    }
};


sf::Vector2f perpendicular(const sf::Vector2f& vec) {
    return sf::Vector2f(vec.y, -vec.x);
}

LinearFunc perpendicular(LinearFunc func) {
    if (func.vert) {
        return {};
    }

    return LinearFunc{
        1 / func.m,
        func.q,
        0.f, false
    };
}



sf::Vector2f CubicBezier::getPoint(double t) const {
    const sf::Vector2d p0 = (1.0 - t) * (1.0 - t) * (1.0 - t) * (sf::Vector2d)a;
    const sf::Vector2d p1 = (1.0 - t) * (1.0 - t) * t * 3 * (sf::Vector2d)c0;
    const sf::Vector2d p2 = (1.0 - t) * t * t * 3 * (sf::Vector2d)c1;
    const sf::Vector2d p3 = t * t * t * (sf::Vector2d)b;

    return sf::Vector2f(p0 + p1 + p2 + p3);
}

sf::Vector2f CubicBezier::derivative(double t) const {
    const sf::Vector2d p0 = (1.0 - t) * (1.0 - t) * 3 * sf::Vector2d(c0 - a);
    const sf::Vector2d p1 = (1.0 - t) * t * 6 * sf::Vector2d(c1 - c0);
    const sf::Vector2d p2 = t * t * 3 * sf::Vector2d(b - c1);

    return sf::Vector2f(p0 + p1 + p2);
}

sf::Vector2f CubicBezier::doubleDerivative(double t) const {
    const sf::Vector2d p0 = (1.0 - t) * 6 * sf::Vector2d(c0 - a);
    const sf::Vector2d p1 = (1.0 - t) * t * 6 * sf::Vector2d(c1 - c0);
    const sf::Vector2d p2 = t * t * 3 * sf::Vector2d(b - c1);

    return sf::Vector2f(p0 + p1 + p2);
}

double CubicBezier::distSquared(double t, const sf::Vector2f& q) const {
    return (getPoint(t) - q).lengthSquared();
}

}

