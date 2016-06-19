UT_OPTION(ENABLE_BASICFACADE "Enable Basic Facade" OFF)
IF(ENABLE_BASICFACADE)
  add_definitions("-DENABLE_BASICFACADE")
ENDIF(ENABLE_BASICFACADE)
set(the_description "The UbiTrack Facade")
ut_add_module(utfacade utcore utdataflow utvision)
ut_module_include_directories(utfacade ${UBITRACK_CORE_DEPS_INCLUDE_DIR} ${OPENCV_INCLUDE_DIR})
ut_glob_module_sources(HEADERS "*.h" SOURCES "*.cpp")

# writes config file into binary_dir, so sourcetree will not be cluttered
configure_file(Config_cmake.hh ${CMAKE_CURRENT_SOURCE_DIR}/Config.h)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/Config.h" DESTINATION "${UBITRACK_INCLUDE_INSTALL_PATH}/utFacade" COMPONENT main)

ut_create_module(${TINYXML_LIBRARIES} ${LOG4CPP_LIBRARIES} ${LAPACK_LIBRARIES} ${Boost_LIBRARIES})
