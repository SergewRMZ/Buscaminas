#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

int main() {
  int segundo = 1;
  while(true) {
    cout << "\rSegundos: " << segundo << "s  " << endl;
    sleep_for(seconds(1));
    segundo++;
  }
}
