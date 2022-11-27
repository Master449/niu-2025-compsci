<!--
    
    CSCI 466 Group Project

    Authors:
       Sami Rezae         Z1920718   
       Bailey Appelhans   Z1759158
       Gerald Ellsworth   Z1885378
       David Flowers II   Z1942130

    Date: 11/30/2022

-->

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
            <div id="title"><h1>Employee Dashboard</h1></div>
            <?php
            include '../hidden.php';
            session_start();

            // Check if the user is an employee, if not redirect to the home page
            if ($_SESSION['employee'] != true) {
                header("Location: ../index.php");
            }

            // Connect to the database
            try {
                $pdo = new PDO($dbname, $username, $password);
            }
            catch(PDOexception $e) {
                echo "<p>Connection to database failed: ${$e->getMessage()}</p>\n";
            }

            // Show who is logged in
            echo "<center><h2>Employee: " . $_SESSION['first_name'] . " " . $_SESSION['last_name'] . "</h2></center>\n";

            // Outer table
            echo "<table style=\"margin: 0px auto; border-spacing: 50px; text-align: center;\">";
            echo "<tr VALIGN=TOP>";
            echo "<td>";
            echo "<h2>Inventory</h2>\n";

            // Query the database for all products
            $sql = "SELECT inv_id, inv_name, inv_stock, inv_price FROM Inventory";
            $result = $pdo->query($sql);

            // Display the products in a table
            echo "<table style=\"border: 1px solid black; border-spacing: 10px;\">";
            echo "<tr><th>Product ID</th><th>Product Name</th><th>Price</th><th>Stock</tr>\n";
            foreach ($result as $row) {
                echo "<tr><td style=\"font-weight: bold; text-align: center;\">${row['inv_id']}</td><td>${row['inv_name']}</td><td>${row['inv_price']}</td><td style=\"text-align: right;\">${row['inv_stock']}</td></tr>\n";
            }
            echo "</table>\n";

            echo "</td>"; // End outer table row

            
            echo "<td>"; // Start outer table row
            echo "<h2>Orders</h2>\n";

            // Query the database for all orders
            $sql = "SELECT * FROM Orders";
            $result = $pdo->query($sql);

            // Orders table
            echo "<table style=\"border: 1px solid black; border-spacing: 10px;\">";
            echo "<tr><th>Order ID</th><th>Tracking Number</th><th>Process State</th><th>Order Date</th><th>User Email</th></tr>\n";

            foreach ($result as $row) {
                echo "<tr><td style=\"font-weight: bold; text-align: center;\">${row['order_no']}</td><td>${row['track_no']}</td><td>${row['process_state']}</td><td>${row['order_date']}</td><td>${row['user_email']}</td></tr>\n";
            }
            echo "</table>\n";

            // Form to change the process state of an Order
            ?>
            <h2>Update Order Status</h2>
            <form action="employee.php" method="post">
                <input type="text" name="order" placeholder="Order ID">
                <select name="process">
                    <option value="Processing">Processing</option>
                    <option value="Shipped">Shipped</option>
                    <option value="Delivered">Delivered</option>
                    <option value="Cancelled">Cancelled</option>
                </select>
                <input type="submit" value="Update">
            </form>
            <?php

            // Process State update form
            if (isset($_POST['order']) && isset($_POST['process'])) {
                $order = $_POST['order'];
                $process = $_POST['process'];

                // Update the process state of the order
                $sql = "UPDATE Orders SET process_state = :process WHERE order_no = :order;";
                $stmt = $pdo->prepare($sql);
                $stmt->execute(['process' => $process, 'order' => $order]);

                echo "<p>Order ${order} updated to ${process}. Refresh to see the changes.</p>\n";

            }

            // Form to update a product
            ?>
            <h2>Update Inventory</h2>
            <form action="employee.php" method="post">
                <input type="text" name="id" placeholder="Product ID">
                <input type="text" name="stock" placeholder="Quantity">
                <input type="number" name="price" step="0.01" placeholder="Price">
                <input type="submit" value="Update">
            </form>

            <?php
            // Product Update Form
            if (isset($_POST['id']) && isset($_POST['stock']) && isset($_POST['price'])) {
                $id = $_POST['id'];
                $stock = $_POST['stock'];
                $price = $_POST['price'];

                $sql = "UPDATE Inventory SET inv_stock = :stock, inv_price = :price WHERE inv_id = :id;";
                $stmt = $pdo->prepare($sql);
                $stmt->execute(['stock' => $stock, 'id' => $id, 'price' => $price]);

                echo "<p>Product ${id} updated to ${stock} at $${price}. Refresh to see the changes.</p>\n";

            }
            
            echo "</td>"; // End outer table row
            echo "</td>"; // End outer table row
            echo "</table>\n"; // End outer table
            ?>
    </div>


    </body>
</html>