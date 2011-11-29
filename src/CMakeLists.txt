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
#---------------------------------------------------------------
add_executable(TradingAgent ${HDRS} ${SRCS})
#---------------------------------------------------------------
set_target_properties(TradingAgent PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(TradingAgent PROPERTIES LINKER_LANGUAGE CXX)
#---------------------------------------------------------------
target_link_libraries(TradingAgent
  debug ${IRR_LIB_DEBUG} optimized ${IRR_LIB_RELEASE}
  debug ${GALIB_LIB_DEBUG} optimized ${GALIB_LIB_RELEASE}
)
#---------------------------------------------------------------