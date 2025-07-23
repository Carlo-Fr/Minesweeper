#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include <SFML/System/Clock.hpp>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "titlescreen.h"
#include "gameboard.h"
#include "timer.h"
#include "leaderboard.h"
using namespace std;
using namespace sf;
void revealSurroundingTiles(vector<vector<tile*>> boardarray, int x, int y, float width, float height, int& count) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    if (boardarray[x][y]->revealed) {
        return;
    }
    boardarray[x][y]->revealed = true;
    if (boardarray[x][y]->flag) {
        boardarray[x][y]->flag = false;
        count++;
    }
    if (boardarray[x][y]->nearby > 0){
        return;
    }
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;  // Skip the current tile
            revealSurroundingTiles(boardarray, x + dx, y + dy, width, height, count);
        }
    }
}
void gamescreen(sf::RenderWindow& window, float width, float height, gameboard& z, string& plyrname) {
    Texture hidden;
    hidden.loadFromFile("files/images/tile_hidden.png");
    Sprite h(hidden);
    Texture revealed;
    revealed.loadFromFile("files/images/tile_revealed.png");
    Sprite r(revealed);
    Texture mine;
    mine.loadFromFile("files/images/mine.png");
    Sprite m(mine);
    Texture num1;
    num1.loadFromFile("files/images/number_1.png");
    Sprite one(num1);
    Texture num2;
    num2.loadFromFile("files/images/number_2.png");
    Sprite two(num2);
    Texture num3;
    num3.loadFromFile("files/images/number_3.png");
    Sprite three(num3);
    Texture num4;
    num4.loadFromFile("files/images/number_4.png");
    Sprite four(num4);
    Texture num5;
    num5.loadFromFile("files/images/number_5.png");
    Sprite five(num5);
    Texture num6;
    num6.loadFromFile("files/images/number_6.png");
    Sprite six(num6);
    Texture num7;
    num7.loadFromFile("files/images/number_7.png");
    Sprite seven(num7);
    Texture num8;
    num8.loadFromFile("files/images/number_8.png");
    Sprite eight(num8);
    Texture flag;
    flag.loadFromFile("files/images/flag.png");
    Sprite f(flag);
    Texture debug;
    debug.loadFromFile("files/images/debug.png");
    Sprite dbg(debug);
    Texture happy;
    happy.loadFromFile("files/images/face_happy.png");
    Sprite hpy(happy);
    Texture lose;
    lose.loadFromFile("files/images/face_lose.png");
    Sprite lse(lose);
    Texture winface;
    winface.loadFromFile("files/images/face_win.png");
    Sprite win(winface);
    Texture digits;
    digits.loadFromFile("files/images/digits.png");
    Sprite t0;
    t0.setTexture(digits);
    t0.setTextureRect(IntRect(0, 0, 21, 32));
    Sprite t1;
    t1.setTexture(digits);
    t1.setTextureRect(IntRect(21, 0, 21, 32));
    Sprite t2;
    t2.setTexture(digits);
    t2.setTextureRect(IntRect(42, 0, 21, 32));
    Sprite t3;
    t3.setTexture(digits);
    t3.setTextureRect(IntRect(63, 0, 21, 32));
    Sprite t4;
    t4.setTexture(digits);
    t4.setTextureRect(IntRect(84, 0, 21, 32));
    Sprite t5;
    t5.setTexture(digits);
    t5.setTextureRect(IntRect(105, 0, 21, 32));
    Sprite t6;
    t6.setTexture(digits);
    t6.setTextureRect(IntRect(126, 0, 21, 32));
    Sprite t7;
    t7.setTexture(digits);
    t7.setTextureRect(IntRect(147, 0, 21, 32));
    Sprite t8;
    t8.setTexture(digits);
    t8.setTextureRect(IntRect(168, 0, 21, 32));
    Sprite t9;
    t9.setTexture(digits);
    t9.setTextureRect(IntRect(189, 0, 21, 32));
    Sprite tneg;
    tneg.setTexture(digits);
    tneg.setTextureRect(IntRect(210, 0, 21, 32));
    Texture play;
    play.loadFromFile("files/images/play.png");
    Sprite ply(play);
    Texture pause;
    pause.loadFromFile("files/images/pause.png");
    Sprite pse(pause);
    Texture leaderbrd;
    leaderbrd.loadFromFile("files/images/leaderboard.png");
    Sprite ldrbrd(leaderbrd);

    int cols = z.getcols();
    int rows = z.getrows();
    int debug_toggle = 0;
    int num_win = (rows*cols) - z.bombs;
    int bomb_count = z.bombs;
    bool clockpaused;
    bool alrdy_won = false;
    bool game_won;
    bool calln;
    bool callw;
    bool ldron = false;
    bool ldrclk = false;
    string bmbcnt = to_string(bomb_count);
    Timer mainclock;
    while (window.isOpen()) {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / 32;
        int y = pos.y / 32;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    if (pos.x <= z.cols*32 && pos.y <= z.rows*32 && !clockpaused && ldron == false && z.boardarray[x][y]->flag == false) {
                        if (z.boardarray[x][y]->mine == true) {
                            z.mineclicked = true;
                            z.boardclickable = false;
                            for (int i = 0; i < cols; i++) {
                                for (int j = 0; j < rows; j++) {
                                    if (z.boardarray[i][j]->mine == true) {
                                        z.boardarray[i][j]->revealed = true;
                                    }
                                }
                            }
                        }
                        if (z.boardclickable) {
                            revealSurroundingTiles(z.boardarray,x,y,cols,rows, bomb_count);
                            bmbcnt = to_string(bomb_count);
                        }
                    }
                    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::FloatRect bounds = dbg.getGlobalBounds();
                    sf::FloatRect facebound1 = hpy.getGlobalBounds();
                    sf::FloatRect facebound2 = lse.getGlobalBounds();
                    sf::FloatRect facebound3 = win.getGlobalBounds();
                    sf::FloatRect pausebound = pse.getGlobalBounds();
                    sf::FloatRect playbound = ply.getGlobalBounds();
                    sf::FloatRect ldrbound = ldrbrd.getGlobalBounds();
                    if (facebound1.contains(mouse) || facebound1.contains(mouse) || facebound1.contains(mouse) && ldron == false) {
                        z.resetarray();
                        z.findnearby();
                        z.winlose = false;
                        z.mineclicked = false;
                        z.mineclickable = true;
                        z.boardclickable = true;
                        debug_toggle = 0;
                        bomb_count = z.bombs;
                        bmbcnt = to_string(bomb_count);
                        mainclock.reset();
                        game_won = false;
                        clockpaused = false;
                        alrdy_won = false;
                        ldrclk = false;
                    }
                    if (pausebound.contains(mouse) || playbound.contains(mouse) && ldron == false) {
                        if (!game_won) {
                            if (!clockpaused) {
                                mainclock.pause();
                                clockpaused = true;
                            }
                            else if (clockpaused == true){
                                clockpaused = false;
                                mainclock.resume();
                            }
                        }

                    }
                    if (ldrbound.contains(mouse) && ldron == false) {
                        if (clockpaused == true) {
                            ldron = true;
                            calln = true;
                            ldrclk = true;
                        }
                        else {
                            mainclock.pause();
                            clockpaused = true;
                            ldron = true;
                            calln = true;
                        }
                    }
                    if (bounds.contains(mouse) && ldron == false) {
                        if (debug_toggle == 0) {
                            for (int i = 0; i < cols; i++) {
                                for (int j = 0; j < rows; j++) {
                                    if (z.boardarray[i][j]->mine == true) {
                                        z.boardarray[i][j]->revealed = true;
                                    }
                                }
                            }
                            debug_toggle++;
                        }
                        else {
                            for (int i = 0; i < cols; i++) {
                                for (int j = 0; j < rows; j++) {
                                    if (z.boardarray[i][j]->mine == true) {
                                        z.boardarray[i][j]->revealed = false;
                                    }
                                }
                            }
                            debug_toggle = 0;
                        }
                    }

                }
                if (event.key.code == Mouse::Right) {
                    if (pos.x <= z.cols*32 && pos.y <= z.rows*32) {
                        if (z.boardarray[x][y]->revealed == false) {
                            if (z.boardarray[x][y]->flag == true) {
                                z.boardarray[x][y]->flag = false;
                                bomb_count++;
                                bmbcnt = to_string(bomb_count);
                            }
                            else {
                                z.boardarray[x][y]->flag = true;
                                bomb_count--;
                                bmbcnt = to_string(bomb_count);
                            }
                        }
                    }
                }
            }

            //window.display();
        }
        window.clear(sf::Color::White);
        int cols = z.getcols();
        int rows = z.getrows();
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (z.boardarray[i][j]->revealed == false ) {
                    h.setPosition(i * 32, j * 32);
                    window.draw(h);
                    if (z.boardarray[i][j]->flag == true) {
                        f.setPosition(i * 32, j * 32);
                        window.draw(f);
                    }
                    if (z.winlose == true) {
                        if (z.boardarray[i][j]->mine == true) {
                            f.setPosition(i * 32, j * 32);
                            window.draw(f);
                        }
                    }
                }
                else if (z.boardarray[i][j]->revealed == true) {
                    if (z.boardarray[i][j]->mine == true) {
                        if (z.boardarray[i][j]->flag == true){
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            f.setPosition(i * 32, j * 32);
                            window.draw(f);
                            m.setPosition(i * 32, j * 32);
                            window.draw(m);

                        }
                        else {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            m.setPosition(i * 32, j * 32);
                            window.draw(m);
                        }
                    }
                    else if (z.boardarray[i][j]->nearby > 0) {
                        if (z.boardarray[i][j]->nearby == 1) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            one.setPosition(i * 32, j * 32);
                            window.draw(one);
                        }
                        if (z.boardarray[i][j]->nearby == 2) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            two.setPosition(i * 32, j * 32);
                            window.draw(two);
                        }
                        if (z.boardarray[i][j]->nearby == 3) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            three.setPosition(i * 32, j * 32);
                            window.draw(three);
                        }
                        if (z.boardarray[i][j]->nearby == 4) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            four.setPosition(i * 32, j * 32);
                            window.draw(four);
                        }
                        if (z.boardarray[i][j]->nearby == 5) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            five.setPosition(i * 32, j * 32);
                            window.draw(five);
                        }
                        if (z.boardarray[i][j]->nearby == 6) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            six.setPosition(i * 32, j * 32);
                            window.draw(six);
                        }
                        if (z.boardarray[i][j]->nearby == 7) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            seven.setPosition(i * 32, j * 32);
                            window.draw(seven);
                        }
                        if (z.boardarray[i][j]->nearby == 8) {
                            r.setPosition(i * 32, j * 32);
                            window.draw(r);
                            eight.setPosition(i * 32, j * 32);
                            window.draw(eight);
                        }
                    }
                    else {
                        r.setPosition(i * 32, j * 32);
                        window.draw(r);
                    }
                }
                if (clockpaused && z.mineclicked == false) {
                    r.setPosition(i * 32, j * 32);
                    window.draw(r);
                }
            }
        }
        int checkwincount = 0;
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (z.boardarray[i][j]->revealed && !z.boardarray[i][j]->mine && !clockpaused){
                    checkwincount++;
                }
            }
        }
        dbg.setPosition((cols*32) - 304, 32*(rows+0.5));
        window.draw(dbg);
        if (checkwincount == num_win && !clockpaused) {
            z.winlose = true;
            z.mineclickable = false;
            bomb_count = 0;
            bmbcnt = to_string(bomb_count);
        }
        if (z.mineclicked && z.mineclickable) {
            lse.setPosition(((cols/2)*32) - 32, 32*(rows+0.5));
            window.draw(lse);
            mainclock.pause();
        }
        else if (z.winlose && !clockpaused && alrdy_won == false) {
            win.setPosition(((cols/2)*32) - 32, 32*(rows+0.5));
            window.draw(win);
            game_won = true;
            mainclock.pause();
            win.setPosition(((cols/2)*32) - 32, 32*(rows+0.5));
            window.draw(win);
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    if (z.boardarray[i][j]->mine == true) {
                        h.setPosition(i * 32, j * 32);
                        window.draw(h);
                        f.setPosition(i * 32, j * 32);
                        window.draw(f);
                    }
                }
            }
            callw = true;
            ldron = true;
            alrdy_won = true;
        }
        else if (z.winlose && !clockpaused && alrdy_won == true) {
            win.setPosition(((cols/2)*32) - 32, 32*(rows+0.5));
            window.draw(win);
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    if (z.boardarray[i][j]->mine == true) {
                        h.setPosition(i * 32, j * 32);
                        window.draw(h);
                        f.setPosition(i * 32, j * 32);
                        window.draw(f);
                    }
                }
            }
        }
        else {
            hpy.setPosition(((cols/2)*32) - 32, 32*(rows+0.5));
            window.draw(hpy);
        }
        ldrbrd.setPosition((cols*32) - 176, 32*(rows+0.5));
        window.draw(ldrbrd);

        if (clockpaused && z.mineclicked == false) {
            ply.setPosition((cols*32) - 240, 32*(rows+0.5));
            window.draw(ply);
        }
        else {
            pse.setPosition((cols*32) - 240, 32*(rows+0.5));
            window.draw(pse);
        }
        int offset = 0;
        if (bmbcnt[0] == '-') {
            tneg.setPosition(12, 32*(rows+0.5) + 16);
            window.draw(tneg);
            string substring = bmbcnt.substr(1, bmbcnt.length());
            if (substring.size() == 1) {
                t0.setPosition(33, 32*(rows+0.5) + 16);
                window.draw(t0);
                t0.setPosition(54, 32*(rows+0.5) + 16);
                window.draw(t0);
                offset += 42;
            }
            else if (substring.size() == 2) {
                t0.setPosition(33, 32*(rows+0.5) + 16);
                window.draw(t0);
                offset += 21;
            }
            for (int j = 0; j < substring.size(); j++) {
                if (substring[j] == '0') {
                    t0.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t0);
                    offset += 21;
                }
                else if (substring[j] == '1') {
                    t1.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t1);
                    offset += 21;
                }
                else if (substring[j] == '2') {
                    t2.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t2);
                    offset += 21;
                }
                else if (substring[j] == '3') {
                    t3.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t3);
                    offset += 21;
                }
                else if (substring[j] == '4') {
                    t4.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t4);
                    offset += 21;
                }
                else if (substring[j] == '5') {
                    t5.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t5);
                    offset += 21;
                }
                else if (substring[j] == '6') {
                    t6.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t6);
                    offset += 21;
                }
                else if (substring[j] == '7') {
                    t7.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t7);
                    offset += 21;
                }
                else if (substring[j] == '8') {
                    t8.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t8);
                    offset += 21;
                }
                else if (substring[j] == '9') {
                    t9.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t9);
                    offset += 21;
                }
            }

        }
        else {
            if (bmbcnt.size() == 1) {
                t0.setPosition(33, 32*(rows+0.5) + 16);
                window.draw(t0);
                t0.setPosition(54, 32*(rows+0.5) + 16);
                window.draw(t0);
                offset += 42;
            }
            else if (bmbcnt.size() == 2) {
                t0.setPosition(33, 32*(rows+0.5) + 16);
                window.draw(t0);
                offset += 21;
            }
            for (int j = 0; j < bmbcnt.size(); j++) {
                if (bmbcnt[j] == '0') {
                    t0.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t0);
                    offset += 21;
                }
                else if (bmbcnt[j] == '1') {
                    t1.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t1);
                    offset += 21;
                }
                else if (bmbcnt[j] == '2') {
                    t2.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t2);
                    offset += 21;
                }
                else if (bmbcnt[j] == '3') {
                    t3.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t3);
                    offset += 21;
                }
                else if (bmbcnt[j] == '4') {
                    t4.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t4);
                    offset += 21;
                }
                else if (bmbcnt[j] == '5') {
                    t5.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t5);
                    offset += 21;
                }
                else if (bmbcnt[j] == '6') {
                    t6.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t6);
                    offset += 21;
                }
                else if (bmbcnt[j] == '7') {
                    t7.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t7);
                    offset += 21;
                }
                else if (bmbcnt[j] == '8') {
                    t8.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t8);
                    offset += 21;
                }
                else if (bmbcnt[j] == '9') {
                    t9.setPosition(33 + offset, 32*(rows+0.5) + 16);
                    window.draw(t9);
                    offset += 21;
                }
            }
        }
        float totalseconds = mainclock.gettotalseconds();
        int minutes = static_cast<int>(totalseconds) / 60;
        int seconds = static_cast<int>(totalseconds) % 60;
        if (minutes < 10) {
            t0.setPosition((cols * 32) - 97, 32*(rows+0.5) + 16);
            window.draw(t0);
            if (minutes == 0) {
                t0.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t0);
            }
            else if (minutes == 1) {
                t1.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t1);
            }
            else if (minutes == 2) {
                t2.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t2);
            }
            else if (minutes == 3) {
                t3.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t3);
            }
            else if (minutes == 4) {
                t4.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t4);
            }
            else if (minutes == 5) {
                t5.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t5);
            }
            else if (minutes == 6) {
                t6.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t6);
            }
            else if (minutes == 7) {
                t7.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t7);
            }
            else if (minutes == 8) {
                t8.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t8);
            }
            else if (minutes == 9) {
                t9.setPosition((cols * 32) - 76, 32*(rows+0.5) + 16);
                window.draw(t9);
            }
        }
        else {
            string number = to_string(minutes);
            int offset2 = 0;
            for (int i = 0; i < number.size(); i++) {
                if (number[i] == '0') {
                    t0.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t0);
                    offset2 += 21;
                }
                else if (number[i] == '1') {
                    t1.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t1);
                    offset2 += 21;
                }
                else if (number[i] == '2') {
                    t2.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t2);
                    offset2 += 21;
                }
                else if (number[i] == '3') {
                    t3.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t3);
                    offset2 += 21;
                }
                else if (number[i] == '4') {
                    t4.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t4);
                    offset2 += 21;
                }
                else if (number[i] == '5') {
                    t5.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t5);
                    offset2 += 21;
                }
                else if (number[i] == '6') {
                    t6.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t6);
                    offset2 += 21;
                }
                else if (number[i] == '7') {
                    t7.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t7);
                    offset2 += 21;
                }
                else if (number[i] == '8') {
                    t8.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t8);
                    offset2 += 21;
                }
                else if (number[i] == '9') {
                    t9.setPosition((cols * 32) - 97 + offset2, 32*(rows+0.5) + 16);
                    window.draw(t9);
                    offset2 += 21;
                }
            }
        }
        if (seconds < 10) {
            t0.setPosition((cols * 32) - 54, 32*(rows+0.5) + 16);
            window.draw(t0);
            if (seconds == 0) {
                t0.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t0);
            }
            else if (seconds == 1) {
                t1.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t1);
            }
            else if (seconds == 2) {
                t2.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t2);
            }
            else if (seconds == 3) {
                t3.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t3);
            }
            else if (seconds == 4) {
                t4.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t4);
            }
            else if (seconds == 5) {
                t5.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t5);
            }
            else if (seconds == 6) {
                t6.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t6);
            }
            else if (seconds == 7) {
                t7.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t7);
            }
            else if (seconds == 8) {
                t8.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t8);
            }
            else if (seconds == 9) {
                t9.setPosition((cols * 32) - 33, 32*(rows+0.5) + 16);
                window.draw(t9);
            }
        }
        else {
            string cseconds = to_string(seconds);
            int offset3 = 0;
            for (int i = 0; i < cseconds.size(); i++) {
                if (cseconds[i] == '0') {
                    t0.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t0);
                    offset3 += 21;
                }
                else if (cseconds[i] == '1') {
                    t1.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t1);
                    offset3 += 21;
                }
                else if (cseconds[i] == '2') {
                    t2.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t2);
                    offset3 += 21;
                }
                else if (cseconds[i] == '3') {
                    t3.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t3);
                    offset3 += 21;
                }
                else if (cseconds[i] == '4') {
                    t4.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t4);
                    offset3 += 21;
                }
                else if (cseconds[i] == '5') {
                    t5.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t5);
                    offset3 += 21;
                }
                else if (cseconds[i] == '6') {
                    t6.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t6);
                    offset3 += 21;
                }
                else if (cseconds[i] == '7') {
                    t7.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t7);
                    offset3 += 21;
                }
                else if (cseconds[i] == '8') {
                    t8.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t8);
                    offset3 += 21;
                }
                else if (cseconds[i] == '9') {
                    t9.setPosition((cols * 32) - 54 + offset3, 32 * (rows + 0.5) + 16);
                    window.draw(t9);
                    offset3 += 21;
                }
            }

        }

        window.display();
        if (calln == true) {
            if (ldrclk == true) {
                float timep = mainclock.gettotalseconds();
                int timeaj = static_cast<int>(timep);
                leaderboard(plyrname,timeaj,rows, cols, false);
                ldron = false;
                ldrclk = false;
                calln = false;
            }
            else {
                float timep = mainclock.gettotalseconds();
                int timeaj = static_cast<int>(timep);
                leaderboard(plyrname,timeaj,rows, cols, false);
                ldron = false;
                clockpaused = false;
                mainclock.resume();
                calln = false;
            }
        }
        if (callw == true) {
            float timep = mainclock.gettotalseconds();
            int timeaj = static_cast<int>(timep);
            leaderboard(plyrname,timeaj,rows, cols, true);
            ldron = false;
            callw = false;
        }

    }
}

int main() {
    ifstream file("files/config.cfg");
    string cols;
    string rows;
    string mines;
    getline(file, cols);
    getline(file, rows);
    getline(file, mines);
    int row_num = stoi(rows);
    int col_num = stoi(cols);
    int bomb_num = stoi(mines);
    int windowheight = (row_num*32) + 100;
    int windowwidth = col_num*32;
    int gameheight = (row_num*32) + 100;
    int gamewidth = col_num*32;

    sf::RenderWindow window(sf::VideoMode(windowwidth, windowheight), "Minesweeper");
    string playername;
    int x = titlescreen(window, windowwidth, windowheight, playername);
    if (x == 1) {
        sf::RenderWindow gwindow(sf::VideoMode(gamewidth, gameheight), "Minesweeper");
        gameboard z(col_num, row_num, bomb_num);
        z.createarray();
        z.findnearby();
        gamescreen(gwindow, gamewidth, gameheight, z, playername);
    }

    return 0;
}