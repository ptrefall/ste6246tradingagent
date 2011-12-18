#pragma once

#include "IGenome.h"
#include <iostream>
#include <unordered_map>
#include <windows.h>

class FixedSupplier
{
public:
	double price_offer;
	double supply_capacity; //[kWh/year]

	double saldo;
	unsigned int customer_count;

	double participation_cost; //How much do a supplier have to pay in order to participate
	const double avg_per_hour_factor;

	FixedSupplier() : price_offer(0.0), supply_capacity(0.0), saldo(0.0), customer_count(0), participation_cost(0.0), avg_per_hour_factor(24.0*365.0) {}
	FixedSupplier(double po, double sc, double saldo, unsigned int cc, double pc) 
		: price_offer(po), supply_capacity(sc), saldo(saldo), customer_count(cc), participation_cost(pc), avg_per_hour_factor(24.0*365.0) {}

	static std::ostream &write(std::ostream& s, FixedSupplier& d)
	{
		s << "- - Price Offer: " << d.price_offer << std::endl;
		s << "- - Supply Capacity: " << d.supply_capacity << std::endl;
		s << "- - Customer Count: " << d.customer_count << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, FixedSupplier& d)
	{
		return d.write(s,d);
	}

	const FixedSupplier &operator= (const FixedSupplier &rhs)
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

class FixedSupplierGenome : public IGenome<FixedSupplier>
{
public:
	FixedSupplierGenome(GAManager &mgr, double po, double sc, double saldo, unsigned int cc, double pc);
	virtual ~FixedSupplierGenome();
public:
	double fitness(unsigned int generation) override;
	const FixedSupplier &chromosomeValue() const override;
	void setChromosomeValue(FixedSupplier &chromosome, bool is_mutation, unsigned int generation) override;
	bool wasMutatedInGeneration(const unsigned int &generation) const override;
	std::vector<unsigned int> getGenerationsOfMutation() const override;

public:
	static std::ostream &write(std::ostream& s, FixedSupplierGenome& d)
	{
		HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		s << "Fitness: " << d.chromosomeValue().saldo << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		
		s << "- Chromosome:" << std::endl;
		d.chromosome.write(s,d.chromosome);
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, FixedSupplierGenome& d)
	{
		return d.write(s,d);
	}
	
private:
	GAManager &mgr;
	FixedSupplier chromosome;
	std::unordered_map<unsigned int, std::pair<FixedSupplier, FixedSupplier>> mutations;
};

template<class ChromosomeType>
bool FixedSupplierGenomeSortPredicate(FixedSupplierGenome *g1, FixedSupplierGenome *g2)
{
	return g1->chromosomeValue().saldo > g2->chromosomeValue().saldo;
}