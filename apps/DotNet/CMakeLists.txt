macro(ut_get_customized_app_creator)
    ut_include_modules(${UBITRACK_APP_${the_app}_DEPS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../utfacade)
    SET(CMAKE_SWIG_FLAGS "-v")

	if(CMAKE_COMPILER_IS_GNUCXX)
      SET(CMAKE_CXX_FLAGS "-fno-strict-aliasing")
    endif(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack)
    SET_SOURCE_FILES_PROPERTIES(${UBITRACK_APP_${the_app}_SOURCES} PROPERTIES CPLUSPLUS ON)
    SET_SOURCE_FILES_PROPERTIES(${UBITRACK_APP_${the_app}_SOURCES}PROPERTIES SWIG_FLAGS "-namespace;Ubitrack")

    SWIG_ADD_MODULE(ubitrack_dotnet_swig csharp ${UBITRACK_APP_${the_app}_SOURCES})
    SWIG_LINK_LIBRARIES(ubitrack_dotnet_swig ${UBITRACK_APP_${the_app}_DEPS} ${UBITRACK_LINKER_LIBS})

	install(TARGETS ${SWIG_MODULE_ubitrack_dotnet_swig_REAL_NAME}
	  RUNTIME DESTINATION bin COMPONENT main
	  LIBRARY DESTINATION ${UBITRACK_LIB_INSTALL_PATH} COMPONENT main
	  ARCHIVE DESTINATION ${UBITRACK_LIB_INSTALL_PATH} COMPONENT main
	)	

	file(GLOB cs_srcs "${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack/*.cs")
	csharp_add_library(ubitrack_dotnet ${cs_srcs})
	install_assembly(ubitrack_dotnet DESTINATION "${UBITRACK_LIB_INSTALL_PATH}")
	
endmacro(ut_get_customized_app_creator)

if (WIN32)
	set(the_description "The UbiTrack DotNet Wrapper")
	if(HAVE_OPENCV)
	  ut_add_app(ubitrack_dotnet_swig DEPS utcore utdataflow utfacade utvision)
	  ut_app_include_directories(${TINYXML_INCLUDE_DIR} ${LOG4CPP_INCLUDE_DIR} ${BOOSTBINDINGS_INCLUDE_DIR} ${LAPACK_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
	else(HAVE_OPENCV)
	  ut_add_app(ubitrack_dotnet_swig DEPS utcore utdataflow utfacade)
	  ut_app_include_directories(${TINYXML_INCLUDE_DIR} ${LOG4CPP_INCLUDE_DIR} ${BOOSTBINDINGS_INCLUDE_DIR} ${LAPACK_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
	endif(HAVE_OPENCV)
	ut_glob_app_sources(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../Java/interface.i")
	ut_create_customized_app()
endif(WIN32)