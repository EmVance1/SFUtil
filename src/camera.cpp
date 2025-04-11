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

void Camera::update(float dt) {
    switch (m_mode) {
    case ControlMode::Static:
        break;
    case ControlMode::TrackLock:
        setCenter(m_trackpos);
        break;
    case ControlMode::TrackBehind:
        move((m_trackpos - getCenter()) * m_trackingdelay * dt * 60.f);
        break;
    case ControlMode::TrackAhead:
        if (m_lastpos == m_trackpos) {
            move((m_trackpos - getCenter()) * m_trackingdelay * dt * 60.f);
        } else {
            const auto seek_to = m_trackpos + (m_trackpos - m_lastpos);
            move((seek_to - getCenter()) * m_trackingdelay * dt * 60.f);
        }
        break;
    case ControlMode::FollowCurve:
        break;
    }
}

}

