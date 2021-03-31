#include <regex>
#include <ctime>
#include <time.h>
#include "mysql/mysql.h"
#include "products.h"
#include "shops.h"
using namespace std;

MYSQL_RES *result;
MYSQL_ROW row;
int query_state;

static int shopSize;
static int productSize;

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
  mysql_free_result(result);
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
  mysql_free_result(result);
  return array;
}
void writeXML (ofstream &file, Shop *shops, Product *products) {
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
    const regex pattern("\\<.*?\\>");
    string s;
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
          s = products[j].getDescription();
          s = regex_replace(s, pattern, "");
          file << "\t\t\t<description>" << s <<"</description>\n";
          char str[64];
          sprintf(str, "%.2f", products[j].getPrice());
          file << "\t\t\t<price>" << str <<"</price>\n";
          file << "\t\t</item>\n";
        }
      }
      file << "\t</offers>\n";
     }
    file << "</shop>\n";
  }
}