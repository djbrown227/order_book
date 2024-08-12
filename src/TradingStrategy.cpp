#include "TradingStrategy.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <deque>
#include <numeric>

// Constructor to initialize the strategy
TradingStrategy::TradingStrategy(OrderBook& orderBook, MarketData& marketData)
    : orderBook(orderBook), marketData(marketData), balance(10000.0), volume(0) { // Starting balance

}

// Executes the trading strategy by placing orders
void TradingStrategy::executeStrategy() {
    while (true) {
        double price = marketData.getLatestPrice();
        int quantity = rand() % 10 + 1;

        // Simulate a decision to buy or sell
        if (rand() % 2 == 0) {
            orderBook.addBuyOrder(price, quantity);
            balance -= price * quantity; // Deduct from balance for buy orders
            volume += quantity; // Increment volume for buy orders
            std::cout << "Placed Buy Order: " << quantity << " @ " << price << " | Balance: " << balance << " | Volume: " << volume << "\n";
        } else {
            orderBook.addSellOrder(price, quantity);
            balance += price * quantity; // Add to balance for sell orders
            volume += quantity; // Increment volume for sell orders
            std::cout << "Placed Sell Order: " << quantity << " @ " << price << " | Balance: " << balance << " | Volume: " << volume << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between orders
    }
}

// New method for the mean reversion strategy
void TradingStrategy::executeMeanReversionStrategy(int movingAveragePeriod) {
    std::deque<double> priceHistory; // Store recent prices

    while (true) {
        double price = marketData.getLatestPrice();
        priceHistory.push_back(price);

        // Maintain only the last `movingAveragePeriod` prices
        if (priceHistory.size() > movingAveragePeriod) {
            priceHistory.pop_front();
        }

        // Calculate the moving average if we have enough data
        if (priceHistory.size() == movingAveragePeriod) {
            double movingAverage = std::accumulate(priceHistory.begin(), priceHistory.end(), 0.0) / movingAveragePeriod;
            int quantity = rand() % 10 + 1;

            // Mean reversion logic
            if (price < movingAverage) {
                orderBook.addBuyOrder(price, quantity);
                balance -= price * quantity; // Deduct from balance for buy orders
                volume += quantity; // Increment volume for buy orders
                std::cout << "Mean Reversion Buy Order: " << quantity << " @ " << price << " (MA: " << movingAverage << ") | Balance: " << balance << " | Volume: " << volume << "\n";
            } else if (price > movingAverage) {
                orderBook.addSellOrder(price, quantity);
                balance += price * quantity; // Add to balance for sell orders
                volume += quantity; // Increment volume for sell orders
                std::cout << "Mean Reversion Sell Order: " << quantity << " @ " << price << " (MA: " << movingAverage << ") | Balance: " << balance << " | Volume: " << volume << "\n";
            }
        }
    }
}

// New method for the market maker strategy
void TradingStrategy::executeMarketMakerStrategy(double spread, int quantity) {
    while (true) {
        double price = marketData.getLatestPrice();

        // Place a buy order below the current price
        double buyPrice = price - spread / 2;
        orderBook.addBuyOrder(buyPrice, quantity);
        balance -= buyPrice * quantity; // Deduct from balance for buy orders
        volume += quantity; // Increment volume for buy orders
        std::cout << "Market Maker Buy Order: " << quantity << " @ " << buyPrice << " | Balance: " << balance << " | Volume: " << volume << "\n";

        // Place a sell order above the current price
        double sellPrice = price + spread / 2;
        orderBook.addSellOrder(sellPrice, quantity);
        balance += sellPrice * quantity; // Add to balance for sell orders
        volume += quantity; // Increment volume for sell orders
        std::cout << "Market Maker Sell Order: " << quantity << " @ " << sellPrice << " | Balance: " << balance << " | Volume: " << volume << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate time between orders
    }
}

// Get current balance
double TradingStrategy::getBalance() const {
    return balance;
}

// Get total volume traded
int TradingStrategy::getVolume() const {
    return volume;
}
