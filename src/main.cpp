#include <Irrlicht\irrlicht.h>

#include <GA\GASimpleGA.h>
#include <GA\GA2DBinStrGenome.h>
#include <iostream>

#include <ClanLib\core.h>
#include <Totem\ComponentFactory.h>

#include <SceneNode\HealthSceneNode.h>
#include <SceneNode\CGridSceneNode.h>
#include <SceneNode\Weather\irrWeatherManager.h>

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


	IrrlichtDevice *device = createDevice( video::EDT_OPENGL, dimension2d<u32>(1920,1080), 16, false, false, false, 0);
	if(!device)
		return -1;

	device->setWindowCaption(L"TradingAgent");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                rect<s32>(10,10,260,22), true);

	smgr->setShadowColor(video::SColor(150,0,0,0));

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
			node->setPosition(vector3df(10.0f, 6.0f, 0.0f));
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
			node->setPosition(vector3df(10.0f, 8.0f, 0.0f));
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
			node->setScale(vector3df(0.2f, 0.2f, 0.2f));

			scene::ISceneCollisionManager* coll = smgr->getSceneCollisionManager();
			HealthSceneNode *healthbar = new scene::HealthSceneNode(node,smgr,-1,coll,50,10,vector3df(0,100,0));
			healthbar->setProgress(60);
			healthbar->setScale(vector3df(0.02f, 0.02f, 0.02f));
		}
	}

	//smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
	//smgr->addCameraSceneNodeMaya(0, -1500.0f, 200.0f, 1500.0f);
	ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.5f);
	camera->setPosition(vector3df(0, 30, -40));

	//ISceneNode *sky = smgr->addSkyDomeSceneNode( driver->getTexture("../../bin/resources/Sky/skydome.jpg"),16,16, 1.0f, 2.0f);
	//sky->setMaterialFlag(EMF_LIGHTING, false);
	//sky->drop();

	driver->setFog(SColor(0, 255, 255, 255), EFT_FOG_LINEAR, 8000.0f, 40000.0f, 0.01f, true, true);
	irrWeatherManager *weatherMgr = new irrWeatherManager(device);
	weatherMgr->getAtmosphere()->setUpdateFog(true);
	weatherMgr->getAtmosphere()->setSkyImage("../../bin/resources/Sky/skydome.jpg");

	SCloudCreationInfo info;
    info.setDefaults();
	info.textureNames.push_back(stringc("../../bin/resources/Clouds/cumulus2.png"));
    info.textureNames.push_back(stringc("../../bin/resources/Clouds/cumulus3.png"));
    info.textureName = "../../bin/resources/Clouds/cumulus2.png";
    info.seed = device->getTimer()->getTime();
    info.numParticles = 10;

	ICloudLayer* layer = weatherMgr->addCloudLayer(vector3df(0,19000,0), info, 50, false);

	info.textureNames.clear();
    info.textureName = "../../bin/resources/Clouds/cumulus1.png";
    weatherMgr->addCloudLayer(vector3df(0,49000,0), info, 300, false);

	scene::CGridSceneNode* grid = new scene::CGridSceneNode(smgr->getRootSceneNode(), smgr);
	grid->setMaterialFlag(EMF_LIGHTING, false);
	grid->drop();

	device->getCursorControl()->setVisible(false);

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

		weatherMgr->updateWeather();

		//tower->setRotation(vector3df(0.0f, 1.0f, 0.0f));

		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();


	}
	delete weatherMgr;
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
