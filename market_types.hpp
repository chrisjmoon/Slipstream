#pragma once

#include <cstdint>

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
using Price = std::int64_t;
using Quantity = std::uint64_t;