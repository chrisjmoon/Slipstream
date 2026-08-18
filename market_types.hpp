#pragma once

#include <cstdint>
#include <string>

enum class Symbol
{
    SYNTH1,
    SYNTH2,
    SYNTH3,
    SYNTH4,
    SYNTH5
};

enum class Aggressor
{
    BUY,
    SELL,
};

// Use abstraction so that the underlying type can be changed if different datasets require
// different precision or range requirements.

struct Price
{
    std::int64_t m_price;

    /**
     * Parses a price string of the form "DDDD.CC".
     *
     * @throws std::invalid_argument if the input is malformed.
     */
    explicit Price(std::string_view price_string);
};

using Quantity = std::uint64_t;