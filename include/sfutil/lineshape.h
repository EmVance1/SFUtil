#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

class LineShape : public sf::Drawable, public sf::Transformable {
private:
    std::vector<sf::Vertex> m_data;
    sf::Color m_color;
    size_t m_begin = 0;
    size_t m_end = 0;

public:
    explicit LineShape(size_t vertexCount = 0);
    explicit LineShape(const std::vector<sf::Vector2f>& points);
    explicit LineShape(const std::vector<sf::Vertex>& vertices);
    explicit LineShape(std::vector<sf::Vertex>&& vertices);

    [[nodiscard]] sf::Color getColor() const;
    void setColor(const sf::Color& color);

    [[nodiscard]] size_t getStart() const;
    void setStart(size_t start);

    [[nodiscard]] size_t getCount() const;
    void setCount(size_t count);

    [[nodiscard]] size_t getSize() const;

    void append(const sf::Vertex& vertex);
    void resize(size_t vertexCount);
    void clear();

    [[nodiscard]] sf::Vertex& operator[](size_t index);
    [[nodiscard]] const sf::Vertex& operator[](size_t index) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}
