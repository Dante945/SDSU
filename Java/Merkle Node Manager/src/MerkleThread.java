import java.util.ArrayList;
public class MerkleThread implements Runnable
{
    public String sThreadName = "Merkle";
    public static volatile ArrayList<String> lstWords;
    private int iMerkleTreeInputs = 4;

    public void run()
    {
        Util oUtil = new Util();
        lstWords = new ArrayList();
        while(true)
        {
            oUtil.sleepRandomTime(sThreadName);
            String sNewWord = MerkleManager.grabWord();
            if(sNewWord != null)
            {
                System.out.println("Merkle grabbed a word!");
                lstWords.add(sNewWord);
                if(lstWords.size() == iMerkleTreeInputs) { MerkleManager.merkleRoot = oUtil.getMerkleRoot(lstWords);}
            }
        }
    }

}

