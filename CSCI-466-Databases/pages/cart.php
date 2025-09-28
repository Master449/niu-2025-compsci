<?php /*
    
    CSCI 466 Group Project

    Authors:
       Sami Rezae         Z1920718   
       Bailey Appelhans   Z1759158
       Gerald Ellsworth   Z1885378
       David Flowers II   Z1942130

    Date: 11/30/2022

*/?>
<style>
button {
  background-color: #D72638;
  color: white;
  font-size: 24px;
  border: none;
  border-radius: 5%;
  padding: 10px 20px;
  margin: 5% 0;
}
</style>
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
                <li><a href="account.php"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 448 512"><path d="M224 256c70.7 0 128-57.3 128-128S294.7 0 224 0S96 57.3 96 128s57.3 128 128 128zm-45.7 48C79.8 304 0 383.8 0 482.3C0 498.7 13.3 512 29.7 512H418.3c16.4 0 29.7-13.3 29.7-29.7C448 383.8 368.2 304 269.7 304H178.3z"/></svg>Account</a></li>
                <li><a href="#"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 576 512"><path d="M24 0C10.7 0 0 10.7 0 24S10.7 48 24 48H76.1l60.3 316.5c2.2 11.3 12.1 19.5 23.6 19.5H488c13.3 0 24-10.7 24-24s-10.7-24-24-24H179.9l-9.1-48h317c14.3 0 26.9-9.5 30.8-23.3l54-192C578.3 52.3 563 32 541.8 32H122l-2.4-12.5C117.4 8.2 107.5 0 96 0H24zM176 512c26.5 0 48-21.5 48-48s-21.5-48-48-48s-48 21.5-48 48s21.5 48 48 48zm336-48c0-26.5-21.5-48-48-48s-48 21.5-48 48s21.5 48 48 48s48-21.5 48-48z"/></svg>Cart</a></li>
            </ul>
        </div>
        <div id="content">
            <div id="title"><h1>Your Cart</h1></div>
            <?php
            include '../hidden.php';

            // Start Session
            session_start();

            // If the user is not logged in, redirect them to the login page
            if (!isset($_SESSION['loggedIn'])) {
                header("Location: account.php");
            }
            
            // Connect to the database
            try {
                $pdo = new PDO($dbname, $username, $password);
            }
            catch(PDOexception $e) {
                echo "<p>Connection to database failed: ${$e->getMessage()}</p>\n";
            }

            // Get the user's cart
            $query = "SELECT * FROM Cart INNER JOIN Inventory ON Cart.id_inv = Inventory.inv_id WHERE id_user = :user_id AND inv_id > 0;";
            $statement = $pdo->prepare($query);
            $statement->execute(array(':user_id' => $_SESSION['user_id']));
            $cart = $statement->fetchAll(PDO::FETCH_BOTH);

            // If the cart is empty, display a message
            if (empty($cart)) {
                echo "<p style=\"text-align: center;\">Your cart is empty.</p>";
            }

            // Otherwise, display the cart
            else {
                echo "<table style=\"margin: 0px auto; border-spacing: 50px; text-align: center;\">";
                echo "<tr><th>Product</th><th>Quantity</th><th>Price</th><th>Quantity</th></tr>";
                foreach ($cart as $item) {
                    echo "<tr>";
                    echo "<td><img src=\"${item['inv_image']}\" style=\"height: 100px;\"></img></td>";
                    echo "<td>${item['inv_name']}</td>";
                    echo "<td>$${item['inv_price']}</td>";
                    echo "<td>${item['quantity']}</td>";
                    // remove from cart
                    echo "<td><form action=\"cart.php\" method=\"post\">";
                    echo "<input type=\"hidden\" name=\"id\" value=\"${item['inv_id']}\">";
                    echo "<button type=\"submit\" value=\"Remove\">Remove</button>";
                    echo "</form></td>";
                    echo "</tr>";
                }
                // Total
                $query = "SELECT SUM(inv_price * quantity) AS total FROM Cart INNER JOIN Inventory ON Cart.id_inv = Inventory.inv_id WHERE id_user = :user_id AND inv_id > 0;";
                $statement = $pdo->prepare($query);
                $statement->execute(array(':user_id' => $_SESSION['user_id']));
                $total = $statement->fetch(PDO::FETCH_BOTH);

                $withTax = $total['total'] * 1.02;

                echo "<tr><td colspan=\"5\"><h2>Subtotal: $${total['total']}<br>Total (2% tax): $" . number_format($withTax, 2) . "</h2></td></td></tr>";
                echo "</table>";
            }

            echo "<center>";
            echo "<form action=\"cart.php\" method=\"post\">";
            echo "<button id=\"check\" type=\"submit\" name=\"checkout\">Checkout</button>";
            echo "</form>";
            echo "</center>";

            // Checkout button logic
            if (isset($_POST['checkout'])) {
                // Get the user's cart
                header("Location: checkout.php");
            }

            // If the user has submitted the form, remove the item from the cart
            // I could not get this to work normally, so I had to use a workaround
            // setting the current inventory id to 0
            // as the cart is displayed, it will only display inv_id > 0
            if (isset($_POST['id'])) {
                // Update the item to inv_id = 0
                $query = "UPDATE Cart SET id_inv = 0 WHERE id_user = :user_id AND id_inv = :inv_id;";
                $statement = $pdo->prepare($query);
                $statement->execute(array(':user_id' => $_SESSION['user_id'], ':inv_id' => $_POST['id']));

                // Refresh the page
                header("Location: cart.php");
            }
            ?>
    </div>


    </body>
</html>