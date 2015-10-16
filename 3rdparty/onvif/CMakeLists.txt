set(ONVIF_NAME "onvif")
set(ONVIF_PATH "${PROJECT_SOURCE_DIR}/3rdparty/onvif")

# files glob
file(GLOB ONVIF_INCLUDE_FILES		"${ONVIF_PATH}/include/onvif/*.h")
file(GLOB GSOAP_INCLUDE_FILES		"${ONVIF_PATH}/include/gsoap/*.h")
file(GLOB ONVIF_SOURCE_FILES		"${ONVIF_PATH}/src/onvif/*.cpp")
file(GLOB GSOAP_SOURCE_FILES		"${ONVIF_PATH}/src/gsoap/*.c*")

	# add library
add_library(${ONVIF_NAME} STATIC ${ONVIF_SOURCE_FILES} ${GSOAP_SOURCE_FILES} ${ONVIF_INCLUDE_FILES} ${GSOAP_INCLUDE_FILES})
target_include_directories(${ONVIF_NAME} PUBLIC 
	${ONVIF_PATH}/include/ 
	${ONVIF_PATH}/include/onvif
	${ONVIF_PATH}/include/gsoap)
	
set_target_properties(${ONVIF_NAME} PROPERTIES FOLDER 3RDPARTY)

target_compile_definitions(${ONVIF_NAME} PUBLIC WITH_DOM)
target_compile_definitions(${ONVIF_NAME} PUBLIC WITH_OPENSSL)
target_compile_definitions(${ONVIF_NAME} PUBLIC WITH_PURE_VIRTUAL)

if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
	set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Wno-deprecated-register -Wno-format")#
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(${ONVIF_NAME} PRIVATE /bigobj)
	# Disable Warning	C4267: conversion from 'size_t' to 'int', possible loss of data
	ADD_DEFINITIONS("/wd4267")
endif()



SET_SOURCE_FILES_PROPERTIES("${ONVIF_PATH}/src/gsoap/duration.c" PROPERTIES LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES("${ONVIF_PATH}/src/gsoap/mecevp.c" PROPERTIES LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES("${ONVIF_PATH}/src/gsoap/smdevp.c" PROPERTIES LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES("${ONVIF_PATH}/src/gsoap/threads.c" PROPERTIES LANGUAGE CXX)
SET_SOURCE_FILES_PROPERTIES("${ONVIF_PATH}/src/gsoap/wsaapi.c" PROPERTIES LANGUAGE CXX)

ssigonvif_link_openssl(${ONVIF_NAME})