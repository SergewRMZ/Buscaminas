#include "./presentation/Game/GameBoard.h"

using namespace std;

int main () {
  GameBoard game(10, 9, 9);
  game.generateGame();
  game.verJuego();

  cout << "Buscaminas, ingresa las celdas para destapar (fila, columna)" << endl;
  unsigned int row, col;
  
  for (;;) {
    game.IA(); 
    // game.showBoard();
    // cin >> row >> col;

    // if (row >= 9 || col >= 9) {
    //   cout << "Fuera de Rango";
    //   continue;
    // }

    // game.revealCell(row, col);
    break;
  }
  
  game.showBoard();
}