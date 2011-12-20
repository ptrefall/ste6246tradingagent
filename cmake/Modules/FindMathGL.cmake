FIND_PATH(MATHGL_INCLUDE_DIR mgl/mgl.h
	../depends/include
)

FIND_LIBRARY(MATHGL_LIBRARY_DEBUG
    NAMES MathGL-static-mt-debug
    PATHS ../depends/lib
)
FIND_LIBRARY(MATHGL_LIBRARY_RELEASE
    NAMES MathGL-static-mt
    PATHS ../depends/lib
)
