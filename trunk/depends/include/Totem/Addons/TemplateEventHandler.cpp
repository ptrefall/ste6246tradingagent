#include <Totem/Addons/TemplateEventHandler.h>

using namespace Totem;
using namespace Addon;

bool TemplateEventHandler::hasEvent(const T_HashedString &id, int num_params)
{
	if(num_params == 0)
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events0.find(id.getId());
		if(it != events0.end())
			return true;
		else
			return false;
	}
	else if(num_params == 1)
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events1.find(id.getId());
		if(it != events1.end())
			return true;
		else
			return false;
	}
	else if(num_params == 2)
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events2.find(id.getId());
		if(it != events2.end())
			return true;
		else
			return false;
	}
	else if(num_params == 3)
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events3.find(id.getId());
		if(it != events3.end())
			return true;
		else
			return false;
	}
	else if(num_params == 4)
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events4.find(id.getId());
		if(it != events4.end())
			return true;
		else
			return false;
	}
	else if(num_params == 5)
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events5.find(id.getId());
		if(it != events5.end())
			return true;
		else
			return false;
	}
	else if(num_params == 6)
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events6.find(id.getId());
		if(it != events6.end())
			return true;
		else
			return false;
	}
	else
	{
		T_Map<T_HashedStringType, IEventSignal*>::Type::iterator it = events0.find(id.getId());
		if(it != events0.end())
			return true;
		it = events1.find(id.getId());
		if(it != events1.end())
			return true;
		it = events2.find(id.getId());
		if(it != events2.end())
			return true;
		it = events3.find(id.getId());
		if(it != events3.end())
			return true;
		it = events4.find(id.getId());
		if(it != events4.end())
			return true;
		it = events5.find(id.getId());
		if(it != events5.end())
			return true;
		it = events6.find(id.getId());
		if(it != events6.end())
			return true;

		return false;
	}
}
