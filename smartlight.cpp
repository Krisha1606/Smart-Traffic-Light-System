#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

class TrafficSignal {
protected:
    string roadName;
    int vehicleCount;
    int redTime;
    const int greenTime = 20;  // Green light is fixed at 20 seconds

public:
    TrafficSignal(string name) : roadName(name), vehicleCount(0), redTime(0) {}

    virtual void calculateRedTime() {
        // Default red light time - will adjust dynamically based on traffic density
        redTime = 40;  // Default red time
    }

    virtual void display() const {
        cout << roadName << ": " << vehicleCount
             << " vehicles -> RED: " << redTime
             << "s | GREEN: " << greenTime << "s\n";
    }

    virtual void run() const {
        // Simulating the red light time and the green light time
        cout << "[RED] " << roadName << " for " << redTime << " seconds\n";
        this_thread::sleep_for(chrono::seconds(1)); // Simulating time passing
        cout << "[GREEN] " << roadName << " for " << greenTime << " seconds\n";
    }

    friend class TrafficController;

    bool operator>(const TrafficSignal& other) const {
        return vehicleCount > other.vehicleCount;
    }

    virtual ~TrafficSignal() {}
};

// Derived Class to handle smarter red light calculation
class SmartSignal : public TrafficSignal {
public:
    SmartSignal(string name) : TrafficSignal(name) {}

    void calculateRedTime() override {
        // Dynamically calculate red light duration based on traffic density

        // High traffic (more vehicles) means longer red light
        // Low traffic (fewer vehicles) means shorter red light

        if (vehicleCount >= 40) {
            // Traffic density is high, give longer red light time
            redTime = 60 + (100 / vehicleCount);  // Adjust formula for smoother traffic flow
        } else if (vehicleCount >= 20) {
            // Moderate traffic, give a medium red light time
            redTime = 40 + (60 / vehicleCount);  // Adjust formula for moderate density
        } else {
            // Low traffic, give shorter red light time
            redTime = 30 - (20 / vehicleCount);  // Reduces waiting time when traffic is low
        }

        // Ensure red light doesn't go below a reasonable minimum (10 seconds)
        if (redTime < 10) {
            redTime = 10;
        }
    }

    void display() const override {
        cout << "[Smart] " << roadName << ": " << vehicleCount
             << " vehicles -> RED: " << redTime
             << "s | GREEN: " << greenTime << "s\n";
    }
};

// Friend Class to handle traffic simulation
class TrafficController {
public:
    void simulateTraffic(vector<SmartSignal*>& roads) {
        // Randomize vehicle count and calculate red time
        for (auto& road : roads) {
            road->vehicleCount = rand() % 50;  // Random vehicle count between 0 and 50
            road->calculateRedTime();  // Adjust red light time based on vehicle count
        }
    }

    void sortByTraffic(vector<SmartSignal*>& roads) {
        // Sort roads by vehicle count to prioritize high traffic roads
        for (size_t i = 0; i < roads.size(); ++i) {
            for (size_t j = i + 1; j < roads.size(); ++j) {
                if (*roads[j] > *roads[i]) {
                    swap(roads[i], roads[j]);
                }
            }
        }
    }

    void runCycle(vector<SmartSignal*>& roads) {
        // Loop through and run each road's traffic light cycle
        for (auto& road : roads) {
            road->display();
            road->run();
        }
    }
};

int main() {
    srand(time(0));  // Seed random number generator

    // Create roads with Smart Signals
    vector<SmartSignal*> roads = {
        new SmartSignal("Road A"),
        new SmartSignal("Road B"),
        new SmartSignal("Road C"),
        new SmartSignal("Road D")
    };

    TrafficController controller;

    while (true) {
        cout << "\n--- Traffic Cycle Start ---\n";
        controller.simulateTraffic(roads);  // Simulate traffic for all roads
        controller.sortByTraffic(roads);    // Sort roads by traffic density
        controller.runCycle(roads);         // Run the traffic cycle
        this_thread::sleep_for(chrono::seconds(2));  // Delay before the next cycle
    }

    // Cleanup allocated memory
    for (auto road : roads) {
        delete road;
    }

    return 0;
}
