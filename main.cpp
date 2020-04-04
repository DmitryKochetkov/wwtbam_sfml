#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctgmath>
#include "Group.h"
#include "ResourceHolder.h"

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

namespace wwtbam {
    const int WIDTH = 1024;
    const int HEIGHT = 768;

    class LongButton : public TexturedButton {
    public:
        LongButton(const sf::Text &text, const float y): TexturedButton(text, sf::Vector2f(0, y), ResourceHolder::Instance().getTexture("long_slot")) {

        }
    };

    class Question: public sf::Drawable {
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
                position.x = i % 2 == 0 ? 0 : WIDTH/2;
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
                position.x = i % 2 == 0 ? 0 : WIDTH/2;
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
}

//class Screen {
//private:
//    //std::vector<sf::Drawable*> screen;
//    std::vector<std::unique_ptr<sf::Drawable>> screen;
//
//public:
////    void add(sf::Drawable* drawable) {
////        screen.push_back(drawable);
////    }
//
//    void add(std::unique_ptr<sf::Drawable>& drawable) {
//        screen.push_back(drawable);
//    }
//
//    void render(sf::RenderWindow& window) {
//        for (const auto &item: screen)
//            window.draw(*item);
//    }
//};

int main() {
    sf::RenderWindow window(sf::VideoMode(wwtbam::WIDTH, wwtbam::HEIGHT), "WWTBAM", sf::Style::Close | sf::Style::Titlebar);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2));

    //Loading textures and fonts
    ResourceHolder::Instance().loadTexture("../resources/img/background.png", "background");
    ResourceHolder::Instance().loadTexture("../resources/img/long_slots.png", "long_slot", sf::IntRect(0, 0, wwtbam::WIDTH, 60));
    ResourceHolder::Instance().loadTexture("../resources/img/question_and_answers.png", "question", sf::IntRect(0, 0, wwtbam::WIDTH, 106));
    ResourceHolder::Instance().loadTexture("../resources/img/question_and_answers.png", "left_answer", sf::IntRect(0, 106, wwtbam::WIDTH/2, wwtbam::Question::ANSWER_HEIGHT));
    ResourceHolder::Instance().loadTexture("../resources/img/question_and_answers.png", "right_answer", sf::IntRect(wwtbam::WIDTH/2, 106, wwtbam::WIDTH/2, wwtbam::Question::ANSWER_HEIGHT));
    ResourceHolder::Instance().loadFont("../resources/fonts/COOP_GEC.TTF", "Cooperplate");
    ResourceHolder::Instance().loadFont("../resources/fonts/ITC Conduit.ttf", "ITC Conduit");

    //Setting up background
    sf::Sprite background(ResourceHolder::Instance().getTexture("background"));

    //Testing button
    Button button(sf::Text("Show", ResourceHolder::Instance().getFont("Cooperplate"), 30), sf::Vector2f(50, 100));
    wwtbam::LongButton button2(sf::Text("Text2", ResourceHolder::Instance().getFont("Cooperplate"), 30), wwtbam::HEIGHT * 0.5f);

    //Testing question
    std::string a[4] = {"London", "Manchester", "Sheffield", "Liverpool"};
    wwtbam::Question q("What is the capital of Great Britain?", a, 0);

    //Initializing a start group
    Group menu;
    menu.push_back(background);
    menu.push_back(button);
    //menu.push_back(button2);
    menu.push_back(q);

    Group settings;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (button.isClicked(window)) {
                q.Show();
            }
        }

        window.draw(menu);
        window.display();
    }
    return 0;
}