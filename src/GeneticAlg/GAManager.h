#pragma once

class ProsumerGeneticAlg;
class FixedSupplierGeneticAlg;
class Prosumer;

#include <vector>

class GAManager
{
public:
	GAManager();
	~GAManager();

	void initialize();
	void trade();
	bool evolve();

//GA getters
public:
	ProsumerGeneticAlg *getProsumer() { return prosumerGA; }
	FixedSupplierGeneticAlg *getFixedSupplier() { return fixedSupplierGA; }

//PIMPL Helper functions for Prosument GA
public:
	unsigned int getProsumerPopulationSize() const;
	double getProsumerEconomicCapacity(unsigned int individual) const;
	double getProsumerEnergyConsumption(unsigned int individual) const;

//PIMPL Helper functions for all Supplier GA
public:
	unsigned int getSuppliersPopulationSize() const;
	unsigned int getSuppliersSupplyCapacity() const;
	int findBestPriceOffer(double economic_capacity, double energy_consumption, double &price, unsigned int &index) const;

//PIMPL Helper functions for Fixed Supplier GA
public:
	unsigned int getFixedSupplierPopulationSize() const;
	double getFixedSupplierPriceOffer(unsigned int individual) const;
	double getFixedSupplierUnreservedSupplyCapacity(unsigned int individual) const; //For each customer reserving energy with this individual supplyer, this capacity will decrease
	double getFixedSupplierSupplyCapacity(unsigned int individual) const;
	double getFixedSupplierSupplyCapacitySUM() const;
	unsigned int getFixedSupplierCustomerCount(unsigned int individual) const;

//PIMPL Helper functions for Spot Supplier GA
public:

//Internal help functions for diverse purposes
private:
	void getCustomersInRandomOrder(std::vector<Prosumer*> &customers);

private:
	ProsumerGeneticAlg *prosumerGA;
	FixedSupplierGeneticAlg *fixedSupplierGA;
};
