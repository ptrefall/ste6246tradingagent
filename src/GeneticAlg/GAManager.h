#pragma once

class ProsumerGeneticAlg;
class SupplierGeneticAlg;
class Prosumer;

#include <Entity\EntityManager.h>
#include <Totem\ComponentFactory.h>
#include <Irrlicht\irrlicht.h>
#include <vector>

class GAManager
{
public:
	GAManager(irr::scene::ISceneManager *smgr, EntityManager &entityMgr, Totem::ComponentFactory &componentFactory);
	~GAManager();

	void initialize();
	void trade();
	bool evolve();

	irr::scene::ISceneManager *getSceneMgr() { return smgr; }
	EntityManager &getEntityMgr() { return entityMgr; }
	Totem::ComponentFactory &getComponentFactory() { return componentFactory; }

//GA getters
public:
	ProsumerGeneticAlg *getProsumer() { return prosumerGA; }
	SupplierGeneticAlg *getSupplier() { return SupplierGA; }

//PIMPL Helper functions for Prosument GA
public:
	unsigned int getProsumerPopulationSize() const;
	double getProsumerEconomicCapacity(unsigned int individual) const;
	double getProsumerEnergyConsumption(unsigned int individual) const;

//PIMPL Helper functions for all Supplier GA
public:
	unsigned int getSuppliersPopulationSize() const;
	double getSuppliersSupplyCapacity() const;
	int findBestPriceOffer(double economic_capacity, double energy_consumption, double &price, unsigned int &index) const;
	double findWorstPriceOffer() const;

//PIMPL Helper functions for Fixed Supplier GA
public:
	unsigned int getSupplierPopulationSize() const;
	double getSupplierPriceOffer(unsigned int individual) const;
	double getSupplierUnreservedSupplyCapacity(unsigned int individual) const; //For each customer reserving energy with this individual supplyer, this capacity will decrease
	double getSupplierSupplyCapacity(unsigned int individual) const;
	double getSupplierSupplyCapacitySUM() const;
	unsigned int getSupplierCustomerCount(unsigned int individual) const;

//PIMPL Helper functions for Spot Supplier GA
public:

//Internal help functions for diverse purposes
private:
	void getCustomersInRandomOrder(std::vector<Prosumer*> &customers);

private:
	irr::scene::ISceneManager *smgr;
	EntityManager &entityMgr;
	Totem::ComponentFactory &componentFactory;
	ProsumerGeneticAlg *prosumerGA;
	SupplierGeneticAlg *SupplierGA;
};
