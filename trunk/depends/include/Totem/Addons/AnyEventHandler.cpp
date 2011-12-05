#include <Totem/Addons/AnyEventHandler.h>

using namespace Totem;
using namespace Addon;

bool AnyEventHandler::hasEvent(const T_HashedString &id, int num_params)
{
	if(num_params == 0)
	{
		T_Map<T_HashedStringType, typename T_Signal_v0<>::Type>::Type::iterator it = events0.find(id.getId());
		if(it != events0.end())
			return true;
		else
			return false;
	}
	else if(num_params == 1)
	{
		T_Map<T_HashedStringType, T_Signal_v1<T_Any>::Type>::Type::iterator it = events1.find(id.getId());
		if(it != events1.end())
			return true;
		else
			return false;
	}
	else if(num_params == 2)
	{
		T_Map<T_HashedStringType, T_Signal_v2<T_Any, T_Any>::Type>::Type::iterator it = events2.find(id.getId());
		if(it != events2.end())
			return true;
		else
			return false;
	}
	else if(num_params == 3)
	{
		T_Map<T_HashedStringType, T_Signal_v3<T_Any, T_Any, T_Any>::Type>::Type::iterator it = events3.find(id.getId());
		if(it != events3.end())
			return true;
		else
			return false;
	}
	else if(num_params == 4)
	{
		T_Map<T_HashedStringType, T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events4.find(id.getId());
		if(it != events4.end())
			return true;
		else
			return false;
	}
	else if(num_params == 5)
	{
		T_Map<T_HashedStringType, T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events5.find(id.getId());
		if(it != events5.end())
			return true;
		else
			return false;
	}
	else if(num_params == 6)
	{
		T_Map<T_HashedStringType, T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events6.find(id.getId());
		if(it != events6.end())
			return true;
		else
			return false;
	}
	else if(num_params == 7)
	{
		T_Map<T_HashedStringType, T_Signal_v7<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events7.find(id.getId());
		if(it != events7.end())
			return true;
		else
			return false;
	}
	else if(num_params == 8)
	{
		T_Map<T_HashedStringType, T_Signal_v8<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events8.find(id.getId());
		if(it != events8.end())
			return true;
		else
			return false;
	}
	else
	{
		{
		T_Map<T_HashedStringType, typename T_Signal_v0<>::Type>::Type::iterator it = events0.find(id.getId());
		if(it != events0.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v1<T_Any>::Type>::Type::iterator it = events1.find(id.getId());
		if(it != events1.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v2<T_Any, T_Any>::Type>::Type::iterator it = events2.find(id.getId());
		if(it != events2.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v3<T_Any, T_Any, T_Any>::Type>::Type::iterator it = events3.find(id.getId());
		if(it != events3.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events4.find(id.getId());
		if(it != events4.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events5.find(id.getId());
		if(it != events5.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events6.find(id.getId());
		if(it != events6.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v7<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events7.find(id.getId());
		if(it != events7.end())
			return true;
		}
		{
		T_Map<T_HashedStringType, T_Signal_v8<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events8.find(id.getId());
		if(it != events8.end())
			return true;
		}

		return false;
	}
}
