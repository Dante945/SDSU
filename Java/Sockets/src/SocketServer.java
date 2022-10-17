import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class SocketServer implements Runnable {

    private int thisServerPort;

    // constructor forces port to be passed in, and that is necessary
    // for startup of ServerSocket

    public SocketServer(int iPort){
        thisServerPort = iPort;
    }

    public void run() {

        try(ServerSocket oServerSocket = new ServerSocket(thisServerPort)){
            System.out.println("Server is listening on port " + thisServerPort);

            while(true){

                Socket oSocket = oServerSocket.accept();
                System.out.println("[server]: New client connected: " + oSocket.getRemoteSocketAddress());

                InputStream input = oSocket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input));

                OutputStream output = oSocket.getOutputStream();
                PrintWriter writer = new PrintWriter(output, true);

                String[] messageArray = new String[3];
                String sReceivedMessage = reader.readLine();
                messageArray = sReceivedMessage.split(",");



                int newMessage = Integer.parseInt(messageArray[0]) + Integer.parseInt(messageArray[1]) + Integer.parseInt(messageArray[2]);


                System.out.println("[server]: Server received message, sum of numbers: " + newMessage);
                writer.println("Server received your message");
                writer.flush();

            }
        }
        catch(IOException ex){

            System.out.println("[server]: Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}

