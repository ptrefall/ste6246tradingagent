cmake_minimum_required(VERSION 2.8)

#---------------------------------------------------------------
project(TradingAgent)
#---------------------------------------------------------------
set(HDRS
)
#---------------------------------------------------------------
set(SRCS
  ./main.cpp
)
#---------------------------------------------------------------
find_package(Irrlicht REQUIRED)
find_package(GAlib REQUIRED)
find_package(ZLIB REQUIRED)
find_package(ClanLib REQUIRED)
find_package(Totem REQUIRED)
#---------------------------------------------------------------
add_executable(TradingAgent ${HDRS} ${SRCS})
#---------------------------------------------------------------
set_target_properties(TradingAgent PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TradingAgent PROPERTIES LINKER_LANGUAGE CXX)
#---------------------------------------------------------------
target_link_libraries(TradingAgent
  debug ${IRR_LIB_DEBUG} optimized ${IRR_LIB_RELEASE}
  debug ${GALIB_LIB_DEBUG} optimized ${GALIB_LIB_RELEASE}
  debug ${ZLIB_LIBRARY_DEBUG} optimized ${ZLIB_LIBRARY_RELEASE}
  debug ${CL_CORE_LIB_DEBUG} optimized ${CL_CORE_LIB_RELEASE}
  debug ${TOTEM_LIB_DEBUG} optimized ${TOTEM_LIB_RELEASE}
)
#---------------------------------------------------------------