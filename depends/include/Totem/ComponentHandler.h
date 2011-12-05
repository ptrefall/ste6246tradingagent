#pragma once

/**
 * @file
 * @class Totem::ComponentHandler
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief ComponentHandler base class
 *
 * @section LICENSE
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 * Note: Some of the libraries Totem EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * The ComponentHandler holds the means of containing and managing components.
 * 
 */

#include <Totem/types_config.h>
#include <Totem/Component.h>
#include <Totem/ComponentFactory.h>

namespace Totem {

template<class EntityType>
class ComponentHandler
{
public:
	/**
	 * Constructor
	 *
	 * @param componentFactory The componentFactory instance from which this ComponentHandler will instanciate components.
	 */
	ComponentHandler(EntityType &thisAsEntity, ComponentFactory& componentFactory)
		: thisAsEntity(thisAsEntity), componentFactory(componentFactory)
	{
	}
	/**
	 * Destructor
	 */
	virtual ~ComponentHandler()
	{
		for(unsigned int i = 0; i < components.size(); i++)
			delete components[i];
		components.clear();
	}

	//--------------------------------------------------------------

	/**
	 * Add a component of specified type to this ComponentHandler.
	 *
	 * @param type The type of the component.
	 * @return Returns a reference to the component that was added to the ComponentHandler.
	 */
	Component &addComponent(const T_String& type);

	/**
	 * Add a component of specified type to this ComponentHandler with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @return Returns a reference to the component that was added to the ComponentHandler.
	 */
	template<class T>
	Component &addComponent(const T_String& type, T &custom1)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			Component &component = *components[i];
			if(component.getType() == type)
				return component;
		}

		T_Any entity = &thisAsEntity;
		T_Any any = &custom1;
		Component* component = componentFactory.createComponentCustom1(entity, type, any);
		components.push_back(component);
		return *component;
	}


	/**
	 * Add a component of specified type to this ComponentHandler with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @return Returns a reference to the component that was added to the ComponentHandler.
	 */
	template<class T, class U>
	Component &addComponent(const T_String& type, T &custom1, U &custom2)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			Component &component = *components[i];
			if(component.getType() == type)
				return component;
		}

		T_Any entity = &thisAsEntity;
		T_Any any = &custom1;
		T_Any any2 = &custom2;
		Component* component = componentFactory.createComponentCustom2(entity, type, any, any2);
		components.push_back(component);
		return *component;
	}

	/**
	 * Add a component of specified type to this ComponentHandler with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @return Returns a reference to the component that was added to the ComponentHandler.
	 */
	template<class T, class U, class V>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			Component &component = *components[i];
			if(component.getType() == type)
				return component;
		}

		T_Any entity = &thisAsEntity;
		T_Any any = &custom1;
		T_Any any2 = &custom2;
		T_Any any3 = &custom3;
		Component* component = componentFactory.createComponentCustom3(entity, type, any, any2, any3);
		components.push_back(component);
		return *component;
	}

	/**
	 * Add a component of specified type to this ComponentHandler with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @return Returns a reference to the component that was added to the ComponentHandler.
	 */
	template<class T, class U, class V, class W>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			Component &component = *components[i];
			if(component.getType() == type)
				return component;
		}

		T_Any entity = &thisAsEntity;
		T_Any any = &custom1;
		T_Any any2 = &custom2;
		T_Any any3 = &custom3;
		T_Any any4 = &custom4;
		Component* component = componentFactory.createComponentCustom4(entity, type, any, any2, any3, any4);
		components.push_back(component);
		return *component;
	}

	/**
	 * Add a component of specified type to this ComponentHandler with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @param custom5 The custom parameter of type X
	 * @return Returns a reference to the component that was added to the ComponentHandler.
	 */
	template<class T, class U, class V, class W, class X>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			Component &component = *components[i];
			if(component.getType() == type)
				return component;
		}

		T_Any entity = &thisAsEntity;
		T_Any any = &custom1;
		T_Any any2 = &custom2;
		T_Any any3 = &custom3;
		T_Any any4 = &custom4;
		T_Any any5 = &custom5;
		Component* component = componentFactory.createComponentCustom5(entity, type, any, any2, any3, any4, any5);
		components.push_back(component);
		return *component;
	}

	/**
	 * Add a component of specified type to this ComponentHandler with custom parameters.
	 *
	 * @param type The type of the component.
	 * @param custom1 The custom parameter of type T
	 * @param custom2 The custom parameter of type U
	 * @param custom3 The custom parameter of type V
	 * @param custom4 The custom parameter of type W
	 * @param custom5 The custom parameter of type X
	 * @param custom6 The custom parameter of type Y
	 * @return Returns a reference to the component that was added to the ComponentHandler.
	 */
	template<class T, class U, class V, class W, class X, class Y>
	Component &addComponent(const T_String& type, T &custom1, U &custom2, V &custom3, W &custom4, X &custom5, Y &custom6)
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			Component &component = *components[i];
			if(component.getType() == type)
				return component;
		}

		T_Any entity = &thisAsEntity;
		T_Any any = &custom1;
		T_Any any2 = &custom2;
		T_Any any3 = &custom3;
		T_Any any4 = &custom4;
		T_Any any5 = &custom5;
		T_Any any6 = &custom6;
		Component* component = componentFactory.createComponentCustom6(entity, type, any, any2, any3, any4, any5, any6);
		components.push_back(component);
		return *component;
	}

	//--------------------------------------------------------------
	
	/**
	 * Check whether the specified component type exist in this ComponentHandler.
	 *
	 * @param type The type of the component.
	 * @return Returns true if the component exist in this ComponentHandler, false if it doesn't.
	 */
	bool hasComponent(const T_String& type);

	/**
	 * Get a reference to a component of specified type from the ComponentHandler.
	 *
	 * @param type The type of the component.
	 * @return Returns a reference to the component.
	 */
	Component &getComponent(const T_String& type);

	/**
	 * Get a reference to the entire list of components owned by the ComponentHandler.
	 *
	 * @return Returns a reference to the ComponentHandler's component list.
	 */
	T_Vector<Component*>::Type &getComponents() { return components; }
	
	//--------------------------------------------------------------

	/**
	 * Call update function on all the components owned by this ComponentHandler.
	 *
	 * @param deltaTime  Should be the time elapsed since update was called last time.
	 */
	void updateComponents(const F32 &deltaTime);

	//--------------------------------------------------------------

	/// Provide an assignment operator to leviate level W4 warning
	ComponentHandler &operator= (const ComponentHandler &rhs);

