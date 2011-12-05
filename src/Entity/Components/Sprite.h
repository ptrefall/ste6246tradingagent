#pragma once

#include <Totem/Component.h>
#include "../Entity.h"
#include "../EntityManager.h"

#include <Irrlicht\irrlicht.h>
#include <SceneNode\TAnimSprite.h>

namespace Components
{
	class Sprite : public Totem::Component
	{
	public:
		COMPONENT_3(Entity, Sprite, irr::scene::ISceneNode, irr::scene::ISceneManager, std::string)
		Sprite(Entity &owner, const std::string &name, irr::scene::ISceneNode& parent, irr::scene::ISceneManager& mgr, std::string &filename);
		virtual ~Sprite();

		virtual void update(const float &dt);

	protected:
		Totem::Property<int> anim_speed_property;
		Totem::Property<irr::scene::ISceneNode*> sceneNode;
		Totem::Property<irr::core::vector3df> position_property;
		/*Totem::Property<float> health_property;
		Totem::Property<float> maxhealth_property;

		void onHealthChanged(const float &oldValue, const float &newValue);*/
		void onPositionChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue);

		irr::scene::ISceneManager& smgr;
		const std::string filename;
		irr::scene::TAnimSprite *spriteNode;
	};
}
