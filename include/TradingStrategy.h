#ifndef TRADING_STRATEGY_H
#define TRADING_STRATEGY_H

#include "OrderBook.h"
#include "MarketData.h"

// TradingStrategy class to implement different trading strategies
class TradingStrategy {
public:
    TradingStrategy(OrderBook& orderBook, MarketData& marketData);

    // Executes the trading strategies
    void executeStrategy();
    void executeMeanReversionStrategy(int movingAveragePeriod);
    void executeMarketMakerStrategy(double spread, int quantity);

    // Get the current balance
    double getBalance() const;

    // Get the total volume traded
    int getVolume() const;

private:
    OrderBook& orderBook;
    MarketData& marketData;
    double balance;  // Current balance of money
    int volume;      // Total volume traded
};

#endif // TRADING_STRATEGY_H
