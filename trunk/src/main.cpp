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


	IrrlichtDevice *device = createDevice( video::EDT_DIRECT3D9, dimension2d<u32>(1680,1200), 16, false, false, false, 0);
	if(!device)
		return -1;

	device->setWindowCaption(L"TradingAgent");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                rect<s32>(10,10,260,22), true);

	ISceneNode *tower = smgr->addSceneNode("Tower");
	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_base1.3ds");
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Base_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(10.0f, 0.0f, 0.0f));
		}
	}
	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_head5.3ds");
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Head_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(10.0f, 6.5f, 0.0f));
		}
	}
	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_gun6.3ds");
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Weapon_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(10.0f, 8.0f, 0.0f));
		}
	}

	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Beast/beast.ms3d");
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			//node->setMD2Animation(scene::EMAT_STAND);
			node->setAnimationSpeed(30.0f);
			node->setFrameLoop(1, 400);
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Beast/beast1.jpg") );
			//node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(-10.0f, 0.0f, 0.0f));
			node->setScale(vector3df(0.1f, 0.1f, 0.1f));
		}
	}

	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	double accum_time = 0.0;
	while(device->run())
	{
		double fps_ms = 1.0 / (double)driver->getFPS();
		device->setWindowCaption((const wchar_t*)(CL_String("TradingAgent") + CL_StringHelp::int_to_text(driver->getFPS())).c_str());

		if(fps_ms < 0.1)
			accum_time += fps_ms;
		if(accum_time > 10.0)
		{
			accum_time = 0.0;
			ga.evolve();
			std::cout << "The GA found:\n" << ga.statistics().bestIndividual() << "\n";
		}

		//tower->setRotation(vector3df(0.0f, 1.0f, 0.0f));

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
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
