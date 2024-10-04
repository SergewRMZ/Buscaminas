#include "game-service.hpp"

vector<vector<string>> GameService::initGame (string difficulty) {
  unsigned int mines, cols, rows;
  this->chronometer.start();
  this->difficulty = difficulty;

  if (difficulty == "easy") {
    mines = 10;
    cols = 9;
    rows = 9;
  }

  else if (difficulty == "normal") {
    mines = 40;
    cols = 16;
    rows = 16;
  }

  else if (difficulty == "hard") {
    mines = 99;
    cols = 30;
    rows = 16;
  }

  if (game != nullptr) {
    delete game;
  }

  game = new GameBoard(mines, rows, cols);
  this->game->generateGame();
  return this->game->getBoard();
}

vector<vector<string>> GameService::revealCell(int row, int col) {
  this->game->revealCell(row, col);
  if (this->game->win || this->game->lose) {
    duration<double> tiempo = this->chronometer.stop();
    this->gameTime = tiempo.count();
  }

  return this->game->getBoard();
}

void GameService::registerRecord () {
  this->fileService.writeRecord(this->difficulty, this->gameTime);
} 

bool GameService::verifyWin () {
  return this->game->win;
}

bool GameService::verifyLose () {
  return this->game->lose;
}


