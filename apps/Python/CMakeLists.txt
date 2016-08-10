if(UBITRACK_INITIAL_PASS)
    set(the_target "ubitrack_python")
    set(UBITRACK_APPS_BUILD ${UBITRACK_APPS_BUILD} "${the_target}" CACHE INTERNAL "List of UbiTrack apps included into the build")
    set(UBITRACK_APPS_${the_target}_LOCATION  "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "Location of ${the_target} app sources")
else()
    if(HAVE_OPENCV)
	  SET(UTPYTHON_REQUIRED_DEPS utcore utdataflow utvision utfacade)
	else(HAVE_OPENCV)
	  SET(UTPYTHON_REQUIRED_DEPS utcore utdataflow utfacade)
	endif(HAVE_OPENCV)
	
	if(BUILD_UTPYTHON)
	    ut_include_modules(${UTPYTHON_REQUIRED_DEPS} ${PYTHON_INCLUDE_PATH})

		SET(CMAKE_SWIG_FLAGS "-shadow")

		SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES CPLUSPLUS ON)
		SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES SWIG_FLAGS "-ignoremissing")

		SWIG_ADD_MODULE(ubitrack python interface.i)
		SWIG_LINK_LIBRARIES(ubitrack ${PYTHON_LIBRARIES} ${UBITRACK_LINKER_LIBS} ${UTPYTHON_REQUIRED_DEPS})
	endif(BUILD_UTPYTHON)
endif(UBITRACK_INITIAL_PASS)
