import { envs } from './config/envs';
import { ServerTCP } from './presentation/ServerTCP'

const main = async () => {
  const server = new ServerTCP(envs.PORT);
  server.start();
}

(async () => {
  main();
})();