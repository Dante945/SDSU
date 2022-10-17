import java.security.SecureRandom;
import java.util.Scanner;

public class GameGrid {
    public void run() {
        Scanner sc = new Scanner(System.in);
        LinkedList oLinkedList = new LinkedList();
        int choice;
        int[][] aiGrid = new int[10][10];
        SecureRandom oRand = new SecureRandom();
        int iWallChance = 10;

        for (int y = 0; y < aiGrid[0].length; y++) {
            for (int x = 0; x < aiGrid.length; x++) {

                int iChance = oRand.nextInt(100);

                if (iChance < iWallChance) {
                    aiGrid[x][y] = 1;
                } else {
                    aiGrid[x][y] = 0;
                }
            }
        }
        aiGrid[0][0] = 0;
        int iUserRow = 0;
        int iUserCol = 0;

        boolean exit = false;
        while(!exit){
            oLinkedList.addHeadNode(iUserCol, iUserRow);
            System.out.println("Press 1 to move right");
            System.out.println("Press 2 to move down");
            choice = sc.nextInt();

            if(choice == 1){
                iUserRow++;
                if(aiGrid[iUserRow][iUserCol] == 1){
                    System.out.println("You Lose!");
                    exit = true;
                }
            }
            if(choice == 2){
                iUserCol++;
                if(aiGrid[iUserRow][iUserCol] == 1){
                    System.out.println("You Lose!");
                    exit = true;
                    }
                }
                if(iUserCol == 9 || iUserRow == 9){
                    oLinkedList.addHeadNode(iUserCol, iUserRow);
                    System.out.println("You win!");
                    exit = true;
                }
            }

        int moves= 0;
        while(oLinkedList.headNode != null){
            Node temp;
            temp = oLinkedList.removeHeadNode();
            aiGrid[temp.yPosition][temp.xPosition] = 8;
            moves++;
        }

        for (int y=0; y< aiGrid[0].length; y++) {
            for (int x = 0; x < aiGrid.length; x++) {
                    System.out.print(aiGrid[x][y] + " ");
            }
            System.out.println();
        }

        System.out.println();
        System.out.println("Number of moves: " + moves);
        }
    }
