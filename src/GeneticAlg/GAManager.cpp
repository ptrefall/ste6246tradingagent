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
							1.0,		//Øk
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
							0.08,		//Price Offer
							10.0,		//Supply capacity
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

void GAManager::trade()
{
	std::vector<Prosumer*> customers;
	getCustomersInRandomOrder(customers);
	
	for(unsigned int i = 0; i < customers.size(); i++)
	{
		const double avg_per_hour_factor = customers[i]->avg_per_hour_cost_factor;
		double economic_capacity = customers[i]->economic_capacity;
		double energy_consumption_this_hour = customers[i]->energy_consumption / avg_per_hour_factor; //We need it per hour/generation
		double price;
		unsigned int index_in_supplier;
		int supplier_type = findBestPriceOffer(economic_capacity, energy_consumption_this_hour, price, index_in_supplier);

		//Could we afford the best price offered to us?
		if(supplier_type == 0)
		{
			//Kill the poor lad
			customers[i]->saldo = 0.0;
		}
		//Best price from a fixed price supplier
		else if(supplier_type == 1)
		{
			customers[i]->genome->makePurchace(price);
			fixedSupplierGA->generation->population->individuals[index_in_supplier]->reserveEnergySupply(energy_consumption_this_hour);
		}
		//Best price from a spot price supplier
		else if(supplier_type == 2)
		{
		}
		//Best price from a hybrid price supplier
		else if(supplier_type == 3)
		{
		}
	}
}

void GAManager::getCustomersInRandomOrder(std::vector<Prosumer*> &customers)
{
	if(prosumerGA)
	{
		std::vector<Prosumer*> temp; 

		//Copy all individuals into a temp list
		for(unsigned int i = 0; i < prosumerGA->generation->population->individuals.size(); i++)
		{
			Prosumer *customer = &prosumerGA->generation->population->individuals[i]->chromosomeValue();
			temp.push_back(customer);
		}

		//Randomly pick an index from temp until it's empty
		while(!temp.empty())
		{
			int rand_index = std::rand() % temp.size();
			customers.push_back(temp[rand_index]);
			
			//then erase index from temp
			temp[rand_index] = temp.back();
			temp.pop_back();
		}
	}
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

double GAManager::getProsumerEconomicCapacity(unsigned int individual) const
{
	if(prosumerGA) return prosumerGA->generation->population->individuals[individual]->chromosomeValue().economic_capacity;
	else return 0.0;
}

double GAManager::getProsumerEnergyConsumption(unsigned int individual) const
{
	if(prosumerGA) return prosumerGA->generation->population->individuals[individual]->chromosomeValue().energy_consumption;
	else return 0.0;
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

int GAManager::findBestPriceOffer(double economic_capacity, double energy_consumption, double &price, unsigned int &index) const
{
	double best_price = 9999999999999999.0;
	int best_at_index = -1;
	int index_is_from = 0;

	//Check best price from all fixed price suppliers
	if(fixedSupplierGA)
	{
		for(unsigned int i = 0; i < getFixedSupplierPopulationSize(); i++)
		{
			//If supplier can meet the energy consumption requirement
			if(getFixedSupplierUnreservedSupplyCapacity(i) >= energy_consumption)
			{
				double price_offer = getFixedSupplierPriceOffer(i);
				if(best_price > price_offer)
				{
					best_price = price_offer;
					best_at_index = i;
					index_is_from = 1; //1 is fixed, 2 is spot and 3 is hybrid
				}
			}
		}
	}

	//Check best price from all spot price suppliers

	//Check best price from all hybrid price suppliers

	//Run this last
	if(best_at_index >= 0)
	{
		//If customer can't afford the best price offered, he's dead!
		if(best_price > economic_capacity)
			return 0;

		//is fixed price
		if(index_is_from == 1)
		{
			price = best_price;
			index = best_at_index;
			return 1;
		}
		//is spot price
		else if(index_is_from == 2)
		{
			price = best_price;
			index = best_at_index;
			return 2;
		}
		//is hybrid price
		else if(index_is_from == 3)
		{
			price = best_price;
			index = best_at_index;
			return 3;
		}
	}

	return 0;
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
	if(fixedSupplierGA) return fixedSupplierGA->generation->population->individuals[individual]->chromosomeValue().actual_price_offer;
	return 0.0;
}

double GAManager::getFixedSupplierUnreservedSupplyCapacity(unsigned int individual) const
{
	if(fixedSupplierGA) return getFixedSupplierSupplyCapacity(individual) - fixedSupplierGA->generation->population->individuals[individual]->chromosomeValue().reserved_energy;
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
