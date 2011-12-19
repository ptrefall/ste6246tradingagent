#pragma once

//#include <Windows.h>
//#include <GL\GL.h>
#include <vector>

#include "../glm/glm.hpp"


struct PriceData
{
  glm::vec3 position;
	float _size;
};


class ElSpotPriceLoader  {

public:
	ElSpotPriceLoader();
	void loadPriceData(const char* filename);

	float getCellFraction(int frame, float Troms);
	int getCellsTroms();
	int getNoFrames();
	std::vector<std::vector< float>> &getPriceData() {return _priceData;}
	glm::vec3 getCellsOrigin();

private:
	int _no_frames;
	int _totCells;
	int _cellsTroms;
	int _cellStartPrices; 


  std::vector<std::vector< float>> _priceData;

};
