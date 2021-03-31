#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "funcs.h"
using namespace std;

// g++ main.cpp -L/usr/include/mysql -lmysqlclient
MYSQL *connection, mysql;

int main () {
  mysql_init(&mysql);
  connection = mysql_real_connect(&mysql,"localhost","root","","shop",3306,0,0);
  if (connection == NULL) {
    cout << mysql_error(&mysql) << endl;
    return 1;
  }
  Shop *shops = getShopsInfo(connection);
  Product *products = getProductsInfo(connection);
  ofstream report;
  report.open("report.xml");
  writeXML(report, shops, products);
  report.close();
  mysql_close(connection);
  return 0;
}
