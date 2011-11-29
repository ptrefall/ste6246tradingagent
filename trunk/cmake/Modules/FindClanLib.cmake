
FIND_PATH(CL_DIR include/ClanLib/core.h
      ../depends
    )

FIND_PATH(CL_INCLUDE_PATH ClanLib/core.h
      ../depends/include
    )
	
FIND_LIBRARY(CL_CORE_LIB_RELEASE
	NAMES clanCore-static-mt
    PATHS ../depends/lib
    )

FIND_LIBRARY(CL_CORE_LIB_DEBUG
	NAMES clanCore-static-mt-debug
    PATHS ../depends/lib
    )
	
FIND_LIBRARY(CL_NET_LIB_RELEASE
	NAMES clanNetwork-static-mt
    PATHS ../depends/lib
    )

FIND_LIBRARY(CL_NET_LIB_DEBUG
	NAMES clanNetwork-static-mt-debug
    PATHS ../depends/lib
    )
