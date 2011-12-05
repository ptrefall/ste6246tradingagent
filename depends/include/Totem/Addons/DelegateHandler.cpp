#include <Totem/Addons/DelegateHandler.h>

using namespace Totem;
using namespace Addon;

bool DelegateHandler::hasFunction(const T_HashedString &id, int num_params)
{
	if(num_params == 0)
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates0.find(id.getId());
		if(it != delegates0.end())
			return true;
		else
			return false;
	}
	else if(num_params == 1)
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates1.find(id.getId());
		if(it != delegates1.end())
			return true;
		else
			return false;
	}
	else if(num_params == 2)
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates2.find(id.getId());
		if(it != delegates2.end())
			return true;
		else
			return false;
	}
	else if(num_params == 3)
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates3.find(id.getId());
		if(it != delegates3.end())
			return true;
		else
			return false;
	}
	else if(num_params == 4)
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates4.find(id.getId());
		if(it != delegates4.end())
			return true;
		else
			return false;
	}
	else if(num_params == 5)
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates5.find(id.getId());
		if(it != delegates5.end())
			return true;
		else
			return false;
	}
	else if(num_params == 6)
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates6.find(id.getId());
		if(it != delegates6.end())
			return true;
		else
			return false;
	}
	else
	{
		T_Map<T_HashedStringType, IDelegate*>::Type::iterator it = delegates0.find(id.getId());
		if(it != delegates0.end())
			return true;
		it = delegates1.find(id.getId());
		if(it != delegates1.end())
			return true;
		it = delegates2.find(id.getId());
		if(it != delegates2.end())
			return true;
		it = delegates3.find(id.getId());
		if(it != delegates3.end())
			return true;
		it = delegates4.find(id.getId());
		if(it != delegates4.end())
			return true;
		it = delegates5.find(id.getId());
		if(it != delegates5.end())
			return true;
		it = delegates6.find(id.getId());
		if(it != delegates6.end())
			return true;

		return false;
	}
}
