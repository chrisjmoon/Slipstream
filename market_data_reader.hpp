#pragma once

#include "market_types.hpp"
#include <chrono>
#include <vector>

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
    std::chrono::nanoseconds timestamp;
    Symbol symbol;
    Quantity quantity;
    Price price;
    Aggressor aggressor;
};

/*
 * The CSV should be newline separated market quotes and trade prints. Market quotes should be of
 * the form: HH:MM:SS.sss,Q,SYMBOL,BID_PRICE,BID_QTY,ASK_PRICE,ASK_QTY. Trade prints should be of
 * the form:
 *
 * An assumption we make about the data is that the time range of the data does not span longer
 * than 24 hours. Otherwise, because timestamps are of the form HH:MM:SS, timestamps that occur at
 * the same time on different days are ambiguous.
 */
std::vector<QuoteData> parse_quote_data_from_csv(std::string_view csv_path);

std::vector<TradeData> parse_trade_data_from_csv(std::string_view csv_path);