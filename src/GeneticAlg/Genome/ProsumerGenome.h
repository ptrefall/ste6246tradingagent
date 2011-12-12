#pragma once

#include <GA\ga.h>
#include <Totem\PropertyHandler.h>
#include <Totem\PropertyListHandler.h>

#define ENERGY_PROD_INVESTMENT_PER_KWH 14000

//The saldo of the prosumer at any given time t.
struct Saldo
{
	unsigned long time;
	float saldo;
	Saldo(unsigned long time, float saldo) : time(time), saldo(saldo) {}
};

//How comfortable the prosumer is at any given time t.
//comfort ranges from 0.0 to 1.0, where 0.0 is no comfort.
struct Comfort
{
	unsigned long time;
	float comfort;
	Comfort(unsigned long time, float comfort) : time(time), comfort(comfort) {}
};

//The age of a prosumer at any given time t.
struct Age
{
	unsigned long time;
	unsigned int age;
	Age(unsigned long time, unsigned int age) : time(time), age(age) {}
};

enum ProsumerPolicy
{
	GREEDY_PROSUMER = 0,
	CAUTIOUS_PROSUMER = 1,
	PROSUMER_POLICY_COUNT
};

class ProsumerGenome : public GAGenome, public Totem::PropertyHandler<>, public Totem::PropertyListHandler<>
{
public:
	GADefineIdentity("ProsumerGenome", 201);
	static void Init(GAGenome&);
	static int Mutate(GAGenome&, float);
	static float Compare(const GAGenome&, const GAGenome&);
	static float Evaluate(GAGenome&);
	static int Cross(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);

public:
	ProsumerGenome();
	ProsumerGenome(const ProsumerGenome &orig) { copy(orig); }
	virtual ~ProsumerGenome();

	ProsumerGenome &operator= (const GAGenome &orig)
	{
		if(&orig != this)
			copy(orig);
		return *this;
	}

	virtual GAGenome *clone(CloneMethod) const;
	virtual void copy(const GAGenome &orig);
	virtual int equal(const GAGenome &rhs) const;

	virtual int read(std::istream &stream);
	virtual int write(std::ostream &stream) const;

public:
	//Takes as input how much energy the individual
	//wishes to invest in, and returns 1 if successful,
	//0 if not (if individual has the cash for it).
	int investInEnergyProduction(int kWh);

//Genetic material
protected:
	Totem::Property<float> economic_capasity;
	Totem::Property<float> energy_production_capacity;
	Totem::Property<float> energy_consumption;
	Totem::Property<float> user_flexibility;
	Totem::Property<ProsumerPolicy> policy;

//State attributes
protected:
	Totem::PropertyList<Saldo> saldo_at_t;
	Totem::PropertyList<Comfort> comfort_at_t;
	Totem::PropertyList<Age> age_at_t;
};
