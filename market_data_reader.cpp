#include <fstream>
#include <string>
#include <vector>
std::ifstream file("Quotes_and_Trades.csv");

/*
 * An assumption we make about the data is that the time range of the data does not span longer
 * than 24 hours. Otherwise, because timestamps are of the form HH:MM:SS, timestamps that occur at
 * the same time on different days are ambiguous.
 */