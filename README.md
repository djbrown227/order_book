# Order Book Simulation Program

This repository contains a multi-threaded C++ simulation of an order book and various trading strategies. It demonstrates key concepts in market trading, including order matching, mean reversion, and market making, all within a simulated market environment. This project is designed to showcase my skills in algorithmic trading, multi-threading, and financial market data processing.

## Overview

The program simulates a financial market with continuously changing prices and an order book that handles buy and sell orders. Three trading strategies are implemented:

1. **Basic Trading Strategy:** Places random buy and sell orders based on the latest market price.
2. **Mean Reversion Strategy:** Places buy or sell orders based on deviations from a moving average of past prices.
3. **Market Maker Strategy:** Places buy and sell orders around the current market price to capture the spread.

### Key Components

- **MarketData Class:**
  - Simulates market price changes using a normal distribution.
  - Provides the latest price in a thread-safe manner.

- **OrderBook Class:**
  - Manages buy and sell orders.
  - Matches buy and sell orders based on price.
  - Displays the current state of the order book.

- **TradingStrategy Class:**
  - Implements different trading strategies:
    - **Basic Trading Strategy:** Randomized buy and sell orders.
    - **Mean Reversion Strategy:** Buys or sells based on price deviations from a moving average.
    - **Market Maker Strategy:** Places buy and sell orders around the spread.
  - Tracks balance and trading volume.

## Getting Started

### Prerequisites

- A C++17 compatible compiler (e.g., GCC, Clang)
- CMake for build automation (optional but recommended)
- Basic understanding of financial trading concepts and multi-threaded programming

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/order-book-simulation.git
   cd order-book-simulation
   ```

2. Compile the program using your preferred method. For example, using `g++`:
   ```bash
   g++ -std=c++17 -pthread main.cpp MarketData.cpp OrderBook.cpp TradingStrategy.cpp -o order_book_simulation
   ```

3. Run the compiled executable:
   ```bash
   ./order_book_simulation
   ```

### Running the Simulation

The main simulation runs in a loop, where market data is continuously generated, and trading strategies are executed in separate threads. The order book is regularly matched and displayed, showing the current state of buy and sell orders. Balances and trading volumes are updated and displayed after each iteration.

## Features

- **Real-Time Market Data Simulation:** The `MarketData` class generates continuous price changes, simulating real market conditions.
- **Order Matching:** The `OrderBook` class efficiently matches buy and sell orders based on price, simulating a real exchange.
- **Multi-Threaded Execution:** Each strategy runs in a separate thread, allowing for concurrent execution and simulating real-time trading.
- **Strategy Implementations:**
  - **Basic Trading Strategy:** Places randomized orders, useful for stress testing the order book.
  - **Mean Reversion:** Exploits deviations from a moving average, a common quantitative trading strategy.
  - **Market Maker:** Places orders around the current price, capturing the spread and providing liquidity to the market.

## Example Output

During execution, the program outputs the following:

- **Orders Placed:** Displays the details of each buy and sell order placed.
- **Order Book State:** Shows the current buy and sell orders at various prices.
- **Balance and Volume:** Continuously updates and displays the balance and total volume traded by the strategies.

Example output snippet:
```
Placed Buy Order: 7 @ 99.8 | Balance: 9926.6 | Volume: 7
Matched 5 at 100.1
Balance: 10026.1, Volume: 12
```

## Future Enhancements

- **Advanced Strategies:** Implement additional strategies such as momentum trading or arbitrage.
- **Data Persistence:** Save the order book and trading results to a file for further analysis.
- **Visualization:** Create visualizations of price movements, order book depth, and trading performance.
