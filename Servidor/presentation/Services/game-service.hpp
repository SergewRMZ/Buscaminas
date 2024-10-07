#ifndef GAME_SERVICE
#define GAME_SERVICE

#include "../Game/GameBoard.hpp"
#include "../Game/cronometer.cpp"
#include "file-service.hpp"

using namespace std;
class GameService {
  private:
    double gameTime;
    string difficulty;
    GameBoard *game;
    Chronometer chronometer;
    FileService fileService;

  public:
    vector<vector<string>> initGame (string difficulty);
    vector<vector<string>> revealCell (int row, int col);
    GameService () : game (nullptr),
      fileService("Records/easy.txt", "Records/medium.txt", "Records/hard.txt") {};

    bool verifyWin();
    bool verifyLose();
    void registerRecord();
    vector<string> getRanking();
};

#endif