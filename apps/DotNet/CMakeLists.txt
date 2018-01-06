set(UBITRACK_WRAPPER_NAME ubitrack_dotnet)

include(CMakeDetermineCSharpCompiler)
include(UbiTrackCSharpHelpers)

# All cpp files for UTCORE
file(GLOB UBITRACK_SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
   "${CMAKE_CURRENT_SOURCE_DIR}/../Java/*.i"
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/components)
include_directories(${JNI_INCLUDE_DIRS})

if(MSVC)
  set(UBITRACK_COMPILE_DEFINITIONS ${UBITRACK_COMPILE_DEFINITIONS} "BOOST_ALL_DYN_LINK")
endif(MSVC)

# ubitrack_java library definition
SET(CMAKE_SWIG_FLAGS "-v")

if(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "-fno-strict-aliasing")
endif(CMAKE_COMPILER_IS_GNUCXX)
SET(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack)

SET_SOURCE_FILES_PROPERTIES(${UBITRACK_SRCS} PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(${UBITRACK_SRCS} PROPERTIES SWIG_FLAGS "-namespace;ubitrack")

set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-I${CMAKE_SOURCE_DIR}/src")
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-I${CMAKE_SOURCE_DIR}/components")
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-I${CONAN_INCLUDE_DIRS_UBITRACK_CORE}")

SWIG_ADD_MODULE(${UBITRACK_WRAPPER_NAME}_swig csharp ${UBITRACK_SRCS})
SWIG_LINK_LIBRARIES(${UBITRACK_WRAPPER_NAME}_swig ${JNI_LIBRARIES} utfacade ${CONAN_LIBS})

ADD_CUSTOM_COMMAND(TARGET ${UBITRACK_WRAPPER_NAME}
	           POST_BUILD
	           COMMAND cmake -E echo "Compiling Java files..."
	           COMMAND cmake -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/classes/ubitrack
	           COMMAND ${Java_JAVAC_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack/*.java -d ${CMAKE_CURRENT_BINARY_DIR}/classes
	           COMMAND cmake -E echo "Creating jar file..."
	           COMMAND ${Java_JAR_EXECUTABLE} cvf ubitrack.jar -C ${CMAKE_CURRENT_BINARY_DIR}/classes ubitrack 
)

file(GLOB cs_srcs "${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack/*.cs")
csharp_add_library(${UBITRACK_WRAPPER_NAME} ${cs_srcs})


# Apply Target Properties
if(MSVC)
  if(CMAKE_CROSSCOMPILING)
    set_target_properties(${UBITRACK_WRAPPER_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:secchk")
  endif()
  set_target_properties(${UBITRACK_WRAPPER_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libc /DEBUG")
endif()

foreach(_flag ${UBITRACK_COMPILE_FLAGS})
  set_target_properties(${UBITRACK_WRAPPER_NAME} PROPERTIES COMPILE_FLAGS "${_flag}")
endforeach()
foreach(_flag ${UBITRACK_LINK_FLAGS})
  set_target_properties(${UBITRACK_WRAPPER_NAME} PROPERTIES LINK_FLAGS "${_flag}")
endforeach()
foreach(_flag ${UBITRACK_LINK_FLAGS_DEBUG})
  set_target_properties(${UBITRACK_WRAPPER_NAME} PROPERTIES LINK_FLAGS_DEBUG "${_flag}")
endforeach()
foreach(_symb ${UBITRACK_DEFINES})
  set_target_properties(${UBITRACK_WRAPPER_NAME} PROPERTIES DEFINE_SYMBOL ${_symb})
endforeach()

# set compiler Definitions
set_target_properties(${UBITRACK_WRAPPER_NAME} PROPERTIES COMPILE_DEFINITIONS "${UBITRACK_COMPILE_DEFINITIONS}")

install(TARGETS ${SWIG_MODULE_ubitrack_dotnet_swig_REAL_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT dotnet
  LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT dotnet
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
  )	
install_assembly(${UBITRACK_WRAPPER_NAME} DESTINATION "${CMAKE_INSTALL_BINDIR}")










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
	  RUNTIME DESTINATION bin COMPONENT dotnet
	  LIBRARY DESTINATION bin COMPONENT dotnet
	  ARCHIVE DESTINATION ${UBITRACK_LIB_INSTALL_PATH} COMPONENT dev
	)	

	file(GLOB cs_srcs "${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack/*.cs")
	csharp_add_library(ubitrack_dotnet ${cs_srcs})
	install_assembly(ubitrack_dotnet DESTINATION "bin")
	
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
	ut_glob_app_sources(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../Java/${UBITRACK_SRCS}")
	ut_create_customized_app()
endif(WIN32)