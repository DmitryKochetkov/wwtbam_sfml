//
// Created by dimedrol on 02.04.2020.
//

#ifndef WWTBAM_SFML_WIDGETMANAGER_H
#define WWTBAM_SFML_WIDGETMANAGER_H

#include "Widget.h"

//TODO: make singleton
class WidgetManager {
private:
    std::vector<std::unique_ptr<Widget>> widgets;
public:
    void draw(sf::RenderWindow &window);

    void add(Widget &widget);

    void remove(const std::string& name);

    void clear();

    Widget& get(const std::string& name);
};



#endif //WWTBAM_SFML_WIDGETMANAGER_H
