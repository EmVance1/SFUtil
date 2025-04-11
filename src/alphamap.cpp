#include "alphamap.h"


namespace sfu {

AlphaMap::AlphaMap(const AlphaMap& other) : m_bits(other.m_bits), m_size(other.m_size) {}

AlphaMap::AlphaMap(AlphaMap&& other) : m_bits(std::move(other.m_bits)), m_size(other.m_size) {}

AlphaMap::AlphaMap(const sf::Vector2u& size) : m_size(size) {
    for (uint32_t y = 0; y < size.y; y++) {
        auto& row = m_bits.emplace_back();
        row.resize(size.x / 8 + 1, 0);
    }
}

AlphaMap::AlphaMap(const sf::Image& img) {
    loadFromImage(img);
}


AlphaMap& AlphaMap::operator=(const AlphaMap& other) {
    m_bits = other.m_bits;
    m_size = other.m_size;
    return *this;
}

AlphaMap& AlphaMap::operator=(AlphaMap&& other) {
    m_bits = std::move(other.m_bits);
    m_size = other.m_size;
    return *this;
}


void AlphaMap::loadFromImage(const sf::Image& img) {
    m_bits.clear();
    for (uint32_t y = 0; y < img.getSize().y; y++) {
        auto& row = m_bits.emplace_back();
        row.resize(img.getSize().x / 8 + 1, 0);
        for (uint32_t x = 0; x < img.getSize().x; x++) {
            setPixel({x, y}, img.getPixel({x, y}).a != 0);
        }
    }
    m_size = img.getSize();
}


void AlphaMap::setPixel(const sf::Vector2u& coords, bool set_high) {
    auto& byte = m_bits[coords.y][coords.x / 8];
    const auto mask = 1 << (7 - (coords.x % 8));
    const auto val = (bool)(byte & mask);
    if (set_high) {
        byte |= mask;
    } else if (val) {
        byte ^= mask;
    }
}

bool AlphaMap::getPixel(const sf::Vector2u& coords) const {
    const auto byte = m_bits[coords.y][coords.x / 8];
    const auto mask = 1 << (7 - (coords.x % 8));
    return (bool)(byte & mask);
}


const sf::Vector2u AlphaMap::getSize() const {
    return m_size;
}

}

