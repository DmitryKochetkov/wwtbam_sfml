//
// Created by dimedrol on 02.04.2020.
//

#ifndef WWTBAM_SFML_QUESTION_H
#define WWTBAM_SFML_QUESTION_H

#include <SFML/Graphics.hpp>
#include "../ResourceHolder.h"
#include "../TexturedButton.h"
#include "WindowResolution.h"

namespace wwtbam {
    class Question;
}

class wwtbam::Question: public sf::Drawable {
private:
    int font_size = 32;
    std::string wording;
    std::string answers[4];

    int shown = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        sf::Font& font = ResourceHolder::Instance().getFont("ITC Conduit");

        TexturedButton t_wording(
                sf::Text(wording, font, font_size),
                sf::Vector2f(0, Y),
                ResourceHolder::Instance().getTexture("question"));

        target.draw(t_wording);
        for (int i = 0; i < 4; i++) {
            sf::Vector2f position;
            position.x = i % 2 == 0 ? 0 : wwtbam::WIDTH/2;
            position.y = i <= 1 ? Y+MARGIN : Y+MARGIN+70;
            sf::Sprite t_answer_bg;
            if (i % 2 == 0)
                t_answer_bg.setTexture(ResourceHolder::Instance().getTexture("left_answer"));
            else t_answer_bg.setTexture(ResourceHolder::Instance().getTexture("right_answer"));
            t_answer_bg.setPosition(position);
            target.draw(t_answer_bg);
        }

        for (int i = 0; i < shown; i++) {
            char l = 'A' + i;
            sf::Text letter(std::string(1, l) + ":", ResourceHolder::Instance().getFont("Cooperplate"), 30);
            letter.setFillColor(sf::Color(255, 170, 0));
            sf::Text answer(answers[i], font, font_size);

            sf::Vector2f position;
            position.x = i % 2 == 0 ? 0 : wwtbam::WIDTH/2;
            position.y = i <= 1 ? Y+MARGIN : Y+MARGIN+70;

            position.y += double(ANSWER_HEIGHT)/2 - letter.getGlobalBounds().height;
            if (i % 2 == 0)
                position.x += 110;
            else position.x += 55;

            letter.setPosition(position);
            answer.setPosition(position + sf::Vector2f(letter.getGlobalBounds().width + 15, 0));
            target.draw(letter);
            target.draw(answer);
        }
    }

public:
    static const int Y = 450;
    static const int ANSWER_HEIGHT = 68;
    static const int MARGIN = 110;

    Question(std::string wording, std::string answers[4], int correct_answers): wording(wording) {
        for (int i = 0; i < 4; i++)
            this->answers[i] = answers[i];
    }

    void Show() {
        if (shown < 4)
            shown++;
    }

    void FinalAnswer(int answer) {
        //Group answers manipulations
    }

    void ShowCorrect() {
        //Group answers manipulations
    }
};

#endif //WWTBAM_SFML_QUESTION_H
