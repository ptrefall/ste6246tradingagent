#pragma once

#include "IGenome.h"
#include <iostream>

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
};

class RgbGenome : public IGenome<Rgb>
{
public:
	RgbGenome(int r, int g, int b);
	virtual ~RgbGenome();
public:
	double fitness() const override;
	const Rgb &chromosomeValue() const override;
	void setChromosomeValue(Rgb &chromosome) override;

	static std::ostream &write(std::ostream& s, RgbGenome& d)
	{
		s << "Fitness: " << d.fitness() << ", Chromosome: ";
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
};

template<class ChromosomeType>
bool RgbGenomeSortPredicate(RgbGenome *g1, RgbGenome *g2)
{
	return g1->fitness() > g2->fitness();
}
