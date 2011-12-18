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

//PIMPL Helper functions for all Supplier GA
public:
	unsigned int getSuppliersPopulationSize() const;
	unsigned int getSuppliersSupplyCapacity() const;

//PIMPL Helper functions for Fixed Supplier GA
public:
	unsigned int getFixedSupplierPopulationSize() const;
	double getFixedSupplierPriceOffer(unsigned int individual) const;
	double getFixedSupplierSupplyCapacity(unsigned int individual) const;
	double getFixedSupplierSupplyCapacitySUM() const;
	unsigned int getFixedSupplierCustomerCount(unsigned int individual) const;

//PIMPL Helper functions for Spot Supplier GA
public:

private:
	ProsumerGeneticAlg *prosumerGA;
	FixedSupplierGeneticAlg *fixedSupplierGA;
};
