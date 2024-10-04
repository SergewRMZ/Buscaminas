#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class Chronometer {
    private:
        time_point<high_resolution_clock> startTime;
        bool running;

    public:
        Chronometer() : running(false) {}

        void start () {
            startTime = high_resolution_clock::now();
            running = true;
        }

        duration<double> stop() {
            if (running) {
                auto endTime = high_resolution_clock::now();
                duration<double> duration = endTime - startTime;
                running = false;
                return duration;
            }

            return duration<double>::zero();
        }
};
