#include <SFML/Graphics.hpp>


namespace sfu {

class PostFx : public sf::RenderTexture {
private:
    std::vector<sf::Shader> m_shaders;

public:
    const std::vector<sf::Shader>& getShaders() const { return m_shaders; }
    std::vector<sf::Shader>& getShaders() { return m_shaders; }

    sf::Shader& addShader() {
        return m_shaders.emplace_back();
    }

    sf::Shader& loadShader(const std::string& filename) {
        return m_shaders.emplace_back(std::string_view(filename), sf::Shader::Type::Fragment);
    }

    void postFxDisplay() {
        const auto view = getView();
        setView(getDefaultView());
        for (const auto& shader : m_shaders) {
            display();
            auto tex = sf::Texture(getTexture());
            const auto buff = sf::Sprite(tex);
            clear();
            draw(buff, &shader);
        }
        display();
        setView(view);
    }
};

}

