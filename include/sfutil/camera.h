#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

class Camera : public sf::View {
public:
    enum class ControlMode {
        Static,
        TrackLock,
        TrackBehind,
        TrackAhead,
        FollowCurve,
    };

private:
    ControlMode m_mode = ControlMode::Static;
    sf::Vector2f m_trackpos;
    sf::Vector2f m_lastpos;
    float m_trackingdelay = 0.1f;

public:
    Camera() = default;
    explicit Camera(const sf::FloatRect& rectangle);
    Camera(const sf::Vector2f& center, const sf::Vector2f& size);

    void setTrackingMode(ControlMode mode) { m_mode = mode; }
    void setTrackingPos(const sf::Vector2f& pos);
    void setTrackingPos(const sf::Vector2f& pos, ControlMode mode);
    void setTrackingOffset(float offset);

    void update(float dt);
};

}

