#pragma once

/**
 * @file
 * @class Totem::IPropertySerializer
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief Property Serializer Interface base class
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
 * Property Serializer Interface
 * RTTI implementation was originally contributed by 'zerotri'.
 * 
 */

#include <Totem/types_config.h>

namespace Totem {

class IProperty;
class IPropertyList;

class IPropertySerializer
{
public: 
	/**
	 * Destructor
	 */
	virtual ~IPropertySerializer() {}

	/**
	 * Serializes a property to text string
	 *
	 * @param property The property to serialize
	 * @return Returns serialized property
	 */
	virtual T_String toString(const IProperty *const property) = 0;

	/**
	 * Serializes a property list to text string
	 *
	 * @param propertyList The property list to serialize
	 * @return Returns serialized property list
	 */
	virtual T_String toString(IPropertyList *const propertyList) = 0;

	/**
	 * Deserializes a property from string
	 *
	 * @param property The property to hold the serialized value
	 * @param serialized_property The string to deserialize
	 */
	virtual void fromString(IProperty *const property, const T_String &serialized_property) = 0;

	/**
	 * Deserializes a property list from string
	 *
	 * @param propertyList The property list to hold the serialized value
	 * @param serialized_propertyList The string to deserialize
	 */
	virtual void fromString(IPropertyList *const propertyList, const T_String &serialized_propertyList) = 0;
};

} //namespace Totem
