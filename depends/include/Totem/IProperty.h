#pragma once

/**
 * @file
 * @class Totem::IProperty
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property Interface base class
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
 * Property Interface
 * RTTI implementation was originally contributed by 'zerotri'.
 * 
 */

#include <Totem/types_config.h>

namespace Totem {

class IPropertySerializer;
class IProperty
{
public: 
	/**
	 * Destructor
	 */
	virtual ~IProperty() {}

	/**
	 * Get the name of this property.
	 *
	 * @return Returns the name of the property.
	 */
	virtual const T_String &getName() const = 0;

	/**
	 * Check if PropertyData exist in this Property.
	 *
	 * @return Returns whether the PropertyData of this property has been initialized.
	 */
	virtual bool isNull() const = 0;

	/**
	 * Get the PropertyTypeId associated with the PropertyType. This value is generated
	 * the first time each type of PropertyType is passed into the function, meaning that
	 * the value of the PropertyTypeId is dependent on the order PropertyTypes are passed
	 * into this function.
	 * @return Returns the PropertyTypeId associated with this PropertyType.
	 */
	template<typename PropertyType>
	static T_PropertyTypeId getType()
	{
		static T_PropertyTypeId typeId(newPropertyTypeId());
		return typeId;
	}

	/**
	 * Get the PropertyTypeId associated with this property instance. Compare the value
	 * with a call to the static function getTypeId<T>() to check which type this property
	 * interface is made of.
	 * @return Returns the PropertyTypeId associated with this property.
	 */
	const T_PropertyTypeId &getType() const { return type; }

	/**
	 * Call this function to serialize the value of the property into a string.
	 * @param serializer The serializer to use for serialization.
	 * @return Returns the serialized string value of this property.
	 */
	virtual T_String toString(IPropertySerializer &serializer) = 0;
	/**
	 * Call this function to deserialize a value from the string.
	 * @param serialized_property The serialized string to deserialize.
	 * @param serializer The serializer to use for deserialization.
	 */
	virtual void fromString(const T_String &serialized_property, IPropertySerializer &serializer) = 0;

protected:
	/// The type id associated with this specific property instance.
	T_PropertyTypeId type;
	
	/**
	 * Simply returns a new PropertyTypeId every time it's called. Called from
	 * the static getTypeId<T>() function.
	 * @return Returns a new PropertyTypeId.
	 */
	static T_PropertyTypeId newPropertyTypeId()
	{
		static T_PropertyTypeId next_id(0);
		return next_id++;
	}
};

} //namespace Totem
