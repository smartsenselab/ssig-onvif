file(GLOB INCLUDE_FILES "${PROJECT_SOURCE_DIR}/ssigonvif/include/ssigonvif/*.hpp")
file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/ssigonvif/src/*.cpp")

add_library(ssigonvif ${SOURCE_FILES} ${INCLUDE_FILES})
target_include_directories(ssigonvif PUBLIC ${PROJECT_SOURCE_DIR}/ssigonvif/include/)
set_target_properties(ssigonvif PROPERTIES FOLDER LIBRARY)

string(TOUPPER "SSIGONVIF_API_EXPORTS" EXPORTS_MACRO)
target_compile_definitions(ssigonvif PUBLIC ${EXPORTS_MACRO})

target_link_libraries(ssigonvif onvif)
ssigonvif_link_openssl(ssigonvif)