
public class LoShuClassTester {

    public static void main(String[] args) {

        LoShuMagic lsm = new LoShuMagic();

        int matrix[][] = new int[4][4];
        matrix[0][0] = 16;
        matrix[0][1] = 3;
        matrix[0][2] = 2;
        matrix[0][3] = 13;
        matrix[1][0] = 5;
        matrix[1][1] = 10;
        matrix[1][2] = 11;
        matrix[1][3] = 8;
        matrix[2][0] = 9;
        matrix[2][1] = 6;
        matrix[2][2] = 7;
        matrix[2][3] = 12;
        matrix[3][0] = 4;
        matrix[3][1] = 15;
        matrix[3][2] = 14;
        matrix[3][3] = 1;

        if(lsm.test(matrix) == true) {
            System.out.println("Test 1 passed");
        } else {
            System.out.println("Test 1 failed");
        }

        matrix[0][1] = 10;

        if(lsm.test(matrix) == true) {
            System.out.println("Test 2 passed");
        } else {
            System.out.println("Test 2 failed");
        }
    }
}