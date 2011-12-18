#pragma once

#include <vector>
#include <functional>
#include <Windows.h>

#include "IGeneticAlg.h"
#include <GeneticAlg\Genome\ProsumerGenome.h>

class ProsumerGeneticAlg : public IGeneticAlg<ProsumerGenome>
{
public:
	ProsumerGeneticAlg(	GAManager &mgr,
						unsigned int populationSize =			100, 
						double fitness_for_survival_threshold = 0.7, 
						double crossover_chance =				0.2, 
						unsigned int max_children_from_cross =	8, 
						double mutation_chance =				0.01,
						double start_saldo =					1.0, 
						double economic_capacity_base =			2.0, 
						double energy_production_base =			1.0, 
						double energy_consumption_base =		0.1, 
						double flex_rate_base =					0.01,
						unsigned int policy_base =				0
					  );

	virtual ~ProsumerGeneticAlg();

	static std::ostream &write(std::ostream& s, ProsumerGeneticAlg& d)
	{
		HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		s << "Generation: " << d.generation->id << ", population size: " << d.generation->population->size << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		/*if(d.generation->bestGenome)
		{
			if(d.generation->bestGenome->chromosomeValue().saldo == 1.0)
			{
				s << "= Perfect individual: ";
				ProsumerGenome::write(s, *d.generation->bestGenome);
			}
			else
			{
				s << "= Best individual: ";
				ProsumerGenome::write(s, *d.generation->bestGenome);
			}
		}*/

		for(unsigned int i = 1; i < d.generation->population->individuals.size(); i++)
		{
			s << "- ";
			ProsumerGenome::write(s, *d.generation->population->individuals[i]);
		}
		s << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, ProsumerGeneticAlg& d)
	{
		return d.write(s,d);
	}

protected:
	bool mutate(ProsumerGenome &genome, double chance) const override;
	std::vector<ProsumerGenome*> crossover(ProsumerGenome &mum, ProsumerGenome &dad, unsigned int child_count, double chance) override;

	void calcMidpoint(Prosumer &midpoint, const Prosumer &a, const Prosumer &b) const;
	void calcDistance(Prosumer &distance, const Prosumer &a, const Prosumer &b) const;
	void calcResult(Prosumer &result, const Prosumer &midpoint, const Prosumer &distance) const;

protected:
	virtual ProsumerGenome *createInitialRandomGenome() override;
	std::vector<ProsumerGenome*> findSurvivors() override;
	void sortPopulation() override;
	void selectBestIndividual() override;

	double start_saldo;
	double economic_capacity_base;
	double energy_production_base;
	double energy_consumption_base;
	double flex_rate_base;
	unsigned int policy_base;
};

