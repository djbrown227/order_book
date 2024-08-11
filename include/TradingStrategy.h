#ifndef TRADING_STRATEGY_H
#define TRADING_STRATEGY_H

#include "OrderBook.h"
#include "MarketData.h"

// TradingStrategy class to implement a basic strategy
class TradingStrategy {
public:
    TradingStrategy(OrderBook& orderBook, MarketData& marketData);

    // Executes the trading strategy
    void executeStrategy();

private:
    OrderBook& orderBook;
    MarketData& marketData;
};

#endif // TRADING_STRATEGY_H
