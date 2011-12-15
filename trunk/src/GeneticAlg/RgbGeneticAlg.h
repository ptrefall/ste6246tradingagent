#pragma once

#include <vector>
#include <functional>

#include "IGeneticAlg.h"
#include <GeneticAlg\Genome\RgbGenome.h>

class RgbGeneticAlg : public IGeneticAlg<RgbGenome>
{
public:
	RgbGeneticAlg(unsigned int populationSize = 100, unsigned int generationSurvivorCount = 10);
	virtual ~RgbGeneticAlg();

protected:
	bool mutate(RgbGenome &genome, double chance) const override;
	std::vector<RgbGenome*> crossover(RgbGenome &mum, RgbGenome &dad, unsigned int child_count, double chance) override;

protected:
	RgbGenome *createInitialRandomGenome() override;
	std::vector<RgbGenome*> findSurvivors() override;
};

