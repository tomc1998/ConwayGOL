cmake_minimum_required (VERSION 2.6)
project(Conway)

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)

set (CONWAY_SRCS ${PROJECT_SOURCE_DIR}/main.c
                 ${PROJECT_SOURCE_DIR}/renderer.c
                 ${PROJECT_SOURCE_DIR}/input_handler.c
                 ${PROJECT_SOURCE_DIR}/state.c)

add_executable(Conway ${CONWAY_SRCS})

if (MSVC)
  target_link_libraries(Conway ${PROJECT_ROOT_DIR}/lib/glfw3.lib opengl32 gdi32 user32 kernel32 shell32)
  include_directories(${PROJECT_ROOT_DIR}/include)
	set (CMAKE_CXX_FLAGS "/MD /EHsc")
endif (MSVC)

if(${CMAKE_COMPILER_IS_GNUCC})
	link_directories(/usr/local/lib)
	target_link_libraries(Conway glfw3 GL 
	# glfw3 library dependencies
	glfw3 rt Xrandr Xinerama Xi Xcursor m dl Xrender drm Xdamage X11-xcb 
		xcb-glx xcb-dri2 xcb-dri3 xcb-present xcb-sync xshmfence Xxf86vm 
		Xfixes Xext X11 pthread xcb Xau Xdmcp
	)
  set (CMAKE_CXX_FLAGS "-std=c++11")
endif()

