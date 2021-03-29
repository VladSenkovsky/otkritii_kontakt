#include <string>
using namespace std;

class Product {
  public: 
    void setProductID (int id) {
      Product::productID = id;
    }
    int getProductID () {
      return productID;
    }
    void setShopId (int id) {
      Product::shopID = id;
    }
    int getShopID () {
      return shopID;
    }
    void setName (string name) {
      Product::name = name;
    }
    string getName () {
      return name;
    }
    void setDescription (string description) {
      Product::description = description;
    }
    string getDescription () {
      return description;
    }
    void setPrice (float price) {
      Product::price = price;
    }
    float getPrice () {
      return price;
    }
  private:
      int productID;
      int shopID;
      string name;
      string description;
      float price;
};