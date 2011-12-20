#pragma once

#include <vector>

class ElSpotPriceLoader
{
public:
	static void loadPriceData(const char* filename, std::vector<double> &prices);
	static std::vector<double> static_prices;
};
