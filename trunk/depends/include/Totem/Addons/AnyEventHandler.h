#pragma once

/**
 * @file
 * @class Totem::Addon::AnyEventHandler
 *
 * @author Pål Trefall
 * @author Kenneth Gangstø
 *
 * @version 2.0
 *
 * @brief AnyEventHandler base class using Any
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
 * The event handler using Any.
 * 
 */

#include <Totem/types_config.h>
#include <Totem/Property.h>

namespace Totem {
namespace Addon {

class Component;
class ComponentFactory;
class AnyEventHandler HAS_SIGNALSLOTS_INHERITANCE_TYPE
{
public:
	/**
	 * Constructor
	 */
	AnyEventHandler() {}
	/**
	 * Destructor
	 */
	virtual ~AnyEventHandler() 
	{
		for(U32 i = 0; i < scheduledEvents.size(); i++)
			delete scheduledEvents[i];
	}

	//--------------------------------------------------------------

	/**
	 * Calls all slots registered to the argument-less event signal of type.
	 *
	 * @param type The hashed type string id of the event.
	 */
	void sendEvent(const T_HashedString &type);

	/**
	 * Calls all slots registered to the event signal of type holding one argument.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 */
	void sendEvent(const T_HashedString &type, T_Any arg0);

	/**
	 * Calls all slots registered to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 */
	void sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1);

	/**
	 * Calls all slots registered to the event signal of type holding three arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 */
	void sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2);

