#include "GAManager.h"
#include "ProsumerGeneticAlg.h"
#include "FixedSupplierGeneticAlg.h"

GAManager::GAManager()
	: prosumerGA(0x0), fixedSupplierGA(0x0)
{
	prosumerGA = new ProsumerGeneticAlg(*this,
							100,		//Population Size 
							0.0,		//Fitness threshold
							0.05,		//Chance for crossover
							1,			//Max children from crossover
							0.05,		//Chance for mutation
							0.1,		//Start saldo
							3.0,		//Øk
							1.0,		//Ep
							24000.0,	//Ef
							0.1,		//Flex
							0);			//Policy

	fixedSupplierGA = new FixedSupplierGeneticAlg(*this,
							10,		//Population Size 
							0.0,		//Fitness threshold
							0.05,		//Chance for crossover
							1,			//Max children from crossover
							0.05,		//Chance for mutation
							0.1,		//Start saldo
							3.0,		//Price Offer
							1.0,		//Supply capacity
							1,			//Customer count
							0.01);		//Participation cost
}

GAManager::~GAManager()
{
	if(prosumerGA) delete prosumerGA;
	if(fixedSupplierGA) delete fixedSupplierGA;
}

void GAManager::initialize()
{
	if(prosumerGA) prosumerGA->initialize();
	if(fixedSupplierGA) fixedSupplierGA->initialize();
}

bool GAManager::evolve()
{
	bool finished = false;
	finished = prosumerGA->evolve();
	std::cout << *prosumerGA;
	if(finished)
		return finished;

	finished = fixedSupplierGA->evolve();
	std::cout << *fixedSupplierGA;
	if(finished)
		return finished;

	return false;
}

////////////////////////////////////////////////////
// PROSUMER HELPERS
////////////////////////////////////////////////////
unsigned int GAManager::getProsumerPopulationSize() const
{
	if(prosumerGA) return prosumerGA->generation->population->individuals.size();
	else return 0;
}

////////////////////////////////////////////////////
// GENERAL ALL SUPPLIERS HELPERS
////////////////////////////////////////////////////
unsigned int GAManager::getSuppliersPopulationSize() const
{
	unsigned int population_size = 0;
	population_size += getFixedSupplierPopulationSize();
	//population_size += getSpotSupplierPopulationSize();
	//population_size += getHybridSupplierPopulationSize();
	return population_size;
}

unsigned int GAManager::getSuppliersSupplyCapacity() const
{
	unsigned int supply_capacity = 0;
	supply_capacity += getFixedSupplierSupplyCapacitySUM();
	//supply_capacity += getSpotSupplierSupplyCapacitySUM();
	//supply_capacity += getHybridSupplierSupplyCapacitySUM();
	return supply_capacity;
}

////////////////////////////////////////////////////
// FIXED SUPPLIER HELPERS
////////////////////////////////////////////////////
unsigned int GAManager::getFixedSupplierPopulationSize() const
{
	if(fixedSupplierGA) return fixedSupplierGA->generation->population->individuals.size();
	else return 0;
}

double GAManager::getFixedSupplierPriceOffer(unsigned int individual) const
{
	if(fixedSupplierGA) return fixedSupplierGA->generation->population->individuals[individual]->chromosomeValue().price_offer;
	return 0.0;
}

double GAManager::getFixedSupplierSupplyCapacity(unsigned int individual) const
{
	if(fixedSupplierGA) return fixedSupplierGA->generation->population->individuals[individual]->chromosomeValue().supply_capacity;
	return 0.0;
}

double GAManager::getFixedSupplierSupplyCapacitySUM() const
{
	double capacity = 0.0;
	for(unsigned int i = 0; i < getFixedSupplierPopulationSize(); i++)
	{
		capacity += getFixedSupplierSupplyCapacity(i);
	}
	return capacity;
}

unsigned int GAManager::getFixedSupplierCustomerCount(unsigned int individual) const
{
	if(fixedSupplierGA) return fixedSupplierGA->generation->population->individuals[individual]->chromosomeValue().customer_count;
	return 0;
}

////////////////////////////////////////////////////
// SPOT SUPPLIER HELPERS
////////////////////////////////////////////////////
