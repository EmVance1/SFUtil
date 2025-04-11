#pragma once
#include <SFML/Graphics.hpp>


namespace sfu {

class ConstQuad : public sf::Drawable {
private:
    const sf::Vertex* begin;

public:
    explicit ConstQuad(const sf::Vertex* _begin) : begin(_begin) {}

    const sf::Vector2f& getPosition() const;
    sf::Vector2f getSize() const;
    sf::IntRect getTextureRect() const;
    const sf::Color& getColor() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class Quad : public sf::Drawable {
private:
    sf::Vertex* begin;

public:
    explicit Quad(sf::Vertex* _begin) : begin(_begin) {}

    void setPosition(const sf::Vector2f& pos);
    void setSize(const sf::Vector2f& size);
    void setTextureRect(const sf::IntRect& rect);
    void setColor(const sf::Color& color);

    const sf::Vector2f& getPosition() const { return ConstQuad(begin).getPosition(); }
    sf::Vector2f getSize() const { return ConstQuad(begin).getSize(); }
    sf::IntRect getTextureRect() const { return ConstQuad(begin).getTextureRect(); }
    const sf::Color& getColor() const { return ConstQuad(begin).getColor(); }

    void move(const sf::Vector2f& move);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


class QuadArray : public sf::Drawable {
private:
    std::vector<sf::Vertex> m_data;

public:
    QuadArray() = default;
    QuadArray(size_t count): m_data(count * 6) {}

    size_t quad_count() const { return m_data.size() / 6; }
    size_t vertex_count() const { return m_data.size(); }
    void resize(size_t count) { m_data.resize(count * 6); }
    void clear() { m_data.clear(); }
    void remove(size_t i) { m_data.erase(m_data.begin() + (6 * i), m_data.begin() + (6 * i) + 6); }
    void remove(const std::vector<size_t>& list);
    void swap_remove(const std::vector<size_t>& list);

    ConstQuad get(size_t i) const { return ConstQuad(&m_data[6 * i]); }
    Quad get(size_t i) { return Quad(&m_data[6 * i]); }
    ConstQuad front() const { return get(0); }
    Quad front() { return get(0); }
    ConstQuad back() const { return get(quad_count() - 1); }
    Quad back() { return get(quad_count() - 1); }

    ConstQuad operator[](size_t i) const { return get(i); }
    Quad operator[](size_t i) { return get(i); }

    void push_back(const sf::Vector2f& position, const sf::Vector2f& size);
    void push_back(const sf::Vector2f& position, const sf::Vector2f& size, const sf::IntRect& texrect);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

