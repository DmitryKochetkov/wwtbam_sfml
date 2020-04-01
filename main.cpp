#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>

using namespace sf;

class Button : public sf::Drawable {
    sf::RectangleShape rectangleShape;
    sf::Sprite sprite;
    sf::Text text;
    sf::Vector2f size;

public:
    //constructor A
    Button(Vector2f size, const char* s, const Vector2f &position) {
        std::cout << "Constructor A called" << std::endl;
        this->size = size;
        sf::Font font;
        if (!font.loadFromFile("../resources/fonts/COOP_GEC.TTF")) {
            std::cerr << "Unable to load font arial.ttf" << std::endl;
        }

//        text = sf::Text(s, font, 30); //error
//        text.setString(s);
        text.setFont(font);

        rectangleShape = sf::RectangleShape(Vector2f(150, 100));
        rectangleShape.setPosition(position);
        rectangleShape.setFillColor(sf::Color(255, 255, 255, 0));
        rectangleShape.setOutlineColor(sf::Color(255, 255, 255));
        rectangleShape.setOutlineThickness(3.0f);
    }

    //constructor B
    Button(const Sprite &sprite, const Text &text, const Vector2f &position) : sprite(sprite), text(text) {
        std::cout << "Constructor B called" << std::endl;
        this->sprite.setPosition(position);
        size = (Vector2f)sprite.getTexture()->getSize();

        sf::Vector2f offset;
        offset.x = this->text.getGlobalBounds().width * 0.5f;
        offset.y = this->text.getGlobalBounds().height;

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

namespace wwtbam {
    const int width = 1024;
    const int height = 768;

    class WideButton : public Button {
        const int height = 64;
    };
}

int main() {
    sf::RenderWindow window(sf::VideoMode(wwtbam::width, wwtbam::height), "WWTBAM", sf::Style::Close | sf::Style::Titlebar);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Loading textures and fonts

    sf::Texture t_background;
    sf::Texture t_long_slot;
    sf::Font cooperplate_cyrillic;

    t_background.loadFromFile("../resources/img/background.png");
    t_long_slot.loadFromFile("../resources/img/long_slots.png", IntRect(0, 0, 1024, 64));

    cooperplate_cyrillic.loadFromFile("../resources/fonts/COOP_GCB.TTF");

    //Loading sprites

    sf::Sprite background(t_background);
    background.setColor(sf::Color(255, 255, 255, 128)); //TODO: check this changes brightness

    sf::Sprite long_slot(t_long_slot);

    //Creating start screen

    Button start_button(long_slot, sf::Text("Play", cooperplate_cyrillic, 30), Vector2f(0, window.getSize().y / 2));
    Button settings_button(long_slot, sf::Text("Settings", cooperplate_cyrillic, 30), Vector2f(0, 600));

    Button test_button(Vector2f(100, 50), "Test", Vector2f(200, 150));

    //Window logic

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (start_button.isClicked(window)) {
                window.close();
            }
        }

        window.draw(background);
        window.draw(start_button);
        window.draw(settings_button);
//        window.draw(test_button);
        window.display();
    }

    return 0;
}
