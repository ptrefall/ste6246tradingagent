#pragma once

class ProsumerGeneticAlg;
class FixedSupplierGeneticAlg;

class GAManager
{
public:
	GAManager();
	~GAManager();

	void initialize();
	bool evolve();

//GA getters
public:
	ProsumerGeneticAlg *getProsumer() { return prosumerGA; }
	FixedSupplierGeneticAlg *getFixedSupplier() { return fixedSupplierGA; }

//PIMPL Helper functions for Prosument GA
public:
	unsigned int getProsumerPopulationSize() const;

//PIMPL Helper functions for Fixed Supplier GA
public:
	unsigned int getFixedSupplierPopulationSize() const;
	double getPriceOffer(unsigned int individual) const;
	double getSupplyCapacity(unsigned int individual) const;
	unsigned int getCustomerCount(unsigned int individual) const;

//PIMPL Helper functions for Spot Supplier GA
public:

private:
	ProsumerGeneticAlg *prosumerGA;
	FixedSupplierGeneticAlg *fixedSupplierGA;
};
