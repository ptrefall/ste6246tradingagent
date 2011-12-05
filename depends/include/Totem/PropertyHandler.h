#pragma once

/**
 * @file
 * @class Totem::PropertyHandler
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief PropertyHandler base class
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
 * The PropertyHandler holds the means of containing and managing properties.
 * 
 */

#include <Totem/Property.h>

namespace Totem {

template<class UserData = void*>
class PropertyHandler
{
public:
	/**
	 * Constructor
	 *
	 */
	PropertyHandler() {}

	/**
	 * Destructor
	 */
	virtual ~PropertyHandler()
	{
		removeAllProperties();
	}

	//--------------------------------------------------------------
	
	/**
	 * Check whether the specified property name exist in this PropertyHandler.
	 * This function works on the interface (IProperty) of the property,
	 * thus no type-casting is involved in it's usage.
	 *
	 * @param name The name of the property.
	 * @return Returns true if the property exist in this PropertyHandler, false if it doesn't.
	 */
	bool hasProperty(const T_String& name);

	/**
	 * Add a property of specified type T and name to this PropertyHandler with a default value.
	 * If readOnly is specified to true, one can only change the property by
	 * directly calling property.set(value, forced=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property used to store and associate the property in the PropertyHandler.
	 * @param defaultValue The initial value this property should be set to when added to the PropertyHandler.
	 * @param readOnly Flag this property as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property that was added to the PropertyHandler.
	 */
	template<class T>Property<T> addProperty(const T_String& name, const T &defaultValue, bool readOnly = false)
	{
		T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
		if(it != properties.end())
		{
			Property<T>* property;
	#ifdef _DEBUG
			property = dynamic_cast< Property<T>* >(it->second);
			if(!property)
				throw T_Exception(("Property " + name + " already exists, but with another type!").c_str());
	#else
			property = static_cast< Property<T>* >(it->second);
	#endif
			sign_propertyAdded.invoke(property->getInterface());
			return *property;
		}

		Property<T> *property = new Property<T>(name, readOnly);
		property->set(defaultValue, true);
		properties[property->getName()] = property;

		//return *property;
		sign_propertyAdded.invoke(property->getInterface());
		return getProperty<T>(name);
	}

	/**
	 * Add a property of specified type T and name to this PropertyHandler with a default value and userdata of type UserData.
	 * If readOnly is specified to true, one can only change the property by
	 * directly calling property.set(value, forced=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property used to store and associate the property in the PropertyHandler.
	 * @param defaultValue The initial value this property should be set to when added to the PropertyHandler.
	 * @param userData The userdata is of type specified for the PropertyHandler's class template, and provides optional userdata description of the property.
	 * @param readOnly Flag this property as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property that was added to the PropertyHandler.
	 */
	template<class T>Property<T> addProperty(const T_String& name, const T &defaultValue, const UserData &userData, bool readOnly = false)
	{
		T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
		if(it != properties.end())
		{
			Property<T>* property;
	#ifdef _DEBUG
			property = dynamic_cast< Property<T>* >(it->second);
			if(!property)
				throw T_Exception(("Property " + name + " already exists, but with another type!").c_str());
	#else
			property = static_cast< Property<T>* >(it->second);
	#endif
			sign_propertyWithUserDataAdded.invoke(property->getInterface(), userData);
			return *property;
		}

		Property<T> *property = new Property<T>(name, readOnly);
		property->set(defaultValue, true);
		properties[property->getName()] = property;

		//return *property;
		sign_propertyWithUserDataAdded.invoke(property->getInterface(), userData);
		return getProperty<T>(name);
	}

	/**
	 * Add a property interface to this PropertyHandler.
	 * There can be situations where this is required.
	 *
	 * @param property The interface of the property.
	 */
	void addProperty(IProperty *property);

	/**
	 * Get a shared_ptr (pimpl) reference to a property of specified name from the PropertyHandler.
	 *
	 * @param name The name of the property.
	 * @return Returns a shared_ptr (pimpl) reference to the property.
	 */
	template<class T>Property<T> getProperty(const T_String& name)
	{
		T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
		if(it != properties.end())
		{
			Property<T>* property;
	#ifdef _DEBUG
			property = dynamic_cast< Property<T>* >(it->second);
			if(!property)
				throw T_Exception(("Tried to get property " + name + ", but the type was wrong!").c_str());
	#else
			property = static_cast< Property<T>* >(it->second);
	#endif
			return *property;
		}
		else
			throw T_Exception(("Unable to get property " + name).c_str());
	}

	/**
	 * Get a property interface pointer to a property of specified name from the PropertyHandler.
	 *
	 * @param name  The name of the property.
	 * @return The interface pointer to the property.
	 */
	IProperty *getIProperty(const T_String& name);

