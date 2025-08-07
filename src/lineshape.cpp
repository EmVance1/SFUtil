#include "lineshape.h"


namespace sfu {

LineShape::LineShape(size_t vertexCount)
    : m_end(m_data.size())
{
    m_data.resize(vertexCount);
}

LineShape::LineShape(const std::vector<sf::Vector2f>& points)
    : m_end(points.size())
{
    m_data.resize(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        m_data[points.size() - i - 1].position = points[i];
    }
}

LineShape::LineShape(const std::vector<sf::Vertex>& vertices)
    : m_data(vertices), m_end(m_data.size())
{}

LineShape::LineShape(std::vector<sf::Vertex>&& vertices)
    : m_data(std::move(vertices)), m_end(m_data.size())
{}


[[nodiscard]] sf::Color LineShape::getColor() const {
    return m_color;
}

void LineShape::setColor(const sf::Color& color) {
    m_color = color;
    for (auto& v : m_data) { v.color = color; }
}


[[nodiscard]] size_t LineShape::getStart() const {
    return m_begin;
}

void LineShape::setStart(size_t start) {
    m_begin = start;
}


[[nodiscard]] size_t LineShape::getCount() const {
    return m_end - m_begin;
}

void LineShape::setCount(size_t count) {
    m_end = m_begin + count;
}


[[nodiscard]] size_t LineShape::getSize() const {
    return m_data.size();
}


void LineShape::append(const sf::Vertex& vertex) {
    m_data.push_back(vertex);
    m_data.back().color = m_color;
}

void LineShape::resize(size_t vertexCount) {
    m_data.resize(vertexCount);
    setColor(m_color);
}

void LineShape::clear() {
    m_data.clear();
    m_begin = 0;
    m_end = 0;
}


[[nodiscard]] sf::Vertex& LineShape::operator[](size_t index) {
    return m_data[index];
}

[[nodiscard]] const sf::Vertex& LineShape::operator[](size_t index) const {
    return m_data[index];
}


void LineShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const auto count = std::min((int32_t)m_data.size() - (int32_t)m_begin, (int32_t)getCount());
    if (count <= 0) { return; }
    states.transform *= getTransform();
    target.draw(m_data.data() + m_begin, count, sf::PrimitiveType::LineStrip, states);
}

}
