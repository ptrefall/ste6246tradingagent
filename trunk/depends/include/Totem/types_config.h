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
 * Types Configuration, originally contributed by 'savuporo'.
 * 
 */

//These can overloaded in each specific types implementation:
//-------------------------------------------------------------------
/**	
 * Some type implementations might require that the signal-slot system
 * place an inheritance dependency on PropertyData and Component, so that
 * they get the "ability" of owning slots for their signals.
 * If the implementation don't, just leave this definition as empty.
 */
#define HAS_SIGNALSLOTS_INHERITANCE_TYPE

/**
 * Some type implementations might want to use different null pointer conventions.
 * For instance the C++0x nullptr type, or some other approach like (void*)0, etc.
 */
#define NULL_PTR 0x0

#include <Totem\Depends\types.h>
