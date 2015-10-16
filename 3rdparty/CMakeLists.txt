#root/3rdparty/CMakeLists.txt

###############################################################################
# 3RDPARTY SUBDIRECTORIES
###############################################################################

#Google Tests
#Include Google Tests if only BUILD_TESTS was checked by user
if(BUILD_TESTS)
	add_subdirectory (gtest-1.7.0)
endif()
add_subdirectory (onvif)
