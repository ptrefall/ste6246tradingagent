#include "ProsumerGenome.h"
#include <math.h>
#include <exception>
#include <GeneticAlg\GAManager.h>

#include <Totem\types_config.h>
#include <Totem\ComponentFactory.h>
#include <Entity\EntityManager.h>
#include <Entity\Entity.h>

#include <Irrlicht\irrlicht.h>

ProsumerGenome::ProsumerGenome(GAManager &mgr, double ec, double ep, double ef, double flex, unsigned int policy, double saldo)
	: mgr(mgr), chromosome(this, ec,ep,ef,flex,policy,saldo), entity(0x0)
{
	try{
		entity = &mgr.getEntityMgr().create(mgr.getComponentFactory());
		entity->addComponent<EntityManager, irr::scene::ISceneManager>("Health", mgr.getEntityMgr(), *mgr.getSceneMgr());
		/*if(a == '1')
		{
			entity.addComponent<irr::scene::ISceneNode, irr::scene::ISceneManager, std::string>("Sprite", 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Particle/Particle.tga"), irr::core::vector2di(64,64));
		}
		else
		{*/
			entity->addComponent<irr::scene::ISceneNode, irr::scene::ISceneManager, std::string>("Sprite", 
				*mgr.getSceneMgr()->getRootSceneNode(), *mgr.getSceneMgr(), std::string("../../bin/resources/Sprites/goblin_001.png"), irr::core::vector2di(72,97));
		//}
		entity->sendEvent0(T_HashedString("LOAD"));
		float x = (float)((std::rand() % 400) - 200);
		float z = (float)((std::rand() % 400) - 200);
		entity->getProperty<irr::core::vector3df>("Position") = irr::core::vector3df(x,0,z);
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}
}

ProsumerGenome::~ProsumerGenome()
{
}

double ProsumerGenome::fitness(unsigned int generation)
{
	double energy_consumption_per_hour = chromosome.energy_consumption / chromosome.avg_per_hour_cost_factor;
	double low_consumption = chromosome.flexi_rate * energy_consumption_per_hour;
	
	double ef_lifetime_reduction_factor = (low_consumption / energy_consumption_per_hour)*(low_consumption / energy_consumption_per_hour);
	if(ef_lifetime_reduction_factor > 1.0f)
		ef_lifetime_reduction_factor = 1.0f;

	double bills_lifetime_reduction_factor = 1.0;
	if(chromosome.policy == 0)
		bills_lifetime_reduction_factor = buyAllEnergy_Strategy(generation, energy_consumption_per_hour);

	chromosome.saldo = (1.0 - (ef_lifetime_reduction_factor+bills_lifetime_reduction_factor)) * chromosome.saldo;

	if(entity)
		entity->getProperty<float>("Health") = (float)chromosome.saldo * 1000.0f;

	return chromosome.saldo;
}

void ProsumerGenome::makePurchace(double price)
{
	//Reserve the price we got offered
	//and use next time the fitness function is called!
	chromosome.reserved_price = price; 
}

double ProsumerGenome::buyAllEnergy_Strategy(unsigned int generation, double energy_consumption_per_hour)
{
	double bill = energy_consumption_per_hour * chromosome.reserved_price;
	chromosome.reserved_price = 0.0; //reset the reserved price. We want a new offer for next generation!
	
	//If we can't pay our bills, we die
	if(chromosome.economic_capacity <= bill)
		return 1.0;

	double factor = bill / chromosome.economic_capacity;
	chromosome.economic_capacity = chromosome.economic_capacity - bill;
	return factor;
}

Prosumer &ProsumerGenome::chromosomeValue()
{
	return chromosome;
}

void ProsumerGenome::setChromosomeValue(Prosumer &chromosome, bool is_mutation, unsigned int generation)
{
	if(is_mutation)
	{
		std::pair<Prosumer,Prosumer> from_to(this->chromosome, chromosome);
		mutations[generation] = from_to;
	}
	this->chromosome = chromosome;
}

bool ProsumerGenome::wasMutatedInGeneration(const unsigned int &generation) const
{
	auto it = mutations.find(generation);
	if(it != mutations.end())
		return true;
	else
		return false;
}

std::vector<unsigned int> ProsumerGenome::getGenerationsOfMutation() const
{
	std::vector<unsigned int> generations;
	auto it = mutations.begin();
	for(; it != mutations.end(); ++it)
	{
		generations.push_back(it->first);
	}
	return generations;
}
