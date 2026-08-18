from enum import Enum


class Symbol(Enum):
    SYNTH1 = "SYNTH1"
    SYNTH2 = "SYNTH2"
    SYNTH3 = "SYNTH3"
    SYNTH4 = "SYNTH4"
    SYNTH5 = "SYNTH5"


class Aggressor(Enum):
    BUY = "B"
    SELL = "S"


class Price:
    """Abstracts price so that the underlying representation can be changed according to
    dataset requirements.
    """

    __slots__ = ("m_price",)

    def __init__(self, price_string: str):
        """Parses a price string of the form "DD.CC", e.g. "87.54".

        Raises:
            ValueError: if the input is malformed.
        """
        decimal_point = price_string.find(".")
        if decimal_point == -1 or decimal_point != len(price_string) - 3:
            raise ValueError(
                f"Price string without decimal point: {price_string}")

        price = 0
        for ch in price_string[:decimal_point]:
            if not ch.isdigit():
                raise ValueError("Price string is not all digits")
            price = price * 10 + int(ch)
        price *= 10_000

        cents = 0
        for ch in price_string[decimal_point + 1:]:
            if not ch.isdigit():
                raise ValueError("Price string is not all digits")
            cents = cents * 10 + int(ch)
        cents *= 100

        self.m_price = price + cents
