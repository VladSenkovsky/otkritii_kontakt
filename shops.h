#include <string>
#include <ctime>
using namespace std;

class Shop {
  public:
    void setID (int id) {
      Shop::id = id;
    }
    int getID () {
      return id;
    }
    void setName (string name) {
      Shop::name = name;
    }
    string getName () {
      return name;
    }
    void setURL (string url) {
      Shop::url = url;
    }
    string getURL () {
      return url;
    }
    void setOpen (time_t opened) {
      Shop::opened = opened;
    }
    time_t getOpen () {
      return opened;
    }
    void setClose (time_t closed) {
      Shop::closed = closed;
    }
    time_t getClose () {
      return closed;
    }
  private:
      int id;
      string name;
      string url;
      time_t opened;
      time_t closed;
};
