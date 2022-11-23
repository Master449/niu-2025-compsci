-- Inventory Products

INSERT INTO Inventory VALUES (0,  '',          0.00, 0, '');
INSERT INTO Inventory VALUES (1,  'Banana',          0.29, 150, 'https://i.imgur.com/CXHmKq1.png');
INSERT INTO Inventory VALUES (2,  'Apple',           0.49, 100, 'https://i.imgur.com/v4ghyqo.png');
INSERT INTO Inventory VALUES (3,  'Orange',          0.35, 100, 'https://i.imgur.com/ML3p2ZE.png');
INSERT INTO Inventory VALUES (4,  'Pineapple',       2.00, 50,  'https://i.imgur.com/Iom2GFz.png');
INSERT INTO Inventory VALUES (5,  'Spinach',         2.99, 75,  'https://i.imgur.com/tJOEqWx.png');
INSERT INTO Inventory VALUES (6,  'Romain Lettuce',  1.99, 25,  'https://i.imgur.com/XA7J0HF.png');
INSERT INTO Inventory VALUES (7,  'Iceberg Lettuce', 2.49, 25,  'https://i.imgur.com/bD6YXhR.png');
INSERT INTO Inventory VALUES (8,  'Asparagus',       0.99, 60,  'https://i.imgur.com/ne2l8BJ.png');
INSERT INTO Inventory VALUES (9,  'Carrot',          0.25, 150, 'https://i.imgur.com/K5jpIaR.png');
INSERT INTO Inventory VALUES (10, 'Celery',          0.29, 150, 'https://i.imgur.com/p2ANnol.png');
INSERT INTO Inventory VALUES (11, 'French Bread',    2.99, 15,  'https://i.imgur.com/3FXSeVX.png');
INSERT INTO Inventory VALUES (12, 'Artichoke',       1.50, 25,  'https://i.imgur.com/8R3rsPo.png');
INSERT INTO Inventory VALUES (13, 'Avacado',         1.00, 50,  'https://i.imgur.com/HZunMJz.png');
INSERT INTO Inventory VALUES (14, 'Green Grapes',    4.99, 20,  'https://i.imgur.com/8gL3LxM.png');
INSERT INTO Inventory VALUES (15, 'Red Grapes',      5.99, 20,  'https://i.imgur.com/xXANv3v.png');
INSERT INTO Inventory VALUES (16, 'Whole Milk',      2.99, 25,  'https://i.imgur.com/KXczA5v.png');
INSERT INTO Inventory VALUES (17, 'Chocolate Milk',  2.99, 10,  'https://i.imgur.com/KXczA5v.png');
INSERT INTO Inventory VALUES (18, 'Spaghetti',       0.99, 30,  'https://i.imgur.com/QSygrd6.png');
INSERT INTO Inventory VALUES (19, 'Canned Beans',    1.19, 30,  'https://i.imgur.com/vkNkQoX.png');
INSERT INTO Inventory VALUES (20, 'Canned Soup',     0.99, 30,  'https://i.imgur.com/Za3GLaB.png');

-- Customers
INSERT INTO User VALUES (1, "John", "Smith", "password1");
INSERT INTO Cart VALUES (1, 0, 0);
INSERT INTO Customer VALUES (1, "john@email.com", 1);

INSERT INTO User VALUES (2, "Mary", "Lancaster", "password2");
INSERT INTO Cart VALUES (2, 0, 0);
INSERT INTO Customer VALUES (2, "mary@email.com", 2);

INSERT INTO User VALUES (3, "Maria", "Orbit", "password3");
INSERT INTO Cart VALUES (3, 0, 0);
INSERT INTO Customer VALUES (3, "maria@email.com", 3);

INSERT INTO User VALUES (4, "Michael", "Frank", "password4");
INSERT INTO Cart VALUES (4, 0, 0);
INSERT INTO Customer VALUES (4, "michael@email.com", 4);

INSERT INTO User VALUES (5, "Lehuta", "Jon", "password5");
INSERT INTO Cart VALUES (5, 0, 0);
INSERT INTO Customer VALUES (5, "lehuta@email.com", 5);


-- Employees
INSERT INTO User VALUES (10, "Sami", "Rezae", "password");
INSERT INTO Employee VALUES (10, 10);

INSERT INTO User VALUES (20, "Bailey", "Appelhans", "password");
INSERT INTO Employee VALUES (20, 20);

INSERT INTO User VALUES (30, "Gerald", "Ellsworth", "password");
INSERT INTO Employee VALUES (30, 30);

INSERT INTO User VALUES (40, "David", "Flowers", "password");
INSERT INTO Employee VALUES (40, 40);