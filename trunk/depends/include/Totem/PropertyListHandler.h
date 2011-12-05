#pragma once

/**
 * @file
 * @class Totem::PropertyListHandler
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief PropertyListHandler base class
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
 * The PropertyListHandler holds the means of containing and managing property lists.
 * 
 */

#include <Totem/PropertyList.h>

namespace Totem {

template<class UserData = void*>
class PropertyListHandler
{
public:
	/**
	 * Constructor
	 *
	 */
	PropertyListHandler() {}

	/**
	 * Destructor
	 */
	virtual ~PropertyListHandler()
	{
		removeAllPropertyLists();
	}

	//--------------------------------------------------------------

	/**
	 * Check whether the specified property list name exist in this PropertyListHandler.
	 * This function works on the interface (IPropertyList) of the property list,
	 * thus no type-casting is involved in it's usage.
	 *
	 * @param name The name of the property list.
	 * @return Returns true if the property list exist in this PropertyListHandler, false if it doesn't.
	 */
	bool hasPropertyList(const T_String& name);

	/**
	 * Add a property list of specified type T and name to this PropertyListHandler.
	 * If readOnly is specified to true, one can only change the property list by
	 * directly calling propertyList.push_back(value, forced=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property list used to store and associate the property list in the PropertyListHandler.
	 * @param readOnly Flag this property list as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property list that was added to the PropertyListHandler.
	 */
	template<class T>PropertyList<T> addPropertyList(const T_String& name, bool readOnly = false)
	{
		T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
		if(it != propertyLists.end())
		{
			PropertyList<T>* propertyList;
	#ifdef _DEBUG
			propertyList = dynamic_cast< PropertyList<T>* >(it->second);
			if(!propertyList)
				throw T_Exception(("PropertyList " + name + " already exists, but with another type!").c_str());
	#else
			propertyList = static_cast< PropertyList<T>* >(it->second);
	#endif
			return *propertyList;
		}

		PropertyList<T> *propertyList = new PropertyList<T>(name, readOnly);
		propertyLists[propertyList->getName()] = propertyList;

		//return *propertyList;
		return getPropertyList<T>(name);
	}

	/**
	 * Add a property list of specified type T and name to this PropertyListHandler.
	 * If readOnly is specified to true, one can only change the property list by
	 * directly calling propertyList.push_back(value, forced=true), all other pipes, like
	 * via operators, will throw an exception.
	 *
	 * @param name The name of the property list used to store and associate the property list in the PropertyListHandler.
	 * @param userData The userdata is of type specified for the PropertyListHandler's class template, and provides optional userdata description of the propertyList.
	 * @param readOnly Flag this property list as read-only if it should only be read. Defaults to false.
	 * @return Returns a shared_ptr (pimpl) reference to the property list that was added to the PropertyListHandler.
	 */
	template<class T>PropertyList<T> addPropertyList(const T_String& name, const UserData &userData, bool readOnly = false)
	{
		T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
		if(it != propertyLists.end())
		{
			PropertyList<T>* propertyList;
	#ifdef _DEBUG
			propertyList = dynamic_cast< PropertyList<T>* >(it->second);
			if(!propertyList)
				throw T_Exception(("PropertyList " + name + " already exists, but with another type!").c_str());
	#else
			propertyList = static_cast< PropertyList<T>* >(it->second);
	#endif
			return *propertyList;
		}

		PropertyList<T> *propertyList = new PropertyList<T>(name, readOnly);
		propertyLists[propertyList->getName()] = propertyList;

		//return *propertyList;
		return getPropertyList<T>(name);
	}

	/**
	 * Add a property list interface to this PropertyListHandler.
	 * There can be situations where this is required.
	 *
	 * @param propertyList The interface of the property list.
	 */
	void addPropertyList(IPropertyList *propertyList);

	/**
	 * Get a shared_ptr (pimpl) reference to a property list of specified name from the PropertyListHandler.
	 *
	 * @param name The name of the property list.
	 * @return Returns a shared_ptr (pimpl) reference to the property list.
	 */
	template<class T>PropertyList<T> getPropertyList(const T_String& name)
	{
		T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
		if(it != propertyLists.end())
		{
			PropertyList<T>* propertyList;
	#ifdef _DEBUG
			propertyList = dynamic_cast< PropertyList<T>* >(it->second);
			if(!propertyList)
				throw T_Exception(("Tried to get property list " + name + ", but the type was wrong!").c_str());
	#else
			propertyList = static_cast< PropertyList<T>* >(it->second);
	#endif
			return *propertyList;
		}
		else
			throw T_Exception(("Unable to get property list " + name).c_str());
	}

