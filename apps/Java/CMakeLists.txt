macro(ut_get_customized_app_creator)
	find_package(Java)
    ut_include_modules(${UBITRACK_APP_${the_app}_DEPS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../utfacade ${JNI_INCLUDE_DIRS})

    SET(CMAKE_SWIG_FLAGS "-v")

	if(CMAKE_COMPILER_IS_GNUCXX)
      SET(CMAKE_CXX_FLAGS "-fno-strict-aliasing")
    endif(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack)
    SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES CPLUSPLUS ON)
    SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES SWIG_FLAGS "-package;ubitrack")

    SWIG_ADD_MODULE(ubitrack_java java ${UBITRACK_APP_${the_app}_SOURCES})
    SWIG_LINK_LIBRARIES(ubitrack_java ${JNI_LIBRARIES} ${UBITRACK_APP_${the_app}_DEPS} ${UBITRACK_LINKER_LIBS})

	ADD_CUSTOM_COMMAND(TARGET ubitrack_java
		           POST_BUILD
		           COMMAND cmake -E echo "Compiling Java files..."
		           COMMAND cmake -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/classes/ubitrack
		           COMMAND ${Java_JAVAC_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack/*.java -d ${CMAKE_CURRENT_BINARY_DIR}/classes
		           COMMAND cmake -E echo "Creating jar file..."
		           COMMAND ${Java_JAR_EXECUTABLE} cvf ubitrack.jar -C ${CMAKE_CURRENT_BINARY_DIR}/classes ubitrack 
	)
	install(TARGETS ${SWIG_MODULE_ubitrack_java_REAL_NAME}
	  RUNTIME DESTINATION bin COMPONENT java
	  LIBRARY DESTINATION ${UBITRACK_LIB_INSTALL_PATH} COMPONENT java
	  ARCHIVE DESTINATION ${UBITRACK_LIB_INSTALL_PATH} COMPONENT dev
	  )	
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ubitrack.jar DESTINATION "${UBITRACK_LIB_INSTALL_PATH}" COMPONENT java)
	
endmacro(ut_get_customized_app_creator)


set(the_description "The UbiTrack Java Wrapper")
if(HAVE_OPENCV)
  ut_add_app(ubitrack_java DEPS utcore utdataflow utfacade utvision)
  ut_app_include_directories(${TINYXML_INCLUDE_DIR} ${LOG4CPP_INCLUDE_DIR} ${BOOSTBINDINGS_INCLUDE_DIR} ${LAPACK_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
else(HAVE_OPENCV)
  ut_add_app(ubitrack_java DEPS utcore utdataflow utfacade)
  ut_app_include_directories(${TINYXML_INCLUDE_DIR} ${LOG4CPP_INCLUDE_DIR} ${BOOSTBINDINGS_INCLUDE_DIR} ${LAPACK_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
endif(HAVE_OPENCV)
ut_glob_app_sources(SOURCES "interface.i")
ut_create_customized_app()
