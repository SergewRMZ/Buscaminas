#include "GameBoard.hpp"

GameBoard::GameBoard(int mines, int rows, int cols) 
  : mines(mines), rows(rows), cols(cols),
    board(rows, vector<int>(cols, 0)),
    countCells((rows * cols) - mines),
    visibleBoard(rows, vector<string>(cols, "-")),
    directions{{-1, -1}, {-1, 0}, {-1, 1},
                {0, -1}, {0, 1},
                {1, -1}, {1, 0}, {1, 1}}
{
  srand(static_cast<unsigned int>(time(0)));
}

int GameBoard::getRandomNumber(int max) {
  return std::rand() % max;
}

void GameBoard:: generateGame () {
  int minesPlaced = 0;
  while (minesPlaced < this->mines) {
    int row = getRandomNumber(this->rows);
    int col = getRandomNumber(this->cols);
    int i, j = 0;
    if (this->board[row][col] != -1) {
      this->board[row][col] = -1;
      minesPlaced++;
      this->minesCoords.push_back({ row, col });
      this->updateCells(row, col);
    }
  }
}

void GameBoard::updateCells(int row, int col) {
  for (const auto& direction : directions) {
    int newRow = row + direction[0];
    int newCol = col + direction[1];

    if (verifyLimits(newRow, newCol)) {
        if (board[newRow][newCol] != -1) {
            board[newRow][newCol]++;
        }
    }
  }
}

bool GameBoard::verifyLimits(int row, int col) {
    return (row >= 0 && row < rows) && (col >= 0 && col < cols);
}

void GameBoard::gameOver () {
  for (const auto &mine: this->minesCoords) {
    int row = mine.first;
    int col = mine.second;
    this->visibleBoard[row][col] = "-1";
  }

  cout << "GAME OVER!" << endl;
  // exit(EXIT_SUCCESS);
}

void GameBoard::revealCell(int row, int col) {
  // Comprueba si la celda ya está abierta
  if (visibleBoard[row][col] != "-") return; 
  int data = board[row][col];

  // Comprueba si hay una mina
  if (data == -1) {
    gameOver();
  } 
  
  else {
    visibleBoard[row][col] = data == 0 ? "0" : to_string(data);
    this->countCells--;
    cout << "Reduce a " << this->countCells << endl; 
    if (data == 0) {
      vector<pair<int, int>> stack = {{row, col}};

      while (!stack.empty()) {
        auto [currentRow, currentCol] = stack.back();
        stack.pop_back();

        for (const auto& direction : directions) {
          int newRow = currentRow + direction[0];
          int newCol = currentCol + direction[1];

          if (verifyLimits(newRow, newCol) && visibleBoard[newRow][newCol] == "-") {
            if (board[newRow][newCol] != -1) {
              visibleBoard[newRow][newCol] = to_string(board[newRow][newCol]);
              this->countCells--;
            }

            if (board[newRow][newCol] == 0) 
              stack.push_back({newRow, newCol});
          }
        }
      }
    }
  }
  cout << "Contador celdas: " << this->countCells << endl;
  if (this->countCells == 0) {
    cout << "¡Felicidades, HAS GANADO!" << endl;
  }
}

void GameBoard::verJuego () {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << board[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}

void GameBoard::showBoard() {
  for (int i = 0; i < rows; i ++) {
    for (int j = 0; j < cols; j++) {
      cout << this->visibleBoard[i][j] << "\t";
    }

    cout << endl;
  }
}

void GameBoard::IA() {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (board[i][j] != -1) {  // Si no es una mina, revela la celda
        revealCell(i, j);
      }
    }
  }
}

vector<vector<string>> GameBoard::getBoard () const { 
  return this->visibleBoard;
}