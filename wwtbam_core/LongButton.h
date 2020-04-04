//
// Created by dimedrol on 04.04.2020.
//

#ifndef WWTBAM_SFML_LONGBUTTON_H
#define WWTBAM_SFML_LONGBUTTON_H


#include "../TexturedButton.h"
#include "../ResourceHolder.h"

namespace wwtbam {
    class LongButton;
}

class wwtbam::LongButton : public TexturedButton {
public:
    LongButton(const sf::Text &text, const float y): TexturedButton(text, sf::Vector2f(0, y), ResourceHolder::Instance().getTexture("long_slot")) {

    }
};


#endif //WWTBAM_SFML_LONGBUTTON_H
