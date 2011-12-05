#pragma once

/**
 * @file
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
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
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 * Note: Some of the libraries Totem EDK may link to may have additional
 * requirements or restrictions.
 * 
 * @section DESCRIPTION
 * Minimal Dependency Types Configuration
 * 
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <memory>
#include <functional>
#include "sigslot.h"
#include "cdiggins_any.h"
#include "FastDelegate.h"
#include "FastDelegateBind.h"

//Sigslot.h requires that PropertyData and Component inherit from
//sigslot::has_slots<>, thus "overload" this preprocessed definition.
//-------------------------------------------------------------------
#undef HAS_SIGNALSLOTS_INHERITANCE_TYPE
#define HAS_SIGNALSLOTS_INHERITANCE_TYPE : public sigslot::has_slots<sigslot::single_threaded>

//--------------------------------------------

//Base types
//#undef NULL_PTR
//#define NULL_PTR nullptr
typedef std::string T_String;
typedef double D32;
typedef float F32;
typedef int S32;
typedef unsigned int U32;
typedef unsigned long T_EntityId;
typedef cdiggins::any T_Any;
typedef cdiggins::anyimpl::bad_any_cast T_BadAnyCast;

//--------------------------------------------

//Container types
template< typename T >
struct T_Vector {
	typedef std::vector<T> Type;
};
template< typename K, typename V >
struct T_Map {
	typedef std::unordered_map<K,V> Type;
};
template< typename K, typename V >
struct T_Pair {
	typedef std::pair<K,V> Type;
};

//--------------------------------------------

//Exception handling
typedef std::runtime_error T_Exception;

//--------------------------------------------

//Signal handling
class NoTemplate {};
template<class T = NoTemplate>
struct T_Signal_v0 {
	typedef sigslot::signal0<sigslot::single_threaded> Type;
};

template< typename T >
struct T_Signal_v1 {
	typedef sigslot::signal1<T,sigslot::single_threaded> Type;
};

template<typename T,typename U>
struct T_Signal_v2 {
   typedef sigslot::signal2<T,U,sigslot::single_threaded> Type;
};

template<typename T,typename U, typename V>
struct T_Signal_v3 {
   typedef sigslot::signal3<T,U,V,sigslot::single_threaded> Type;
};

template<typename T,typename U, typename V, typename W>
struct T_Signal_v4 {
   typedef sigslot::signal4<T,U,V,W,sigslot::single_threaded> Type;
};

template<typename T,typename U, typename V, typename W, typename X>
struct T_Signal_v5 {
   typedef sigslot::signal5<T,U,V,W,X,sigslot::single_threaded> Type;
};

template<typename T,typename U, typename V, typename W, typename X, typename Y>
struct T_Signal_v6 {
   typedef sigslot::signal6<T,U,V,W,X,Y,sigslot::single_threaded> Type;
};

//--------------------------------------------

//Delegate handling
typedef const void *T_Void;

template<class RetType=T_Void>
struct T_Delegate_v0 {
	typedef fastdelegate::FastDelegate0<RetType> Type;
};

template<class Param1, class RetType=T_Void>
struct T_Delegate_v1 {
	typedef fastdelegate::FastDelegate1<Param1, RetType> Type;
};

template<class Param1, class Param2, class RetType=T_Void>
struct T_Delegate_v2 {
	typedef fastdelegate::FastDelegate2<Param1, Param2, RetType> Type;
};

template<class Param1, class Param2, class Param3, class RetType=T_Void>
struct T_Delegate_v3 {
	typedef fastdelegate::FastDelegate3<Param1, Param2, Param3, RetType> Type;
};

template<class Param1, class Param2, class Param3, class Param4, class RetType=T_Void>
struct T_Delegate_v4 {
	typedef fastdelegate::FastDelegate4<Param1, Param2, Param3, Param4, RetType> Type;
};

template<class Param1, class Param2, class Param3, class Param4, class Param5, class RetType=T_Void>
struct T_Delegate_v5 {
	typedef fastdelegate::FastDelegate5<Param1, Param2, Param3, Param4, Param5, RetType> Type;
};

template<class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class RetType=T_Void>
struct T_Delegate_v6 {
	typedef fastdelegate::FastDelegate6<Param1, Param2, Param3, Param4, Param5, Param6, RetType> Type;
};

//--------------------------------------------

template < typename T >
struct T_SharedPtr {
	typedef std::shared_ptr<T> Type;
};

//--------------------------------------------

typedef unsigned int T_HashedStringType;
//typedef T_String T_HashedStringType;

class T_HashedString
{
public:
	T_HashedString(const T_String &str)
		: hashId(0), str(T_String())
	{
		this->str = str;
		this->hashId = std::hash<T_String>()(str);
	}

	~T_HashedString()
	{
		str = T_String();
		hashId = 0;
	}

	const T_HashedStringType &getId() const { return hashId; }
	const T_String &getStr() const { return str; }

private:
	T_HashedStringType hashId;
	T_String str;
};

//--------------------------------------------

typedef unsigned int T_PropertyTypeId;
