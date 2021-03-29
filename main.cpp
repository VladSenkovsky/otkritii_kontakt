#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include "products.h"
#include "shops.h"
#include "mysql/mysql.h"
using namespace std;


MYSQL *connection, mysql;
MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

// g++ main.cpp -L/usr/include/mysql -lmysqlclient
Shop* getShopsInfo (MYSQL *connection) {
  mysql_query(connection, "SELECT COUNT(*) FROM SHOPS");
  result = mysql_store_result(connection);
  row = mysql_fetch_row(result);
  int amount = atoi(row[0]);
  Shop *array = new Shop[amount];
  mysql_free_result(result);

  mysql_query(connection, "SELECT id FROM SHOPS");
  result = mysql_store_result(connection);
  int counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i < mysql_num_fields(result); i++){
      array[counter].setID(atoi(row[i])); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT name FROM SHOPS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setName(row[i]); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT url FROM SHOPS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setURL(row[i]); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT opens FROM SHOPS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      struct tm tm;
      strptime(row[i], "%H:%M:%S", &tm);
      time_t t = mktime(&tm);
      array[counter].setOpen(t); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT closes FROM SHOPS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      struct tm tm;
      strptime(row[i], "%H:%M:%S", &tm);
      time_t t = mktime(&tm);
      array[counter].setClose(t); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  return array;
}
Product* getProductsInfo(MYSQL *connection) {
  mysql_query(connection, "SELECT COUNT(*) FROM PRODUCTS");
  result = mysql_store_result(connection);
  row = mysql_fetch_row(result);
  int amount = atoi(row[0]);
  Product *array = new Product[amount];
  mysql_free_result(result);

  mysql_query(connection, "SELECT product_id FROM PRODUCTS");
  result = mysql_store_result(connection);
  int counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i < mysql_num_fields(result); i++){
      array[counter].setProductID(atoi(row[i])); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT shop_id FROM PRODUCTS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setShopId(atoi(row[i])); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT name FROM PRODUCTS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setName(row[i]); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT description FROM PRODUCTS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setDescription(row[i]); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT price FROM PRODUCTS");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setPrice(stof(row[i])); //Выводим все что есть в базе через цикл
    }
    counter++;
  }
  return array;

}
int main () {
  mysql_init(&mysql);
  connection = mysql_real_connect(&mysql,"localhost","root","","shop",3306,0,0);
  // if (connection == NULL) {
  // cout << mysql_error(&mysql) << endl;
  // return 1;
  // }
  //
  // query_state = mysql_query(connection, "select id from SHOPS");
  // if (query_state !=0) {
  // cout << mysql_error(connection) << endl;
  // return 1;
  // }
  //
  // result = mysql_store_result(connection);
  // while (( row = mysql_fetch_row(result)) != NULL) {
  // cout << "Number of active users : " << row[0] << endl;
  // }
  //   mysql_query(connection,"SELECT id FROM SHOPS");
  //
  //   if (result = mysql_store_result(connection)){
  //   while(row = mysql_fetch_row(result)) {
  //   for (int i=0 ; i <mysql_num_fields(result); i++){
  //   cout<<row[i] <<"\n"; //Выводим все что есть в базе через цикл
  //   }
  //   }
  // } else {
  // fprintf(stderr, "%s\n", mysql_error(connection));
  // }

  Shop *shops = getShopsInfo(connection);
  Product *products = getProductsInfo(connection);

  char buff[20];
  for (int i = 0; i < sizeof(shops)-3; i++) { //?????????????????????????????
    time_t t = shops[i].getOpen();
    strftime(buff, 20, "%H:%M:%S", localtime(&t));
    cout << buff << endl;
  }
  for (int i = 0; i < sizeof(products); i++) { //?????????????????????????????
    cout << products[i].getDescription() << endl;
  }
  mysql_free_result(result);
  mysql_close(connection);
  return 0;
}
