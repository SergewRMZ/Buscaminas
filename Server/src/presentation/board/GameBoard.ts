interface Options {
  mines: number;
  rows: number;
  cols: number;
}

type CellValue = string | number;

export class GameBoard {
  private board: number[][];
  private visibleBoard: CellValue[][];
  private rows: number;
  private cols: number;
  private mines: number;
  private directions: number[][];

  constructor (options: Options) {
    const { mines, rows, cols } = options;
    this.cols = cols;
    this.rows = rows;
    this.mines = mines; 
    this.board = Array.from({ length: rows }, () => Array(cols).fill(0));
    this.visibleBoard = Array.from({ length: rows }, () => Array(cols).fill('-'));
    this.directions = [
      [-1, -1], [-1, 0], [-1, 1], // Fila superior
      [0, -1], [0, 1], // Fila central
      [1, -1], [1, 0], [1, 1] // Fila inferior
    ]
  }

  public generateGame () {
    let minesPlaced = 0;
    while (minesPlaced < this.mines) {
      const row = this.getRandomNumber(this.rows);
      const col = this.getRandomNumber(this.cols);
      
      if (this.board[row][col] !== -1) {
        this.board[row][col] = -1; // Coloca mina
        minesPlaced++;
        this.updateCells(row, col);
      }
    }
  }

  private updateCells (row: number, col: number) {
    for (const[dx, dy] of this.directions) {
      const newRow = row + dx;
      const newCol = col + dy;

      if (this.verifyLimits(newRow, newCol)) {
        if (this.board[newRow][newCol] !== -1) {
          this.board[newRow][newCol]++;
        }
      }
    }
  }

  private verifyLimits (row: number, col: number): boolean {
    return ( (row >= 0 && row < this.rows) && (col >= 0 && col < this.cols) )
  }

  public revealCell (row: number, col: number) {
    // La celda está destapada.
    if (this.visibleBoard[row][col] !== '-') return; 
    const data = this.board[row][col];

    // La celda presionada es una mina
    if (data === -1) {
      this.visibleBoard[row][col] = '-1';
      console.log('Game Over!');
    } 
    
    else {
      this.visibleBoard[row][col] = data === 0 ? 0 : data;

      // Si la celda está vacía, algoritmo para destapar celdas adyacentes.
      if (data === 0) {
        const stack: [number, number][] = [[row, col]];

        while (stack.length) {
          const [currentRow, currentCol] = stack.pop()!;

          for (const [dx, dy] of this.directions) {
            const newRow = currentRow + dx;
            const newCol = currentCol + dy;
            
            // Verificar límites y que celda adyacente no esté tapada
            if (this.verifyLimits(newRow, newCol) && this.visibleBoard[newRow][newCol] === '-') {

              if (this.board[newRow][newCol] !== -1) {
                this.visibleBoard[newRow][newCol] = this.board[newRow][newCol];
              }

              // Si la celda vecina es un 0, entonces se destapa y continua apartir de ahí
              if (this.board[newRow][newCol] === 0) 
                stack.push([newRow, newCol]);
            }
          }
        } // While
      } // if
    } // else
  } // function: revealCell

  public showBoard () {
    for (let i = 0; i < this.rows; i++) {
      let rowString = '';  // Almacena la fila actual en formato de cadena
      for (let j = 0; j < this.cols; j++) {
        rowString += `${this.board[i][j]}\t`;  // Agrega cada elemento de la fila a la cadena
      }
      console.log(rowString.trim());  // Muestra la fila completa en la consola
    }
  }

  private getRandomNumber (max: number): number {
    return Math.floor(Math.random() * max);
  }


}