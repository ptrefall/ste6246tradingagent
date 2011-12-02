#include <ft2build.h>
#include FT_FREETYPE_H

#include <Irrlicht\irrlicht.h>

#include <GA\GASStateGA.h>
#include <GA\GA3DBinStrGenome.h>
#include <iostream>

#include <ClanLib\core.h>
#include <Totem\ComponentFactory.h>

#include <SceneNode\HealthSceneNode.h>
#include <SceneNode\CGridSceneNode.h>
#include <SceneNode\Weather\irrWeatherManager.h>
#include <SceneNode\TAnimSprite.h>

#include <GUI/CIrrRocketGUI.h>

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
	GAGenome &individual = ga.population().individual(0);


	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1920,1080), 32, false, false, false, 0);
	if(!device)
		return -1;

	device->setWindowCaption(L"TradingAgent");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                rect<s32>(10,10,260,22), true);

	smgr->setShadowColor(video::SColor(150,0,0,0));
	smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);

	IMeshManipulator *meshManip = driver->getMeshManipulator();

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
            core::vector3df(-4500.f, 100.f, -4500.f),         // position
            core::vector3df(0.f, 0.f, 0.f),         // rotation
            core::vector3df(100.f, 1.0f, 100.f),      // scale
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
    terrain->scaleTexture(4.0f, 320.0f);

	//const float spawn_height = 175.0f;

	ISceneNode *tower = smgr->addSceneNode("Tower");
	{
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
	}

	{
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
	}

	//ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
	//ICameraSceneNode *camera = smgr->addCameraSceneNodeMaya(0, -1500.0f, 200.0f, 1500.0f);
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.25f);
	camera->setPosition(vector3df(0, 0, -40));
	float spawn_height = terrain->getHeight(camera->getPosition().X, camera->getPosition().Z);
	camera->setPosition(vector3df(0.0f, spawn_height+30.0f, -40.0f));
	camera->setFarValue(100000);

	//ISceneNode *sky = smgr->addSkyDomeSceneNode( driver->getTexture("../../bin/resources/Sky/skydome.jpg"),16,16, 1.0f, 2.0f);
	//sky->setMaterialFlag(EMF_LIGHTING, false);
	//sky->drop();

	driver->setFog(SColor(0, 255, 255, 255), EFT_FOG_LINEAR, 8000.0f, 40000.0f, 0.01f, true, true);
	irrWeatherManager *weatherMgr = new irrWeatherManager(device);
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

	scene::CGridSceneNode* grid = new scene::CGridSceneNode(smgr->getRootSceneNode(), smgr);
	grid->setMaterialFlag(EMF_LIGHTING, false);
	grid->drop();

	std::vector<TAnimSprite*> sprites;
	{
		TAnimSprite* myNode = new TAnimSprite(smgr->getRootSceneNode(), smgr, 666);
		myNode->Load("../../bin/resources/Sprites/human_001.png",72,96);
		myNode->SetSpeed(100);
		myNode->setPosition(vector3df(40, 0, 0));
		float spwn_height = terrain->getHeight(myNode->getPosition().X, myNode->getPosition().Z);
		myNode->setPosition(vector3df(40, spwn_height, 0));
		myNode->setScale(vector3df(45,45,00));
		sprites.push_back(myNode);
	}
	{
		TAnimSprite* myNode = new TAnimSprite(smgr->getRootSceneNode(), smgr, 667);
		myNode->Load("../../bin/resources/Sprites/goblin_001.png",72,96);
		myNode->SetSpeed(100);
		myNode->setPosition(vector3df(30, 0, 0));
		float spwn_height = terrain->getHeight(myNode->getPosition().X, myNode->getPosition().Z);
		myNode->setPosition(vector3df(30, spwn_height, 0));
		myNode->setScale(vector3df(40,40,00));
		sprites.push_back(myNode);
	}

	CIrrRocketGUI rocket_gui(device);

	device->getCursorControl()->setVisible(false);

	double accum_time = 0.0;
	while(device->run())
	{
		if (!device->isWindowActive())
			device->yield();

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

		weatherMgr->updateWeather();

		for(unsigned int i = 0; i < sprites.size(); i++)
			sprites[i]->Update();

		//tower->setRotation(vector3df(0.0f, 1.0f, 0.0f));

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		rocket_gui.run();
		driver->endScene();


	}
	delete weatherMgr;
	device->drop();
	return 0;
}

float Objective(GAGenome &g) 
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
}
