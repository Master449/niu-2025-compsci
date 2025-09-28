/*
 * Maoyuan Sun
 * 10/12/2023
 * Winner Class, simply stores a world series winner, and the year they won
 */
public class Winner {
    private String team;
    private int year;

    private Winner() {
        /*
         * Make default constructor private so programers who use this
         * class are forced to use the constructor that requires them
         * to provide both the team name and year
         */
    }

    public Winner(String team, int year) {
        this.team = team;
        this.year = year;
    }

    public int getYear() {
        return year;
    }

    public String getTeam() {
        return team;
    }
}