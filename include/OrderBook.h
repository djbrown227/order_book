#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <deque>
#include <mutex>

// Order struct for managing orders
struct Order {
    double price;
    int quantity;
};

// OrderBook class to manage buy and sell orders
class OrderBook {
public:
    // Adds a new buy order
    void addBuyOrder(double price, int quantity);

    // Adds a new sell order
    void addSellOrder(double price, int quantity);

    // Matches buy and sell orders
    void matchOrders();

    // Displays the current state of the order book
    void displayOrderBook();

    std::mutex orderBookMutex;

private:
    std::map<double, std::deque<Order>> buyOrders;  // Buy orders map (price -> queue of orders)
    std::map<double, std::deque<Order>> sellOrders; // Sell orders map (price -> queue of orders)
};

#endif // ORDER_BOOK_H
