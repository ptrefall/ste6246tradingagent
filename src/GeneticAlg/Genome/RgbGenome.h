#pragma once

#include "IGenome.h"
#include <iostream>
#include <unordered_map>

class Rgb
{
public:
	int r,g,b;
	Rgb() : r(0), g(0), b(0) {}
	Rgb(int r, int g, int b) : r(r), g(g), b(b) {}

	static std::ostream &write(std::ostream& s, Rgb& d)
	{
		s << "Color: " << d.r << "," << d.g << "," << d.b << std::endl;
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, Rgb& d)
	{
		return d.write(s,d);
	}

	const Rgb &operator= (const Rgb &rhs)
	{
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
		return *this;
	}
};

class RgbGenome : public IGenome<Rgb>
{
public:
	RgbGenome(int r, int g, int b);
	virtual ~RgbGenome();
public:
	double fitness(unsigned int generation) override;
	const Rgb &chromosomeValue() const override;
	void setChromosomeValue(Rgb &chromosome, bool is_mutation, unsigned int generation) override;
	bool wasMutatedInGeneration(const unsigned int &generation) const override;
	std::vector<unsigned int> getGenerationsOfMutation() const override;

	static std::ostream &write(std::ostream& s, RgbGenome& d)
	{
		s << "Fitness: " << d.fitness(0) << ", Chromosome: ";
		d.chromosome.write(s,d.chromosome);
		return s;
	}

	friend std::ostream& operator << (std::ostream& s, RgbGenome& d)
	{
		return d.write(s,d);
	}
	
private:
	Rgb target;
	Rgb chromosome;
	std::unordered_map<unsigned int, std::pair<Rgb, Rgb>> mutations;
};

template<class ChromosomeType>
bool RgbGenomeSortPredicate(RgbGenome *g1, RgbGenome *g2)
{
	return g1->fitness(0) > g2->fitness(0);
}
