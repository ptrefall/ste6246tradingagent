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
	./SceneNode/TAnimSprite.h
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
set(GUI_HDRS
	./GUI/CIrrRocketEventReceiver.h
	./GUI/CIrrRocketGUI.h
	./GUI/IrrRocketFileInterface.h
	./GUI/IrrRocketInterface.h
	./GUI/IrrRocketRenderer.h
)
SOURCE_GROUP("Header Files\\GUI" FILES ${GUI_HDRS})
#---------------------------------------------------------------
set(GUI_SRCS
	./GUI/CIrrRocketEventReceiver.cpp
	./GUI/CIrrRocketGUI.cpp
	./GUI/IrrRocketFileInterface.cpp
	./GUI/IrrRocketInterface.cpp
	./GUI/IrrRocketRenderer.cpp
)
SOURCE_GROUP("Source Files\\GUI" FILES ${GUI_SRCS})
#---------------------------------------------------------------
set(GA_GENOME_HDRS
	./GeneticAlg/Genome/ProsumerGenome.h
)
SOURCE_GROUP("Header Files\\GeneticAlg\\Genome" FILES ${GA_GENOME_HDRS})
#---------------------------------------------------------------
set(GA_GENOME_SRCS
	./GeneticAlg/Genome/ProsumerGenome.cpp
)
SOURCE_GROUP("Source Files\\GeneticAlg\\Genome" FILES ${GA_GENOME_SRCS})
#---------------------------------------------------------------
find_package(Irrlicht REQUIRED)
find_package(GAlib REQUIRED)
find_package(ZLIB REQUIRED)
find_package(ClanLib REQUIRED)
find_package(Totem REQUIRED)
find_package(Freetype REQUIRED)
find_package(Rocket REQUIRED)
#---------------------------------------------------------------
add_executable(TradingAgent ${HDRS} ${SRCS} 
							${SCENE_NODE_HDRS} ${SCENE_NODE_SRCS}
							${WEATHER_SCENE_NODE_HDRS} ${WEATHER_SCENE_NODE_SRCS}
							${GUI_HDRS} ${GUI_SRCS}
							${GA_GENOME_HDRS} ${GA_GENOME_SRCS}
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
  debug ${FREETYPE_LIB_DEBUG} optimized ${FREETYPE_LIB_RELEASE}
  debug ${ROCKET_CORE_LIB_DEBUG} optimized ${ROCKET_CORE_LIB_RELEASE}
  debug ${ROCKET_CONTROLS_LIB_DEBUG} optimized ${ROCKET_CONTROLS_LIB_RELEASE}
)
#---------------------------------------------------------------