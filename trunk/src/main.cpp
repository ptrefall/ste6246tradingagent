#include <Irrlicht\irrlicht.h>

#include <GA\GASimpleGA.h>
#include <GA\GA2DBinStrGenome.h>
#include <iostream>

#include <ClanLib\core.h>
#include <Totem\ComponentFactory.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

float Objective(GAGenome &);

int main(int argc, char **argv)
{
	CL_SetupCore clanlib_core_setup;
	Totem::ComponentFactory factory;
	for(int ii=1; ii<argc; ii++) 
	{
		if(strcmp(argv[ii++],"seed") == 0) {
			GARandomSeed((unsigned int)atoi(argv[ii]));
		}
	}
	int width    = 10;
	int height   = 5;
	int popsize  = 30;
	int ngen     = 400;
	float pmut   = 0.001;
	float pcross = 0.9;
	GA2DBinaryStringGenome genome(width, height, Objective);

	GASimpleGA ga(genome);
	ga.populationSize(popsize);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);


	IrrlichtDevice *device = createDevice( video::EDT_DIRECT3D9, dimension2d<u32>(640,480), 16, false, false, false, 0);
	if(!device)
		return -1;

	device->setWindowCaption(L"TradinAgent");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	double accum_time = 0.0;
	while(device->run())
	{
		double fps_ms = 1.0 / (double)driver->getFPS();
		if(fps_ms < 0.1)
			accum_time += fps_ms;
		if(accum_time > 10.0)
		{
			accum_time = 0.0;
			ga.evolve();
			std::cout << "The GA found:\n" << ga.statistics().bestIndividual() << "\n";
		}

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		driver->endScene();
	}
	device->drop();
	return 0;
}

float Objective(GAGenome &g) 
{
	GA2DBinaryStringGenome & genome = (GA2DBinaryStringGenome &)g;
	
	float score = 0.0;
	int count = 0;
	
	for(int i = 0; i<genome.width(); i++)
	{
		for(int j = 0; j<genome.height(); j++)
		{
			if(genome.gene(i,j) == 0 && count%2 == 0)
				score += 1.0;
			if(genome.gene(i,j) == 1 && count%2 != 0)
				score += 1.0;
			count++;
		}
	}
	return score;
}
