#include "TradingStrategy.h"
#include <chrono>
#include <thread>
#include <iostream> // Include the iostream header for std::cout

// Constructor to initialize the strategy
TradingStrategy::TradingStrategy(OrderBook& orderBook, MarketData& marketData)
    : orderBook(orderBook), marketData(marketData) {}

// Executes the trading strategy by placing orders
void TradingStrategy::executeStrategy() {
    while (true) {
        double price = marketData.getLatestPrice();
        int quantity = rand() % 10 + 1;

        // Simulate a decision to buy or sell
        if (rand() % 2 == 0) {
            orderBook.addBuyOrder(price, quantity);
            std::cout << "Placed Buy Order: " << quantity << " @ " << price << "\n";
        } else {
            orderBook.addSellOrder(price, quantity);
            std::cout << "Placed Sell Order: " << quantity << " @ " << price << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between orders
    }
}
