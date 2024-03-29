#pragma once

#include <vector>
#include <functional>
#include <algorithm>

template<class GenomeType>
class Population
{
public:
	unsigned int size;
	std::vector<GenomeType*> individuals;

	Population(unsigned int size) : size(size) {}
	~Population() 
	{
		/*for(unsigned int i = 0; i < individuals.size(); i++)
			delete individuals[i];*/
	}
};

template<class GenomeType>
class Generation
{
public:
	unsigned int id;
	double fitness_for_survival_threshold;
	Population<GenomeType> *population;
	GenomeType *bestGenome;
	unsigned int deaths;

	Generation(	unsigned int id,
				double fitness_for_survival_threshold, 
				unsigned int populationSize) 

		:	id(id), 
			fitness_for_survival_threshold(fitness_for_survival_threshold), 
			population(new Population<GenomeType>(populationSize)), 
			bestGenome(0x0), deaths(0) {}

	~Generation() { delete population; }
};

class GAManager;

template<class GenomeType>
class IGeneticAlg abstract
{

////////////////////////////////////////////
// CONSTRUCTION / DESTRUCTION
////////////////////////////////////////////
public:
	IGeneticAlg(GAManager &mgr, 
				unsigned int populationSize, 
				double fitness_for_survival_threshold, 
				double crossover_chance, 
				unsigned int max_children_from_cross, 
				double mutation_chance)

		: mgr(mgr), 
		  crossover_chance(crossover_chance), 
		  max_children_from_cross(max_children_from_cross), 
		  mutation_chance(mutation_chance)
	{
		generation = new Generation<GenomeType>(1, fitness_for_survival_threshold, populationSize);
		generations.push_back(generation);
	}

	virtual ~IGeneticAlg()
	{
		for(unsigned int i = 0; i < generations.size(); i++)
			delete generations[i];
	}

////////////////////////////////////////////
// PUBLIC DATA
////////////////////////////////////////////
public:
	Generation<GenomeType> *generation;
	std::vector<Generation<GenomeType>*> generations;
	double crossover_chance; 
	unsigned int max_children_from_cross;
	double mutation_chance;

////////////////////////////////////////////
// PROTECTED DATA
////////////////////////////////////////////
protected:
	GAManager &mgr;

////////////////////////////////////////////
// EVOLVE AND OTHER GENETIC BASE ALGORITHMS
////////////////////////////////////////////
public:
	double randomize() const
	{
		return (((double)(std::rand()%1000000))/1000000.0);
	}

	void initialize()
	{
		createInitialGenomes();
	}

	bool evolve()
	{
		//New parameters for next generation
		Generation<GenomeType> *newGeneration = 0x0;
		unsigned int newPopulationSize = 0;
		unsigned int mutationCount = 0;

		//Start extracting data from current generation
		std::vector<GenomeType*> survivors = findSurvivors();
		newPopulationSize += survivors.size();

		//All survivors are allowed to crossover, 
		//but only if there's more than one survivor..
		std::vector<GenomeType*> children_of_current_gen;
		if(survivors.size() > 1)
		{
			for(unsigned int i = 1; i < survivors.size(); i += 2)
			{
				unsigned int rand_child_count = std::rand() % (max_children_from_cross+1); //There's 8 possible combinations of RGB for 2 parents crossing
				if(rand_child_count > 0)
				{
					std::vector<GenomeType*> children = crossover(*survivors[i-1], *survivors[i], rand_child_count, crossover_chance); //% chance for any of the children in rand_child_count to result in a child
			
					//Add to list of children of current generation
					for(unsigned int j = 0; j < children.size(); j++)
						children_of_current_gen.push_back(children[j]);
				}
			}
		}
		newPopulationSize += children_of_current_gen.size();

		//Finally, we step over all newly born children and cause a percentage chance of mutation
		for(unsigned int i = 0; i < children_of_current_gen.size(); i++)
		{
			if(mutate(*children_of_current_gen[i], mutation_chance)) //% chance of a mutation for R, G and B values of each child.
				mutationCount++;
		}

		//And for the very last step, we pass the current generation into the history books
		//and let a new generation rise!
		newGeneration = new Generation<GenomeType>(generation->id+1, generation->fitness_for_survival_threshold, newPopulationSize);
		
		//Each survivor remain part of the new generation
		for(unsigned int i = 0; i < survivors.size(); i++)
		{
			newGeneration->population->individuals.push_back(survivors[i]);
		}

		//And all newborn children are part of this new generation as well!
		for(unsigned int i = 0; i < children_of_current_gen.size(); i++)
		{
			newGeneration->population->individuals.push_back(children_of_current_gen[i]);
		}

		generation = newGeneration;
		generations.push_back(newGeneration);

		//Calculate the fitness of the new population
		for(unsigned int i = 0; i < generation->population->individuals.size(); i++)
			generation->population->individuals[i]->fitness(generation->id);

		selectBestIndividual();

		//Did the population become extinct with this generation?
		if(generation->population->individuals.empty())
			return true;
		return false;
	}

////////////////////////////////////////////
// ABSTRACT MUTATION AND CROSSOVER
////////////////////////////////////////////
protected:
	virtual bool mutate(GenomeType &genome, double chance) const = 0;
	virtual std::vector<GenomeType*> crossover(GenomeType &mum, GenomeType &dad, unsigned int child_count, double chance) = 0;

////////////////////////////////////////////
// ABSTRACT HELPERS
////////////////////////////////////////////
protected:
	virtual GenomeType *createInitialRandomGenome(unsigned int index, unsigned int population_size) = 0;
	virtual std::vector<GenomeType*> findSurvivors() = 0;
	virtual void sortPopulation() = 0;
	virtual void selectBestIndividual() = 0;

////////////////////////////////////////////
// INTERNAL GENOME INITIALIZATION
////////////////////////////////////////////
private:
	void createInitialGenomes()
	{
		//Create an initial population
		for(unsigned int i = 0; i < generation->population->size; i++)
			generation->population->individuals.push_back(createInitialRandomGenome(i, generation->population->size));

		//Calculate the fitness of the initial population
		for(unsigned int i = 0; i < generation->population->individuals.size(); i++)
			generation->population->individuals[i]->fitness(generation->id);

		selectBestIndividual();
	}
};