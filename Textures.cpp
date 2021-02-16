#include "Textures.h"
#include <iostream>

using namespace std;

std::unique_ptr<sf::RenderTexture> Textures::empty = []() {
    auto texture = make_unique<sf::RenderTexture>();
    if (!texture->create(getTextureWidth(), getTextureHeight())) {
        cerr << "couldn't create empty texture" << endl;
        exit(0);
    }
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2<float>(getTextureWidth() - 2, getTextureHeight() - 2));
    rect.setPosition(sf::Vector2<float>(1, 1));
    rect.setFillColor(sf::Color::Black);
    texture->draw(rect);
    texture->display();
    return texture;
}();

std::unique_ptr<sf::RenderTexture> Textures::agent = []() {
    auto texture = make_unique<sf::RenderTexture>();
    if (!texture->create(getTextureWidth(), getTextureHeight())) {
        cerr << "couldn't create agent texture" << endl;
        exit(0);
    }
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2<float>(getTextureWidth() - 2, getTextureHeight() - 2));
    rect.setPosition(sf::Vector2<float>(1, 1));
    rect.setFillColor(sf::Color::Red);
    texture->draw(rect);
    texture->display();
    return texture;
}();

std::unique_ptr<sf::RenderTexture> Textures::food = []() {
    auto texture = make_unique<sf::RenderTexture>();
    if (!texture->create(getTextureWidth(), getTextureHeight())) {
        cerr << "couldn't create food texture" << endl;
        exit(0);
    }
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2<float>(getTextureWidth() - 2, getTextureHeight() - 2));
    rect.setPosition(sf::Vector2<float>(1, 1));
    rect.setFillColor(sf::Color::Green);
    texture->draw(rect);
    texture->display();
    return texture;
}();

int Textures::getTextureWidth() {
    return 10;
}

int Textures::getTextureHeight() {
    return 10;
}
