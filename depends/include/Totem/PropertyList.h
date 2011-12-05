#pragma once

/**
 * @file
 * @class Totem::PropertyListData
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property List Data implementation class
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
 * PropertyListData
 * 
 */

#include <Totem/IPropertyList.h>
#include <Totem/IPropertySerializer.h>

namespace Totem {

template<class T>
class PropertyListData HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	/**
	 * Destructor
	 */
	~PropertyListData() {}
	/// Actual list data of the property list.
	typename T_Vector<T>::Type value;
	/// Name of the property list.
	T_String name;
	/// Is the property read-only?
	bool readOnly;
	/// Signal that's emitted when a value in the property list change, returning the index that was changed, plus the old and new value.
	typename T_Signal_v3<const U32&, const T&, const T&>::Type valueChanged;
	/// Signal that's emitted when a value is added to the property list, passing the new value with the signal along with the index.
	typename T_Signal_v2<const U32&, const T&>::Type valueAdded;
	/// Signal that's emitted when a value is erased from the property list, passing the erased value with the signal along with the index.
	typename T_Signal_v2<const U32&, const T&>::Type valueErased;
	/// Signal that's emitted when the values of the property list is cleared.
	typename T_Signal_v0<>::Type valuesCleared;
	/// Signal that's emitted when the size of the property list is resized to a given value
	typename T_Signal_v1<const U32&>::Type listResized;
};

/**
 * @file
 * @class Totem::PropertyListIndexValue
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property List Index Value, returned by list to allow changing an index in the list safely.
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
 * PropertyListIndexValue
 * 
 */

template<class T>
class PropertyListIndexValue
{
public:
	/**
	 * Constructor
	 */
	PropertyListIndexValue(typename T_SharedPtr< PropertyListData<T> >::Type data, const U32 &index)
		: data(data), index(index)
	{
	}
	
	/**
	 * Destructor
	 */
	~PropertyListIndexValue() {}

	/**
	 * Returns the real value of the PropertyListValue
	 *
	 * @return Returns the real value of the PropertyListValue.
	 */
	const T &get() const { return data->value[index]; }

	/// Set's property list value's data to rhs' shared pointer data.
	void set(const T& rhs);

	/// Set's property list value's data to rhs' shared pointer data.
	void operator= (const T& rhs);

	/// Provide an assignment operator to leviate level W4 warning
	PropertyListIndexValue<T> &operator= (const PropertyListIndexValue<T> &rhs);

	/// Instead of propertyListValue.get() this operator exist for convenience.
	operator const T &() const { return get(); }

private:
	/// PropertyListData of the Property list is stored inside a shared pointer.
	typename T_SharedPtr< PropertyListData<T> >::Type data;
	/// The index in the Property list's data value that this PropertyListIndexValueBool represent.
	const U32 &index;
};

template<class T>
inline void PropertyListIndexValue<T>::set(const T &rhs)
{
	T oldValue = data->value[index];
	data->value[index] = rhs;
	data->valueChanged.invoke(index, oldValue, data->value[index]);
}

template<class T>
inline void PropertyListIndexValue<T>::operator =(const T &rhs)
{
	set(rhs);
}

template<class T>
inline PropertyListIndexValue<T> &PropertyListIndexValue<T>::operator= (const PropertyListIndexValue<T> &rhs)
{
	if(this == &rhs)
		return *this;

	throw T_Exception("Assignment operation between property list index values are not supported!");
}

/**
 * @file
 * @class Totem::PropertyList
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property List implementation class
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
 * PropertyList
 * RTTI implementation was originally contributed by 'zerotri'.
 * 
 */

template<class T>
class PropertyList : public IPropertyList
{
public:
	/**
	 * Default Constructor, results in a PropertyList with no data!
	 */
	PropertyList()
	{
		type = getType<T>();
	}

	/**
	 * Copy Constructor
	 */
	PropertyList(const PropertyList& copy)
	: data(copy.data)
	{
		type = getType<T>();
	}

	/**
	 * Constructor
	 *
	 * @param name Name of the property list.
	 * @param readOnly Should the property list be read only? (Defaults to false).
	 */
	PropertyList(const T_String &name, bool readOnly = false)
	: data(new PropertyListData<T>())
	{	
		data->name = name;
		data->readOnly = readOnly;
		type = getType<T>();
	}

	/**
	 * Destructor
	 */
	virtual ~PropertyList() {}

	/**
	 * Push back a value to the property list. Handles pushing onto the actual PropertyData.value,
	 * plus invoke the valueAdded signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param value The new value to add to the property list.
	 * @param forced If this property list is read-only, setting this parameter to true will bypass the read-only rule.
	 * @param duplicationGuard Whether the PropertyList should make an effort to guard against duplicate entires, defaults to false.
	 */
	void push_back(const T& value, bool forced = false, bool duplicationGuard = false) 
	{ 
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		if(duplicationGuard)
		{
			for(U32 i = 0; i < data->value.size(); i++)
			{
				if(data->value[i] == value)
					return;
			}
		}

		data->value.push_back(value); 
		data->valueAdded.invoke((U32)data->value.size()-1, value);
	}

