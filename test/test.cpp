#include <SFML/Graphics.hpp>
#include "mscmptest/asserts.h"
#include "sfutil.h"


void fountain_visual() {
    auto window = sf::RenderWindow(sf::VideoMode({800, 800}), "TEST FOUNTAIN", sf::Style::Default);
    auto postfx = sfu::PostFx();
    std::ignore = postfx.resize({800, 800});

    auto& s2 = postfx.loadShader("test/res/glitch.glsl");
    s2.setUniform("dist", 4);

    auto& s1 = postfx.loadShader("test/res/CRT.glsl");
    s1.setUniform("curvature", sf::Vector2f(3.5f, 3.5f));

    auto system = sfu::ps::ParticleSystem::make<sfu::ps::Fountain>();
    system.setCullStrategy(sfu::ps::Cull::Swap);
    system.setCullBoundary(sf::FloatRect({0.f, 0.f}, {800.f, 800.f}));

    auto& control = system.getBehaviour<sfu::ps::Fountain>();
    control.size = sf::Vector2f(20, 20);
    control.falldir = sf::Vector2f(0.f, 1.f) * 0.0f;
    control.start_speed = 4.f;
    control.randspeed_factor = 0.8f;
    control.randsize_factor = 0.4f;
    control.damp_factor = 0.9f;
    control.grow_factor = 0.8f;
    control.fade_factor = 1.f;
    // control.lifetime = 2.f;

    auto clock = sf::Clock();
    auto t = 0.f;
    while (window.isOpen()) {
        const auto dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        t += dt;
        if (t > 1.f / 60.f) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                control.source = (sf::Vector2f)sf::Mouse::getPosition(window);
                system.spawn(100);
            }
            t -= 1.f / 60.f;
            std::cout << "frames: " << 1.f / dt << ", count: " << system.getParticleCount() << "\n";
        }

        system.update(dt);

        postfx.clear();
        postfx.draw(system); //, &s2);
        postfx.display();
        // postfx.postFxDisplay();
        window.draw(sf::Sprite(postfx.getTexture()));
        window.display();
    }
}

void snow_visual() {
    auto window = sf::RenderWindow(sf::VideoMode({800, 800}), "TEST SNOW", sf::Style::Default);
    auto postfx = sfu::PostFx();
    std::ignore = postfx.resize({800, 800});

    auto& s2 = postfx.loadShader("test/res/glitch.glsl");
    s2.setUniform("dist", 2);

    auto& s1 = postfx.loadShader("test/res/CRT.glsl");
    s1.setUniform("curvature", sf::Vector2f(3.5f, 3.5f));

    auto system = sfu::ps::ParticleSystem::make<sfu::ps::Snow>();
    system.setCullStrategy(sfu::ps::Cull::Swap);
    system.setCullBoundary(sf::FloatRect({0.f, -100.f}, {800.f, 900.f}));

    auto& control = system.getBehaviour<sfu::ps::Snow>();
    control.source = sf::Vector2f(400.f, -50.f);
    control.width = 800.f;
    control.size = sf::Vector2f(5, 5);
    control.falldir = sf::Vector2f(0.f, 1.f) * 2.f;
    control.randdepth_factor = 0.4f;
    control.grow_factor = 0.6f;
    control.fade_factor = 1.f;

    auto clock = sf::Clock();
    auto t = 0.f;
    while (window.isOpen()) {
        const auto dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        t += dt;
        if (t > 1.f / 60.f) {
            system.spawn(10);
            t -= 1.f / 60.f;
        }
        // std::cout << "frames: " << 1.f / dt << ", count: " << system.getParticleCount() << "\n";

        system.update(dt);

        postfx.clear();
        postfx.draw(system);
        postfx.postFxDisplay();
        window.draw(sf::Sprite(postfx.getTexture()));
        window.display();
    }
}

void anim_visual() {
    auto window = sf::RenderWindow(sf::VideoMode({800, 800}), "TEST ANIMATION", sf::Style::Default);

    auto tex = sf::Texture("test/res/player.png");
    auto anim = sfu::AnimatedSprite(tex, {4, 5});
    anim.setFramerate(4);
    anim.setPosition({400, 400});
    anim.setScale({4, 4});

    auto clock = sf::Clock();
    while (window.isOpen()) {
        const auto dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // std::cout << "frames: " << 1.f / dt << ", count: " << system.getParticleCount() << "\n";

        anim.update(dt);

        window.clear();
        window.draw(anim);
        window.display();
    }
}


int main() {
    snow_visual();
    // fountain_visual();
    // anim_visual();
}

