//
// Created by dimedrol on 02.04.2020.
//

#include "WidgetManager.h"

void WidgetManager::draw(sf::RenderWindow &window) {
    for (const auto &widget: widgets)
        window.draw(*widget);
}

//void WidgetManager::add(Widget &widget) {
//    widgets.push_back(std::make_unique<Widget>(widget));
//}

template <typename T>
void WidgetManager::add(T&& widget) {
    widgets.push_back(std::make_unique<T>(widget));
}

void WidgetManager::remove(const std::string &name) {
    for (auto it = widgets.begin(); it != widgets.end(); it++) {
        if (it->get()->getName() == name)
            widgets.erase(it);
    }
}

void WidgetManager::clear() {
    widgets.clear();
}

Widget &WidgetManager::get(const std::string &name) {
    for (auto & widget : widgets) {
        if (widget->getName() == name)
            return *widget;
    }
}

template<typename T>
void WidgetManager::add(T &widget) {
    widgets.push_back(std::make_unique<T>(widget));
}


