/*
 * David Flowers II
 * 10/20/2023
 * LoShuMagic class to test rows, cols, and diagonals for their sum
 */
public class LoShuMagic {
    public boolean test(int[][] ar) {
        // Adding them up on the assignment gave me 34
        // and were going to need it later
        final int PROPER_SUM = 34;

        // Check the rows and columns
        for (int i = 0; i < ar.length; i++) {

            // Initialize variables to hold the sum
            int rowSum = 0;
            int colSum = 0;

            // Loop through and add up the sums
            for (int j = 0; j < ar[i].length; j++) {
                rowSum += ar[i][j];
                colSum += ar[j][i];
            }

            // If the sums don't match, its not the Lo Shu Magic Square
            if (rowSum != PROPER_SUM || colSum != PROPER_SUM)
                return false;
        }

        // Check the top to bottom diagonal
        int topDiagSum = 0;
        int botDiagSum = 0;
        for (int i = 0; i < ar.length; i++ ) {
            topDiagSum += ar[i][i];
            botDiagSum += ar[i][ar.length - 1 - i];
        }

        return topDiagSum == PROPER_SUM && botDiagSum == PROPER_SUM;
    }
}
