#pragma once

/**
 * @file
 * @class Totem::Component
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Component base class
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
 * The base ComponentType class simply holds the means to build ComponentTypes on top of it.
 * It has a type identifier used to associate with what type of ComponentType it is, and
 * a reference to the Entity that owns it.
 *
 * It also holds two virtual functions, update and onEvent, that can optionally be
 * overloaded by each ComponentType implementation.
 *
 * Note that the constructor takes an optional HAS_SIGNALSLOTS_INHERITANCE_TYPE. This is
 * a pre-processor type specified via types_config.h, and allows a user to specify the
 * exact requirement of the signal/slot system in use (Some implementations do require
 * that a class holding slots inherit from some class). Look at MinDepends/types.h for
 * an example of this.
 * 
 */

#include <Totem/types_config.h>

#include <Totem/Property.h>
#include <Totem/ComponentFactory.h>

namespace Totem {

class Component HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	/**
	 * Destructor
	 */
	virtual ~Component() {}

	/**
	 * Get the type that defines this ComponentType.
	 *
	 * @return Returns the type of the ComponentType.
	 */
	const T_String &getType() const { return type; }

	/**
	 * Optional virtual function that can be overloaded by
	 * ComponentType implementations. Update is typically called
	 * at least once per frame, and is channeled via the Entity.
	 *
	 */
    virtual void update(const F32 &/*deltaTime*/) {};

	/// Provide an assignment operator to leviate level W4 warning
	Component &operator= (const Component &rhs)
	{
		if(this == &rhs)
			return *this;

		throw T_Exception("Assignment operation between ComponentTypes are not supported!");
	}

protected:
	/**
	 * Protected Constructor
	 *
	 * @param owner Reference to the Entity that owns this ComponentType.
	 * @param type The type-name assigned to this ComponentType from it's implementation.
	 */
	Component(const T_String &type) : type(type) {};

	/// The type identifier for this ComponentType.
    T_String type;
};

} //namespace Totem

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the ComponentType implementation that calls it. It simplifies adding new ComponentTypes, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param ComponentType The ComponentImplementation class, for instance Health
 */
