/**
 * MileTicket.java
 * 
 * Assignment 6
 * David Flowers II
 * Z1942130
 * 
 * Due 12/01/23
 */
 
public class MileTicket {
    private String destination;
    private int normalMiles;
    private int superSaverMiles;
    private int additionalMiles;
    private int startMonth;
    private int endMonth;

    // Private so it cannot be used without params
    private MileTicket() {}

    MileTicket(String DESTINATION, int NORMAL_MILES, int SUPER_SAVER_MILES, int ADDITIONAL_MILES, int START_MONTH, int END_MONTH) {
        destination = new String(DESTINATION);
        normalMiles = NORMAL_MILES;
        superSaverMiles = SUPER_SAVER_MILES;
        additionalMiles = ADDITIONAL_MILES;
        startMonth = START_MONTH;
        endMonth = END_MONTH;
    }

    // Getters
    public String getDestination() { return destination; }
    public int getNormalMiles() { return normalMiles; }
    public int getSuperSaverMiles() { return superSaverMiles; }
    public int getAdditionalMiles() { return additionalMiles; }
    public int getStartMonth() { return startMonth; }
    public int getEndMonth() { return endMonth; }

    // Override method to make sorting easier
    @Override
    public boolean equals(Object obj) {
        // Cast it to a MileTicket object, too lazy to deal with it otherwise
        if (this.normalMiles < ((MileTicket)obj).normalMiles) {
            return true;
        } else {
            return false;
        }
    }
}