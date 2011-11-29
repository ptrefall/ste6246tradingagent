
FIND_PATH(TOTEM_DIR include/Totem/Component.h
      ../depends
    )
	
FIND_PATH(TOTEM_INCLUDE_PATH Totem/Component.h
      ../depends/include
    )

FIND_LIBRARY(TOTEM_LIB_DEBUG
  NAMES TotemEDK_ClanLib-static-mt-debug
  PATHS ../depends/lib
    )
	
FIND_LIBRARY(TOTEM_LIB_RELEASE
  NAMES TotemEDK_ClanLib-static-mt
  PATHS ../depends/lib
    )