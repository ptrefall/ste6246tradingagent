#pragma once

#include <vector>
#include <functional>

#include <Totem\types_config.h>

template<class GenomeType>
class Population
{
public:
	unsigned int size;
	std::vector<GenomeType*> individuals;

	Population(unsigned int size) : size(size) {}
	~Population() 
	{
		for(unsigned int i = 0; i < individuals.size(); i++)
			delete individuals[i];
	}
};

template<class GenomeType>
class Generation
{
public:
	unsigned int id;
	unsigned int survivorCount;
	Population<GenomeType> *population;
	GenomeType *bestGenome;

	Generation(unsigned int id, unsigned int survivorCount, unsigned int populationSize) : id(id), survivorCount(survivorCount), population(new Population<GenomeType>(populationSize)), bestGenome(0x0) {}
	~Generation() { delete population; }
};

template<class GenomeType>
class IGeneticAlg abstract
{
public:
	IGeneticAlg(unsigned int populationSize, unsigned int generationSurvivorCount)
	{
		if(generationSurvivorCount >= populationSize)
			throw T_Exception("The survival count of a generation must be smaller than the population size!");
		if(generationSurvivorCount < 2)
			throw T_Exception("Can't reproduce if there's only one she or one he... we'll die here");

		generation = new Generation<GenomeType>(1, generationSurvivorCount, populationSize);
		generations.push_back(generation);

		createInitialGenomes();
	}

	virtual ~IGeneticAlg()
	{
		for(unsigned int i = 0; i < generations.size(); i++)
			delete generations[i];
	}

public:
	
	Generation<GenomeType> *generation;
	std::vector<Generation<GenomeType>*> generations;

public:
	void evolve()
	{
		//New parameters for next generation
		Generation<GenomeType> *newGeneration = 0x0;
		unsigned int newPopulationSize = 0;
		unsigned int mutationCount = 0;

		//Start extracting data from current generation
		std::vector<RgbGenome*> survivors = findSurvivors();
		newPopulationSize += survivors.size();

		//All survivors are allowed to crossover
		std::vector<RgbGenome*> children_of_current_gen;
		for(unsigned int i = 1; i < survivors.size(); i++)
		{
			unsigned int rand_child_count = std::rand() % 8; //There's 8 possible combinations of RGB for 2 parents crossing
			std::vector<RgbGenome*> children = crossover(*survivors[i-1], *survivors[i], rand_child_count, 0.2); //20% chance for any of the children in rand_child_count to result in a child
			
			//Add to list of children of current generation
			for(unsigned int j = 0; j < children.size(); j++)
				children_of_current_gen.push_back(children[j]);
		}
		newPopulationSize += children_of_current_gen.size();

		//Finally, we step over all newly born children and cause a percentage chance of mutation
		for(unsigned int i = 0; i < children_of_current_gen.size(); i++)
		{
			if(mutate(*children_of_current_gen[i], 0.01)) //1% chance of a mutation for R, G and B values of each child.
				mutationCount++;
		}

		//And for the very last step, we pass the current generation into the history books
		//and let a new generation rise!
		newGeneration = new Generation<RgbGenome>(generation->id+1, generation->survivorCount, newPopulationSize);
		
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
	}

protected:
	virtual bool mutate(GenomeType &genome, double chance) const = 0;
	virtual std::vector<GenomeType*> crossover(GenomeType &mum, GenomeType &dad, unsigned int child_count, double chance) = 0;

protected:
	virtual GenomeType *createInitialRandomGenome() = 0;
	virtual std::vector<GenomeType*> findSurvivors() = 0;

private:
	void createInitialGenomes()
	{
		for(unsigned int i = 0; i < generation->population->size; i++)
			generation->population->individuals.push_back(createInitialRandomGenome());
	}
};
