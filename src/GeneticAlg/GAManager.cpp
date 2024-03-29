#include "GAManager.h"
#include "ProsumerGeneticAlg.h"
#include "SupplierGeneticAlg.h"

GAManager::GAManager(irr::scene::ISceneManager *smgr, EntityManager &entityMgr, Totem::ComponentFactory &componentFactory)
	: smgr(smgr), entityMgr(entityMgr), componentFactory(componentFactory), prosumerGA(0x0), SupplierGA(0x0)
{
	prosumerGA = new ProsumerGeneticAlg(*this,
							100,		//Population Size 
							0.0,		//Fitness threshold
							0.05,		//Chance for crossover
							1,			//Max children from crossover
							0.05,		//Chance for mutation
							0.1,		//Start saldo
							1.01,		//�k
							1.0,		//Ep
							24000.0,	//Ef
							0.1,		//Flex
							0);			//Policy

	SupplierGA = new SupplierGeneticAlg(*this,
							10,		//Population Size 
							0.0,		//Fitness threshold
							0.05,		//Chance for crossover
							1,			//Max children from crossover
							0.15,		//Chance for mutation
							0.1,		//Start saldo
							0.12,		//Price Offer
							8.0,		//Supply capacity
							0.04,		//Participation cost
							0.4,		//Hybrid Spot Percentage of Spot Price
							0.75);		//Hybrid Fixed Percentage of Fixed Price
}

GAManager::~GAManager()
{
	if(prosumerGA) delete prosumerGA;
	if(SupplierGA) delete SupplierGA;
}

void GAManager::initialize()
{
	if(prosumerGA) prosumerGA->initialize();
	if(SupplierGA) SupplierGA->initialize();
}

void GAManager::trade()
{
	//Register all suppliers for trade, this is to mark any new-born suppliers as having a valid fitness
	for(unsigned int i = 0; i < SupplierGA->generation->population->individuals.size(); i++)
		SupplierGA->generation->population->individuals[i]->trade();

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
			SupplierGA->generation->population->individuals[index_in_supplier]->reserveEnergySupply(energy_consumption_this_hour);
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
	//std::cout << *prosumerGA;
	if(finished)
		return finished;

	finished = SupplierGA->evolve();
	//std::cout << *SupplierGA;
	if(finished)
		return finished;

	//Genearation	ProsumerSaldo	EconomicCapacity	EnergyConsumption	ProsumerPopulationSize	ProsumerDeaths	SupplierSaldo	PriceOffer	CustomerCount	PriceStrategy	SupplierPopulationSize	SupplierDeaths

	std::cout << prosumerGA->generation->id << "\t";
	if(prosumerGA->generation->bestGenome)
	{
		std::cout << prosumerGA->generation->bestGenome->chromosomeValue().saldo << "\t";
		std::cout << prosumerGA->generation->bestGenome->chromosomeValue().economic_capacity << "\t";
		std::cout << prosumerGA->generation->bestGenome->chromosomeValue().energy_consumption << "\t";
		std::cout << prosumerGA->generation->population->individuals.size() << "\t";
		std::cout << prosumerGA->generation->deaths << "\t";
	}
	if(SupplierGA->generation->bestGenome)
	{
		std::cout << SupplierGA->generation->bestGenome->chromosomeValue().saldo << "\t";
		std::cout << SupplierGA->generation->bestGenome->chromosomeValue().actual_price_offer << "\t";
		std::cout << SupplierGA->generation->bestGenome->chromosomeValue().customer_count << "\t";
		std::cout << SupplierGA->generation->bestGenome->chromosomeValue().price_strategy << "\t";
		std::cout << SupplierGA->generation->population->individuals.size() << "\t";
		std::cout << SupplierGA->generation->deaths << "\t";
	}
	std::cout << std::endl;

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
	population_size += getSupplierPopulationSize();
	//population_size += getSpotSupplierPopulationSize();
	//population_size += getHybridSupplierPopulationSize();
	return population_size;
}

double GAManager::getSuppliersSupplyCapacity() const
{
	double supply_capacity = 0;
	supply_capacity += getSupplierSupplyCapacitySUM();
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
	if(SupplierGA)
	{
		for(unsigned int i = 0; i < getSupplierPopulationSize(); i++)
		{
			//If supplier can meet the energy consumption requirement
			if(getSupplierUnreservedSupplyCapacity(i) >= energy_consumption)
			{
				double price_offer = getSupplierPriceOffer(i);
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

double GAManager::findWorstPriceOffer() const
{
	double worst_price = 0.0;

	//Check best price from all fixed price suppliers
	if(SupplierGA)
	{
		for(unsigned int i = 0; i < getSupplierPopulationSize(); i++)
		{
			double price_offer = getSupplierPriceOffer(i);
			if(worst_price < price_offer)
				worst_price = price_offer;
		}
	}

	return worst_price;
}

////////////////////////////////////////////////////
// FIXED SUPPLIER HELPERS
////////////////////////////////////////////////////
unsigned int GAManager::getSupplierPopulationSize() const
{
	if(SupplierGA) return SupplierGA->generation->population->individuals.size();
	else return 0;
}

double GAManager::getSupplierPriceOffer(unsigned int individual) const
{
	if(SupplierGA) return SupplierGA->generation->population->individuals[individual]->chromosomeValue().actual_price_offer;
	return 0.0;
}

double GAManager::getSupplierUnreservedSupplyCapacity(unsigned int individual) const
{
	if(SupplierGA) return getSupplierSupplyCapacity(individual) - SupplierGA->generation->population->individuals[individual]->chromosomeValue().reserved_energy;
	return 0.0;
}

double GAManager::getSupplierSupplyCapacity(unsigned int individual) const
{
	if(SupplierGA) return SupplierGA->generation->population->individuals[individual]->chromosomeValue().supply_capacity;
	return 0.0;
}

double GAManager::getSupplierSupplyCapacitySUM() const
{
	double capacity = 0.0;
	for(unsigned int i = 0; i < getSupplierPopulationSize(); i++)
	{
		capacity += getSupplierSupplyCapacity(i);
	}
	return capacity;
}

unsigned int GAManager::getSupplierCustomerCount(unsigned int individual) const
{
	if(SupplierGA) return SupplierGA->generation->population->individuals[individual]->chromosomeValue().customer_count_ref;
	return 0;
}

////////////////////////////////////////////////////
// SPOT SUPPLIER HELPERS
////////////////////////////////////////////////////
