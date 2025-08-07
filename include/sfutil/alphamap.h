#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


namespace sfu {

class AlphaMap {
private:
    std::vector<std::vector<uint8_t>> m_bits;
    sf::Vector2u m_size;

public:
    AlphaMap() = default;
    AlphaMap(const AlphaMap& other);
    AlphaMap(AlphaMap&& other);
    explicit AlphaMap(const sf::Vector2u& size);
    explicit AlphaMap(const sf::Image& img);

    AlphaMap& operator=(const AlphaMap& other);
    AlphaMap& operator=(AlphaMap&& other);

    void loadFromImage(const sf::Image& img);

    void setPixel(const sf::Vector2u& coords, bool set_high);
    bool getPixel(const sf::Vector2u& coords) const;

    const sf::Vector2u getSize() const;
};

}
