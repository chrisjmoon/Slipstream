#include "market_data_reader.hpp"
#include "market_types.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/*
 * Explicitly map string to a Symbol enum. Although the symbols in the dataset are of the form SYNTH
 * + N, we want to avoid coupling text format to enum ordinal values.
 */
Symbol parse_symbol(std::string_view symbol_text)
{
    if (symbol_text == "SYNTH1")
    {
        return Symbol::SYNTH1;
    }
    else if (symbol_text == "SYNTH2")
    {
        return Symbol::SYNTH2;
    }
    else if (symbol_text == "SYNTH3")
    {
        return Symbol::SYNTH3;
    }
    else if (symbol_text == "SYNTH4")
    {
        return Symbol::SYNTH4;
    }
    else if (symbol_text == "SYNTH5")
    {
        return Symbol::SYNTH5;
    }
    else
    {
        throw std::invalid_argument(std::format("Cannot parse symbol: {}", symbol_text));
    }
}

std::vector<QuoteData> parse_quote_data_from_csv(std::string_view csv_path)
{
    std::ifstream file(std::string{csv_path});
    if (!file)
    {
        throw std::runtime_error("Failed to read market data csv");
    }

    std::vector<QuoteData> quotes;

    std::string line;
    while (std::getline(file, line))
    {
        // Ignore header comments and the CSV column header row
        if (line.size() > 0 && (line[0] == '#' || line.starts_with("Timestamp,")))
        {
            continue;
        }

        std::istringstream line_stream{line};
        std::string field;

        // Extract timestamp
        std::chrono::nanoseconds timestamp;
        line_stream >> std::chrono::parse("%T", timestamp); // %T expects form HH:MM:SS:sss

        // Extract market data type
        std::getline(line_stream, field, ','); // Consume leftover comma after parsing timestamp
        std::getline(line_stream, field, ',');
        if (field != "Q")
        {
            continue;
        }

        // Extract symbol
        std::getline(line_stream, field, ',');
        Symbol symbol{parse_symbol(field)};

        // Extract bid price
        std::getline(line_stream, field, ',');
        Price bid_price{field};

        // Extract bid quantity
        std::getline(line_stream, field, ',');
        Quantity bid_quantity;
        std::from_chars(field.data(), field.data() + field.size(), bid_quantity);

        // Extract ask price
        std::getline(line_stream, field, ',');
        Price ask_price{field};

        // Extract ask quantity
        std::getline(line_stream, field, ',');
        Quantity ask_quantity;
        std::from_chars(field.data(), field.data() + field.size(), ask_quantity);

        quotes.push_back(
            QuoteData{timestamp, symbol, bid_price, bid_quantity, ask_price, ask_quantity});
    }

    return quotes;
}