	/**
	 * Erase a value from the property list. Handles erasing from the actual PropertyData.value,
	 * plus invoke the valueErased signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param index The index to erase from the property list.
	 * @param forced If this property list is read-only, setting this parameter to true will bypass the read-only rule.
	 */
	void erase(const U32 &index, bool forced = false)
	{
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		if(index >= data->value.size())
			return;

		T value = data->value[index];
		data->value.erase(data->value.begin()+index);
		data->valueErased.invoke(index, value);
	}

	/**
	 * Clear all values from the property list. Handles clearing all values from the actual PropertyData.value,
	 * plus invoke the valuesCleared signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param forced If this property list is read-only, setting this parameter to true will bypass the read-only rule.
	 */
	void clear(bool forced = false)
	{
		if(data->readOnly && !forced)
			throw T_Exception(("PropertyList " + data->name + " is read-only!").c_str());

		data->value.clear();
		data->valuesCleared.invoke();
	}

	/**
	 * Get the number of values in the property list.
	 *
	 * @return Returns the number of values in the property list.
	 */
	U32 size() const { return (U32)data->value.size(); }

	/**
	 * Check if the property list is empty.
	 *
	 * @return Returns true if list is empty, false if it has values.
	 */
	bool empty() const { return data->value.empty(); }

	/**
	 * Resize the size of the list.
	 *
	 * @param size Sets the size of the list.
	 */
	void resize(const U32 &size) 
	{ 
		data->value.resize(size);
		data->listResized.invoke(size);
	}
	/**
	 * Resize the size of the list.
	 *
	 * @param size Sets the size of the list.
	 * @param value Fills list with this initial value
	 */
	void resize(const U32 &size, const T &value) 
	{ 
		data->value.resize(size, value);
		data->listResized.invoke(size);
	}

	/**
	 * Get the value of list at given index.
	 *
	 * @param index Index in the list for which value is returned
	 */
	PropertyListIndexValue<T> at(const U32 &index) 
	{ 
		if(index >= data->value.size())
			throw T_Exception(("Index was out of bounds for property list " + data->name).c_str());

		return PropertyListIndexValue<T>(this->data, index);
	}

	/**
	 * Returns the real list data of the PropertyListData value
	 *
	 * @return Returns the real list data of the PropertyListData value.
	 */
	const typename T_Vector<T>::Type &get() const { return data->value; }

	/**
	 * Get the interface of this property list.
	 * 
	 * @return Returns the property list interface of this property list.
	 */
	IPropertyList *getInterface() { return static_cast<IPropertyList*>(this); }

	/**
	 * Get the name of this property list.
	 * 
	 * @return Returns the name of this property list.
	 */
	virtual const T_String &getName() const { return data->name; }

	/**
	 * Check whether the PropertyListData is valid.
	 *
	 * @return Returns true if data does not exist, false if it does.
	 */
	virtual bool isNull() const { return data == NULL_PTR; }

	/**
	 * Call this function to serialize the value of the property list into a string.
	 * @param serializer The serializer to use for serialization.
	 * @return Returns the serialized string value of this property list.
	 */
	virtual T_String toString(IPropertySerializer &serializer) { return serializer.toString(this); }
	/**
	 * Call this function to deserialize a value from the string.
	 * @param serialized_propertyList The serialized string to deserialize.
	 * @param serializer The serializer to use for deserialization.
	 */
	virtual void fromString(const T_String &serialized_propertyList, IPropertySerializer &serializer) { serializer.fromString(this, serialized_propertyList); }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valueChanged signal. It's through this function call we can
	 * register slots to the valueChanged signal.
	 *
	 * @return Returns the valueChanged signal of this property list's PropertyListData.
	 */
	typename T_Signal_v3<const U32&, const T&, const T&>::Type &valueChanged() { return data->valueChanged; }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valueAdded signal. It's through this function call we can
	 * register slots to the valueAdded signal.
	 *
	 * @return Returns the valueAdded signal of this property list's PropertyListData.
	 */
	typename T_Signal_v2<const U32&, const T&>::Type &valueAdded() { return data->valueAdded; }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valueErased signal. It's through this function call we can
	 * register slots to the valueErased signal.
	 *
	 * @return Returns the valueErased signal of this property list's PropertyListData.
	 */
	typename T_Signal_v2<const U32&, const T&>::Type &valueErased() { return data->valueErased; }

	/**
	 * Function that gives the outside access to the PropertyListData's
	 * valuesCleared signal. It's through this function call we can
	 * register slots to the valuesCleared signal.
	 *
	 * @return Returns the valueCleared signal of this property list's PropertyListData.
	 */
	typename T_Signal_v0<>::Type &valuesCleared() { return data->valuesCleared; }

	/// Set's property list's data to rhs' shared pointer data.
	PropertyList<T> operator= (const PropertyList<T>& rhs);

	/// Get the value of list at given index.
	PropertyListIndexValue<T> operator[] (const U32& index);

	/// Instead of propertyList.get() this operator exist for convenience.
	operator const typename T_Vector<T>::Type &() const { return data->value; }

private:
	/// PropertyListData of the Property list is stored inside a shared pointer.
	typename T_SharedPtr< PropertyListData<T> >::Type data;
};

template<class T>
inline PropertyList<T> PropertyList<T>::operator =(const PropertyList<T> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class T>
inline PropertyListIndexValue<T> PropertyList<T>::operator [](const U32 &index)
{
	return at(index);
}

} //namespace Totem
