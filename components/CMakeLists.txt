set(UBITRACK_LIBRARY_NAME utfacade_components)


include_directories(${CMAKE_SOURCE_DIR}/src)

# All cpp files for UTCORE
FILE(GLOB UBITRACK_SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
   "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*/*.cpp"
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*/*/*.cpp"
)

# All header files for UTCORE
FILE(GLOB UBITRACK_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
   "${CMAKE_CURRENT_SOURCE_DIR}/*.h"  
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*.h" 
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*/*.h"
   "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*/*/*.h"
)


# UTCORE library definition
ADD_LIBRARY(${UBITRACK_LIBRARY_NAME} ${UBITRACK_SRCS} ${UBITRACK_HEADERS})


target_link_libraries(${UBITRACK_LIBRARY_NAME} 
  CONAN_PKG::ubitrack_core
  CONAN_PKG::ubitrack_vision
  CONAN_PKG::ubitrack_dataflow
  utfacade
  OpenGL::GL
  OpenGL::GLU
  OpenCL::OpenCL
  )

target_include_directories(${UBITRACK_LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)


# Apply Target Properties
if(MSVC)
  if(CMAKE_CROSSCOMPILING)
    set_target_properties(${UBITRACK_LIBRARY_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:secchk")
  endif()
  set_target_properties(${UBITRACK_LIBRARY_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libc /DEBUG")
endif()

ubitrack_set_target_properties(${UBITRACK_LIBRARY_NAME})
ubitrack_install_headers(${UBITRACK_HEADERS})
ubitrack_install_component(${UBITRACK_LIBRARY_NAME})