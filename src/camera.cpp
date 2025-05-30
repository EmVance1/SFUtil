#include "camera.h"


namespace sfu {

Camera::Camera(const sf::FloatRect& rectangle): sf::View(rectangle) {}

Camera::Camera(const sf::Vector2f& center, const sf::Vector2f& size): sf::View(center, size) {}


void Camera::setTrackingPos(const sf::Vector2f& pos) {
    m_lastpos = m_trackpos;
    m_trackpos = pos;
}

void Camera::setTrackingPos(const sf::Vector2f& pos, ControlMode mode) {
    m_mode = mode;
    setTrackingPos(pos);
}

void Camera::setTrackingOffset(float offset) {
    m_trackingdelay = 1.f / offset;
}


void Camera::setCenter(const sf::Vector2f& center, bool reset_track) {
    sf::View::setCenter(center);
    if (reset_track) {
        m_lastpos = center;
        m_trackpos = center;
    }
}

sf::FloatRect Camera::getFrustum() const {
    return sf::FloatRect(getCenter() - getSize() * 0.5f, getSize());
}


void Camera::update(float deltatime) {
    switch (m_mode) {
    case ControlMode::Static:
        break;
    case ControlMode::TrackLock:
        setCenter(m_trackpos);
        break;
    case ControlMode::TrackBehind: {
        move((m_trackpos - getCenter()) * m_trackingdelay * deltatime * 60.f);
        break; }
    case ControlMode::FollowCurve:
        break;
    }
}

}

