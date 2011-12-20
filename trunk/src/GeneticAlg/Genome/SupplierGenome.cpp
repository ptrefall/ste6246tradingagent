#include "SupplierGenome.h"
#include "../GAManager.h"
#include "../ElPrice_loader.h"
#include <math.h>

SupplierGenome::SupplierGenome(GAManager &mgr, unsigned int ps, double po, double sc, double saldo, double pc)
	: mgr(mgr), chromosome(ps,po,sc,saldo,pc), first_time(true), has_traded(false)
{
	if(ps == SPS_SPOT_PRICE)
	{
		chromosome.spotPrice = new SpotPriceArray();
		ElSpotPriceLoader::loadPriceData("../../bin/resources/ElPrice/Elspot_prices.txt", chromosome.spotPrice->prices_per_generation);
	}
}

SupplierGenome::~SupplierGenome()
{
	if(chromosome.spotPrice)
		delete chromosome.spotPrice;
}

double SupplierGenome::fitness(unsigned int generation)
{
	if(chromosome.price_strategy == SPS_FIXED_PRICE)
		fixedPrice_strategy(generation);
	else if(chromosome.price_strategy == SPS_SPOT_PRICE)
		spotPrice_strategy(generation);

	chromosome.customer_count = chromosome.customer_count_ref;

	if(!first_time)
	{
		//Here we calculate the fitness of the supplier based on it's price offer and customer count
		if(chromosome.customer_count == 0)
			chromosome.saldo = 0.0;
		else
		{
			//How good is your price compared to the worst price? Worst price gives a factor of 1, thus we do 1.0-factor for saldo.
			double price_factor = chromosome.actual_price_offer / mgr.findWorstPriceOffer();

			//We add a small factor of how many customers you have compared to the customer population size to help further the strongest
			double customer_factor = (double)chromosome.customer_count / (double)mgr.getProsumerPopulationSize();

			//Cost of participation accumulates logarithmically over generations, thus long living suppliers will have to pay more to stay alive.
			//This adds a bit of chaos to the fitness value, such that fitness won't completely reflect the supplier's price offer and customer count.
			//Basically it means that the older a supplier is, the harder it is to stay alive, but the impact of the participation cost reduce over time,
			//due to the logarithmic nature of the participation cost factor accumulation. We chose to do this logarithmically over linearly, because a
			//linear participation cost killed price specialization... this might have been the result of a too high participation cost (adding to heavy
			//a linear impact on the fitness/saldo).
			chromosome.participation_cost_accumulator += chromosome.participation_cost;
			double participation_factor = (chromosome.participation_cost / chromosome.participation_cost_accumulator) * chromosome.participation_cost;
			chromosome.participation_factor_accumulator += participation_factor;
		
			//Calculate new fitness
			chromosome.saldo = (1.0 - price_factor) + customer_factor - chromosome.participation_factor_accumulator;
		}
	}
	else
	{
		first_time = false;
	}

	chromosome.customer_count_ref = 0;

	//Reset reserved energy for next round
	chromosome.reserved_energy = 0.0;

	return chromosome.saldo;
}

///////////////////////////////////////////////
// FIXED PRICE SUPPLIER STRATEGY
///////////////////////////////////////////////
void SupplierGenome::fixedPrice_strategy(unsigned int generation)
{
	// Bargain price
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
}

///////////////////////////////////////////////
// SPOT PRICE SUPPLIER STRATEGY
///////////////////////////////////////////////
void SupplierGenome::spotPrice_strategy(unsigned int generation)
{
	if(chromosome.spotPrice && chromosome.spotPrice->prices_per_generation.size() < generation)
		chromosome.actual_price_offer = chromosome.spotPrice->prices_per_generation[generation];
}

Supplier &SupplierGenome::chromosomeValue()
{
	return chromosome;
}

void SupplierGenome::setChromosomeValue(Supplier &chromosome, bool is_mutation, unsigned int generation)
{
	if(is_mutation)
	{
		std::pair<Supplier,Supplier> from_to(this->chromosome, chromosome);
		mutations[generation] = from_to;
	}
	this->chromosome = chromosome;
}

bool SupplierGenome::wasMutatedInGeneration(const unsigned int &generation) const
{
	auto it = mutations.find(generation);
	if(it != mutations.end())
		return true;
	else
		return false;
}

std::vector<unsigned int> SupplierGenome::getGenerationsOfMutation() const
{
	std::vector<unsigned int> generations;
	auto it = mutations.begin();
	for(; it != mutations.end(); ++it)
	{
		generations.push_back(it->first);
	}
	return generations;
}

void SupplierGenome::reserveEnergySupply(double energy)
{
	chromosome.reserved_energy += energy;
	chromosome.customer_count_ref++;
}