	/**
	 * Calls all slots registered to the event signal of type holding four arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 */
	void sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3);

	/**
	 * Calls all slots registered to the event signal of type holding five arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 * @param arg4 Fifth argument of type X.
	 */
	void sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4);

	/**
	 * Calls all slots registered to the event signal of type holding six arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T.
	 * @param arg1 Second argument of type U.
	 * @param arg2 Third argument of type V.
	 * @param arg3 Fourth argument of type W.
	 * @param arg4 Fifth argument of type X.
	 * @param arg5 Sixth argument of type Y.
	 */
	void sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4, T_Any arg5);

	//--------------------------------------------------------------

	/**
	 * Call update function on all the scheduled events pending in this EventHandler.
	 *
	 * @param deltaTime  Should be the time elapsed since update was called last time.
	 */
	void updateScheduledEvents(const F32 &deltaTime);

	/**
	 * Schedule an event that after X seconds will call all slots 
	 * registered to the argument-less event signal of type.
	 *
	 * @param type The hashed type string id of the event.
	 * @param time The time in seconds this event should be delayed by
	 */
	void scheduleEvent(const T_HashedString &type, const F32 &time);

	/**
	 * Schedule an event that after X seconds will call all slots 
	 * registered to the event signal of type holding one argument.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T_Any.
	 * @param time The time in seconds this event should be delayed by
	 */
	void scheduleEvent(const T_HashedString &type, T_Any arg0, const F32 &time);

	/**
	 * Schedule an event that after X seconds will call all slots 
	 * registered to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T_Any.
	 * @param arg1 Second argument of type T_Any.
	 * @param time The time in seconds this event should be delayed by
	 */
	void scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, const F32 &time);

	/**
	 * Schedule an event that after X seconds will call all slots 
	 * registered to the event signal of type holding three arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T_Any.
	 * @param arg1 Second argument of type T_Any.
	 * @param arg2 Third argument of type T_Any.
	 * @param time The time in seconds this event should be delayed by
	 */
	void scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, const F32 &time);

	/**
	 * Schedule an event that after X seconds will call all slots 
	 * registered to the event signal of type holding four arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T_Any.
	 * @param arg1 Second argument of type T_Any.
	 * @param arg2 Third argument of type T_Any.
	 * @param arg3 Fourth argument of type T_Any.
	 * @param time The time in seconds this event should be delayed by
	 */
	void scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, const F32 &time);

	/**
	 * Schedule an event that after X seconds will call all slots 
	 * registered to the event signal of type holding five arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T_Any.
	 * @param arg1 Second argument of type T_Any.
	 * @param arg2 Third argument of type T_Any.
	 * @param arg3 Fourth argument of type T_Any.
	 * @param arg4 Fifth argument of type T_Any.
	 * @param time The time in seconds this event should be delayed by
	 */
	void scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4, const F32 &time);

	/**
	 * Schedule an event that after X seconds will call all slots 
	 * registered to the event signal of type holding six arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @param arg0 First argument of type T_Any.
	 * @param arg1 Second argument of type T_Any.
	 * @param arg2 Third argument of type T_Any.
	 * @param arg3 Fourth argument of type T_Any.
	 * @param arg4 Fifth argument of type T_Any.
	 * @param arg5 Sixth argument of type T_Any.
	 * @param time The time in seconds this event should be delayed by
	 */
	void scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4, T_Any arg5, const F32 &time);

	//--------------------------------------------------------------

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires no arguments in the slot.
	 */
	T_Signal_v0<>::Type &registerToEvent0(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding one argument.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires one arguments in the slot.
	 */
	T_Signal_v1<T_Any>::Type &registerToEvent1(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding two arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires two arguments in the slot.
	 */
	T_Signal_v2<T_Any, T_Any>::Type &registerToEvent2(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding three arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires three arguments in the slot.
	 */
	T_Signal_v3<T_Any, T_Any, T_Any>::Type &registerToEvent3(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding four arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires four arguments in the slot.
	 */
	T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type &registerToEvent4(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding five arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires five arguments in the slot.
	 */
	T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type &registerToEvent5(const T_HashedString &type);

	/**
	 * Register a slot to the event signal of type holding six arguments.
	 *
	 * @param type The hashed type string id of the event.
	 * @return A signal that requires six arguments in the slot.
	 */
	T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type &registerToEvent6(const T_HashedString &type);

	//--------------------------------------------------------------

	bool hasEvent(const T_HashedString &id, int num_params = -1);

protected:
	/// Map of argument-less event signals held by EventHandler.
	T_Map<T_HashedStringType, typename T_Signal_v0<>::Type>::Type events0;
	/// Map of event signals with one argument held by EventHandler.
	T_Map<T_HashedStringType, T_Signal_v1<T_Any>::Type>::Type events1;
	/// Map of event signals with two arguments held by EventHandler.
	T_Map<T_HashedStringType, T_Signal_v2<T_Any, T_Any>::Type>::Type events2;
	/// Map of event signals with three arguments held by EventHandler.
	T_Map<T_HashedStringType, T_Signal_v3<T_Any, T_Any, T_Any>::Type>::Type events3;
	/// Map of event signals with four arguments held by EventHandler.
	T_Map<T_HashedStringType, T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type>::Type events4;
	/// Map of event signals with five arguments held by EventHandler.
	T_Map<T_HashedStringType, T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type events5;
	/// Map of event signals with six arguments held by EventHandler.
	T_Map<T_HashedStringType, T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type events6;

	//--------------------------------------------------------

	/// Scheduled event base class definition
	class ScheduledEvent 
	{
	public:
		/// A flag that says whether this instance is free so we can write a new scheduled event to it.
		bool empty;
		/// Type of the scheduled event
		T_HashedString type;
		/// The exact time this event should be invoked
		F32 time;
		/// List of any arguments
		T_Vector<T_Any>::Type arguments;

		/// The constructor takes all parameters in structure in, with empty defaulting to false on construction.
		ScheduledEvent(const T_HashedString &type, const F32 &time, const bool &empty = false) 
			: type(type), time(time), empty(empty) //Leave option for pooling these at construction, thus empty can be set as true via constructor
		{}
	};

	/// List of argument-less, scheduled event signals held by EventHandler.
	T_Vector<ScheduledEvent*>::Type scheduledEvents;
};

//------------------------------------------------------

inline void AnyEventHandler::sendEvent(const T_HashedString &type)
{
	T_Map<T_HashedStringType, typename T_Signal_v0<>::Type>::Type::iterator it = events0.find(type.getId());
	if(it == events0.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events0 registry!").c_str());

	it->second.invoke();
}

inline void AnyEventHandler::sendEvent(const T_HashedString &type, T_Any arg0)
{
	T_Map<T_HashedStringType, T_Signal_v1<T_Any>::Type>::Type::iterator it = events1.find(type.getId());
	if(it == events1.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events1 registry!").c_str());

	it->second.invoke(arg0);
}

inline void AnyEventHandler::sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1)
{
	T_Map<T_HashedStringType, T_Signal_v2<T_Any, T_Any>::Type>::Type::iterator it = events2.find(type.getId());
	if(it == events2.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events2 registry!").c_str());

	it->second.invoke(arg0, arg1);
}

inline void AnyEventHandler::sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2)
{
	T_Map<T_HashedStringType, T_Signal_v3<T_Any, T_Any, T_Any>::Type>::Type::iterator it = events3.find(type.getId());
	if(it == events3.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events3 registry!").c_str());

	it->second.invoke(arg0, arg1, arg2);
}

inline void AnyEventHandler::sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3)
{
	T_Map<T_HashedStringType, T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events4.find(type.getId());
	if(it == events4.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events4 registry!").c_str());

	it->second.invoke(arg0, arg1, arg2, arg3);
}

inline void AnyEventHandler::sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4)
{
	T_Map<T_HashedStringType, T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events5.find(type.getId());
	if(it == events5.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events5 registry!").c_str());

	it->second.invoke(arg0, arg1, arg2, arg3, arg4);
}

inline void AnyEventHandler::sendEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4, T_Any arg5)
{
	T_Map<T_HashedStringType, T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events6.find(type.getId());
	if(it == events6.end())
		throw T_Exception(("Couldn't find event type " + type.getStr() + " in events6 registry!").c_str());

	it->second.invoke(arg0, arg1, arg2, arg3, arg4, arg5);

}

//------------------------------------------------------

inline void AnyEventHandler::updateScheduledEvents(const F32 &deltaTime)
{
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
			continue;

		event->time -= deltaTime;
		if(event->time <= 0.0f)
		{
			if(event->arguments.empty())
				this->sendEvent(event->type);
			else if(event->arguments.size() == 1)
				this->sendEvent(event->type, event->arguments[0]);
			else if(event->arguments.size() == 2)
				this->sendEvent(event->type, event->arguments[0], event->arguments[1]);
			else if(event->arguments.size() == 3)
				this->sendEvent(event->type, event->arguments[0], event->arguments[1], event->arguments[2]);
			else if(event->arguments.size() == 4)
				this->sendEvent(event->type, event->arguments[0], event->arguments[1], event->arguments[2], event->arguments[3]);
			else if(event->arguments.size() == 5)
				this->sendEvent(event->type, event->arguments[0], event->arguments[1], event->arguments[2], event->arguments[3], event->arguments[4]);
			else if(event->arguments.size() == 6)
				this->sendEvent(event->type, event->arguments[0], event->arguments[1], event->arguments[2], event->arguments[3], event->arguments[4], event->arguments[5]);

			event->empty = true;
			scheduledEvents[i] = scheduledEvents.back();
			scheduledEvents.pop_back();
			i--;
		}
	}
}

inline void AnyEventHandler::scheduleEvent(const T_HashedString &type, const F32 &time)
{
	//Check first if any instance of scheduled event that
	//already excist is free for writing...
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
		{
			event->empty = false;
			event->type = type;
			event->time = time;
			event->arguments.clear();
			return;
		}
	}

	ScheduledEvent *event = new ScheduledEvent(type, time);
	scheduledEvents.push_back(event);
}

inline void AnyEventHandler::scheduleEvent(const T_HashedString &type, T_Any arg0, const F32 &time)
{
	//Check first if any instance of scheduled event that
	//already excist is free for writing...
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
		{
			event->empty = false;
			event->type = type;
			event->time = time;
			event->arguments.clear();
			event->arguments.push_back(arg0);
			return;
		}
	}

	ScheduledEvent *event = new ScheduledEvent(type, time);
	event->arguments.push_back(arg0);
	scheduledEvents.push_back(event);
}

inline void AnyEventHandler::scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, const F32 &time)
{
	//Check first if any instance of scheduled event that
	//already excist is free for writing...
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
		{
			event->empty = false;
			event->type = type;
			event->time = time;
			event->arguments.clear();
			event->arguments.push_back(arg0);
			event->arguments.push_back(arg1);
			return;
		}
	}

	ScheduledEvent *event = new ScheduledEvent(type, time);
	event->arguments.push_back(arg0);
	event->arguments.push_back(arg1);
	scheduledEvents.push_back(event);
}

