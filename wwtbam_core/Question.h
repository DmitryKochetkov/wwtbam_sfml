//
// Created by dimedrol on 02.04.2020.
//

#ifndef WWTBAM_SFML_QUESTION_H
#define WWTBAM_SFML_QUESTION_H

#include "SFML/Graphics.hpp"
#include "../Widget.h"
#include "../WidgetManager.h"
#include "../ResourceHolder.h"

namespace wwtbam {
    class Question;
}

class wwtbam::Question: sf::Drawable {
    std::string wording;
    std::string answers[4];
    int correct_answer;

    std::unique_ptr<Widget> wQuestion;
    //Widget wAnswers[4];

public:
    Question(const std::string &wording, std::string answers[4], int correctAnswer) : wording(wording), correct_answer(correctAnswer) {
        for (int i = 0; i < 4; i++)
            this->answers[i] = answers[i];

        auto t = ResourceHolder::Instance().getTexture("question_and_answers");
        auto f = ResourceHolder::Instance().getFont("Cooperplate");
        wQuestion = std::make_unique<Widget>(Widget("question", sf::Sprite(t), sf::Text(wording, f, 30), sf::Vector2f(0, 450)));
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(*wQuestion);
    }
};


#endif //WWTBAM_SFML_QUESTION_H
