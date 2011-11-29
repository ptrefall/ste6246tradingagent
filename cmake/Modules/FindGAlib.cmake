
FIND_PATH(GALIB_DIR include/GA/ga.h
      ../depends
    )
	
FIND_PATH(GALIB_INCLUDE_PATH GA/ga.h
      ../depends/include
    )

FIND_LIBRARY(GALIB_LIB_DEBUG
  NAMES galib-mt-debug-static.lib
  PATHS ../depends/lib
    )
	
FIND_LIBRARY(GALIB_LIB_RELEASE
  NAMES galib-mt-static.lib
  PATHS ../depends/lib
    )