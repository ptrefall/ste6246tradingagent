#include "FixedSupplierGenome.h"
#include "../GAManager.h"
#include <math.h>

FixedSupplierGenome::FixedSupplierGenome(GAManager &mgr, double po, double sc, double saldo, unsigned int cc, double pc)
	: mgr(mgr), chromosome(po,sc,saldo,cc,pc)
{
}

FixedSupplierGenome::~FixedSupplierGenome()
{
}

double FixedSupplierGenome::fitness(unsigned int generation)
{
	///////////////////////////////
	// Bargain price
	///////////////////////////////
	unsigned int prosumer_population_size = mgr.getProsumerPopulationSize();
	unsigned int suppliers_population_size = mgr.getSuppliersPopulationSize();
	unsigned int suppliers_supply_capacity = mgr.getSuppliersSupplyCapacity();
	double prosumer_vs_supplier_relation = (double)prosumer_population_size / (double)suppliers_population_size;

	//If the relation between number of customers and suppliers is more than double in size
	//compared to the estimated customer capacity of the competition, the fixed price suppliers
	//will add addition 15% to their fixed price.
	if(((unsigned int)prosumer_vs_supplier_relation*2.0) > suppliers_supply_capacity)
	{
		chromosome.actual_price_offer = chromosome.price_offer + (chromosome.price_offer*0.15);
	}
	//Else, if the relation between the customers and suppliers is one to one or less in size
	//compared to the estimated customer capacity of the competition, the fixed price suppliers
	//will subtract 15% from their fixed price.
	else if((unsigned int)prosumer_vs_supplier_relation <= suppliers_supply_capacity)
	{
		chromosome.actual_price_offer = chromosome.price_offer - (chromosome.price_offer*0.15);
	}
	//Otherwise, the price is unchanged.
	else
	{
		chromosome.actual_price_offer = chromosome.price_offer;
	}


	/*double energy_consumption_per_hour = chromosome.energy_consumption / chromosome.avg_per_hour_cost_factor;
	double low_consumption = chromosome.flexi_rate * energy_consumption_per_hour;
	
	double ef_lifetime_reduction_factor = (low_consumption / energy_consumption_per_hour)*(low_consumption / energy_consumption_per_hour);
	if(ef_lifetime_reduction_factor > 1.0f)
		ef_lifetime_reduction_factor = 1.0f;

	double bills_lifetime_reduction_factor = 1.0;
	if(chromosome.policy == 0)
		bills_lifetime_reduction_factor = buyAllEnergy_Strategy(generation, energy_consumption_per_hour);

	chromosome.saldo = (1.0 - (ef_lifetime_reduction_factor+bills_lifetime_reduction_factor)) * chromosome.saldo;*/

	return chromosome.saldo;
}

FixedSupplier &FixedSupplierGenome::chromosomeValue()
{
	return chromosome;
}

void FixedSupplierGenome::setChromosomeValue(FixedSupplier &chromosome, bool is_mutation, unsigned int generation)
{
	if(is_mutation)
	{
		std::pair<FixedSupplier,FixedSupplier> from_to(this->chromosome, chromosome);
		mutations[generation] = from_to;
	}
	this->chromosome = chromosome;
}

bool FixedSupplierGenome::wasMutatedInGeneration(const unsigned int &generation) const
{
	auto it = mutations.find(generation);
	if(it != mutations.end())
		return true;
	else
		return false;
}

std::vector<unsigned int> FixedSupplierGenome::getGenerationsOfMutation() const
{
	std::vector<unsigned int> generations;
	auto it = mutations.begin();
	for(; it != mutations.end(); ++it)
	{
		generations.push_back(it->first);
	}
	return generations;
}
