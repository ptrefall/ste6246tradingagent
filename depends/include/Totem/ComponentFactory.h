#pragma once

/**
 * @file
 * @class Totem::ComponentFactory
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Component Factory class
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
 * The component factory has the job of holding a register of component types and the means
 * to instanciate those registered component types.
 *
 * It holds a function pointer definition ComponentCreator, that each component implementation
 * must adhere to in order to register a component type to the factory.
 * 
 * There's nothing in the design that stops the user from having multiple factory instances
 * active, and use it as a way to organize components, but an Entity- and a component-instance
 * will only associate with a single component factory instance.
 * 
 */

#include <Totem/types_config.h>

namespace Totem {

class Component;
class ComponentFactory
{
public:
	/**
	 * Constructor
	 */
	ComponentFactory();

	/**
	 * Destructor
	 */
	~ComponentFactory();

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param Entity Reference to the Entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 */
	typedef Component*(* ComponentCreator)(T_Any &owner, const T_String &type);

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param Entity Reference to the Entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 * @param custom1 The first custom parameter injected into the component constructor
	 */
	typedef Component*(* ComponentCreator1)(T_Any &owner, const T_String &type, T_Any &custom1);

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param Entity Reference to the Entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 * @param custom1 The first custom parameter injected into the component constructor
	 * @param custom2 The second custom parameter injected into the component constructor
	 */
	typedef Component*(* ComponentCreator2)(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2);

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param Entity Reference to the Entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 * @param custom1 The first custom parameter injected into the component constructor
	 * @param custom2 The second custom parameter injected into the component constructor
	 * @param custom3 The third custom parameter injected into the component constructor
	 */
	typedef Component*(* ComponentCreator3)(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3);

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param Entity Reference to the Entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 * @param custom1 The first custom parameter injected into the component constructor
	 * @param custom2 The second custom parameter injected into the component constructor
	 * @param custom3 The third custom parameter injected into the component constructor
	 * @param custom4 The fourth custom parameter injected into the component constructor
	 */
	typedef Component*(* ComponentCreator4)(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4);

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param Entity Reference to the Entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 * @param custom1 The first custom parameter injected into the component constructor
	 * @param custom2 The second custom parameter injected into the component constructor
	 * @param custom3 The third custom parameter injected into the component constructor
	 * @param custom4 The fourth custom parameter injected into the component constructor
	 * @param custom5 The fifth custom parameter injected into the component constructor
	 */
	typedef Component*(* ComponentCreator5)(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5);

	/**
	 * Function pointer definition, forces a component implementation to provide
	 * a function that supports the format. Meant for a component implementation
	 * to instanciate itself within it's function, and then provide it, along with
	 * a type identifier, to the component factory for registration.
	 *
	 * @param Entity Reference to the Entity that will own this component instance.
	 * @param type The type identifier assigned to this component instance.
	 * @param custom1 The first custom parameter injected into the component constructor
	 * @param custom2 The second custom parameter injected into the component constructor
	 * @param custom3 The third custom parameter injected into the component constructor
	 * @param custom4 The fourth custom parameter injected into the component constructor
	 * @param custom5 The fifth custom parameter injected into the component constructor
	 * @param custom6 The sixth custom parameter injected into the component constructor
	 */
	typedef Component*(* ComponentCreator6)(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5, T_Any &custom6);

	//--------------------------------------------------------------------------------

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponent(const T_String &type, ComponentCreator functor);

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponentCustom1(const T_String &type, ComponentCreator1 functor);

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponentCustom2(const T_String &type, ComponentCreator2 functor);

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponentCustom3(const T_String &type, ComponentCreator3 functor);

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponentCustom4(const T_String &type, ComponentCreator4 functor);

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponentCustom5(const T_String &type, ComponentCreator5 functor);

	/**
	 * Registers a component with the factory. This has to be done before the component
	 * can be instanciated.
	 *
	 * @param type The identifier assigned to this component type.
	 * @param functor The function pointer to the component's create function.
	 */
    void registerComponentCustom6(const T_String &type, ComponentCreator6 functor);

	//--------------------------------------------------------------------------------

	/**
	 * Create an instance of a component of type, owned by Entity.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 */
	Component* createComponent(T_Any &owner, const T_String &type);

	/**
	 * Create an instance of a component of type, owned by Entity, that takes custom parameters.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 * @param custom1 The first custom parameter passed into component constructor.
	 */
	Component* createComponentCustom1(T_Any &owner, const T_String &type, T_Any &custom1);

	/**
	 * Create an instance of a component of type, owned by Entity, that takes custom parameters.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 * @param custom1 The first custom parameter passed into component constructor.
	 * @param custom2 The second custom parameter passed into component constructor.
	 */
	Component* createComponentCustom2(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2);

	/**
	 * Create an instance of a component of type, owned by Entity, that takes custom parameters.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 * @param custom1 The first custom parameter passed into component constructor.
	 * @param custom2 The second custom parameter passed into component constructor.
	 * @param custom3 The third custom parameter passed into component constructor.
	 */
	Component* createComponentCustom3(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3);

	/**
	 * Create an instance of a component of type, owned by Entity, that takes custom parameters.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 * @param custom1 The first custom parameter passed into component constructor.
	 * @param custom2 The second custom parameter passed into component constructor.
	 * @param custom3 The third custom parameter passed into component constructor.
	 * @param custom4 The fourth custom parameter passed into component constructor.
	 */
	Component* createComponentCustom4(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4);

	/**
	 * Create an instance of a component of type, owned by Entity, that takes custom parameters.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 * @param custom1 The first custom parameter passed into component constructor.
	 * @param custom2 The second custom parameter passed into component constructor.
	 * @param custom3 The third custom parameter passed into component constructor.
	 * @param custom4 The fourth custom parameter passed into component constructor.
	 * @param custom5 The fifth custom parameter passed into component constructor.
	 */
	Component* createComponentCustom5(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5);

	/**
	 * Create an instance of a component of type, owned by Entity, that takes custom parameters.
	 *
	 * @param entity The owner of the component instance.
	 * @param type The registered component type identifier associated with the component.
	 * @param custom1 The first custom parameter passed into component constructor.
	 * @param custom2 The second custom parameter passed into component constructor.
	 * @param custom3 The third custom parameter passed into component constructor.
	 * @param custom4 The fourth custom parameter passed into component constructor.
	 * @param custom5 The fifth custom parameter passed into component constructor.
	 * @param custom6 The sixth custom parameter passed into component constructor.
	 */
	Component* createComponentCustom6(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5, T_Any &custom6);

private:
	/// The container of component creator function pointers registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator>::Type* creators;
	/// The container of component creator function pointers that take one custom parameter registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator1>::Type* creators_custom1;
	/// The container of component creator function pointers that take two custom parameter registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator2>::Type* creators_custom2;
	/// The container of component creator function pointers that take three custom parameter registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator3>::Type* creators_custom3;
	/// The container of component creator function pointers that take four custom parameter registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator4>::Type* creators_custom4;
	/// The container of component creator function pointers that take five custom parameter registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator5>::Type* creators_custom5;
	/// The container of component creator function pointers that take six custom parameter registered to the factory, each associated with a string key.
	T_Map<T_String, ComponentCreator6>::Type* creators_custom6;
};

} //namespace Totem
