#pragma once

//#include "ProsumerGeneticAlg.h"
//#include "FixedSupplierGeneticAlg.h"

class ProsumerGeneticAlg;
//class FixedSupplierGeneticAlg;

class GAManager
{
public:
	GAManager();
	~GAManager();

	void initialize();
	bool update(unsigned int generation);

//GA getters
public:
	ProsumerGeneticAlg *getProsumer() { return prosumerGA; }
	//FixedSupplierGeneticAlg *getFixedSupplier() { return fixedSupplierGA; }

//PIMPL Helper functions for Prosument GA
public:
	unsigned int getPopulationSize() const;

//PIMPL Helper functions for Fixed Supplier GA
public:
	double getPriceOffer() const;
	unsigned int getCustomerCount() const;

private:
	ProsumerGeneticAlg *prosumerGA;
	//FixedSupplierGeneticAlg *fixedSupplierGA;
};
