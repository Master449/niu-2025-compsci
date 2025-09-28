/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 5                  Fall 2023    *
 *                                                                      *
 * App Name: stalker                                                    *
 *                                                                      *
 * Class Name: Faction.java                                             *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 11/03/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Model to hold the faction information and images.           *
 *                                                                      *
 ************************************************************************/
package edu.niu.android.stalker;

public class Faction {
    private String factionName;
    private int factionImageID;
    private String factionInformation;

    // Constructor
    Faction(String name, String info, int image) {
        factionName = new String(name);
        factionInformation = new String(info);
        factionImageID = image;
    }

    // Setters
    public void setFactionName(String s) { factionName = new String(s); }
    public void setFactionInformation(String s) { factionInformation = new String(s); }
    public void setFactionImageID(int n) { factionImageID = n; }

    // Getters
    public String getFactionName() { return factionName; }
    public String getFactionInformation() { return factionInformation; }
    public int getFactionImageID() { return factionImageID; }

}
