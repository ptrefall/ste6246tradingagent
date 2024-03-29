###
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#
# Note: Some of the libraries Totem EDK may link to may have additional
# requirements or restrictions.
#
###
# CMake system for Totem EDK was contributed by Jacob 'jacmoe' Moen
#
###

cmake_minimum_required(VERSION 2.8)
 
project(TotemEDK)

set(Default_HDRS
	./Depends/types.h
	./Depends/cdiggins_any.h
	./Depends/sigslot.h
	./Depends/FastDelegate.h
	./Depends/FastDelegateBind.h
)
SOURCE_GROUP("Header Files\\Types" FILES ${Default_HDRS})

set(HDRS
  ./Component.h
  ./ComponentFactory.h
  ./ComponentHandler.h
  ./IProperty.h
  ./Property.h
  ./PropertyHandler.h
  ./IPropertySerializer.h
  ./PropertySerializer.h
  ./IPropertyList.h
  ./PropertyList.h
  ./PropertyListHandler.h
  ./types_config.h
)

set(SRCS
  ./ComponentFactory.cpp
)
 
add_library(TotemEDK STATIC  ${Default_HDRS} ${HDRS} ${SRCS})

set_target_properties(TotemEDK PROPERTIES DEBUG_POSTFIX -static-mt-debug)