inline void AnyEventHandler::scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, const F32 &time)
{
	//Check first if any instance of scheduled event that
	//already excist is free for writing...
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
		{
			event->empty = false;
			event->type = type;
			event->time = time;
			event->arguments.clear();
			event->arguments.push_back(arg0);
			event->arguments.push_back(arg1);
			event->arguments.push_back(arg2);
			return;
		}
	}

	ScheduledEvent *event = new ScheduledEvent(type, time);
	event->arguments.push_back(arg0);
	event->arguments.push_back(arg1);
	event->arguments.push_back(arg2);
	scheduledEvents.push_back(event);
}

inline void AnyEventHandler::scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, const F32 &time)
{
	//Check first if any instance of scheduled event that
	//already excist is free for writing...
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
		{
			event->empty = false;
			event->type = type;
			event->time = time;
			event->arguments.clear();
			event->arguments.push_back(arg0);
			event->arguments.push_back(arg1);
			event->arguments.push_back(arg2);
			event->arguments.push_back(arg3);
			return;
		}
	}

	ScheduledEvent *event = new ScheduledEvent(type, time);
	event->arguments.push_back(arg0);
	event->arguments.push_back(arg1);
	event->arguments.push_back(arg2);
	event->arguments.push_back(arg3);
	scheduledEvents.push_back(event);
}

