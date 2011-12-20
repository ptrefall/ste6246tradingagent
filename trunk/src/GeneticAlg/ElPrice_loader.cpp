#include <fstream>
#include <sstream>
#include <iostream>
#include "ElPrice_loader.h"

std::vector<double> ElSpotPriceLoader::static_prices;

void ElSpotPriceLoader::loadPriceData(const char* filename, std::vector<double> &prices)
{
	if(!static_prices.empty())
	{
		prices = static_prices;
		return;
	}

	std::ifstream stream( filename, std::ios::in);
	if(stream.bad())
	{
		stream.close();
		return;
	}

	std::streampos stream_length;
	stream.seekg( 0, std::ios::end );
	stream_length = stream.tellg();
	stream.seekg( 0, std::ios::beg );

	std::vector<char> buffer( stream_length );
	stream.read(&buffer[0], stream_length );
	stream.close();

	std::stringstream ss(&buffer[0]);

	//Skip header stuff
	for(unsigned int i = 0; i < 11; i++)
	{
		ss.ignore( 256, '\n' );
	}

	//Process actual price data
	while( !ss.eof() ) 
	{
		double price_kWh = 0.0;
		ss >> price_kWh;
		prices.push_back(price_kWh);
		static_prices.push_back(price_kWh);
	}
	ss.clear();
}