	/**
	 * Remove the property of specified name from PropertyHandler with
	 * option to postpone deletion until the next time update
	 * is called on the PropertyHandler.
	 *
	 * @param name The name of the property.
	 * @param postponeDelete Flag whether to postpone the deletion of this property (if true), or delete it immediately (if false). Defaults to false.
	 */
	void removeProperty(const T_String& name, bool postponeDelete = false);

	/**
	 * Remove all properties from PropertyHandler.
	 *
	 */
	void removeAllProperties();

	/**
	 * Delete all properties that was deleted last time update was called
	 * and marked postponeDelete.
	 *
	 */
	void clearDeletedProperties();

	/**
	 * Get a reference to the entire map of properties owned by the PropertyHandler.
	 *
	 * @return Returns a reference to the PropertyHandler's property map.
	 */
	T_Map<T_String, IProperty*>::Type &getProperties() { return properties; }

	//--------------------------------------------------------------
	
	/**
	 * Handles deletion of all properties pending for deletion in this PropertyHandler.
	 *
	 */
	void updateProperties();

	//--------------------------------------------------------------

	/// Provide an assignment operator to leviate level W4 warning
	PropertyHandler &operator= (const PropertyHandler &rhs)
	{
		if(this == &rhs)
			return *this;

		throw T_Exception("Assignment operation between PropertyHandler are not supported!");
	}

	//--------------------------------------------------------------

	/**
	 * Function that gives the outside access to the PropertyHandler's
	 * propertyAdded signal. It's through this function call we can
	 * register slots to the propertyAdded signal.
	 *
	 * @return Returns the propertyAdded signal of this property handler.
	 */
	typename T_Signal_v1<IProperty*>::Type &propertyAdded() { return sign_propertyAdded; }

	/**
	 * Function that gives the outside access to the PropertyHandler's
	 * propertyWithUserDataAdded signal. It's through this function call we can
	 * register slots to the propertyWithUserDataAdded signal.
	 *
	 * @return Returns the propertyWithUserDataAdded signal of this property handler.
	 */
	typename T_Signal_v2<IProperty*, const UserData&>::Type &propertyWithUserDataAdded() { return sign_propertyWithUserDataAdded; }

protected:
	/// The map of all properties owned by this PropertyHandler.
	T_Map<T_String, IProperty*>::Type properties;
	/// The list of all properties pending deletion in this PropertyHandler.
	T_Vector<IProperty*>::Type deletedProperties;
	/// Signal that's emitted when a property with NO userdata is added to the property handler.
	typename T_Signal_v1<IProperty*>::Type sign_propertyAdded;
	/// Signal that's emitted when a property with userdata is added to the property handler.
	typename T_Signal_v2<IProperty*, const UserData&>::Type sign_propertyWithUserDataAdded;
};

//------------------------------------------------------

template<class UserData>
inline bool PropertyHandler<UserData>::hasProperty(const T_String& name)
{
	if(properties.empty())
		return false;

	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
	if(it != properties.end())
		return true;
	else
		return false;
}

template<class UserData>
inline void PropertyHandler<UserData>::addProperty(IProperty *property)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(property->getName());
	if(it == properties.end())
		properties[property->getName()] = property;
}

template<class UserData>
inline IProperty *PropertyHandler<UserData>::getIProperty(const T_String& name)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
	if(it != properties.end())
		return it->second;
	else
		throw T_Exception(("Unable to get property " + name).c_str());
}

template<class UserData>
inline void PropertyHandler<UserData>::removeProperty(const T_String& name, bool postponeDelete)
{
	T_Map<T_String, IProperty*>::Type::iterator it = properties.find(name);
	if(it != properties.end())
	{
		IProperty* property = (*it).second;
		if(postponeDelete)
			deletedProperties.push_back(property);
		else
			delete property;
		properties.erase(it);
	}
}

template<class UserData>
inline void PropertyHandler<UserData>::removeAllProperties()
{
	T_Map<T_String, IProperty*>::Type::iterator it;
	for(it = properties.begin(); it != properties.end(); ++it)
	{
		IProperty* property = (*it).second;
		delete property;
	}
	properties.clear();
	clearDeletedProperties();
}

template<class UserData>
inline void PropertyHandler<UserData>::updateProperties()
{
	clearDeletedProperties();
}

template<class UserData>
inline void PropertyHandler<UserData>::clearDeletedProperties()
{
	for(unsigned int i = 0; i < deletedProperties.size(); i++)
		delete deletedProperties[i];
	deletedProperties.clear();
}

} //namespace Totem
