-- Sami Rezae, Bailey Appelhans, Gerald Ellsworth, David Flowers
-- Lehuta 466
-- 11/13/22

CREATE TABLE User (

    user_id INT NOT NULL UNIQUE,
    f_name CHAR(50) NOT NULL,
    l_name CHAR(50) NOT NULL,
    password CHAR(50) NOT NULL,

    PRIMARY KEY(user_id)

);

CREATE TABLE Inventory (

    inv_id INT NOT NULL UNIQUE,
    inv_name CHAR(50) NOT NULL,
    inv_price DECIMAL(5,2) NOT NULL,
    inv_stock INT NOT NULL,
    inv_image CHAR(100) NOT NULL,

    PRIMARY KEY(inv_id)

);

CREATE TABLE Cart (

    cart_id INT AUTO_INCREMENT,
    id_inv INT NOT NULL,
    quantity INT NOT NULL,
    id_user INT NOT NULL,
    
    PRIMARY KEY(cart_id),
    FOREIGN KEY(id_inv) REFERENCES Inventory(inv_id),
    FOREIGN KEY(id_user) REFERENCES User(user_id)

);

CREATE TABLE Customer (

    id_user INT NOT NULL UNIQUE,
    email_addr CHAR(100) NOT NULL UNIQUE,
    cart_id INT NOT NULL UNIQUE,

    PRIMARY KEY(id_user, email_addr),
    FOREIGN KEY(id_user) REFERENCES User(user_id),
    FOREIGN KEY(cart_id) REFERENCES Cart(cart_id)

);

CREATE TABLE Employee (

    id_user INT NOT NULL UNIQUE,
    emp_id INT NOT NULL UNIQUE,

    PRIMARY KEY(id_user, emp_id),
    FOREIGN KEY(id_user) REFERENCES User(user_id)

);

CREATE TABLE Orders (

    order_no INT NOT NULL UNIQUE,
    track_no INT NOT NULL UNIQUE,
    process_state CHAR(50) NOT NULL,
    order_date DATETIME NOT NULL,
    user_email CHAR(100) NOT NULL UNIQUE,
    id_emp INT NOT NULL UNIQUE,

    PRIMARY KEY(order_no),
    FOREIGN KEY(user_email) REFERENCES Customer(email_addr),
    FOREIGN KEY(id_emp) REFERENCES Employee(emp_id)

);

CREATE TABLE OrderInfo (

    no_order INT NOT NULL,
    id_inv INT NOT NULL,
    quantity INT NOT NULL,

    PRIMARY KEY(no_order, id_inv),
    FOREIGN KEY(no_order) REFERENCES Orders(order_no),
    FOREIGN KEY(id_inv) REFERENCES Inventory(inv_id)
 
);

CREATE TABLE Shipping (

    shipping_id INT NOT NULL UNIQUE AUTO_INCREMENT,
    country CHAR(50) NOT NULL,
    state_province CHAR(50) NOT NULL,
    city CHAR(50) NOT NULL,
    zipcode INT NOT NULL,
    address CHAR(100) NOT NULL,
    user_email CHAR(100) NOT NULL UNIQUE,

    PRIMARY KEY(shipping_id),
    FOREIGN KEY(user_email) REFERENCES Customer(email_addr)

);

CREATE TABLE Billing (

    billing_id INT NOT NULL UNIQUE auto_increment,
    country CHAR(50) NOT NULL,
    state_province CHAR(50) NOT NULL,
    city CHAR(50) NOT NULL,
    zipcode INT NOT NULL,
    address CHAR(100) NOT NULL,
    user_email CHAR(100) NOT NULL UNIQUE,

    PRIMARY KEY(billing_id),
    FOREIGN KEY(user_email) REFERENCES Customer(email_addr)

);

