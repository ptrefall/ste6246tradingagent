#include <ft2build.h>
#include FT_FREETYPE_H

#include <Irrlicht\irrlicht.h>

#include <GA\GASStateGA.h>
#include <GA\GA3DBinStrGenome.h>
#include <iostream>

#include <ClanLib\core.h>

#include <SceneNode\HealthSceneNode.h>
#include <SceneNode\CGridSceneNode.h>
#include <SceneNode\Weather\irrWeatherManager.h>
#include <SceneNode\TAnimSprite.h>
#include <SceneNode\GraphSceneNode.h>

#include <GUI/CIrrRocketGUI.h>

#include <Entity\EntityManager.h>
#include <Entity\Entity.h>
#include <Entity\Components\Health.h>
#include <Entity\Components\Sprite.h>
#include <Totem\ComponentFactory.h>

#include <GeneticAlg\Genome\ProsumerGenome.h>

#include <GeneticAlg\RgbGeneticAlg.h>

#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//float Objective(GAGenome &);

int main(int argc, char **argv)
{
	CL_SetupCore clanlib_core_setup;

	/*for(int ii=1; ii<argc; ii++) 
	{
		if(strcmp(argv[ii++],"seed") == 0) {
			GARandomSeed((unsigned int)atoi(argv[ii]));
		}
	}
	int width    = 10;
	int height   = 10;
	int depth   = 3;
	int popsize  = 30;
	int ngen     = 100;
	float preplace = 1.0;
	float pmut   = 0.001;
	float pcross = 0.9;
	GA3DBinaryStringGenome genome(width, height, depth, Objective);

	GASteadyStateGA ga(genome);
	ga.minimize();
	ga.populationSize(popsize);
	ga.pReplacement(preplace);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);
	ga.scoreFilename("../../bin/bog.dat");	// name of file for scores
	ga.scoreFrequency(10);	// keep the scores of every 10th generation
	ga.flushFrequency(50);	// specify how often to write the score to disk
	ga.selectScores(GAStatistics::AllScores);
	GAGenome &individual = ga.population().individual(0);*/

	//{
	/*ProsumerGenome genome; //default constructor
	std::cout << "genome after creation:\n" << genome << std::endl;

	int popsize  = 300;
	int ngen     = 30;
	float preplace = 0.1;
	float pmut   = 0.02;
	float pcross = 0.35;

	GASteadyStateGA ga(genome);
	ga.minimize();
	ga.populationSize(popsize);
	ga.pReplacement(preplace);
	ga.nGenerations(ngen);
	ga.pMutation(pmut);
	ga.pCrossover(pcross);
	ga.scoreFilename("../../bin/bog.dat");	// name of file for scores
	ga.scoreFrequency(1);	// keep the scores of every 10th generation
	ga.flushFrequency(50);	// specify how often to write the score to disk
	ga.selectScores(GAStatistics::Maximum|GAStatistics::Minimum);
	GANoScaling scalor;
	ga.scaling(scalor);
	GARankSelector selector;
	ga.selector(selector);*/


	/*genome.initialize();  // test the initializer
	std::cout << "genome after initialization:\n" << genome << std::endl;

	genome.mutate(0.99f);      // test the mutator
	std::cout << "genome after mutation:\n" << genome << std::endl;

	ProsumerGenome* a = new ProsumerGenome(genome);   // test copy constructor
	ProsumerGenome* b = new ProsumerGenome(genome);

	ProsumerGenome* c = static_cast<ProsumerGenome*>(genome.clone(GAGenome::CONTENTS));
	std::cout << "clone contents:\n" << *c << "\n";
	ProsumerGenome* d = static_cast<ProsumerGenome*>(genome.clone(GAGenome::ATTRIBUTES));
	std::cout << "clone attributes:\n" << *d << "\n";

	a->initialize();
	b->initialize();
	std::cout << "parents:\n" << *a << "\n" << *b << "\n";

	ProsumerGenome::Cross(*a, *b, c, d);   // test two child crossover
	std::cout << "children of crossover:\n" << *c << "\n" << *d << "\n";
	ProsumerGenome::Cross(*a, *b, c, 0);   // test single child crossover
	std::cout << "child of crossover:\n" << *c << "\n";

	a->compare(*b);       // test the comparator

	delete a;
	delete b;
	delete c;
	delete d;
	}*/

	RgbGeneticAlg ga(20, 5);
	ga.initialize();
	for(unsigned int i = 0; i < 100; i++)
	{
		std::cout << ga;
		bool perfect_genome_found = ga.evolve();
		if(perfect_genome_found)
			break;
	}
	std::cout << ga << std::endl;

	char a;
	std::cout << "Do you want to draw the scene with 1) Software, or 2) OpenGL renderer?" << std::endl;
	std::cin >> a;

	IrrlichtDevice *device = 0x0;
	if(a == '1')
		device = createDevice( video::EDT_BURNINGSVIDEO, dimension2d<u32>(800,600), 16, false, false, false, 0);
	else if(a == '2')
		device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1920,1080), 32, false, false, false, 0);
	
	if(!device)
		return -1;

	device->setWindowCaption(L"TradingAgent");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	smgr->setShadowColor(video::SColor(150,0,0,0));
	smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);

	//IMeshManipulator *meshManip = driver->getMeshManipulator();

	// create light
	/*{
		ISceneNode * node = smgr->addLightSceneNode(0, core::vector3df(0,0,0),
				video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
		scene::ISceneNodeAnimator* anim = 0;
		anim = smgr->createFlyCircleAnimator (core::vector3df(0,10,0),100.0f, 0.0003f);
		node->addAnimator(anim);
		anim->drop();

		// attach billboard to light

		node = smgr->addBillboardSceneNode(node, core::dimension2d<f32>(50, 50));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		node->setMaterialTexture(0, driver->getTexture("../../bin/resources/Particle/particlewhite.bmp"));
	}*/

	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
            "../../bin/resources/Terrain/terrain-heightmap.bmp",
            0,                                      // parent node
            -1,                                     // node id
            core::vector3df(-2500.f, 100.f, -2500.f),         // position
            core::vector3df(0.f, 0.f, 0.f),         // rotation
            core::vector3df(50.f, 1.0f, 50.f),      // scale
            video::SColor ( 255, 255, 255, 255 ),   // vertexColor
            5,                                      // maxLOD
            scene::ETPS_17,                         // patchSize
            4                                       // smoothFactor
            );

    terrain->setMaterialFlag(video::EMF_LIGHTING, true);
    terrain->setMaterialTexture(0,
                    driver->getTexture("../../bin/resources/Terrain/terrain_dl.tga"));
    terrain->setMaterialTexture(1,
                    driver->getTexture("../../bin/resources/Terrain/detailmap3.jpg"));
    terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(4.0f, 1280.0f);

	//const float spawn_height = 175.0f;

	//ISceneNode *tower = smgr->addSceneNode("Tower");
	/*{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_base3.3ds");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();

			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Base_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));

			node->setPosition(vector3df(10.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(10.0f, spawn_height, 0.0f));
		}
	}
	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_head6.3ds");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Head_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(10.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(10.0f, spawn_height+6.0f, 0.0f));
		}
	}
	{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Tower/turret_gun6.3ds");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Tower/Weapon_Diffuse.tga") );
			node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(10.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(10.0f, spawn_height+8.0f, 0.0f));
		}
	}*/

	/*{
		IAnimatedMesh* mesh = smgr->getMesh("../../bin/resources/Mesh/Beast/beast.ms3d");
		meshManip->recalculateTangents(mesh, true, true, true);
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh, tower );
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, true);
			node->setMaterialFlag(EMF_FOG_ENABLE, true);
			node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
			//node->addShadowVolumeSceneNode();

			node->setAnimationSpeed(30.0f);
			node->setFrameLoop(1, 400);
			node->setMaterialTexture( 0, driver->getTexture("../../bin/resources/Mesh/Beast/beast1.jpg") );
			//node->setRotation(vector3df(-90.0f, 0.0f, 0.0f));
			node->setPosition(vector3df(-20.0f, 0.0f, 0.0f));
			float spawn_height = terrain->getHeight(node->getPosition().X, node->getPosition().Z);
			node->setPosition(vector3df(-20.0f, spawn_height, 0.0f));
			node->setScale(vector3df(0.2f, 0.2f, 0.2f));

			scene::ISceneCollisionManager* coll = smgr->getSceneCollisionManager();
			HealthSceneNode *healthbar = new scene::HealthSceneNode(node,smgr,-1,coll,50,10,vector3df(0,100,0));
			healthbar->setProgress(60);
			healthbar->setScale(vector3df(0.02f, 0.02f, 0.02f));
		}
	}*/

	//ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
	//ICameraSceneNode *camera = smgr->addCameraSceneNodeMaya(0, -1500.0f, 200.0f, 1500.0f);
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.25f);
	camera->setPosition(vector3df(0, 0, -40));
	float spawn_height = terrain->getHeight(camera->getPosition().X, camera->getPosition().Z);
	camera->setPosition(vector3df(0.0f, spawn_height+30.0f, -40.0f));
	if(a == '2')
		camera->setFarValue(100000);

	//////////////////////////////////////////
	// WEATHER INITIALIZING
	//////////////////////////////////////////
	irrWeatherManager *weatherMgr = 0x0;
	if(a == '1')
	{
		ISceneNode *sky = smgr->addSkyDomeSceneNode( driver->getTexture("../../bin/resources/Sky/skydome.jpg"),16,16, 1.0f, 2.0f);
		sky->setMaterialFlag(EMF_LIGHTING, false);
		//sky->drop();
	}
	else
	{
		driver->setFog(SColor(0, 255, 255, 255), EFT_FOG_LINEAR, 8000.0f, 40000.0f, 0.01f, true, true);
		weatherMgr = new irrWeatherManager(device);
		weatherMgr->getAtmosphere()->setUpdateFog(true);
		weatherMgr->getAtmosphere()->setSkyImage("../../bin/resources/Sky/skydome.jpg");
		weatherMgr->getAtmosphere()->setDaysPerDay(400);

		SCloudCreationInfo info;
		info.setDefaults();
		info.textureNames.push_back(stringc("../../bin/resources/Clouds/cumulus2.png"));
		info.textureNames.push_back(stringc("../../bin/resources/Clouds/cumulus3.png"));
		info.textureName = "../../bin/resources/Clouds/cumulus2.png";
		info.seed = device->getTimer()->getTime();
		info.numParticles = 10;

		ICloudLayer* layer = weatherMgr->addCloudLayer(vector3df(0,10000,0), info, 50, false);

		//info.textureNames.clear();
		info.textureName = "../../bin/resources/Clouds/cumulus1.png";
		weatherMgr->addCloudLayer(vector3df(0,19000,0), info, 80, false);
	}

	/*scene::CGridSceneNode* grid = new scene::CGridSceneNode(smgr->getRootSceneNode(), smgr);
	grid->setMaterialFlag(EMF_LIGHTING, false);
	grid->drop();*/

	/*GraphSceneNode *graph = new GraphSceneNode(smgr->getRootSceneNode(), smgr);
	for(unsigned int i = 0; i < 100.0f; i++)
	{
		graph->AddPlotPoint(vector3df(i*10.0f,sin(i*0.01f),0.0f));
	}
	graph->RegenerateGraph();
	graph->setMaterialFlag(EMF_LIGHTING, false);*/
	

	//////////////////////////////////////////
	// TOTEM INITIALIZING
	//////////////////////////////////////////
	Totem::ComponentFactory factory;
	Components::Health::RegisterToFactory(factory);
	Components::Sprite::RegisterToFactory(factory);
	EntityManager emgr(*terrain);

	///////////////////////////////
	// POPULATION
	///////////////////////////////
	try{
		Entity &entity = emgr.create(factory);
		entity.addComponent<EntityManager, ISceneManager>("Health", emgr, *smgr);
		if(a == '1')
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Particle/Particle.tga"), vector2di(64,64));
		}
		else
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Sprites/goblin_001.png"), vector2di(72,97));
		}
		entity.sendEvent0(T_HashedString("LOAD"));
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}

	try{
		Entity &entity = emgr.create(factory);
		entity.addComponent<EntityManager, ISceneManager>("Health", emgr, *smgr);
		if(a == '1')
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Particle/Particle.tga"), vector2di(64,64));
		}
		else
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Sprites/human_001.png"), vector2di(72,97));
		}
		entity.sendEvent0(T_HashedString("LOAD"));
		entity.getProperty<vector3df>("Position") = vector3df(40,0,0);
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}

	try{
		Entity &entity = emgr.create(factory);
		entity.addComponent<EntityManager, ISceneManager>("Health", emgr, *smgr);
		if(a == '1')
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string, vector2di>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Particle/Particle.tga"), vector2di(64,64));
		}
		else
		{
			entity.addComponent<ISceneNode, ISceneManager, std::string>(Components::Sprite::Type(), 
				*smgr->getRootSceneNode(), *smgr, std::string("../../bin/resources/Sprites/human_002.png"), vector2di(72,97));
		}
		entity.sendEvent0(T_HashedString("LOAD"));
		entity.getProperty<vector3df>("Position") = vector3df(30,0,0);
	}catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}

	//////////////////////////////////////////
	// GUI INITIALIZING
	//////////////////////////////////////////
	CIrrRocketGUI *rocket_gui = 0x0;
	if(a == '1')
	{
		guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                rect<s32>(10,10,260,22), true);
	}
	else
	{
		rocket_gui = new CIrrRocketGUI(device);
	}

	device->getCursorControl()->setVisible(false);

	double accum_time = 0.0;
	//int generation = 0;
	while(device->run())
	{
		if (!device->isWindowActive())
			device->yield();

		double fps_ms = 1.0 / (double)driver->getFPS();
		//device->setWindowCaption((const wchar_t*)(std::string("TradingAgent") + std::stringHelp::int_to_text(driver->getFPS())).c_str());

		if(fps_ms < 0.1)
			accum_time += fps_ms;
		/*if(accum_time > 10.0)
		{
			accum_time = 0.0;*/
		/*if(generation <= ngen)
		{
			ga.evolve();
			const ProsumerGenome &prosumer = static_cast<const ProsumerGenome &>(ga.statistics().bestIndividual());
			std::cout << "Best prosumer of generation " << generation << ":\n" << prosumer << "\n";
			generation++;
		}*/
		//}*/

		if(weatherMgr)
			weatherMgr->updateWeather();
		//emgr.update((float)fps_ms);

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		if(rocket_gui)
			rocket_gui->run();
		else
			guienv->drawAll();
		driver->endScene();


	}
	delete weatherMgr;
	device->drop();
	return 0;
}

/*float Objective(GAGenome &g) 
{
	GA3DBinaryStringGenome & genome = (GA3DBinaryStringGenome &)g;
	
	float score = 0.0;
	int count = 0;
	
	for(int i = 0; i<genome.width(); i++)
	{
		for(int j = 0; j<genome.height(); j++)
		{
			for(int k = 0; k<genome.depth(); k++)
			{
				if(genome.gene(i,j,k) == 0 && count%2 == 0)
					score += 1.0;
				if(genome.gene(i,j,k) == 1 && count%2 != 0)
					score += 1.0;
				count++;
			}
		}
	}
	return score;
}*/
