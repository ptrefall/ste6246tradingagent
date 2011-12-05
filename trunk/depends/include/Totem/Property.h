#pragma once

/**
 * @file
 * @class Totem::PropertyData
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief PropertyData implementation class
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
 * PropertyData
 * 
 */

#include <Totem/IProperty.h>
#include <Totem/IPropertySerializer.h>

namespace Totem {

template<class T>
class PropertyData HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	/**
	 * Destructor
	 */
	~PropertyData() {}
	/// Actual data of the property.
	T value;
	/// Name of the property.
	T_String name;
	/// Is the property read-only?
	bool readOnly;
	/// Signal that's emitted when the value of the property change, returning the old and new value.
	typename T_Signal_v2<const T&, const T&>::Type valueChanged;
};

/**
 * @file
 * @class Totem::Property
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property implementation class
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
 * Property
 * RTTI implementation was originally contributed by 'zerotri'.
 * 
 */

template<class T>
class Property : public IProperty
{
public:
	/**
	 * Default Constructor, results in a Property with no data!
	 */
	Property()
	{
		type = getType<T>(); //RTTI id
	}

	/**
	 * Copy Constructor, points to same data via smart pointer
	 */
	Property(const Property& copy)
	: data(copy.data)
	{
		type = getType<T>(); //RTTI id
	}

	/**
	 * Constructor
	 *
	 * @param name Name of the property.
	 * @param readOnly Should the property be read only? (Defaults to false).
	 */
	Property(const T_String &name, bool readOnly = false)
	: data(new PropertyData<T>())
	{	
		data->name = name;
		data->readOnly = readOnly;
		type = getType<T>(); //RTTI id
	}

	/**
	 * Destructor
	 */
	virtual ~Property() {}

	/**
	 * Set the value of the property. Handles setting the actual PropertyData.value,
	 * plus invoke the valueChanged signal. This also enforces the readOnly flag, which
	 * can only be bypassed by passing in forced = true.
	 *
	 * @param value The new value of the property.
	 * @param forced If this property is read-only, setting this parameter to true will bypass the read-only rule.
	 */
	void set(const T& value, bool forced = false, bool invoke = true) 
	{ 
		if(data->readOnly && !forced)
			throw T_Exception(("Property " + data->name + " is read-only!").c_str());

		if(data->value != value)
		{
			T oldValue = data->value;
			data->value = value; 

			if(invoke)
				data->valueChanged.invoke(oldValue, value);
		}
	}

	/**
	 * Returns the real data of the PropertyData value
	 *
	 * @return Returns the real data of the PropertyData value.
	 */
	const T& get() const { return data->value; }

	/**
	 * Get the interface of this property.
	 * 
	 * @return Returns the property interface of this property.
	 */
	IProperty *getInterface() { return static_cast<IProperty*>(this); }

	/**
	 * Get the name of this property.
	 * 
	 * @return Returns the name of this property.
	 */
	virtual const T_String &getName() const { return data->name; }

	/**
	 * Check whether the PropertyData is valid.
	 *
	 * @return Returns true if data does not exist, false if it does.
	 */
	virtual bool isNull() const { return data == NULL_PTR; }

	/**
	 * Call this function to serialize the value of the property into a string.
	 * @param serializer The serializer to use for serialization.
	 * @return Returns the serialized string value of this property.
	 */
	virtual T_String toString(IPropertySerializer &serializer) { return serializer.toString(this); }
	/**
	 * Call this function to deserialize a value from the string.
	 * @param serialized_property The serialized string to deserialize.
	 * @param serializer The serializer to use for deserialization.
	 */
	virtual void fromString(const T_String &serialized_property, IPropertySerializer &serializer) { serializer.fromString(this, serialized_property); }

	/**
	 * Function that gives the outside access to the PropertyData's
	 * valueChanged signal. It's through this function call we can
	 * register slots to the valueChanged signal.
	 *
	 * @return Returns the valueChanged signal of this property's PropertyData.
	 */
	typename T_Signal_v2<const T&, const T&>::Type &valueChanged() { return data->valueChanged; }

	/// Set's property's data to rhs' shared pointer data.
	Property<T> operator= (const Property<T>& rhs);
	/// Set's property's data to rhs' value.
	Property<T> operator= (const T& rhs);

	/// Adds rhs' data value to property's data value
	Property<T> operator+= (const Property<T>& rhs);
	/// Adds rhs' value to property's data value
	Property<T> operator+= (const T& rhs);

	/// Subtracts rhs' data value from property's data value
	Property<T> operator-= (const Property<T>& rhs);
	/// Subtracts rhs' value from property's data value
	Property<T> operator-= (const T& rhs);

	/// Multiplies rhs' data value with property's data value
	Property<T> operator*= (const Property<T>& rhs);
	/// Multiplies rhs' value with property's data value
	Property<T> operator*= (const T& rhs);

	/// Check whether the shared pointer data of rhs is same as property's
	bool operator== (const Property<T>& rhs);
	/// Check whether the value of rhs equals that of property's data value
	bool operator== (const T& rhs);

	/// Check whether the shared pointer data of rhs is not the same as property's
	bool operator!= (const Property<T>& rhs);
	/// Check whether the value of rhs is not equals that of property's data value
	bool operator!= (const T& rhs);

	/// Check whether the data value of rhs is less than property's data value
	bool operator> (const Property<T>& rhs);
	/// Check whether the value of rhs is less than property's data value
	bool operator> (const T& rhs);

	/// Check whether the data value of rhs is greater than property's data value
	bool operator< (const Property<T>& rhs);
	/// Check whether the value of rhs is greater than property's data value
	bool operator< (const T& rhs);

	/// Instead of property.get() this operator exist for convenience.
	operator const T &() const { return data->value; }

private:
	/// PropertyData of the Property is stored inside a shared pointer.
	typename T_SharedPtr< PropertyData<T> >::Type data;
};

template<class T>
inline Property<T> Property<T>::operator =(const Property<T> &rhs)
{
	data = rhs.data;
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator =(const T &rhs)
{
	set(rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator +=(const Property<T> &rhs)
{
	set(data->value + rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator +=(const T &rhs)
{
	set(data->value + rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator -=(const Property<T> &rhs)
{
	set(data->value - rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator -=(const T &rhs)
{
	set(data->value - rhs);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator *=(const Property<T> &rhs)
{
	set(data->value * rhs.data->value);
	return *this;
}

template<class T>
inline Property<T> Property<T>::operator *=(const T &rhs)
{
	set(data->value * rhs);
	return *this;
}

template<class T>
inline bool Property<T>::operator ==(const Property<T> &rhs)
{
	return data == rhs.data;
}

template<class T>
inline bool Property<T>::operator ==(const T &rhs)
{
	return (data->value == rhs);
}

template<class T>
inline bool Property<T>::operator !=(const Property<T> &rhs)
{
	return data != rhs.data;
}

template<class T>
inline bool Property<T>::operator !=(const T &rhs)
{
	return (data->value != rhs);
}

template<class T>
inline bool Property<T>::operator >(const Property<T> &rhs)
{
	return (data->value > rhs.data->value);
}

template<class T>
inline bool Property<T>::operator >(const T &rhs)
{
	return (data->value > rhs);
}

template<class T>
inline bool Property<T>::operator <(const Property<T> &rhs)
{
	return (data->value < rhs.data->value);
}

template<class T>
inline bool Property<T>::operator <(const T &rhs)
{
	return (data->value < rhs);
}

} //namespace Totem
