#include "GAManager.h"
#include "ProsumerGeneticAlg.h"
//#include "FixedSupplierGeneticAlg.h"

GAManager::GAManager()
	: prosumerGA(0x0)//, fixedSupplierGA(0x0)
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

	//fixedSupplierGA = new FixedSupplierGeneticAlg(this);
}

GAManager::~GAManager()
{
	if(prosumerGA) delete prosumerGA;
	//if(fixedSupplierGA) delete fixedSupplierGA;
}

void GAManager::initialize()
{
	if(prosumerGA) prosumerGA->initialize();
	//if(fixedSupplierGA) fixedSupplierGA->initialize();
}

bool GAManager::evolve()
{
	bool finished = false;
	finished = prosumerGA->evolve();
	std::cout << *prosumerGA;
	if(finished)
		return finished;

	/*finished = fixedSupplierGA->evolve();
	std::cout << *fixedSupplierGA;
	if(finished)
		return finished;*/

	return false;
}

////////////////////////////////////////////////////
// PROSUMER HELPERS
////////////////////////////////////////////////////
unsigned int GAManager::getPopulationSize() const
{
	if(prosumerGA) return prosumerGA->generation->population->individuals.size();
	else return 0;
}

////////////////////////////////////////////////////
// FIXED SUPPLIER HELPERS
////////////////////////////////////////////////////
double GAManager::getPriceOffer() const
{
	return 0.0;
}


unsigned int GAManager::getCustomerCount() const
{
	return 0;
}
