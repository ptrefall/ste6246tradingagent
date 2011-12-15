#include "RgbGenome.h"
#include <math.h>

RgbGenome::RgbGenome(int r, int g, int b)
	: target(255, 125, 60), chromosome(r,g,b)
{
}

RgbGenome::~RgbGenome()
{
}

double RgbGenome::fitness() const
{
	//Some fitness function goes here
	int maxDiff = 255*3;

	int rDiff = abs(chromosome.r - target.r);
	int gDiff = abs(chromosome.g - target.g);
	int bDiff = abs(chromosome.b - target.b);

	int totalDiff = rDiff+gDiff+bDiff;

	return ((double)(maxDiff-totalDiff))/((double)maxDiff);
}

const Rgb &RgbGenome::chromosomeValue() const
{
	return chromosome;
}

void RgbGenome::setChromosomeValue(Rgb &chromosome)
{
	this->chromosome.r = chromosome.r;
	this->chromosome.g = chromosome.g;
	this->chromosome.b = chromosome.b;
}
