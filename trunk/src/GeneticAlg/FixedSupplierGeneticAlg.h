#pragma once

#include <vector>
#include <functional>
#include <Windows.h>

#include "IGeneticAlg.h"
#include <GeneticAlg\Genome\FixedSupplierGenome.h>

class FixedSupplierGeneticAlg : public IGeneticAlg<FixedSupplierGenome>
{
public:
	FixedSupplierGeneticAlg(GAManager &mgr,
						unsigned int population_size =			10, 
						double fitness_for_survival_threshold = 0.0, 
						double crossover_chance =				0.2, 
						unsigned int max_children_from_cross =	2, 
						double mutation_chance =				0.01,
						double start_saldo =					1.0, 
						double price_offer_base =				2.0, 
						double supply_capacity_base =			1.0, 
						double participation_cost_base =		0.01
					  );

	virtual ~FixedSupplierGeneticAlg();

	static std::ostream &write(std::ostream& s, FixedSupplierGeneticAlg& d)
	{
		HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		s << "Generation: " << d.generation->id << ", population: " << d.generation->population->size << std::endl;
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
			FixedSupplierGenome::write(s, *d.generation->population->individuals[i]);
		}
		s << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, FixedSupplierGeneticAlg& d)
	{
		return d.write(s,d);
	}

protected:
	bool mutate(FixedSupplierGenome &genome, double chance) const override;
	std::vector<FixedSupplierGenome*> crossover(FixedSupplierGenome &mum, FixedSupplierGenome &dad, unsigned int child_count, double chance) override;

	void calcMidpoint(FixedSupplier &midpoint, const FixedSupplier &a, const FixedSupplier &b) const;
	void calcDistance(FixedSupplier &distance, const FixedSupplier &a, const FixedSupplier &b) const;
	void calcResult(FixedSupplier &result, const FixedSupplier &midpoint, const FixedSupplier &distance) const;

protected:
	virtual FixedSupplierGenome *createInitialRandomGenome() override;
	std::vector<FixedSupplierGenome*> findSurvivors() override;
	void sortPopulation() override;
	void selectBestIndividual() override;

	double start_saldo;
	double price_offer_base;
	double supply_capacity_base;
	double participation_cost_base;
};

