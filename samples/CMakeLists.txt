#root/components/cameras/app/CMakeLists.txt

if(BUILD_SAMPLES)

	#Create set of cameras tests files
	file(GLOB SAMPLE_FILES "${PROJECT_SOURCE_DIR}/samples/*.cpp" "${PROJECT_SOURCE_DIR}/samples/*.hpp")
	
	add_executable(ssigonvif-samples ${SAMPLE_FILES})


	# Extra linking for the project.
	target_link_libraries(ssigonvif-samples ssigonvif)

	target_include_directories(ssigonvif-samples PUBLIC ${PROJECT_SOURCE_DIR}/ssigonvif/include)
	target_include_directories(ssigonvif-samples PUBLIC ${CURSES_INCLUDE_DIR})	

	#Configure folder to cameras library
	set_target_properties(ssigonvif-samples PROPERTIES FOLDER SAMPLES)

	
endif()