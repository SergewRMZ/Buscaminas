// import { envs } from './config/envs';
// import { ServerTCP } from './presentation/ServerTCP'

// const main = async () => {
//   const server = new ServerTCP(envs.PORT);
//   server.start();
// }

// (async () => {
//   main();
// })();

import { GameBoard } from './presentation/board/GameBoard';

const gameBoard = new GameBoard({
  mines: 10,
  cols: 9,
  rows: 9
});

gameBoard.generateGame();
gameBoard.showBoard();
