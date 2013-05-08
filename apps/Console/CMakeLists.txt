SET(UTCONSOLE_REQUIRED_DEPS utcore utdataflow utvision utfacade)

#ut_check_dependencies(${UTCONSOLE_REQUIRED_DEPS})

#MESSAGE(STATUS "UT_DEPENDENCIES FOUND ${UT_DEPENDENCIES_FOUND} ${HAVE_utcore}")
if(BUILD_UTCONSOLE)
  project(utConsole)

  #ut_include_directories("${utConsole_SOURCE_DIR}/include")#for opencv.hpp
  ut_include_modules(${UTCONSOLE_REQUIRED_DEPS})

  #if(CMAKE_COMPILER_IS_GNUCXX AND NOT ENABLE_NOISY_WARNINGS)
  #  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function")
  #endif()

  set(the_target "utConsole")
  set(srcs "console.cpp")
  
  add_executable(${the_target} ${srcs})
  target_link_libraries(${the_target} ${UBITRACK_LINKER_LIBS} ${UTCONSOLE_REQUIRED_DEPS})

  set_target_properties(${the_target} PROPERTIES
    OUTPUT_NAME "utConsole"
    PROJECT_LABEL "utConsole")

  if(WIN32)
    if (MSVC AND NOT BUILD_SHARED_LIBS)
      set_target_properties(${the_target} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:atlthunk.lib /NODEFAULTLIB:atlsd.lib /DEBUG")
    endif()
    install(TARGETS ${the_target}
            RUNTIME DESTINATION "${EXECUTABLE_OUTPUT_PATH}" COMPONENT main)
  endif()
endif(BUILD_UTCONSOLE)