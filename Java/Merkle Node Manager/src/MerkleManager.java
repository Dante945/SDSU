import java.util.Scanner;


public class MerkleManager {

    Scanner sc= new Scanner(System.in);

    public static volatile String uEntered;
    public static String eMerkleRoot;
    public static String merkleRoot = null;
    public static int strikes = 0;

   public void manage(){
    Util oUtil1 = new Util();
    eMerkleRoot = oUtil1.promptUser("Enter the expected merkle root: ");

       MerkleThread oMerkleThread1 = new MerkleThread();
       MonitorThread oMonitorThread1 = new MonitorThread();
       RogueThread oRogueThread1 = new RogueThread();

       Thread oThread1 = new Thread(oMerkleThread1);
       Thread oThread2 = new Thread(oMonitorThread1);
       Thread oThread3 = new Thread(oRogueThread1);

       oThread1.start();
       oThread2.start();
       oThread3.start();

       while(true){
           uEntered = oUtil1.promptUser("Enter a word: ");
       }
   }
   public static synchronized String grabWord(){
       String temp;
       temp = uEntered;
       uEntered = null;
       return temp;
   }
}

