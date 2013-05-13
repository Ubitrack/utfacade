set(the_description "The UbiTrack Facade")
ut_add_module(utfacade utcore utdataflow utvision)
ut_module_include_directories(${TINYXML_INCLUDE_DIR} ${LOG4CPP_INCLUDE_DIR} ${BOOSTBINDINGS_INCLUDE_DIR} ${LAPACK_INCLUDE_DIR}  ${Boost_INCLUDE_DIR})
ut_glob_module_sources(HEADERS "src/utFacade/*.h" SOURCES "src/utFacade/*.cpp")
ut_glob_component_sources(HEADERS "src/utComponents/*.h" SOURCES "src/utComponents/*.cpp")

# writes config file into binary_dir, so sourcetree will not be cluttered
configure_file(src/utFacade/Config_cmake.hh src/utFacade/Config.h)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/src/utFacade/Config.h" DESTINATION "${UBITRACK_INCLUDE_INSTALL_PATH}/utFacade/Config.h" COMPONENT main)

ut_create_module()

add_subdirectory(apps/Console)
add_subdirectory(apps/DotNet)
add_subdirectory(apps/Java)
add_subdirectory(apps/Python)
add_subdirectory(apps/C)
