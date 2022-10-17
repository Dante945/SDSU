public class RogueThread implements Runnable {
    public String sThreadName = "Rogue";
    public void run() {

        Util oUtil = new Util();

        while(true){
            oUtil.sleepRandomTime(sThreadName);

            if(MerkleManager.grabWord() != null){
                MerkleManager.strikes = MerkleManager.strikes + 1;
                String sNewWord = MerkleManager.grabWord();
                System.out.println("Rogue grabbed a work, STRIKE!");
            }
        }
    }
}
