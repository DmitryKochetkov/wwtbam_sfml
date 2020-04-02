//
// Created by dimedrol on 02.04.2020.
//

#include "Widget.h"

Widget::Widget(std::string name, sf::Vector2f size, std::string s, const sf::Vector2f &position): name(name) {
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

    rectangleShape = sf::RectangleShape(sf::Vector2f(size.x, size.y));
    rectangleShape.setPosition(position);
    rectangleShape.setFillColor(sf::Color(255, 255, 255, 0));
    rectangleShape.setOutlineColor(sf::Color(255, 255, 255));
    rectangleShape.setOutlineThickness(3.0f);
}

Widget::Widget(std::string name, const sf::Sprite &sprite, const sf::Text &text, const sf::Vector2f &position) : name(name), sprite(sprite), text(text) {
    this->sprite.setPosition(position);
    size = (sf::Vector2f)sprite.getTexture()->getSize();

    sf::Vector2f offset;
    offset.x = this->text.getGlobalBounds().width * 0.5f;
    offset.y = this->text.getGlobalBounds().height;

    //maybe I'm blind, but the text seems noisy with no round
    offset.x = round(offset.x);
    offset.y = round(offset.y);
    this->text.setPosition(position + size * 0.5f - offset);
}

const sf::Vector2f &Widget::getSize() const {
    return size;
}

void Widget::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (sprite.getTexture() != nullptr)
        target.draw(sprite);
    else target.draw(rectangleShape);
    target.draw(text);
}

const std::string &Widget::getName() const {
    return name;
}

