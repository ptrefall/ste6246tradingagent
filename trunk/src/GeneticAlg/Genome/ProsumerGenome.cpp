
#include "ProsumerGenome.h"

ProsumerGenome::ProsumerGenome()
: GAGenome(Init, Mutate, Compare), compareFactor(800.0f), avg_per_hour_cost_factor(24.0f*365.0f*52.0f)
{
	evaluator(Evaluate);
	crossover(Cross);

	economic_capasity = addProperty<float>("Capacity", 0.0f);
	energy_production_capacity = addProperty<float>("Production", 0.0f);
	energy_consumption = addProperty<float>("Energy", 0.0f);
	user_flexibility = addProperty<float>("Flexibility", 0.0f);
	policy = addProperty<ProsumerPolicy>("Policy", GREEDY_PROSUMER);

	saldo_at_t = addPropertyList<Saldo>("Saldo");
	comfort_at_t = addPropertyList<Comfort>("Comfort");
	age_at_t = addPropertyList<Age>("Age");

	serializer = new Totem::PropertySerializer();
}

ProsumerGenome::ProsumerGenome(const ProsumerGenome &orig) 
: compareFactor(800.0f), avg_per_hour_cost_factor(24.0f*365.0f*52.0f)
{ 
	economic_capasity = addProperty<float>("Capacity", 0.0f);
	energy_production_capacity = addProperty<float>("Production", 0.0f);
	energy_consumption = addProperty<float>("Energy", 0.0f);
	user_flexibility = addProperty<float>("Flexibility", 0.0f);
	policy = addProperty<ProsumerPolicy>("Policy", GREEDY_PROSUMER);

	saldo_at_t = addPropertyList<Saldo>("Saldo");
	comfort_at_t = addPropertyList<Comfort>("Comfort");
	age_at_t = addPropertyList<Age>("Age");

	serializer = new Totem::PropertySerializer();

	copy(orig);
}

ProsumerGenome::~ProsumerGenome()
{
	if(serializer)
		delete serializer;
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

	ProsumerGenome *prosumer = dynamic_cast<ProsumerGenome *>(const_cast<GAGenome*>(&orig));
	if(prosumer)
	{
		//Copy genetic prosumer data here
		economic_capasity = prosumer->getProperty<float>("Capacity").get();
		energy_production_capacity = prosumer->getProperty<float>("Production").get();
		energy_consumption = prosumer->getProperty<float>("Energy").get();
		user_flexibility = prosumer->getProperty<float>("Flexibility").get();
		policy = prosumer->getProperty<ProsumerPolicy>("Policy").get();
	}
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
	stream << "- Economic Capacity: " << economic_capasity.toString(*serializer).c_str() << "\n";
	stream << "- Energy Production: " << energy_production_capacity.toString(*serializer).c_str() << "\n";
	stream << "- Energy Consumption: " << energy_consumption.toString(*serializer).c_str() << "\n";
	stream << "- User Flexibility: " << user_flexibility.toString(*serializer).c_str() << "\n";
	stream << "- Policy: " << (policy.get() == GREEDY_PROSUMER ?  "Greedy" : "Cautious") << "\n";
	//stream << "- SCORE: " << this->score() << "\n";
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
	
	prosumer.economic_capasity = GARandomFloat(0.05f, 0.35f);
	prosumer.energy_production_capacity = 0.0f;
	prosumer.energy_consumption = GARandomFloat(0.05f, 0.35f);
	prosumer.user_flexibility = 0.01f;
	prosumer.policy = GREEDY_PROSUMER;

	//prosumer._evaluated = gaFalse;
}

int ProsumerGenome::Mutate(GAGenome &genome, float pmut)
{
	ProsumerGenome &prosumer = static_cast<ProsumerGenome &>(genome);
	int nmut = 0;
	if(GAFlipCoin(pmut))
	{
		prosumer.economic_capasity = prosumer.economic_capasity.get() + GARandomFloat(-0.5, 0.5);
		if(prosumer.economic_capasity.get() < 0.0f)
		{
			//Death...
			prosumer.economic_capasity = 0.0f;
		}
		nmut++;
	}
	if(GAFlipCoin(pmut))
	{
		prosumer.energy_consumption = prosumer.energy_consumption.get() + GARandomFloat(-0.5, 0.5);
		nmut++;
	}
	return nmut;
}

