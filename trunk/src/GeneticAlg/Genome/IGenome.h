#pragma once

#include <vector>

template<class ChromosomeType>
class IGenome abstract
{
public:
	virtual double fitness() = 0;
	virtual const ChromosomeType &chromosomeValue() const = 0;
	virtual void setChromosomeValue(ChromosomeType &chromosome, bool is_mutation, unsigned int generation) = 0;
	virtual bool wasMutatedInGeneration(const unsigned int &generation) const = 0;
	virtual std::vector<unsigned int> getGenerationsOfMutation() const = 0;
};
