//
// Created by dimedrol on 02.04.2020.
//

#ifndef WWTBAM_SFML_QUESTION_H
#define WWTBAM_SFML_QUESTION_H

#include "SFML/Graphics.hpp"
#include "../Widget.h"

namespace wwtbam {
    class Question;
}

class wwtbam::Question {
    std::string wording;
    std::string answers[4];
    int correct_answer;

    static sf::Texture t_question;
    //static sf::Texture t_answers;

public:
    Question(const std::string &wording, std::string answers[4], int correctAnswer) : wording(wording), correct_answer(correctAnswer) {
        for (int i = 0; i < 4; i++)
            this->answers[i] = answers[i];

//        sf::Texture t;
//        sf::Font f;
//        t.loadFromFile("../resources/img/question_and_answers.png");
//        f.loadFromFile("../resources/fonts/COOP_GEC.TTF");
    }

protected:
private:
//    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
//
//    }
};


#endif //WWTBAM_SFML_QUESTION_H
