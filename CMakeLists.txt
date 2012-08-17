cmake_minimum_required (VERSION 2.6)
project (IrrLuaEngine)

SET(CMAKE_BUILD_TYPE Debug)

SET(WORKSPACE "../")


IF(WIN32)
	SET(LIBRARY_EXTENSION ".lib")	
	SET(IRRLICHT_LIBRARY "${CMAKE_SOURCE_DIR}/${WORKSPACE}irrlicht-1.7.3/lib/Win32-visualstudio/Irrlicht${LIBRARY_EXTENSION}")
	SET(LUAJIT_LIBRARY "${CMAKE_SOURCE_DIR}/${WORKSPACE}luajit-2.0/src/lua51${LIBRARY_EXTENSION}")
ELSE()
	SET(LIBRARY_EXTENSION ".a")
	SET(IRRLICHT_LIBRARY "${CMAKE_SOURCE_DIR}/${WORKSPACE}irrlicht-1.7.3/lib/Linux/libIrrlicht${LIBRARY_EXTENSION}")
	SET(LUAJIT_LIBRARY "${CMAKE_SOURCE_DIR}/${WORKSPACE}luajit-2.0/src/libluajit${LIBRARY_EXTENSION}")
	SET(ADDITIONAL_LIBS "Xxf86vm")
	find_package(GLUT)
ENDIF()


find_package(OpenGL)

SET(SUBDIRS "GUI" "Script" "Video")

FILE(GLOB_RECURSE SOURCES "src/*.cpp")
FILE(GLOB_RECURSE HEADERS "src/*.h")

add_executable(exec ${SOURCES})

include_directories("src")
foreach(dir ${SUBDIRS})
 include_directories("src/${dir}")
endforeach()
include_directories("${WORKSPACE}irrlicht-1.7.3/include")
include_directories("${WORKSPACE}luajit-2.0/src")


target_link_libraries(exec ${IRRLICHT_LIBRARY} ${LUAJIT_LIBRARY} ${ADDITIONAL_LIBS} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )

