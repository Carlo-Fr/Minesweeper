//
// Created by carlo on 4/9/2024.
//

#ifndef MINESWEEPER_GAMEBOARD_H
#define MINESWEEPER_GAMEBOARD_H

#endif //MINESWEEPER_GAMEBOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
struct tile {
    bool revealed = false;
    bool flag = false;
    bool mine = false;
    int nearby = 0;
};

class gameboard {
public:
    bool winlose;
    bool mineclicked;
    bool mineclickable = true;
    bool boardclickable = true;
    int cols;
    int rows;
    int bombs;
    int mine_counter;
    vector<vector<tile*>> boardarray;
public:
    gameboard(int col, int row, int bomb) {
        cols = col;
        rows = row;
        bombs = bomb;
        mine_counter = 0;
    }
    void createarray() {
        boardarray.resize(cols, vector<tile*>(rows));
        for (int i = 0; i < cols; i++) {
            for (int k = 0; k < rows; k++) {
                boardarray[i][k] = new tile();
            }
        }
        while (mine_counter < bombs) {
            int colrand = rand() % cols;
            int rowrand = rand() % rows;
            if (boardarray[colrand][rowrand]->mine == false) {
                boardarray[colrand][rowrand]->mine = true;
                mine_counter++;
            }
        }
    }
    void resetarray() {
        vector<vector<tile*>> nboardarray;
        mine_counter = 0;
        nboardarray.resize(cols, vector<tile*>(rows));
        for (int i = 0; i < cols; i++) {
            for (int k = 0; k < rows; k++) {
                nboardarray[i][k] = new tile();
            }
        }
        while (mine_counter < bombs) {
            int colrand = rand() % cols;
            int rowrand = rand() % rows;
            if (nboardarray[colrand][rowrand]->mine == false) {
                nboardarray[colrand][rowrand]->mine = true;
                mine_counter++;
            }
        }
        boardarray = nboardarray;
    }
    void findnearby() {
        for (int i = 0; i < cols; i++) {
            for (int k = 0; k < rows; k++) {
                if (i == 0 && k == 0) {
                    int count = 0;
                    if (boardarray[1][0]->mine) {
                        count ++;
                    }
                    if (boardarray[1][1]->mine) {
                        count ++;
                    }
                    if (boardarray[0][1]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else if (i == cols - 1 && k == 0) {
                    int count = 0;
                    if (boardarray[i - 1][0]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][1]->mine) {
                        count ++;
                    }
                    if (boardarray[i][1]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else if (i == 0 && k == rows - 1) {
                    int count = 0;
                    if (boardarray[i][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else if (i == cols - 1 && k == rows -1) {
                    int count = 0;
                    if (boardarray[i - 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k]->mine) {
                        count ++;
                    }
                    if (boardarray[i][k - 1]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else if (i == 0) {
                    int count = 0;
                    if (boardarray[i][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else if (i == cols - 1) {
                    int count = 0;
                    if (boardarray[i][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else if (k == 0) {
                    int count = 0;
                    if (boardarray[i + 1][k]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i][k + 1]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else if (k == rows -1) {
                    int count = 0;
                    if (boardarray[i + 1][k]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i][k - 1]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
                else {
                    int count = 0;
                    if (boardarray[i + 1][k]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i][k - 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i + 1][k + 1]->mine) {
                        count ++;
                    }
                    if (boardarray[i - 1][k + 1]->mine) {
                        count ++;
                    }
                    boardarray[i][k]->nearby = count;
                }
            }
        }
    }
    void Printboard() {
        for (int k = 0; k < rows; k ++) {
            for (int i = 0; i < cols; i ++) {
                if (boardarray[i][k]->mine == true) {
                    cout << "x ";
                }
                else {
                    int num = boardarray[i][k]->nearby;
                    cout << num << " ";
                }
            }
            cout << endl;
        }
    }
    int getcols() {
        return cols;
    }
    int getrows() {
        return rows;
    }



};
