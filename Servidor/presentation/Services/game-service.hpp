#ifndef GAME_SERVICE
#define GAME_SERVICE

#include "../Game/GameBoard.hpp"
using namespace std;


class GameService {
  private:
    GameBoard *game;

  public:
    vector<vector<string>> initGame (string difficulty);
    vector<vector<string>> revealCell (int row, int col);
    GameService () : game (nullptr) {};
};

#endif