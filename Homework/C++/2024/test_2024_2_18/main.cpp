#include <iostream>

using namespace std;

class CCar;
class CDriver {
  public:
    void ModifyCar(CCar* pCar);
};
class CCar {
  private:
    int price;
    friend int MostExpensiveCar(CCar cars[], int total);
    friend void CDriver::ModifyCar(CCar* pCar);
};
void CDriver::ModifyCar(CCar* pCar) {
  pCar->price += 1000;
}
int MostExpensiveCar(CCar cars[], int total) {
  int tmpMax = -1;
  for (int i = 0; i < total; ++i) {
    if (cars[i].price > tmpMax) {
      tmpMax = cars[i].price;
    }
  }
}

int main() {
  cout << "Hello World!" << endl;
  return 0;
}