#define COMPONENT_0(EntityType, ComponentType) \
			static T_String Type() { return T_String(#ComponentType); } \
			static Totem::Component *Create(T_Any &owner, const T_String &name) \
			{ \
				EntityType *entity = NULL_PTR; \
				try { \
					entity = owner.cast<EntityType*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of owner was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#EntityType)).c_str()); \
				} \
				return new ComponentType(*entity, name); \
			} \
			static void RegisterToFactory(Totem::ComponentFactory &factory) { factory.registerComponent(ComponentType::Type(), &ComponentType::Create); } \
			ComponentType &operator= (const ComponentType &rhs) \
			{ \
				if(this == &rhs) \
					return *this; \
				throw T_Exception("Assignment operation between ComponentTypes are not supported!"); \
			} \
		protected: \
			EntityType &owner; \
		public: \
\

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the ComponentType implementation that calls it. It simplifies adding new ComponentTypes, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param ComponentType The ComponentImplementation class, for instance Health
 * @param Custom_type1 The custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_1(EntityType, ComponentType, Custom_type1) \
			static T_String Type() { return T_String(#ComponentType); } \
			static Totem::Component *Create(T_Any &owner, const T_String &name, T_Any &custom1) \
			{ \
				EntityType *entity = NULL_PTR; \
				try { \
					entity = owner.cast<EntityType*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of owner was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#EntityType)).c_str()); \
				} \
				Custom_type1 *custom = NULL_PTR; \
				try { \
					custom = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				return new ComponentType(*entity, name, *custom); \
			} \
			static void RegisterToFactory(Totem::ComponentFactory &factory) { factory.registerComponentCustom1(ComponentType::Type(), &ComponentType::Create); } \
			ComponentType &operator= (const ComponentType &rhs) \
			{ \
				if(this == &rhs) \
					return *this; \
				throw T_Exception("Assignment operation between ComponentTypes are not supported!"); \
			} \
		protected: \
			EntityType &owner; \
		public: \
\

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the ComponentType implementation that calls it. It simplifies adding new ComponentTypes, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param ComponentType The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_2(EntityType, ComponentType, Custom_type1, Custom_type2) \
			static T_String Type() { return T_String(#ComponentType); } \
			static Totem::Component *Create(T_Any &owner, const T_String &name, T_Any &custom1, T_Any &custom2) \
			{ \
				EntityType *entity = NULL_PTR; \
				try { \
					entity = owner.cast<EntityType*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of owner was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#EntityType)).c_str()); \
				} \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				return new ComponentType(*entity, name, *customA, *customB); \
			} \
			static void RegisterToFactory(Totem::ComponentFactory &factory) { factory.registerComponentCustom2(ComponentType::Type(), &ComponentType::Create); } \
			ComponentType &operator= (const ComponentType &rhs) \
			{ \
				if(this == &rhs) \
					return *this; \
				throw T_Exception("Assignment operation between ComponentTypes are not supported!"); \
			} \
		protected: \
			EntityType &owner; \
		public: \
\

 /**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the ComponentType implementation that calls it. It simplifies adding new ComponentTypes, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param ComponentType The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_3(EntityType, ComponentType, Custom_type1, Custom_type2, Custom_type3) \
			static T_String Type() { return T_String(#ComponentType); } \
			static Totem::Component *Create(T_Any &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3) \
			{ \
				EntityType *entity = NULL_PTR; \
				try { \
					entity = owner.cast<EntityType*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of owner was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#EntityType)).c_str()); \
				} \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				return new ComponentType(*entity, name, *customA, *customB, *customC); \
			} \
			static void RegisterToFactory(Totem::ComponentFactory &factory) { factory.registerComponentCustom3(ComponentType::Type(), &ComponentType::Create); } \
			ComponentType &operator= (const ComponentType &rhs) \
			{ \
				if(this == &rhs) \
					return *this; \
				throw T_Exception("Assignment operation between ComponentTypes are not supported!"); \
			} \
		protected: \
			EntityType &owner; \
		public: \
\

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the ComponentType implementation that calls it. It simplifies adding new ComponentTypes, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param ComponentType The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_4(EntityType, ComponentType, Custom_type1, Custom_type2, Custom_type3, Custom_type4) \
			static T_String Type() { return T_String(#ComponentType); } \
			static Totem::Component *Create(T_Any &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4) \
			{ \
				EntityType *entity = NULL_PTR; \
				try { \
					entity = owner.cast<EntityType*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of owner was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#EntityType)).c_str()); \
				} \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				return new ComponentType(*entity, name, *customA, *customB, *customC, *customD); \
			} \
			static void RegisterToFactory(Totem::ComponentFactory &factory) { factory.registerComponentCustom4(ComponentType::Type(), &ComponentType::Create); } \
			ComponentType &operator= (const ComponentType &rhs) \
			{ \
				if(this == &rhs) \
					return *this; \
				throw T_Exception("Assignment operation between ComponentTypes are not supported!"); \
			} \
		protected: \
			EntityType &owner; \
		public: \
\

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the ComponentType implementation that calls it. It simplifies adding new ComponentTypes, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param ComponentType The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type5 The fifth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_5(EntityType, ComponentType, Custom_type1, Custom_type2, Custom_type3, Custom_type4, Custom_type5) \
			static T_String Type() { return T_String(#ComponentType); } \
			static Totem::Component *Create(T_Any &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5) \
			{ \
				EntityType *entity = NULL_PTR; \
				try { \
					entity = owner.cast<EntityType*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of owner was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#EntityType)).c_str()); \
				} \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				Custom_type5 *customE = NULL_PTR; \
				try { \
					customE = custom5.cast<Custom_type5*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom5 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type5)).c_str()); \
				} \
				return new ComponentType(*entity, name, *customA, *customB, *customC, *customD, *customE); \
			} \
			static void RegisterToFactory(Totem::ComponentFactory &factory) { factory.registerComponentCustom5(ComponentType::Type(), &ComponentType::Create); } \
			ComponentType &operator= (const ComponentType &rhs) \
			{ \
				if(this == &rhs) \
					return *this; \
				throw T_Exception("Assignment operation between ComponentTypes are not supported!"); \
			} \
		protected: \
			EntityType &owner; \
		public: \
\

/**
 * This preprocessor macro simply adds a Type(), Create() and RegisterToFactory function 
 * to the ComponentType implementation that calls it. It simplifies adding new ComponentTypes, and
 * is here for convenience. Nothing is stopping the user to overlook this macro and implement
 * these three classes on their own.
 *
 * @param ComponentType The ComponentImplementation class, for instance Health
 * @param Custom_type1 The first custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type2 The second custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type3 The third custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type4 The fourth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type5 The fifth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 * @param Custom_type6 The sixth custom type passed into the macro, requires that the ComponentImplementation has a constructor that takes this type as custom parameter.
 */
#define COMPONENT_6(EntityType, ComponentType, Custom_type1, Custom_type2, Custom_type3, Custom_type4, Custom_type5, Custom_type6) \
			static T_String Type() { return T_String(#ComponentType); } \
			static Totem::Component *Create(T_Any &owner, const T_String &name, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5, T_Any &custom6) \
			{ \
				EntityType *entity = NULL_PTR; \
				try { \
					entity = owner.cast<EntityType*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of owner was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#EntityType)).c_str()); \
				} \
				Custom_type1 *customA = NULL_PTR; \
				try { \
					customA = custom1.cast<Custom_type1*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom1 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type1)).c_str()); \
				} \
				Custom_type2 *customB = NULL_PTR; \
				try { \
					customB = custom2.cast<Custom_type2*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom2 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type2)).c_str()); \
				} \
				Custom_type3 *customC = NULL_PTR; \
				try { \
					customC = custom3.cast<Custom_type3*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom3 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type3)).c_str()); \
				} \
				Custom_type4 *customD = NULL_PTR; \
				try { \
					customD = custom4.cast<Custom_type4*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom4 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type4)).c_str()); \
				} \
				Custom_type5 *customE = NULL_PTR; \
				try { \
					customE = custom5.cast<Custom_type5*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom5 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type5)).c_str()); \
				} \
				Custom_type6 *customF = NULL_PTR; \
				try { \
					customF = custom6.cast<Custom_type6*>(); \
				}catch(T_BadAnyCast) { \
					throw T_Exception(("Type of custom6 was bad when calling " + T_String(#ComponentType) + "::Create, expected " + T_String(#Custom_type6)).c_str()); \
				} \
				return new ComponentType(*entity, name, *customA, *customB, *customC, *customD, *customE, *customF); \
			} \
			static void RegisterToFactory(Totem::ComponentFactory &factory) { factory.registerComponentCustom6(ComponentType::Type(), &ComponentType::Create); } \
			ComponentType &operator= (const ComponentType &rhs) \
			{ \
				if(this == &rhs) \
					return *this; \
				throw T_Exception("Assignment operation between ComponentTypes are not supported!"); \
			} \
		protected: \
			EntityType &owner; \
		public:
