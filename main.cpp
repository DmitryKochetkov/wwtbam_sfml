#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <ctgmath>

#include "ResourceHolder.h"
#include "Widget.h"

using namespace sf;



//TODO: make singleton
class WidgetManager {
private:
    std::vector<std::unique_ptr<Widget>> widgets;
public:
    void draw(sf::RenderWindow &window) {
        for (const auto &widget: widgets)
            window.draw(*widget);
    }

    void add(Widget &widget) {
        widgets.push_back(std::make_unique<Widget>(widget));
    }

    void remove(const std::string& name) {
        for (auto it = widgets.begin(); it != widgets.end(); it++) {
            if (it->get()->getName() == name)
                widgets.erase(it);
        }
    }

    void clear() {
        widgets.clear();
    }

    Widget& get(const std::string& name) {
        for (auto & widget : widgets) {
            if (widget->getName() == name)
                return *widget;
        }
    }
};

namespace wwtbam {
    const int WIDTH = 1024;
    const int HEIGHT = 768;

    //TODO: should be deserializable
    class Question: public sf::Drawable {
            std::string wording;
            std::string answers[4];
            int correct_answer;

            static sf::Texture t_question;
            //static sf::Texture t_answers;

    public:
        Question(const std::string &wording, std::string answers[4], int correctAnswer) : wording(wording), correct_answer(correctAnswer) {

            sf::Texture t;
            sf::Font f;
            t.loadFromFile("../resources/img/question_and_answers.png");
            f.loadFromFile("../resources/fonts/COOP_GEC.TTF");

            for (int i = 0; i < 4; i++)
                this->answers[i] = answers[i];
        }

    protected:
        void draw(RenderTarget &target, RenderStates states) const override {

        }
    };
}

int main() {
    sf::RenderWindow window(sf::VideoMode(wwtbam::WIDTH, wwtbam::HEIGHT), "WWTBAM", sf::Style::Close | sf::Style::Titlebar);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Loading textures and fonts

    ResourceHolder resourceHolder;
    resourceHolder.loadTexture("../resources/img/background.png", "background");
    resourceHolder.loadTexture("../resources/img/long_slots.png", "long_slots", IntRect(0, 0, wwtbam::WIDTH, 64));
    resourceHolder.loadFont("../resources/fonts/COOP_GEC.TTF", "Cooperplate");

    //Loading sprites

    sf::Sprite background(resourceHolder.getTexture("background"));
    background.setColor(sf::Color(255, 255, 255, 128)); //TODO: check this changes brightness

    sf::Sprite long_slot(resourceHolder.getTexture("long_slots"));

    //Creating start screen

    WidgetManager manager = WidgetManager();
    manager.add(*(new Widget("start_button", long_slot, sf::Text("Play", resourceHolder.getFont("Cooperplate"), 30), Vector2f(0, window.getSize().y / 2))));
    manager.add(*(new Widget("settings_button", long_slot, sf::Text("Settings", resourceHolder.getFont("Cooperplate"), 30), Vector2f(0, 600))));

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
                //manager.clear();
                manager.remove("start_button");
            }
        }

        window.draw(background);
        manager.draw(window);
        window.display();
    }

    return 0;
}
