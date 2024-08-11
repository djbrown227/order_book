#ifndef MARKET_DATA_H
#define MARKET_DATA_H

#include <vector>
#include <mutex>
#include <random>

// MarketData class to simulate price movements
class MarketData {
public:
    MarketData();

    // Returns the latest price
    double getLatestPrice();

    // Simulates the market data stream
    void generateMarketData();

private:
    std::vector<double> prices;
    std::mutex marketDataMutex;
    std::mt19937 rng;
};

#endif // MARKET_DATA_H
