#include "FixedSupplierGenome.h"
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

const FixedSupplier &FixedSupplierGenome::chromosomeValue() const
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
