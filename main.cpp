#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <ctgmath>

#include "ResourceHolder.h"

using namespace sf;

class Button : public sf::Drawable {
    sf::RectangleShape rectangleShape;
    sf::Sprite sprite;
    sf::Text text;
    sf::Vector2f size;

public:
    //constructor A
    Button(Vector2f size, std::string s, const Vector2f &position) {
        this->size = size;
        sf::Font *font = new sf::Font(); //is this save? TODO: make_unique
        if (!font->loadFromFile("../resources/fonts/COOP_GEC.TTF")) {
            std::cerr << "Unable to load font arial.ttf" << std::endl;
        }

        text = sf::Text(s, *font, 30);

        //дублирование кода, может лучше вынести в отдельный метод или делегировать приватный конструктор
        sf::Vector2f offset;
        offset.x = this->text.getGlobalBounds().width * 0.5f;
        offset.y = this->text.getGlobalBounds().height;
        this->text.setPosition(position + size * 0.5f - offset);

        rectangleShape = sf::RectangleShape(Vector2f(size.x, size.y));
        rectangleShape.setPosition(position);
        rectangleShape.setFillColor(sf::Color(255, 255, 255, 0));
        rectangleShape.setOutlineColor(sf::Color(255, 255, 255));
        rectangleShape.setOutlineThickness(3.0f);
    }

    //constructor B
    Button(const Sprite &sprite, const Text &text, const Vector2f &position) : sprite(sprite), text(text) {
        this->sprite.setPosition(position);
        size = (Vector2f)sprite.getTexture()->getSize();

        sf::Vector2f offset;
        offset.x = this->text.getGlobalBounds().width * 0.5f;
        offset.y = this->text.getGlobalBounds().height;

        //maybe I'm blind, but the text seems noisy with no round
        offset.x = round(offset.x);
        offset.y = round(offset.y);
        this->text.setPosition(position + size * 0.5f - offset);
    }

    bool isClicked(RenderWindow& window) {
        return Mouse::isButtonPressed(Mouse::Left) && sprite.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
    }

    const Vector2f &getSize() const {
        return size;
    }

protected:
    void draw(RenderTarget &target, RenderStates states) const override {
        if (sprite.getTexture() != nullptr)
            target.draw(sprite);
        else target.draw(rectangleShape);
        target.draw(text);
    }
};

//TODO: make singleton
class WidgetManager {
private:
    std::vector<std::unique_ptr<sf::Drawable>> widgets;
public:
    void draw(sf::RenderWindow &window) {
        for (const auto &widget: widgets)
            window.draw(*widget);
    }

//    void add(sf::Drawable &widget) {
//        //widgets.push_back(std::unique_ptr<sf::Drawable>(&widget));
//        widgets.push_back(std::make_unique<sf::Drawable>(widget));
//    }

    //TODO: maybe there is a way to make it better than a bunch of similar functions?

    void add(sf::Text &text) {
        widgets.push_back(std::make_unique<sf::Text>(text));
    }

    void add(sf::Sprite &sprite) {
        widgets.push_back(std::make_unique<sf::Sprite>(sprite));
    }

    void add(Button &button) {
        widgets.push_back(std::make_unique<Button>(button));
    }

    //Doesn't work
    void remove(sf::Drawable &widget) {
        for (auto it = widgets.begin(); it != widgets.end(); it++) {
            if ((*it).get() == &widget)
                widgets.erase(it);
        }
    }

    void clear() {
        widgets.clear();
    }
};

namespace wwtbam {
    const int width = 1024;
    const int height = 768;

    class WideButton : public Button {
        const int height = 64;
    };
}

int main() {
    sf::RenderWindow window(sf::VideoMode(wwtbam::WIDTH, wwtbam::HEIGHT), "WWTBAM", sf::Style::Close | sf::Style::Titlebar);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Loading textures and fonts

    sf::Texture t_background;
    sf::Texture t_long_slot;
    sf::Font cooperplate_cyrillic;

    t_background.loadFromFile("../resources/img/background.png");
    t_long_slot.loadFromFile("../resources/img/long_slots.png", IntRect(0, 0, wwtbam::WIDTH, 64));

    cooperplate_cyrillic.loadFromFile("../resources/fonts/COOP_GEC.TTF");

    //Loading sprites

    sf::Sprite background(t_background);
    background.setColor(sf::Color(255, 255, 255, 128)); //TODO: check this changes brightness

    sf::Sprite long_slot(t_long_slot);

    //Creating start screen

    WidgetManager manager = WidgetManager();
    Button start_button(long_slot, sf::Text("Play", cooperplate_cyrillic, 30), Vector2f(0, window.getSize().y / 2));
    Button settings_button(long_slot, sf::Text("Settings", cooperplate_cyrillic, 30), Vector2f(0, 600));
    Button test_button(Vector2f(200, 150), "Test", Vector2f(600, 150));
    manager.add(start_button);
    manager.add(settings_button);

    //Window logic

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (start_button.isClicked(window)) {
                manager.clear();
            }
        }

        window.draw(background);
        manager.draw(window);
        window.display();
    }

    return 0;
}
