#include <Irrlicht\irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
	IrrlichtDevice *device = createDevice( video::EDT_DIRECT3D9, dimension2d<u32>(640,480), 16, false, false, false, 0);
	if(!device)
		return -1;

	device->setWindowCaption(L"TradinAgent");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
		smgr->drawAll();
		driver->endScene();
	}
	device->drop();
	return 0;
}
