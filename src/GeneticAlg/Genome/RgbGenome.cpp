#include "RgbGenome.h"
#include <math.h>

RgbGenome::RgbGenome(int r, int g, int b)
	: target(255, 125, 60), chromosome(r,g,b)
{
}

RgbGenome::~RgbGenome()
{
}

double RgbGenome::fitness()
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

void RgbGenome::setChromosomeValue(Rgb &chromosome, bool is_mutation, unsigned int generation)
{
	std::pair<Rgb,Rgb> from_to(this->chromosome, chromosome);
	this->chromosome = chromosome;
	mutations[generation] = from_to;
}

bool RgbGenome::wasMutatedInGeneration(const unsigned int &generation) const
{
	auto it = mutations.find(generation);
	if(it != mutations.end())
		return true;
	else
		return false;
}

std::vector<unsigned int> RgbGenome::getGenerationsOfMutation() const
{
	std::vector<unsigned int> generations;
	auto it = mutations.begin();
	for(; it != mutations.end(); ++it)
	{
		generations.push_back(it->first);
	}
	return generations;
}

