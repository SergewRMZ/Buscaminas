package modules;
import java.io.*;
import java.net.*;

public class ClientServer {
    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;
    private final int port = 5000;
    private final String host = "127.0.0.1";
    public ClientServer() { 
        try {
            socket = new Socket(this.host, this.port);
            System.out.println("Conectado al servidor " + this.host + ":" + this.port);   
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        }   catch (IOException e) {
            System.err.println("Error al conectar con el servidor: " + e.getMessage());
        }
    }
    
    public void sendMessage (String message) {
        out.println(message);
    }
}
