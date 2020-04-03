#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <ctgmath>

#include "ResourceHolder.h"
#include "WidgetManager.h"
#include "Widget.h"
#include "wwtbam_core/Question.h"
#include "ResourceHolder.h"

using namespace sf;

namespace wwtbam {
    const int WIDTH = 1024;
    const int HEIGHT = 768;


}

int main() {
    sf::RenderWindow window(sf::VideoMode(wwtbam::WIDTH, wwtbam::HEIGHT), "WWTBAM", sf::Style::Close | sf::Style::Titlebar);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Loading textures and fonts

    ResourceHolder::Instance().loadTexture("../resources/img/background.png", "background");
    ResourceHolder::Instance().loadTexture("../resources/img/long_slots.png", "long_slots", IntRect(0, 0, wwtbam::WIDTH, 64));
    ResourceHolder::Instance().loadFont("../resources/fonts/COOP_GEC.TTF", "Cooperplate");

    //Loading sprites

    sf::Sprite background(ResourceHolder::Instance().getTexture("background"));
    background.setColor(sf::Color(255, 255, 255, 128)); //TODO: check this changes brightness

    sf::Sprite long_slot(ResourceHolder::Instance().getTexture("long_slots"));

    //Creating start screen

    WidgetManager manager = WidgetManager();
    manager.add(*(new Widget("start_button", long_slot, sf::Text("Play", ResourceHolder::Instance().getFont("Cooperplate"), 30), Vector2f(0, window.getSize().y / 2))));
    manager.add(*(new Widget("settings_button", long_slot, sf::Text("Settings", ResourceHolder::Instance().getFont("Cooperplate"), 30), Vector2f(0, 600))));

    std::string a[4] = {"London", "Manchester", "Sheffield", "Liverpool"};
    wwtbam::Question q_test("What is the capital of Great Britain?", a, 0);

    //Window logic

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (manager.get("start_button").isClicked(window)) {
                manager.clear();
            }
        }

        window.draw(background);
        manager.draw(window);
        window.display();
    }

    return 0;
}
