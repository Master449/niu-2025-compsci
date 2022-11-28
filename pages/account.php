<?php /*
    
    CSCI 466 Group Project

    Authors:
       Sami Rezae         Z1920718   
       Bailey Appelhans   Z1759158
       Gerald Ellsworth   Z1885378
       David Flowers II   Z1942130

    Date: 11/30/2022

    This is the login / logout page for the Users. If the user is currently logged in,
    it will display the logout button, otherwise it will display the login form.

    After successful logon it will send the customer to the home page.
    Successful employee login will send the employee to the employee dashboard.

    Some accounts to test with:
       Employee:  David Flowers
            username: 40  
            password: password

       Customer:  John Smith
            username: john@email.com 
            password: password1

    There are more accounts however, they are located in the database and SQL script.

    Session Variables Quick Reference:
        ['loggedIn']        Boolean     If a User is logged in
        ['customer']        Boolean     If a User is a customer
        ['employee']        Boolean     If a User if an Employee
        ['user_id']         String      Stores their user_id
        ['first_name']      String      Stores their First Name
        ['last_name']       String      Stored their Last Name
        ['email_addr']      String      Stored their Email Address


*/?>

<html>
    <head>
        <title>Assignment 9</title>
        <link rel="stylesheet" href="../css/styles.css">
    </head>

    <body>
        <div id="nav">
            <img src="../images/logo.png">
            <ul>
                <li><a href="../index.php"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 576 512"><path d="M575.8 255.5c0 18-15 32.1-32 32.1h-32l.7 160.2c0 2.7-.2 5.4-.5 8.1V472c0 22.1-17.9 40-40 40H456c-1.1 0-2.2 0-3.3-.1c-1.4 .1-2.8 .1-4.2 .1H416 392c-22.1 0-40-17.9-40-40V448 384c0-17.7-14.3-32-32-32H256c-17.7 0-32 14.3-32 32v64 24c0 22.1-17.9 40-40 40H160 128.1c-1.5 0-3-.1-4.5-.2c-1.2 .1-2.4 .2-3.6 .2H104c-22.1 0-40-17.9-40-40V360c0-.9 0-1.9 .1-2.8V287.6H32c-18 0-32-14-32-32.1c0-9 3-17 10-24L266.4 8c7-7 15-8 22-8s15 2 21 7L564.8 231.5c8 7 12 15 11 24z"/></svg>Home</a></li>
                <li><a href="#"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 448 512"><path d="M224 256c70.7 0 128-57.3 128-128S294.7 0 224 0S96 57.3 96 128s57.3 128 128 128zm-45.7 48C79.8 304 0 383.8 0 482.3C0 498.7 13.3 512 29.7 512H418.3c16.4 0 29.7-13.3 29.7-29.7C448 383.8 368.2 304 269.7 304H178.3z"/></svg>Account</a></li>
                <li><a href="cart.php"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 576 512"><path d="M24 0C10.7 0 0 10.7 0 24S10.7 48 24 48H76.1l60.3 316.5c2.2 11.3 12.1 19.5 23.6 19.5H488c13.3 0 24-10.7 24-24s-10.7-24-24-24H179.9l-9.1-48h317c14.3 0 26.9-9.5 30.8-23.3l54-192C578.3 52.3 563 32 541.8 32H122l-2.4-12.5C117.4 8.2 107.5 0 96 0H24zM176 512c26.5 0 48-21.5 48-48s-21.5-48-48-48s-48 21.5-48 48s21.5 48 48 48zm336-48c0-26.5-21.5-48-48-48s-48 21.5-48 48s21.5 48 48 48s48-21.5 48-48z"/></svg>Cart</a></li>
            </ul>
        </div>
        <div id="content">
            <div id="title"><h1>Your Account</h1></div>
            <div id="account">
                <?php
                // if the user is logged in, display their account information
                include "../hidden.php";
                session_start();

                if (isset($_SESSION['user_id'])) {
                    // logout button
                    echo "<form action=\"account.php\" method=\"post\">";
                    echo "<input type=\"submit\" name=\"Logout\" value=\"Logout\" class=\"button\">";
                    echo "</form>";
                } else {
                    echo "<form action=\"account.php\" method=\"post\">";
                    echo "<label for=\"user\">Username:</label>";
                    echo "<input type=\"text\" id=\"user\" name=\"user\"><br><br>";

                    echo "<label for=\"pass\">Password:</label>";
                    echo "<input type=\"password\" id=\"password\" name=\"password\"> <br><br>";

                    echo "<label for=\"employee\">Employee Login?</label>";
                    echo "<input type=\"checkbox\" id=\"employee\" name=\"employee\" value=\"emp\"><br>";
                    echo "<input type=\"submit\" value=\"Login\" class=\"button\">";
                    echo "</form>";
                }

                try {
                    $pdo = new PDO($dbname, $username, $password);
                }
                catch(PDOexception $e) {
                    echo "<p>Connection to database failed: ${$e->getMessage()}</p>\n";
                }

                // If the checkbox is checked, then the user is an employee
                // connect to the employee table
                if (isset($_POST['employee'])) {

                    // ------------------- EMPLOYEE LOGIN -------------------------
                    // Employee logon should use their employee ID as the username
                    $sql = "SELECT * FROM User WHERE user_id = :user AND password = :pass";
                    $stmt = $pdo->prepare($sql);
                    $stmt->execute(array(':user' => $_POST['user'], ':pass' => $_POST['password']));
                    $row = $stmt->fetch(PDO::FETCH_ASSOC);

                    if ($row === false) {
                        echo "<p>Incorrect username or password</p>";
                    }
                    else {
                        echo "<p>Logged in as employee</p>";
                        $_SESSION['loggedIn'] = true;
                        $_SESSION['employee'] = true;
                        $_SESSION['user_id'] = $row['user_id'];
                        $_SESSION['first_name'] = $row['f_name'];
                        $_SESSION['last_name'] = $row['l_name'];
                        header("Location: employee.php");
                    }
                } else {

                    // ----------------- CUSTOMER LOGIN -----------------
                    /* This complicated query is because the customer should login with their email address */
                     
                    $sql = "SELECT * FROM User INNER JOIN Customer ON Customer.id_user = User.user_id WHERE email_addr = :user AND password = :pass";
                    $stmt = $pdo->prepare($sql);
                    $stmt->bindParam(':user', $_POST['user']);
                    $stmt->bindParam(':pass', $_POST['password']);
                    $stmt->execute();
                    $row = $stmt->fetch(PDO::FETCH_ASSOC);

                    // store the customer id in a session variable
                    if ($row === false) {
                        // sucks to suck
                    }
                    else {
                        $_SESSION['loggedIn'] = true;
                        $_SESSION['customer'] = true;
                        $_SESSION['user_id'] = $row['user_id'];
                        $_SESSION['first_name'] = $row['f_name'];
                        $_SESSION['last_name'] = $row['l_name'];
                        $_SESSION['email_addr'] = $row['email_addr'];
                        // back to the home page
                        header("Location: ../index.php");

                    }
                }

                if (isset($_POST['Logout'])) {
                    session_destroy();
                    header("Location: ../index.php");
                }
                ?>
                
            </div>
            <h2 style="text-align: center; font-size: 16px;">If you get redirected to the home page, you have successfully logged in / out.</h2><br><br>
            <?php
            /* 
               This query is for the Customer logon information.
               SELECT * FROM User INNER JOIN Customer ON Customer.id_user = User.user_id;
               Use the customer email, and password.

               This query is for the employee logon information.
               SELECT * FROM User INNER JOIN Employee ON User.user_id = Employee.id_user;;
               Use the employee ID, and password. */
            ?>
        </div>


    </body>
</html>