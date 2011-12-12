
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
	ProsumerGenome &prosumer = static_cast<ProsumerGenome &>(genome);
	
	prosumer.economic_capasity = prosumer.addProperty<float>("Capacity", GARandomFloat(0.5f, 3.5f));
	prosumer.energy_production_capacity = prosumer.addProperty<float>("Production", 0.0f);
	prosumer.energy_consumption = prosumer.addProperty<float>("Energy", GARandomFloat(0.5f, 3.5f));
	prosumer.user_flexibility = prosumer.addProperty<float>("Flexibility", 0.0f);
	prosumer.policy = prosumer.addProperty<ProsumerPolicy>("Policy", GREEDY_PROSUMER);

	prosumer.saldo_at_t = prosumer.addPropertyList<Saldo>("Saldo");
	prosumer.comfort_at_t = prosumer.addPropertyList<Comfort>("Comfort");
	prosumer.age_at_t = prosumer.addPropertyList<Age>("Age");

	prosumer._evaluated = gaFalse;
}

int ProsumerGenome::Mutate(GAGenome &genome, float pmut)
{
	ProsumerGenome &prosumer = static_cast<ProsumerGenome &>(genome);
	int nmut = 0;
	if(GAFlipCoin(pmut))
	{
		prosumer.economic_capasity = prosumer.economic_capasity.get() + GARandomFloat(-0.5, 0.5);
		nmut++;
	}
	if(GAFlipCoin(pmut))
	{
		prosumer.energy_consumption = prosumer.energy_consumption.get() + GARandomFloat(-0.5, 0.5);
		nmut++;
	}
	return nmut;
}

static const float cFactor = 800.0f;

float ProsumerGenome::Compare(const GAGenome &genomeA, const GAGenome &genomeB)
{
	const ProsumerGenome &sis = static_cast<const ProsumerGenome &>(genomeA);
	const ProsumerGenome &bro = static_cast<const ProsumerGenome &>(genomeB);

	float val = exp( - ((sis.economic_capasity.get()-bro.economic_capasity.get())*(sis.economic_capasity.get()-bro.economic_capasity.get())) / cFactor );
	if(1.0f - val < 0.0f) val = 0.0f;
	if(1.0f - val > 1.0f) val = 1.0f;

	return 1.0f - val;
}

float ProsumerGenome::Evaluate(GAGenome &genome)
{
	ProsumerGenome &prosumer = static_cast<ProsumerGenome&>(genome);
	float saldo = 0.0f;
	return saldo;
}

int ProsumerGenome::Cross(const GAGenome &a, const GAGenome &b, GAGenome *c, GAGenome *d)
{
	const ProsumerGenome &mum = static_cast<const ProsumerGenome &>(a);
	const ProsumerGenome &dad = static_cast<const ProsumerGenome &>(b);
	int n = 0;
	if(c)
	{
		ProsumerGenome &child = static_cast<ProsumerGenome &>(*c);
		float distance = 0.0f, midpoint = 0.0f;

		midpoint = (mum.economic_capasity.get() + dad.economic_capasity.get()) / 2.0f;
		distance = fabs(mum.economic_capasity.get() - dad.economic_capasity.get());
		child.economic_capasity = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.energy_consumption.get() + dad.energy_consumption.get()) / 2.0f;
		distance = fabs(mum.energy_consumption.get() - dad.energy_consumption.get());
		child.energy_consumption = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.energy_production_capacity.get() + dad.energy_production_capacity.get()) / 2.0f;
		distance = fabs(mum.energy_production_capacity.get() - dad.energy_production_capacity.get());
		child.energy_production_capacity = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.user_flexibility.get() + dad.user_flexibility.get()) / 2.0f;
		distance = fabs(mum.user_flexibility.get() - dad.user_flexibility.get());
		child.user_flexibility = midpoint + distance * (GARandomFloat() - GARandomFloat());

		child.policy = mum.policy.get();

		child._evaluated = gaFalse;
		n++;
	}
	if(d)
	{
		ProsumerGenome &child = static_cast<ProsumerGenome &>(*d);
		float distance = 0.0f, midpoint = 0.0f;

		midpoint = (mum.economic_capasity.get() + dad.economic_capasity.get()) / 2.0f;
		distance = fabs(mum.economic_capasity.get() - dad.economic_capasity.get());
		child.economic_capasity = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.energy_consumption.get() + dad.energy_consumption.get()) / 2.0f;
		distance = fabs(mum.energy_consumption.get() - dad.energy_consumption.get());
		child.energy_consumption = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.energy_production_capacity.get() + dad.energy_production_capacity.get()) / 2.0f;
		distance = fabs(mum.energy_production_capacity.get() - dad.energy_production_capacity.get());
		child.energy_production_capacity = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.user_flexibility.get() + dad.user_flexibility.get()) / 2.0f;
		distance = fabs(mum.user_flexibility.get() - dad.user_flexibility.get());
		child.user_flexibility = midpoint + distance * (GARandomFloat() - GARandomFloat());

		child.policy = dad.policy.get();

		child._evaluated = gaFalse;
		n++;
	}
	return n;
}
