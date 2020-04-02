//
// Created by dimedrol on 02.04.2020.
//

#include "ResourceHolder.h"

void ResourceHolder::loadTexture(std::string path, std::string name, sf::IntRect crop) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(path)) {
        throw std::runtime_error("ResourceHolder failed to load texture " + path);
    }

    if (crop.width != 0 && crop.height != 0)
        texture->loadFromFile(path, crop);

    //std::string name = path.substr(0, path.find_last_of(".") - 1);

    textures.insert(std::make_pair(name, std::move(texture)));
}

void ResourceHolder::loadFont(std::string path, std::string name) {
    std::unique_ptr<sf::Font> font(new sf::Font());
    if (!font->loadFromFile(path)) {
        throw std::runtime_error("ResourceHolder failed to load font " + path);
    }

    //std::string name = path.substr(0, path.find_last_of(".") - 1);

    fonts.insert(std::make_pair(name, std::move(font)));
}

sf::Texture &ResourceHolder::getTexture(std::string name) {
    return *textures[name];
}

sf::Font &ResourceHolder::getFont(std::string name) {
    return *fonts[name];
}

