#include "ProsumerGenome.h"
#include <math.h>

ProsumerGenome::ProsumerGenome(GAManager &mgr, double ec, double ep, double ef, double flex, unsigned int policy, double saldo)
	: mgr(mgr), chromosome(ec,ep,ef,flex,policy,saldo)
{
}

ProsumerGenome::~ProsumerGenome()
{
}

double ProsumerGenome::fitness(unsigned int generation)
{
	double energy_consumption_per_hour = chromosome.energy_consumption / chromosome.avg_per_hour_cost_factor;
	double low_consumption = chromosome.flexi_rate * energy_consumption_per_hour;
	
	double ef_lifetime_reduction_factor = (low_consumption / energy_consumption_per_hour)*(low_consumption / energy_consumption_per_hour);
	if(ef_lifetime_reduction_factor > 1.0f)
		ef_lifetime_reduction_factor = 1.0f;

	double bills_lifetime_reduction_factor = 1.0;
	if(chromosome.policy == 0)
		bills_lifetime_reduction_factor = buyAllEnergy_Strategy(generation, energy_consumption_per_hour);

	chromosome.saldo = (1.0 - (ef_lifetime_reduction_factor+bills_lifetime_reduction_factor)) * chromosome.saldo;

	return chromosome.saldo;
}

double ProsumerGenome::buyAllEnergy_Strategy(unsigned int generation, double energy_consumption_per_hour)
{
	double spot_price = 192.35 / 1000.0;
	double bill = energy_consumption_per_hour * spot_price;
	
	//If we can't pay our bills, we die
	if(chromosome.economic_capacity <= bill)
		return 1.0;

	double factor = bill / chromosome.economic_capacity;
	chromosome.economic_capacity = chromosome.economic_capacity - bill;
	return factor;
}

const Prosumer &ProsumerGenome::chromosomeValue() const
{
	return chromosome;
}

void ProsumerGenome::setChromosomeValue(Prosumer &chromosome, bool is_mutation, unsigned int generation)
{
	if(is_mutation)
	{
		std::pair<Prosumer,Prosumer> from_to(this->chromosome, chromosome);
		mutations[generation] = from_to;
	}
	this->chromosome = chromosome;
}

bool ProsumerGenome::wasMutatedInGeneration(const unsigned int &generation) const
{
	auto it = mutations.find(generation);
	if(it != mutations.end())
		return true;
	else
		return false;
}

std::vector<unsigned int> ProsumerGenome::getGenerationsOfMutation() const
{
	std::vector<unsigned int> generations;
	auto it = mutations.begin();
	for(; it != mutations.end(); ++it)
	{
		generations.push_back(it->first);
	}
	return generations;
}
