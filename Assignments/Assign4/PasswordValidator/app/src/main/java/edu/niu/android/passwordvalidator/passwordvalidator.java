/************************************************************************
 *                                                                      *
 * CSCI 322/522              Assignment 4                  Fall 2023    *
 *                                                                      *
 * App Name: Password Validator                                         *
 *                                                                      *
 * Class Name: passwordvalidator.java                                   *
 *                                                                      *
 * Developer(s): Anthony Juarez                                         *
 *               David Flowers II                                       *
 *                                                                      *
 * Due Date: 10/20/23 by 11:59p                                         *
 *                                                                      *
 * Purpose: Model to validate and store password variables              *
 *                                                                      *
 ************************************************************************/


package edu.niu.android.passwordvalidator;

public class passwordvalidator {

    private String password = new String();

    public passwordvalidator()
    {
        password = new String("");
    }

    public void setPassword(String new_password)
    {
        password = new String(new_password);
    }

    public String getPassword()
    {
        return password;
    }

    public boolean check_password(String new_password)
    {
        // checking if the string passed in is less than or equal to 8 characters
        if (new_password.length() <= 8)
        {
            return false;
        }

        return true;
    }




}
