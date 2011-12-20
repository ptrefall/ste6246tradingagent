#pragma once

#include "IGenome.h"
#include <iostream>
#include <unordered_map>
#include <windows.h>

enum SupplierPriceStrategy
{
	SPS_FIXED_PRICE = 1,
	SPS_SPOT_PRICE,
	SPS_HYBRID_PRICE
};

class SpotPriceArray
{
public:
	std::vector<double> prices_per_generation;
};

class Supplier
{
public:
	double price_offer;
	double actual_price_offer;
	double supply_capacity; //[kWh/year]

	double saldo;
	unsigned int customer_count;
	unsigned int customer_count_ref;

	double participation_cost; //How much do a supplier have to pay in order to participate
	double participation_cost_accumulator;
	double participation_factor_accumulator;
	const double avg_per_hour_factor;

	double reserved_energy;

	unsigned int price_strategy;

	SpotPriceArray *spotPrice; //create this if we're a spot-price strategy supplier

	Supplier() 
		:	
			price_strategy(0),
			price_offer(0.0), 
			actual_price_offer(price_offer), 
			supply_capacity(0.0), 
			saldo(0.0), 
			customer_count(0), 
			customer_count_ref(0), 
			participation_cost(0.0), 
			avg_per_hour_factor(24.0*365.0), 
			reserved_energy(0.0), 
			participation_cost_accumulator(0.0),
			participation_factor_accumulator(0.0),
			spotPrice(0x0) {}

	Supplier(unsigned int ps, double po, double sc, double saldo, double pc) 
		:	price_strategy(ps),
			price_offer(po), 
			actual_price_offer(price_offer), 
			supply_capacity(sc), 
			saldo(saldo), 
			customer_count(0), 
			customer_count_ref(0),  
			participation_cost(pc), 
			avg_per_hour_factor(24.0*365.0), 
			reserved_energy(0.0), 
			participation_cost_accumulator(0.0),
			participation_factor_accumulator(0.0),
			spotPrice(0x0) {}

	static std::ostream &write(std::ostream& s, Supplier& d)
	{
		s << "- - Price Offer: " << d.price_offer << std::endl;
		s << "- - Supply Capacity: " << d.supply_capacity << std::endl;
		s << "- - Customer Count: " << d.customer_count << std::endl;
		if(d.price_strategy == SPS_FIXED_PRICE)
			s << "- - Strategy: FIXED PRICE" << std::endl;
		else if(d.price_strategy == SPS_SPOT_PRICE)
			s << "- - Strategy: SPOT PRICE" << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, Supplier& d)
	{
		return d.write(s,d);
	}

	const Supplier &operator= (const Supplier &rhs)
	{
		price_offer = rhs.price_offer;
		supply_capacity = rhs.supply_capacity;
		saldo = rhs.saldo;
		customer_count = rhs.customer_count;
		participation_cost = rhs.participation_cost;
		return *this;
	}
};

class GAManager;

class SupplierGenome : public IGenome<Supplier>
{
public:
	SupplierGenome(GAManager &mgr, unsigned int ps, double po, double sc, double saldo, double pc);
	virtual ~SupplierGenome();
public:
	double fitness(unsigned int generation) override;
	
	Supplier &chromosomeValue() override;
	void setChromosomeValue(Supplier &chromosome, bool is_mutation, unsigned int generation) override;
	
	bool wasMutatedInGeneration(const unsigned int &generation) const override;
	std::vector<unsigned int> getGenerationsOfMutation() const override;

	void reserveEnergySupply(double energy);

	void trade() { has_traded = true; }

public:
	static std::ostream &write(std::ostream& s, SupplierGenome& d)
	{
		if(!d.has_traded)
			return s;
		
		HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		s << "Fitness: " << d.chromosomeValue().saldo << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		
		s << "- Chromosome:" << std::endl;
		d.chromosome.write(s,d.chromosome);
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, SupplierGenome& d)
	{
		return d.write(s,d);
	}

private:
	void fixedPrice_strategy(unsigned int generation);
	void spotPrice_strategy(unsigned int generation);
	
private:
	GAManager &mgr;
	Supplier chromosome;
	std::unordered_map<unsigned int, std::pair<Supplier, Supplier>> mutations;
	bool first_time;
	bool has_traded;
};

template<class ChromosomeType>
bool SupplierGenomeSortPredicate(SupplierGenome *g1, SupplierGenome *g2)
{
	return g1->chromosomeValue().saldo > g2->chromosomeValue().saldo;
}
