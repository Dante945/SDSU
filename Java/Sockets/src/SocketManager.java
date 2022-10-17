import java.util.Scanner;

public class SocketManager {
    public static void main(String[] args) {

        System.out.println("Enter port for this server to listen on: ");
        int iPort = new Scanner(System.in).nextInt();

        System.out.println("Enter IP address of server to connect to: ");
        String sOtherServerIP = new Scanner(System.in).nextLine();

        System.out.println("Enter port of server to connect to: ");
        int iOtherServerPort = new Scanner(System.in).nextInt();

        SocketServer oServer = new SocketServer(iPort);
        Thread oServerThread = new Thread(oServer);
        oServerThread.start();


        SocketClient oClient = new SocketClient();
        while(true){

            System.out.println("Enter 3 numbers separated by commas: ");
            String sMessage = new Scanner(System.in).nextLine();

            String sReplyFromServer = oClient.connectForOneMessage(sOtherServerIP, iOtherServerPort, sMessage);

            System.out.println("[client] Server reply: " + sReplyFromServer);

        }


    }
}

