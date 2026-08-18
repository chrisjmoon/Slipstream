import datetime as dt
from dataclasses import dataclass

from market_types import Aggressor, Price, Symbol


def _parse_symbol(symbol_string: str) -> Symbol:
    """Maps a string to a Symbol enum.

    Raises:
        ValueError: if the input cannot be parsed as a Symbol.
    """
    try:
        return Symbol(symbol_string)
    except ValueError:
        raise ValueError(f"Cannot parse symbol: {symbol_string}") from None


def _parse_aggressor(aggressor_string: str) -> Aggressor:
    """Maps a string to an Aggressor enum.

    Raises:
        ValueError: if the input cannot be parsed as an Aggressor.
    """
    try:
        return Aggressor(aggressor_string)
    except ValueError:
        raise ValueError(
            f"Cannot parse aggressor: {aggressor_string}") from None


@dataclass
class QuoteData:
    timestamp: dt.time
    symbol: Symbol
    bid_price: Price
    bid_quantity: int
    ask_price: Price
    ask_quantity: int


@dataclass
class TradeData:
    timestamp: dt.time
    symbol: Symbol
    price: Price
    quantity: int
    aggressor: Aggressor


def _parse_timestamp(timestamp_string: str) -> dt.time:
    """Parses a timestamp string of the form HH:MM:SS.sss on a 24 hour clock.

    An assumption we make about the data is that the time range of the data does not span
    longer than 24 hours; timestamps that occur at the same time on different days would
    otherwise be ambiguous.
    """
    return dt.datetime.strptime(timestamp_string, "%H:%M:%S.%f").time()


def _is_ignorable_row(line: str) -> bool:
    return not line or line[0] == "#" or line.startswith("Timestamp,")


def parse_quote_data_from_csv(csv_path: str) -> list[QuoteData]:
    """Parses market quotes from a CSV of newline separated market quotes and trade prints.

    Market quotes should be of the form: HH:MM:SS.sss,Q,SYMBOL,BID_PRICE,BID_QTY,ASK_PRICE,ASK_QTY.
    """
    quotes: list[QuoteData] = []

    with open(csv_path, "r") as file:
        for line in file:
            line = line.rstrip("\n")
            if _is_ignorable_row(line):
                continue

            fields = line.split(",")
            if fields[1] != "Q":
                continue

            quotes.append(
                QuoteData(
                    timestamp=_parse_timestamp(fields[0]),
                    symbol=_parse_symbol(fields[2]),
                    bid_price=Price(fields[3]),
                    bid_quantity=int(fields[4]),
                    ask_price=Price(fields[5]),
                    ask_quantity=int(fields[6]),
                )
            )

    return quotes


def parse_trade_data_from_csv(csv_path: str) -> list[TradeData]:
    """Parses trade prints from a CSV of newline separated market quotes and trade prints.

    Trade prints should be of the form: HH:MM:SS.sss,T,SYMBOL,,,,,PRICE,QTY,AGGRESSOR.
    """
    trades: list[TradeData] = []

    with open(csv_path, "r") as file:
        for line in file:
            line = line.rstrip("\n")
            if _is_ignorable_row(line):
                continue

            fields = line.split(",")
            if fields[1] != "T":
                continue

            trades.append(
                TradeData(
                    timestamp=_parse_timestamp(fields[0]),
                    symbol=_parse_symbol(fields[2]),
                    price=Price(fields[7]),
                    quantity=int(fields[8]),
                    aggressor=_parse_aggressor(fields[9]),
                )
            )

    return trades


def main() -> None:
    quotes = parse_quote_data_from_csv("Quotes_and_Trades.csv")
    trades = parse_trade_data_from_csv("Quotes_and_Trades.csv")
    print(f"Parsed {len(quotes)} quotes and {len(trades)} trades")


if __name__ == "__main__":
    main()
