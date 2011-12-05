/*Totem EDK
Copyright (c) 2009 Pål Trefall and Kenneth Gangstø

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Note: Some of the libraries Totem EDK may link to may have additional
requirements or restrictions.
*/

#include <Totem/types_config.h>
#include <Totem/ComponentFactory.h>
#include <Totem/Component.h>

using namespace Totem;

ComponentFactory::ComponentFactory()
: creators(NULL_PTR), creators_custom1(NULL_PTR), creators_custom2(NULL_PTR), creators_custom3(NULL_PTR), creators_custom4(NULL_PTR), 
					  creators_custom5(NULL_PTR), creators_custom6(NULL_PTR)
{
}

ComponentFactory::~ComponentFactory()
{
	if(creators)
	{
		creators->clear();
		delete creators;
	}
	if(creators_custom1)
	{
		creators_custom1->clear();
		delete creators_custom1;
	}
	if(creators_custom2)
	{
		creators_custom2->clear();
		delete creators_custom2;
	}
	if(creators_custom3)
	{
		creators_custom3->clear();
		delete creators_custom3;
	}
	if(creators_custom4)
	{
		creators_custom4->clear();
		delete creators_custom4;
	}
	if(creators_custom5)
	{
		creators_custom5->clear();
		delete creators_custom5;
	}
	if(creators_custom6)
	{
		creators_custom6->clear();
		delete creators_custom6;
	}
}

//-----------------------------------------------------------------------------

void ComponentFactory::registerComponent(const T_String& type, ComponentCreator functor)
{
	if(creators == NULL_PTR)
		creators = new T_Map<T_String, ComponentCreator>::Type();

	if(creators->find(type) == creators->end())
	{
		T_Pair<T_String, ComponentCreator>::Type value(type, functor);
		creators->insert(value);
	}
}

void ComponentFactory::registerComponentCustom1(const T_String& type, ComponentCreator1 functor)
{
	if(creators_custom1 == NULL_PTR)
		creators_custom1 = new T_Map<T_String, ComponentCreator1>::Type();

	if(creators_custom1->find(type) == creators_custom1->end())
	{
		T_Pair<T_String, ComponentCreator1>::Type value(type, functor);
		creators_custom1->insert(value);
	}
}

void ComponentFactory::registerComponentCustom2(const T_String& type, ComponentCreator2 functor)
{
	if(creators_custom2 == NULL_PTR)
		creators_custom2 = new T_Map<T_String, ComponentCreator2>::Type();

	if(creators_custom2->find(type) == creators_custom2->end())
	{
		T_Pair<T_String, ComponentCreator2>::Type value(type, functor);
		creators_custom2->insert(value);
	}
}

void ComponentFactory::registerComponentCustom3(const T_String& type, ComponentCreator3 functor)
{
	if(creators_custom3 == NULL_PTR)
		creators_custom3 = new T_Map<T_String, ComponentCreator3>::Type();

	if(creators_custom3->find(type) == creators_custom3->end())
	{
		T_Pair<T_String, ComponentCreator3>::Type value(type, functor);
		creators_custom3->insert(value);
	}
}

void ComponentFactory::registerComponentCustom4(const T_String& type, ComponentCreator4 functor)
{
	if(creators_custom4 == NULL_PTR)
		creators_custom4 = new T_Map<T_String, ComponentCreator4>::Type();

	if(creators_custom4->find(type) == creators_custom4->end())
	{
		T_Pair<T_String, ComponentCreator4>::Type value(type, functor);
		creators_custom4->insert(value);
	}
}

void ComponentFactory::registerComponentCustom5(const T_String& type, ComponentCreator5 functor)
{
	if(creators_custom5 == NULL_PTR)
		creators_custom5 = new T_Map<T_String, ComponentCreator5>::Type();

	if(creators_custom5->find(type) == creators_custom5->end())
	{
		T_Pair<T_String, ComponentCreator5>::Type value(type, functor);
		creators_custom5->insert(value);
	}
}

void ComponentFactory::registerComponentCustom6(const T_String& type, ComponentCreator6 functor)
{
	if(creators_custom6 == NULL_PTR)
		creators_custom6 = new T_Map<T_String, ComponentCreator6>::Type();

	if(creators_custom6->find(type) == creators_custom6->end())
	{
		T_Pair<T_String, ComponentCreator6>::Type value(type, functor);
		creators_custom6->insert(value);
	}
}

//-----------------------------------------------------------------------------