float ProsumerGenome::Compare(const GAGenome &genomeA, const GAGenome &genomeB)
{
	const ProsumerGenome &sis = static_cast<const ProsumerGenome &>(genomeA);
	const ProsumerGenome &bro = static_cast<const ProsumerGenome &>(genomeB);

	float val = exp( - ((sis.economic_capasity.get()-bro.economic_capasity.get())*(sis.economic_capasity.get()-bro.economic_capasity.get())) / sis.compareFactor );
	if(1.0f - val < 0.0f) val = 0.0f;
	if(1.0f - val > 1.0f) val = 1.0f;

	return 1.0f - val;
}

float ProsumerGenome::Evaluate(GAGenome &genome)
{
	ProsumerGenome &prosumer = static_cast<ProsumerGenome&>(genome);
	float saldo = prosumer.economic_capasity.get();

	float energy_consumption_per_hour = prosumer.energy_consumption.get() / prosumer.avg_per_hour_cost_factor;
	float low_consumption = prosumer.user_flexibility * energy_consumption_per_hour; //prosumer.economic_capasity.get();
	float saldo_reduction_factor = (low_consumption / energy_consumption_per_hour)*(low_consumption / energy_consumption_per_hour);

	if(saldo_reduction_factor > 1.0f)
		saldo_reduction_factor = 1.0f;

	saldo = (1.0f - saldo_reduction_factor) * saldo;

	prosumer.saldo_at_t.push_back(Saldo(prosumer.saldo_at_t.size(), saldo));


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

		if(child.economic_capasity.get() < 0.0f)
		{
			//Death...
			child.economic_capasity = 0.0f;
		}

		midpoint = (mum.energy_consumption.get() + dad.energy_consumption.get()) / 2.0f;
		distance = fabs(mum.energy_consumption.get() - dad.energy_consumption.get());
		child.energy_consumption = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.energy_production_capacity.get() + dad.energy_production_capacity.get()) / 2.0f;
		distance = fabs(mum.energy_production_capacity.get() - dad.energy_production_capacity.get());
		child.energy_production_capacity = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.user_flexibility.get() + dad.user_flexibility.get()) / 2.0f;
		distance = fabs(mum.user_flexibility.get() - dad.user_flexibility.get());
		child.user_flexibility = midpoint + distance * (GARandomFloat() - GARandomFloat());
		
		//Flexibility can never go beyond 20%
		if(child.user_flexibility.get() > 0.2f)
		{
			child.user_flexibility = 0.2f;
		}

		child.policy = mum.policy.get();

		//child._evaluated = gaFalse;
		n++;
	}
	if(d)
	{
		ProsumerGenome &child = static_cast<ProsumerGenome &>(*d);
		float distance = 0.0f, midpoint = 0.0f;

		midpoint = (mum.economic_capasity.get() + dad.economic_capasity.get()) / 2.0f;
		distance = fabs(mum.economic_capasity.get() - dad.economic_capasity.get());
		child.economic_capasity = midpoint + distance * (GARandomFloat() - GARandomFloat());

		if(child.economic_capasity.get() < 0.0f)
		{
			//Death...
			child.economic_capasity = 0.0f;
		}

		midpoint = (mum.energy_consumption.get() + dad.energy_consumption.get()) / 2.0f;
		distance = fabs(mum.energy_consumption.get() - dad.energy_consumption.get());
		child.energy_consumption = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.energy_production_capacity.get() + dad.energy_production_capacity.get()) / 2.0f;
		distance = fabs(mum.energy_production_capacity.get() - dad.energy_production_capacity.get());
		child.energy_production_capacity = midpoint + distance * (GARandomFloat() - GARandomFloat());

		midpoint = (mum.user_flexibility.get() + dad.user_flexibility.get()) / 2.0f;
		distance = fabs(mum.user_flexibility.get() - dad.user_flexibility.get());
		child.user_flexibility = midpoint + distance * (GARandomFloat() - GARandomFloat());

		//Flexibility can never go beyond 20%
		if(child.user_flexibility.get() > 0.2f)
		{
			child.user_flexibility = 0.2f;
		}

		child.policy = dad.policy.get();

		//child._evaluated = gaFalse;
		n++;
	}
	return n;
}
