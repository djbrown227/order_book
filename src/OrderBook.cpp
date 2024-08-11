#include "OrderBook.h"
#include <iostream>
#include <iomanip> // For formatting order book display

// Adds a buy order to the order book
void OrderBook::addBuyOrder(double price, int quantity) {
    std::lock_guard<std::mutex> lock(orderBookMutex);
    buyOrders[price].push_back({ price, quantity });
}

// Adds a sell order to the order book
void OrderBook::addSellOrder(double price, int quantity) {
    std::lock_guard<std::mutex> lock(orderBookMutex);
    sellOrders[price].push_back({ price, quantity });
}

// Matches buy and sell orders
void OrderBook::matchOrders() {
    std::lock_guard<std::mutex> lock(orderBookMutex);

    while (!buyOrders.empty() && !sellOrders.empty()) {
        auto& highestBuy = buyOrders.rbegin()->second;
        auto& lowestSell = sellOrders.begin()->second;

        if (buyOrders.rbegin()->first >= sellOrders.begin()->first) {
            int tradeQuantity = std::min(highestBuy.front().quantity, lowestSell.front().quantity);

            highestBuy.front().quantity -= tradeQuantity;
            lowestSell.front().quantity -= tradeQuantity;

            std::cout << "Matched " << tradeQuantity << " at " << lowestSell.front().price << "\n";

            if (highestBuy.front().quantity == 0) {
                highestBuy.pop_front();
                if (highestBuy.empty()) {
                    buyOrders.erase(buyOrders.rbegin()->first);
                }
            }
            if (lowestSell.front().quantity == 0) {
                lowestSell.pop_front();
                if (lowestSell.empty()) {
                    sellOrders.erase(sellOrders.begin());
                }
            }
        } else {
            break;
        }
    }
}

// Displays the current state of the order book
void OrderBook::displayOrderBook() {
    std::lock_guard<std::mutex> lock(orderBookMutex);

    std::cout << "================== Order Book ==================\n";
    std::cout << std::setw(10) << "BUY" << " | " << std::setw(10) << "PRICE" << " | " << std::setw(10) << "SELL" << "\n";
    std::cout << "-------------------------------------------------\n";

    auto buyIt = buyOrders.rbegin();
    auto sellIt = sellOrders.begin();

    while (buyIt != buyOrders.rend() || sellIt != sellOrders.end()) {
        std::string buyQuantity = (buyIt != buyOrders.rend()) ? std::to_string(buyIt->second.front().quantity) : "";
        std::string buyPrice = (buyIt != buyOrders.rend()) ? std::to_string(buyIt->first) : "";
        std::string sellPrice = (sellIt != sellOrders.end()) ? std::to_string(sellIt->first) : "";
        std::string sellQuantity = (sellIt != sellOrders.end()) ? std::to_string(sellIt->second.front().quantity) : "";

        std::cout << std::setw(10) << buyQuantity << " | " << std::setw(10) << buyPrice << " | " << std::setw(10) << sellQuantity << "\n";

        if (buyIt != buyOrders.rend()) ++buyIt;
        if (sellIt != sellOrders.end()) ++sellIt;
    }

    std::cout << "=================================================\n";
}
