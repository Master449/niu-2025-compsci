<?php /*
    
    CSCI 466 Group Project

    Authors:
       Sami Rezae         Z1920718   
       Bailey Appelhans   Z1759158
       Gerald Ellsworth   Z1885378
       David Flowers II   Z1942130

    Date: 11/30/2022

    This is the main page for our CSCI 466 Group Project. This page will be used to display the
    products in a list here. The products are only displayed if they are in stock and the ID is
    not 0. The products are displayed in a table with the product name, price, and quantity.

*/ ?>

<html>
    <head>
        <title>Assignment 9</title>
        <link rel="stylesheet" href="css/styles.css">
    </head>

    <body>
        <div id="nav">
            <img src="images/logo.png">
            <ul>
                <li><a href="#"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 576 512"><path d="M575.8 255.5c0 18-15 32.1-32 32.1h-32l.7 160.2c0 2.7-.2 5.4-.5 8.1V472c0 22.1-17.9 40-40 40H456c-1.1 0-2.2 0-3.3-.1c-1.4 .1-2.8 .1-4.2 .1H416 392c-22.1 0-40-17.9-40-40V448 384c0-17.7-14.3-32-32-32H256c-17.7 0-32 14.3-32 32v64 24c0 22.1-17.9 40-40 40H160 128.1c-1.5 0-3-.1-4.5-.2c-1.2 .1-2.4 .2-3.6 .2H104c-22.1 0-40-17.9-40-40V360c0-.9 0-1.9 .1-2.8V287.6H32c-18 0-32-14-32-32.1c0-9 3-17 10-24L266.4 8c7-7 15-8 22-8s15 2 21 7L564.8 231.5c8 7 12 15 11 24z"/></svg>Home</a></li>
                <li><a href="pages/account.php"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 448 512"><path d="M224 256c70.7 0 128-57.3 128-128S294.7 0 224 0S96 57.3 96 128s57.3 128 128 128zm-45.7 48C79.8 304 0 383.8 0 482.3C0 498.7 13.3 512 29.7 512H418.3c16.4 0 29.7-13.3 29.7-29.7C448 383.8 368.2 304 269.7 304H178.3z"/></svg>Account</a></li>
                <li><a href="pages/cart.php"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 576 512"><path d="M24 0C10.7 0 0 10.7 0 24S10.7 48 24 48H76.1l60.3 316.5c2.2 11.3 12.1 19.5 23.6 19.5H488c13.3 0 24-10.7 24-24s-10.7-24-24-24H179.9l-9.1-48h317c14.3 0 26.9-9.5 30.8-23.3l54-192C578.3 52.3 563 32 541.8 32H122l-2.4-12.5C117.4 8.2 107.5 0 96 0H24zM176 512c26.5 0 48-21.5 48-48s-21.5-48-48-48s-48 21.5-48 48s21.5 48 48 48zm336-48c0-26.5-21.5-48-48-48s-48 21.5-48 48s21.5 48 48 48s48-21.5 48-48z"/></svg>Cart</a></li>
            </ul>
        </div>
            <!--
                The table below should be able to be easily implemented
                with a foreach loop after a query. The query should return
                return the image, name, description and price of each item
            -->
        <div id="content">
            <div id="title"><h1>Welcome to Placeholder Mart</h1>
            <?php
            session_start();
            if (isset($_SESSION['user_id']) && !(isset($_SESSION['employee']))) {
                echo "<h4>Welcome back " . $_SESSION['first_name'] . " " . $_SESSION['last_name'] . ".</h4>";;
            } else if (isset($_SESSION['employee'])) {
                echo "<h4>Click <a href=\"pages/employee.php\">Here</a> for the Employee Dashboard</h4>";
            } else {
                echo "<h4>We got groceries or something.</h4></div>";
            }
            ?>
            <div id="products">
            <?php
                // Database configuration
                include 'hidden.php';

                // try to connect to the database
                try {
                    $pdo = new PDO($dbname, $username, $password);
                }
                catch(PDOexception $e) {
                    echo "<p>Connection to database failed: ${$e->getMessage()}</p>\n";
                }

                // query the database
                try {
                    $query = "SELECT * FROM Inventory WHERE inv_stock > 0 AND inv_id > 0";
                    $rs = $pdo->query($query);
                    $rows = $rs->fetchAll(PDO::FETCH_BOTH);
                }
                catch(PDOexception $e) {
                    echo "<p>Query failed: ${$e->getMessage()}</p>\n";
                }

                echo "<table>\n";
                
                // print the products table
                foreach($rows as $row) {
                    echo "<tr>\n";
                    echo "<td><a href=\"pages/product.php?productID= $row[0] \"><img src=\"$row[4]\" alt=\" $row[1] \"></a></td>\n";
                                                    // this ?productID= part is sending the inv_id to the product page
                                                    // so that it can query the database for the product info
                    echo "<td><h3> $row[1] <h3> <br> <p></p></td>\n";
                    echo "<td><p id=\"price\"> $ $row[2] </td>\n";
                    echo "</tr>\n";
                }
                echo "</table>"?>
        </div>
    </div>


    </body>
</html>