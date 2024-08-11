#include "MarketData.h"
#include "OrderBook.h"
#include "TradingStrategy.h"
#include <thread>
#include <chrono>

// Thread function to simulate market data generation
void marketDataThread(MarketData& marketData) {
    marketData.generateMarketData();
}

// Thread function to simulate the trading strategy execution
void tradingStrategyThread(TradingStrategy& strategy) {
    strategy.executeStrategy();
}

// Main function to run the simulation
int main() {
    MarketData marketData;
    OrderBook orderBook;
    TradingStrategy strategy(orderBook, marketData);

    std::thread marketThread(marketDataThread, std::ref(marketData));
    std::thread strategyThread(tradingStrategyThread, std::ref(strategy));

    for (int i = 0; i < 100; ++i) {
        orderBook.matchOrders(); // Match orders every iteration
        orderBook.displayOrderBook(); // Display the order book after each iteration
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between trades
    }

    marketThread.join();
    strategyThread.join();

    return 0;
}