	/**
	 * Get a property list interface pointer to a property list of specified name from the PropertyListHandler.
	 *
	 * @param name  The name of the property list.
	 * @return The interface pointer to the property list.
	 */
	IPropertyList *getIPropertyList(const T_String& name);

	/**
	 * Remove the property list of specified name from PropertyListHandler with
	 * option to postpone deletion until the next time update
	 * is called on the PropertyListHandler.
	 *
	 * @param name The name of the property list.
	 * @param postponeDelete Flag whether to postpone the deletion of this property list (if true), or delete it immediately (if false). Defaults to false.
	 */
	void removePropertyList(const T_String& name, bool postponeDelete = false);

	/**
	 * Remove all property lists from PropertyListHandler.
	 *
	 */
	void removeAllPropertyLists();

	/**
	 * Delete all property lists that was deleted last time update was called
	 * and marked postponeDelete.
	 *
	 */
	void clearDeletedPropertyLists();

	/**
	 * Get a reference to the entire map of property lists owned by the PropertyListHandler.
	 *
	 * @return Returns a reference to the PropertyListHandler's property list map.
	 */
	T_Map<T_String, IPropertyList*>::Type &getPropertyLists() { return propertyLists; }
	
	//--------------------------------------------------------------

	/**
	 * Handles deletion of all property lists pending for deletion in this PropertyListHandler.
	 *
	 */
	void updatePropertyLists();

	//--------------------------------------------------------------

	/// Provide an assignment operator to leviate level W4 warning
	PropertyListHandler &operator= (const PropertyListHandler &rhs)
	{
		if(this == &rhs)
			return *this;

		throw T_Exception("Assignment operation between PropertyListHandler are not supported!");
	}

protected:
	/// The map of all property lists owned by this PropertyListHandler.
	T_Map<T_String, IPropertyList*>::Type propertyLists;
	/// The list of all property lists pending deletion in this PropertyListHandler.
	T_Vector<IPropertyList*>::Type deletedPropertyLists;
};

//------------------------------------------------------

template<class UserData>
inline bool PropertyListHandler<UserData>::hasPropertyList(const T_String& name)
{
	if(propertyLists.empty())
		return false;

	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
	if(it != propertyLists.end())
		return true;
	else
		return false;
}

template<class UserData>
inline void PropertyListHandler<UserData>::addPropertyList(IPropertyList *propertyList)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(propertyList->getName());
	if(it == propertyLists.end())
		propertyLists[propertyList->getName()] = propertyList;
}

template<class UserData>
inline IPropertyList *PropertyListHandler<UserData>::getIPropertyList(const T_String& name)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
	if(it != propertyLists.end())
		return it->second;
	else
		throw T_Exception(("Unable to get property list " + name).c_str());
}

template<class UserData>
inline void PropertyListHandler<UserData>::removePropertyList(const T_String& name, bool postponeDelete)
{
	T_Map<T_String, IPropertyList*>::Type::iterator it = propertyLists.find(name);
	if(it != propertyLists.end())
	{
		IPropertyList* propertyList = (*it).second;
		if(postponeDelete)
			deletedPropertyLists.push_back(propertyList);
		else
			delete propertyList;
		propertyLists.erase(it);
	}
}

template<class UserData>
inline void PropertyListHandler<UserData>::removeAllPropertyLists()
{
	T_Map<T_String, IPropertyList*>::Type::iterator it;
	for(it = propertyLists.begin(); it != propertyLists.end(); ++it)
	{
		IPropertyList* propertyList = (*it).second;
		delete propertyList;
	}
	propertyLists.clear();
	clearDeletedPropertyLists();
}

template<class UserData>
inline void PropertyListHandler<UserData>::updatePropertyLists()
{
	clearDeletedPropertyLists();
}

template<class UserData>
inline void PropertyListHandler<UserData>::clearDeletedPropertyLists()
{
	for(unsigned int i = 0; i < deletedPropertyLists.size(); i++)
		delete deletedPropertyLists[i];
	deletedPropertyLists.clear();
}

} //namespace Totem