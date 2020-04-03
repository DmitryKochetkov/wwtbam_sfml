//
// Created by dimedrol on 02.04.2020.
//

#ifndef WWTBAM_SFML_WIDGET_H
#define WWTBAM_SFML_WIDGET_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctgmath>

class Widget : public sf::Drawable {
    std::string name; //TODO: change to sort of hash and make a ==operator
    sf::RectangleShape rectangleShape;
    sf::Sprite sprite;
    sf::Text text;
    sf::Vector2f size;

public:
    Widget(const std::string &name, sf::Vector2f size, const std::string &text, const sf::Vector2f &position);

    Widget(const std::string &name, const sf::Sprite &sprite, const sf::Text &text, const sf::Vector2f &position);

    bool isClicked(sf::RenderWindow& window) {
        return sf::Mouse::isButtonPressed(sf::Mouse::Left) && sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
    }

    const sf::Vector2f &getSize() const;

    const std::string &getName() const;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //WWTBAM_SFML_WIDGET_H
