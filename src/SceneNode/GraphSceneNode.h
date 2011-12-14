#pragma once

#include <Irrlicht\ISceneNode.h>
#include <Irrlicht\SMeshBuffer.h>
#include <vector>

namespace irr
{
namespace scene
{

class GraphSceneNode : public ISceneNode
{
public:
	//! Constructor
	GraphSceneNode(ISceneNode* parent, ISceneManager* smgr, s32 id = -1, video::SColor graphcolor = video::SColor(255,128,128,128));

	//! Will create a copy of this scenenode and it's settings
	virtual GraphSceneNode* clone(ISceneNode* newParent = 0, ISceneManager* newSceneManager = 0);

	//! Pre-Register stuff
	virtual void OnRegisterSceneNode();

	//! Render our graph using 3D lines stored inside the internal meshbuffer
	virtual void render();

	//! Returns our bounding box
	virtual const core::aabbox3d<f32>& getBoundingBox() const;

	//! Returns the total number of materials, in this case, only 1
	virtual u32 getMaterialCount();

	//! Returns the only material
	virtual video::SMaterial& getMaterial(u32 i);

	//! Will cause the graph scene node to rebuild it's graph
	void RegenerateGraph();

	//! Returns the Grid Color
	video::SColor GetGraphColor();

	//! Sets the general graph color
	void SetGraphColor(video::SColor newcolor);

	//! Allows for setting a complete new material
	void SetMaterial(video::SMaterial newMaterial);

	void AddPlotPoint(const core::vector3df &point);

private:
	video::SColor m_graphcolor;

	SMeshBuffer Buffer;
	std::vector<core::vector3df> plot;
};

}}
