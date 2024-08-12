#include "MarketData.h"
#include "OrderBook.h"
#include "TradingStrategy.h"
#include <thread>
#include <chrono>
#include <iostream>

// Thread function to simulate market data generation
void marketDataThread(MarketData& marketData) {
    marketData.generateMarketData();
}

// Thread function to simulate the trading strategy execution
void tradingStrategyThread(TradingStrategy& strategy) {
    strategy.executeStrategy();
}

// Thread function to simulate the mean reversion strategy execution
void meanReversionStrategyThread(TradingStrategy& strategy, int movingAveragePeriod) {
    strategy.executeMeanReversionStrategy(movingAveragePeriod);
}

// Thread function to simulate the market maker strategy execution
void marketMakerStrategyThread(TradingStrategy& strategy, double spread, int quantity) {
    strategy.executeMarketMakerStrategy(spread, quantity);
}

// Main function to run the simulation
int main() {
    MarketData marketData;
    OrderBook orderBook;
    TradingStrategy strategy(orderBook, marketData);

    std::thread marketThread(marketDataThread, std::ref(marketData));
    std::thread strategyThread(tradingStrategyThread, std::ref(strategy));
    std::thread meanReversionThread(meanReversionStrategyThread, std::ref(strategy), 5); // Using a moving average period of 5
    std::thread marketMakerThread(marketMakerStrategyThread, std::ref(strategy), 0.5, 10); // Spread of 0.5 and quantity of 10

    for (int i = 0; i < 100; ++i) {
        orderBook.matchOrders(); // Match orders every iteration
        orderBook.displayOrderBook(); // Display the order book after each iteration
        
        // Display balance and volume after each iteration
        std::cout << "Balance: " << strategy.getBalance() << ", Volume: " << strategy.getVolume() << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between trades
    }

    marketThread.join();
    strategyThread.join();
    meanReversionThread.join();
    marketMakerThread.join(); // Wait for the market maker thread to finish

    return 0;
}
