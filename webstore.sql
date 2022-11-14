-- Sami Rezae, Bailey Appelhans, Gerald Ellsworth, David Flowers
-- Lehuta 466
-- 11/13/22

--CREATE DATABASE webstore;

USE webstore;

CREATE TABLE User (

    user_id INT NOT NULL UNIQUE,
    password CHAR(50) NOT NULL,
    PRIMARY KEY(user_id)

);

CREATE TABLE Customer (



)