protected:
	/// The list of all components owned by this ComponentHandler.
	T_Vector<Component*>::Type components;

	//--------------------------------------------------------------

	/// Reference to the entity implementation that inherits this ComponentHandler.
	EntityType &thisAsEntity;

	/// Reference to the component factory responsible for instancing components for this ComponentHandler.
	ComponentFactory& componentFactory;
};

//------------------------------------------------------

template<class EntityType>
Component &ComponentHandler<EntityType>::addComponent(const T_String& type)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component &component = *components[i];
		if(component.getType() == type)
			return component;
	}
	T_Any entity = &thisAsEntity;
	Component* component = componentFactory.createComponent(entity, type);
	components.push_back(component);
	return *component;
}

template<class EntityType>
bool ComponentHandler<EntityType>::hasComponent(const T_String& type)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component *component = components[i];
		if(component->getType() == type)
			return true;
	}
	return false;
}

template<class EntityType>
Component &ComponentHandler<EntityType>::getComponent(const T_String& type)
{
	for(unsigned int i = 0; i < components.size(); i++)
	{
		Component *component = components[i];
		if(component->getType() == type)
		{
			return *component;
		}
	}
	throw T_Exception(("Unable to get component " + type).c_str());
}

template<class EntityType>
void ComponentHandler<EntityType>::updateComponents(const F32 &deltaTime)
{
	for(unsigned int i = 0; i < components.size(); i++)
		components[i]->update(deltaTime);
}

template<class EntityType>
ComponentHandler<EntityType> &ComponentHandler<EntityType>::operator= (const ComponentHandler<EntityType> &rhs)
{
	if(this == &rhs)
		return *this;

	throw T_Exception("Assignment operation between ComponentHandlers are not supported!");
}

} //namespace Totem
