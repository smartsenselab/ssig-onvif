include(CMakeParseArguments)

macro(ssigonvif_find_openssl)
	set(ssigonvif_options REQUIRED QUIET)
	set(ssigonvif_multiValueArgs COMPONENTS)
	cmake_parse_arguments(SSIGONVIF_FIND_OPEN_SSL "${ssf_options}" "${ssf_oneValueArgs}" "${ssf_multiValueArgs}" ${ARGN} )	
	
	set(ssigonvif_options "")
	if(${SSF_FIND_OPEN_SSL_REQUIRED})
		set(ssigonvif_options "REQUIRED")
	endif()	
	
	if(${SSF_FIND_OPEN_SSL_QUIET})
		set(ssigonvif_options "QUIET")
	endif()	
	
	find_package(OpenSSL ${ssf_options})
	
endmacro()

macro(ssigonvif_link_openssl TARGET)
	
	ssigonvif_find_openssl(COMPONENTS ${ARGN} REQUIRED)	
	target_compile_definitions(${TARGET} PUBLIC WITH_OPENSSL)
	target_include_directories(${TARGET} PUBLIC ${OPENSSL_INCLUDE_DIR})	
	target_link_libraries(${TARGET} ${OPENSSL_LIBRARIES})
	
endmacro()