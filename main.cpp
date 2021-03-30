#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <time.h>
#include <iomanip>
#include "products.h"
#include "shops.h"
#include "mysql/mysql.h"
using namespace std;


MYSQL *connection, mysql;
MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

static int shopSize;
static int productSize;
// g++ main.cpp -L/usr/include/mysql -lmysqlclient
Shop* getShopsInfo (MYSQL *connection) {
  mysql_query(connection, "SELECT COUNT(*) FROM SHOPS");
  result = mysql_store_result(connection);
  row = mysql_fetch_row(result);
  int amount = atoi(row[0]);
  Shop *array = new Shop[amount];
  shopSize = amount;
  mysql_free_result(result);
  mysql_query(connection, "SELECT id FROM SHOPS order by id");
  result = mysql_store_result(connection);
  int counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i < mysql_num_fields(result); i++){
      array[counter].setID(atoi(row[i]));
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT name FROM SHOPS order by id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setName(row[i]);
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT url FROM SHOPS order by id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setURL(row[i]);
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT opens FROM SHOPS order by id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      struct tm tm;
      strptime(row[i], "%H:%M:%S", &tm);
      time_t t = mktime(&tm);
      array[counter].setOpen(t);
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT closes FROM SHOPS order by id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      struct tm tm;
      strptime(row[i], "%H:%M:%S", &tm);
      time_t t = mktime(&tm);
      array[counter].setClose(t);
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
  productSize = amount;
  mysql_free_result(result);
  mysql_query(connection, "SELECT product_id FROM PRODUCTS order by product_id");
  result = mysql_store_result(connection);
  int counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i < mysql_num_fields(result); i++){
      array[counter].setProductID(atoi(row[i]));
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT shop_id FROM PRODUCTS order by product_id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setShopId(atoi(row[i]));
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT name FROM PRODUCTS order by product_id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setName(row[i]);
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT description FROM PRODUCTS order by product_id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setDescription(row[i]);
    }
    counter++;
  }
  mysql_free_result(result);
  mysql_query(connection, "SELECT price FROM PRODUCTS order by product_id");
  result = mysql_store_result(connection);
  counter = 0;
  while(row = mysql_fetch_row(result)) {
    for (int i=0 ; i <mysql_num_fields(result); i++){
      array[counter].setPrice(stof(row[i]));
    }
    counter++;
  }
  return array;

}
void writeXML (std::ofstream &file, Shop *shops, Product *products) {
    time_t t = time(0);
    tm now = *localtime(&t);
    now.tm_year += 1990;
    now.tm_mon += 1;
    tm open, close;
  for (int i = 0; i < shopSize; i++) {
    t = shops[i].getOpen();
    open = *localtime(&t);
    open.tm_year = now.tm_year;
    open.tm_mon = now.tm_mon;
    open.tm_mday = now.tm_mday;
    t = shops[i].getClose();
    close = *localtime(&t);
    close.tm_year = now.tm_year;
    close.tm_mon = now.tm_mon;
    close.tm_mday = now.tm_mday;
      if (difftime(mktime(&now), mktime(&open)) >= 0 && difftime(mktime(&close), mktime(&now)) > 0) {
      file << "<shop id=\"" << shops[i].getID() << "\">\n";
      file << "\t<name>" << shops[i].getName() << "</name>\n";
      file << "\t<url>" << shops[i].getURL() << "</url>\n";
      file << "\t<working_time>\n";
      file << "\t\t<open>" << open.tm_hour << ":" << open.tm_min<<"</open>\n";
      file << "\t\t<close>" << close.tm_hour << ":" << close.tm_min<<"</close>\n";
      file << "\t<working_time>\n";
      file << "\t<offers>\n";
      for (int j = 0; j < productSize; j++) {
        if (products[j].getShopID() == shops[i].getID()) {
          file << "\t\t<item id=\"" << products[j].getProductID() << "\">\n";
          file << "\t\t\t<name>" << products[j].getName() << "</name>\n";
          file << "\t\t\t<description>" << products[j].getDescription() <<"</description>\n";
          char str[64];
          sprintf(str, "%7.2f", products[j].getPrice());
          file << "\t\t\t<price>" << str <<"</price>\n";
          file << "\t\t</item>\n";
        }
      }
      file << "\t</offers>\n";
     }
    file << "</shop>\n";
  }
}
// <shop id="1">
//   <name>Мой магазин</name>
//   <url>ololo.shop.by</url>
//   <working_time>
//     <open>10:00</open>
//     <close>23:00</close>
//   </working_time>
//   <offers>
//     <item id="111">
//       <name>имя товара</name>
//       <description>описание без html тегов</description>
//       <price>5.80</price>
//     </item>
//     <item id="222">
//     ...
//     </item>
//     ...
//   </offers>
// </shop>
// <shop id="2">
// ...
// </shop>
// ...
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
  //   cout<<row[i] <<"\n";
  //   }
  //   }
  // } else {
  // fprintf(stderr, "%s\n", mysql_error(connection));
  // }

  Shop *shops = getShopsInfo(connection);
  Product *products = getProductsInfo(connection);

  char buff[20];
  for (int i = 0; i < shopSize; i++) {
    time_t t = shops[i].getOpen();
    strftime(buff, 20, "%H:%M:%S", localtime(&t));
    cout << buff << endl;
  }
  for (int i = 0; i < productSize; i++) {
    cout << products[i].getDescription() << endl;
  }
  ofstream report;
  report.open("report.xml");
  writeXML(report, shops, products);
  report.close();
  mysql_free_result(result);
  mysql_close(connection);
  return 0;
}
