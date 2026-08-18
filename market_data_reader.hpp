#pragma once

#include <chrono>
#include <market_types.hpp>

struct QuoteData
{
    std::chrono::nanoseconds timestamp;
    Symbol symbol;
    Price bid_price;
    Quantity bid_quantity;
    Price ask_price;
    Quantity ask_quantity;
};

struct TradeData
{
    Quantity quantity;
    Price price;
    Aggressor aggressor;
};