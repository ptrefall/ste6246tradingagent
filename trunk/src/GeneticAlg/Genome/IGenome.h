#pragma once

template<class ChromosomeType>
class IGenome abstract
{
public:
	virtual double fitness() const = 0;
	virtual const ChromosomeType &chromosomeValue() const = 0;
	virtual void setChromosomeValue(ChromosomeType &chromosome) = 0;
};
