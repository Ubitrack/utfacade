find_package(Java)

SET(UTJAVA_REQUIRED_DEPS utcore utdataflow utvision utfacade)
if(BUILD_UTJAVA)
    ut_include_modules(${UTJAVA_REQUIRED_DEPS} ${JNI_INCLUDE_DIRS})

        SET(CMAKE_SWIG_FLAGS "-v")
        
	SET(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack)
        SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES CPLUSPLUS ON)
        #SET_SOURCE_FILES_PROPERTIES(interface.i PROPERTIES SWIG_FLAGS "-package")

        SWIG_ADD_MODULE(ubitrack_java java interface.i)
        SWIG_LINK_LIBRARIES(ubitrack_java ${JNI_LIBRARIES} ${UBITRACK_LINKER_LIBS} ${UTJAVA_REQUIRED_DEPS})

	ADD_CUSTOM_COMMAND(TARGET ubitrack_java
		           POST_BUILD
		           COMMAND cmake -E echo "Compiling Java files..."
		           COMMAND cmake -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/classes/ubitrack
		           COMMAND ${Java_JAVAC_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/gensrc/ubitrack/*.java -d ${CMAKE_CURRENT_BINARY_DIR}/classes/ubitrack
		           COMMAND cmake -E echo "Creating jar file..."
		           COMMAND ${Java_JAR_EXECUTABLE} cvf ubitrack.jar -C ${CMAKE_CURRENT_BINARY_DIR}/classes ubitrack 
	)


# Need to install the wrapper files somewhere ..
endif(BUILD_UTJAVA)
