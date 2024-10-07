#include "GameController.hpp"

GameController::GameController () {}
string GameController::initGame(string difficulty) {
  auto board = this->gameService.initGame(difficulty);
  nlohmann::json response;

  if (!board.empty()) {
    response["status"] = "success";
    response["mode"] = difficulty;
    response["board"] = board;
  }

  else {
    response["status"] = "error";
    response["message"] = "Error al iniciar el juego.";
  }
  return response.dump() + "\n";
}

string GameController::revealCell(int row, int col) {
  auto board = this->gameService.revealCell(row, col);
  nlohmann:: json response;

  if (!board.empty()) {
    response["status"] = "success";
    response["board"] = board;

    if (this->gameService.verifyWin()) {
      response["win"] = true;
      this->gameService.registerRecord(); // Solicitar escribir el récord.
      cout << "Has ganado" << endl;
    }

    if (this->gameService.verifyLose()) {
      response["lose"] = true;
      cout << "Has perdido" << endl;

    }
  }
  
  else {
    response["status"] = "error";
    response["message"] = "Error al intentar destapar la celda.";
  }
  
  return response.dump() + "\n";
}

string GameController:: getRanking () {
  vector<string> ranking = this->gameService.getRanking();
  nlohmann::json response;

  if (!ranking.empty()) {
    response["status"] = "success";
    response["ranking"] = ranking;
  }

  else {
    response["status"] = "error";
    response["message"] = "Error al obtener el ranking del juego.";
  }
  return response.dump() + "\n";
}

string GameController::boardToJSON(const vector<vector<string>> &board) {
  nlohmann::json jsonBoard = board;
  return jsonBoard.dump();
}