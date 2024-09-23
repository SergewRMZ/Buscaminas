import modules.ClientServer;

public class App {
    public static void main (String[] args) {
        ClientServer client = new ClientServer();
        client.sendMessage("Hola Denia");
    }
}
