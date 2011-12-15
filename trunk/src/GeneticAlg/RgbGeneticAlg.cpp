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

	for(unsigned int i = 0; i < child_count; i++)
	{
		double result = (std::rand()%1000000)/1000000.0;
		if(result <= chance)
		{
			Rgb midpoint;
			midpoint.r = (mum.chromosomeValue().r + dad.chromosomeValue().r) / 2.0;
			midpoint.g = (mum.chromosomeValue().g + dad.chromosomeValue().g) / 2.0;
			midpoint.b = (mum.chromosomeValue().b + dad.chromosomeValue().b) / 2.0;

			Rgb distance;
			distance.r = (int)fabs((double)mum.chromosomeValue().r - (double)dad.chromosomeValue().r);
			distance.g = (int)fabs((double)mum.chromosomeValue().g - (double)dad.chromosomeValue().g);
			distance.b = (int)fabs((double)mum.chromosomeValue().b - (double)dad.chromosomeValue().b);

			Rgb res;
			res.r = midpoint.r + distance.r * (((std::rand()%1000000)/1000000.0)*((std::rand()%1000000)/1000000.0));
			res.g = midpoint.g + distance.g * (((std::rand()%1000000)/1000000.0)*((std::rand()%1000000)/1000000.0));
			res.b = midpoint.b + distance.b * (((std::rand()%1000000)/1000000.0)*((std::rand()%1000000)/1000000.0));

			RgbGenome *child = new RgbGenome(res.r, res.g, res.b);
			children.push_back(child);
		}
	}

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
