DROP TABLE PRODUCTS;
DROP TABLE SHOPS;

CREATE TABLE SHOPS (
    id INT unsigned NOT NULL AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    url VARCHAR(255) NOT NULL,
    opens TIME NOT NULL,
    closes TIME NOT NULL,
    PRIMARY KEY (id)
);
COMMIT;
INSERT INTO SHOPS (name, url, opens, closes) VALUES ('Check', 'check.ru', '10:00:00',  '23:00:00');
INSERT INTO SHOPS (name, url, opens, closes) VALUES ('TipTop', 'ttshop.by', '8:00:00',  '19:00:00');
INSERT INTO SHOPS (name, url, opens, closes) VALUES ('MobileCity', 'mcityshop.ru', '11:15:00',  '13:15:00');
INSERT INTO SHOPS (name, url, opens, closes) VALUES ('PCShop', 'buydatpc.ru', '7:30:00',  '15:45:00');
INSERT INTO SHOPS (name, url, opens, closes) VALUES ('Soulja', 'souljashop.by', '9:00:00',  '23:00:00');
COMMIT;
CREATE TABLE PRODUCTS (
    product_id INT unsigned NOT NULL AUTO_INCREMENT,
    shop_id INT unsigned NOT NULL,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    price decimal(15,2) NOT NULL,
    PRIMARY KEY (product_id),
    FOREIGN KEY (shop_id) REFERENCES SHOPS (id)
);
COMMIT;
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (1, 'YouPhone', 'This product was made in the <i>USA</i>.<br>At the moment we have 1100 of these items.', 1000000.25);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (2, 'Wooden table', 'Handmade product. This could be a great wedding gift. Manufacturer\'s contacts: <b>80297776655</b>.', 10.00);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (3, 'Earings', 'Stock item. Discount up to <mark>70%</mark>.', 100.99);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (4, 'Glasses', 'Previous price of <del>120.25</del> was reduced due to new development technology.', 77.8);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (5, 'Leather couch', 'World market leader since <strong>1925</strong>.', 1120.00);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (1, 'Sobranie cigars', 'World market leader since <strong>2010</strong>.', 900.5);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (2, 'Teddybear', 'Stock item!<br> Discount up to<mark>55%</mark>.', 5);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (3, 'Razor mouse', 'Previous price of <del>50.25</del> was reduced due to new development technology.', 29.99);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (4, 'Napkins', 'Handmade product. This could be a great wedding gift.<br>Manufacturer\'s contacts: <b>80297778899</b>.', 10);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (5, 'Lolipops', 'This product was made in <i>China</i>.<br>At the moment we have <sup>200</sup> of these items.', 99.99);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (1, 'Emoji stickers', 'Positive reviews record holder. Produced with <sub>diogonal lamination</sub> technology', 12.35);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (1, 'Giraff\'s paintings', 'Description w/o tags', 100.10);
INSERT INTO PRODUCTS (shop_id, name, description, price) VALUES (2, 'Teapot', 'This product was made in <i>Britain</i>. At the moment we have <b>398</b> of these items.', 55);
