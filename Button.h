//
// Created by dimedrol on 04.04.2020.
//

#ifndef WWTBAM_SFML_BUTTON_H
#define WWTBAM_SFML_BUTTON_H

#include <SFML/Graphics.hpp>
#include <ctgmath>

class Button: public sf::Drawable {
protected:
    sf::RectangleShape body;
    sf::Text text;

public:
    Button(const sf::Text &text, const sf::Vector2f &position, const sf::Vector2f &size = sf::Vector2f(120, 50)) : text(text) {
        body = sf::RectangleShape(size);
        body.setOutlineThickness(3.0f);
        body.setFillColor(sf::Color(255, 255, 255, 0));

        sf::Vector2f offset;
        offset.x = this->text.getGlobalBounds().width * 0.5f;
        offset.y = this->text.getGlobalBounds().height;

        //maybe I'm blind, but the text seems noisy with no round
        offset.x = round(offset.x);
        offset.y = round(offset.y);
        body.setPosition(position);
        this->text.setPosition(position + size * 0.5f - offset);
    }

    bool isClicked(sf::RenderWindow& window) {
        return sf::Mouse::isButtonPressed(sf::Mouse::Left) && body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(text);
        target.draw(body);
    }
};

#endif //WWTBAM_SFML_BUTTON_H
