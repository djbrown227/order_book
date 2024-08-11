#include "MarketData.h"
#include <chrono>
#include <thread>

// Constructor initializes RNG and seed
MarketData::MarketData() : rng(std::random_device{}()) {
    prices.push_back(100.0); // Start price
}

// Returns the latest price in a thread-safe way
double MarketData::getLatestPrice() {
    std::lock_guard<std::mutex> lock(marketDataMutex);
    return prices.back();
}

// Generates market data by simulating price changes
void MarketData::generateMarketData() {
    std::normal_distribution<double> dist(0.0, 1.0);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate time

        std::lock_guard<std::mutex> lock(marketDataMutex);
        double newPrice = prices.back() + dist(rng); // Simulate price movement
        prices.push_back(newPrice);
    }
}
