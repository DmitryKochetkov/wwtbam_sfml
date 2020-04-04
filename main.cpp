#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctgmath>
#include "Group.h"
#include "ResourceHolder.h"
#include "Button.h"
#include "wwtbam_core/Question.h"
#include "wwtbam_core/LongButton.h"

//class Screen {
//private:
//    //std::vector<sf::Drawable*> screen;
//    std::vector<std::unique_ptr<sf::Drawable>> screen;
//
//public:
////    void add(sf::Drawable* drawable) {
////        screen.push_back(drawable);
////    }
//
//    void add(std::unique_ptr<sf::Drawable>& drawable) {
//        screen.push_back(drawable);
//    }
//
//    void render(sf::RenderWindow& window) {
//        for (const auto &item: screen)
//            window.draw(*item);
//    }
//};

int main() {
    sf::RenderWindow window(sf::VideoMode(wwtbam::WIDTH, wwtbam::HEIGHT), "WWTBAM", sf::Style::Close | sf::Style::Titlebar);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Loading textures and fonts
    ResourceHolder::Instance().loadTexture("../resources/img/background.png", "background");
    ResourceHolder::Instance().loadTexture("../resources/img/long_slots.png", "long_slot", sf::IntRect(0, 0, wwtbam::WIDTH, 60));
    ResourceHolder::Instance().loadTexture("../resources/img/question_and_answers.png", "question", sf::IntRect(0, 0, wwtbam::WIDTH, 106));
    ResourceHolder::Instance().loadTexture("../resources/img/question_and_answers.png", "left_answer", sf::IntRect(0, 106, wwtbam::WIDTH/2, wwtbam::Question::ANSWER_HEIGHT));
    ResourceHolder::Instance().loadTexture("../resources/img/question_and_answers.png", "right_answer", sf::IntRect(wwtbam::WIDTH/2, 106, wwtbam::WIDTH/2, wwtbam::Question::ANSWER_HEIGHT));
    ResourceHolder::Instance().loadFont("../resources/fonts/COOP_GEC.TTF", "Cooperplate");
    ResourceHolder::Instance().loadFont("../resources/fonts/ITC Conduit.ttf", "ITC Conduit");

    //Setting up background
    sf::Sprite background(ResourceHolder::Instance().getTexture("background"));

    //Testing button
    Button button(sf::Text("Show", ResourceHolder::Instance().getFont("Cooperplate"), 30), sf::Vector2f(50, 100));
    wwtbam::LongButton button2(sf::Text("Text2", ResourceHolder::Instance().getFont("Cooperplate"), 30), wwtbam::HEIGHT * 0.5f);

    //Testing question
    std::string a[4] = {"London", "Manchester", "Sheffield", "Liverpool"};
    wwtbam::Question q("What is the capital of Great Britain?", a, 0);

    //Initializing a start group
    Group menu;
    menu.push_back(background);
    menu.push_back(button);
    //menu.push_back(button2);
    menu.push_back(q);

    Group settings;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (button.isClicked(window)) {
                q.Show();
            }
        }

        window.draw(menu);
        window.display();
    }
    return 0;
}