set(UBITRACK_WRAPPER_NAME ubitrack_java)

find_package(Java REQUIRED)

# All cpp files for UTCORE
file(GLOB UBITRACK_SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
   "${CMAKE_CURRENT_SOURCE_DIR}/*.i"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/components)
include_directories(${JNI_INCLUDE_DIRS})

# ubitrack_java library definition
SET(CMAKE_SWIG_FLAGS "-v")

if(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "-fno-strict-aliasing")
endif(CMAKE_COMPILER_IS_GNUCXX)
SET(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack)

SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES SWIG_FLAGS "-package;ubitrack")

set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-I${CMAKE_SOURCE_DIR}/src")
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-I${CMAKE_SOURCE_DIR}/components")
set(CMAKE_SWIG_FLAGS ${CMAKE_SWIG_FLAGS} "-I${CONAN_INCLUDE_DIRS_UBITRACK_CORE}")

SWIG_ADD_MODULE(${UBITRACK_WRAPPER_NAME} java ${UBITRACK_SRCS})
SWIG_LINK_LIBRARIES(${UBITRACK_WRAPPER_NAME} ${JNI_LIBRARIES} utfacade ${CONAN_LIBS})

ADD_CUSTOM_COMMAND(TARGET ${UBITRACK_WRAPPER_NAME}
	           POST_BUILD
	           COMMAND cmake -E echo "Compiling Java files..."
	           COMMAND cmake -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/classes/ubitrack
	           COMMAND ${Java_JAVAC_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack/*.java -d ${CMAKE_CURRENT_BINARY_DIR}/classes
	           COMMAND cmake -E echo "Creating jar file..."
	           COMMAND ${Java_JAR_EXECUTABLE} cvf ubitrack.jar -C ${CMAKE_CURRENT_BINARY_DIR}/classes ubitrack 
)

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

install(TARGETS ${SWIG_MODULE_ubitrack_java_REAL_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT java
  LIBRARY DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT java
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
  )	
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ubitrack.jar DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT java)
