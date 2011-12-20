#include "SupplierGeneticAlg.h"
#include <algorithm>


SupplierGeneticAlg::SupplierGeneticAlg(GAManager &mgr,
										unsigned int population_size, 
										double fitness_for_survival_threshold, 
										double crossover_chance, 
										unsigned int max_children_from_cross, 
										double mutation_chance,
										double start_saldo, 
										double price_offer_base, 
										double supply_capacity_base, 
										double participation_cost_base)

	: IGeneticAlg<SupplierGenome>(	mgr,
										population_size, 
										fitness_for_survival_threshold, 
										crossover_chance, 
										max_children_from_cross, 
										mutation_chance
								 ), 
								 start_saldo(start_saldo), 
								 price_offer_base(price_offer_base), 
								 supply_capacity_base(supply_capacity_base), 
								 participation_cost_base(participation_cost_base)
{
}

SupplierGeneticAlg::~SupplierGeneticAlg()
{
}

bool SupplierGeneticAlg::mutate(SupplierGenome &genome, double chance) const
{
	bool genome_was_mutated = false;
	Supplier value = genome.chromosomeValue();
	
	Supplier temp;
	temp.price_offer = value.price_offer;
	temp.supply_capacity = value.supply_capacity;
	temp.participation_cost = value.participation_cost;

	double result = randomize();
	if(result <= chance)
	{
		temp.price_offer = (price_offer_base*0.5) + randomize()*price_offer_base;
		genome_was_mutated = true;
	}
	result = randomize();
	if(result <= chance)
	{
		temp.supply_capacity = (supply_capacity_base*0.5) + randomize()*supply_capacity_base;
		genome_was_mutated = true;
	}

	if(genome_was_mutated)
	{
		Supplier midpoint;
		calcMidpoint(midpoint, value, temp);
		
		Supplier distance;
		calcDistance(distance, value, temp);

		calcResult(value, midpoint, distance);
		genome.setChromosomeValue(value, true, generation->id);
	}

	return genome_was_mutated;
}

std::vector<SupplierGenome*> SupplierGeneticAlg::crossover(SupplierGenome &mum, SupplierGenome &dad, unsigned int child_count, double chance)
{
	std::vector<SupplierGenome*> children;

	double result = randomize();
	if(result <= chance)
	{
		for(unsigned int i = 0; i < child_count; i++)
		{
			Supplier midpoint;
			calcMidpoint(midpoint, mum.chromosomeValue(), dad.chromosomeValue());

			Supplier distance;
			calcDistance(distance, mum.chromosomeValue(), dad.chromosomeValue());

			Supplier res;
			calcResult(res, midpoint, distance);

			SupplierGenome *child = new SupplierGenome(	mgr,
																	mum.chromosomeValue().price_strategy,
																	res.price_offer, 
																	res.supply_capacity, 
																	res.saldo,
																	res.participation_cost);
			children.push_back(child);
		}
	}

	return children;
}

void SupplierGeneticAlg::calcMidpoint(Supplier &midpoint, const Supplier &a, const Supplier &b) const
{
	midpoint.price_offer = (a.price_offer + b.price_offer) / 2.0;
	midpoint.supply_capacity = (a.supply_capacity + b.supply_capacity) / 2.0;
	midpoint.saldo = (a.saldo + b.saldo) / 2.0;
	midpoint.participation_cost = (a.participation_cost + b.participation_cost) / 2.0;
}

void SupplierGeneticAlg::calcDistance(Supplier &distance, const Supplier &a, const Supplier &b) const 
{
	distance.price_offer = (int)fabs((double)a.price_offer - (double)b.price_offer);
	distance.supply_capacity = (int)fabs((double)a.supply_capacity - (double)b.supply_capacity);
	distance.saldo = (int)fabs((double)a.saldo - (double)b.saldo);
	distance.participation_cost = (int)fabs((double)a.participation_cost - (double)b.participation_cost);
}

void SupplierGeneticAlg::calcResult(Supplier &result, const Supplier &midpoint, const Supplier &distance) const
{
	result.price_offer = midpoint.price_offer + distance.price_offer * (randomize()*randomize());
	result.supply_capacity = midpoint.supply_capacity + distance.supply_capacity * (randomize()*randomize());
	result.saldo = midpoint.saldo + distance.saldo * (randomize()*randomize());
	result.participation_cost = midpoint.participation_cost;
}

SupplierGenome *SupplierGeneticAlg::createInitialRandomGenome(unsigned int index, unsigned int population_size)
{
	double po = price_offer_base/**0.5) + randomize()*price_offer_base*/;
	double sc = supply_capacity_base/**0.5) + randomize()*supply_capacity_base*/;
	double pc = participation_cost_base/**0.5) + randomize()*participation_cost_base*/;

	if(index < population_size/2)
		return new SupplierGenome(mgr, SPS_FIXED_PRICE, po,sc,start_saldo,pc);
	else
		return new SupplierGenome(mgr, SPS_SPOT_PRICE, po,sc,start_saldo,pc);
}

std::vector<SupplierGenome*> SupplierGeneticAlg::findSurvivors()
{
	std::vector<SupplierGenome*> survivors;

	sortPopulation();
	for(unsigned int i = 0; i < generation->population->individuals.size(); i++)
	{
		if(generation->population->individuals[i]->chromosomeValue().saldo > generation->fitness_for_survival_threshold)
			survivors.push_back(generation->population->individuals[i]);
	}

	unsigned int deaths = generation->population->individuals.size() - survivors.size();

	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	//std::cout << "Fixed Supplier Deaths: " << deaths << std::endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	return survivors;
}

void SupplierGeneticAlg::sortPopulation()
{
	std::sort(generation->population->individuals.begin(), generation->population->individuals.end(), SupplierGenomeSortPredicate<SupplierGenome>);
}

void SupplierGeneticAlg::selectBestIndividual()
{
	if(generation->population->individuals.empty())
	{
		generation->bestGenome = 0x0;
		return;
	}

	sortPopulation();
	generation->bestGenome = generation->population->individuals[0];
}
