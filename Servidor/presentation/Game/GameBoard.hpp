#ifndef GAMEBOARD_H
#define GAMEBOARD

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
class GameBoard {
  private: 
    vector<vector<int>> board;
    vector<vector<string>> visibleBoard;
    vector<vector<int>> directions;
    vector<pair<int, int>> minesCoords;
    void updateCells(int row, int col);
    void gameOver();
    int getRandomNumber(int max);
    bool verifyLimits(int row, int col);
    int rows;
    int cols;
    int mines;
    int countCells;

  public:
    GameBoard(int mines, int rows, int cols);
    void generateGame();
    void revealCell(int row, int col);
    void showBoard();
    void verJuego();
    void IA();
    vector<vector<string>> getBoard() const;

};

#endif