//
// Created by dimedrol on 04.04.2020.
//

#ifndef WWTBAM_SFML_TEXTUREDBUTTON_H
#define WWTBAM_SFML_TEXTUREDBUTTON_H

#include <SFML/Graphics.hpp>
#include "Button.h"

class TexturedButton : public Button {
    sf::Sprite sprite;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(sprite);
        target.draw(text);
    }

public:
    TexturedButton(const sf::Text &text, const sf::Vector2f &position, const sf::Texture& texture) : Button(text, position, sf::Vector2f(texture.getSize())) {
        //можно ли передавать sf::Texture?
        sprite = sf::Sprite(texture);
        sprite.setPosition(position);
    }
};


#endif //WWTBAM_SFML_TEXTUREDBUTTON_H
