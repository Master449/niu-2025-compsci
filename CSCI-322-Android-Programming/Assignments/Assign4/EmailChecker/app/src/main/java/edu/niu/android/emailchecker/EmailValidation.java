/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 4                  Fall 2023    *
 *                                                                      *
 * App Name: Email Checker                                              *
 *                                                                      *
 * Class Name: EmailValidation.java                                     *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 10/20/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Model to validate and store email variables                 *
 *                                                                      *
 ************************************************************************/

package edu.niu.android.emailchecker;

public class EmailValidation {
    private String email = new String();

    public EmailValidation() {
        email = new String("");
    }

    public EmailValidation(String e) {
        email = new String(e);
    }

    public void setEmail(String e) { email = new String(e); }
    public String getEmail() { return email; }

    public boolean checkValidity() {
        // Both of these return the index of the char
        // the dot gets the last index
        int atSign = email.indexOf('@');
        int domainDot = email.lastIndexOf('.');

        // Check if theres more than one @ sign
        int lastAtSign = email.lastIndexOf('@');

        // lastOf methods returns -1 if it is not found
        if (atSign == -1 || domainDot == -1)
            return false;

        // If there is only one @ these will be equal
        // there can be multiple dots though
        if (lastAtSign != atSign)
            return false;

        // And if the @ sign is a higher index
        // than the dot
        if (atSign > domainDot)
            return false;

        return true;
    }
}
