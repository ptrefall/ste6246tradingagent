#include "ProsumerGenome.h"
#include <math.h>

ProsumerGenome::ProsumerGenome(double ec, double ep, double ef, double flex, unsigned int policy)
	: chromosome(ec,ep,ef,flex,policy)
{
}

ProsumerGenome::~ProsumerGenome()
{
}

double ProsumerGenome::fitness()
{
	double energy_consumption_per_hour = chromosome.energy_consumption / chromosome.avg_per_hour_cost_factor;
	double low_consumption = chromosome.flexi_rate * energy_consumption_per_hour;
	double saldo_reduction_factor = (low_consumption / energy_consumption_per_hour)*(low_consumption / energy_consumption_per_hour);

	if(saldo_reduction_factor > 1.0f)
		saldo_reduction_factor = 1.0f;

	saldo = (1.0 - saldo_reduction_factor) * saldo;
	return saldo;
}

const Prosumer &ProsumerGenome::chromosomeValue() const
{
	return chromosome;
}

void ProsumerGenome::setChromosomeValue(Prosumer &chromosome, bool is_mutation, unsigned int generation)
{
	std::pair<Prosumer,Prosumer> from_to(this->chromosome, chromosome);
	this->chromosome = chromosome;
	mutations[generation] = from_to;
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
