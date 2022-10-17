public class MonitorThread implements Runnable {
    public String sThreadName = "Monitor";
    public void run(){
        while(true){
            if (MerkleManager.merkleRoot != null){
                if (MerkleManager.merkleRoot.equals(MerkleManager.eMerkleRoot)){
                    System.out.println("You win: " + MerkleManager.merkleRoot);
                }
                else{
                    System.out.println("You lost: " + MerkleManager.eMerkleRoot);
                }
                System.exit(0);
            }
            else if (MerkleManager.strikes == 3){
                System.out.println("3 strikes: you lost!");
                System.exit(0);

            }
            Util.sleep(1);
        }
    }
}