Component* ComponentFactory::createComponent(T_Any &owner, const T_String &type)
{
	if(creators == NULL_PTR)
		throw T_Exception(("Unable to create component " + type).c_str());

	T_Map<T_String, ComponentCreator>::Type::iterator creatorIt = creators->find(type);
	if(creatorIt == creators->end())
		throw T_Exception(("Unable to create component " + type + ", make sure type specified is correct, and that the number of custom parameters are identical to those at registration!").c_str());
	
	ComponentCreator creator = creatorIt->second;
	return creator(owner, type);
}

Component* ComponentFactory::createComponentCustom1(T_Any &owner, const T_String &type, T_Any &custom1)
{
	if(creators_custom1 == NULL_PTR)
		throw T_Exception(("Unable to create component " + type).c_str());

	T_Map<T_String, ComponentCreator1>::Type::iterator creatorIt = creators_custom1->find(type);
	if(creatorIt == creators_custom1->end())
		throw T_Exception(("Unable to create component " + type + ", make sure type specified is correct, and that the number of custom parameters are identical to those at registration!").c_str());
	
	ComponentCreator1 creator = creatorIt->second;
	return creator(owner, type, custom1);
}

Component* ComponentFactory::createComponentCustom2(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2)
{
	if(creators_custom2 == NULL_PTR)
		throw T_Exception(("Unable to create component " + type).c_str());

	T_Map<T_String, ComponentCreator2>::Type::iterator creatorIt = creators_custom2->find(type);
	if(creatorIt == creators_custom2->end())
		throw T_Exception(("Unable to create component " + type + ", make sure type specified is correct, and that the number of custom parameters are identical to those at registration!").c_str());
	
	ComponentCreator2 creator = creatorIt->second;
	return creator(owner, type, custom1, custom2);
}

Component* ComponentFactory::createComponentCustom3(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3)
{
	if(creators_custom3 == NULL_PTR)
		throw T_Exception(("Unable to create component " + type).c_str());

	T_Map<T_String, ComponentCreator3>::Type::iterator creatorIt = creators_custom3->find(type);
	if(creatorIt == creators_custom3->end())
		throw T_Exception(("Unable to create component " + type + ", make sure type specified is correct, and that the number of custom parameters are identical to those at registration!").c_str());
	
	ComponentCreator3 creator = creatorIt->second;
	return creator(owner, type, custom1, custom2, custom3);
}

Component* ComponentFactory::createComponentCustom4(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4)
{
	if(creators_custom4 == NULL_PTR)
		throw T_Exception(("Unable to create component " + type).c_str());

	T_Map<T_String, ComponentCreator4>::Type::iterator creatorIt = creators_custom4->find(type);
	if(creatorIt == creators_custom4->end())
		throw T_Exception(("Unable to create component " + type + ", make sure type specified is correct, and that the number of custom parameters are identical to those at registration!").c_str());
	
	ComponentCreator4 creator = creatorIt->second;
	return creator(owner, type, custom1, custom2, custom3, custom4);
}

Component* ComponentFactory::createComponentCustom5(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5)
{
	if(creators_custom5 == NULL_PTR)
		throw T_Exception(("Unable to create component " + type).c_str());

	T_Map<T_String, ComponentCreator5>::Type::iterator creatorIt = creators_custom5->find(type);
	if(creatorIt == creators_custom5->end())
		throw T_Exception(("Unable to create component " + type + ", make sure type specified is correct, and that the number of custom parameters are identical to those at registration!").c_str());
	
	ComponentCreator5 creator = creatorIt->second;
	return creator(owner, type, custom1, custom2, custom3, custom4, custom5);
}

Component* ComponentFactory::createComponentCustom6(T_Any &owner, const T_String &type, T_Any &custom1, T_Any &custom2, T_Any &custom3, T_Any &custom4, T_Any &custom5, T_Any &custom6)
{
	if(creators_custom6 == NULL_PTR)
		throw T_Exception(("Unable to create component " + type).c_str());

	T_Map<T_String, ComponentCreator6>::Type::iterator creatorIt = creators_custom6->find(type);
	if(creatorIt == creators_custom6->end())
		throw T_Exception(("Unable to create component " + type + ", make sure type specified is correct, and that the number of custom parameters are identical to those at registration!").c_str());
	
	ComponentCreator6 creator = creatorIt->second;
	return creator(owner, type, custom1, custom2, custom3, custom4, custom5, custom6);
}
