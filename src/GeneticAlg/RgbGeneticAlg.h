#pragma once

#include <vector>
#include <functional>
#include <algorithm>

#include "IGeneticAlg.h"
#include <GeneticAlg\Genome\RgbGenome.h>

class RgbGeneticAlg : public IGeneticAlg<RgbGenome>
{
public:
	RgbGeneticAlg(unsigned int populationSize = 100, unsigned int generationSurvivorCount = 10);
	virtual ~RgbGeneticAlg();

	static std::ostream &write(std::ostream& s, RgbGeneticAlg& d)
	{
		std::sort(d.generation->population->individuals.begin(), d.generation->population->individuals.end(), RgbGenomeSortPredicate<RgbGenome>);
		s << "Generation: " << d.generation->id << ", population size: " << d.generation->population->size << std::endl;
		for(unsigned int i = 0; i < d.generation->population->individuals.size(); i++)
		{
			s << "- ";
			RgbGenome::write(s, *d.generation->population->individuals[i]);
		}
		s << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, RgbGeneticAlg& d)
	{
		return d.write(s,d);
	}

protected:
	bool mutate(RgbGenome &genome, double chance) const override;
	std::vector<RgbGenome*> crossover(RgbGenome &mum, RgbGenome &dad, unsigned int child_count, double chance) override;

protected:
	virtual RgbGenome *createInitialRandomGenome() override;
	std::vector<RgbGenome*> findSurvivors() override;
};

