#root/CMakeLists.txt

#CMake Version Minimum Required
cmake_minimum_required (VERSION 2.8.11)

###############################################################################
# DEFINITION
###############################################################################

set(PROJECT_ACRONYM_STR "SSIG-ONVIF")
set(PROJECT_NAME_STR "SSIG ONVIF Library")
project(${PROJECT_ACRONYM_STR} CXX)

###############################################################################
# USER OPTIONS
###############################################################################

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")

#Option to check if 'test' will be available
option(BUILD_TESTS "Build tests" ON)

#Option to check if 'app' will be available
option(BUILD_APPS "Build APP's" ON)

# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." ON)

#Option to check if 'docs' will be build
# option(BUILD_DOCS "Create and install the HTML based API documentation (requires Doxygen)" OFF)

#Option to check if 'docs' will be build
option(BUILD_SAMPLES "Build onvif samples" ON)

# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
# option(ENABLE_COVERAGE "Enable coverage collection with  GCov." OFF)

mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH ENABLE_COVERAGE)
mark_as_advanced(CMAKE_CONFIGURATION_TYPES CMAKE_INSTALL_PREFIX)
mark_as_advanced(SSL_EAY_DEBUG SSL_EAY_RELEASE LIB_EAY_DEBUG LIB_EAY_RELEASE)

###############################################################################
# CMake OPTIONS
###############################################################################

#Remove Warning CMP0054 from gtest cmake build
if(POLICY CMP0054)
	cmake_policy(SET CMP0054 OLD)
endif()

if(POLICY CMP0042)
	cmake_policy(SET CMP0042 OLD)
endif()

#Check compilers version
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE TEMP_COMPILER_VERSION)
	if(TEMP_COMPILER_VERSION VERSION_LESS 4.7)
		message(FATAL_ERROR "${PROJECT_NAME_STR} requires g++ 4.7 or greater. Installed version: ${CMAKE_CXX_COMPILER_VERSION}")
	endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE TEMP_COMPILER_VERSION)
	if (TEMP_COMPILER_VERSION VERSION_LESS 3.4)
		message(FATAL_ERROR "${PROJECT_NAME_STR} requires Clang 3.4 or greater. Installed version: ${CMAKE_CXX_COMPILER_VERSION}")
	endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")	
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
		message(FATAL_ERROR "${PROJECT_NAME_STR} requires MSVC 1700 (MSVC 2012) or greater. Installed version: ${CMAKE_CXX_COMPILER_VERSION}")
	endif()
else()
    message(WARNING "You are using an unsupported compiler! ${PROJECT_NAME_STR} has only been tested with Clang, GCC and MSVC.")
endif()


#Definitions
set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL}")
set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
	set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -std=gnu++11")#
	set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
	set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL} -Os -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE} -O4 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")
	#Solve plugin problem for some linux versions
	set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS}")
	set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG}")
	set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL}")
	set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE}")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
endif()

#Disable C4996
if(MSVC)
	add_definitions(/D_SCL_SECURE_NO_WARNINGS=1)
	add_definitions(/D_CRT_SECURE_NO_WARNINGS=1)
endif()

#Allows the solution folder utilization (for MSVC)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# If install location is default, set new default to "build/install"
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "default install path" FORCE )
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Enable tests if BUILD_TEST was checked by user
if(BUILD_TESTS)
	enable_testing()
endif()

# if(ENABLE_COVERAGE)
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
# endif()

###############################################################################
# CMake Auxiliary Files
###############################################################################
include(cmake/SSIGOnvifOpenSSLUtil.cmake)
include(cmake/SSIGOnvifUtil.cmake)

###############################################################################
# SUBDIRECTORIES
###############################################################################

#Add 3rdparty
add_subdirectory(3rdparty)

# Add modules
add_subdirectory(ssigonvif)

# Add documentation
add_subdirectory(samples)