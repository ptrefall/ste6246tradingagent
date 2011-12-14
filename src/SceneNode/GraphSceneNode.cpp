#include "GraphSceneNode.h"
#include <Irrlicht\ISceneManager.h>
#include <Irrlicht\IVideoDriver.h>

namespace irr
{
namespace scene
{
GraphSceneNode::GraphSceneNode(ISceneNode* parent, ISceneManager* smgr, s32 id, video::SColor graphcolor)
		: ISceneNode(parent, smgr, id),m_graphcolor(graphcolor)
{
	// Set the material
	Buffer.Material.Wireframe = false;
	Buffer.Material.Lighting = false;
	Buffer.Material.Thickness = 1;
	Buffer.Material.FogEnable = false;
	Buffer.Material.ZWriteEnable = false;

	// Set the default culling state to Frustum Box
	AutomaticCullingState = EAC_FRUSTUM_BOX;

	//RegenerateGraph();
}

GraphSceneNode* GraphSceneNode::clone(ISceneNode *newParent, ISceneManager *newSceneManager)
{
	if (!newParent) newParent = Parent;
	if (!newSceneManager) newSceneManager = SceneManager;

	GraphSceneNode* clone = new GraphSceneNode(
		Parent,
		SceneManager,
		ID,
		m_graphcolor);

	if(!clone)
		return 0x0;

	clone->SetMaterial(Buffer.Material);

	clone->drop();
	return clone;
}

void GraphSceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void GraphSceneNode::RegenerateGraph()
{
	//Clean up memory
	Buffer.Indices.clear();
	Buffer.Vertices.clear();

	u32 m_numVertices = plot.size(); //((m_height / m_width) + 1) * 2 * 2;

	if ( m_numVertices > 65535)
	{
		//Too many vertices on 16 bit for for 16bit indices of SMeshBuffer
		//Returning with a blank buffer to avoid segfaulting the entire application
		return;
	}

	u32 indexIndex = 0;

	float min_x = 0.0f, min_y = 0.0f;
	float max_x = 0.0f, max_y = 0.0f;

	for(u32 i = 0; i < m_numVertices; i++)
	{
		Buffer.Vertices.push_back(video::S3DVertex(plot[i], core::vector3df(0.0f, 1.0f, 0.0f), m_graphcolor, core::vector2df(0.0f, 0.0f)));
		Buffer.Indices.push_back(indexIndex++);

		if(plot[i].X < min_x)
			min_x = plot[i].X;
		else if(plot[i].X > max_x)
			max_x = plot[i].X;

		if(plot[i].Y < min_y)
			min_y = plot[i].Y;
		else if(plot[i].Y > max_y)
			max_y = plot[i].Y;
	}

	// Create our box, it is the size of the graph exactly, plus 1 in the Z axis
	Buffer.BoundingBox = core::aabbox3df(min_x, min_y, -0.5f, max_x, max_y, 0.5f);
}

void GraphSceneNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	//Prep to render
	if(driver)
	{
		driver->setMaterial(Buffer.Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

		driver->drawVertexPrimitiveList(Buffer.getVertices(), Buffer.getVertexCount(), Buffer.getIndices(), Buffer.getVertexCount(), video::EVT_STANDARD, scene::EPT_LINES);
	}
}

const core::aabbox3d<f32>& GraphSceneNode::getBoundingBox() const
{
	return Buffer.BoundingBox;
}

u32 GraphSceneNode::getMaterialCount()
{
	return 1;
}

video::SMaterial& GraphSceneNode::getMaterial(u32 i)
{
	return Buffer.Material;
}

video::SColor GraphSceneNode::GetGraphColor()
{
	return m_graphcolor;
}

void GraphSceneNode::SetGraphColor(video::SColor newcolor)
{
	m_graphcolor = newcolor;
	RegenerateGraph();
}

void GraphSceneNode::SetMaterial(video::SMaterial newMaterial)
{
	Buffer.Material = newMaterial;
}

void GraphSceneNode::AddPlotPoint(const core::vector3df &point)
{
	plot.push_back(point);
}

}
}
