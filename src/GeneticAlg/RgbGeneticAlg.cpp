#include "RgbGeneticAlg.h"
#include <algorithm>


RgbGeneticAlg::RgbGeneticAlg(unsigned int populationSize, double fitness_for_survival_threshold, double crossover_chance, double mutation_chance)
	: IGeneticAlg<RgbGenome>(populationSize, fitness_for_survival_threshold, crossover_chance, 8, mutation_chance)
{
}

RgbGeneticAlg::~RgbGeneticAlg()
{
}

bool RgbGeneticAlg::mutate(RgbGenome &genome, double chance) const
{
	bool genome_was_mutated = false;
	Rgb value = genome.chromosomeValue();
	Rgb temp;
	temp.r = value.r;
	temp.g = value.g;
	temp.b = value.b;

	double result = (std::rand()%1000000)/1000000.0;
	if(result <= chance)
	{
		temp.r = std::rand()%256;
		genome_was_mutated = true;
	}
	result = (std::rand()%1000000)/1000000.0;
	if(result <= chance)
	{
		temp.g = std::rand()%256;
		genome_was_mutated = true;
	}
	result = (std::rand()%1000000)/1000000.0;
	if(result <= chance)
	{
		temp.b = std::rand()%256;
		genome_was_mutated = true;
	}

	if(genome_was_mutated)
	{
		Rgb midpoint;
		midpoint.r = (value.r + temp.r) / 2.0;
		midpoint.g = (value.g + temp.g) / 2.0;
		midpoint.b = (value.b + temp.b) / 2.0;
		Rgb distance;
		distance.r = (int)fabs((double)value.r - (double)temp.r);
		distance.g = (int)fabs((double)value.g - (double)temp.g);
		distance.b = (int)fabs((double)value.b - (double)temp.b);
		value.r = midpoint.r + distance.r * (((std::rand()%1000000)/1000000.0)*((std::rand()%1000000)/1000000.0));
		value.g = midpoint.g + distance.g * (((std::rand()%1000000)/1000000.0)*((std::rand()%1000000)/1000000.0));
		value.b = midpoint.b + distance.b * (((std::rand()%1000000)/1000000.0)*((std::rand()%1000000)/1000000.0));
		genome.setChromosomeValue(value, true, generation->id);
	}

	return genome_was_mutated;
}

std::vector<RgbGenome*> RgbGeneticAlg::crossover(RgbGenome &mum, RgbGenome &dad, unsigned int child_count, double chance)
{
	std::vector<RgbGenome*> children;

	/*if(	mum.chromosomeValue().r == dad.chromosomeValue().r &&
		mum.chromosomeValue().g == dad.chromosomeValue().g &&
		mum.chromosomeValue().b == dad.chromosomeValue().b )
	{
		return children;
	}*/

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

			bool duplicate = false;
			/*for(unsigned int i = 0; i < children.size(); i++)
			{
				if(	res.r == children[i]->chromosomeValue().r && 
					res.g == children[i]->chromosomeValue().g &&
					res.b == children[i]->chromosomeValue().b )
				{
					duplicate = true;
					break;
				}
			}*/

			if(duplicate == false)
			{
				RgbGenome *child = new RgbGenome(res.r, res.g, res.b);
				children.push_back(child);
			}
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

	sortPopulation();
	for(unsigned int i = 0; i < generation->population->individuals.size(); i++)
	{
		if(generation->population->individuals[i]->fitness() >= generation->fitness_for_survival_threshold)
			survivors.push_back(generation->population->individuals[i]);
	}



	return survivors;
}

void RgbGeneticAlg::sortPopulation()
{
	std::sort(generation->population->individuals.begin(), generation->population->individuals.end(), RgbGenomeSortPredicate<RgbGenome>);
}

void RgbGeneticAlg::selectBestIndividual()
{
	if(generation->population->individuals.empty())
	{
		generation->bestGenome = 0x0;
		return;
	}

	sortPopulation();
	generation->bestGenome = generation->population->individuals[0];
}
