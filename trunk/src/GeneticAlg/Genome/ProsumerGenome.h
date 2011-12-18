#pragma once

#include "IGenome.h"
#include <iostream>
#include <unordered_map>
#include <windows.h>

class Prosumer
{
public:
	double economic_capacity;
	double energy_production_capacity;
	double energy_consumption;
	double flexi_rate;
	unsigned int policy;

	double saldo;

	const double compareFactor;
	const double avg_per_hour_cost_factor;

	Prosumer() : economic_capacity(1.0), energy_production_capacity(0.0), energy_consumption(0.1), flexi_rate(0.01), policy(0), saldo(1.0), compareFactor(800.0), avg_per_hour_cost_factor(24.0*365.0) {}
	Prosumer(double ec, double ep, double ef, double flex, unsigned int policy, double saldo) 
		: economic_capacity(ec), energy_production_capacity(ep), energy_consumption(ef), flexi_rate(flex), policy(policy), saldo(saldo), compareFactor(800.0), avg_per_hour_cost_factor(24.0*365.0) {}

	static std::ostream &write(std::ostream& s, Prosumer& d)
	{
		s << "- - Economic Capacity: " << d.economic_capacity << std::endl;
		s << "- - Energy Production Capacity: " << d.energy_production_capacity << std::endl;
		s << "- - Energy Consumption: " << d.energy_consumption << std::endl;
		s << "- - Flexi Rate: " << d.flexi_rate << std::endl;
		s << "- - Policy: " << d.policy << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, Prosumer& d)
	{
		return d.write(s,d);
	}

	const Prosumer &operator= (const Prosumer &rhs)
	{
		economic_capacity = rhs.economic_capacity;
		energy_production_capacity = rhs.energy_production_capacity;
		energy_consumption = rhs.energy_consumption;
		flexi_rate = rhs.flexi_rate;
		policy = rhs.policy;
		saldo = rhs.saldo;
		return *this;
	}
};

class GAManager;

class ProsumerGenome : public IGenome<Prosumer>
{
public:
	ProsumerGenome(GAManager &mgr, double ec, double ep, double ef, double flex, unsigned int policy, double saldo);
	virtual ~ProsumerGenome();
public:
	double fitness(unsigned int generation) override;
	const Prosumer &chromosomeValue() const override;
	void setChromosomeValue(Prosumer &chromosome, bool is_mutation, unsigned int generation) override;
	bool wasMutatedInGeneration(const unsigned int &generation) const override;
	std::vector<unsigned int> getGenerationsOfMutation() const override;

//Object functions
public:
	double buyAllEnergy_Strategy(unsigned int generation, double energy_consumption_per_hour);

public:
	static std::ostream &write(std::ostream& s, ProsumerGenome& d)
	{
		HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		s << "Fitness: " << d.chromosomeValue().saldo << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		//s << "- Chromosome:" << std::endl;
		//d.chromosome.write(s,d.chromosome);
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, ProsumerGenome& d)
	{
		return d.write(s,d);
	}
	
private:
	GAManager &mgr;
	Prosumer chromosome;
	std::unordered_map<unsigned int, std::pair<Prosumer, Prosumer>> mutations;
};

template<class ChromosomeType>
bool ProsumerGenomeSortPredicate(ProsumerGenome *g1, ProsumerGenome *g2)
{
	return g1->chromosomeValue().saldo > g2->chromosomeValue().saldo;
}
