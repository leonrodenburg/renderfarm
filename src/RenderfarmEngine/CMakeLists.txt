# set up project
cmake_minimum_required (VERSION 2.6)
project (renderfarm)

# if the generator is Xcode or Unix
if (CMAKE_GENERATOR MATCHES Xcode OR CMAKE_GENERATOR MATCHES Unix)
    	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-write-strings")
endif()

# if the generator is Xcode
if (CMAKE_GENERATOR MATCHES Xcode)
	# find Cocoa library
	find_library (COCOA_LIBRARY NAMES Cocoa)

	# include Cocoa library
	set (EXTRA_LIBS ${EXTRA_LIBS} ${COCOA_LIBRARY})

	# set library name
	set (LIBRARY_NAME renderfarm-engine-0.1a-osx)

	# set platform
	set (RF_PLATFORM 2)
elseif (CMAKE_GENERATOR MATCHES Unix)
	# set library name
	set (LIBRARY_NAME renderfarm-engine-0.1a-unix)

	# set platform
	set (RF_PLATFORM 3)
else()
  	# set library name
	set (LIBRARY_NAME renderfarm-engine-0.1a-win32)

	# set platform
	set (RF_PLATFORM 1)
endif()

# configure a header file
configure_file (
    "${PROJECT_SOURCE_DIR}/Resources.h.in"
    "${PROJECT_SOURCE_DIR}/Resources.h"
)

add_library (${LIBRARY_NAME} SHARED
			Resources.h
			Core/Kernel.h
			Core/Kernel.cpp
			Core/Logger.h
			Core/Logger.cpp
			Geometry/Cube.h
			Geometry/Cube.cpp
			Geometry/Geometry.h
			Geometry/Geometry.cpp
			Geometry/World.h
			Geometry/World.cpp
			Math/Matrix.h
			Math/Matrix.cpp
			Math/Utility.h
			Math/Vector3.h
			Math/Vector3.cpp
			Math/Vector4.h
			Math/Vector4.cpp
			Stage/Clipper.h
			Stage/Clipper.cpp
			Stage/Rasterizer.h
			Stage/Rasterizer.cpp
)
