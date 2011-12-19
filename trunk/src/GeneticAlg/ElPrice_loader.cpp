#include <fstream>
#include <sstream>
#include <iostream>
#include "ElPrice_loader.h"


ElSpotPriceLoader::ElSpotPriceLoader(){
	_no_frames       = 0;
	_cellStartPrices = 0;
	_cellsTroms      = 0;
}


void ElSpotPriceLoader::loadPriceData( const char* filename ) {

	std::ifstream stream( filename, std::ios::in); // | std::ios::binary );

	std::streampos stream_length;

	stream.seekg( 0, std::ios::end );
	stream_length = stream.tellg();
	stream.seekg( 0, std::ios::beg );

	std::vector<char> buffer( stream_length );
  stream.read(&buffer[0], stream_length );


	stream.close();

	std::stringstream ss(&buffer[0]);

	int no_frames = 0;
	int max_no_particles = 0;

	while( !ss.eof() ) {

		std::string w;
		ss >> w;
		ss.ignore( 256, '\n' );

		if( !w.compare( "printing" ) ) {

			no_frames++;

//			std::string str;
			int no_p;
//			ss >> str >> str >> str >> str;
			ss >> no_p;

			if( no_p > max_no_particles )
				max_no_particles = no_p;
		}
	}

	_priceData.resize(no_frames);

	ss.clear();
	ss.seekg(0,std::ios::beg);


	int frame = 0;

	while( !ss.eof() ) {

		std::string w;
		ss >> w;
		ss.ignore( 256, '\n' );

		if( !w.compare( "printing " ) ) {

			std::string str;
			int frame_nr; //, no_p;
			double t;
			ss >> frame_nr; // >> str >> t >> str >> no_p;

			ss.ignore( 256, '\n' );

	//		if( no_p != 0 ) {
       while(!ss.eof()) {
				ss.ignore( 256, '\n' );

				for( int j = 0; j < 2770; j++ ) {

			//		int p;
					float price_kWh;
					ss >> price_kWh;

					_priceData[frame].push_back(price_kWh);

          std::cout << "         Price kWh: " << price_kWh;
					ss.ignore( 256, '\n' );
				}
			}

			frame++;
		}
	}
 _no_frames = _priceData.size();

}

int ElSpotPriceLoader::getCellsTroms(){return _cellsTroms;}
int ElSpotPriceLoader::getNoFrames(){return _no_frames;}


glm::vec3 ElSpotPriceLoader::getCellsOrigin()
{
	return glm::vec3( (float)_cellStartPrices);
}