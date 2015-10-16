#root/components/cameras/app/CMakeLists.txt

if(BUILD_SAMPLES)

	#Create set of cameras tests files
	file(GLOB SAMPLE_FILES "${PROJECT_SOURCE_DIR}/samples/*.cpp" "${PROJECT_SOURCE_DIR}/samples/*.hpp")
	
	# add_executable(ssigonvif-samples ${CAMERAS_APP_FILES})

	# Standard linking to gtest stuff.
	# target_include_directories(app_cameras PUBLIC ${CAMERAS_PATH}/include/)

	# Extra linking for the project.
	# target_link_libraries(app_cameras ssf_cameras)
	
	#Configure folder to cameras library
	# set_target_properties(app_cameras PROPERTIES FOLDER APPS)

	
endif()