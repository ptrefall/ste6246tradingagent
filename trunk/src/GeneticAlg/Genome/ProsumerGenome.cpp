
#include "ProsumerGenome.h"

ProsumerGenome::ProsumerGenome()
: GAGenome(Init, Mutate, Compare)
{
	evaluator(Evaluate);
	crossover(Cross);
}

ProsumerGenome::~ProsumerGenome()
{
}

/////////////////////////////////////////////////
//MEMBER FUNCTIONALITY
/////////////////////////////////////////////////
GAGenome *ProsumerGenome::clone(CloneMethod) const 
{ 
	return new ProsumerGenome(*this); 
}

void ProsumerGenome::copy(const GAGenome &orig)
{
	GAGenome::copy(orig); //this copies all of the base genome parts
	//Copy genetic prosumer data here
}

int ProsumerGenome::equal(const GAGenome &rhs) const
{
	return 0;
}

int ProsumerGenome::read(std::istream &stream)
{
	return 0;
}
int ProsumerGenome::write(std::ostream &stream) const
{
	return 0;
}

/////////////////////////////////////////////////
//PROSUMER MEMBER FUNCTIONALITY
/////////////////////////////////////////////////
int ProsumerGenome::investInEnergyProduction(int kWh)
{
	int economic_investment = kWh * ENERGY_PROD_INVESTMENT_PER_KWH;
	if(economic_investment > economic_capasity.get())
		return 0;

	return 0;
}

/////////////////////////////////////////////////
//STATIC FUNCTIONALITY
/////////////////////////////////////////////////
void ProsumerGenome::Init(GAGenome &genome)
{
}

int ProsumerGenome::Mutate(GAGenome &genome, float pmut)
{
	return 0;
}

float ProsumerGenome::Compare(const GAGenome &genomeA, const GAGenome &genomeB)
{
	return 0.0f;
}

float ProsumerGenome::Evaluate(GAGenome &genome)
{
	ProsumerGenome &prosumer = static_cast<ProsumerGenome&>(genome);
	return 0.0f;
}

int ProsumerGenome::Cross(const GAGenome &mum, const GAGenome &dad, GAGenome *sis, GAGenome *bro)
{
	return 0;
}
