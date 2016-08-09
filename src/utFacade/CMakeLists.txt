UT_OPTION(ENABLE_BASICFACADE "Enable Basic Facade" ON)
IF(ENABLE_BASICFACADE)
  add_definitions("-DENABLE_BASICFACADE")
ENDIF(ENABLE_BASICFACADE)


set(the_description "The UbiTrack Facade")
if(HAVE_OPENCV)
  ut_add_module(utfacade utcore utdataflow utvision)
  ut_module_include_directories(utfacade ${UBITRACK_CORE_DEPS_INCLUDE_DIR} ${OPENCV_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${Freeglut_INCLUDE_DIR})
else(HAVE_OPENCV)
  ut_add_module(utfacade utcore utdataflow)
  ut_module_include_directories(utfacade ${UBITRACK_CORE_DEPS_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${Freeglut_INCLUDE_DIR})
endif(HAVE_OPENCV)

ut_glob_module_sources(HEADERS "*.h" SOURCES "*.cpp")

# writes config file into binary_dir, so sourcetree will not be cluttered
configure_file(Config_cmake.hh ${CMAKE_CURRENT_SOURCE_DIR}/Config.h)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/Config.h" DESTINATION "${UBITRACK_INCLUDE_INSTALL_PATH}/utFacade" COMPONENT main)

ut_create_module(${TINYXML_LIBRARIES} ${LOG4CPP_LIBRARIES} ${LAPACK_LIBRARIES} ${Boost_LIBRARIES})
