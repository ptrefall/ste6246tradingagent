
FIND_PATH(ROCKET_DIR include/Rocket/Core.h
      ../depends
    )

FIND_PATH(ROCKET_INCLUDE_PATH Rocket/Core.h
      ../depends/include
    )
	
FIND_LIBRARY(ROCKET_CORE_LIB_RELEASE
	NAMES RocketCore-static-mt
    PATHS ../depends/lib
    )

FIND_LIBRARY(ROCKET_CORE_LIB_DEBUG
	NAMES RocketCore-static-mt-debug
    PATHS ../depends/lib
    )
	
FIND_LIBRARY(ROCKET_CONTROLS_LIB_RELEASE
	NAMES RocketControls-static-mt
    PATHS ../depends/lib
    )

FIND_LIBRARY(ROCKET_CONTROLS_LIB_DEBUG
	NAMES RocketControls-static-mt-debug
    PATHS ../depends/lib
    )
	
FIND_LIBRARY(ROCKET_DEBUGGER_LIB_RELEASE
	NAMES RocketDebugger-static-mt
    PATHS ../depends/lib
    )

FIND_LIBRARY(ROCKET_DEBUGGER_LIB_DEBUG
	NAMES RocketDebugger-static-mt-debug
    PATHS ../depends/lib
    )
