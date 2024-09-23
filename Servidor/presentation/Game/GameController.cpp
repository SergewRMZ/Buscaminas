#include "GameController.hpp"
#include <nlohmann/json.hpp>

GameController::GameController () {}

string GameController::initGame(string difficulty) {
  auto board = this->gameService.initGame(difficulty);
  if (!board.empty()) {
    string boardJSON = this->boardToJSON(board);
    return "{\"status\": \"success\", \"message\": \"Juego iniciado en dificultad " + difficulty + "\", \"board\": " + boardJSON + "}\n";
  } 

  else {
      return "{\"status\": \"error\", \"message\": \"Error al iniciar el juego.\"}\n";
  }
}

string GameController::revealCell(int row, int col) {
  auto board = this->gameService.revealCell(row, col);
  if (!board.empty()) {
    string boardJSON = this->boardToJSON(board);
    return "{\"status\": \"success\", \"board\": " + boardJSON + "}\n";
  }
  
  else {
      return "{\"status\": \"error\", \"message\": \"Error al intentar destapar la celda.\"}\n";
  }
}

string GameController::boardToJSON(const vector<vector<string>> &board) {
  nlohmann::json jsonBoard = board;
  return jsonBoard.dump();
}