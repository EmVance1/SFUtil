#include "quadarray.h"


namespace sfu {

const sf::Vector2f& ConstQuad::getPosition() const {
    return begin[0].position;
}

sf::Vector2f ConstQuad::getSize() const {
    return begin[5].position - begin[0].position;
}

sf::IntRect ConstQuad::getTextureRect() const {
    const auto pos = begin[0].texCoords;
    const auto size = begin[5].texCoords - pos;
    return sf::IntRect((sf::Vector2i)pos, (sf::Vector2i)size);
}

const sf::Color& ConstQuad::getColor() const {
    return begin[0].color;
}


void ConstQuad::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(begin, 6, sf::PrimitiveType::Triangles, states);
}


void Quad::setPosition(const sf::Vector2f& pos) {
    const auto size = getSize();
    begin[0].position = pos;
    begin[1].position = pos + sf::Vector2f(size.x, 0.f);
    begin[2].position = pos + sf::Vector2f(0.f, size.y);
    begin[3].position = pos + sf::Vector2f(0.f, size.y);
    begin[4].position = pos + sf::Vector2f(size.x, 0.f);
    begin[5].position = pos + size;
}

void Quad::setSize(const sf::Vector2f& size) {
    const auto pos = begin[0].position;
    begin[1].position = pos + sf::Vector2f(size.x, 0.f);
    begin[2].position = pos + sf::Vector2f(0.f, size.y);
    begin[3].position = pos + sf::Vector2f(0.f, size.y);
    begin[4].position = pos + sf::Vector2f(size.x, 0.f);
    begin[5].position = pos + size;
}

void Quad::setTextureRect(const sf::IntRect& rect) {
    begin[0].texCoords = (sf::Vector2f)rect.position;
    begin[1].texCoords = (sf::Vector2f)rect.position + sf::Vector2f((float)rect.size.x, 0.f);
    begin[2].texCoords = (sf::Vector2f)rect.position + sf::Vector2f(0.f,(float)rect.size.y);
    begin[3].texCoords = (sf::Vector2f)rect.position + sf::Vector2f(0.f,(float)rect.size.y);
    begin[4].texCoords = (sf::Vector2f)rect.position + sf::Vector2f((float)rect.size.x, 0.f);
    begin[5].texCoords = (sf::Vector2f)rect.position + sf::Vector2f(rect.size);
}

void Quad::setColor(const sf::Color& color) {
    for (size_t i = 0; i < 6; i++) {
        begin[i].color = color;
    }
}


void Quad::move(const sf::Vector2f& move) {
    setPosition(getPosition() + move);
}

void Quad::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(begin, 6, sf::PrimitiveType::Triangles, states);
}


void QuadArray::remove(const std::vector<size_t>& list) {
    const size_t end_size = quad_count() - list.size();
    if (end_size == 0) {
        clear();
        return;
    }
    size_t offset = 0;

    for (size_t i = 0; i < end_size; i++) {
        while (std::find(list.begin(), list.end(), i + offset) != list.end()) {
            offset++;
        }
        if (offset != 0) {
            for (size_t j = 0; j < 6; j++) {
                m_data[(6 * i) + j] = m_data[(6 * (i + offset)) + j];
            }
        }
    }

    resize(end_size);
}

void QuadArray::swap_remove(const std::vector<size_t>& list) {
    const size_t begin_size = quad_count();
    if (list.size() == begin_size) {
        clear();
        return;
    }
    size_t eff_size = quad_count();

    for (size_t index : list) {
        if (index < eff_size) {
            while (std::find(list.begin(), list.end(), eff_size - 1) != list.end()) {
                eff_size--;
                if (index == eff_size) {
                    goto outer_break;
                }
            }
            for (size_t j = 0; j < 6; j++) {
                m_data[(6 * index) + j] = m_data[(6 * (eff_size - 1)) + j];
            }
            eff_size--;
        }
    }

outer_break:
    resize(eff_size);
}


void QuadArray::push_back(const sf::Vector2f& position, const sf::Vector2f& size) {
    const auto last = m_data.size();
    m_data.resize(m_data.size() + 6);
    Quad(&m_data[last]).setPosition(position);
    Quad(&m_data[last]).setSize(size);
}

void QuadArray::push_back(const sf::Vector2f& position, const sf::Vector2f& size, const sf::IntRect& texrect) {
    const auto last = m_data.size();
    m_data.resize(m_data.size() + 6);
    Quad(&m_data[last]).setPosition(position);
    Quad(&m_data[last]).setSize(size);
    Quad(&m_data[last]).setTextureRect(texrect);
}

void QuadArray::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_data.data(), m_data.size(), sf::PrimitiveType::Triangles, states);
}

}

