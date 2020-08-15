#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    const int N = 30;
    const int M = 20;

    const std::size_t size = 16;

    sf::RenderWindow window(sf::VideoMode(size * N, size * M), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;

    float color[3] = { 0.f, 0.f, 0.f };

    // let's use char array as buffer, see next part
    // for instructions on using std::string with ImGui
    char windowTitle[255] = "ImGui + SFML = <3";

    sf::Texture texture_1, texture_2, texture_3, texture_4;

    texture_1.loadFromFile("textures/white.png");
    texture_2.loadFromFile("textures/red.png");
    texture_3.loadFromFile("textures/green.png");
    texture_4.loadFromFile("textures/black.png");


    sf::Sprite sprite_1(texture_1);
    sf::Sprite sprite_2(texture_2);
    sf::Sprite sprite_3(texture_3);
    sf::Sprite sprite_4(texture_4);

    window.setTitle(windowTitle);
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample window"); // begin window

                                       // Background color edit
        if (ImGui::ColorEdit3("Background color", color)) {

            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }


        if (ImGui::InputText("Window title", windowTitle, 255)) {

            window.setTitle(windowTitle);
        }
        ImGui::End(); // end window

        window.clear(bgColor); // fill background with color

        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < M; ++j) {
                sprite_1.setPosition(
                    static_cast <float> (i * size),
                    static_cast <float> (j * size));

                window.draw(sprite_1);
            }
        }

        sprite_4.setPosition(0.f, 0.f);
        window.draw(sprite_4);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}