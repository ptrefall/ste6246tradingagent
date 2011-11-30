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
set(SCENE_NODE_HDRS
	./SceneNode/HealthSceneNode.h
	./SceneNode/CGridSceneNode.h
)
SOURCE_GROUP("Header Files\\SceneNode" FILES ${SCENE_NODE_HDRS})
#---------------------------------------------------------------
set(SCENE_NODE_SRCS
  ./SceneNode/HealthSceneNode.cpp
  ./SceneNode/CGridSceneNode.cpp
)
SOURCE_GROUP("Source Files\\SceneNode" FILES ${SCENE_NODE_SRCS})
#---------------------------------------------------------------
set(WEATHER_SCENE_NODE_HDRS
	./SceneNode/Weather/IAtmosphereSkySceneNode.h
	./SceneNode/Weather/IAtmosphereStarSceneNode.h
	./SceneNode/Weather/IBoltSceneNode.h
	./SceneNode/Weather/ICloudLayer.h
	./SceneNode/Weather/ICloudSceneNode.h
	./SceneNode/Weather/irrWeatherManager.h
	./SceneNode/Weather/IWeatherManagerAtmosphere.h
)
SOURCE_GROUP("Header Files\\SceneNode\\Weather" FILES ${WEATHER_SCENE_NODE_HDRS})
#---------------------------------------------------------------
set(WEATHER_SCENE_NODE_SRCS
	./SceneNode/Weather/IAtmosphereSkySceneNode.cpp
	./SceneNode/Weather/IAtmosphereStarSceneNode.cpp
	./SceneNode/Weather/IBoltSceneNode.cpp
	./SceneNode/Weather/ICloudLayer.cpp
	./SceneNode/Weather/ICloudSceneNode.cpp
	./SceneNode/Weather/irrWeatherManager.cpp
	./SceneNode/Weather/IWeatherManagerAtmosphere.cpp
)
SOURCE_GROUP("Source Files\\SceneNode\\Weather" FILES ${WEATHER_SCENE_NODE_SRCS})
#---------------------------------------------------------------
find_package(Irrlicht REQUIRED)
find_package(GAlib REQUIRED)
find_package(ZLIB REQUIRED)
find_package(ClanLib REQUIRED)
find_package(Totem REQUIRED)
#---------------------------------------------------------------
add_executable(TradingAgent ${HDRS} ${SRCS} 
							${SCENE_NODE_HDRS} ${SCENE_NODE_SRCS}
							${WEATHER_SCENE_NODE_HDRS} ${WEATHER_SCENE_NODE_SRCS}
	)
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