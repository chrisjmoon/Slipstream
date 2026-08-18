#include "market_types.hpp"
#include <format>
#include <stdexcept>

Price::Price(std::string_view price_string)
{
    size_t decimal_point{price_string.find('.')};
    if (decimal_point == std::string_view::npos || decimal_point != price_string.size() - 3)
    {
        throw std::invalid_argument(
            std::format("Price string without decimal point: {}", price_string));
    }

    std::int64_t price{};
    for (size_t i{}; i < decimal_point; i++)
    {
        if ('0' > price_string[i] || price_string[i] > '9')
        {
            throw std::invalid_argument("Price string is not all digits");
        }

        price *= 10;
        price += (price_string[i] - '0');
    }
    price *= 10'000;

    std::int64_t cents{};
    for (size_t i{decimal_point + 1}; i < price_string.size(); i++)
    {
        if ('0' > price_string[i] || price_string[i] > '9')
        {
            throw std::invalid_argument("Price string is not all digits");
        }

        cents *= 10;
        cents += (price_string[i] - '0');
    }

    cents *= 100;
    price += cents;
    m_price = price;
}