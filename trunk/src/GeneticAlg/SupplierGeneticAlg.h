#pragma once

#include <vector>
#include <functional>
#include <Windows.h>

#include "IGeneticAlg.h"
#include <GeneticAlg\Genome\SupplierGenome.h>

class SupplierGeneticAlg : public IGeneticAlg<SupplierGenome>
{
public:
	SupplierGeneticAlg(GAManager &mgr,
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

	virtual ~SupplierGeneticAlg();

	static std::ostream &write(std::ostream& s, SupplierGeneticAlg& d)
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
			SupplierGenome::write(s, *d.generation->population->individuals[i]);
		}
		s << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, SupplierGeneticAlg& d)
	{
		return d.write(s,d);
	}

protected:
	bool mutate(SupplierGenome &genome, double chance) const override;
	std::vector<SupplierGenome*> crossover(SupplierGenome &mum, SupplierGenome &dad, unsigned int child_count, double chance) override;

	void calcMidpoint(Supplier &midpoint, const Supplier &a, const Supplier &b) const;
	void calcDistance(Supplier &distance, const Supplier &a, const Supplier &b) const;
	void calcResult(Supplier &result, const Supplier &midpoint, const Supplier &distance) const;

protected:
	virtual SupplierGenome *createInitialRandomGenome(unsigned int index, unsigned int population_size) override;
	std::vector<SupplierGenome*> findSurvivors() override;
	void sortPopulation() override;
	void selectBestIndividual() override;

	double start_saldo;
	double price_offer_base;
	double supply_capacity_base;
	double participation_cost_base;
};

