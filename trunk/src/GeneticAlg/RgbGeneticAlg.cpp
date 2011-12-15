#include "RgbGeneticAlg.h"
#include <algorithm>


RgbGeneticAlg::RgbGeneticAlg(unsigned int populationSize, unsigned int generationSurvivorCount)
	: IGeneticAlg<RgbGenome>(populationSize, generationSurvivorCount)
{
}

RgbGeneticAlg::~RgbGeneticAlg()
{
}

bool RgbGeneticAlg::mutate(RgbGenome &genome, double chance) const
{
	bool genome_was_mutated = false;
	Rgb value = genome.chromosomeValue();

	double result = (std::rand()%1000000)/1000000.0;
	if(result <= chance)
	{
		value.r = std::rand()%256;
		genome_was_mutated = true;
	}
	result = (std::rand()%1000000)/1000000.0;
	if(result <= chance)
	{
		value.g = std::rand()%256;
		genome_was_mutated = true;
	}
	result = (std::rand()%1000000)/1000000.0;
	if(result <= chance)
	{
		value.b = std::rand()%256;
		genome_was_mutated = true;
	}

	if(genome_was_mutated)
		genome.setChromosomeValue(value);

	return genome_was_mutated;
}

std::vector<RgbGenome*> RgbGeneticAlg::crossover(RgbGenome &mum, RgbGenome &dad, unsigned int child_count, double chance)
{
	std::vector<RgbGenome*> children;
	return children;
}

RgbGenome *RgbGeneticAlg::createInitialRandomGenome()
{
	int r = std::rand()%256;
	int g = std::rand()%256;
	int b = std::rand()%256;
	return new RgbGenome(r,g,b);
}

std::vector<RgbGenome*> RgbGeneticAlg::findSurvivors()
{
	std::vector<RgbGenome*> survivors;

	std::sort(generation->population->individuals.begin(), generation->population->individuals.end(), RgbGenomeSortPredicate<RgbGenome>);
	for(unsigned int i = 0; i < generation->survivorCount; i++)
		survivors.push_back(generation->population->individuals[i]);

	return survivors;
}
