import net from 'net';

// SO_REUSEADDR YA ESTÁ CONFIGURADO.

export class ServerTCP {
  private clients: net.Socket[] = [];
  private readonly port: number;

  private readonly server = net.createServer((socket) => {
    console.log(`Cliente conectado: ${socket.remoteAddress}`);
    this.clients.push(socket);
    
    socket.on('data', (data) => {
      const mensaje = data.toString().trim();
      console.log('Mensaje recibido', mensaje);

    });

    socket.on('end', () => {
      console.log(`Cliente desconectado: ${socket.remoteAddress}`);
    });

    socket.on('error', (err) => {
      console.error(`Error en el socket ${err}`);
    });
  });

  constructor (port: number) {
    this.port = port;
  }

  async start () {
    const backlog = 5;
    this.server.listen(this.port, backlog, () => {
      console.log(`Servidor TCP escuchando en el puerto ${this.port}`);
    });
  }
}
