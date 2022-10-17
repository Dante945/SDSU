import java.security.SecureRandom;
import java.util.Random;

public class LinkedList {
    Node headNode;

    public void addHeadNode(int x, int y) {

        Node oNode = new Node();

        oNode.xPosition = x;
        oNode.yPosition = y;

        oNode.nextNode = headNode;
        headNode = oNode;
    }

    public Node removeHeadNode() {

        Node tempNode;
        tempNode = headNode;
        if (headNode != null) {
            headNode = headNode.nextNode;
        }

        return tempNode;

    }

    Random orand = new Random();
    SecureRandom orand1 = new SecureRandom();
}

