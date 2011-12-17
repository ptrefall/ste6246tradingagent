#include "ProsumerGeneticAlg.h"
#include <algorithm>


ProsumerGeneticAlg::ProsumerGeneticAlg(	unsigned int populationSize, 
										double fitness_for_survival_threshold, 
										double crossover_chance, 
										unsigned int max_children_from_cross, 
										double mutation_chance,
										double start_saldo, 
										double economic_capacity_base, 
										double energy_production_base, 
										double energy_consumption_base, 
										double flex_rate_base,
										unsigned int policy_base)

	: IGeneticAlg<ProsumerGenome>(		populationSize, 
										fitness_for_survival_threshold, 
										crossover_chance, 
										max_children_from_cross, 
										mutation_chance
								 ), 
								 start_saldo(start_saldo), 
								 economic_capacity_base(economic_capacity_base), 
								 energy_production_base(energy_production_base), 
								 energy_consumption_base(energy_consumption_base), 
								 flex_rate_base(flex_rate_base),
								 policy_base(policy_base)
{
}

ProsumerGeneticAlg::~ProsumerGeneticAlg()
{
}

bool ProsumerGeneticAlg::mutate(ProsumerGenome &genome, double chance) const
{
	bool genome_was_mutated = false;
	Prosumer value = genome.chromosomeValue();
	
	Prosumer temp;
	temp.economic_capacity = value.economic_capacity;
	temp.energy_production_capacity = value.energy_production_capacity;
	temp.energy_consumption = value.energy_consumption;
	temp.flexi_rate = value.flexi_rate;
	temp.policy = value.policy;

	double result = randomize();
	if(result <= chance)
	{
		temp.economic_capacity = (economic_capacity_base*0.5) + randomize()*economic_capacity_base;
		genome_was_mutated = true;
	}
	result = randomize();
	if(result <= chance)
	{
		temp.energy_production_capacity = (energy_production_base*0.5) + randomize()*energy_production_base;
		genome_was_mutated = true;
	}
	result = randomize();
	if(result <= chance)
	{
		temp.energy_consumption = (energy_consumption_base*0.5) + randomize()*energy_consumption_base;
		genome_was_mutated = true;
	}
	result = randomize();
	if(result <= chance)
	{
		temp.flexi_rate = (flex_rate_base*0.5) + randomize()*flex_rate_base;
		genome_was_mutated = true;
	}
	result = randomize();
	if(result <= chance)
	{
		temp.policy = (policy_base*0.5) + randomize()*policy_base;
		genome_was_mutated = true;
	}

	if(genome_was_mutated)
	{
		Prosumer midpoint;
		calcMidpoint(midpoint, value, temp);
		
		Prosumer distance;
		calcDistance(distance, value, temp);

		calcResult(value, midpoint, distance);
		genome.setChromosomeValue(value, true, generation->id);
	}

	return genome_was_mutated;
}

std::vector<ProsumerGenome*> ProsumerGeneticAlg::crossover(ProsumerGenome &mum, ProsumerGenome &dad, unsigned int child_count, double chance)
{
	std::vector<ProsumerGenome*> children;

	/*if(	mum.chromosomeValue().r == dad.chromosomeValue().r &&
		mum.chromosomeValue().g == dad.chromosomeValue().g &&
		mum.chromosomeValue().b == dad.chromosomeValue().b )
	{
		return children;
	}*/

	for(unsigned int i = 0; i < child_count; i++)
	{
		double result = randomize();
		if(result <= chance)
		{
			Prosumer midpoint;
			calcMidpoint(midpoint, mum.chromosomeValue(), dad.chromosomeValue());

			Prosumer distance;
			calcDistance(distance, mum.chromosomeValue(), dad.chromosomeValue());

			Prosumer res;
			calcResult(res, midpoint, distance);

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
				ProsumerGenome *child = new ProsumerGenome(	res.economic_capacity, 
															res.energy_production_capacity, 
															res.energy_consumption,
															res.flexi_rate,
															res.policy,
															start_saldo);
				children.push_back(child);
			}
		}
	}

	return children;
}

void ProsumerGeneticAlg::calcMidpoint(Prosumer &midpoint, const Prosumer &a, const Prosumer &b) const
{
	midpoint.economic_capacity = (a.economic_capacity + b.economic_capacity) / 2.0;
	midpoint.energy_production_capacity = (a.energy_production_capacity + b.energy_production_capacity) / 2.0;
	midpoint.energy_consumption = (a.energy_consumption + b.energy_consumption) / 2.0;
	midpoint.flexi_rate = (a.flexi_rate + b.flexi_rate) / 2.0;
	midpoint.policy = (a.policy + b.policy) / 2.0;
}

void ProsumerGeneticAlg::calcDistance(Prosumer &distance, const Prosumer &a, const Prosumer &b) const 
{
	distance.economic_capacity = (int)fabs((double)a.economic_capacity - (double)b.economic_capacity);
	distance.energy_production_capacity = (int)fabs((double)a.energy_production_capacity - (double)b.energy_production_capacity);
	distance.energy_consumption = (int)fabs((double)a.energy_consumption - (double)b.energy_consumption);
	distance.flexi_rate = (int)fabs((double)a.flexi_rate - (double)b.flexi_rate);
	distance.policy = (int)fabs((double)a.policy - (double)b.policy);
}

void ProsumerGeneticAlg::calcResult(Prosumer &result, const Prosumer &midpoint, const Prosumer &distance) const
{
	result.economic_capacity = midpoint.economic_capacity + distance.economic_capacity * (randomize()*randomize());
	result.energy_production_capacity = midpoint.energy_production_capacity + distance.energy_production_capacity * (randomize()*randomize());
	result.energy_consumption = midpoint.energy_consumption + distance.energy_consumption * (randomize()*randomize());
	result.flexi_rate = midpoint.flexi_rate + distance.flexi_rate * (randomize()*randomize());
	result.policy = midpoint.policy + distance.policy * (randomize()*randomize());
}

ProsumerGenome *ProsumerGeneticAlg::createInitialRandomGenome()
{
	double ec = economic_capacity_base/**0.5) + randomize()*economic_capacity_base*/;
	double ep = energy_production_base/**0.5) + randomize()*energy_production_base*/;
	double ef = energy_consumption_base/**0.5) + randomize()*energy_consumption_base*/;
	double flex = flex_rate_base/**0.5) + randomize()*flex_rate_base*/;
	unsigned int policy = policy_base/**0.5) + randomize()*policy_base*/;
	return new ProsumerGenome(ec,ep,ef,flex,policy, start_saldo);
}

std::vector<ProsumerGenome*> ProsumerGeneticAlg::findSurvivors()
{
	std::vector<ProsumerGenome*> survivors;

	sortPopulation();
	for(unsigned int i = 0; i < generation->population->individuals.size(); i++)
	{
		if(generation->population->individuals[i]->chromosomeValue().saldo > generation->fitness_for_survival_threshold)
			survivors.push_back(generation->population->individuals[i]);
	}

	return survivors;
}

void ProsumerGeneticAlg::sortPopulation()
{
	std::sort(generation->population->individuals.begin(), generation->population->individuals.end(), ProsumerGenomeSortPredicate<ProsumerGenome>);
}

void ProsumerGeneticAlg::selectBestIndividual()
{
	if(generation->population->individuals.empty())
	{
		generation->bestGenome = 0x0;
		return;
	}

	sortPopulation();
	generation->bestGenome = generation->population->individuals[0];
}
