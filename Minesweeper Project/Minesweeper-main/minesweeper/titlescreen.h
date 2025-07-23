#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;


void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int titlescreen(sf::RenderWindow& window, float width, float height, string& playername) {
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text title;
    title.setFont(font);
    title.setString("WELCOME TO MINESWEEPER!");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    float adj_width = width / 2.f;
    float adj_height = (height / 2.f) - 150.f;
    setText(title, adj_width, adj_height);
    sf::Text entername;
    entername.setFont(font);
    entername.setString("Enter your name:");
    entername.setCharacterSize(20);
    entername.setFillColor(sf::Color::White);
    entername.setStyle(sf::Text::Bold);
    float adj_width2 = width / 2.f;
    float adj_height2 = (height / 2.f) - 75.f;
    setText(entername, adj_width2, adj_height2);
    float adj_height3 = (height / 2.f) - 45.f;
    sf::Text nametext("", font, 28);
    nametext.setFillColor(sf::Color::Yellow);
    nametext.setPosition(adj_width2, adj_height3);
    sf::Text typingindicator("|", font, 18);
    typingindicator.setFillColor(sf::Color::Yellow);
    bool is_typing = true;
    bool showCursor = true;
    while (window.isOpen() && is_typing) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
            nametext.setString(playername + (showCursor ? "|" : ""));
            setText(nametext, adj_width2, nametext.getPosition().y);
            if (event.type == sf::Event::TextEntered) {
                if (isalpha(event.text.unicode) && event.text.unicode != 8 && playername.size() < 10){
                    if (playername.empty()) {
                        playername += toupper(static_cast<char>(event.text.unicode));
                    }
                    else {
                        playername += tolower(static_cast<char>(event.text.unicode));
                    }
                }
                else if (event.text.unicode == 8 && playername.size() > 0) {
                    playername.pop_back();
                }
                nametext.setString(playername + (showCursor ? "|" : ""));
                setText(nametext, adj_width2, nametext.getPosition().y);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && playername.size() > 0) {
                is_typing = false;
                window.close();
                return 1;
            }
        }
        if (showCursor) {
            window.clear(sf::Color::Blue);
            window.draw(title);
            window.draw(entername);
            window.draw(nametext);
            window.display();
        }
    }

}