inline void AnyEventHandler::scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4, const F32 &time)
{
	//Check first if any instance of scheduled event that
	//already excist is free for writing...
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
		{
			event->empty = false;
			event->type = type;
			event->time = time;
			event->arguments.clear();
			event->arguments.push_back(arg0);
			event->arguments.push_back(arg1);
			event->arguments.push_back(arg2);
			event->arguments.push_back(arg3);
			event->arguments.push_back(arg4);
			return;
		}
	}

	ScheduledEvent *event = new ScheduledEvent(type, time);
	event->arguments.push_back(arg0);
	event->arguments.push_back(arg1);
	event->arguments.push_back(arg2);
	event->arguments.push_back(arg3);
	event->arguments.push_back(arg4);
	scheduledEvents.push_back(event);
}

inline void AnyEventHandler::scheduleEvent(const T_HashedString &type, T_Any arg0, T_Any arg1, T_Any arg2, T_Any arg3, T_Any arg4, T_Any arg5, const F32 &time)
{
	//Check first if any instance of scheduled event that
	//already excist is free for writing...
	for(U32 i = 0; i < scheduledEvents.size(); i++)
	{
		ScheduledEvent *event = scheduledEvents[i];
		if(event->empty)
		{
			event->empty = false;
			event->type = type;
			event->time = time;
			event->arguments.clear();
			event->arguments.push_back(arg0);
			event->arguments.push_back(arg1);
			event->arguments.push_back(arg2);
			event->arguments.push_back(arg3);
			event->arguments.push_back(arg4);
			event->arguments.push_back(arg5);
			return;
		}
	}

	ScheduledEvent *event = new ScheduledEvent(type, time);
	event->arguments.push_back(arg0);
	event->arguments.push_back(arg1);
	event->arguments.push_back(arg2);
	event->arguments.push_back(arg3);
	event->arguments.push_back(arg4);
	event->arguments.push_back(arg5);
	scheduledEvents.push_back(event);
}

//------------------------------------------------------------------

inline T_Signal_v0<>::Type &AnyEventHandler::registerToEvent0(const T_HashedString &type)
{
	T_Map<T_HashedStringType, typename T_Signal_v0<>::Type>::Type::iterator it = events0.find(type.getId());
	if(it == events0.end())
		return events0[type.getId()] = T_Signal_v0<>::Type();
	else
		return it->second;
}

inline T_Signal_v1<T_Any>::Type &AnyEventHandler::registerToEvent1(const T_HashedString &type)
{
	T_Map<T_HashedStringType, T_Signal_v1<T_Any>::Type>::Type::iterator it = events1.find(type.getId());
	if(it == events1.end())
		return events1[type.getId()] = T_Signal_v1<T_Any>::Type();
	else
		return it->second;
}

inline T_Signal_v2<T_Any, T_Any>::Type &AnyEventHandler::registerToEvent2(const T_HashedString &type)
{
	T_Map<T_HashedStringType, T_Signal_v2<T_Any, T_Any>::Type>::Type::iterator it = events2.find(type.getId());
	if(it == events2.end())
		return events2[type.getId()] = T_Signal_v2<T_Any, T_Any>::Type();
	else
		return it->second;
}

inline T_Signal_v3<T_Any, T_Any, T_Any>::Type &AnyEventHandler::registerToEvent3(const T_HashedString &type)
{
	T_Map<T_HashedStringType, T_Signal_v3<T_Any, T_Any, T_Any>::Type>::Type::iterator it = events3.find(type.getId());
	if(it == events3.end())
		return events3[type.getId()] = T_Signal_v3<T_Any, T_Any, T_Any>::Type();
	else
		return it->second;
}

inline T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type &AnyEventHandler::registerToEvent4(const T_HashedString &type)
{
	T_Map<T_HashedStringType, T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events4.find(type.getId());
	if(it == events4.end())
		return events4[type.getId()] = T_Signal_v4<T_Any, T_Any, T_Any, T_Any>::Type();
	else
		return it->second;
}

inline T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type &AnyEventHandler::registerToEvent5(const T_HashedString &type)
{
	T_Map<T_HashedStringType, T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events5.find(type.getId());
	if(it == events5.end())
		return events5[type.getId()] = T_Signal_v5<T_Any, T_Any, T_Any, T_Any, T_Any>::Type();
	else
		return it->second;
}

inline T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type &AnyEventHandler::registerToEvent6(const T_HashedString &type)
{
	T_Map<T_HashedStringType, T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type>::Type::iterator it = events6.find(type.getId());
	if(it == events6.end())
		return events6[type.getId()] = T_Signal_v6<T_Any, T_Any, T_Any, T_Any, T_Any, T_Any>::Type();
	else
		return it->second;
}

} //namespace Addon
} //namespace Totem
