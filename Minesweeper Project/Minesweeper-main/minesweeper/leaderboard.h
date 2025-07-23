//
// Created by carlo on 4/11/2024.
//

#ifndef MINESWEEPER_LEADERBOARD_H
#define MINESWEEPER_LEADERBOARD_H

#endif //MINESWEEPER_LEADERBOARD_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

void setText2(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void leaderboard(string& playername, int time, int row, int col, bool done) {
    int width = (col*16);
    int height = (row*16) + 50;
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text title;
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    int titlewidth = width / 2;
    int titleheight = (height / 2) - 120;
    setText2(title, titlewidth, titleheight);
    ifstream file("files/leaderboard.txt");
    string line;
    map<int, string> bplayers;
    while (getline(file, line)) {
        stringstream ss(line);
        string ttime, name;
        getline(ss, ttime, ',');
        getline(ss, name, ',');
        string minutes = ttime.substr(0, 2);
        string seconds = ttime.substr(3,2);
        int iminutes = stoi(minutes);
        int iseconds = stoi(seconds);
        int tseconds = (iminutes * 60) + iseconds;
        string adjname = name.substr(1, name.length());
        bplayers[tseconds] = adjname;
    }
    file.close();
    if (done == true) {
        bplayers[time] = playername;
    }
    map<int,string> :: iterator iter;
    int count = 1;
    string output = "";
    ofstream file2("files/leaderboard.txt");
    for (iter = bplayers.begin(); iter != bplayers.end() && count < 6; iter++ ) {
        int pminutes = (iter->first) / 60;
        string adjminutes = to_string(pminutes);
        if (pminutes < 10) {
            adjminutes = "0" + adjminutes;
        }
        int pseconds = (iter->first) % 60;
        string adjseconds = to_string(pseconds);
        if (pseconds < 10) {
            adjseconds = "0" + adjseconds;
        }
        string adjtime = adjminutes + ":" + adjseconds;
        if (iter->second == playername && done && iter->first == time) {
            output += to_string(count) + "." + "\t" + adjtime + "\t" + iter->second + "*" + "\n\n";
            count++;
        }
        else {
            output += to_string(count) + "." + "\t" + adjtime + "\t" + iter->second + "\n\n";
            count++;
        }
        file2 << adjtime << ", " << iter->second << endl;
    }
    file2.close();
    sf::Text ldrbrd;
    ldrbrd.setFont(font);
    ldrbrd.setString(output);
    ldrbrd.setCharacterSize(18);
    ldrbrd.setFillColor(sf::Color::White);
    ldrbrd.setStyle(sf::Text::Bold);
    int ldrbrdwidth = width / 2;
    int ldrbrdheight = (height / 2) + 20;
    setText2(ldrbrd, ldrbrdwidth, ldrbrdheight);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(title);
        window.draw(ldrbrd);
        window.display();
    }
}